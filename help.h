#ifndef HELP_H_
#define HELP_H_

#include <iostream>

class Help {
public:
    Help() {
        std::cout << "\"archiver -c archive_name file1 [file2 ...]\" - archive files file1, file2, ... and save the "
                     "result to file archive_name."
                  << std::endl;
        std::cout << "\"archiver -d archive_name\" - unzip files from archive archive_name and put them in the current "
                     "directory."
                  << std::endl;
        std::cout << "\"archiver -h\" - display help on using the program." << std::endl;
    }
};

#endif