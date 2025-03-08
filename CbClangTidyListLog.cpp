#include "sdk.h"

#ifndef CB_PRECOMP
    #include "cbeditor.h"
    #include "editormanager.h"
    #include "manager.h"
    #include <wx/arrstr.h>
    #include <wx/filename.h>
    #include <wx/listctrl.h>
#endif
#include "cbstyledtextctrl.h"

#include "CbClangTidyListLog.h"

namespace
{
    const int ID_List = wxNewId();
};

BEGIN_EVENT_TABLE(CbClangTidyListLog, wxEvtHandler)
//
END_EVENT_TABLE()

CbClangTidyListLog::CbClangTidyListLog(const wxArrayString& Titles, wxArrayInt& Widths)
    : ListCtrlLogger(Titles, Widths)
{
    // ctor
}

CbClangTidyListLog::~CbClangTidyListLog()
{
    // dtor
    Disconnect(ID_List, -1, wxEVT_COMMAND_LIST_ITEM_ACTIVATED,
               (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&CbClangTidyListLog::OnDoubleClick);
}

// TODO : use Getter instead of protected 'control'

wxWindow* CbClangTidyListLog::CreateControl(wxWindow* parent)
{
    ListCtrlLogger::CreateControl(parent);
    control->SetId(ID_List);
    Connect(ID_List, -1, wxEVT_COMMAND_LIST_ITEM_ACTIVATED,
            (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&CbClangTidyListLog::OnDoubleClick);
    Manager::Get()->GetAppWindow()->PushEventHandler(this);
    return control;
}

void CbClangTidyListLog::DestroyControls()
{
    if (!Manager::Get()->IsAppShuttingDown())
    {
        Manager::Get()->GetAppWindow()->RemoveEventHandler(this);
    }
}

void CbClangTidyListLog::OnDoubleClick(wxCommandEvent& /*event*/)
{
    // go to the relevant file/line
    if (control->GetSelectedItemCount() == 0)
        return;

    // find selected item index
    const int Index = control->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    SyncEditor(Index);
} // end of OnDoubleClick

void CbClangTidyListLog::SyncEditor(int SelIndex)
{
    wxFileName Filename(control->GetItemText(SelIndex));
    wxString File;
    File = Filename.GetFullPath();

    wxListItem li;
    li.SetId(SelIndex);
    li.SetColumn(1);
    li.SetMask(wxLIST_MASK_TEXT);
    control->GetItem(li);

    long Line = 0;
    li.GetText().ToLong(&Line);
    cbEditor* Editor = Manager::Get()->GetEditorManager()->Open(File);
    if (!Line || !Editor)
        return;

    Line -= 1;
    Editor->Activate();
    Editor->GotoLine(Line);

    if (cbStyledTextCtrl* Control = Editor->GetControl())
        Control->EnsureVisible(Line);
}
