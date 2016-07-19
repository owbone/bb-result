#ifndef RESULT_HPP
#define RESULT_HPP

#include <type_traits>
#include <utility>

//------------------------------------------------------------------------------

namespace bb {

//------------------------------------------------------------------------------

template <class T, class Err>
class result
{
public:
  template <class U>
  result(U&& value)
    : result(traits<U>::tag, std::forward<U>(value))
  { }

  template <class U>
  result&
  operator=(U&& value)
  {
    return assign(traits<U>::tag, std::forward<U>(value));
  }

  template <class U>
  result&
  set_value(U&& value)
  {
    // FIXME: Check if error is set, destroy it and construct value if so.
    this->value = std::forward<U>(value);
    return *this;
  }

  template <class U>
  result&
  set_error(U&& error)
  {
    // FIXME: Check if value is set, destroy it and construct error if so.
    this->error = std::forward<U>(error);
    return *this;
  }

private:
  struct default_tag_t { };
  struct error_tag_t { };
  struct value_tag_t { };

  template <class U, class = void>
  struct traits;

  template <class U>
  struct traits<U, std::enable_if_t<std::is_convertible<U, T>::value>>
  {
    static const value_tag_t tag;
  };

  template <class U>
  struct traits<U, std::enable_if_t<std::is_convertible<U, Err>::value>>
  {
    static const error_tag_t tag;
  };

  template <class U>
  result(value_tag_t, U&& value)
    : value{std::forward<U>(value)}
  { }

  template <class U>
  result(error_tag_t, U&& error)
    : error{std::forward<U>(error)}
  { }

  template <class U>
  result&
  assign(value_tag_t, U&& value)
  {
    return set_value(std::forward<U>(value));
  }

  template <class U>
  result&
  assign(error_tag_t, U&& error)
  {
    return set_error(std::forward<U>(error));
  }

  union
  {
    T value;
    Err error;
  };
};

//------------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

#endif  // RESULT_HPP
