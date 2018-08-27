#pragma once

#include <string_view>
#include <string>
#include <vector>
#include <algorithm>

namespace str_utils {

    namespace detail {

        template <class _CharT = char>
        std::vector<std::basic_string_view<_CharT>> split_str_impl(
            std::basic_string_view<_CharT> view, std::basic_string_view<_CharT> sep)
        {
            if (view.empty())
                return {};

            if (sep.empty() || sep.size() >= view.size())
                return {{view}};

            std::vector<std::basic_string_view<_CharT>> result;

            auto first = std::begin(view);
            auto last = std::end(view);

            auto delimFirst = std::begin(sep);
            auto delimLast = std::end(sep);
            auto delimLen = std::distance(std::begin(sep), std::end(sep));

            auto delimCurrent = std::begin(view);

            while (delimCurrent != last && first != last) {
                delimCurrent = std::search(first, last, delimFirst, delimLast);

                auto len = std::distance(first, delimCurrent);
                if (len != 0)
                    result.emplace_back(&*first, len);

                std::advance(first, delimLen + len);
            }

            return result;
        }

    } // namespace detail


    auto split_str(const std::string &str, const std::string &sep = " ")
    {
        return detail::split_str_impl<char>({str.data(), str.size()}, sep);
    }

    auto split_wstr(const std::wstring &str, const std::wstring &sep = L" ")
    {
        return detail::split_str_impl<wchar_t>({str.data(), str.size()}, sep);
    }

} // namespace str
