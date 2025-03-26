#include "encode.h"

Encode::Encode(std::filesystem::path archive_name, std::vector<std::filesystem::path> files)
    : out_(archive_name, 0, 0) {
    for (size_t i = 0; i < files.size(); ++i) {
        if (i != files.size() - 1) {
            EncodeFile(files[i], false);
        } else {
            EncodeFile(files[i], true);
        }
    }
}

void Encode::EncodeFile(const std::filesystem::path& file, bool flag_end) {
    std::vector<size_t> freq(utilities::ALPHABET_SIZE, 0);
    CountFreq(file, freq);
    Haffman haffman;
    haffman.BuildByFreq(freq);
    std::vector<std::pair<size_t, Token>> symbols = haffman.GetSymbols();
    std::vector<std::vector<bool>> code_tokens = haffman.GetCodeTokens();
    WriteAddInformationToArchive(symbols);
    WriteFileToArchive(file, code_tokens, flag_end);
}

void Encode::CountFreq(const std::filesystem::path& file, std::vector<size_t>& freq) {
    freq[utilities::FILENAME_END] = 1;
    freq[utilities::ONE_MORE_FILE] = 1;
    freq[utilities::ARCHIVE_END] = 1;
    ModifiedIStream in(file, 0, 0);
    for (Token symb : file.filename().string()) {
        ++freq[symb];
    }
    Token cur_symb = 0;
    while (in.GetToken(cur_symb, utilities::BYTE_SIZE)) {
        ++freq[cur_symb];
    }
}

void Encode::WriteAddInformationToArchive(const std::vector<std::pair<size_t, Token>>& symbols) {
    out_.PutToken(static_cast<Token>(symbols.size()), utilities::BIG_BYTE_SIZE);
    std::vector<Token> cnt_symbols_for_length;
    for (std::pair<size_t, Token> symbol : symbols) {
        out_.PutToken(symbol.second, utilities::BIG_BYTE_SIZE);
        while (symbol.first > cnt_symbols_for_length.size()) {
            cnt_symbols_for_length.push_back(0);
        }
        ++cnt_symbols_for_length[symbol.first - 1];
    }
    for (Token cnt : cnt_symbols_for_length) {
        out_.PutToken(cnt, utilities::BIG_BYTE_SIZE);
    }
}

void Encode::WriteFileToArchive(const std::filesystem::path& file, const std::vector<std::vector<bool>>& code_tokens,
                                bool flag_end) {
    for (Token symb : file.filename().string()) {
        for (bool bit : code_tokens[symb]) {
            out_.PutToken(bit, 1);
        }
    }
    for (bool bit : code_tokens[utilities::FILENAME_END]) {
        out_.PutToken(bit, 1);
    }
    Token symb = 0;
    ModifiedIStream in(file, 0, 0);
    while (in.GetToken(symb, utilities::BYTE_SIZE)) {
        for (bool bit : code_tokens[symb]) {
            out_.PutToken(bit, 1);
        }
    }
    if (!flag_end) {
        for (bool bit : code_tokens[utilities::ONE_MORE_FILE]) {
            out_.PutToken(bit, 1);
        }
    } else {
        for (bool bit : code_tokens[utilities::ARCHIVE_END]) {
            out_.PutToken(bit, 1);
        }
        out_.ClearBuffer();
    }
}
