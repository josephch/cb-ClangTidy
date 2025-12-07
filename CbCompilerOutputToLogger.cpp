#include "CbCompilerOutputToLogger.h"
#include "compiler-output-parser/compiler_output_parser.hpp"

LoggerInfo CompilerOutputToLoggerFormat(const std::string& line)
{
    LoggerInfo loggerInfo;
    loggerInfo.level = Logger::level::info;
    CompilerOutputLineInfo compilerOutputLineInfo = ::GetCompilerOutputLineInfo(line);
    if (compilerOutputLineInfo.type != CompilerOutputLineType::normal)
    {
        switch (compilerOutputLineInfo.type)
        {
        case CompilerOutputLineType::error:
            loggerInfo.level = Logger::level::error;
            break;
        case CompilerOutputLineType::warning:
            loggerInfo.level = Logger::level::warning;
            break;
        default:
            break;
        }
        int i = 0;
        loggerInfo.colValues.Add(compilerOutputLineInfo.fileName);
        loggerInfo.colValues.Add(compilerOutputLineInfo.line);
        loggerInfo.colValues.Add(compilerOutputLineInfo.message);
    }
    else
    {
        loggerInfo.colValues.Add(wxEmptyString);
        loggerInfo.colValues.Add(wxEmptyString);
        loggerInfo.colValues.Add(line);
    }
    return loggerInfo;
}
