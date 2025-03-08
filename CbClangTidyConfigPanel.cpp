#include "CbClangTidyConfigPanel.h"

#include <wx/filedlg.h>

#include <manager.h>
#include <configmanager.h>

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
const wxWindowID CbClangTidyConfigPanel::ID_TXT_CPP_CHECK_APP = wxNewId();
const wxWindowID CbClangTidyConfigPanel::ID_BTN_CPPCHECK_APP = wxNewId();
const wxWindowID CbClangTidyConfigPanel::ID_TXT_CPP_CHECK_ARGS = wxNewId();
const wxWindowID CbClangTidyConfigPanel::ID_HYC_CPP_CHECK_WWW = wxNewId();
const wxWindowID CbClangTidyConfigPanel::ID_TXT_VERA_APP = wxNewId();
const wxWindowID CbClangTidyConfigPanel::ID_BTN_VERA = wxNewId();
const wxWindowID CbClangTidyConfigPanel::ID_TXT_VERA_ARGS = wxNewId();
const wxWindowID CbClangTidyConfigPanel::ID_HYC_VERA_WWW = wxNewId();
const wxWindowID CbClangTidyConfigPanel::ID_STATICLINE1 = wxNewId();
const wxWindowID CbClangTidyConfigPanel::ID_STATICLINE2 = wxNewId();
const wxWindowID CbClangTidyConfigPanel::ID_CHO_OPERATION = wxNewId();
//*)

BEGIN_EVENT_TABLE(CbClangTidyConfigPanel,wxPanel)
    //(*EventTable(CbClangTidyConfigPanel)
    //*)
END_EVENT_TABLE()

CbClangTidyConfigPanel::CbClangTidyConfigPanel(wxWindow* parent)
{
    //(*Initialize(CbClangTidyConfigPanel)
    wxBoxSizer* bszCbClangTidyApp;
    wxBoxSizer* bszMain;
    wxBoxSizer* bszVeraApp;
    wxButton* btnCbClangTidyApp;
    wxButton* btnVeraApp;
    wxFlexGridSizer* flsMain;
    wxHyperlinkCtrl* hycCbClangTidyWWW;
    wxHyperlinkCtrl* hycVeraWWW;
    wxStaticLine* slSeparatorLeft;
    wxStaticLine* slSeparatorRight;
    wxStaticText* lblCbClangTidyApp;
    wxStaticText* lblCbClangTidyArgs;
    wxStaticText* lblCbClangTidyArgsComment;
    wxStaticText* lblCbClangTidyWWW;
    wxStaticText* lblOperation;
    wxStaticText* lblVeraApp;
    wxStaticText* lblVeraArgs;
    wxStaticText* lblVeraArgsComment;
    wxStaticText* lblVeraWWW;

    Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
    bszMain = new wxBoxSizer(wxHORIZONTAL);
    flsMain = new wxFlexGridSizer(0, 2, 0, 0);
    flsMain->AddGrowableCol(1);
    lblCbClangTidyApp = new wxStaticText(this, wxID_ANY, _("CbClangTidy application:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
    flsMain->Add(lblCbClangTidyApp, 0, wxLEFT|wxALIGN_CENTER_VERTICAL, 5);
    bszCbClangTidyApp = new wxBoxSizer(wxHORIZONTAL);
    txtCbClangTidyApp = new wxTextCtrl(this, ID_TXT_CPP_CHECK_APP, _("cppcheck"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TXT_CPP_CHECK_APP"));
    bszCbClangTidyApp->Add(txtCbClangTidyApp, 1, wxEXPAND, 5);
    btnCbClangTidyApp = new wxButton(this, ID_BTN_CPPCHECK_APP, _T("..."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BTN_CPPCHECK_APP"));
    btnCbClangTidyApp->SetMinSize(wxSize(30,-1));
    bszCbClangTidyApp->Add(btnCbClangTidyApp, 0, wxLEFT|wxALIGN_CENTER_VERTICAL, 5);
    flsMain->Add(bszCbClangTidyApp, 1, wxLEFT|wxEXPAND, 5);
    lblCbClangTidyArgs = new wxStaticText(this, wxID_ANY, _("CbClangTidy arguments:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
    flsMain->Add(lblCbClangTidyArgs, 0, wxTOP|wxLEFT|wxALIGN_CENTER_VERTICAL, 5);
    txtCbClangTidyArgs = new wxTextCtrl(this, ID_TXT_CPP_CHECK_ARGS, _("--verbose --enable=all --enable=style --xml"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TXT_CPP_CHECK_ARGS"));
    txtCbClangTidyArgs->SetMinSize(wxSize(240,-1));
    flsMain->Add(txtCbClangTidyArgs, 1, wxTOP|wxLEFT|wxEXPAND, 5);
    lblCbClangTidyArgsComment = new wxStaticText(this, wxID_ANY, _("(before \"--file-list\")"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
    flsMain->Add(lblCbClangTidyArgsComment, 0, wxLEFT|wxALIGN_TOP, 5);
    flsMain->Add(-1,-1,1, wxLEFT|wxEXPAND, 5);
    lblCbClangTidyWWW = new wxStaticText(this, wxID_ANY, _("CbClangTidy homepage:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
    flsMain->Add(lblCbClangTidyWWW, 0, wxTOP|wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    hycCbClangTidyWWW = new wxHyperlinkCtrl(this, ID_HYC_CPP_CHECK_WWW, _("http://cppcheck.sourceforge.net"), wxEmptyString, wxDefaultPosition, wxDefaultSize, wxHL_CONTEXTMENU|wxHL_ALIGN_CENTRE, _T("ID_HYC_CPP_CHECK_WWW"));
    flsMain->Add(hycCbClangTidyWWW, 1, wxTOP|wxLEFT|wxEXPAND, 5);
    slSeparatorLeft = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("wxID_ANY"));
    flsMain->Add(slSeparatorLeft, 0, wxTOP|wxBOTTOM|wxLEFT|wxEXPAND, 5);
    slSeparatorRight = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("wxID_ANY"));
    flsMain->Add(slSeparatorRight, 0, wxTOP|wxBOTTOM|wxEXPAND, 5);
    lblVeraApp = new wxStaticText(this, wxID_ANY, _("Vera++ application:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
    flsMain->Add(lblVeraApp, 0, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    bszVeraApp = new wxBoxSizer(wxHORIZONTAL);
    txtVeraApp = new wxTextCtrl(this, ID_TXT_VERA_APP, _("vera++"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TXT_VERA_APP"));
    bszVeraApp->Add(txtVeraApp, 1, wxEXPAND, 5);
    btnVeraApp = new wxButton(this, ID_BTN_VERA, _T("..."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BTN_VERA"));
    btnVeraApp->SetMinSize(wxSize(30,-1));
    bszVeraApp->Add(btnVeraApp, 0, wxLEFT|wxALIGN_TOP, 5);
    flsMain->Add(bszVeraApp, 1, wxLEFT|wxEXPAND, 5);
    lblVeraArgs = new wxStaticText(this, wxID_ANY, _("Vera++ arguments:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
    flsMain->Add(lblVeraArgs, 0, wxTOP|wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    txtVeraArgs = new wxTextCtrl(this, ID_TXT_VERA_ARGS, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TXT_VERA_ARGS"));
    flsMain->Add(txtVeraArgs, 1, wxTOP|wxLEFT|wxEXPAND, 5);
    lblVeraArgsComment = new wxStaticText(this, wxID_ANY, _("(before file list)"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
    flsMain->Add(lblVeraArgsComment, 0, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    flsMain->Add(-1,-1,1, wxLEFT|wxEXPAND, 5);
    lblVeraWWW = new wxStaticText(this, wxID_ANY, _("Vera++  homepage:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
    flsMain->Add(lblVeraWWW, 0, wxTOP|wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    hycVeraWWW = new wxHyperlinkCtrl(this, ID_HYC_VERA_WWW, _("https://bitbucket.org/verateam/vera"), wxEmptyString, wxDefaultPosition, wxDefaultSize, wxHL_CONTEXTMENU|wxHL_ALIGN_CENTRE, _T("ID_HYC_VERA_WWW"));
    flsMain->Add(hycVeraWWW, 1, wxTOP|wxLEFT|wxEXPAND, 5);
    StaticLine1 = new wxStaticLine(this, ID_STATICLINE1, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
    flsMain->Add(StaticLine1, 0, wxTOP|wxBOTTOM|wxLEFT|wxEXPAND, 5);
    StaticLine2 = new wxStaticLine(this, ID_STATICLINE2, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE2"));
    flsMain->Add(StaticLine2, 1, wxTOP|wxBOTTOM|wxEXPAND, 5);
    lblOperation = new wxStaticText(this, wxID_ANY, _("Select operation:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
    flsMain->Add(lblOperation, 0, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    choOperation = new wxChoice(this, ID_CHO_OPERATION, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHO_OPERATION"));
    choOperation->SetSelection( choOperation->Append(_("CbClangTidy only")) );
    choOperation->Append(_("Vera++ only"));
    choOperation->Append(_("CbClangTidy and Vera++"));
    flsMain->Add(choOperation, 1, wxLEFT|wxEXPAND, 5);
    bszMain->Add(flsMain, 1, wxEXPAND, 5);
    SetSizer(bszMain);
    bszMain->SetSizeHints(this);

    Connect(ID_BTN_CPPCHECK_APP,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(CbClangTidyConfigPanel::OnCbClangTidyApp));
    Connect(ID_BTN_VERA,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(CbClangTidyConfigPanel::OnVeraApp));
    //*)

    ConfigManager* cfg = Manager::Get()->GetConfigManager(_T("cppcheck"));
    if (cfg)
    {
        txtCbClangTidyApp->SetValue( cfg->Read(_T("cppcheck_app"),
                                  GetDefaultCbClangTidyExecutableName()) );
        txtCbClangTidyArgs->SetValue( cfg->Read(_T("cppcheck_args"),
                                   _T("--verbose --enable=all --enable=style --xml")) );

        txtVeraApp->SetValue( cfg->Read(_T("vera_app"),
                                  GetDefaultVeraExecutableName()) );
        txtVeraArgs->SetValue( cfg->Read(_T("vera_args"), wxEmptyString) );

        choOperation->SetSelection( cfg->ReadInt(_T("operation"), 0) );
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
    wxFileDialog dialog (this, _("Select CbClangTidy application"),
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


void CbClangTidyConfigPanel::OnVeraApp(cb_unused wxCommandEvent& event)
{
    wxFileName initialFile(txtVeraApp->GetValue());
    wxFileDialog dialog (this, _("Select Vera++ application"),
                         initialFile.GetPath(),
                         GetDefaultVeraExecutableName(),
#ifdef __WXMSW__
                         _("Executable files (*.exe)|*.exe"),
#else
                         _("Executable files (*)|*"),
#endif
                        wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    PlaceWindow(&dialog);
    if (dialog.ShowModal() == wxID_OK)
        txtVeraApp->SetValue(dialog.GetPath());
}

void CbClangTidyConfigPanel::OnApply()
{
    ConfigManager* cfg = Manager::Get()->GetConfigManager(_T("cppcheck"));
    if (cfg)
    {
        wxString app = txtCbClangTidyApp->GetValue();
        if (!app.IsEmpty())
            cfg->Write(_T("cppcheck_app"), app);
        if (!txtCbClangTidyArgs->GetValue().IsEmpty())
            cfg->Write(_T("cppcheck_args"), txtCbClangTidyArgs->GetValue());

        app = txtVeraApp->GetValue();
        if (!app.IsEmpty())
            cfg->Write(_T("vera_app"), app);
        if (!txtVeraArgs->GetValue().IsEmpty())
            cfg->Write(_T("vera_args"), txtVeraArgs->GetValue());

        cfg->Write(_T("operation"), choOperation->GetSelection());
    }
}

wxString CbClangTidyConfigPanel::GetDefaultCbClangTidyExecutableName()
{
#ifdef __WXMSW__
    return _T("cppcheck.exe");
#else
    return _T("cppcheck");
#endif
}

wxString CbClangTidyConfigPanel::GetDefaultVeraExecutableName()
{
#ifdef __WXMSW__
    return _T("vera++.exe");
#else
    return _T("vera++");
#endif
}

