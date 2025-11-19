/*
 * This file is part of the Code::Blocks IDE and licensed under the GNU Lesser General Public License, version 3
 * http://www.gnu.org/licenses/lgpl-3.0.html
 */

#ifndef CBCLANGTIDYLISTLOG_H
#define CBCLANGTIDYLISTLOG_H

#include "loggers.h"
#include <vector>
#include <wx/event.h>

class wxArrayString;
class wxArrayInt;
class wxCommandEvent;
class wxWindow;

struct CbClangTidyLogItem
{
    wxArrayString colValues;
    Logger::level lv;
    int autoSize;
};

class CbClangTidyListLog : public ListCtrlLogger, public wxEvtHandler
{
  public:
    CbClangTidyListLog(const wxArrayString& Titles, wxArrayInt& Widths);
    ~CbClangTidyListLog();
    wxWindow* CreateControl(wxWindow* Parent) override;
    void DestroyControls();
    bool HasFeature(Feature::Enum feature) const override;
    void AppendAdditionalMenuItems(wxMenu& menu) override;
    void Append(const wxArrayString& colValues, Logger::level lv = info, int autoSize = -1) override;
    void Clear() override;

  private:
    void OnDoubleClick(wxCommandEvent& Event);
    void SyncEditor(int selIndex);
    void OnFilterView(wxCommandEvent& event);
    bool m_expanded{true};
    std::vector<CbClangTidyLogItem> m_Items;

    DECLARE_EVENT_TABLE()
};

#endif // CBCLANGTIDYLISTLOG_H
