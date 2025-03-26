#include "decode.h"

Decode::Decode(std::filesystem::path archive_name) : in_(archive_name, 0, 0) {
    while (DecodeFile()) {
        len_tokens_.clear();
    }
}

bool Decode::DecodeFile() {
    GetLenSymbols();
    Haffman haffman;
    haffman.BuildByLen(len_tokens_);
    root_ = haffman.GetRoot();
    std::filesystem::path file_name = DecodeFileName();
    ModifiedOStream out(file_name, 0, 0);
    return DecodeFragment(out);
}

std::filesystem::path Decode::DecodeFileName() {
    Node* cur_node = root_;
    Token bit = 0;
    std::string file_name;
    while (in_.GetToken(bit, 1)) {
        if (bit == 0) {
            cur_node = cur_node->GetLeft();
        } else {
            cur_node = cur_node->GetRight();
        }
        if (cur_node->GetToken() != utilities::MID_NODE) {
            if (cur_node->GetToken() == utilities::FILENAME_END) {
                return file_name;
            }
            file_name.push_back(static_cast<char>(cur_node->GetToken()));
            cur_node = root_;
        }
    }
    return file_name;
}

bool Decode::DecodeFragment(ModifiedOStream& out) {
    Node* cur_node = root_;
    Token bit = 0;
    while (in_.GetToken(bit, 1)) {
        if (bit == 0) {
            cur_node = cur_node->GetLeft();
        } else {
            cur_node = cur_node->GetRight();
        }
        if (cur_node->GetToken() != utilities::MID_NODE) {
            if (cur_node->GetToken() == utilities::ARCHIVE_END) {
                return false;
            }
            if (cur_node->GetToken() == utilities::ONE_MORE_FILE) {
                return true;
            }
            out.PutToken(cur_node->GetToken(), utilities::BYTE_SIZE);
            cur_node = root_;
        }
    }
    return false;
}

void Decode::GetLenSymbols() {
    Token symbols_count = 0;
    in_.GetToken(symbols_count, utilities::BIG_BYTE_SIZE);
    std::vector<Token> symbols(symbols_count);
    len_tokens_.resize(utilities::ALPHABET_SIZE, 0);
    for (size_t i = 0; i < symbols_count; ++i) {
        Token symbol = 0;
        in_.GetToken(symbol, utilities::BIG_BYTE_SIZE);
        symbols[i] = symbol;
    }
    int cur_pos = 0;
    int cur_length = 1;
    while (cur_pos < symbols.size()) {
        Token cnt_symbols = 0;
        in_.GetToken(cnt_symbols, utilities::BIG_BYTE_SIZE);
        for (size_t i = 0; i < cnt_symbols; ++i) {
            len_tokens_[symbols[cur_pos]] = cur_length;
            ++cur_pos;
        }
        ++cur_length;
    }
}
