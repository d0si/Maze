#include <gtest/gtest.h>
#include <Maze/Object.hpp>
#include <Maze/Array.hpp>

using Maze::Object;
using Maze::Array;

class ObjectTest : public ::testing::Test {
protected:
	ObjectTest() {}
	virtual ~ObjectTest() {}

	virtual void SetUp() {}
	virtual void TearDown() {}

public:
	static Object get_demo_object();
};

TEST(ObjectTest, ConstructFromJsonString) {
	const std::string input = R"(
	{
		"config": {
			"key_1": "value_1"
		}
	}
)";

	Object parsed = Object::from_json(input);

	EXPECT_TRUE(parsed.size() == 1);
	EXPECT_TRUE(parsed[0].is_object());
	EXPECT_TRUE(parsed["config"].is_object());
}

TEST(ObjectTest, IsString) {
	Object obj = ObjectTest::get_demo_object();

	EXPECT_FALSE(obj.is_string("obj1"));
	EXPECT_FALSE(obj.is_string("arr1"));
	EXPECT_TRUE(obj.is_string("str1"));
	EXPECT_FALSE(obj.is_string("null1"));
	EXPECT_FALSE(obj.is_string("int1"));
	EXPECT_FALSE(obj.is_string("double1"));
	EXPECT_FALSE(obj.is_string("bool1"));
}

TEST(ObjectTest, IsInt) {
	Object obj = ObjectTest::get_demo_object();

	EXPECT_FALSE(obj.is_int("obj1"));
	EXPECT_FALSE(obj.is_int("arr1"));
	EXPECT_FALSE(obj.is_int("str1"));
	EXPECT_FALSE(obj.is_int("null1"));
	EXPECT_TRUE(obj.is_int("int1"));
	EXPECT_FALSE(obj.is_int("double1"));
	EXPECT_FALSE(obj.is_int("bool1"));
}

TEST(ObjectTest, IsDouble) {
	Object obj = ObjectTest::get_demo_object();

	EXPECT_FALSE(obj.is_double("obj1"));
	EXPECT_FALSE(obj.is_double("arr1"));
	EXPECT_FALSE(obj.is_double("str1"));
	EXPECT_FALSE(obj.is_double("null1"));
	EXPECT_FALSE(obj.is_double("int1"));
	EXPECT_TRUE(obj.is_double("double1"));
	EXPECT_FALSE(obj.is_double("bool1"));
}

TEST(ObjectTest, IsBool) {
	Object obj = ObjectTest::get_demo_object();

	EXPECT_FALSE(obj.is_bool("obj1"));
	EXPECT_FALSE(obj.is_bool("arr1"));
	EXPECT_FALSE(obj.is_bool("str1"));
	EXPECT_FALSE(obj.is_bool("null1"));
	EXPECT_FALSE(obj.is_bool("int1"));
	EXPECT_FALSE(obj.is_bool("double1"));
	EXPECT_TRUE(obj.is_bool("bool1"));
}

TEST(ObjectTest, IsArray) {
	Object obj = ObjectTest::get_demo_object();

	EXPECT_FALSE(obj.is_array("obj1"));
	EXPECT_TRUE(obj.is_array("arr1"));
	EXPECT_FALSE(obj.is_array("str1"));
	EXPECT_FALSE(obj.is_array("null1"));
	EXPECT_FALSE(obj.is_array("int1"));
	EXPECT_FALSE(obj.is_array("double1"));
	EXPECT_FALSE(obj.is_array("bool1"));
}

TEST(ObjectTest, IsObject) {
	Object obj = ObjectTest::get_demo_object();

	EXPECT_TRUE(obj.is_object("obj1"));
	EXPECT_FALSE(obj.is_object("arr1"));
	EXPECT_FALSE(obj.is_object("str1"));
	EXPECT_FALSE(obj.is_object("null1"));
	EXPECT_FALSE(obj.is_object("int1"));
	EXPECT_FALSE(obj.is_object("double1"));
	EXPECT_FALSE(obj.is_object("bool1"));
}

Object ObjectTest::get_demo_object() {
	Object obj;

	obj.set("obj1", Object());
	obj.set("arr1", Array());
	obj.set("str1", "");
	obj.set("null1", Maze::Element::get_null());
	obj.set("int1", 54321);
	obj.set("double1", 9876.54321);
	obj.set("bool1", true);

	return obj;
}
