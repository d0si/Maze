#include <gtest/gtest.h>
#include <Maze/Element.hpp>
#include <Maze/Helpers.hpp>
#include <Maze/Object.hpp>
#include <Maze/Array.hpp>

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
	Element el = Object();

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
