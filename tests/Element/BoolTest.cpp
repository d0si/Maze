#include <gtest/gtest.h>
#include <Maze/Maze.hpp>

class ElementBoolTest : public ::testing::Test {};

TEST_F(ElementBoolTest, Construct_FromBool) {
    Maze::Element el_false(false);
    Maze::Element el_true(true);

    ASSERT_FALSE(el_false.get_bool());
    ASSERT_TRUE(el_true.get_bool());
}

TEST_F(ElementBoolTest, Getter_Short) {
    Maze::Element el;

    el.set_bool(false);
    ASSERT_FALSE(el.b());

    el.set_bool(true);
    ASSERT_TRUE(el.b());
}

TEST_F(ElementBoolTest, Getter_Cast) {
    Maze::Element el;

    el.set_bool(false);
    ASSERT_FALSE((bool)el);

    el.set_bool(true);
    ASSERT_TRUE((bool)el);
}

TEST_F(ElementBoolTest, Getter_FallbackValues_NotAffectingActual) {
    Maze::Element el;

    el.set_bool(false);
    ASSERT_FALSE(el.get_bool(false));
    ASSERT_FALSE(el.get_bool(true));

    el.set_bool(true);
    ASSERT_TRUE(el.get_bool(false));
    ASSERT_TRUE(el.get_bool(true));
}

TEST_F(ElementBoolTest, Getter_FallbackValues_NonBoolElement) {
    Maze::Element el;

    ASSERT_FALSE(el.get_bool());
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

TEST_F(ElementBoolTest, Getter_Ref) {
    Maze::Element el_false(false);
    Maze::Element el_true(true);

    ASSERT_FALSE(el_false.get_bool_ref());
    ASSERT_TRUE(el_true.get_bool_ref());
}

TEST_F(ElementBoolTest, Getter_Ref_ThrowsIfNotBool) {
    Maze::Element el_string("val");

    ASSERT_THROW(el_string.get_bool_ref(), Maze::MazeException);
}

TEST_F(ElementBoolTest, Setter_Short) {
    Maze::Element el;

    el.b(true);
    ASSERT_TRUE(el.is_bool());
    ASSERT_TRUE(el.get_bool());

    el.b(false);
    ASSERT_TRUE(el.is_bool());
    ASSERT_FALSE(el.get_bool());
}

TEST_F(ElementBoolTest, Setter_OperatorEq) {
    Maze::Element el;

    el = true;
    ASSERT_TRUE(el.is_bool());
    ASSERT_TRUE(el.get_bool());

    el = false;
    ASSERT_TRUE(el.is_bool());
    ASSERT_FALSE(el.get_bool());
}

TEST_F(ElementBoolTest, Setter) {
    Maze::Element el;

    el.set_bool(true);
    ASSERT_TRUE(el.is_bool());
    ASSERT_TRUE(el.get_bool());

    el.set_bool(false);
    ASSERT_TRUE(el.is_bool());
    ASSERT_FALSE(el.get_bool());
}

TEST_F(ElementBoolTest, Setter_ChangeType) {
    Maze::Element el("val");

    el.set_bool(true);
    ASSERT_TRUE(el.is_bool());
    ASSERT_TRUE(el.get_bool());

    el = Maze::Element("val");
    el.set_bool(false);
    ASSERT_TRUE(el.is_bool());
    ASSERT_FALSE(el.get_bool());
}

TEST_F(ElementBoolTest, IsBoolType) {
    Maze::Element el;

    el.set_bool(false);
    ASSERT_FALSE(el.is_null());
    ASSERT_TRUE(el.is_bool());
    ASSERT_TRUE(el.is(Maze::Type::Bool));

    el = Maze::Element();
    el.set_bool(true);
    ASSERT_FALSE(el.is_null());
    ASSERT_TRUE(el.is_bool());
    ASSERT_TRUE(el.is(Maze::Type::Bool));

    el = Maze::Element(true);
    ASSERT_FALSE(el.is_null());
    ASSERT_TRUE(el.is_bool());
    ASSERT_TRUE(el.is(Maze::Type::Bool));

    el = Maze::Element(false);
    ASSERT_FALSE(el.is_null());
    ASSERT_TRUE(el.is_bool());
    ASSERT_TRUE(el.is(Maze::Type::Bool));
}

TEST_F(ElementBoolTest, Apply_NullToBool) {
    Maze::Element el(Maze::Type::Null);

    el.apply(Maze::Element(true));
    ASSERT_TRUE(el.get_bool());
    ASSERT_TRUE(el.is_bool());

    el = Maze::Element(Maze::Type::Null);
    el.apply(Maze::Element(false));
    ASSERT_FALSE(el.get_bool());
    ASSERT_TRUE(el.is_bool());
}

TEST_F(ElementBoolTest, Apply_ChangeType) {
    Maze::Element el("val");

    el.apply(Maze::Element(true));
    ASSERT_TRUE(el.get_bool());
    ASSERT_TRUE(el.is_bool());

    el = Maze::Element("val");
    el.apply(Maze::Element(false));
    ASSERT_FALSE(el.get_bool());
    ASSERT_TRUE(el.is_bool());
}

TEST_F(ElementBoolTest, ToJson) {
    Maze::Element el;

    el.set_bool(true);
    ASSERT_EQ(el.to_json(), "true");

    el.set_bool(false);
    ASSERT_EQ(el.to_json(), "false");
}

TEST_F(ElementBoolTest, FromJson) {
    Maze::Element el;

    el = Maze::Element::from_json("true");
    ASSERT_TRUE(el.is_bool());
    ASSERT_TRUE(el.get_bool());

    el = Maze::Element::from_json("false");
    ASSERT_TRUE(el.is_bool());
    ASSERT_FALSE(el.get_bool());
}
