#include "result.hpp"

#include <gtest/gtest.h>

#include <type_traits>

//------------------------------------------------------------------------------

namespace {

//------------------------------------------------------------------------------

// Check that a result can be explicitly and implicitly initialised with a
// value of the exact value type.
TEST(result_test, initialise_with_value)
{
  struct dummy_error { };

  auto test = [](const bb::result<int, dummy_error>&){ };

  test(bb::result<int, dummy_error>{1});
  test(1);
}

// Check that a result can be explicitly and implicitly initialised with a
// value of a type which is convertible to the value type.
TEST(result_test, initialise_with_converted_value)
{
  struct dummy_error { };
  struct bar { };
  struct foo { foo(const bar&) { } };

  auto test = [](const bb::result<foo, dummy_error>&){ };

  test(bb::result<foo, dummy_error>{bar{}});
  test(bar{});
}

// Check that a result can be explicitly and implicitly initialised with an
// error of the exact error type.
TEST(result_test, initialise_with_error)
{
  struct dummy_error { };

  auto test = [](const bb::result<int, dummy_error>&){ };

  test(bb::result<int, dummy_error>{dummy_error{}});
  test(dummy_error{});
}

// Check that a result can be explicitly and implicity initialised with an
// error of a type which is convertible to the error type.
TEST(result_test, initialise_with_converted_error)
{
  struct bar { };
  struct foo { foo(const bar&) { } };

  auto test = [](const bb::result<int, foo>&){ };

  test(bb::result<int, foo>{bar{}});
  test(bar{});
}

// Check that an existing result can be assigned a value of the exact value
// type.

// Check that an existing result can be assigned an error of the exact error
// type.

// Check that an existing result containing a value can be assigned an error,
// and that the value is correctly destroyed.

// Check that an existing result containing an error can be assigned a value,
// and that the error is correctly destroyed.

//------------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

int main(int argc, char* argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
