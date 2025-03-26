#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <exception>

#include "cmd_line_args_parser.h"
#include "encode.h"
#include "decode.h"
#include "help.h"
#include "exceptions.h"

class Application {
public:
    Application(int argc, char* argv[]);
    void Run();

private:
    CmdLineArgsParser parser_;
};

#endif