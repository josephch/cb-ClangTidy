#include "CbClangTidyConfigPanel.h"

#include <wx/filedlg.h>

#include <configmanager.h>
#include <manager.h>

//(*InternalHeaders(CbClangTidyConfigPanel)
#include <wx/button.h>
#include <wx/choice.h>
#include <wx/hyperlink.h>
#include <wx/intl.h>
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/stattext.h>
#include <wx/string.h>
#include <wx/textctrl.h>
//*)

//(*IdInit(CbClangTidyConfigPanel)
const wxWindowID CbClangTidyConfigPanel::ID_TXT_CLANG_TIDY_APP = wxNewId();
const wxWindowID CbClangTidyConfigPanel::ID_BTN_CLANG_TIDY_APP = wxNewId();
const wxWindowID CbClangTidyConfigPanel::ID_TXT_CLANG_TIDY_ARGS = wxNewId();
const wxWindowID CbClangTidyConfigPanel::ID_HYC_CLANG_TIDY_WWW = wxNewId();
//*)

BEGIN_EVENT_TABLE(CbClangTidyConfigPanel, wxPanel)
//(*EventTable(CbClangTidyConfigPanel)
//*)
END_EVENT_TABLE()

CbClangTidyConfigPanel::CbClangTidyConfigPanel(wxWindow* parent)
{
    //(*Initialize(CbClangTidyConfigPanel)
    wxBoxSizer* bszCbClangTidyApp;
    wxBoxSizer* bszMain;
    wxButton* btnCbClangTidyApp;
    wxFlexGridSizer* flsMain;
    wxHyperlinkCtrl* hycCbClangTidyWWW;
    wxStaticLine* slSeparatorLeft;
    wxStaticLine* slSeparatorRight;
    wxStaticText* lblCbClangTidyApp;
    wxStaticText* lblCbClangTidyArgs;
    wxStaticText* lblCbClangTidyArgsComment;
    wxStaticText* lblCbClangTidyWWW;

    Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
    bszMain = new wxBoxSizer(wxHORIZONTAL);
    flsMain = new wxFlexGridSizer(0, 2, 0, 0);
    flsMain->AddGrowableCol(1);
    lblCbClangTidyApp = new wxStaticText(this, wxID_ANY, _("CbClangTidy application:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
    flsMain->Add(lblCbClangTidyApp, 0, wxLEFT | wxALIGN_CENTER_VERTICAL, 5);
    bszCbClangTidyApp = new wxBoxSizer(wxHORIZONTAL);
    txtCbClangTidyApp = new wxTextCtrl(this, ID_TXT_CLANG_TIDY_APP, _("clang-tidy"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TXT_CPP_CHECK_APP"));
    bszCbClangTidyApp->Add(txtCbClangTidyApp, 1, wxEXPAND, 5);
    btnCbClangTidyApp = new wxButton(this, ID_BTN_CLANG_TIDY_APP, _T("..."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BTN_CLANG_TIDY_APP"));
    btnCbClangTidyApp->SetMinSize(wxSize(30, -1));
    bszCbClangTidyApp->Add(btnCbClangTidyApp, 0, wxLEFT | wxALIGN_CENTER_VERTICAL, 5);
    flsMain->Add(bszCbClangTidyApp, 1, wxLEFT | wxEXPAND, 5);
    lblCbClangTidyArgs = new wxStaticText(this, wxID_ANY, _("CbClangTidy arguments:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
    flsMain->Add(lblCbClangTidyArgs, 0, wxTOP | wxLEFT | wxALIGN_CENTER_VERTICAL, 5);
    txtCbClangTidyArgs = new wxTextCtrl(this, ID_TXT_CLANG_TIDY_ARGS, _("--verbose --enable=all --enable=style --xml"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TXT_CPP_CHECK_ARGS"));
    txtCbClangTidyArgs->SetMinSize(wxSize(240, -1));
    flsMain->Add(txtCbClangTidyArgs, 1, wxTOP | wxLEFT | wxEXPAND, 5);
    lblCbClangTidyArgsComment = new wxStaticText(this, wxID_ANY, _("(before \"--file-list\")"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
    flsMain->Add(lblCbClangTidyArgsComment, 0, wxLEFT | wxALIGN_TOP, 5);
    flsMain->Add(-1, -1, 1, wxLEFT | wxEXPAND, 5);
    lblCbClangTidyWWW = new wxStaticText(this, wxID_ANY, _("CbClangTidy homepage:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
    flsMain->Add(lblCbClangTidyWWW, 0, wxTOP | wxLEFT | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
    hycCbClangTidyWWW = new wxHyperlinkCtrl(this, ID_HYC_CLANG_TIDY_WWW, _("https://clang.llvm.org/extra/clang-tidy/"), wxEmptyString, wxDefaultPosition, wxDefaultSize, wxHL_CONTEXTMENU | wxHL_ALIGN_CENTRE, _T("ID_HYC_CPP_CHECK_WWW"));
    flsMain->Add(hycCbClangTidyWWW, 1, wxTOP | wxLEFT | wxEXPAND, 5);
    slSeparatorLeft = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxSize(10, -1), wxLI_HORIZONTAL, _T("wxID_ANY"));
    flsMain->Add(slSeparatorLeft, 0, wxTOP | wxBOTTOM | wxLEFT | wxEXPAND, 5);
    slSeparatorRight = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxSize(10, -1), wxLI_HORIZONTAL, _T("wxID_ANY"));
    flsMain->Add(slSeparatorRight, 0, wxTOP | wxBOTTOM | wxEXPAND, 5);
    flsMain->Add(-1, -1, 1, wxLEFT | wxEXPAND, 5);
    bszMain->Add(flsMain, 1, wxEXPAND, 5);
    SetSizer(bszMain);
    bszMain->SetSizeHints(this);

    Connect(ID_BTN_CLANG_TIDY_APP, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CbClangTidyConfigPanel::OnCbClangTidyApp));
    //*)

    ConfigManager* cfg = Manager::Get()->GetConfigManager(_T("clang-tidy"));
    if (cfg)
    {
        txtCbClangTidyApp->SetValue(cfg->Read(_T("clang-tidy_app"),
                                              GetDefaultCbClangTidyExecutableName()));
        txtCbClangTidyArgs->SetValue(cfg->Read(_T("clang-tidy_args")));
    }
}

CbClangTidyConfigPanel::~CbClangTidyConfigPanel()
{
    //(*Destroy(CbClangTidyConfigPanel)
    //*)
}

void CbClangTidyConfigPanel::OnCbClangTidyApp(cb_unused wxCommandEvent& event)
{
    wxFileName initialFile(txtCbClangTidyApp->GetValue());
    wxFileDialog dialog(this, _("Select CbClangTidy application"),
                        initialFile.GetPath(),
                        GetDefaultCbClangTidyExecutableName(),
#ifdef __WXMSW__
                        _("Executable files (*.exe)|*.exe"),
#else
                        _("Executable files (*)|*"),
#endif
                        wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    PlaceWindow(&dialog);
    if (dialog.ShowModal() == wxID_OK)
        txtCbClangTidyApp->SetValue(dialog.GetPath());
}

void CbClangTidyConfigPanel::OnApply()
{
    ConfigManager* cfg = Manager::Get()->GetConfigManager(_T("clang-tidy"));
    if (cfg)
    {
        wxString app = txtCbClangTidyApp->GetValue();
        if (!app.IsEmpty())
            cfg->Write(_T("clang-tidy_app"), app);
        if (!txtCbClangTidyArgs->GetValue().IsEmpty())
            cfg->Write(_T("clang-tidy_args"), txtCbClangTidyArgs->GetValue());
    }
}

wxString CbClangTidyConfigPanel::GetDefaultCbClangTidyExecutableName()
{
#ifdef __WXMSW__
    return _T("clang-tidy.exe");
#else
    return _T("clang-tidy");
#endif
}
