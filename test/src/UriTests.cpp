// Copyright (c) 2019 shaqsnake. All rights reserved.
/**
 * @Author: shaqsnake
 * @Email: shaqsnake@gmail.com
 * @Date: 2019-06-27 09:17:12
 * @LastEditTime: 2019-07-22 17:27:15
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

TEST(UriTests, ParseFromIPv6Addr) {
    uri::Uri uri;
    ASSERT_TRUE(
        uri.parseFromString("ldap://[2001:db8::7]/c=GB?objectClass?one"));
    ASSERT_EQ("ldap", uri.getScheme());
    ASSERT_EQ("[2001:db8::7]", uri.getAuthority());
    ASSERT_EQ("[2001:db8::7]", uri.getHost());
    ASSERT_EQ(-1, uri.getPort());
    ASSERT_EQ("/c=GB", uri.getPath());
    ASSERT_EQ("objectClass?one", uri.getQuery());
    ASSERT_EQ("", uri.getFragment());
}

TEST(UriTests, ParseFromGeneralUriStrings) {
    struct TestCase {
        std::string uriString;
        std::string authority;
        std::string path;
    };

    std::vector<TestCase> testCases{
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

TEST(UriTests, ParseFromUriWithInvalidScheme) {

    std::vector<std::string> uriStrings{
        "123://example.com",  "0foo://example.com", "+foo://example.com",
        "foo!://example.com", "foo$://example.com", "foo&://example.com",
        "foo'://example.com", "foo(://example.com", "foo)://example.com",
        "foo*://example.com", "foo,://example.com", "foo;://example.com",
        "foo=://example.com", "foo[://example.com", "foo]://example.com",
        "foo@://example.com", "foo_://example.com", "foo~://example.com",
        // In this case , the scheme is "foo", so it's legal,
        // but the authority, "://example.com", is ilegal.
        // "foo:://example.com", "foo?://example.com", "foo#://example.com",
    };

    size_t idx = 0;
    uri::Uri uri;
    for (const auto &uriString : uriStrings) {
        ASSERT_FALSE(uri.parseFromString(uriString)) << idx;
        ++idx;
    }
}

TEST(UriTests, PaserFromUriWithBarelyValidScheme) {
    struct TestCase {
        std::string uriString;
        std::string scheme;
    };

    std::vector<TestCase> testCases{
        {"foo0://example.com", "foo0"}, {"foo+://example.com", "foo+"},
        {"foo-://example.com", "foo-"}, {"foo.://example.com", "foo."},
        {"f0o://example.com", "f0o"},   {"f+o://example.com", "f+o"},
        {"f-o://example.com", "f-o"},   {"f.o://example.com", "f.o"},
    };

    size_t idx = 0;
    uri::Uri uri;
    for (const auto &testCase : testCases) {
        ASSERT_TRUE(uri.parseFromString(testCase.uriString)) << idx;
        ASSERT_EQ(testCase.scheme, uri.getScheme()) << idx;
        ++idx;
    }
}

TEST(UriTests, ParseFromUriWithInvalidAuthority) {
    std::vector<std::string> uriStrings{
        // Testcase of userinfo
        "foo://bar[@example.com",
        "foo://bar]@example.com",
        "foo://bar@@example.com",
        // Tesecase of host
        "foo://bar@example:com",
        "foo://bar@example[com",
        "foo://bar@example]com",
        "foo://bar@example@com",
        // Testcase of port
        "foo://bar@example.com:-2",
        "foo://bar@example.com:65536",
    };

    size_t idx = 0;
    uri::Uri uri;
    for (const auto &uriString : uriStrings) {
        ASSERT_FALSE(uri.parseFromString(uriString))
            << ">>> Test is failed at " << idx << ". <<<";
        ++idx;
    }
}

TEST(UriTests, PaserFromUriWithBarelyValidAuthority) {
    struct TestCase {
        std::string uriString;
        std::string authority;
        std::string userinfo;
        std::string host;
        int port;
    };

    std::vector<TestCase> testCases{
        // Testcase of userinfo
        {"foo://bar@example.com:80", "bar@example.com:80", "bar", "example.com",
         80},
        {"foo://bar:@example.com:80", "bar:@example.com:80",
         "bar:", "example.com", 80},
        {"foo://bar-@example.com:80", "bar-@example.com:80", "bar-",
         "example.com", 80},
        {"foo://bar.@example.com:80", "bar.@example.com:80", "bar.",
         "example.com", 80},
        {"foo://bar_@example.com:80", "bar_@example.com:80", "bar_",
         "example.com", 80},
        {"foo://bar~@example.com:80", "bar~@example.com:80", "bar~",
         "example.com", 80},
        {"foo://bar0@example.com:80", "bar0@example.com:80", "bar0",
         "example.com", 80},
        {"foo://bar!@example.com:80", "bar!@example.com:80", "bar!",
         "example.com", 80},
        {"foo://bar$@example.com:80", "bar$@example.com:80", "bar$",
         "example.com", 80},
        {"foo://bar&@example.com:80", "bar&@example.com:80", "bar&",
         "example.com", 80},
        {"foo://bar'@example.com:80", "bar'@example.com:80", "bar'",
         "example.com", 80},
        {"foo://bar(@example.com:80", "bar(@example.com:80", "bar(",
         "example.com", 80},
        {"foo://bar)@example.com:80", "bar)@example.com:80", "bar)",
         "example.com", 80},
        {"foo://bar*@example.com:80", "bar*@example.com:80", "bar*",
         "example.com", 80},
        {"foo://bar+@example.com:80", "bar+@example.com:80", "bar+",
         "example.com", 80},
        {"foo://bar,@example.com:80", "bar,@example.com:80", "bar,",
         "example.com", 80},
        {"foo://bar;@example.com:80", "bar;@example.com:80", "bar;",
         "example.com", 80},
        {"foo://bar=@example.com:80", "bar=@example.com:80",
         "bar=", "example.com", 80},
        // Tesecase of host
        {"foo://bar@example-com:80", "bar@example-com:80", "bar", "example-com",
         80},
        {"foo://bar@example.com:80", "bar@example.com:80", "bar", "example.com",
         80},
        {"foo://bar@example_com:80", "bar@example_com:80", "bar", "example_com",
         80},
        {"foo://bar@example~com:80", "bar@example~com:80", "bar", "example~com",
         80},
        {"foo://bar@example0com:80", "bar@example0com:80", "bar", "example0com",
         80},
        {"foo://bar@example!com:80", "bar@example!com:80", "bar", "example!com",
         80},
        {"foo://bar@example$com:80", "bar@example$com:80", "bar", "example$com",
         80},
        {"foo://bar@example&com:80", "bar@example&com:80", "bar", "example&com",
         80},
        {"foo://bar@example'com:80", "bar@example'com:80", "bar", "example'com",
         80},
        {"foo://bar@example(com:80", "bar@example(com:80", "bar", "example(com",
         80},
        {"foo://bar@example)com:80", "bar@example)com:80", "bar", "example)com",
         80},
        {"foo://bar@example*com:80", "bar@example*com:80", "bar", "example*com",
         80},
        {"foo://bar@example+com:80", "bar@example+com:80", "bar", "example+com",
         80},
        {"foo://bar@example,com:80", "bar@example,com:80", "bar", "example,com",
         80},
        {"foo://bar@example;com:80", "bar@example;com:80", "bar", "example;com",
         80},
        {"foo://bar@example=com:80", "bar@example=com:80", "bar", "example=com",
         80},
        // Testcase of port
        {"foo://bar@example.com:0", "bar@example.com:0", "bar", "example.com",
         0},
        {"foo://bar@example.com:65535", "bar@example.com:65535", "bar",
         "example.com", 65535},
    };

    size_t idx = 0;
    uri::Uri uri;
    for (const auto &testCase : testCases) {
        ASSERT_TRUE(uri.parseFromString(testCase.uriString))
            << ">>> Test is failed at " << idx << ". <<<";
        ASSERT_EQ(testCase.authority, uri.getAuthority())
            << ">>> Test is failed at " << idx << ". <<<";
        ASSERT_EQ(testCase.userinfo, uri.getUserinfo())
            << ">>> Test is failed at " << idx << ". <<<";
        ASSERT_EQ(testCase.host, uri.getHost())
            << ">>> Test is failed at " << idx << ". <<<";
        ASSERT_EQ(testCase.port, uri.getPort())
            << ">>> Test is failed at " << idx << ". <<<";
        ++idx;
    }
}

TEST(UriTests, ParseFromUriWithInvalidIPv6Addr) {
    std::vector<std::string> uriStrings{
        "http://[]",
        "http://[:]",
        "http://[I]",
        "http://[::fFfF::1]",
        "http://[::ffff:1.2.x.4]/",
        "http://[::ffff:1.2.3.4.8]/",
        "http://[::ffff:1.2.3]/",
        "http://[::ffff:1.2.3.]/",
        "http://[::ffff:1.2.3.256]/",
        "http://[::fxff:1.2.3.4]/",
        "http://[::ffff:1.2.3.-4]/",
        "http://[::ffff:1.2.3. 4]/",
        "http://[::ffff:1.2.3.4 ]/",
        "http://[::ffff:1.2.3.4/",
        "http://::ffff:1.2.3.4]/",
        "http://::ffff:a.2.3.4]/",
        "http://::ffff:1.a.3.4]/",
        "http://[2001:db8:85a3:8d3:1319:8a2e:370:7348:0000]/",
        "http://[2001:db8:85a3::8a2e:0:]/",
        "http://[2001:db8:85a3::8a2e::]/",
    };

    size_t idx = 0;
    uri::Uri uri;
    for (const auto &uriString : uriStrings) {
        ASSERT_FALSE(uri.parseFromString(uriString))
            << ">>> Test is failed at " << idx << ". <<<";
        ++idx;
    }
}

TEST(UriTests, PaserFromUriWithBarelyValidIPv6Addr) {
    struct TestCase {
        std::string uriString;
        std::string host;
    };

    std::vector<TestCase> testCases{
        {"http://[::1]/", "[::1]"},
        {"http://[::ffff:1.2.3.4]/", "[::ffff:1.2.3.4]"},
        {"http://[2001:db8:85a3:8d3:1319:8a2e:370:7348]/",
         "[2001:db8:85a3:8d3:1319:8a2e:370:7348]"},
        {"http://[fFfF::1]", "[ffff::1]"},
        {"http://[fFfF:1:2:3:4:5:6:a]", "[ffff:1:2:3:4:5:6:a]"},
    };

    size_t idx = 0;
    uri::Uri uri;
    for (const auto &testCase : testCases) {
        ASSERT_TRUE(uri.parseFromString(testCase.uriString))
            << ">>> Test is failed at " << idx << ". <<<";
        ASSERT_EQ(testCase.host, uri.getHost())
            << ">>> Test is failed at " << idx << ". <<<";
        ++idx;
    }
}

TEST(UriTests, ParseFromUriWithInvalidPath) {
    std::vector<std::string> uriStrings{
        "foo://example.com/[bar",
        "foo://example.com/]bar",
    };

    size_t idx = 0;
    uri::Uri uri;
    for (const auto &uriString : uriStrings) {
        ASSERT_FALSE(uri.parseFromString(uriString))
            << ">>> Test is failed at " << idx << ". <<<";
        ++idx;
    }
}

TEST(UriTests, PaserFromUriWithBarelyValidPath) {
    struct TestCase {
        std::string uriString;
        std::string path;
    };

    std::vector<TestCase> testCases{
        {"foo://example.com/bar", "/bar"},
        {"foo://example.com/0bar", "/0bar"},
        {"foo://example.com/:bar", "/:bar"},
        {"foo://example.com/@bar", "/@bar"},
        {"foo://example.com/-bar", "/-bar"},
        {"foo://example.com/.bar", "/.bar"},
        {"foo://example.com/_bar", "/_bar"},
        {"foo://example.com/~bar", "/~bar"},
        {"foo://example.com/!bar", "/!bar"},
        {"foo://example.com/$bar", "/$bar"},
        {"foo://example.com/&bar", "/&bar"},
        {"foo://example.com/'bar", "/'bar"},
        {"foo://example.com/(bar", "/(bar"},
        {"foo://example.com/)bar", "/)bar"},
        {"foo://example.com/*bar", "/*bar"},
        {"foo://example.com/+bar", "/+bar"},
        {"foo://example.com/,bar", "/,bar"},
        {"foo://example.com/;bar", "/;bar"},
        {"foo://example.com/=bar", "/=bar"},
    };

    size_t idx = 0;
    uri::Uri uri;
    for (const auto &testCase : testCases) {
        ASSERT_TRUE(uri.parseFromString(testCase.uriString))
            << ">>> Test is failed at " << idx << ". <<<";
        ASSERT_EQ(testCase.path, uri.getPath())
            << ">>> Test is failed at " << idx << ". <<<";
        ++idx;
    }
}

TEST(UriTests, ParseFromUriWithInvalidQuery) {
    std::vector<std::string> uriStrings{
        "foo://example.com/bar?zoo]",
        "foo://example.com/bar?zoo[",
    };

    size_t idx = 0;
    uri::Uri uri;
    for (const auto &uriString : uriStrings) {
        ASSERT_FALSE(uri.parseFromString(uriString))
            << ">>> Test is failed at " << idx << ". <<<";
        ++idx;
    }
}

TEST(UriTests, PaserFromUriWithBarelyValidQuery) {
    struct TestCase {
        std::string uriString;
        std::string query;
    };

    std::vector<TestCase> testCases{{"foo://example.com/bar?", ""},
                                    {"foo://example.com/bar?zoo", "zoo"},
                                    {"foo://example.com/bar?0zoo", "0zoo"},
                                    {"foo://example.com/bar?-zoo", "-zoo"},
                                    {"foo://example.com/bar?.zoo", ".zoo"},
                                    {"foo://example.com/bar?_zoo", "_zoo"},
                                    {"foo://example.com/bar?~zoo", "~zoo"},
                                    {"foo://example.com/bar?:zoo", ":zoo"},
                                    {"foo://example.com/bar?@zoo", "@zoo"},
                                    {"foo://example.com/bar?!zoo", "!zoo"},
                                    {"foo://example.com/bar?$zoo", "$zoo"},
                                    {"foo://example.com/bar?&zoo", "&zoo"},
                                    {"foo://example.com/bar?'zoo", "'zoo"},
                                    {"foo://example.com/bar?(zoo", "(zoo"},
                                    {"foo://example.com/bar?)zoo", ")zoo"},
                                    {"foo://example.com/bar?*zoo", "*zoo"},
                                    {"foo://example.com/bar?+zoo", "+zoo"},
                                    {"foo://example.com/bar?,zoo", ",zoo"},
                                    {"foo://example.com/bar?;zoo", ";zoo"},
                                    {"foo://example.com/bar?=zoo", "=zoo"},
                                    {"foo://example.com/bar?/zoo", "/zoo"},
                                    {"foo://example.com/bar??zoo", "?zoo"},
                                    {"foo?://example.com", "://example.com"}};

    size_t idx = 0;
    uri::Uri uri;
    for (auto const &testCase : testCases) {
        ASSERT_TRUE(uri.parseFromString(testCase.uriString))
            << ">>> Test is failed at " << idx << ". <<<";
        ASSERT_EQ(testCase.query, uri.getQuery())
            << ">>> Test is failed at " << idx << ". <<<";
        ++idx;
    }
}

TEST(UriTests, ParseFromUriWithInvalidFragment) {
    std::vector<std::string> uriStrings{
        "foo://example.com/bar#zoo]",
        "foo://example.com/bar#zoo[",
    };

    size_t idx = 0;
    uri::Uri uri;
    for (const auto &uriString : uriStrings) {
        ASSERT_FALSE(uri.parseFromString(uriString))
            << ">>> Test is failed at " << idx << ". <<<";
        ++idx;
    }
}

TEST(UriTests, PaserFromUriWithBarelyValidFragment) {
    struct TestCase {
        std::string uriString;
        std::string fragment;
    };

    std::vector<TestCase> testCases{
        {"foo://example.com/bar#", ""},
        {"foo://example.com/bar#zoo", "zoo"},
        {"foo://example.com/bar#0zoo", "0zoo"},
        {"foo://example.com/bar#-zoo", "-zoo"},
        {"foo://example.com/bar#.zoo", ".zoo"},
        {"foo://example.com/bar#_zoo", "_zoo"},
        {"foo://example.com/bar#~zoo", "~zoo"},
        {"foo://example.com/bar#:zoo", ":zoo"},
        {"foo://example.com/bar#@zoo", "@zoo"},
        {"foo://example.com/bar#!zoo", "!zoo"},
        {"foo://example.com/bar#$zoo", "$zoo"},
        {"foo://example.com/bar#&zoo", "&zoo"},
        {"foo://example.com/bar#'zoo", "'zoo"},
        {"foo://example.com/bar#(zoo", "(zoo"},
        {"foo://example.com/bar#)zoo", ")zoo"},
        {"foo://example.com/bar#*zoo", "*zoo"},
        {"foo://example.com/bar#+zoo", "+zoo"},
        {"foo://example.com/bar#,zoo", ",zoo"},
        {"foo://example.com/bar#;zoo", ";zoo"},
        {"foo://example.com/bar#=zoo", "=zoo"},
        {"foo://example.com/bar#/zoo", "/zoo"},
        {"foo://example.com/bar#?zoo", "?zoo"},
        {"foo#://example.com", "://example.com"},
    };

    size_t idx = 0;
    uri::Uri uri;
    for (auto const &testCase : testCases) {
        ASSERT_TRUE(uri.parseFromString(testCase.uriString))
            << ">>> Test is failed at " << idx << ". <<<";
        ASSERT_EQ(testCase.fragment, uri.getFragment())
            << ">>> Test is failed at " << idx << ". <<<";
        ++idx;
    }
}

TEST(UriTests, PaserFromUriDecodingAuthority) {
    struct TestCase {
        std::string rawUriString;
        std::string decodedUriString;
    };

    std::vector<TestCase> testCases{
        {"foo://bar@example.com:80", "bar@example.com:80"},
        {"foo://%41@example.com:80", "A@example.com:80"},
        {"foo://bar@ex%61mple.com:80", "bar@example.com:80"},
        {"foo://%41%42%43@example.com:80", "ABC@example.com:80"},
        {"foo://bar@example%2Ecom:80", "bar@example.com:80"},
        {"foo://bar@example%2ecom:80", "bar@example.com:80"},
        {"foo://bar@%61%62%63:80", "bar@abc:80"},
        {"foo://bar@%61%GG:80", "bar@a%GG:80"},
    };

    size_t idx = 0;
    uri::Uri uri;
    for (auto const &testCase : testCases) {
        uri.parseFromString(testCase.rawUriString);
        ASSERT_EQ(testCase.decodedUriString, uri.getAuthority())
            << ">>> Test is failed at " << idx << ". <<<";
        ++idx;
    }
}

TEST(UriTests, PaserFromUriDecodingPath) {
    struct TestCase {
        std::string rawUriString;
        std::string decodedUriString;
    };

    std::vector<TestCase> testCases{
        {"foo://example.com/bar", "/bar"},
        {"foo://example.com/b%61r", "/bar"},
        {"foo://example.com/bar/%2b", "/bar/+"},
        {"foo://example.com/b%2dr", "/b-r"},
        {"foo://example.com/b%2Dr", "/b-r"},
        {"foo://@example.com/%41%42%43", "/ABC"},
        {"foo://@example.com/%GG", "/%GG"},
    };

    size_t idx = 0;
    uri::Uri uri;
    for (auto const &testCase : testCases) {
        uri.parseFromString(testCase.rawUriString);
        ASSERT_EQ(testCase.decodedUriString, uri.getPath())
            << ">>> Test is failed at " << idx << ". <<<";
        ++idx;
    }
}

TEST(UriTests, PaserFromUriDecodingQuery) {
    struct TestCase {
        std::string rawUriString;
        std::string decodedUriString;
    };

    std::vector<TestCase> testCases{
        {"foo://example.com?bar", "bar"},
        {"foo://example.com?b%61r", "bar"},
        {"foo://example.com?bar/%2b", "bar/+"},
        {"foo://example.com?b%2dr", "b-r"},
        {"foo://example.com?b%2Dr", "b-r"},
        {"foo://@example.com?%41%42%43", "ABC"},
        {"foo://@example.com?%GG", "%GG"},
    };

    size_t idx = 0;
    uri::Uri uri;
    for (auto const &testCase : testCases) {
        uri.parseFromString(testCase.rawUriString);
        ASSERT_EQ(testCase.decodedUriString, uri.getQuery())
            << ">>> Test is failed at " << idx << ". <<<";
        ++idx;
    }
}

TEST(UriTests, PaserFromUriDecodingFragment) {
    struct TestCase {
        std::string rawUriString;
        std::string decodedUriString;
    };

    std::vector<TestCase> testCases{
        {"foo://example.com#bar", "bar"},
        {"foo://example.com#b%61r", "bar"},
        {"foo://example.com#bar/%2b", "bar/+"},
        {"foo://example.com#b%2dr", "b-r"},
        {"foo://example.com#b%2Dr", "b-r"},
        {"foo://@example.com#%41%42%43", "ABC"},
        {"foo://@example.com#%GG", "%GG"},
    };

    size_t idx = 0;
    uri::Uri uri;
    for (auto const &testCase : testCases) {
        uri.parseFromString(testCase.rawUriString);
        ASSERT_EQ(testCase.decodedUriString, uri.getFragment())
            << ">>> Test is failed at " << idx << ". <<<";
        ++idx;
    }
}

TEST(UriTests, ProduceToUriStrings) {
    struct TestCase {
        std::string inputUriString;
        std::string targetUriString;
    };

    std::vector<TestCase> testCases{
        {"http://user:password@example.com:8080/some/path/to"
         "/somewhere?search=regex&order=desc#fragment",
         "http%3A%2F%2Fuser%3Apassword%40example.com%3A8080%2Fsome%2Fpath%2Fto"
         "%2Fsomewhere%3Fsearch%3Dregex%26order%3Ddesc%23fragment"},
        {"foo://%41%42%43@example.com:80/b%2dr?GG",
         "foo%3A%2F%2FABC%40example.com%3A80%2Fb-r%3FGG"},
        {"example.com/", "example.com%2F"},
        {"/foo/bar", "%2Ffoo%2Fbar"},
        {"http://user:password@", "http%3A%2F%2Fuser%3Apassword%40"},
    };

    size_t idx = 0;
    for (const auto &testCase : testCases) {
        uri::Uri uri;
        ASSERT_TRUE(uri.parseFromString(testCase.inputUriString))
            << ">>> Test is failed at " << idx << ". <<<";
        ASSERT_EQ(testCase.targetUriString, uri.produceToString())
            << ">>> Test is failed at " << idx << ". <<<";
        ++idx;
    }
}

TEST(UriTests, ParseFromUriWithCaseSensitive) {
    struct TestCase {
        std::string uriString;
        std::string scheme;
        std::string host;
    };

    std::vector<TestCase> testCases{
        {"HTTP://www.EXAMPLE.com/", "http", "www.example.com"},
        {"htTp://www.example.com/", "http", "www.example.com"},
        {"http://www.exAMple.com/", "http", "www.example.com"},
        {"hTTp://www.ex%41%4dple.com/", "http", "www.example.com"},
    };

    size_t idx = 0;
    uri::Uri uri;
    for (const auto &testCase : testCases) {
        ASSERT_TRUE(uri.parseFromString(testCase.uriString))
            << ">>> Test is failed at " << idx << ". <<<";
        ASSERT_EQ(testCase.scheme, uri.getScheme())
            << ">>> Test is failed at " << idx << ". <<<";
        ASSERT_EQ(testCase.host, uri.getHost())
            << ">>> Test is failed at " << idx << ". <<<";
        ++idx;
    }
}

TEST(UriTests, ParseFromUriWithNomalizePath) {
    struct TestCase {
        std::string uriString;
        std::string path;
    };

    std::vector<TestCase> testCases{{"/a/b/c/./../../g", "/a/g"},
                                    {"mid/content=5/../6", "mid/6"},
                                    {"/a/b/c/../../../g", "/g"},
                                    {"/a/b/c/../../../../g", "/g"},
                                    {"foo://bar.com/", "/"},
                                    {"foo://bar.com/../g", "/g"},
                                    {"foo://bar.com/a/../b/", "/b/"},
                                    {"./foo/bar", "foo/bar"},
                                    {".", ""},
                                    {"..", ""},
                                    {"/", "/"},
                                    {"foo/bar", "foo/bar"},
                                    {"foo/bar/..", "foo/"},
                                    {"foo/bar/.", "foo/bar/"},
                                    {"foo/bar/./zoo", "foo/bar/zoo"},
                                    {"foo/bar/./zoo/", "foo/bar/zoo/"},
                                    {"./foo/bar/..", "foo/"},
                                    {"/./foo/bar", "/foo/bar"},
                                    {"/../foo/bar", "/foo/bar"},
                                    {"../foo/bar/./../zoo/", "foo/zoo/"}};

    size_t idx = 0;
    uri::Uri uri;
    for (const auto &testCase : testCases) {
        ASSERT_TRUE(uri.parseFromString(testCase.uriString))
            << ">>> Test is failed at " << idx << ". <<<";
        ASSERT_EQ(testCase.path, uri.getPath())
            << ">>> Test is failed at " << idx << ". <<<";
        ++idx;
    }
}

TEST(UriTests, ResolveRelativeUriString) {

    struct TestCase {
        std::string baseUri;
        std::string relativeRef;
        std::string targetUri;
    };

    std::vector<TestCase> testCases{
        {"http://a/b/c/d;p?q", "g:h", "g:h"},
        {"http://a/b/c/d;p?q", "g", "http://a/b/c/g"},
        {"http://a/b/c/d;p?q", "./g", "http://a/b/c/g"},
        {"http://a/b/c/d;p?q", "g/", "http://a/b/c/g/"},
        {"http://a/b/c/d;p?q", "/g", "http://a/g"},
        {"http://a/b/c/d;p?q", "//g", "http://g"},
        {"http://a/b/c/d;p?q", "?y", "http://a/b/c/d;p?y"},
        {"http://a/b/c/d;p?q", "g?y", "http://a/b/c/g?y"},
        {"http://a/b/c/d;p?q", "#s", "http://a/b/c/d;p?q#s"},
        {"http://a/b/c/d;p?q", "g#s", "http://a/b/c/g#s"},
        {"http://a/b/c/d;p?q", "g?y#s", "http://a/b/c/g?y#s"},
        {"http://a/b/c/d;p?q", ";x", "http://a/b/c/;x"},
        {"http://a/b/c/d;p?q", "g;x", "http://a/b/c/g;x"},
        {"http://a/b/c/d;p?q", "g;x?y#s", "http://a/b/c/g;x?y#s"},
        {"http://a/b/c/d;p?q", ""  , "http://a/b/c/d;p?q"},
        // {"http://a/b/c/d;p?q", "." , "http://a/b/c/"},
        // {"http://a/b/c/d;p?q", "./", "http://a/b/c/"},
        // {"http://a/b/c/d;p?q", "..", "http://a/b/"},
        // {"http://a/b/c/d;p?q", "../", "http://a/b/"},
        // {"http://a/b/c/d;p?q", "../g", "http://a/b/g"},
        // {"http://a/b/c/d;p?q", "../..", "http://a/"},
        // {"http://a/b/c/d;p?q", "../../", "http://a/"},
        // {"http://a/b/c/d;p?q", "../../g", "http://a/g"},
    };

    size_t idx = 0;
    uri::Uri uri;
    for (const auto &testCase : testCases) {
        ASSERT_TRUE(uri.parseFromString(testCase.baseUri));
        uri.resolve(testCase.relativeRef);
        ASSERT_EQ(testCase.targetUri, uri.produceToString(false))
            << ">>> Test is failed at " << idx << ". <<<";
        ++idx;
    }
}