#include <iostream>
#include <exception>
#include <cstdint>
#include <vector>

#include "application.h"

int main() {//int argc, char* argv[]) {
    try {
        int argc = 3;
        // char* Argv[] = {"path", "-c", "check.txt", "/home/ilya/Programs/Project/Archivery/T.txt"};
        //char* argv[] = {"path", "-c", "check.txt", "/home/ilya/Programs/Archiver/T.txt"};
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