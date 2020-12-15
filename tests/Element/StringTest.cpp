#include <gtest/gtest.h>
#include <Maze/Maze.hpp>

class ElementStringTest : public ::testing::Test {
protected:
    Maze::Element el_empty;
    Maze::Element el_val;

    void SetUp() override {
        el_empty = Maze::Element("");
        el_val = Maze::Element("val");
    }
};

TEST_F(ElementStringTest, Construct_FromInt) {
    ASSERT_TRUE(el_empty.is_string());
    ASSERT_TRUE(el_val.is_string());
    ASSERT_EQ(el_empty.get_string(), "");
    ASSERT_EQ(el_val.get_string(), "val");
}

TEST_F(ElementStringTest, Getter_Short) {
    ASSERT_EQ(el_empty.s(), "");
    ASSERT_EQ(el_val.s(), "val");
}

TEST_F(ElementStringTest, Getter_Cast) {
    ASSERT_EQ((std::string)el_empty, "");
    ASSERT_EQ((std::string)el_val, "val");
    ASSERT_EQ((const std::string)el_empty, "");
    ASSERT_EQ((const std::string)el_val, "val");
    ASSERT_EQ((const std::string&)el_empty, "");
    ASSERT_EQ((const std::string&)el_val, "val");
}

TEST_F(ElementStringTest, Getter_FallbackValues_NotAffectingActual) {
    ASSERT_EQ(el_empty.get_string("default"), "");
    ASSERT_EQ(el_val.get_string("default"), "val");
}

TEST_F(ElementStringTest, Getter_FallbackValues_NonStringElement) {
    Maze::Element el;

    ASSERT_EQ(el.get_string(), "");
    ASSERT_EQ(el.get_string("val1"), "val1");

    el.set_double(1234.5678);
    ASSERT_EQ(el.get_string("val2"), "val2");

    el.set_bool(true);
    ASSERT_EQ(el.get_string("val3"), "val3");
}

TEST_F(ElementStringTest, Getter_ConstRef) {
    ASSERT_EQ(el_empty.get_string_const_ref(""), "");
    ASSERT_EQ(el_val.get_string_const_ref(""), "val");
}

TEST_F(ElementStringTest, Getter_Ref) {
    ASSERT_EQ(el_empty.get_string_ref(), "");
    ASSERT_EQ(el_val.get_string_ref(), "val");
}

TEST_F(ElementStringTest, Getter_Ref_ThrowsIfNotString) {
    Maze::Element el_int(42);

    ASSERT_THROW(el_int.get_string_ref(), Maze::MazeException);
}

TEST_F(ElementStringTest, Setter_Short) {
    Maze::Element el;

    el.s("val1");
    ASSERT_TRUE(el.is_string());
    ASSERT_EQ(el.get_string(), "val1");
}

TEST_F(ElementStringTest, Setter_OperatorEq) {
    Maze::Element el;

    el = "val1";
    ASSERT_TRUE(el.is_string());
    ASSERT_EQ(el.get_string(), "val1");

    el = std::string("val2");
    ASSERT_TRUE(el.is_string());
    ASSERT_EQ(el.get_string(), "val2");
}

TEST_F(ElementStringTest, Setter) {
    Maze::Element el;

    el.set_string("val1");
    ASSERT_TRUE(el.is_string());
    ASSERT_EQ(el.get_string(), "val1");
}

TEST_F(ElementStringTest, Setter_ChangeType) {
    Maze::Element el(42);

    el.set_string("val1");
    ASSERT_TRUE(el.is_string());
    ASSERT_EQ(el.get_string(), "val1");
}

TEST_F(ElementStringTest, IsStringType) {
    Maze::Element el;

    el.set_string("val1");
    ASSERT_FALSE(el.is_null());
    ASSERT_TRUE(el.is_string());
    ASSERT_TRUE(el.is(Maze::Type::String));

    el = Maze::Element("val2");
    ASSERT_FALSE(el.is_null());
    ASSERT_TRUE(el.is_string());
    ASSERT_TRUE(el.is(Maze::Type::String));

    el = Maze::Element(std::string("val3"));
    ASSERT_FALSE(el.is_null());
    ASSERT_TRUE(el.is_string());
    ASSERT_TRUE(el.is(Maze::Type::String));
}

TEST_F(ElementStringTest, Apply_NullToString) {
    Maze::Element el(Maze::Type::Null);

    el.apply(Maze::Element("val1"));
    ASSERT_TRUE(el.is_string());
    ASSERT_EQ(el.get_string(), "val1");
}

TEST_F(ElementStringTest, Apply_ChangeType) {
    Maze::Element el(42);

    el.apply(Maze::Element("val1"));
    ASSERT_TRUE(el.is_string());
    ASSERT_EQ(el.get_string(), "val1");
}

TEST_F(ElementStringTest, ToJson) {
    ASSERT_EQ(el_empty.to_json(), "\"\"");
    ASSERT_EQ(el_val.to_json(), "\"val\"");
}

TEST_F(ElementStringTest, FromJson) {
    Maze::Element el;

    el = Maze::Element::from_json("\"val\"");
    ASSERT_TRUE(el.is_string());
    ASSERT_EQ(el.get_string(), "val");
}
