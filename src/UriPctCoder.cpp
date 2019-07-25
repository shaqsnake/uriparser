// Copyright (c) 2019 shaqsnake. All rights reserved.
/**
 * @Author: shaqsnake
 * @Email: shaqsnake@gmail.com
 * @Date: 2019-07-10 10:47:34
 * @LastEditTime: 2019-07-25 15:14:12
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
    // std::set<u_char> hexdig{'0', '1', '2', '3', '4', '5', '6', '7',
    //                         '8', '9', 'A', 'B', 'C', 'D', 'E', 'F',
    //                         'a', 'b', 'c', 'd', 'e', 'f'};
    std::string hex = "0123456789ABCDEF";

    unsigned char hexval(unsigned char c);
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
 * @param[in] inputUriString
 *      An URI string contains percent hexdig format("% HEXDIG HEXDIG") terms.
 * @return:
 *      A decoded URI string.
 */
std::string UriPctCoder::decode(const std::string &inputUriString) const {
    std::string decodedUriString = "";
    std::string hexdigString = "";
    bool decodeMode = false;
    for (const auto &c : inputUriString) {
        if (decodeMode) {
            hexdigString += toupper(c);
            // The hexdig is not valid.
            if (impl_->hex.find(toupper(c)) == std::string::npos) {
                decodedUriString += hexdigString;
                decodeMode = false;
                hexdigString.clear();
            }
            // Ready to decode.
            if (hexdigString.size() == 3) {
                decodedUriString += (impl_->hexval(hexdigString[1]) << 4) +
                                    impl_->hexval(hexdigString[2]);
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
 *     Encode input string,
 *     if a charater is not unreserved, change it to hexdig format.
 * @param[in] inputUriString
 *     An raw URI string.
 * @return:
 *    An encoded URI string.
 */
std::string UriPctCoder::encode(const std::string &inputUriString) const {
    std::string targetUriString = "";

    for (const auto &c : inputUriString) {
        // Unreserved character.
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
            (c >= '0' && c <= '9') || c == '-' || c == '_' || c == '.' ||
            c == '~') {
            targetUriString += c;
        } else {
            targetUriString += "%";
            targetUriString += impl_->hex[(c & 0xF0) >> 4];
            targetUriString += impl_->hex[c & 0x0F];
        }
    }

    return targetUriString;
}

/**
 * @description:
 *     Parse hex digit to ascii character.
 * @param[in] c
 *     A hex digit.
 * @return:
 *     An ascii character.
 */
u_char UriPctCoder::Impl::hexval(u_char c) {
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
