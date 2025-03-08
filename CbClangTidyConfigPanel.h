#ifndef CONFIGPANEL_H
#define CONFIGPANEL_H

//(*Headers(CbClangTidyConfigPanel)
#include <wx/panel.h>
class wxBoxSizer;
class wxButton;
class wxChoice;
class wxFlexGridSizer;
class wxHyperlinkCtrl;
class wxStaticLine;
class wxStaticText;
class wxTextCtrl;
//*)

#include <wx/string.h>

#include <configurationpanel.h>

class CbClangTidy;

class CbClangTidyConfigPanel : public cbConfigurationPanel
{
public:

    CbClangTidyConfigPanel(wxWindow* parent);
    virtual ~CbClangTidyConfigPanel();

    //(*Declarations(CbClangTidyConfigPanel)
    wxChoice* choOperation;
    wxStaticLine* StaticLine1;
    wxStaticLine* StaticLine2;
    wxTextCtrl* txtCbClangTidyApp;
    wxTextCtrl* txtCbClangTidyArgs;
    wxTextCtrl* txtVeraApp;
    wxTextCtrl* txtVeraArgs;
    //*)

    /// @return the panel's title.
    virtual wxString GetTitle() const { return _("CbClangTidy"); }
    /// @return the panel's bitmap base name. You must supply two bitmaps: \<basename\>.png and \<basename\>-off.png...
    virtual wxString GetBitmapBaseName() const { return wxT("CbClangTidy"); }
    /// Called when the user chooses to apply the configuration.
    virtual void OnApply();
    /// Called when the user chooses to cancel the configuration.
    virtual void OnCancel() { ; }

    static wxString GetDefaultCbClangTidyExecutableName();
    static wxString GetDefaultVeraExecutableName();
protected:

    //(*Identifiers(CbClangTidyConfigPanel)
    static const wxWindowID ID_TXT_CPP_CHECK_APP;
    static const wxWindowID ID_BTN_CPPCHECK_APP;
    static const wxWindowID ID_TXT_CPP_CHECK_ARGS;
    static const wxWindowID ID_HYC_CPP_CHECK_WWW;
    static const wxWindowID ID_TXT_VERA_APP;
    static const wxWindowID ID_BTN_VERA;
    static const wxWindowID ID_TXT_VERA_ARGS;
    static const wxWindowID ID_HYC_VERA_WWW;
    static const wxWindowID ID_STATICLINE1;
    static const wxWindowID ID_STATICLINE2;
    static const wxWindowID ID_CHO_OPERATION;
    //*)

private:

    //(*Handlers(CbClangTidyConfigPanel)
    void OnCbClangTidyApp(wxCommandEvent& event);
    void OnVeraApp(wxCommandEvent& event);
    //*)

    DECLARE_EVENT_TABLE()
};

#endif
