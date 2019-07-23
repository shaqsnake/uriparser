// Copyright (c) 2019 shaqsnake. All rights reserved.
/**
 * @Author: shaqsnake
 * @Email: shaqsnake@gmail.com
 * @Date: 2019-06-27 09:17:12
 * @LastEditTime: 2019-07-23 15:45:04
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
    std::string produceToString(bool encode=true);
    std::string &getScheme() const;
    std::string &getAuthority() const;
    std::string &getUserinfo() const;
    std::string &getHost() const;
    int &getPort() const;
    std::string &getPath() const;
    std::string &getQuery() const;
    std::string &getFragment() const;
    void setScheme(const std::string &scheme);
    void setAuthority(const std::string &authority);
    void setPath(const std::string &path);
    void setQuery(const std::string &query);
    void setFragment(const std::string &fragment);
    void normalizePath();
    // TODO: Refactor to Uri resolve(const Uri& relativeRef) const;
    void resolve(const std::string &relativeRef);

private:
    struct Impl;
    std::unique_ptr<struct Impl> impl_;

    void parseAuthority();
    std::string recompose();
    std::string removeDotSegments(std::string inputBuffer);
};

} // namespace uri

#endif // URIPARSER_URI_HPP
