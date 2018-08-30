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

TEST(StrSplitRef, SuccessSplit)
{
    using FType = std::vector<std::string_view>(*)(const std::string&, const std::string &);
    successSplitImpl<std::string>(strSample(), " ", strTokens(), static_cast<FType>(&str_utils::split_str_ref));
}

TEST(WStrSplitRef, SuccessSplit)
{
    successSplitImpl<std::wstring>(wstrSample(), L" ", wstrTokens(), &str_utils::split_wstr_ref);
}

TEST(StrSplitRef, EmptyInput)
{
    std::string input = "";

    auto tokens = str_utils::split_str_ref(input, " ");
    ASSERT_EQ(tokens.size(), 0);
}

TEST(StrSplitRef, LongSep)
{
    std::string input = "Lorem inpsum";

    auto tokens = str_utils::split_str_ref(input, "qqqqqqqqqqqqqqqq");
    ASSERT_EQ(tokens.size(), 1);
    ASSERT_EQ(tokens.at(0), input);
}

TEST(StrSplitRef, EmptySep)
{
    std::string input = "Lorem inpsum";

    auto tokens = str_utils::split_str_ref(input, "");
    ASSERT_EQ(tokens.size(), 1);
    ASSERT_EQ(tokens.at(0), input);
}

TEST(StrSplitRef, InputWithoutSep)
{
    std::string input = "Lorem inpsum";

    auto tokens = str_utils::split_str_ref(input, "qq");
    ASSERT_EQ(tokens.size(), 1);
    ASSERT_EQ(tokens.at(0), input);
}

TEST(StrSplitRef, ResultIsAView)
{
    std::string input = "Lorem inpsum";

    auto tokens = str_utils::split_str_ref(input, " ");
    ASSERT_EQ(tokens.size(), 2);
    ASSERT_EQ(tokens.at(0), "Lorem");
    ASSERT_EQ(tokens.at(1), "inpsum");

    ASSERT_EQ(tokens.at(0).data(), input.data());
    ASSERT_EQ(tokens.at(1).data(), input.data() + 6);
}

TEST(StrSplit, EqualToSplitRef)
{
    auto input = strSample();
    auto tokens = strTokens();

    auto refTokens = str_utils::split_str_ref(input, " ");
    auto copiedTokens = str_utils::split_str(input, " ");

    ASSERT_EQ(refTokens.size(), copiedTokens.size());
    ASSERT_TRUE(std::equal(std::begin(refTokens), std::end(refTokens), std::begin(copiedTokens)));
}

TEST(StrSplit, ResultIsACopy)
{
    std::string input = "Lorem inpsum";

    // The input variable is not used intentionally
    auto tokens = str_utils::split_str("Lorem inpsum", " ");

    ASSERT_EQ(tokens.size(), 2);

    ASSERT_EQ(tokens.at(0), "Lorem");
    ASSERT_EQ(tokens.at(1), "inpsum");

    ASSERT_NE(tokens.at(0).data(), input.data());
    ASSERT_NE(tokens.at(1).data(), input.data() + 6);
}

TEST(StrSplitRe, SuccessSplit)
{
    std::string in = "Lorem inpsum";
    std::regex re{"([a-zA-Z]+)"};

    auto tokens = str_utils::split_str_ref(in, re);

    ASSERT_EQ(tokens.size(), 2);
    ASSERT_EQ(tokens.at(0), "Lorem");
    ASSERT_EQ(tokens.at(1), "inpsum");
}
