/***************************************************************
 * Name:      CbClangTidy.cpp
 * Purpose:   Code::Blocks CbClangTidy plugin: main functions
 * Author:    Lieven de Cock (aka killerbot)
 * Created:   12/11/2009
 * Copyright: (c) Lieven de Cock (aka killerbot)
 * License:   GPL
 **************************************************************/
#include "sdk.h"
#ifndef CB_PRECOMP
    #include <wx/arrstr.h>
    #include <wx/dir.h>
    #include <wx/file.h>
    #include <wx/filefn.h>
    #include <wx/filename.h>
    #include <wx/fs_zip.h>
    #include <wx/intl.h>
    #include <wx/menu.h>
    #include <wx/string.h>
    #include <wx/xrc/xmlres.h>

    #include "cbplugin.h"
    #include "cbproject.h"
    #include "configmanager.h"
    #include "logmanager.h"
    #include "macrosmanager.h"
    #include "manager.h"
    #include "pluginmanager.h"
    #include "projectmanager.h"
#endif

#include <wx/busyinfo.h>
#include <wx/filedlg.h>
#include <wx/filefn.h>
#include <wx/utils.h>

#include "filefilters.h"
#include "loggers.h"
#include <tinyxml.h>

#include "CbClangTidy.h"
#include "CbClangTidyConfigPanel.h"
#include "CbClangTidyListLog.h"

#define PARSE_CLANG_TIDY_OUTPUT
#ifdef PARSE_CLANG_TIDY_OUTPUT
    #include "compiler-output-parser/compiler_output_parser.hpp"
#endif

// Register the plugin
namespace
{
    PluginRegistrant<CbClangTidy> reg(_T("CbClangTidy"));
};

namespace
{
    bool CheckRequirements()
    {
        cbProject* Project = Manager::Get()->GetProjectManager()->GetActiveProject();
        // if no project open, exit
        if (!Project)
        {
            wxString msg = _("You need to open a project\nbefore using the plugin!");
            cbMessageBox(msg, _("Error"), wxICON_ERROR | wxOK, Manager::Get()->GetAppWindow());
            Manager::Get()->GetLogManager()->DebugLog(msg);
            return false;
        }
        return true;
    }
}; // namespace

CbClangTidy::CbClangTidy() : m_ListLog(0),
                             m_ListLogPageIndex(0),
                             m_PATH(wxEmptyString)
{
}

CbClangTidy::~CbClangTidy()
{
}

void CbClangTidy::OnAttach()
{
    // do whatever initialization you need for your plugin
    // NOTE: after this function, the inherited member variable
    // IsAttached() will be TRUE...
    // You should check for it in other functions, because if it
    // is FALSE, it means that the application did *not* "load"
    // (see: does not need) this plugin...
    if (LogManager* LogMan = Manager::Get()->GetLogManager())
    {
        wxArrayString Titles;
        wxArrayInt Widths;
        Titles.Add(_("File"));
        Widths.Add(128);
        Titles.Add(_("Line"));
        Widths.Add(48);
        Titles.Add(_("Message"));
        Widths.Add(640);
        m_ListLog = new CbClangTidyListLog(Titles, Widths);

        m_ListLogPageIndex = LogMan->SetLog(m_ListLog);
        LogMan->Slot(m_ListLogPageIndex).title = _("ClangTidy");
        CodeBlocksLogEvent evtAdd2(cbEVT_ADD_LOG_WINDOW, m_ListLog, LogMan->Slot(m_ListLogPageIndex).title);
        Manager::Get()->ProcessEvent(evtAdd2);
    }
}

void CbClangTidy::OnRelease(bool /*appShutDown*/)
{
    // do de-initialization for your plugin
    // if appShutDown is false, the plugin is unloaded because Code::Blocks is being shut down,
    // which means you must not use any of the SDK Managers
    // NOTE: after this function, the inherited member variable
    // IsAttached() will be FALSE...
    if (Manager::Get()->GetLogManager())
    {
        if (m_ListLog)
        {
            CodeBlocksLogEvent evt(cbEVT_REMOVE_LOG_WINDOW, m_ListLog);
            m_ListLog->DestroyControls();
            Manager::Get()->ProcessEvent(evt);
        }
    }
    m_ListLog = nullptr;
}

void CbClangTidy::WriteToLog(const wxString& Text)
{
    m_ListLog->Clear();
    AppendToLog(Text);
}

void CbClangTidy::AppendToLog(const wxString& Text)
{
    wxArrayString Arr;
    Arr.Add(wxEmptyString);
    Arr.Add(wxEmptyString);
    Arr.Add(Text);
    m_ListLog->Append(Arr, Logger::level::info);
    CodeBlocksLogEvent evtSwitch(cbEVT_SWITCH_TO_LOG_WINDOW, m_ListLog);
    Manager::Get()->ProcessEvent(evtSwitch);
}

cbConfigurationPanel* CbClangTidy::GetConfigurationPanel(wxWindow* parent)
{
    // Called by plugin manager to show config panel in global Setting Dialog
    if (!IsAttached())
        return NULL;

    return new CbClangTidyConfigPanel(parent);
}

int CbClangTidy::Execute()
{
    WriteToLog(_("Running clang-tidy analysis... please wait..."));

    if (!CheckRequirements())
        return -1;

    cbProject* Project = Manager::Get()->GetProjectManager()->GetActiveProject();
    if (Project->GetFilesCount() < 1)
        return 0;

    const wxString BasePath = Project->GetBasePath();
    AppendToLog(_("Switching working directory to : ") + BasePath);
    ::wxSetWorkingDirectory(BasePath);

    return ExecuteCbClangTidy(Project);
}

//{ CbClangTidy
int CbClangTidy::ExecuteCbClangTidy(cbProject* Project)
{
    if (!DoVersion(_T("clang-tidy"), _T("clang-tidy_app")))
        return -1;

    TCbClangTidyAttribs CbClangTidyAttribs;

    wxFile InputFile;
    CbClangTidyAttribs.InputFileName = _T("CbClangTidyInput.txt");
    if (!InputFile.Create(CbClangTidyAttribs.InputFileName, true))
    {
        cbMessageBox(_("Failed to create input file 'CbClangTidyInput.txt' for clang-tidy.\nPlease check file/folder access rights."),
                     _("Error"), wxICON_ERROR | wxOK, Manager::Get()->GetAppWindow());
        return -1;
    }
    wxFileName compileCommands(Project->GetFilename());
    compileCommands.SetFullName("compile_commands.json");
    InputFile.Write(_T("-p ") + compileCommands.GetFullPath() + _T("\n"));
    for (FilesList::iterator it = Project->GetFilesList().begin(); it != Project->GetFilesList().end(); ++it)
    {
        ProjectFile* pf = *it;
        // filter to avoid including non C/C++ files
        if (pf->relativeFilename.EndsWith(FileFilters::C_DOT_EXT) || pf->relativeFilename.EndsWith(FileFilters::CPP_DOT_EXT) || pf->relativeFilename.EndsWith(FileFilters::CC_DOT_EXT) || pf->relativeFilename.EndsWith(FileFilters::CXX_DOT_EXT) || pf->relativeFilename.EndsWith(FileFilters::CPLPL_DOT_EXT) || (FileTypeOf(pf->relativeFilename) == ftHeader) || (FileTypeOf(pf->relativeFilename) == ftTemplateSource))
        {
            InputFile.Write(pf->relativeFilename + _T("\n"));
        }
    }
    InputFile.Close();

    MacrosManager* MacrosMgr = Manager::Get()->GetMacrosManager();
    ProjectBuildTarget* Target = Project->GetBuildTarget(Project->GetActiveBuildTarget());

    // project include dirs
    const wxArrayString& IncludeDirs = Project->GetIncludeDirs();
    for (unsigned int Dir = 0; Dir < IncludeDirs.GetCount(); ++Dir)
    {
        wxString IncludeDir(IncludeDirs[Dir]);
        if (Target)
            MacrosMgr->ReplaceMacros(IncludeDir, Target);
        else
            MacrosMgr->ReplaceMacros(IncludeDir);
        CbClangTidyAttribs.IncludeList += _T("-I\"") + IncludeDir + _T("\" ");
    }
    if (Target)
    {
        // target include dirs
        const wxArrayString& targetIncludeDirs = Target->GetIncludeDirs();
        for (unsigned int Dir = 0; Dir < targetIncludeDirs.GetCount(); ++Dir)
        {
            wxString IncludeDir(targetIncludeDirs[Dir]);
            MacrosMgr->ReplaceMacros(IncludeDir, Target);
            CbClangTidyAttribs.IncludeList += _T("-I\"") + IncludeDir + _T("\" ");
        }
    }

    // project #defines
    const wxArrayString& Defines = Project->GetCompilerOptions();
    for (unsigned int Opt = 0; Opt < Defines.GetCount(); ++Opt)
    {
        wxString Define(Defines[Opt]);
        if (Target)
            MacrosMgr->ReplaceMacros(Define, Target);
        else
            MacrosMgr->ReplaceMacros(Define);

        if (Define.StartsWith(_T("-D")))
            CbClangTidyAttribs.DefineList += Define + _T(" ");
    }
    if (Target)
    {
        // target #defines
        const wxArrayString& targetDefines = Target->GetCompilerOptions();
        for (unsigned int Opt = 0; Opt < targetDefines.GetCount(); ++Opt)
        {
            wxString Define(targetDefines[Opt]);
            MacrosMgr->ReplaceMacros(Define, Target);

            if (Define.StartsWith(_T("-D")))
                CbClangTidyAttribs.DefineList += Define + _T(" ");
        }
    }

    return DoCbClangTidyExecute(CbClangTidyAttribs);
}

int CbClangTidy::DoCbClangTidyExecute(TCbClangTidyAttribs& CbClangTidyAttribs)
{
    ConfigManager* cfg = Manager::Get()->GetConfigManager(_T("clang-tidy"));

    wxString CppExe = GetAppExecutable(_T("clang-tidy"), _T("clang-tidy_app"));
    wxString CppArgs = cfg->Read(_T("clang-tidy_args"));
    Manager::Get()->GetMacrosManager()->ReplaceMacros(CppArgs);
    wxString CommandLine = CppExe + _T(" ") + CppArgs + _T(" @") + CbClangTidyAttribs.InputFileName;

    wxArrayString Output, Errors;
    bool isOK = AppExecuteWithBusyBanner(_T("clang-tidy"), CommandLine, Output, Errors);
    ::wxRemoveFile(CbClangTidyAttribs.InputFileName);
    if (!isOK)
        return -1;
    std::string line;
    bool logsPresent = false;
    for (size_t idxCount = 0; idxCount < Output.GetCount(); ++idxCount)
    {
#ifdef DEBUG
        fprintf(stderr, "Output[%zu] : %s\n", idxCount, Output[idxCount].ToUTF8().data());
#endif
#ifdef PARSE_CLANG_TIDY_OUTPUT
        Logger::level level = Logger::level::info;
        wxArrayString Arr;
        std::string line = Output[idxCount].ToStdString();
        CompilerOutputLineInfo compilerOutputLineInfo = ::GetCompilerOutputLineInfo(line);
        if (compilerOutputLineInfo.type != CompilerOutputLineType::normal)
        {
            switch (compilerOutputLineInfo.type)
            {
            case CompilerOutputLineType::error:
                level = Logger::level::error;
                break;
            case CompilerOutputLineType::warning:
                level = Logger::level::warning;
                break;
            default:
                break;
            }
            int i = 0;
            Arr.Add(compilerOutputLineInfo.fileName);
            Arr.Add(compilerOutputLineInfo.line);
            Arr.Add(compilerOutputLineInfo.message);
        }
        else
        {
            Arr.Add(wxEmptyString);
            Arr.Add(wxEmptyString);
            Arr.Add(line);
        }
        m_ListLog->Append(Arr, level);
        logsPresent = true;
#endif
    }
    for (size_t idxCount = 0; idxCount < Errors.GetCount(); ++idxCount)
    {
#ifdef DEBUG
        fprintf(stderr, "Errors[%zu] : %s\n", idxCount, Errors[idxCount].ToUTF8().data());
#endif
        AppendToLog(Errors[idxCount]);
    }

    if (logsPresent)
    {
        if (Manager::Get()->GetLogManager())
        {
            CodeBlocksLogEvent evtSwitch(cbEVT_SWITCH_TO_LOG_WINDOW, m_ListLog);
            Manager::Get()->ProcessEvent(evtSwitch);
        }
    }
    return 0;
}

bool CbClangTidy::DoVersion(const wxString& app, const wxString& app_cfg)
{
    wxString app_exe = GetAppExecutable(app, app_cfg);

    wxArrayString Output, Errors;
    wxString CommandLine = app_exe + _T(" --version");
    bool ret = AppExecute(app, CommandLine, Output, Errors);

    int Count = Output.GetCount();
    for (int idxCount = 0; idxCount < Count; ++idxCount)
        AppendToLog(Output[idxCount]);

    Count = Errors.GetCount();
    for (int idxCount = 0; idxCount < Count; ++idxCount)
        AppendToLog(Errors[idxCount]);
    return ret;
}

bool CbClangTidy::AppExecuteWithBusyBanner(const wxString& app, const wxString& CommandLine, wxArrayString& Output, wxArrayString& Errors)
{
    wxWindowDisabler disableAll;
    wxBusyInfo running(wxString::Format(_("Running %s... please wait (this may take several minutes)..."), app),
                       Manager::Get()->GetAppWindow());
    return AppExecute(app, CommandLine, Output, Errors);
}

bool CbClangTidy::AppExecute(const wxString& app, const wxString& CommandLine, wxArrayString& Output, wxArrayString& Errors)
{
    AppendToLog(CommandLine);
    if (-1 == wxExecute(CommandLine, Output, Errors, wxEXEC_SYNC))
    {
        wxString msg;
        msg.Printf(_("Failed to launch %s.\nPlease setup the %s executable accordingly in the settings\n"
                     "and make sure it is also in the path so %s resources are found."),
                   app, app, app);

        AppendToLog(msg);
        cbMessageBox(msg, _("Error"), wxICON_ERROR | wxOK, Manager::Get()->GetAppWindow());
        if (!m_PATH.empty())
            wxSetEnv("PATH", m_PATH); // Restore

        return false;
    }

    if (!m_PATH.IsEmpty())
        wxSetEnv(wxT("PATH"), m_PATH); // Restore
    return true;
}

wxString CbClangTidy::GetAppExecutable(const wxString& app, const wxString& app_cfg)
{
    ConfigManager* cfg = Manager::Get()->GetConfigManager(_T("clang-tidy"));
    wxString Executable = CbClangTidyConfigPanel::GetDefaultCbClangTidyExecutableName();
    if (cfg)
        Executable = cfg->Read(app_cfg, Executable);
    Manager::Get()->GetMacrosManager()->ReplaceMacros(Executable);

    AppendToLog(wxString::Format(_("Executable %s: '%s'."), app, Executable));

    // Make sure file is accessible, otherwise add path to clang-tidy to PATH envvar
    wxFileName fn(Executable);
    if (fn.IsOk() && fn.FileExists())
    {
        wxString AppPath = fn.GetPath();
        AppendToLog(wxString::Format(_("Path to %s: '%s'."), app, AppPath));

        if (AppPath.Trim().IsEmpty())
            return Executable; // Nothing to do, lets hope it works and clang-tidy is in the PATH

        bool PrependPath = true;
        wxString NewPathEnvVar = wxEmptyString;

        wxPathList PathList;
        PathList.AddEnvList(wxT("PATH"));
        for (size_t i = 0; i < PathList.GetCount(); ++i)
        {
            wxString PathItem = PathList.Item(i);
            if (PathItem.IsSameAs(AppPath, (platform::windows ? false : true)))
            {
                AppendToLog(_("Executable of clang-tidy is in the path."));
                PrependPath = false;
                break; // Exit for-loop
            }

            if (!NewPathEnvVar.IsEmpty())
                NewPathEnvVar << wxPATH_SEP;
            NewPathEnvVar << PathItem;
        }

        if (m_PATH.IsEmpty())
            m_PATH = NewPathEnvVar;

        if (PrependPath)
        {
            NewPathEnvVar = NewPathEnvVar.Prepend(wxPATH_SEP);
            NewPathEnvVar = NewPathEnvVar.Prepend(AppPath);
            wxSetEnv("PATH", NewPathEnvVar); // Don't care about return value
            AppendToLog(wxString::Format(_("Updated PATH environment to include path to %s: '%s' ('%s')."),
                                         app, AppPath, NewPathEnvVar));
        }
    }

    return Executable;
}
