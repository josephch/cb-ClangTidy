/***************************************************************
 * Name:      CbClangTidy.h
 * Purpose:   Code::Blocks CbClangTidy plugin: main functions
 * Author:    Lieven de Cock (aka killerbot)
 * Created:   12/11/2009
 * Copyright: (c) Lieven de Cock (aka killerbot)
 * License:   GPL
 **************************************************************/

#ifndef CPPCHECK_H_INCLUDED
#define CPPCHECK_H_INCLUDED

#include "cbplugin.h" // the base class we 're inheriting

#include <tinyxml.h>
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
    void DoCbClangTidyAnalysis(const wxString& Xml);
    bool DoCbClangTidyParseXMLv1(TiXmlHandle& Handle);
    bool DoCbClangTidyParseXMLv2(TiXmlHandle& Handle);
    //} CbClangTidy

    bool DoVersion(const wxString& app, const wxString& app_cfg);
    bool AppExecute(const wxString& app, const wxString& CommandLine, wxArrayString& Output, wxArrayString& Errors);
    wxString GetAppExecutable(const wxString& app, const wxString& app_cfg);

    TextCtrlLogger* m_CbClangTidyLog; //!< log tab in the message pane
    CbClangTidyListLog* m_ListLog;    //!< log tab to click/double click to take you to offending line of code
    int m_LogPageIndex;               //!< index of our log tab (can this change during run time ??)
    int m_ListLogPageIndex;           //!< index of our list log tab

    wxString m_PATH;
};

#endif // CPPCHECK_H_INCLUDED
