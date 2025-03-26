#include <iostream>
#include <exception>
#include <cstdint>
#include <vector>

#include "application.h"

int main(int argc, char* argv[]) {
    try {
        char* argv[] = {"path", "-d", "check.txt"};
        Application app(argc, argv);
        app.Run();
        return 0;
    } catch (Exception& e) {
        std::cerr << "An exception handled: " << e.what();
        return ERROR;
    } catch (std::exception& e) {
        std::cerr << "An exception handled: " << e.what();
        return ERROR;
    } catch (...) {
        std::cerr << "Unknown exception raised. Nothing more to say..";
        return ERROR;
    }
    return ERROR;
}