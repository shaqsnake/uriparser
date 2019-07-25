// Copyright (c) 2019 shaqsnake. All rights reserved.
/**
 * @Author: shaqsnake
 * @Email: shaqsnake@gmail.com
 * @Date: 2019-07-25 14:13:54
 * @LastEditTime: 2019-07-25 14:59:51
 * @Description:
 */
#include <gtest/gtest.h>
#include <src/UriPctCoder.hpp>

TEST(UriPctCoderTests, EncodeUnreservedCharater) {
    struct TestCase {
        std::string inputCharaters;
        std::string expectedHexdig;
    };

    std::vector<TestCase> testCases{
        {" ", "%20"},  {"!", "%21"},
        {"\"", "%22"}, {"#", "%23"},
        {"$", "%24"},  {"%", "%25"},
        {"&", "%26"},  {"'", "%27"},
        {"(", "%28"},  {")", "%29"},
        {"*", "%2A"},  {"+", "%2B"},
        {",", "%2C"},  {"/", "%2F"},
        {":", "%3A"},  {";", "%3B"},
        {"<", "%3C"},  {"=", "%3D"},
        {">", "%3E"},  {"?", "%3F"},
        {"@", "%40"},  {"[", "%5B"},
        {"{", "%7B"},  {"|", "%7C"},
        {"}", "%7D"},  {"@ABC?012#-_ .~", "%40ABC%3F012%23-_%20.~"},
    };

    uri::UriPctCoder pctCoder;
    size_t idx = 0;
    for (const auto &testCase : testCases) {
        auto targetHexdig = pctCoder.encode(testCase.inputCharaters);
        ASSERT_EQ(testCase.expectedHexdig, targetHexdig)
            << ">>> Test is failed at " << idx << ". <<<";
        ++idx;
    }
}