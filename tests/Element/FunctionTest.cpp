#include <gtest/gtest.h>
#include <Maze/Maze.hpp>

#define ACTUAL_PI 3
#define ACTUAL_G 10

class ElementFunctionTest : public ::testing::Test {
protected:
    Maze::Element el_func_empty;
    Maze::Element el_func_return_input;
    Maze::Element el_func_num_add;
    Maze::Element el_int;

    void SetUp() override {
        el_func_empty = Maze::Element([](const Maze::Element& value) {
            return Maze::Element();
            });

        el_func_return_input = Maze::Element([](const Maze::Element& value) {
            return value;
            });

        el_func_num_add = Maze::Element([](const Maze::Element& value) {
            if (value.is_int())
                return Maze::Element(value.get_int() + 1);
            else if (value.is_double())
                return Maze::Element(value.get_double() + 1);

            return Maze::Element(1);
            });

        el_int = Maze::Element(42);
    }
};

TEST_F(ElementFunctionTest, Construct_FromLambda) {
    ASSERT_TRUE(el_func_empty.is_function());
    ASSERT_TRUE(el_func_return_input.is_function());
    ASSERT_TRUE(el_func_num_add.is_function());
}

TEST_F(ElementFunctionTest, Execute_Empty) {
    auto result = el_func_empty.execute_function(el_int);
    ASSERT_TRUE(result.is_null());

    result = el_func_empty.execute_function(Maze::Element());
    ASSERT_TRUE(result.is_null());

    result = el_func_empty.execute_function(Maze::Element("val"));
    ASSERT_TRUE(result.is_null());

    result = el_func_empty.execute_function("val123");
    ASSERT_TRUE(result.is_null());
}

TEST_F(ElementFunctionTest, Execute_ReturnInput) {
    auto result = el_func_return_input.execute_function(el_int);
    ASSERT_TRUE(result.is_int());
    ASSERT_EQ(result.get_int(), el_int.get_int());

    result = el_func_return_input.execute_function(Maze::Element());
    ASSERT_TRUE(result.is_null());

    result = el_func_return_input.execute_function(Maze::Element("val"));
    ASSERT_TRUE(result.is_string());
    ASSERT_EQ(result.get_string(), "val");

    result = el_func_return_input.execute_function("val123");
    ASSERT_TRUE(result.is_string());
    ASSERT_EQ(result.get_string(), "val123");
}

TEST_F(ElementFunctionTest, Execute_NumAddOne) {
    auto result = el_func_num_add.execute_function(el_int);
    ASSERT_TRUE(result.is_int());
    ASSERT_EQ(result.get_int(), el_int.get_int() + 1);

    result = el_func_num_add.execute_function(9.9);
    ASSERT_TRUE(result.is_double());
    ASSERT_EQ(result.get_double(), 10.9);

    result = el_func_num_add.execute_function(Maze::Element());
    ASSERT_TRUE(result.is_int());
    ASSERT_EQ(result.get_int(), 1);

    result = el_func_num_add.execute_function(Maze::Element("val"));
    ASSERT_TRUE(result.is_int());
    ASSERT_EQ(result.get_int(), 1);

    result = el_func_num_add.execute_function("val123");
    ASSERT_TRUE(result.is_int());
    ASSERT_EQ(result.get_int(), 1);
}

TEST_F(ElementFunctionTest, Execute_NumAddOne_Short) {
    auto result = el_func_num_add.e(el_int);
    ASSERT_TRUE(result.is_int());
    ASSERT_EQ(result.get_int(), el_int.get_int() + 1);

    result = el_func_num_add.e(9.9);
    ASSERT_TRUE(result.is_double());
    ASSERT_EQ(result.get_double(), 10.9);

    result = el_func_num_add.e(Maze::Element());
    ASSERT_TRUE(result.is_int());
    ASSERT_EQ(result.get_int(), 1);

    result = el_func_num_add.e(Maze::Element("val"));
    ASSERT_TRUE(result.is_int());
    ASSERT_EQ(result.get_int(), 1);

    result = el_func_num_add.e("val123");
    ASSERT_TRUE(result.is_int());
    ASSERT_EQ(result.get_int(), 1);
}

TEST_F(ElementFunctionTest, Setter) {
    Maze::Element el;

    el.set_function([](const Maze::Element& value) {return value;});
    ASSERT_TRUE(el.is_function());
    ASSERT_EQ(el.e(42).get_int(), 42);
}

TEST_F(ElementFunctionTest, Setter_ChangeType) {
    Maze::Element el("val");

    el.set_function([](const Maze::Element& value) {return value;});
    ASSERT_TRUE(el.is_function());
}

TEST_F(ElementFunctionTest, GetCallback) {
    auto func = [](const Maze::Element& value) {return value;};
    Maze::Element el(func);

    ASSERT_TRUE(el.is_function());
    ASSERT_EQ(el.get_callback(), func);
}

TEST_F(ElementFunctionTest, IsFunctionType) {
    auto func = [](const Maze::Element& value) {return value;};
    Maze::Element el;

    el.set_function(func);
    ASSERT_FALSE(el.is_null());
    ASSERT_TRUE(el.is_function());
    ASSERT_TRUE(el.is(Maze::Type::Function));

    el = Maze::Element(func);
    ASSERT_FALSE(el.is_null());
    ASSERT_TRUE(el.is_function());
    ASSERT_TRUE(el.is(Maze::Type::Function));
}

TEST_F(ElementFunctionTest, Apply_NullToFunction) {
    Maze::Element el(Maze::Type::Null);
    auto func = [](const Maze::Element& value) {return value;};
    auto func2 = [](const Maze::Element& value) {return value;};

    el.apply(Maze::Element(func));
    ASSERT_TRUE(el.is_function());
    ASSERT_EQ(el.get_callback(), func);
    ASSERT_NE(el.get_callback(), func2);
}

TEST_F(ElementFunctionTest, Apply_ChangeType) {
    Maze::Element el("val");
    auto func = [](const Maze::Element& value) {return value;};

    el.apply(Maze::Element(func));
    ASSERT_TRUE(el.is_function());
    ASSERT_EQ(el.get_callback(), func);
}

TEST_F(ElementFunctionTest, ToJson) {
    ASSERT_EQ(el_func_empty.to_json(), "null");
    ASSERT_EQ(el_func_num_add.to_json(), "null");
    ASSERT_EQ(el_func_return_input.to_json(), "null");
}
