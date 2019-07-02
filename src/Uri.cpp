// Copyright (c) 2019 shaqsnake. All rights reserved.
/**
 * @Author: shaqsnake
 * @Email: shaqsnake@gmail.com
 * @Date: 2019-06-27 09:17:12
 * @LastEditTime: 2019-07-02 17:05:52
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
    std::string host;
    int port;
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

bool Uri::parseFromString(const std::string &uriString) {
    std::regex r(URI_PATTERN);
    std::smatch m;
    regex_match(uriString, m, r);

    // TODO: refactor the match procedure.
    if (!m.empty()) {
        impl_->scheme = m[2].str();
        impl_->authority = m[4].str();
        impl_->host = "";
        impl_->port = -1;
        if (impl_->authority.size()) {
            impl_->host = parseHostFromAuth(impl_->authority);
            impl_->port = parsePortFromAuth(impl_->authority);
        }
        impl_->path = m[5].str();
        impl_->query = m[7].str();
        impl_->fragment = m[9].str();

        return true;
    }
    return false;
}

std::string Uri::parseHostFromAuth(std::string authorityString) {
    auto hostEnd = authorityString.rfind(':');
    if (hostEnd != std::string::npos)
        authorityString = authorityString.substr(0, hostEnd);
    auto hostStart = authorityString.find('@');
    if (hostStart != std::string::npos)
        authorityString = authorityString.substr(hostStart+1);
    return authorityString;
}

int Uri::parsePortFromAuth(std::string authorityString) {
    int port = -1;
    auto portStart = authorityString.rfind(':');
    if (portStart != std::string::npos)
        port = std::stoi(authorityString.substr(portStart+1));
    return port;
}

std::string &Uri::getScheme() const { return impl_->scheme; }

std::string &Uri::getAuthority() const { return impl_->authority; }

std::string Uri::getHost() const {
    return impl_->host;
}

int Uri::getPort() const {
    return impl_->port;
}

std::string &Uri::getPath() const { return impl_->path; }

std::string &Uri::getQuery() const { return impl_->query; }

std::string &Uri::getFragment() const { return impl_->fragment; }

} // namespace uri
