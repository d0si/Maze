#include "testarray.h"
#include <maze/array.h>

ArrayTest::ArrayTest() {

}

ArrayTest::~ArrayTest() {};

void ArrayTest::SetUp() {};

void ArrayTest::TearDown() {};

TEST_F(ArrayTest, ConstructIsEmpty) {
  maze::array array;

  EXPECT_TRUE(array.is_empty());
}