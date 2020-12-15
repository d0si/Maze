#include <gtest/gtest.h>
#include <Maze/Maze.hpp>

#define ACTUAL_PI 3.000014
#define ACTUAL_G 9.9

class ElementDoubleTest : public ::testing::Test {
protected:
    Maze::Element el_zero;
    Maze::Element el_one;
    Maze::Element el_i;
    Maze::Element el_pi;
    Maze::Element el_g;

    void SetUp() override {
        el_zero = Maze::Element(0.0);
        el_one = Maze::Element(1.0);
        el_i = Maze::Element(-1.0);
        el_pi = Maze::Element(ACTUAL_PI);
        el_g = Maze::Element(ACTUAL_G);
    }
};

TEST_F(ElementDoubleTest, Construct_FromDouble) {
    ASSERT_TRUE(el_zero.is_double());
    ASSERT_TRUE(el_one.is_double());
    ASSERT_TRUE(el_i.is_double());
    ASSERT_TRUE(el_pi.is_double());
    ASSERT_TRUE(el_g.is_double());
    ASSERT_EQ(el_zero.get_double(), 0.0);
    ASSERT_EQ(el_one.get_double(), 1.0);
    ASSERT_EQ(el_i.get_double(), -1.0);
    ASSERT_EQ(el_pi.get_double(), 3.000014);
    ASSERT_EQ(el_g.get_double(), 9.9);
}

TEST_F(ElementDoubleTest, Getter_Short) {
    ASSERT_EQ(el_zero.d(), 0.0);
    ASSERT_EQ(el_one.d(), 1.0);
    ASSERT_EQ(el_i.d(), -1.0);
    ASSERT_EQ(el_pi.d(), 3.000014);
    ASSERT_EQ(el_g.d(), 9.9);
}

TEST_F(ElementDoubleTest, Getter_Cast) {
    ASSERT_EQ((double)el_zero, 0.0);
    ASSERT_EQ((double)el_one, 1.0);
    ASSERT_EQ((double)el_i, -1.0);
    ASSERT_EQ((double)el_pi, 3.000014);
    ASSERT_EQ((double)el_g, 9.9);
}

TEST_F(ElementDoubleTest, Getter_FallbackValues_NotAffectingActual) {
    ASSERT_EQ(el_zero.get_double(55.1), 0.0);
    ASSERT_EQ(el_one.get_double(55.1), 1.0);
    ASSERT_EQ(el_i.get_double(55.1), -1.0);
    ASSERT_EQ(el_pi.get_double(55.1), 3.000014);
    ASSERT_EQ(el_g.get_double(55.1), 9.9);
}

TEST_F(ElementDoubleTest, Getter_FallbackValues_NonDoubleElement) {
    Maze::Element el;

    ASSERT_EQ(el.get_double(), 0);
    ASSERT_EQ(el.get_double(55.1), 55.1);

    el.set_int(1234);
    ASSERT_EQ(el.get_double(55.1), 55.1);

    el.set_string("abcd");
    ASSERT_EQ(el.get_double(55.1), 55.1);
}

TEST_F(ElementDoubleTest, Getter_Ref) {
    ASSERT_EQ(el_zero.get_double_ref(), 0.0);
    ASSERT_EQ(el_one.get_double_ref(), 1.0);
    ASSERT_EQ(el_i.get_double_ref(), -1.0);
    ASSERT_EQ(el_pi.get_double_ref(), 3.000014);
    ASSERT_EQ(el_g.get_double_ref(), 9.9);
}

TEST_F(ElementDoubleTest, Getter_Ref_ThrowsIfNotDouble) {
    Maze::Element el_string("val");

    ASSERT_THROW(el_string.get_double_ref(), Maze::MazeException);
}

TEST_F(ElementDoubleTest, Setter_Short) {
    Maze::Element el;

    el.d(42.1);
    ASSERT_TRUE(el.is_double());
    ASSERT_EQ(el.get_double(), 42.1);
}

TEST_F(ElementDoubleTest, Setter_OperatorEq) {
    Maze::Element el;

    el = 42.1;
    ASSERT_TRUE(el.is_double());
    ASSERT_EQ(el.get_double(), 42.1);
}

TEST_F(ElementDoubleTest, Setter) {
    Maze::Element el;

    el.set_double(42.1);
    ASSERT_TRUE(el.is_double());
    ASSERT_EQ(el.get_double(), 42.1);
}

TEST_F(ElementDoubleTest, Setter_ChangeType) {
    Maze::Element el("val");

    el.set_double(42.1);
    ASSERT_TRUE(el.is_double());
    ASSERT_EQ(el.get_double(), 42.1);
}

TEST_F(ElementDoubleTest, IsDoubleType) {
    Maze::Element el;

    el.set_double(42.1);
    ASSERT_FALSE(el.is_null());
    ASSERT_TRUE(el.is_double());
    ASSERT_TRUE(el.is(Maze::Type::Double));

    el = Maze::Element(42.1);
    ASSERT_FALSE(el.is_null());
    ASSERT_TRUE(el.is_double());
    ASSERT_TRUE(el.is(Maze::Type::Double));
}

TEST_F(ElementDoubleTest, Apply_NullToDouble) {
    Maze::Element el(Maze::Type::Null);

    el.apply(Maze::Element(42));
    ASSERT_TRUE(el.is_int());
    ASSERT_EQ(el.get_int(), 42);
}

TEST_F(ElementDoubleTest, Apply_ChangeType) {
    Maze::Element el("val");

    el.apply(Maze::Element(42.1));
    ASSERT_TRUE(el.is_double());
    ASSERT_EQ(el.get_double(), 42.1);
}

TEST_F(ElementDoubleTest, ToJson) {
    ASSERT_EQ(el_pi.to_json(), "3.000014");
    ASSERT_EQ(el_g.to_json(), "9.9");
}

TEST_F(ElementDoubleTest, FromJson) {
    Maze::Element el;

    el = Maze::Element::from_json("42.1");
    ASSERT_TRUE(el.is_double());
    ASSERT_EQ(el.get_double(), 42.1);
}
