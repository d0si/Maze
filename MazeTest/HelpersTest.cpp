#include <gtest/gtest.h>
#include <Maze/Maze.hpp>
#include <Maze/Helpers.hpp>
#include <Maze/Object.hpp>

using Maze::Element;
using Maze::Object;
using Maze::Array;

class HelpersTest : public ::testing::Test {
protected:
	HelpersTest() {}
	virtual ~HelpersTest() {}

	virtual void SetUp() {}
	virtual void TearDown() {}
};

TEST(HelpersTest, Element_ToJsonElement_Null) {
	Element el = Element::get_null();

	auto result = Maze::Helpers::Element::to_json_element(&el);

	ASSERT_TRUE(result.is_null());
}

TEST(HelpersTest, Element_ToJsonElement_Bool) {
	Element el = true;

	auto result = Maze::Helpers::Element::to_json_element(&el);

	ASSERT_TRUE(result.is_boolean());
}

TEST(HelpersTest, Element_ToJsonElement_Int) {
	Element el = 54321;

	auto result = Maze::Helpers::Element::to_json_element(&el);

	ASSERT_TRUE(result.is_number());
	ASSERT_TRUE(result.is_number_integer());
}

TEST(HelpersTest, Element_ToJsonElement_Double) {
	Element el = 9876.54321;

	auto result = Maze::Helpers::Element::to_json_element(&el);

	ASSERT_TRUE(result.is_number());
	ASSERT_TRUE(result.is_number_float());
}

TEST(HelpersTest, Element_ToJsonElement_String) {
	Element el = "test_string";

	auto result = Maze::Helpers::Element::to_json_element(&el);

	ASSERT_TRUE(result.is_string());
}

TEST(HelpersTest, Element_ToJsonElement_Array) {
	Element el = Array();

	auto result = Maze::Helpers::Element::to_json_element(&el);

	ASSERT_TRUE(result.is_array());
}

TEST(HelpersTest, Element_ToJsonElement_Object) {
	Element el = Object();

	auto result = Maze::Helpers::Element::to_json_element(&el);

	ASSERT_TRUE(result.is_object());
}

TEST(HelpersTest, Element_ElementFromJson_Null) {
	nlohmann::json json_el;

	auto result = Maze::Helpers::Element::from_json(json_el);

	ASSERT_TRUE(result.is_null());
}

TEST(HelpersTest, Element_ElementFromJson_Bool) {
	nlohmann::json json_el = true;

	auto result = Maze::Helpers::Element::from_json(json_el);

	ASSERT_TRUE(result.is_bool());
}

TEST(HelpersTest, Element_ElementFromJson_Int) {
	nlohmann::json json_el = 54321;

	auto result = Maze::Helpers::Element::from_json(json_el);

	ASSERT_TRUE(result.is_int());
}

TEST(HelpersTest, Element_ElementFromJson_Double) {
	nlohmann::json json_el = 9876.54321;

	auto result = Maze::Helpers::Element::from_json(json_el);

	ASSERT_TRUE(result.is_double());
}

TEST(HelpersTest, Element_ElementFromJson_String) {
	nlohmann::json json_el = "test_string";

	auto result = Maze::Helpers::Element::from_json(json_el);

	ASSERT_TRUE(result.is_string());
}

TEST(HelpersTest, Element_ElementFromJson_Array) {
	nlohmann::json json_el = nlohmann::json::array();

	auto result = Maze::Helpers::Element::from_json(json_el);

	ASSERT_TRUE(result.is_array());
}

TEST(HelpersTest, Element_ElementFromJson_Object) {
	nlohmann::json json_el = nlohmann::json::object();

	auto result = Maze::Helpers::Element::from_json(json_el);

	ASSERT_TRUE(result.is_object());
}
