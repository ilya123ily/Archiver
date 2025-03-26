#ifndef CMD_LINE_ARGS_PARSER_H_
#define CMD_LINE_ARGS_PARSER_H_

#include <vector>
#include <filesystem>

#include "utilities.h"

enum class Action { ENCODE, DECODE, HELP };

class CmdLineArgsParser {
public:
    CmdLineArgsParser(int argc, char* argv[]);
    Action GetActionType();
    std::filesystem::path GetArchiveName();
    std::vector<std::filesystem::path> GetFiles();

private:
    Action action_;
    std::filesystem::path archive_name_;
    std::vector<std::filesystem::path> files_;
};

#endif