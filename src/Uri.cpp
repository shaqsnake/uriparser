// Copyright (c) 2019 shaqsnake. All rights reserved.
/**
 * @Author: shaqsnake
 * @Email: shaqsnake@gmail.com
 * @Date: 2019-06-27 09:17:12
 * @LastEditTime: 2019-07-16 10:02:46
 * @Description: An implementation of class uri::Uri.
 */
#include "UriPattern.hpp"
#include "UriPctCoder.hpp"
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
 *     An indication of whether or not the given string
 *     was valid is returned.
 */
bool isValid(std::string str, std::string pattern) {
    std::regex r(pattern);
    return std::regex_match(str, r);
}

} // namespace

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
        UriPctCoder uriPctCoder;

        impl_->scheme = m[2].str(); // schema
        transform(impl_->scheme.begin(), impl_->scheme.end(),
                  impl_->scheme.begin(), ::tolower);
        if (!impl_->scheme.empty() && !isValid(impl_->scheme, SchemePattern))
            return false;

        impl_->authority = uriPctCoder.decode(m[4].str()); // authority
        if (!impl_->authority.empty() &&
            !isValid(impl_->authority, AuthorityPatten))
            return false;
        parseAuthority();
        // The tcp port are 16bit digits.
        if (impl_->port >= (1 << 16))
            return false;
        impl_->path = uriPctCoder.decode(m[5].str()); // path
        if (!impl_->path.empty() && !isValid(impl_->path, PathPattern))
            return false;
        normalizePath(impl_->path);
        impl_->query = uriPctCoder.decode(m[7].str()); // query
        if (!impl_->query.empty() && !isValid(impl_->query, QueryPattern))
            return false;
        impl_->fragment = uriPctCoder.decode(m[9].str()); // fragment
        if (!impl_->fragment.empty() &&
            !isValid(impl_->fragment, FragmentPattern))
            return false;

        return true;
    }
    return false;
}

/**
 * @description:
 *     Produce URI string by its components, and encode charaters
 *     which are not unreserved.
 * @return:
 *     Encoded URI string.
 */
std::string Uri::produceToString() {
    UriPctCoder uriPctCoder;
    return uriPctCoder.encode(recompose());
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
 *     Get the userinfo of URI which is defined in RFC3986.
 * @return:
 *      A userinfo string.
 */
std::string &Uri::getUserinfo() const { return impl_->userinfo; }

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
        std::regex r(AuthorityPatten);
        std::smatch m;
        regex_match(impl_->authority, m, r);

        /* DEBUG code */
        // std::cout << uri::AuthorityPatten << std::endl;
        // std::cout << impl_->authority << std::endl;
        // std::cout << m[1] << " " << m[2] << " " << m[3] << std::endl;
        if (m.size()) {
            impl_->userinfo = m[1].str();
            impl_->host = m[2].str();
            transform(impl_->host.begin(), impl_->host.end(),
                      impl_->host.begin(), ::tolower);
            if (m[3].str().size())
                impl_->port = std::stoi(m[3].str());
        }
    }
}

/**
 * @description:
 *     Recompose URI components to obtain the corresponding URI
 *     string.
 * @return:
 *     A completed URI string.
 */
std::string Uri::recompose() {
    std::string target = "";
    if (!impl_->scheme.empty())
        target += impl_->scheme + ":";

    if (!impl_->authority.empty())
        target += "//" + impl_->authority;

    target += impl_->path;

    if (!impl_->query.empty())
        target += "?" + impl_->query;

    if (!impl_->fragment.empty())
        target += "#" + impl_->fragment;

    return target;
}

/**
 * @description:
 *     Normalize path component by "remove_dot_segments" routine
 *     which is interpreting and removing the special "." and ".."
 *     complete path segments from a referenced path.
 * @param[in|out] outputBuffer
 *     A string buffer should be normalized in-place.
 */
void Uri::normalizePath(std::string &outputBuffer) {
    // Initialize input and output buffer.
    std::string inputBuffer = std::move(outputBuffer);
    outputBuffer.clear();

    while (!inputBuffer.empty()) {
        // Extract path segment from input buffer.
        auto segPos = inputBuffer.find("/", 1);
        auto seg = inputBuffer.substr(0, segPos + 1);
        if (seg.empty())
            seg = inputBuffer;
        // std::cout << seg << std::endl;

        if (seg == "../" || seg == "./") { // "Remove_dot_segments" routine 2A
            // std::cout << "STEP 2A:" << " ";
            size_t pos = inputBuffer.find("/");
            inputBuffer.erase(0, pos + 1);
        } else if (seg == "/./" ||
                   seg == "/.") { // "Remove_dot_segments" routine 2B
            // std::cout << "STEP 2B:" << " ";
            inputBuffer.erase(0, 2);
            if (inputBuffer.find("/") != 0) {
                inputBuffer.insert(0, "/");
            }
        } else if (seg == "/../" ||
                   seg == "/..") { // "Remove_dot_segments" routine 2C
            // std::cout << "STEP 2C:" << " ";
            inputBuffer.erase(0, 3);
            if (!outputBuffer.empty()) {
                auto pos = outputBuffer.rfind("/");
                outputBuffer.erase(pos);
            }
            if (inputBuffer.find("/") != 0) {
                inputBuffer.insert(0, "/");
            }
        } else if (seg == "." ||
                   seg == "..") { // "Remove_dot_segments" routine 2D
            // std::cout << "STEP 2D:" << " ";
            inputBuffer.erase(0, seg.size());
        } else { // "Remove_dot_segments" routine 2E
            // std::cout << "STEP 2E:" << " ";
            // Output buffer should start with '/' if path is absolutely.
            if (inputBuffer.find("/") == 0) {
                outputBuffer += "/";
                inputBuffer.erase(0, 1);
            }
            // Move path segment from input buffer to output buffer.
            size_t pos = 0;
            if ((pos = inputBuffer.find("/")) != std::string::npos) {
                outputBuffer += inputBuffer.substr(0, pos);
                inputBuffer.erase(0, pos);
            } else { // only have last segment rest.
                outputBuffer += inputBuffer;
                inputBuffer.clear();
            }
        }
        /* DEBUG code */
        // std::cout << "out: " << outputBuffer << " ";
        // std::cout << "in: " << inputBuffer << std::endl;
    }
}

} // namespace uri
