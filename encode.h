#ifndef ENCODE_H_
#define ENCODE_H_

#include <filesystem>
#include <vector>

#include "modified_iostream.h"
#include "haffman.h"

class Encode {
public:
    explicit Encode(std::filesystem::path archive_name, std::vector<std::filesystem::path> files);
    void EncodeFile(const std::filesystem::path& file, bool flag_end);
    void CountFreq(const std::filesystem::path& file, std::vector<size_t>& freq);
    void WriteFileToArchive(const std::filesystem::path& file, const std::vector<std::vector<bool>>& code_tokens,
                            bool flag_end);
    void WriteAddInformationToArchive(const std::vector<std::pair<size_t, Token>>& symbols);

private:
    ModifiedOStream out_;
};

#endif