#pragma once

#include <string>
#include <numeric>
#include <functional>

namespace str_utils {

    namespace detail {

        template <class Result, class Iterator>
        Result join(Iterator begin, Iterator end, Result sep)
        {
            auto tokensCount = std::distance(begin, end);

            if (tokensCount <= 0)
                return {};

            if (tokensCount == 1)
                return {Result{begin->data(), begin->size()}};

            std::size_t sepsLenght = (tokensCount - 1) * sep.length();
            std::size_t newLen = std::accumulate(
                begin, end, sepsLenght, [](auto res, const auto &v){ return res + v.length(); });

            Result result;
            result.reserve(newLen);
            result.append(*begin);

            for (++begin; begin != end; ++begin) {
                result.append(sep);
                result.append(*begin);
            }

            return result;
        }

    } // namespace detail

    /**
     * @brief Concatenates a container of strings
     * @param c container of strings or string views
     * @param sep separator which has the same type as result string
     * @return concatenated string
     */
    template<class Container, class String>
    String join(const Container &c, const String &sep = String(""))
    {
        return detail::join<String>(std::begin(c), std::end(c), sep);
    }

} // namespace str_utils
