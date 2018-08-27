# Convenient helpers for standard C++ string classes

Only splitting functionality is added now. You can use it like this:
```cpp
std::string input = "Lorem inpsum";
auto tokens = str_utils::split_str_ref(input, " ");
```
Please note, that the result vector of tokens contains `string_view` objects, hence input string should live long enough. See more examples in the test directory.

If you need string objects rather than string views, you may use the following approach:
```cpp
auto tokens = str_utils::split_str("Lorem inpsum", " ");
```

Implemented:
- [X] Splitting `std::basic_string<_CharT>` into substrings whenever a separator occurs

TODO:
- [ ] Splitting string using regular expressions
- [ ] Joining strings
