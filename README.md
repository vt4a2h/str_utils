# Convenient helpers for standard C++ string classes

## Split
Basic splitting functionality can be used like this:
```cpp
std::string input = "Lorem inpsum";
auto tokens = str_utils::split_view(input, " "); // ==> ["Lorem", "inpsum"]
```
Please note, that the result vector of tokens contains `string_view` objects, hence input string should live long enough. See more examples in the test directory.

If you need string objects rather than string views, you may use the following approach:
```cpp
auto tokens = str_utils::split("Lorem inpsum", " "); // ==> ["Lorem", "inpsum"]
```

Splitting with regular expression is also possible now:
```cpp
std::string in = "Lorem inpsum";
std::regex re{"([a-zA-Z]+)"};

auto tokens = str_utils::split_view(in, re); // ==> ["Lorem", "inpsum"]
```
Suffix `_view` means the same that in the example above: the result vector contains `string_view` objects. If you need a vector of copies, try using a function without `_view` suffix.

## Join
You can concatenate strings (or string views) stored in a container of any type (which supports at least forward iterators):
```cpp
std::vector<std::string> in{"Lorem", "inpsum"};

auto result = str_utils::join(in, std::string(" ")); ==> "Lorem inpsum"
```
See more examples in the test directory.

Implemented:
- [X] Splitting `std::basic_string<_CharT>` into substrings whenever a separator occurs
- [X] Splitting string using regular expressions
- [X] Joining strings
