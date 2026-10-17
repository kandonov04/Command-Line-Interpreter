#include "../h/CommandTime.h"
#include "../h/ErrorHandler.h"

CommandTime::CommandTime(Types::Data* myData) : Command(myData)
{
    executor = new Executor();
}

CommandTime::~CommandTime()
{
    delete executor;
}

void CommandTime::checkError()
{
    if (myData->arg.size() > 0) {
        throw ErrorHandler("tooManyArg");
    }

    if (!myData->inputRedir.empty()) {
        throw ErrorHandler("inRdrNotSupported");
    }

    if (!myData->opt.empty()) {
        throw ErrorHandler("optNotSupported");
    }
}

std::string CommandTime::inputCommand()
{
    return std::string();
}

std::string CommandTime::processCommand(std::string line)
{
    auto now = std::chrono::system_clock::now();
    std::time_t nowTime = std::chrono::system_clock::to_time_t(now);
    std::tm localTime;
#ifdef _WIN32
    localtime_s(&localTime, &nowTime);
#else
    localtime_r(&nowTime, &localTime);
#endif
    std::ostringstream ss;
    ss << std::put_time(&localTime, "%H:%M:%S");
    std::string time = ss.str();
    return time;
}

void CommandTime::doCommand()
{
    checkError();
    std::string in = inputCommand();
    std::string out = processCommand(in);
    executor->print(out, myData -> outputRedir);
}
