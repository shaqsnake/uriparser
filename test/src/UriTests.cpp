// Copyright (c) 2019 shaqsnake. All rights reserved.
/**
 * @Author: shaqsnake
 * @Email: shaqsnake@gmail.com
 * @Date: 2019-06-27 09:17:12
 * @LastEditTime: 2019-06-28 16:50:53
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
    // ASSERT_EQ("example.com", uri.getHost());
    // ASSERT_EQ("8080", uri.getPort());
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
    // ASSERT_EQ("", uri.getHost());
    // ASSERT_EQ("", uri.getPort());
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
    ASSERT_EQ("/c=GB", uri.getPath());
    ASSERT_EQ("objectClass?one", uri.getQuery());
    ASSERT_EQ("", uri.getFragment());
}