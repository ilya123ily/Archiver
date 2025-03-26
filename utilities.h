#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <cstdint>

using Token = uint16_t;
using Byte = uint8_t;

namespace utilities {
const Token FILENAME_END = 256;
const Token ONE_MORE_FILE = 257;
const Token ARCHIVE_END = 258;
const Token MID_NODE = ARCHIVE_END + 1;
const uint8_t BYTE_SIZE = 8;
const uint8_t BIG_BYTE_SIZE = 9;
const std::size_t ALPHABET_SIZE = 259;
}  // namespace utilities

#endif