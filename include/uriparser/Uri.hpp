// Copyright (c) 2019 shaqsnake. All rights reserved.
/**
 * @Author: shaqsnake
 * @Email: shaqsnake@gmail.com
 * @Date: 2019-06-27 09:17:12
 * @LastEditTime: 2019-06-28 16:52:40
 * @Description: A declaration of class uri::Uri.
 */
#ifndef URIPARSER_URI_HPP
#define URIPARSER_URI_HPP

#include <memory>
#include <string>

namespace uri {

/**
 * @class Uri
 *
 * Represents URI(Uniform Resource Identifier)
 * which is defined in [RFC3986](https://tools.ietf.org/html/rfc3986).
 *
 * Example:
 *     blahblahblah...
 */
class Uri {
public:
    Uri();
    ~Uri();
    Uri(const Uri &) = delete;
    Uri(Uri &&) = delete;
    Uri &operator=(const Uri &) = delete;
    Uri &operator=(Uri &&) = delete;

    // Public methods
    bool parseFromString(const std::string &uriString); 
    std::string getScheme();
    std::string getAuthority();
    // TODO: implement getHost method.
    std::string getHost();
    // TODO: implement getPort method.
    std::string getPort();
    std::string getPath();
    std::string getQuery();
    std::string getFragment();

private:
    struct Impl;
    std::unique_ptr<struct Impl> impl_;
};

} // namespace uri

#endif
