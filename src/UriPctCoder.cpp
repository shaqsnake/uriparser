// Copyright (c) 2019 shaqsnake. All rights decodedUriStringerved.
/**
 * @Author: shaqsnake
 * @Email: shaqsnake@gmail.com
 * @Date: 2019-07-10 10:47:34
 * @LastEditTime: 2019-07-10 14:05:50
 * @Description:
 */
#include "UriPctCoder.hpp"
#include <iostream>
#include <set>

namespace uri {

/**
 * The concrete implemetation of Uri class.
 */
struct UriPctCoder::Impl {
    std::set<u_char> hexdig{'0', '1', '2', '3', '4', '5', '6', '7',
                            '8', '9', 'A', 'B', 'C', 'D', 'E', 'F',
                            'a', 'b', 'c', 'd', 'e', 'f'};
};

/**
 * Constructor by default.
 */
UriPctCoder::UriPctCoder() : impl_(new Impl) {}

/**
 * Destructor.
 */
UriPctCoder::~UriPctCoder() = default;

/**
 * @description:
 *     Decode pecent hexdig format("% HEXDIG HEXDIG") terms of URI string into
 *     ascii character.
 * @param[in] rawUriString
 *      An URI string contains percent hexdig format("% HEXDIG HEXDIG") terms.
 * @return:
 *      A decoded URI string.
 */
std::string UriPctCoder::decode(const std::string &rawUriString) {
    std::string decodedUriString = "";
    std::string hexdigString = "";
    bool decodeMode = false;
    for (const auto &c : rawUriString) {
        if (decodeMode) {
            hexdigString += c;
            // The hexdig is not valid.
            if (!impl_->hexdig.count(c)) {
                decodedUriString += hexdigString;
                decodeMode = false;
                hexdigString.clear();
            }
            // Ready to decode.
            if (hexdigString.size() == 3) {
                decodedUriString +=
                    (hexval(hexdigString[1]) << 4) + hexval(hexdigString[2]);
                decodeMode = false;
                hexdigString.clear();
            }
        } else {
            if (c == '%') {
                decodeMode = true;
                hexdigString += c;
            } else {
                decodedUriString += c;
            }
        }
    }

    return decodedUriString;
}

/**
 * @description:
 *     Parse hex digit to ascii character.
 * @param[in] c
 *     A hex digit.
 * @return:
 *     An ascii character.
 */
u_char UriPctCoder::hexval(u_char c) {
    if ('0' <= c && c <= '9')
        return c - '0';
    else if ('a' <= c && c <= 'f')
        return c - 'a' + 10;
    else if ('A' <= c && c <= 'F')
        return c - 'A' + 10;
    else
        return c;
}

} // namespace uri