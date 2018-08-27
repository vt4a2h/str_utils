#pragma once

#include <functional>

#include <gtest/gtest.h>

#include "split.hpp"
#include "helpers.hpp"

template <class String, class Tokens, class Splitter>
void successSplitImpl(const String &input, const String &sep, const Tokens &resTokens, Splitter s)
{
    auto tokens = std::invoke(s, input, sep);
    ASSERT_EQ(tokens.size(), 19);

    ASSERT_TRUE(std::equal(std::begin(resTokens), std::end(resTokens), std::begin(tokens)));
}

TEST(StrSplit, TestSplit_SuccessSplit)
{
    successSplitImpl<std::string>(strSample(), " ", strTokens(), &str_utils::split_str_ref);
}

TEST(WStrSplit, TestSplit_SuccessSplit)
{
    successSplitImpl<std::wstring>(wstrSample(), L" ", wstrTokens(), &str_utils::split_wstr_ref);
}

TEST(StrSplit, TestSplit_EmptyInput)
{
    std::string input = "";

    auto tokens = str_utils::split_str_ref(input, " ");
    ASSERT_EQ(tokens.size(), 0);
}

TEST(StrSplit, TestSplit_LongDelim)
{
    std::string input = "Lorem inpsum";

    auto tokens = str_utils::split_str_ref(input, "qqqqqqqqqqqqqqqq");
    ASSERT_EQ(tokens.size(), 1);
    ASSERT_EQ(tokens.at(0), input);
}

TEST(StrSplit, TestSplit_EmptyDelim)
{
    std::string input = "Lorem inpsum";

    auto tokens = str_utils::split_str_ref(input, "");
    ASSERT_EQ(tokens.size(), 1);
    ASSERT_EQ(tokens.at(0), input);
}

TEST(StrSplit, TestSplit_InputWithoutDelim)
{
    std::string input = "Lorem inpsum";

    auto tokens = str_utils::split_str_ref(input, "qq");
    ASSERT_EQ(tokens.size(), 1);
    ASSERT_EQ(tokens.at(0), input);
}

TEST(StrSplit, TestSplit_ResultIsAView)
{
    std::string input = "Lorem inpsum";

    auto tokens = str_utils::split_str_ref(input, " ");
    ASSERT_EQ(tokens.size(), 2);
    ASSERT_EQ(tokens.at(0), "Lorem");
    ASSERT_EQ(tokens.at(1), "inpsum");

    ASSERT_EQ(tokens.at(0).data(), input.data());
    ASSERT_EQ(tokens.at(1).data(), input.data() + 6);
}
