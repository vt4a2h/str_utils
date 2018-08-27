#pragma once

#include <string_view>
#include <string>
#include <vector>
#include <algorithm>

namespace str_utils {

    namespace detail {

        template <
            class _CharT        = char                          ,
            class TokenType     = std::basic_string_view<_CharT>,
            class ContainerType = std::vector<TokenType>        ,
            class InputType     = std::basic_string_view<_CharT>>
        ContainerType split_str_impl(InputType view, InputType sep)
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

    } // namespace detail


    /**
     * @brief Function for splitting std::string
     * @note @p str should live long enough
     * @param str input string
     * @param sep separator
     * @return vector of string views point to the parts of initial string
     */
    auto split_str_ref(const std::string &str, const std::string &sep = " ")
    {
        return detail::split_str_impl({str.data(), str.size()}, {sep.data(), sep.size()});
    }

    /**
     * @brief Function for splitting std::string
     * @param str input string
     * @param sep separator
     * @return vector of tokens, each of them represented as std::string
     */
    auto split_str(const std::string &str, const std::string &sep = " ")
    {
        return detail::split_str_impl<char, std::string>({str.data(), str.size()},
                                                         {sep.data(), sep.size()});
    }

    /**
     * @brief Function for splitting std::wstring
     * @note @p str should live long enough
     * @param str input string
     * @param sep separator
     * @return vector of wstring views point to the parts of initial string
     */
    auto split_wstr_ref(const std::wstring &str, const std::wstring &sep = L" ")
    {
        return detail::split_str_impl<wchar_t>({str.data(), str.size()}, {sep.data(), sep.size()});
    }

    /**
     * @brief Function for splitting std::wstring
     * @param str input string
     * @param sep separator
     * @return vector of tokens, each of them represented as std::wstring
     */
    auto split_wstr(const std::wstring &str, const std::wstring &sep = L" ")
    {
        return detail::split_str_impl<wchar_t, std::wstring>({str.data(), str.size()},
                                                             {sep.data(), sep.size()});
    }

} // namespace str
