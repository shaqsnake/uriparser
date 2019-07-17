// Copyright (c) 2019 shaqsnake. All rights reserved.
/**
 * @Author: shaqsnake
 * @Email: shaqsnake@gmail.com
 * @Date: 2019-07-03 10:26:50
 * @LastEditTime: 2019-07-17 11:35:23
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

static const std::string IPv6addressPattern = "(?:"
                                              "(?:(?:[0-9A-Fa-f]{1,4}:){6}"
                                              "|::(?:[0-9A-Fa-f]{1,4}:){5}"
                                              "|(?:[0-9A-Fa-f]{1,4})?::(?:[0-9A-Fa-f]{1,4}:){4}"
                                              "|(?:(?:[0-9A-Fa-f]{1,4}:){0,1}[0-9A-Fa-f]{1,4})?::(?:[0-9A-Fa-f]{1,4}:){3}"
                                              "|(?:(?:[0-9A-Fa-f]{1,4}:){0,2}[0-9A-Fa-f]{1,4})?::(?:[0-9A-Fa-f]{1,4}:){2}"
                                              "|(?:(?:[0-9A-Fa-f]{1,4}:){0,3}[0-9A-Fa-f]{1,4})?::[0-9A-Fa-f]{1,4}:"
                                              "|(?:(?:[0-9A-Fa-f]{1,4}:){0,4}[0-9A-Fa-f]{1,4})?::"
                                              ")(?:"                                                 // ls32
                                              "[0-9A-Fa-f]{1,4}:[0-9A-Fa-f]{1,4}"                    // factored out
                                              "|(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}"  // from first 7 liines
                                              "(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)"             // of ABNF rule above.
                                              ")"
                                              "|(?:(?:[0-9A-Fa-f]{1,4}:){0,5}[0-9A-Fa-f]{1,4})?::[0-9A-Fa-f]{1,4}"
                                              "|(?:(?:[0-9A-Fa-f]{1,4}:){0,6}[0-9A-Fa-f]{1,4})?::"
                                              ")";

static const std::string IPvFuturePattern = "[Vv][0-9A-Fa-f]+\\.[A-Za-z0-9\\-._~!$&'()*+,;=:]+"; // "v" 1*HEXDIG "." 1*( unreserved / sub-delims / ":" )

static const std::string IPLiteralPattern =
    "\\[(?:" + IPv6addressPattern + '|' + IPvFuturePattern + ")\\]";

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

static const std::string QueryPattern =
    "(?:[A-Za-z0-9\\-._~!$&'()*+,;=:@/?]|%[0-9A-Fa-f]{2})*";

static const std::string FragmentPattern =
    "(?:[A-Za-z0-9\\-._~!$&'()*+,;=:@/?]|%[0-9A-Fa-f]{2})*";

} // namespace uri

#endif // URIPARSER_URIPATTERN_HPP