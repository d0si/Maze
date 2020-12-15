#include <gtest/gtest.h>
#include <Maze/Maze.hpp>

class ElementNullTest : public ::testing::Test {
protected:
    Maze::Element null_el;
    Maze::Element str_el;
    Maze::Element obj_el;

    void SetUp() override {
        null_el = Maze::Element(Maze::Type::Null);
        str_el = Maze::Element("val");
        obj_el = Maze::Element(Maze::Type::Object);
    }
};

TEST_F(ElementNullTest, ConstructNull) {
    Maze::Element el;
    ASSERT_TRUE(el.is_null());

    el = Maze::Element(Maze::Type::Null);
    ASSERT_TRUE(el.is_null());
}

TEST_F(ElementNullTest, SetType) {
    ASSERT_TRUE(null_el.is_null());
    ASSERT_FALSE(str_el.is_null());
    ASSERT_FALSE(obj_el.is_null());

    null_el.set_type(Maze::Type::Null);
    str_el.set_type(Maze::Type::Null);
    obj_el.set_type(Maze::Type::Null);

    ASSERT_TRUE(null_el.is_null());
    ASSERT_TRUE(str_el.is_null());
    ASSERT_TRUE(obj_el.is_null());
}

TEST_F(ElementNullTest, SetAsNull) {
    ASSERT_TRUE(null_el.is_null());
    ASSERT_FALSE(str_el.is_null());
    ASSERT_FALSE(obj_el.is_null());

    null_el.set_as_null();
    str_el.set_as_null();
    obj_el.set_as_null();

    ASSERT_TRUE(null_el.is_null());
    ASSERT_TRUE(str_el.is_null());
    ASSERT_TRUE(obj_el.is_null());
}

TEST_F(ElementNullTest, IsCorrectType) {
    ASSERT_TRUE(null_el.is_null());
    ASSERT_TRUE(null_el.is(Maze::Type::Null));
}

TEST_F(ElementNullTest, ApplyNull) {
    null_el.apply(Maze::Element());
    str_el.apply(Maze::Element());
    obj_el.apply(Maze::Element());

    ASSERT_TRUE(null_el.is_null());
    ASSERT_TRUE(str_el.is_null());
    ASSERT_TRUE(obj_el.is_null());
}

TEST_F(ElementNullTest, ApplyItself) {
    null_el.apply(null_el);
    ASSERT_TRUE(null_el.is_null());
}

TEST_F(ElementNullTest, ToJson) {
    ASSERT_EQ(null_el.to_json(), "null");
}

TEST_F(ElementNullTest, FromJson) {
    Maze::Element el = Maze::Element::from_json("null");
    ASSERT_TRUE(el.is_null());
}

TEST_F(ElementNullTest, GetNullElement) {
    const Maze::Element& el_ref = Maze::Element::get_null_element();
    ASSERT_TRUE(el_ref.is_null());

    Maze::Element el = Maze::Element::get_null_element();
    ASSERT_TRUE(el.is_null());
}
