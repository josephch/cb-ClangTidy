/***************************************************************
 * Name:      CbClangTidy.h
 * Purpose:   Code::Blocks CbClangTidy plugin: main functions
 * Author:    Lieven de Cock (aka killerbot)
 * Created:   12/11/2009
 * Copyright: (c) Lieven de Cock (aka killerbot)
 * License:   GPL
 **************************************************************/

#ifndef CBCLANGTIDY_H_INCLUDED
#define CBCLANGTIDY_H_INCLUDED

#include "cbplugin.h" // the base class we 're inheriting

#include <wx/string.h>

class wxArrayString;
class cbProject;
class ConfigManager;
class TextCtrlLogger;
class CbClangTidyListLog;

class CbClangTidy : public cbToolPlugin
{
  public:
    CbClangTidy();
    ~CbClangTidy();
    void OnAttach();                  // fires when the plugin is attached to the application
    void OnRelease(bool appShutDown); // fires when the plugin is released from the application

    int Execute();

    virtual cbConfigurationPanel* GetConfigurationPanel(wxWindow* /*parent*/);

  private:
    void WriteToLog(const wxString& Text);
    void AppendToLog(const wxString& Text);

    //{ CbClangTidy
    struct SCbClangTidyAttribs
    {
        wxString InputFileName;
        wxString IncludeList;
        wxString DefineList;
    };
    typedef struct SCbClangTidyAttribs TCbClangTidyAttribs;

    int ExecuteCbClangTidy(cbProject* Project);
    int DoCbClangTidyExecute(TCbClangTidyAttribs& CbClangTidyAttribs);
    //} CbClangTidy

    bool DoVersion(const wxString& app, const wxString& app_cfg);
    bool AppExecute(const wxString& app, const wxString& CommandLine, wxArrayString& Output, wxArrayString& Errors);
    bool AppExecuteWithBusyBanner(const wxString& app, const wxString& CommandLine, wxArrayString& Output, wxArrayString& Errors);
    wxString GetAppExecutable(const wxString& app, const wxString& app_cfg);

    CbClangTidyListLog* m_ListLog; //!< log tab to click/double click to take you to offending line of code
    int m_ListLogPageIndex;        //!< index of our list log tab

    wxString m_PATH;
};

#endif // CBCLANGTIDY_H_INCLUDED
