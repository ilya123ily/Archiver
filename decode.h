#ifndef DECODE_H_
#define DECODE_H_

#include <filesystem>
#include <vector>

#include "modified_iostream.h"
#include "haffman.h"

class Decode {
public:
    explicit Decode(std::filesystem::path archive_name);
    bool DecodeFile();
    std::filesystem::path DecodeFileName();
    bool DecodeFragment(ModifiedOStream& out);
    void GetLenSymbols();

private:
    ModifiedIStream in_;
    std::vector<size_t> len_tokens_;
    Node* root_;
};

#endif