#include <gtest/gtest.h>
#include <Maze/Maze.hpp>

using Maze::Element;

class ArrayTest : public ::testing::Test {
protected:
	ArrayTest() {}
	virtual ~ArrayTest() {}

	virtual void SetUp() {}
	virtual void TearDown() {}
};

TEST_F(ArrayTest, PushIntegerElements) {
	Element el1((int)1234567);
	Element el2((int)2432455);
	Element el3((int)5940);

	Element array(Maze::Type::Array);
	array.push_back(el1);
	array.push_back(el2);
	array.push_back(el3);

	EXPECT_EQ(array.count_children(), 3);
	EXPECT_EQ(Maze::to_string(array.get(0).get_type()), "int");
	EXPECT_EQ(Maze::to_string(array.get(1).get_type()), "int");
	EXPECT_EQ(Maze::to_string(array.get(2).get_type()), "int");
	EXPECT_EQ(array.get(0).get_int(), el1.get_int());
	EXPECT_EQ(array.get(1).get_int(), el2.get_int());
	EXPECT_EQ(array.get(2).get_int(), el3.get_int());

	Element array2(Maze::Type::Array);
	array2 << el1;
	array2 << el2;
	array2 << el3;

	EXPECT_EQ(array2.count_children(), 3);
	EXPECT_EQ(Maze::to_string(array2.get(0).get_type()), "int");
	EXPECT_EQ(Maze::to_string(array2.get(1).get_type()), "int");
	EXPECT_EQ(Maze::to_string(array2.get(2).get_type()), "int");
	EXPECT_EQ(array2.get(0).get_int(), el1.get_int());
	EXPECT_EQ(array2.get(1).get_int(), el2.get_int());
	EXPECT_EQ(array2.get(2).get_int(), el3.get_int());
}

TEST_F(ArrayTest, ConstructIsEmpty) {
	Element array(Maze::Type::Array);

	EXPECT_FALSE(array.has_children());
	EXPECT_EQ(array.count_children(), 0);
}
