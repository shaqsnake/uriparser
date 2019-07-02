// Copyright (c) 2019 shaqsnake. All rights reserved.
/**
 * @Author: shaqsnake
 * @Email: shaqsnake@gmail.com
 * @Date: 2019-06-27 09:17:12
 * @LastEditTime: 2019-07-02 17:11:43
 * @Description: A unittest of class uri::Uri.
 */
#include <gtest/gtest.h>
#include <uriparser/Uri.hpp>
TEST(UriTests, ParseFromCommonUri) {
    uri::Uri uri;
    ASSERT_TRUE(
        uri.parseFromString("http://user:password@example.com:8080/some/path/"
                            "to/somewhere?search=regex&order=desc#fragment"));
    ASSERT_EQ("http", uri.getScheme());
    ASSERT_EQ("user:password@example.com:8080", uri.getAuthority());
    ASSERT_EQ("example.com", uri.getHost());
    ASSERT_EQ(8080, uri.getPort());
    ASSERT_EQ("/some/path/to/somewhere", uri.getPath());
    ASSERT_EQ("search=regex&order=desc", uri.getQuery());
    ASSERT_EQ("fragment", uri.getFragment());
}

TEST(UriTests, ParseFromUrn) {
    uri::Uri uri;
    ASSERT_TRUE(uri.parseFromString(
        "urn:oasis:names:specification:docbook:dtd:xml:4.1.2"));
    ASSERT_EQ("urn", uri.getScheme());
    ASSERT_EQ("", uri.getAuthority());
    ASSERT_EQ("", uri.getHost());
    ASSERT_EQ(-1, uri.getPort());
    ASSERT_EQ("oasis:names:specification:docbook:dtd:xml:4.1.2", uri.getPath());
    ASSERT_EQ("", uri.getQuery());
    ASSERT_EQ("", uri.getFragment());
}

TEST(UriTests, ParseFromNestedUri) {
    uri::Uri uri;
    ASSERT_TRUE(
        uri.parseFromString("mina:tcp://mainframeip:4444?textline=true"));
    ASSERT_EQ("mina", uri.getScheme());
    ASSERT_EQ("", uri.getAuthority());
    ASSERT_EQ("", uri.getHost());
    ASSERT_EQ(-1, uri.getPort());
    ASSERT_EQ("tcp://mainframeip:4444", uri.getPath());
    ASSERT_EQ("textline=true", uri.getQuery());
    ASSERT_EQ("", uri.getFragment());
}

// TEST(UriTests, ParseFromIPv6Addr) {
//     uri::Uri uri;
//     ASSERT_TRUE(
//         uri.parseFromString("ldap://[2001:db8::7]/c=GB?objectClass?one"));
//     ASSERT_EQ("ldap", uri.getScheme());
//     ASSERT_EQ("[2001:db8::7]", uri.getAuthority());
//     ASSERT_EQ("2001:db8::7", uri.getHost());
//     ASSERT_EQ(-1, uri.getPort());
//     ASSERT_EQ("/c=GB", uri.getPath());
//     ASSERT_EQ("objectClass?one", uri.getQuery());
//     ASSERT_EQ("", uri.getFragment());
// }

TEST(UriTests, ParseFromGeneralUriStrings) {
    struct Tests {
        std::string uriString;
        std::string authority;
        std::string path;
    };

    std::vector<Tests> testCases{
        {
            "ftp://ftp.is.co.za/rfc/rfc1808.txt",
            "ftp.is.co.za",
            "/rfc/rfc1808.txt",
        },
        {
            "http://www.ietf.org/rfc/rfc2396.txt",
            "www.ietf.org",
            "/rfc/rfc2396.txt",
        },
        {
            "ldap://[2001:db8::7]/c=GB?objectClass?one",
            "[2001:db8::7]",
            "",
        },
        {
            "mailto:John.Doe@example.com",
            "",
            "John.Doe@example.com",
        },
        {
            "news:comp.infosystems.www.servers.unix",
            "",
            "comp.infosystems.www.servers.unix",
        },
        {
            "tel:+1-816-555-1212",
            "",
            "+1-816-555-1212",
        },
        {
            "telnet://192.0.2.16:80/",
            "192.0.2.16:80",
            "/",
        },
        {"urn:oasis:names:specification:docbook:dtd:xml:4.1.2", "",
         "oasis:names:specification:docbook:dtd:xml:4.1.2"},
    };

    std::size_t idx = 0;
    uri::Uri uri;
    for (const auto &testCase : testCases) {
        ASSERT_TRUE(uri.parseFromString(testCase.uriString)) << idx;
        ASSERT_EQ(testCase.authority, uri.getAuthority()) << idx;
        ++idx;
    }
}
