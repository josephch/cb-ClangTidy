#include "sdk.h"
#include "wx/menu.h"
#include "wx/xrc/xmlres.h"

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
    const int idMenuViewFilter = wxNewId();
};

BEGIN_EVENT_TABLE(CbClangTidyListLog, wxEvtHandler)
//
END_EVENT_TABLE()

CbClangTidyListLog::CbClangTidyListLog(const wxArrayString& Titles, wxArrayInt& Widths)
    : ListCtrlLogger(Titles, Widths)
{
    Bind(wxEVT_COMMAND_MENU_SELECTED, &CbClangTidyListLog::OnFilterView, this, idMenuViewFilter);
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

bool CbClangTidyListLog::HasFeature(Feature::Enum feature) const
{
    if (feature == Feature::Additional)
        return true;
    return ListCtrlLogger::HasFeature(feature);
}

void CbClangTidyListLog::AppendAdditionalMenuItems(wxMenu& menu)
{
    menu.Append(idMenuViewFilter, _("Expand/Contract list"), _("Expand/Contract list"));
}

void CbClangTidyListLog::OnFilterView(wxCommandEvent& event)
{
    m_expanded = !m_expanded;
    ListCtrlLogger::Clear();
    if (m_expanded)
    {
        for (const CbClangTidyLogItem& logItem : m_Items)
        {
            ListCtrlLogger::Append(logItem.colValues, logItem.lv, logItem.autoSize);
        }
    }
    else
    {
        for (const CbClangTidyLogItem& logItem : m_Items)
        {
            if ((logItem.lv == warning) || (logItem.lv == error) || (logItem.lv == critical))
            {
                ListCtrlLogger::Append(logItem.colValues, logItem.lv, logItem.autoSize);
            }
        }
    }
}

void CbClangTidyListLog::Append(const wxArrayString& colValues, Logger::level lv, int autoSize)
{
    m_Items.emplace_back(colValues, lv, autoSize);
    ListCtrlLogger::Append(colValues, lv, autoSize);
}

void CbClangTidyListLog::Clear()
{
    m_Items.clear();
    m_expanded = true;
    ListCtrlLogger::Clear();
};
