#include "application.h"

Application::Application(int argc, char* argv[]) : parser_(argc, argv) {
}

void Application::Run() {
    try {
        if (parser_.GetActionType() == Action::ENCODE) {
            Encode(parser_.GetArchiveName(), parser_.GetFiles());
        }
        if (parser_.GetActionType() == Action::DECODE) {
            Decode(parser_.GetArchiveName());
        }
        if (parser_.GetActionType() == Action::HELP) {
        }
    } catch (Exception& e) {
        throw;
    } catch (...) {
        throw;
    }
}