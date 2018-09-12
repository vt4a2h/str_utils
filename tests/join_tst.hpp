#pragma once

#include <iterator>

#include <gtest/gtest.h>

#include "join.hpp"
#include "helpers.hpp"

TEST(JoinStr, SuccessJoin)
{
    auto in = strTokens();

    auto result = str_utils::join(in, std::string(" "));

    ASSERT_EQ(result, strSample());
}

TEST(JoinWStr, SuccessJoin)
{
    auto in = wstrTokens();

    auto result = str_utils::join(in, std::wstring(L" "));

    ASSERT_EQ(result, wstrSample());
}

TEST(JoinStr, JoinEmptyContainer)
{
    std::vector<std::string> in;

    auto result = str_utils::join(in, std::string(" "));

    ASSERT_EQ(result, std::string(""));
}

TEST(JoinStr, JoinContainerWithOneToken)
{
    std::vector<std::string> in{"Lorem"};

    auto result = str_utils::join(in, std::string(" "));

    ASSERT_EQ(result, std::string("Lorem"));
}

TEST(JoinStr, JoinViews)
{
    auto in = strTokens();

    std::vector<std::string_view> views;
    views.reserve(in.size());
    for (auto &&str: in)
        views.emplace_back(str.data(), str.length());

    for (std::size_t i = 0; i < in.size(); ++i)
        ASSERT_EQ(in.at(i).data(), views.at(i).data());

    auto result = str_utils::join(views, std::string(" "));

    ASSERT_EQ(result, strSample());
}
