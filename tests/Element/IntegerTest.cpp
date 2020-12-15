#include <gtest/gtest.h>
#include <Maze/Maze.hpp>

#define ACTUAL_PI 3
#define ACTUAL_G 10

class ElementIntegerTest : public ::testing::Test {
protected:
    Maze::Element el_zero;
    Maze::Element el_one;
    Maze::Element el_i;
    Maze::Element el_pi;
    Maze::Element el_g;

    void SetUp() override {
        el_zero = Maze::Element(0);
        el_one = Maze::Element(1);
        el_i = Maze::Element(-1);
        el_pi = Maze::Element(ACTUAL_PI);
        el_g = Maze::Element(ACTUAL_G);
    }
};

TEST_F(ElementIntegerTest, Construct_FromInt) {
    ASSERT_TRUE(el_zero.is_int());
    ASSERT_TRUE(el_one.is_int());
    ASSERT_TRUE(el_i.is_int());
    ASSERT_TRUE(el_pi.is_int());
    ASSERT_TRUE(el_g.is_int());
    ASSERT_EQ(el_zero.get_int(), 0);
    ASSERT_EQ(el_one.get_int(), 1);
    ASSERT_EQ(el_i.get_int(), -1);
    ASSERT_EQ(el_pi.get_int(), 3);
    ASSERT_EQ(el_g.get_int(), 10);
}

TEST_F(ElementIntegerTest, Getter_Short) {
    ASSERT_EQ(el_zero.i(), 0);
    ASSERT_EQ(el_one.i(), 1);
    ASSERT_EQ(el_i.i(), -1);
    ASSERT_EQ(el_pi.i(), 3);
    ASSERT_EQ(el_g.i(), 10);
}

TEST_F(ElementIntegerTest, Getter_Cast) {
    ASSERT_EQ((int)el_zero, 0);
    ASSERT_EQ((int)el_one, 1);
    ASSERT_EQ((int)el_i, -1);
    ASSERT_EQ((int)el_pi, 3);
    ASSERT_EQ((int)el_g, 10);
}

TEST_F(ElementIntegerTest, Getter_FallbackValues_NotAffectingActual) {
    ASSERT_EQ(el_zero.get_int(55), 0);
    ASSERT_EQ(el_one.get_int(55), 1);
    ASSERT_EQ(el_i.get_int(55), -1);
    ASSERT_EQ(el_pi.get_int(55), 3);
    ASSERT_EQ(el_g.get_int(55), 10);
}

TEST_F(ElementIntegerTest, Getter_FallbackValues_NonIntElement) {
    Maze::Element el;

    ASSERT_EQ(el.get_int(), 0);
    ASSERT_EQ(el.get_int(55), 55);

    el.set_double(1234.5678);
    ASSERT_EQ(el.get_int(55), 55);

    el.set_string("abcd");
    ASSERT_EQ(el.get_int(55), 55);
}

TEST_F(ElementIntegerTest, Getter_Ref) {
    ASSERT_EQ(el_zero.get_int_ref(), 0);
    ASSERT_EQ(el_one.get_int_ref(), 1);
    ASSERT_EQ(el_i.get_int_ref(), -1);
    ASSERT_EQ(el_pi.get_int_ref(), 3);
    ASSERT_EQ(el_g.get_int_ref(), 10);
}

TEST_F(ElementIntegerTest, Getter_Ref_ThrowsIfNotInt) {
    Maze::Element el_string("val");

    ASSERT_THROW(el_string.get_int_ref(), Maze::MazeException);
}

TEST_F(ElementIntegerTest, Setter_Short) {
    Maze::Element el;

    el.i(42);
    ASSERT_TRUE(el.is_int());
    ASSERT_EQ(el.get_int(), 42);
}

TEST_F(ElementIntegerTest, Setter_OperatorEq) {
    Maze::Element el;

    el = 42;
    ASSERT_TRUE(el.is_int());
    ASSERT_EQ(el.get_int(), 42);
}

TEST_F(ElementIntegerTest, Setter) {
    Maze::Element el;

    el.set_int(42);
    ASSERT_TRUE(el.is_int());
    ASSERT_EQ(el.get_int(), 42);
}

TEST_F(ElementIntegerTest, Setter_ChangeType) {
    Maze::Element el("val");

    el.set_int(42);
    ASSERT_TRUE(el.is_int());
    ASSERT_EQ(el.get_int(), 42);
}

TEST_F(ElementIntegerTest, IsIntType) {
    Maze::Element el;

    el.set_int(42);
    ASSERT_FALSE(el.is_null());
    ASSERT_TRUE(el.is_int());
    ASSERT_TRUE(el.is(Maze::Type::Int));

    el = Maze::Element(42);
    ASSERT_FALSE(el.is_null());
    ASSERT_TRUE(el.is_int());
    ASSERT_TRUE(el.is(Maze::Type::Int));
}

TEST_F(ElementIntegerTest, Apply_NullToInt) {
    Maze::Element el(Maze::Type::Null);

    el.apply(Maze::Element(42));
    ASSERT_TRUE(el.is_int());
    ASSERT_EQ(el.get_int(), 42);
}

TEST_F(ElementIntegerTest, Apply_ChangeType) {
    Maze::Element el("val");

    el.apply(Maze::Element(42));
    ASSERT_TRUE(el.is_int());
    ASSERT_EQ(el.get_int(), 42);
}

TEST_F(ElementIntegerTest, ToJson) {
    ASSERT_EQ(el_pi.to_json(), "3");
    ASSERT_EQ(el_g.to_json(), "10");
}

TEST_F(ElementIntegerTest, FromJson) {
    Maze::Element el;

    el = Maze::Element::from_json("42");
    ASSERT_TRUE(el.is_int());
    ASSERT_EQ(el.get_int(), 42);
}
