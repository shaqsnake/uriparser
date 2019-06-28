// Copyright (c) 2019 shaqsnake. All rights reserved.
/**
 * @Author: shaqsnake
 * @Email: shaqsnake@gmail.com
 * @Date: 2019-06-27 09:17:12
 * @LastEditTime: 2019-06-28 16:55:45
 * @Description: An implementation of class uri::Uri.
 */
#include <iostream>
#include <regex>
#include <uriparser/Uri.hpp>

namespace uri {

// TODO: extract this const variable to a class?
const std::string URI_PATTERN =
    "^(([^:/?#]+):)?(//([^/?#]*))?([^?#]*)(\\?([^#]*))?(#(.*))?";

/**
 * The concrete implemetation of Uri class.
 */
struct Uri::Impl {
    std::string scheme;
    // std::string delimiter;
    std::string authority;
    std::string path;
    std::string query;
    std::string fragment;
};

/**
 * Constructor by default.
 */
Uri::Uri() : impl_(new Impl) {}

/**
 * Destructor.
 */
Uri::~Uri() = default;

/**
 * @description:
 *     Parse URI formatted string, extract the elements and store them into uri
 *     object.
 * @param[in] uriString:
 *     An URI string should be parsed by RFC3986 defination.
 * @return:
 *     An indication of whether or not the uriString was parsed successfully.
 */
bool Uri::parseFromString(const std::string &uriString) {
    std::regex r(URI_PATTERN);
    std::smatch m;
    regex_match(uriString, m, r);

    // TODO: refactor the match procedure.
    if (!m.empty()) {
        impl_->scheme = m[2].str();
        impl_->authority = m[4].str();
        impl_->path = m[5].str();
        impl_->query = m[7].str();
        impl_->fragment = m[9].str();

        return true;
    }
    return false;
}

/**
 * @description:
 *     Get the scheme of URI which is defined in RFC3986.
 * @return: 
 *     A scheme string.
 */
std::string Uri::getScheme() { return impl_->scheme; }

/**
 * @description:
 *     Get the authority of URI which is defined in RFC3986.
 * @return: 
 *     A authority string.
 */
std::string Uri::getAuthority() { return impl_->authority; }

/**
 * @description:
 *     Get the path of URI which is defined in RFC3986.
 * @return: 
 *     A path string.
 */
std::string Uri::getPath() { return impl_->path; }

/**
 * @description:
 *     Get the query of URI which is defined in RFC3986.
 * @return: 
 *     A query string.
 */
std::string Uri::getQuery() { return impl_->query; }

/**
 * @description:
 *     Get the fragment of URI which is defined in RFC3986.
 * @return: 
 *     A fragment string.
 */
std::string Uri::getFragment() { return impl_->fragment; }

} // namespace uri
