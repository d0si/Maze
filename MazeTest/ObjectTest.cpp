#include <gtest/gtest.h>
#include <Maze/Object.hpp>

using Maze::Object;

class ObjectTest : public ::testing::Test {
protected:
	ObjectTest() {}
	virtual ~ObjectTest() {}

	virtual void SetUp() {}
	virtual void TearDown() {}
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
