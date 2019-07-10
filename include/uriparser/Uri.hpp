// Copyright (c) 2019 shaqsnake. All rights reserved.
/**
 * @Author: shaqsnake
 * @Email: shaqsnake@gmail.com
 * @Date: 2019-06-27 09:17:12
 * @LastEditTime: 2019-07-10 10:53:11
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

public:
    bool parseFromString(const std::string &uriString);
    std::string &getScheme() const;
    std::string &getAuthority() const;
    std::string &getUserinfo() const;
    std::string &getHost() const;
    int &getPort() const;
    std::string &getPath() const;
    std::string &getQuery() const;
    std::string &getFragment() const;

private:
    struct Impl;
    std::unique_ptr<struct Impl> impl_;
    
    void parseAuthority();
};

} // namespace uri

#endif // URIPARSER_URI_HPP
