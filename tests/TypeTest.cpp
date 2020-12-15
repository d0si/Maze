#include <gtest/gtest.h>
#include <Maze/Maze.hpp>

class TypeTest : public ::testing::Test {};

TEST(TypeTest, ToString_CorrectValue) {
	Maze::Type type = Maze::Type::Array;
	EXPECT_EQ(Maze::to_string(type), "array");

	type = Maze::Type::Bool;
	EXPECT_EQ(Maze::to_string(type), "bool");

	type = Maze::Type::Double;
	EXPECT_EQ(Maze::to_string(type), "double");

	type = Maze::Type::Int;
	EXPECT_EQ(Maze::to_string(type), "int");

	type = Maze::Type::Null;
	EXPECT_EQ(Maze::to_string(type), "null");

	type = Maze::Type::Object;
	EXPECT_EQ(Maze::to_string(type), "object");

	type = Maze::Type::String;
	EXPECT_EQ(Maze::to_string(type), "string");
}
