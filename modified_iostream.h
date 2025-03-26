#ifndef MOFIDIED_IOSTREAM_H_
#define MOFIDIED_IOSTREAM_H_

#include <fstream>
#include <filesystem>

#include "exceptions.h"
#include "utilities.h"

class ModifiedIStream {
public:
    explicit ModifiedIStream(std::filesystem::path file, Token buffer, uint8_t cnt_used_bit);
    bool GetToken(Token& t, uint8_t cnt_bit);

private:
    std::ifstream in_;
    Token buffer_;
    uint8_t cnt_used_bit_;
};

class ModifiedOStream {
public:
    explicit ModifiedOStream(std::filesystem::path file, Token buffer, uint8_t cnt_used_bit);
    void PutToken(Token t, uint8_t cnt_bit);
    void ClearBuffer();

private:
    std::ofstream out_;
    Token buffer_;
    uint8_t cnt_used_bit_;
};

#endif
