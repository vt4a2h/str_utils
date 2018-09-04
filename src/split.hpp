#pragma once

#include <string_view>
#include <string>
#include <vector>
#include <algorithm>
#include <regex>

namespace str_utils {

    namespace detail {

        template <
            class _CharT        = char                          ,
            class TokenType     = std::basic_string_view<_CharT>,
            class ContainerType = std::vector<TokenType>        ,
            class InputType     = std::basic_string_view<_CharT>>
        ContainerType split_impl(InputType view, InputType sep)
        {
            if (view.empty())
                return {};

            if (sep.empty() || sep.size() >= view.size())
                return {{view.data(), view.size()}};

            ContainerType result;

            auto first = std::begin(view);
            auto last = std::end(view);

            auto sepFirst = std::begin(sep);
            auto sepLast = std::end(sep);
            auto sepLen = std::distance(std::begin(sep), std::end(sep));

            auto sepCurrent = std::begin(view);

            while (sepCurrent != last && first != last) {
                sepCurrent = std::search(first, last, sepFirst, sepLast);

                auto len = std::distance(first, sepCurrent);
                if (len != 0)
                    result.emplace_back(&*first, len);

                std::advance(first, sepLen + len);
            }

            return result;
        }

        template <
            class _CharT        = char                          ,
            class TokenType     = std::basic_string_view<_CharT>,
            class ContainerType = std::vector<TokenType>        ,
            class RegexType     = std::basic_regex<_CharT>      ,
            class IteratorType>
        ContainerType split_re_impl(IteratorType begin, IteratorType end, const RegexType &re)
        {
            ContainerType result;

            std::match_results<const _CharT*> match;

            auto len = std::distance(begin, end);
            while (std::regex_search(&*begin, match, re)) {
                if (match.size() <= 1)
                    break;

                for (auto it = std::begin(match) + 1; it != std::end(match); ++it)
                    result.emplace_back(it->first, it->length());

                if (match.suffix().length() == 0)
                    break;

                std::advance(begin, len - match.suffix().length());
            }

            return result;
        }

    } // namespace detail

    /**
     * @brief Function for splitting std::string
     * @note @p str should live long enough
     * @param str input string
     * @param sep separator
     * @return std::vector of string views point to the parts of initial string
     */
    auto split_view(const std::string &str, const std::string &sep = " ")
    {
        return detail::split_impl({str.data(), str.size()}, {sep.data(), sep.size()});
    }

    /**
     * @brief Splits @p str into substrings wherever the regular expression @p re matches
     * @note @p str should live long enough
     * @return std::vector of string views point to the parts of initial string
     */
    auto split_view(const std::string &str, const std::regex &re)
    {
        return detail::split_re_impl(std::begin(str), std::end(str), re);
    }

    /**
     * @brief Function for splitting std::string
     * @param str input string
     * @param sep separator
     * @return std::vector of tokens, each of them represented as std::string
     */
    auto split(const std::string &str, const std::string &sep)
    {
        return detail::split_impl<char, std::string>({str.data(), str.size()},
                                                         {sep.data(), sep.size()});
    }

    /**
     * @brief Splits @p str into substrings wherever the regular expression @p re matches
     * @return std::vector of strings point to the parts of initial string
     */
    auto split(const std::string &str, const std::regex &re)
    {
        return detail::split_re_impl<char, std::string>(std::begin(str), std::end(str), re);
    }


    /**
     * @brief Function for splitting std::wstring
     * @note @p str should live long enough
     * @param str input string
     * @param sep separator
     * @return std::vector of wstring views point to the parts of initial string
     */
    auto split_view(const std::wstring &str, const std::wstring &sep)
    {
        return detail::split_impl<wchar_t>({str.data(), str.size()}, {sep.data(), sep.size()});
    }

    /**
     * @brief Splits @p str into substrings wherever the regular expression @p re matches
     * @note @p str should live long enough
     * @return std::vector of string views point to the parts of initial string
     */
    auto split_view(const std::wstring &str, const std::wregex &re)
    {
        return detail::split_re_impl<wchar_t>(std::begin(str), std::end(str), re);
    }

    /**
     * @brief Function for splitting std::wstring
     * @param str input string
     * @param sep separator
     * @return std::vector of tokens, each of them represented as std::wstring
     */
    auto split(const std::wstring &str, const std::wstring &sep = L" ")
    {
        return detail::split_impl<wchar_t, std::wstring>({str.data(), str.size()},
                                                             {sep.data(), sep.size()});
    }

    /**
     * @brief Splits @p str into substrings wherever the regular expression @p re matches
     * @return std::vector of strings point to the parts of initial string
     */
    auto split(const std::wstring &str, const std::wregex &re)
    {
        return detail::split_re_impl<wchar_t, std::wstring>(std::begin(str), std::end(str), re);
    }

} // namespace str_utils
