// Copyright (c) 2019 shaqsnake. All rights reserved.
/**
 * @Author: shaqsnake
 * @Email: shaqsnake@gmail.com
 * @Date: 2019-06-27 09:17:12
 * @LastEditTime: 2019-07-05 11:17:24
 * @Description: An implementation of class uri::Uri.
 */
#include "UriPattern.hpp"
#include <iostream>
#include <regex>
#include <uriparser/Uri.hpp>

namespace {
    /**
     * @description:
     *     Check the format of input string is vaild or not.
     * @param[in] str
     *     A input string to be checked.
     * @param[in] pattern
     *     A valid pattern to check. 
     * @return: 
     *     An indication of whether or not the input string is valid.
     */
    bool isValid(std::string str, std::string pattern) {
        std::regex r(pattern);
        return std::regex_match(str, r);
    }
}

namespace uri {

/**
 * The concrete implemetation of Uri class.
 */
struct Uri::Impl {
    std::string scheme;
    // std::string delimiter;
    std::string authority;
    std::string userinfo;
    std::string host;
    int port = -1;
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
bool Uri::parseFromString(const std::string &uriString) {
    std::regex r(uri::UriPattern);
    std::smatch m;
    regex_match(uriString, m, r);

    // TODO: refactor the match procedure.
    if (!m.empty()) {
        impl_->scheme = m[2].str(); // schema
        if (!isValid(impl_->scheme, uri::SchemePattern))
            return false;

        impl_->authority = m[4].str();
        parseAuthority();
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
std::string &Uri::getScheme() const { return impl_->scheme; }

/**
 * @description:
 *     Get the authority of URI which is defined in RFC3986.
 * @return:
 *     A authority string.
 */
std::string &Uri::getAuthority() const { return impl_->authority; }

/**
 * @description:
 *     Get the host address of URI which is defined in RFC3986.
 * @return:
 *     A host string.
 */
std::string &Uri::getHost() const { return impl_->host; }

/**
 * @description:
 *     Get the port number of URI which is defined in RFC3986.
 * @return:
 *     A port number which should be from 1 to 65,535.
 */
int &Uri::getPort() const { return impl_->port; }

/**
 * @description:
 *     Get the path of URI which is defined in RFC3986.
 * @return:
 *     A path string.
 */
std::string &Uri::getPath() const { return impl_->path; }

/**
 * @description:
 *     Get the query of URI which is defined in RFC3986.
 * @return:
 *     A query string.
 */
std::string &Uri::getQuery() const { return impl_->query; }

/**
 * @description:
 *     Get the fragment of URI which is defined in RFC3986.
 * @return:
 *     A fragment string.
 */
std::string &Uri::getFragment() const { return impl_->fragment; }

// Private methods
/**
 * @description:
 *     Parse the authority component;
 *     Split it into userinfo, host and port;
 *     Store thems into class members accordingly.
 */
void Uri::parseAuthority() {
    if (impl_->authority.size()) {
        std::regex r(uri::AuthorityPatten);
        std::smatch m;
        regex_match(impl_->authority, m, r);

        // DEBUG code
        // std::cout << uri::AuthorityPatten << std::endl;
        // std::cout << impl_->authority << std::endl;
        // std::cout << m[1] << " " << m[2] << " " << m[3] << std::endl;
        if (m.size()) {
            impl_->userinfo = m[1].str();
            impl_->host = m[2].str();
            if (m[3].str().size())
                impl_->port = std::stoi(m[3].str());
        }
    }
}
} // namespace uri
