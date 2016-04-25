#ifndef PROMPT_HPP
#define PROMPT_HPP

#include <iostream>
#include <string>

std::string getstr(std::istream& in = std::cin) {
  std::string input;
  std::getline(in, input);
  return input;
}

template <typename T>
std::string prompt(T strs, std::istream& in = std::cin);

template <>
std::string prompt(std::string str, std::istream& in) {
  std::cout << str << '\n';
  return getstr(in);
}

template <>
std::string prompt(const char str[], std::istream& in) {
  std::cout << str << '\n';
  return getstr(in);
}

template <>
std::string prompt(std::vector<std::string> strs, std::istream& in) {
  for (auto it : strs) {
    std::cout << it << '\n';
  }
  return getstr(in);
}

#endif //PROMPT_HPP