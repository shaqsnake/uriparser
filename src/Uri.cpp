// Copyright (c) 2019 shaqsnake. All rights reserved.
/**
 * @Author: shaqsnake
 * @Email: shaqsnake@gmail.com
 * @Date: 2019-06-27 09:17:12
 * @LastEditTime: 2019-07-03 14:02:19
 * @Description: An implementation of class uri::Uri.
 */
#include <iostream>
#include <regex>
#include <uriparser/Uri.hpp>
#include <uriparser/UriPattern.hpp>

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

bool Uri::parseFromString(const std::string &uriString) {
    std::regex r(uri::UriPattern);
    std::smatch m;
    regex_match(uriString, m, r);

    // TODO: refactor the match procedure.
    if (!m.empty()) {
        impl_->scheme = m[2].str();
        impl_->authority = m[4].str();
        parseAuthority();
        impl_->path = m[5].str();
        impl_->query = m[7].str();
        impl_->fragment = m[9].str();

        return true;
    }
    return false;
}

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
