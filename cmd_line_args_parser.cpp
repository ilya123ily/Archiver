#include <cstring>

#include "cmd_line_args_parser.h"

CmdLineArgsParser::CmdLineArgsParser(int argc, char* argv[]) {
    if (std::strcmp(argv[1], "-h") == 0) {
        action_ = Action::HELP;
        return;
    }
    archive_name_ = argv[2];
    if (strcmp(argv[1], "-d") == 0) {
        action_ = Action::DECODE;
        return;
    }
    action_ = Action::ENCODE;
    files_.resize(argc - 3);
    for (size_t i = 3; i < argc; ++i) {
        files_[i - 3] = argv[i];
    }
}

Action CmdLineArgsParser::GetActionType() {
    return action_;
}

std::filesystem::path CmdLineArgsParser::GetArchiveName() {
    return archive_name_;
}

std::vector<std::filesystem::path> CmdLineArgsParser::GetFiles() {
    return files_;
}
