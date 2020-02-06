#include "arraytest.hpp"
#include <maze/array.hpp>
#include <maze/maze.hpp>

using maze::Array;
using maze::Element;

ArrayTest::ArrayTest() {

}

ArrayTest::~ArrayTest() {};

void ArrayTest::SetUp() {};

void ArrayTest::TearDown() {};

TEST_F(ArrayTest, PushIntegerElements) {
  Element el1((int)1234567);
  Element el2((int)2432455);
  Element el3((int)5940);

  Array array;
  array.push(el1);
  array.push(el2);
  array.push(el3);

  EXPECT_EQ(array.size(), 3);
  EXPECT_EQ(maze::to_string(array.get(0).get_type()), "int");
  EXPECT_EQ(maze::to_string(array.get(1).get_type()), "int");
  EXPECT_EQ(maze::to_string(array.get(2).get_type()), "int");
  EXPECT_EQ(array.get(0).get_int(), el1.get_int());
  EXPECT_EQ(array.get(1).get_int(), el2.get_int());
  EXPECT_EQ(array.get(2).get_int(), el3.get_int());

  Array array2;
  array2 << el1;
  array2 << el2;
  array2 << el3;

  EXPECT_EQ(array2.size(), 3);
  EXPECT_EQ(maze::to_string(array2.get(0).get_type()), "int");
  EXPECT_EQ(maze::to_string(array2.get(1).get_type()), "int");
  EXPECT_EQ(maze::to_string(array2.get(2).get_type()), "int");
  EXPECT_EQ(array2.get(0).get_int(), el1.get_int());
  EXPECT_EQ(array2.get(1).get_int(), el2.get_int());
  EXPECT_EQ(array2.get(2).get_int(), el3.get_int());
}

TEST_F(ArrayTest, ConstructIsEmpty) {
  Array array;

  EXPECT_TRUE(array.is_empty());
  EXPECT_EQ(array.size(), 0);
}

TEST_F(ArrayTest, Version) {
  EXPECT_EQ(maze::get_version(), "0.0.1");
}
