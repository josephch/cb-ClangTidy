#ifndef CBCOMPILEROUTPUTTOLOGGER_H_INCLUDED
#define CBCOMPILEROUTPUTTOLOGGER_H_INCLUDED

#include "logger.h"
#include "wx/arrstr.h"

struct LoggerInfo
{
    wxArrayString colValues;
    Logger::level level;
};

LoggerInfo CompilerOutputToLoggerFormat(const std::string& line);

#endif // CBCOMPILEROUTPUTTOLOGGER_H_INCLUDED
