#pragma once

#include <string>
#include <algorithm>
#include <vector>
#include <locale>
#include <codecvt>

inline std::wstring toWideString(const std::string &s)
{
   return std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>().from_bytes(s);
}

inline std::string strSample()
{
    return "Lorem ipsum dolor sit amet, consectetur adipiscing elit,"
           " sed do eiusmod tempor incididunt ut labore et dolore magna aliqua";
}

inline std::vector<std::string> strTokens()
{
    return {"Lorem", "ipsum", "dolor", "sit", "amet,", "consectetur",
            "adipiscing", "elit,", "sed", "do", "eiusmod", "tempor",
            "incididunt", "ut", "labore", "et", "dolore", "magna", "aliqua"};
}

inline std::wstring wstrSample()
{
    static auto result = toWideString(strSample());
    return result;
}

inline std::vector<std::wstring> wstrTokens()
{
    static auto result = []{
        auto inTokens = strTokens();

        std::vector<std::wstring> tokens;
        tokens.reserve(inTokens.size());
        std::transform(std::begin(inTokens), std::end(inTokens),
                       std::back_inserter(tokens), [](auto &&token) { return toWideString(token); });
        return tokens;
    }();

    return result;
}
