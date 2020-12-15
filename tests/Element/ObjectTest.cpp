#include <gtest/gtest.h>
#include <Maze/Maze.hpp>

class ElementObjectTest : public ::testing::Test {
protected:
    Maze::Element obj_empty;
    Maze::Element obj_1;
    Maze::Element obj_2;

    void SetUp() override {
        obj_empty = Maze::Element(Maze::Type::Object);

        obj_1 = Maze::Element(Maze::Type::Object);
        obj_1.set("val1", "val1");
        obj_1.set("val2", 42);
        obj_1.set("val3", true);

        obj_2 = Maze::Element(Maze::Type::Object);
        obj_2.set("obj1", Maze::Element(Maze::Type::Object));
        obj_2.set("arr1", Maze::Element(Maze::Type::Array));
        obj_2.set("str1", "test_string");
        obj_2.set("null1", Maze::Element::get_null_element());
        obj_2.set("int1", 54321);
        obj_2.set("double1", 9876.54321);
        obj_2.set("bool1", true);
    }
};

TEST_F(ElementObjectTest, Constructor) {
    EXPECT_TRUE(obj_empty.is_object());
    EXPECT_EQ(obj_empty.count_children(), 0);
    EXPECT_TRUE(obj_1.is_object());
    EXPECT_EQ(obj_1.count_children(), 3);
    EXPECT_TRUE(obj_2.is_object());
    EXPECT_EQ(obj_2.count_children(), 7);

    Maze::Element el({ "key1", "key2" }, { Maze::Element("el1"), Maze::Element(23) });
    EXPECT_TRUE(el.is_object());
    EXPECT_EQ(el.count_children(), 2);

    el = Maze::Element({ "key3", "key4", "key5", "key6" }, { 5532, "value1", false, true });
    EXPECT_TRUE(el.is_object());
    EXPECT_EQ(el.count_children(), 4);
}

TEST_F(ElementObjectTest, Construct_FromAnother) {
    Maze::Element el(obj_2);
    EXPECT_TRUE(el.is_object());
    EXPECT_EQ(el.count_children(), 7);
}

TEST_F(ElementObjectTest, Getter_Brackets) {
    EXPECT_EQ(obj_1["val1"].s(), "val1");
    EXPECT_EQ(obj_1["val2"].i(), 42);
    EXPECT_EQ(obj_1["val3"].b(), true);

    std::string key = "str1";
    EXPECT_EQ(obj_2[key].s(), "test_string");
}

TEST_F(ElementObjectTest, Getter) {
    EXPECT_EQ(obj_1.get("val1").s(), "val1");
    EXPECT_EQ(obj_1.get("val2").i(), 42);
    EXPECT_EQ(obj_1.get("val3").b(), true);

    std::string key = "str1";
    EXPECT_EQ(obj_2.get(key).s(), "test_string");

    EXPECT_TRUE(obj_2.get("val99").is_null());
}

TEST_F(ElementObjectTest, Getter_ConstRef) {
    EXPECT_EQ(obj_1.get_const_ref("val1", 42).s(), "val1");

    EXPECT_TRUE(obj_1.get_const_ref("val99", Maze::Element()).is_null());
    EXPECT_EQ(obj_1.get_const_ref("val99", 42).i(), 42);
}

TEST_F(ElementObjectTest, Getter_FallbackValues) {
    EXPECT_EQ(obj_1.get("val1", 42).s(), "val1");

    EXPECT_TRUE(obj_1.get("val99").is_null());
    EXPECT_TRUE(obj_1.get("val99", Maze::Element()).is_null());
    EXPECT_EQ(obj_1.get("val99", 42).i(), 42);
}

TEST_F(ElementObjectTest, Getter_Ref) {
    EXPECT_EQ(obj_1.get_ref("val1").s(), "val1");
    EXPECT_EQ(obj_1.get_ref("val2").i(), 42);
    EXPECT_EQ(obj_1.get_ref("val3").b(), true);

    std::string key = "str1";
    EXPECT_EQ(obj_2.get_ref(key).s(), "test_string");
}

TEST_F(ElementObjectTest, SetElement) {
    Maze::Element el(Maze::Type::Object);
    el.set("val", "val1");
    EXPECT_TRUE(el.get("val").is_string());
    EXPECT_EQ(el.get("val").s(), "val1");

    el.set("val", "val99");
    EXPECT_TRUE(el.get("val").is_string());
    EXPECT_EQ(el.get("val").s(), "val99");

    el.set("val", 66);
    EXPECT_TRUE(el.get("val").is_int());
    EXPECT_EQ(el.get("val").i(), 66);
}

TEST_F(ElementObjectTest, SetElement_ToNull) {
    Maze::Element el(Maze::Type::Object);
    el.set("val", "val1");
    EXPECT_TRUE(el.get("val").is_string());
    EXPECT_EQ(el.get("val").s(), "val1");

    el.set("val1", Maze::Element(Maze::Type::Null));
    EXPECT_TRUE(el.get("val1").is_null());
}

TEST_F(ElementObjectTest, Remove) {
    EXPECT_EQ(obj_1.count_children(), 3);

    obj_1.remove("val2");
    EXPECT_EQ(obj_1.count_children(), 2);
    EXPECT_FALSE(obj_1.exists("val2"));
    EXPECT_TRUE(obj_1.get("val2").is_null());
}

TEST_F(ElementObjectTest, Clear) {
    EXPECT_EQ(obj_1.count_children(), 3);
    EXPECT_TRUE(obj_1.has_children());

    obj_1.remove_all_children();

    EXPECT_EQ(obj_1.count_children(), 0);
    EXPECT_FALSE(obj_1.has_children());
}

TEST_F(ElementObjectTest, Exists) {
    EXPECT_TRUE(obj_1.exists("val1"));
    EXPECT_TRUE(obj_1.exists("val2"));
    EXPECT_TRUE(obj_1.exists("val3"));
    EXPECT_FALSE(obj_1.exists("val99"));
    EXPECT_FALSE(obj_1.exists("val100"));
}

TEST_F(ElementObjectTest, IndexOf) {
    EXPECT_EQ(obj_1.index_of("val1"), 0);
    EXPECT_EQ(obj_1.index_of("val2"), 1);
    EXPECT_EQ(obj_1.index_of("val3"), 2);

    obj_1.remove("val1");
    EXPECT_EQ(obj_1.index_of("val1"), -1);
    EXPECT_EQ(obj_1.index_of("val2"), 0);
    EXPECT_EQ(obj_1.index_of("val3"), 1);
}

TEST_F(ElementObjectTest, GetKeys) {
    EXPECT_EQ(obj_1.get_keys(), std::vector<std::string>({ "val1", "val2", "val3" }));
}

TEST_F(ElementObjectTest, IsString) {
    EXPECT_TRUE(obj_1.is_string("val1"));
    EXPECT_FALSE(obj_1.is_string("val2"));
    EXPECT_FALSE(obj_1.is_string("val3"));
}

TEST_F(ElementObjectTest, IsInt) {
    EXPECT_FALSE(obj_1.is_int("val1"));
    EXPECT_TRUE(obj_1.is_int("val2"));
    EXPECT_FALSE(obj_1.is_int("val3"));
}

TEST_F(ElementObjectTest, IsDouble) {
    obj_1.set("val2", 9.9);

    EXPECT_FALSE(obj_1.is_double("val1"));
    EXPECT_TRUE(obj_1.is_double("val2"));
    EXPECT_FALSE(obj_1.is_double("val3"));
}

TEST_F(ElementObjectTest, IsBool) {
    EXPECT_FALSE(obj_1.is_bool("val1"));
    EXPECT_FALSE(obj_1.is_bool("val2"));
    EXPECT_TRUE(obj_1.is_bool("val3"));
}

TEST_F(ElementObjectTest, IsArray) {
    EXPECT_FALSE(obj_2.is_array("obj1"));
    EXPECT_FALSE(obj_2.is_array("str1"));
    EXPECT_TRUE(obj_2.is_array("arr1"));
}

TEST_F(ElementObjectTest, IsObject) {
    EXPECT_TRUE(obj_2.is_object("obj1"));
    EXPECT_FALSE(obj_2.is_object("str1"));
    EXPECT_FALSE(obj_2.is_object("arr1"));
}

TEST_F(ElementObjectTest, IsNull) {
    EXPECT_FALSE(obj_2.is_null("obj1"));
    EXPECT_FALSE(obj_2.is_null("str1"));
    EXPECT_TRUE(obj_2.is_null("null1"));
}

TEST_F(ElementObjectTest, IsFunction) {
    obj_1.set("val2", Maze::Element([](const Maze::Element& value) {return value;}));

    EXPECT_FALSE(obj_1.is_function("val1"));
    EXPECT_TRUE(obj_1.is_function("val2"));
    EXPECT_FALSE(obj_1.is_function("val3"));
}

TEST_F(ElementObjectTest, ApplyObject) {
    Maze::Element changes(Maze::Type::Object);
    changes["val1"] = "test";
    changes["str1"] = "overriden value";

    obj_2.apply(changes);

    EXPECT_TRUE(obj_2.is_string("val1"));
    EXPECT_TRUE(obj_2.is_string("str1"));
    EXPECT_EQ(obj_2["val1"].s(), "test");
    EXPECT_EQ(obj_2["str1"].s(), "overriden value");
}

TEST_F(ElementObjectTest, FromJsonString) {
    const std::string input = R"(
	{
		"config": {
			"key_1": "value_1"
		}
	}
)";

    Maze::Element parsed = Maze::Element::from_json(input);

    EXPECT_TRUE(parsed.count_children() == 1);
    EXPECT_TRUE(parsed[0].is_object());
    EXPECT_TRUE(parsed["config"].is_object());
}

TEST_F(ElementObjectTest, ToJsonString) {
    Maze::Element el({ "key1", "key2" }, { "val1", 42 });

    EXPECT_EQ(el.to_json(), R"({
  "key1": "val1",
  "key2": 42
})");
}
