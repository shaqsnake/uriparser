/**
 * @file Uri.hpp
 * @brief A declaration of Class uri::Uri.
 * @author shaqsnake
 * @email shaqsnake@gmail.com
 */

#ifndef URIPARSER_URI_HPP
#define URIPARSER_URI_HPP

#include <memory>

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

private:
    struct Impl;
    std::unique_ptr<struct Impl> impl_;
};

} // namespace uri

#endif
