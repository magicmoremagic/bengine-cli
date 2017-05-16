#pragma once
#ifndef BE_CLI_NUMERIC_PARAM_HPP_
#define BE_CLI_NUMERIC_PARAM_HPP_

#include "param.hpp"
#include <be/util/parse_numeric_string.hpp>

namespace be::cli {

///////////////////////////////////////////////////////////////////////////////
template <typename T>
auto numeric_param(std::initializer_list<S> short_options,
                   std::initializer_list<S> long_options,
                   S value_name, T& dest) {
   auto func = [=, &dest](const S& str) {
      dest = util::throw_on_error(util::parse_numeric_string<T>(str));
   };
   
   ct::Cell extra;
   extra << "Default value: "
         << color::fg_cyan << dest << color::reset;

   return Param<decltype(func)>(std::move(short_options), std::move(long_options), value_name, std::move(func))
      .extra(std::move(extra));
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
auto numeric_param(std::initializer_list<S> short_options,
                   std::initializer_list<S> long_options,
                   S value_name, T& dest, T min, T max) {
   auto func = [=, &dest](const S& str) {
      dest = util::throw_on_error(util::parse_bounded_numeric_string<T>(str, min, max));
   };

   ct::Cell extra;
   extra << "Valid values: "
         << color::fg_cyan << min << color::reset << " - "
         << color::fg_cyan << max << color::reset << nl << "Default value: "
         << color::fg_cyan << dest << color::reset;

   return Param<decltype(func)>(std::move(short_options), std::move(long_options), value_name, std::move(func))
      .extra(std::move(extra));
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename F>
auto numeric_param(std::initializer_list<S> short_options,
                   std::initializer_list<S> long_options,
                   S value_name, T& dest, F func = F()) {
   auto f = [=, &dest](const S& str) {
      dest = util::throw_on_error(util::parse_numeric_string<T>(str));
      func();
   };

   ct::Cell extra;
   extra << "Default value: "
         << color::fg_cyan << dest << color::reset;

   return Param<decltype(f)>(std::move(short_options), std::move(long_options), value_name, std::move(f))
      .extra(std::move(extra));
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename F>
auto numeric_param(std::initializer_list<S> short_options,
                   std::initializer_list<S> long_options,
                   S value_name, T& dest, T min, T max, F func = F()) {
   auto f = [=, &dest](const S& str) {
      dest = util::throw_on_error(util::parse_bounded_numeric_string<T>(str, min, max));
      func();
   };

   ct::Cell extra;
   extra << "Valid values: "
         << color::fg_cyan << min << color::reset << " - "
         << color::fg_cyan << max << color::reset << nl << "Default value: "
         << color::fg_cyan << dest << color::reset;

   return Param<decltype(f)>(std::move(short_options), std::move(long_options), value_name, std::move(f))
      .extra(std::move(extra));
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename F>
auto numeric_param(std::initializer_list<S> short_options,
                   std::initializer_list<S> long_options,
                   S value_name, F func = F()) {
   auto f = [=](const S& str) {
      func(util::throw_on_error(util::parse_numeric_string<T>(str)));
   };

   return Param<decltype(f)>(std::move(short_options), std::move(long_options), value_name, std::move(f));
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename F>
auto numeric_param(std::initializer_list<S> short_options,
                   std::initializer_list<S> long_options,
                   S value_name, T min, T max, F func = F()) {
   auto f = [=](const S& str) {
      func(util::throw_on_error(util::parse_bounded_numeric_string<T>(str, min, max)));
   };

   ct::Cell extra;
   extra << "Valid values: "
         << color::fg_cyan << min << color::reset << " - "
         << color::fg_cyan << max << color::reset;

   return Param<decltype(f)>(std::move(short_options), std::move(long_options), value_name, std::move(f))
      .extra(std::move(extra));
}


} // be::cli

#endif