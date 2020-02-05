#include <gtest/gtest.h>

class ArrayTest : public ::testing::Test {
protected:
  ArrayTest();

  virtual ~ArrayTest();

  virtual void SetUp();
  virtual void TearDown();
};
