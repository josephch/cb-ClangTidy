/*
 * This file is part of the Code::Blocks IDE and licensed under the GNU Lesser General Public License, version 3
 * http://www.gnu.org/licenses/lgpl-3.0.html
 */

#ifndef CPPCHECKLISTLOG_H
#define CPPCHECKLISTLOG_H

#include "loggers.h"
#include <wx/event.h>

class wxArrayString;
class wxArrayInt;
class wxCommandEvent;
class wxWindow;

class CbClangTidyListLog : public ListCtrlLogger, public wxEvtHandler
{
  public:
    CbClangTidyListLog(const wxArrayString& Titles, wxArrayInt& Widths);
    ~CbClangTidyListLog();
    wxWindow* CreateControl(wxWindow* Parent);
    void DestroyControls();

  private:
    void OnDoubleClick(wxCommandEvent& Event);
    void SyncEditor(int selIndex);

    DECLARE_EVENT_TABLE()
};

#endif // CPPCHECKLISTLOG_H
