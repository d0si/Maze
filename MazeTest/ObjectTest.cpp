#include <gtest/gtest.h>
#include <Maze/Maze.hpp>

using Maze::Object;

class ObjectTest : public ::testing::Test {
protected:
	Object test_object;

	void SetUp() override {
		test_object.set("obj1", Object());
		test_object.set("arr1", Maze::Element(Maze::Type::Array));
		test_object.set("str1", "test_string");
		test_object.set("null1", Maze::Element::get_null_element());
		test_object.set("int1", 54321);
		test_object.set("double1", 9876.54321);
		test_object.set("bool1", true);
	}
};

TEST_F(ObjectTest, ConstructFromJsonString) {
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

TEST_F(ObjectTest, IsString) {
	EXPECT_FALSE(test_object.is_string("obj1"));
	EXPECT_FALSE(test_object.is_string("arr1"));
	EXPECT_TRUE(test_object.is_string("str1"));
	EXPECT_FALSE(test_object.is_string("null1"));
	EXPECT_FALSE(test_object.is_string("int1"));
	EXPECT_FALSE(test_object.is_string("double1"));
	EXPECT_FALSE(test_object.is_string("bool1"));
}

TEST_F(ObjectTest, IsInt) {
	EXPECT_FALSE(test_object.is_int("obj1"));
	EXPECT_FALSE(test_object.is_int("arr1"));
	EXPECT_FALSE(test_object.is_int("str1"));
	EXPECT_FALSE(test_object.is_int("null1"));
	EXPECT_TRUE(test_object.is_int("int1"));
	EXPECT_FALSE(test_object.is_int("double1"));
	EXPECT_FALSE(test_object.is_int("bool1"));
}

TEST_F(ObjectTest, IsDouble) {
	EXPECT_FALSE(test_object.is_double("obj1"));
	EXPECT_FALSE(test_object.is_double("arr1"));
	EXPECT_FALSE(test_object.is_double("str1"));
	EXPECT_FALSE(test_object.is_double("null1"));
	EXPECT_FALSE(test_object.is_double("int1"));
	EXPECT_TRUE(test_object.is_double("double1"));
	EXPECT_FALSE(test_object.is_double("bool1"));
}

TEST_F(ObjectTest, IsBool) {
	EXPECT_FALSE(test_object.is_bool("obj1"));
	EXPECT_FALSE(test_object.is_bool("arr1"));
	EXPECT_FALSE(test_object.is_bool("str1"));
	EXPECT_FALSE(test_object.is_bool("null1"));
	EXPECT_FALSE(test_object.is_bool("int1"));
	EXPECT_FALSE(test_object.is_bool("double1"));
	EXPECT_TRUE(test_object.is_bool("bool1"));
}

TEST_F(ObjectTest, IsArray) {
	EXPECT_FALSE(test_object.is_array("obj1"));
	EXPECT_TRUE(test_object.is_array("arr1"));
	EXPECT_FALSE(test_object.is_array("str1"));
	EXPECT_FALSE(test_object.is_array("null1"));
	EXPECT_FALSE(test_object.is_array("int1"));
	EXPECT_FALSE(test_object.is_array("double1"));
	EXPECT_FALSE(test_object.is_array("bool1"));
}

TEST_F(ObjectTest, IsObject) {
	EXPECT_TRUE(test_object.is_object("obj1"));
	EXPECT_FALSE(test_object.is_object("arr1"));
	EXPECT_FALSE(test_object.is_object("str1"));
	EXPECT_FALSE(test_object.is_object("null1"));
	EXPECT_FALSE(test_object.is_object("int1"));
	EXPECT_FALSE(test_object.is_object("double1"));
	EXPECT_FALSE(test_object.is_object("bool1"));
}

TEST_F(ObjectTest, Get_NonexistentElement) {
	auto el = test_object.get("nonexistent_key");
	
	EXPECT_TRUE(el.is_null());
}

TEST_F(ObjectTest, Get_ExistingElement) {
	auto el = test_object.get("str1");

	EXPECT_EQ(el.get_string(), "test_string");
}

TEST_F(ObjectTest, SetNull) {
	test_object.set_null("str1");

	EXPECT_TRUE(test_object.get("str1").is_null());
}

TEST_F(ObjectTest, Remove) {
	test_object.remove("str1");

	EXPECT_FALSE(test_object.exists("str1"));
}

TEST_F(ObjectTest, Clear) {
	test_object.clear();

	EXPECT_TRUE(test_object.is_empty());
}

TEST_F(ObjectTest, ApplyObject) {
	Object obj2;
	obj2["val1"] = "test";
	obj2["str1"] = "overriden value";

	test_object.apply(obj2);

	EXPECT_TRUE(test_object.is_string("val1"));
	EXPECT_TRUE(test_object.is_string("str1"));
	EXPECT_EQ(test_object["val1"].s(), "test");
	EXPECT_EQ(test_object["str1"].s(), "overriden value");
}
