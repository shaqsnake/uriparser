// Copyright (c) 2019 shaqsnake. All rights reserved.
/**
 * @Author: shaqsnake
 * @Email: shaqsnake@gmail.com
 * @Date: 2019-06-27 09:17:12
 * @LastEditTime: 2019-07-03 14:11:30
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
    /**
     * @description:
     *     Parse URI formatted string, extract the elements and store them into
     *     uri object.
     * @param[in] uriString:
     *     An URI string should be parsed by RFC3986 defination.
     * @return:
     *     An indication of whether or not the uriString was parsed
     *     successfully.
     */
    bool parseFromString(const std::string &uriString);

    /**
     * @description:
     *     Get the scheme of URI which is defined in RFC3986.
     * @return:
     *     A scheme string.
     */
    std::string &getScheme() const;

    /**
     * @description:
     *     Get the authority of URI which is defined in RFC3986.
     * @return:
     *     A authority string.
     */
    std::string &getAuthority() const;

    /**
     * @description:
     *     Get the host address of URI which is defined in RFC3986.
     * @return: 
     *     A host string.
     */
    std::string getHost() const;
    
    /**
     * @description:
     *     Get the port number of URI which is defined in RFC3986.
     * @return: 
     *     A port number which should be from 1 to 65,535.
     */
    int getPort() const;

    /**
     * @description:
     *     Get the path of URI which is defined in RFC3986.
     * @return:
     *     A path string.
     */
    std::string &getPath() const;

    /**
     * @description:
     *     Get the query of URI which is defined in RFC3986.
     * @return:
     *     A query string.
     */
    std::string &getQuery() const;

    /**
     * @description:
     *     Get the fragment of URI which is defined in RFC3986.
     * @return:
     *     A fragment string.
     */
    std::string &getFragment() const;

private:
    struct Impl;
    std::unique_ptr<struct Impl> impl_;

    // Private methods
    /**
     * @description:
     *     Parse the authority component;
     *     Split it into userinfo, host and port;
     *     Store thems into class members accordingly.
     */
    void parseAuthority();
};

} // namespace uri

#endif
