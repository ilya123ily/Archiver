#include "modified_iostream.h"

ModifiedIStream::ModifiedIStream(std::filesystem::path file, Token buffer, uint8_t cnt_used_bit)
    : buffer_{buffer}, cnt_used_bit_{cnt_used_bit} {
    in_.open(file);
    if (!in_.good()) {
        throw Exception("Failed to read data from file");
    }
}

bool ModifiedIStream::GetToken(Token& t, uint8_t cnt_bit) {
    Byte c = 0;
    while (cnt_bit > cnt_used_bit_) {
        if (in_.peek() == EOF) {
            return false;
        }
        c = in_.get();
        buffer_ = (buffer_ << utilities::BYTE_SIZE) | c;
        cnt_used_bit_ += utilities::BYTE_SIZE;
    }
    t = (buffer_ >> (cnt_used_bit_ - cnt_bit));
    cnt_used_bit_ -= cnt_bit;
    buffer_ = (buffer_ & ((1 << cnt_used_bit_) - 1));
    return true;
}

ModifiedOStream::ModifiedOStream(std::filesystem::path file, Token buffer, uint8_t cnt_used_bit)
    : buffer_{buffer}, cnt_used_bit_{cnt_used_bit} {
    out_.open(file);
    if (!out_.good()) {
        throw Exception("failed to write data to file");
    }
}

void ModifiedOStream::PutToken(Token t, uint8_t cnt_bit) {
    buffer_ = (buffer_ << cnt_bit) | t;
    cnt_used_bit_ += cnt_bit;
    while (cnt_used_bit_ >= utilities::BYTE_SIZE) {
        Byte c = (buffer_ >> (cnt_used_bit_ - utilities::BYTE_SIZE));
        out_ << c;
        cnt_used_bit_ -= utilities::BYTE_SIZE;
        buffer_ = (buffer_ & ((1 << cnt_used_bit_) - 1));
    }
}

void ModifiedOStream::ClearBuffer() {
    if (cnt_used_bit_ != 0) {
        //  out_ << buffer_;
        cnt_used_bit_ = 0;
        buffer_ = 0;
    }
}
