// Copyright (c) 2019 shaqsnake. All rights reserved.
/**
 * @Author: shaqsnake
 * @Email: shaqsnake@gmail.com
 * @Date: 2019-07-03 10:26:50
 * @LastEditTime: 2019-07-10 09:23:51
 * @Description: A header to present uri pattern.
 */
#ifndef URIPARSER_URIPATTERN_HPP
#define URIPARSER_URIPATTERN_HPP

#include <string>

namespace uri {

static const std::string UriPattern =
    "^(([^:/?#]+):)?(//([^/?#]*))?([^?#]*)(\\?([^#]*))?(#(.*))?";

static const std::string SchemePattern = "[A-Za-z][A-Za-z0-9+\\-.]*";

static const std::string UserInfoPattern = "((?:[A-Za-z0-9\\-._~!$&'()*+,;=:]|"
                                           "%[0-9A-Fa-f]{2})*)";

static const std::string IPLiteralPattern =
    "(?:\\[.*?\\])"; // TODO: Refactor the regex of IPv6 and IP-future

static const std::string IPv4addressPattern =
    "(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}"
    "(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)";

static const std::string RegNamePattern =
    "(?:[A-Za-z0-9\\-._~!$&'()*+,;=]|%[0-9A-Fa-f]{2})*";

static const std::string PortPattern = "([0-9]*)";

static const std::string HostPattern = "(" + IPLiteralPattern + "|" +
                                       IPv4addressPattern + "|" +
                                       RegNamePattern + ")";

static const std::string AuthorityPatten = "(?:" + UserInfoPattern + "@)?" +
                                           "(?:" + HostPattern + ")" +
                                           "(?::" + PortPattern + ")?";

static const std::string PathAbemptyPattern =
    "(?:/(?:[A-Za-z0-9\\-._~!$&'()*+,;=:@]|%[0-9A-Fa-f]{2})*)*";

static const std::string PathAbsolutePattern =
    "/"
    "(?:(?:[A-Za-z0-9\\-._~!$&'()*+,;=:@]|%[0-9A-Fa-f]{2})+"
    "(?:/(?:[A-Za-z0-9\\-._~!$&'()*+,;=:@]|%[0-9A-Fa-f]{2})*)*"
    ")?";

static const std::string PathNoschemePattern =
    "(?:[A-Za-z0-9\\-._~!$&'()*+,;=@]|%[0-9A-Fa-f]{2})+"
    "(?:/(?:[A-Za-z0-9\\-._~!$&'()*+,;=:@]|%[0-9A-Fa-f]{2})*)*";

static const std::string PathRootlessPattern =
    "(?:[A-Za-z0-9\\-._~!$&'()*+,;=:@]|%[0-9A-Fa-f]{2})+"
    "(?:/(?:[A-Za-z0-9\\-._~!$&'()*+,;=:@]|%[0-9A-Fa-f]{2})*)*";

static const std::string PathPattern =
    "(?:" + PathAbemptyPattern + "|" + PathAbsolutePattern + "|" +
    PathNoschemePattern + "|" + PathRootlessPattern + "|)";

static const std::string QueryPattern = "(?:[A-Za-z0-9\\-._~!$&'()*+,;=:@/?]|%[0-9A-Fa-f]{2})*";

static const std::string FragmentPattern = "(?:[A-Za-z0-9\\-._~!$&'()*+,;=:@/?]|%[0-9A-Fa-f]{2})*";

} // namespace uri

#endif // URIPARSER_URIPATTERN_HPP