#include <gtest/gtest.h>
#include <Maze/Maze.hpp>

namespace Element {
    class Bool : public ::testing::Test {

    };

    TEST_F(Bool, Getter_FallbackValues) {
        Maze::Element el;

        el.set_bool(false);
        ASSERT_FALSE(el.get_bool(false));
        ASSERT_FALSE(el.get_bool(true));

        el.set_bool(true);
        ASSERT_TRUE(el.get_bool(false));
        ASSERT_TRUE(el.get_bool(true));
    }

    TEST_F(Bool, Getter_FallbackValues_NonBoolElement) {
        Maze::Element el;

        ASSERT_FALSE(el.get_bool(false));
        ASSERT_TRUE(el.get_bool(true));

        el.set_as_null();
        ASSERT_FALSE(el.get_bool(false));
        ASSERT_TRUE(el.get_bool(true));

        el.set_int(1234);
        ASSERT_FALSE(el.get_bool(false));
        ASSERT_TRUE(el.get_bool(true));

        el.set_string("abcd");
        ASSERT_FALSE(el.get_bool(false));
        ASSERT_TRUE(el.get_bool(true));
    }
}
