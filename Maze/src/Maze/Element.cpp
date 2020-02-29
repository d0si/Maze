#include <Maze/Element.hpp>
#include <Maze/Array.hpp>
#include <Maze/Object.hpp>
#include <Maze/Helpers.hpp>
#include <nlohmann/json.hpp>

namespace Maze {
	Element::Element() {

	}

	Element::Element(bool val) {
		set_bool(val);
	}

	Element::Element(int val) {
		set_int(val);
	}

	Element::Element(double val) {
		set_double(val);
	}

	Element::Element(std::string& val) {
		set_string(val);
	}

	Element::Element(const char* val) {
		set_string(val);
	}

	Element::Element(Array val) {
		set_array(val);
	}

	Element::Element(Object val) {
		set_object(val);
	}

	Element::Element(Type type) {
		set_type(type);
	}

	Element::~Element() {
	}

	void Element::set_type(Type type) {
		switch (type) {
		case Type::Null:
			set_null();
			break;
		case Type::Bool:
			set_bool(false);
			break;
		case Type::Int:
			set_int(0);
			break;
		case Type::Double:
			set_double(0);
			break;
		case Type::String:
			set_string("");
			break;
		case Type::Array:
			set_array(Array());
			break;
		case Type::Object:
			set_object(Object());
			break;
		default:
			set_null();
		}
	}

	Type Element::get_type() {
		return type_;
	}

	void Element::set_key(std::string key) {
		ptr_key_ = std::make_shared<std::string>(key);
	}

	std::string Element::get_key() {
		return *ptr_key_;
	}

	void Element::set_null() {
		if (type_ != Type::Null) {
			val_bool_ = false;
			val_int_ = 0;
			type_ = Type::Null;
		}
	}

	void Element::set_bool(bool val) {
		val_bool_ = val;
		type_ = Type::Bool;
	}

	void Element::operator=(bool val) {
		set_bool(val);
	}

	bool Element::get_bool() {
		if (type_ == Type::Bool) {
			return val_bool_;
		}
		return false;
	}

	Element::operator bool() {
		return get_bool();
	}

	void Element::set_int(int val) {
		val_int_ = val;
		type_ = Type::Int;
	}

	void Element::operator=(int val) {
		set_int(val);
	}

	int Element::get_int() {
		if (type_ == Type::Int) {
			return val_int_;
		}

		return 0;
	}

	Element::operator int() {
		return get_int();
	}

	void Element::set_double(double val) {
		ptr_double_ = std::make_shared<double>(val);
		type_ = Type::Double;
	}

	void Element::operator=(double val) {
		set_double(val);
	}

	double Element::get_double() {
		if (type_ == Type::Double) {
			return *ptr_double_;
		}

		return 0;
	}

	Element::operator double() {
		return get_double();
	}

	void Element::set_string(std::string val) {
		ptr_string_ = std::make_shared<std::string>(val);
		type_ = Type::String;
	}

	void Element::operator=(std::string val) {
		set_string(val);
	}

	void Element::operator=(const char* val) {
		set_string(val);
	}

	std::string Element::get_string() {
		if (type_ == Type::String) {
			return *ptr_string_;
		}

		return "";
	}

	Element::operator std::string() {
		return get_string();
	}

	void Element::set_array(Array val) {
		ptr_array_ = std::make_shared<Array>(val);
		type_ = Type::Array;
	}

	void Element::operator=(Array val) {
		set_array(val);
	}

	Array Element::get_array() {
		if (type_ == Type::Array) {
			return *ptr_array_;
		}
		return Array();
	}

	Element::operator Array() {
		return get_array();
	}

	void Element::set_object(Object val) {
		ptr_object_ = std::make_shared<Object>(val);
		type_ = Type::Object;
	}

	void Element::operator=(Object val) {
		set_object(val);
	}

	Object Element::get_object() {
		if (type_ == Type::Object) {
			return *ptr_object_;
		}
		return Object();
	}

	Element::operator Object() {
		return get_object();
	}

	bool Element::is_null() {
		return is(Type::Null);
	}

	bool Element::is_bool() {
		return is(Type::Bool);
	}

	bool Element::is_int() {
		return is(Type::Int);
	}

	bool Element::is_double() {
		return is(Type::Double);
	}

	bool Element::is_string() {
		return is(Type::String);
	}

	bool Element::is_array() {
		return is(Type::Array);
	}

	bool Element::is_object() {
		return is(Type::Object);
	}

	bool Element::is(Type type) {
		return (type_ == type);
	}

	void Element::apply(Element new_element) {
		switch (new_element.get_type()) {
		case Type::Null:
			set_null();
			break;
		case Type::Bool:
			set_bool(new_element.get_bool());
			break;
		case Type::Int:
			set_int(new_element.get_int());
			break;
		case Type::Double:
			set_double(new_element.get_double());
			break;
		case Type::String:
			set_string(new_element.get_string());
			break;
		case Type::Array:
			set_array(new_element.get_array());
			break;
		case Type::Object:
			get_object().apply(new_element.get_object());
			break;
		}
	}

	std::string Element::to_json(int spacing) {
		return Helpers::Element::to_json_element(this).dump(spacing);
	}

	void Element::apply_json(std::string json_string) {
		Helpers::Element::apply_json(this, nlohmann::json::parse(json_string));
	}

	Element Element::from_json(std::string json_string) {
		return Helpers::Element::from_json(nlohmann::json::parse(json_string));
	}

	Element Element::get_null() {
		Element el;
		el.set_null();
		return el;
	}
}  // namespace Maze
