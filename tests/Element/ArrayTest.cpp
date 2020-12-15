#include <gtest/gtest.h>
#include <Maze/Maze.hpp>

class ElementArrayTest : public ::testing::Test {
protected:
    Maze::Element arr_empty;
    Maze::Element arr_1;
    Maze::Element arr_2;

    void SetUp() override {
        arr_empty = Maze::Element(Maze::Type::Array);

        arr_1 = Maze::Element(Maze::Type::Array);
        arr_1.push_back("val1");
        arr_1.push_back( 42);
        arr_1.push_back(true);

        arr_2 = Maze::Element(Maze::Type::Array);
        arr_2 << ("obj1", Maze::Element(Maze::Type::Object))
            << ("arr1", Maze::Element(Maze::Type::Array))
            << ("str1", "test_string")
            << ("null1", Maze::Element::get_null_element())
            << ("int1", 54321)
            << ("double1", 9876.54321)
            << ("bool1", true);
    }
};

TEST_F(ElementArrayTest, Constructor) {
    EXPECT_TRUE(arr_empty.is_array());
    EXPECT_EQ(arr_empty.count_children(), 0);
    EXPECT_TRUE(arr_1.is_array());
    EXPECT_EQ(arr_1.count_children(), 3);
    EXPECT_TRUE(arr_2.is_array());
    EXPECT_EQ(arr_2.count_children(), 7);

    Maze::Element el({ Maze::Element("el1"), Maze::Element(23) });
    EXPECT_TRUE(el.is_array());
    EXPECT_EQ(el.count_children(), 2);

    el = Maze::Element({ 5532, "value1", false, true });
    EXPECT_TRUE(el.is_array());
    EXPECT_EQ(el.count_children(), 4);
}

TEST_F(ElementArrayTest, Construct_FromAnother) {
    Maze::Element el(arr_2);
    EXPECT_TRUE(el.is_array());
    EXPECT_EQ(el.count_children(), 7);
}

TEST_F(ElementArrayTest, Getter_Brackets) {
    EXPECT_EQ(arr_1[0].s(), "val1");
    EXPECT_EQ(arr_1[1].i(), 42);
    EXPECT_EQ(arr_1[2].b(), true);
}

TEST_F(ElementArrayTest, Getter_Brackets_OutOfBounds) {
    EXPECT_THROW(arr_1[99], Maze::MazeException);
}

TEST_F(ElementArrayTest, Getter) {
    EXPECT_EQ(arr_1.get(0).s(), "val1");
    EXPECT_EQ(arr_1.get(1).i(), 42);
    EXPECT_EQ(arr_1.get(2).b(), true);
    
    EXPECT_TRUE(arr_1.get(99).is_null());
}

TEST_F(ElementArrayTest, Getter_ConstRef) {
    EXPECT_EQ(arr_1.get_const_ref(0, 42).s(), "val1");

    EXPECT_TRUE(arr_1.get_const_ref(99, Maze::Element()).is_null());
    EXPECT_EQ(arr_1.get_const_ref(99, 42).i(), 42);
}

TEST_F(ElementArrayTest, Getter_FallbackValues) {
    EXPECT_EQ(arr_1.get(0, 42).s(), "val1");

    EXPECT_TRUE(arr_1.get(99).is_null());
    EXPECT_TRUE(arr_1.get(99, Maze::Element()).is_null());
    EXPECT_EQ(arr_1.get(99, 42).i(), 42);
}

TEST_F(ElementArrayTest, Getter_Ref) {
    EXPECT_EQ(arr_1.get_ref(0).s(), "val1");
    EXPECT_EQ(arr_1.get_ref(1).i(), 42);
    EXPECT_EQ(arr_1.get_ref(2).b(), true);
}

TEST_F(ElementArrayTest, Push_Operator) {
    Maze::Element el(Maze::Type::Array);
    el << "val1";
    el << 42 << false << true;
    EXPECT_EQ(el.count_children(), 4);
    EXPECT_TRUE(el.get(0).is_string());
    EXPECT_EQ(el.get(0).s(), "val1");
}

TEST_F(ElementArrayTest, PushBack) {
    Maze::Element el(Maze::Type::Array);
    el.push_back("val1");
    el.push_back(42).push_back(false).push_back(true);
    EXPECT_EQ(el.count_children(), 4);
    EXPECT_TRUE(el.get(0).is_string());
    EXPECT_EQ(el.get(0).s(), "val1");
}

TEST_F(ElementArrayTest, GetRef_SetToNull) {
    EXPECT_EQ(arr_1.count_children(), 3);
    EXPECT_FALSE(arr_1.get(0).is_null());

    arr_1.get_ref(0).set_as_null();

    EXPECT_EQ(arr_1.count_children(), 3);
    EXPECT_TRUE(arr_1.get(0).is_null());
}

TEST_F(ElementArrayTest, GetRef_ChangeValue) {
    EXPECT_EQ(arr_1.count_children(), 3);
    EXPECT_TRUE(arr_1.get(0).is_string());

    arr_1.get_ref(0).set_string("newvalue");

    EXPECT_EQ(arr_1.count_children(), 3);
    EXPECT_TRUE(arr_1.get(0).is_string());
    EXPECT_EQ(arr_1.get(0).s(), "newvalue");
}

TEST_F(ElementArrayTest, GetRef_ChangeType) {
    EXPECT_EQ(arr_1.count_children(), 3);
    EXPECT_TRUE(arr_1.get(0).is_string());

    arr_1.get_ref(0).set_int(99);

    EXPECT_EQ(arr_1.count_children(), 3);
    EXPECT_TRUE(arr_1.get(0).is_int());
    EXPECT_EQ(arr_1.get(0).i(), 99);
}

TEST_F(ElementArrayTest, RemoveAt) {
    EXPECT_EQ(arr_1.count_children(), 3);
    arr_1.remove_at(1);
    EXPECT_EQ(arr_1.count_children(), 2);
}

TEST_F(ElementArrayTest, Clear) {
    EXPECT_EQ(arr_1.count_children(), 3);
    EXPECT_TRUE(arr_1.has_children());

    arr_1.remove_all_children();

    EXPECT_EQ(arr_1.count_children(), 0);
    EXPECT_FALSE(arr_1.has_children());
}

TEST_F(ElementArrayTest, GetKeys) {
    EXPECT_EQ(arr_1.get_keys(), std::vector<std::string>({ "~0", "~1", "~2" }));
}

TEST_F(ElementArrayTest, IsString) {
    EXPECT_TRUE(arr_1.is_string(0));
    EXPECT_FALSE(arr_1.is_string(1));
    EXPECT_FALSE(arr_1.is_string(2));
}

TEST_F(ElementArrayTest, IsInt) {
    EXPECT_FALSE(arr_1.is_int(0));
    EXPECT_TRUE(arr_1.is_int(1));
    EXPECT_FALSE(arr_1.is_int(2));
}

TEST_F(ElementArrayTest, IsDouble) {
    arr_1.get_ref(1) = 9.9;

    EXPECT_FALSE(arr_1.is_double(0));
    EXPECT_TRUE(arr_1.is_double(1));
    EXPECT_FALSE(arr_1.is_double(2));
}

TEST_F(ElementArrayTest, IsBool) {
    EXPECT_FALSE(arr_1.is_bool(0));
    EXPECT_FALSE(arr_1.is_bool(1));
    EXPECT_TRUE(arr_1.is_bool(2));
}

TEST_F(ElementArrayTest, IsArray) {
    EXPECT_FALSE(arr_2.is_array(0));
    EXPECT_TRUE(arr_2.is_array(1));
    EXPECT_FALSE(arr_2.is_array(2));
}

TEST_F(ElementArrayTest, IsObject) {
    EXPECT_TRUE(arr_2.is_object(0));
    EXPECT_FALSE(arr_2.is_object(1));
    EXPECT_FALSE(arr_2.is_object(2));
}

TEST_F(ElementArrayTest, IsNull) {
    EXPECT_FALSE(arr_2.is_null(1));
    EXPECT_FALSE(arr_2.is_null(2));
    EXPECT_TRUE(arr_2.is_null(3));
}

TEST_F(ElementArrayTest, IsFunction) {
    arr_1 << Maze::Element([](const Maze::Element& value) {return value;});

    EXPECT_FALSE(arr_1.is_function(0));
    EXPECT_FALSE(arr_1.is_function(1));
    EXPECT_FALSE(arr_1.is_function(2));
    EXPECT_TRUE(arr_1.is_function(3));
}

TEST_F(ElementArrayTest, ApplyArray_Overrides) {
    Maze::Element changes(Maze::Type::Array);
    changes << "test" << "another value";

    EXPECT_EQ(arr_2.count_children(), 7);
    arr_2.apply(changes);
    EXPECT_EQ(arr_2.count_children(), 2);
}

TEST_F(ElementArrayTest, FromJsonString) {
    const std::string input = R"(
	[
        "aaa", 1234, false, true
    ]
)";

    Maze::Element parsed = Maze::Element::from_json(input);

    EXPECT_TRUE(parsed.count_children() == 4);
    EXPECT_TRUE(parsed.is_array());
}

TEST_F(ElementArrayTest, ToJsonString) {
    Maze::Element el(Maze::Type::Array);
    el << "val1" << 42;

    EXPECT_EQ(el.to_json(), R"([
  "val1",
  42
])");
}
