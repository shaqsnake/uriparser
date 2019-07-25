// Copyright (c) 2019 shaqsnake. All rights reserved.
/**
 * @Author: shaqsnake
 * @Email: shaqsnake@gmail.com
 * @Date: 2019-07-10 10:47:27
 * @LastEditTime: 2019-07-25 14:31:08
 * @Description:
 */

#ifndef URIPARSER_URIPCTCODER_HPP
#define URIPARSER_URIPCTCODER_HPP

#include <memory>
#include <string>

namespace uri {

/**
 * @class UriPctCoder
 * 
 * A Percent-Coder to encode/decode 
 * URI string to/from "% HEXDIG HEXDIG" format.
 *
 */
class UriPctCoder {
public:
    UriPctCoder();
    ~UriPctCoder();
    UriPctCoder(const UriPctCoder &) = delete;
    UriPctCoder(UriPctCoder &&) = delete;
    UriPctCoder &operator=(const UriPctCoder &) = delete;
    UriPctCoder &operator=(UriPctCoder &&) = delete;

public:
    std::string decode(const std::string &inputUriString) const;
    std::string encode(const std::string &inputUriString) const;

private:
    struct Impl;
    std::unique_ptr<struct Impl> impl_;
};

} // namespace uri

#endif // URIPARSER_URIPCTCODER_HPP
