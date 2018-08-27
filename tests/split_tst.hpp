#pragma once

#include <functional>

#include <gtest/gtest.h>

#include "split.hpp"
#include "helpers.hpp"

template <class String, class Tokens, class Splitter>
void successSplitImpl(const String &input, const String &delim, const Tokens &resTokens, Splitter s)
{
    auto tokens = std::invoke(s, input, delim);
    ASSERT_EQ(tokens.size(), 19);

    ASSERT_TRUE(std::equal(std::begin(resTokens), std::end(resTokens), std::begin(tokens)));
}

TEST(StrSplit, TestSplit_SuccessSplit)
{
    successSplitImpl<std::string>(strSample(), " ", strTokens(), &str::split_str);
}

TEST(WStrSplit, TestSplit_SuccessSplit)
{
    successSplitImpl<std::wstring>(wstrSample(), L" ", wstrTokens(), &str::split_wstr);
}

TEST(StrSplit, TestSplit_EmptyInput)
{
    std::string input = "";

    auto tokens = str::split_str(input, " ");
    ASSERT_EQ(tokens.size(), 0);
}

TEST(StrSplit, TestSplit_LongDelim)
{
    std::string input = "Lorem inpsum";

    auto tokens = str::split_str(input, "qqqqqqqqqqqqqqqq");
    ASSERT_EQ(tokens.size(), 1);
    ASSERT_EQ(tokens.at(0), input);
}

TEST(StrSplit, TestSplit_EmptyDelim)
{
    std::string input = "Lorem inpsum";

    auto tokens = str::split_str(input, "");
    ASSERT_EQ(tokens.size(), 1);
    ASSERT_EQ(tokens.at(0), input);
}

TEST(StrSplit, TestSplit_InputWithoutDelim)
{
    std::string input = "Lorem inpsum";

    auto tokens = str::split_str(input, "qq");
    ASSERT_EQ(tokens.size(), 1);
    ASSERT_EQ(tokens.at(0), input);
}

TEST(StrSplit, TestSplit_ResultIsAView)
{
    std::string input = "Lorem inpsum";

    auto tokens = str::split_str(input, " ");
    ASSERT_EQ(tokens.size(), 2);
    ASSERT_EQ(tokens.at(0), "Lorem");
    ASSERT_EQ(tokens.at(1), "inpsum");

    ASSERT_EQ(tokens.at(0).data(), input.data());
    ASSERT_EQ(tokens.at(1).data(), input.data() + 6);
}
