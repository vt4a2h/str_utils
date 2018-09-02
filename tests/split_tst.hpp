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

TEST(StrSplitView, SuccessSplit)
{
    using FType = std::vector<std::string_view>(*)(const std::string&, const std::string &);
    successSplitImpl<std::string>(strSample(), " ", strTokens(), static_cast<FType>(&str_utils::split_view));
}

TEST(WStrSplitView, SuccessSplit)
{
    using FType = std::vector<std::wstring_view>(*)(const std::wstring&, const std::wstring &);
    successSplitImpl<std::wstring>(wstrSample(), L" ", wstrTokens(), static_cast<FType>(&str_utils::split_view));
}

TEST(StrSplitView, EmptyInput)
{
    std::string input = "";

    auto tokens = str_utils::split_view(input, " ");
    ASSERT_EQ(tokens.size(), 0);
}

TEST(StrSplitView, LongSep)
{
    std::string input = "Lorem inpsum";

    auto tokens = str_utils::split_view(input, "qqqqqqqqqqqqqqqq");
    ASSERT_EQ(tokens.size(), 1);
    ASSERT_EQ(tokens.at(0), input);
}

TEST(StrSplitView, EmptySep)
{
    std::string input = "Lorem inpsum";

    auto tokens = str_utils::split_view(input, "");
    ASSERT_EQ(tokens.size(), 1);
    ASSERT_EQ(tokens.at(0), input);
}

TEST(StrSplitView, InputWithoutSep)
{
    std::string input = "Lorem inpsum";

    auto tokens = str_utils::split_view(input, "qq");
    ASSERT_EQ(tokens.size(), 1);
    ASSERT_EQ(tokens.at(0), input);
}

TEST(StrSplitView, ResultIsAView)
{
    std::string input = "Lorem inpsum";

    auto tokens = str_utils::split_view(input, " ");
    ASSERT_EQ(tokens.size(), 2);
    ASSERT_EQ(tokens.at(0), "Lorem");
    ASSERT_EQ(tokens.at(1), "inpsum");

    ASSERT_EQ(tokens.at(0).data(), input.data());
    ASSERT_EQ(tokens.at(1).data(), input.data() + 6);
}

TEST(StrSplit, EqualToSplitView)
{
    auto input = strSample();
    auto tokens = strTokens();

    auto refTokens = str_utils::split_view(input, " ");
    auto copiedTokens = str_utils::split(input, " ");

    ASSERT_EQ(refTokens.size(), copiedTokens.size());
    ASSERT_TRUE(std::equal(std::begin(refTokens), std::end(refTokens), std::begin(copiedTokens)));
}

TEST(StrSplit, ResultIsACopy)
{
    std::string input = "Lorem inpsum";

    // The input variable is not used intentionally
    auto tokens = str_utils::split("Lorem inpsum", " ");

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

    auto tokens = str_utils::split_view(in, re);

    ASSERT_EQ(tokens.size(), 2);
    ASSERT_EQ(tokens.at(0), "Lorem");
    ASSERT_EQ(tokens.at(1), "inpsum");
}

TEST(WStrSplitRe, SuccessSplit)
{
    std::wstring in = L"Lorem inpsum";
    std::wregex re{L"([a-zA-Z]+)"};

    auto tokens = str_utils::split(in, re);

    ASSERT_EQ(tokens.size(), 2);
    ASSERT_EQ(tokens.at(0), L"Lorem");
    ASSERT_EQ(tokens.at(1), L"inpsum");
}

TEST(StrSplitRe, ResultIsAView)
{
    std::string in = "Lorem inpsum";
    std::regex re{"([a-zA-Z]+)"};

    auto tokens = str_utils::split_view(in, re);

    ASSERT_EQ(tokens.size(), 2);
    ASSERT_EQ(tokens.at(0).data(), in.data());
    ASSERT_EQ(tokens.at(1).data(), in.data() + 6);
}

TEST(StrSplitRe, ResultIsACopy)
{
    std::string in = "Lorem inpsum";
    std::regex re{"([a-zA-Z]+)"};

    auto tokens = str_utils::split(in, re);

    ASSERT_EQ(tokens.size(), 2);
    ASSERT_NE(tokens.at(0).data(), in.data());
    ASSERT_NE(tokens.at(1).data(), in.data() + 6);
}

TEST(StrSplitRe, NoMatches)
{
    std::string in = "Lorem inpsum";
    std::regex re{"(\\d+)"};

    auto tokens = str_utils::split_view(in, re);

    ASSERT_EQ(tokens.size(), 0);
}

TEST(StrSplitRe, EmptyInput)
{
    std::string in = "";
    std::regex re{"(\\d+)"};

    auto tokens = str_utils::split_view(in, re);

    ASSERT_EQ(tokens.size(), 0);
}

TEST(StrSplitRe, EmptyRegex)
{
    std::string in = "Lorem inpsum";
    std::regex re{""};

    auto tokens = str_utils::split_view(in, re);

    ASSERT_EQ(tokens.size(), 0);
}

