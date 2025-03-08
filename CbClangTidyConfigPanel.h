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
    wxStaticLine* StaticLine1;
    wxStaticLine* StaticLine2;
    wxTextCtrl* txtCbClangTidyApp;
    wxTextCtrl* txtCbClangTidyArgs;
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

  protected:
    //(*Identifiers(CbClangTidyConfigPanel)
    static const wxWindowID ID_TXT_CLANG_TIDY_APP;
    static const wxWindowID ID_BTN_CLANG_TIDY_APP;
    static const wxWindowID ID_TXT_CLANG_TIDY_ARGS;
    static const wxWindowID ID_HYC_CLANG_TIDY_WWW;
    static const wxWindowID ID_STATICLINE1;
    static const wxWindowID ID_STATICLINE2;
    static const wxWindowID ID_CHO_OPERATION;
    //*)

  private:
    //(*Handlers(CbClangTidyConfigPanel)
    void OnCbClangTidyApp(wxCommandEvent& event);
    //*)

    DECLARE_EVENT_TABLE()
};

#endif
