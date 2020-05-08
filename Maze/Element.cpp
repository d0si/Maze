#include <Maze/Maze.hpp>
#include <Maze/Helpers.hpp>
#include <nlohmann/json.hpp>

namespace Maze {
#pragma region Constructors/destructors
	Element::Element() {
		set_as_null();
	}

	Element::Element(const Element& val) {
		copy_from_element(val);
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

	Element::Element(const std::string& val) {
		set_string(val);
	}

	Element::Element(const char* val) {
		set_string(val);
	}
	
	Element::Element(const std::vector<Element>& val) {
		set_array(val);
	}
	
	Element::Element(const std::vector<std::string>& keys, const std::vector<Element>& val) {
		set_object(keys, val);
	}

	Element::Element(Type type) {
		set_type(type);
	}

	Element::~Element() {

	}
#pragma endregion

	void Element::copy_from_element(const Element& val) {
		switch (val.get_type()) {
		case Type::Bool:
			set_bool(val.get_bool());
			break;
		case Type::Int:
			set_int(val.get_int());
			break;
		case Type::Double:
			set_double(val.get_double());
			break;
		case Type::String:
			set_string(val.get_string());
			break;
		case Type::Array:
			set_array(val.get_children());
			break;
		case Type::Object:
			set_object(val.get_keys(), val.get_children());
			break;
		default:
			set_as_null();
		}
	}

	void Element::operator=(const Element& val) {
		copy_from_element(val);
	}

	void Element::set_type(Type type) {
		switch (type) {
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
			set_array({});
			break;
		case Type::Object:
			set_object({}, {});
			break;
		default:
			set_as_null();
		}
	}

	Type Element::get_type() const {
		return type_;
	}

	void Element::set_key(const std::string& key) {
		val_key_ = key;
	}

	const std::string& Element::get_key() const {
		return val_key_;
	}

	void Element::set_as_null(bool clear_existing_values) {
		type_ = Type::Null;

		if (clear_existing_values) {
			val_bool_ = false;
			val_int_ = 0;
			val_double_ = 0;
			val_string_ = "";
			children_.clear();
			children_keys_.clear();
		}
	}

#pragma region Boolean
	const bool& Element::get_bool() const {
		if (type_ == Type::Bool) {
			return val_bool_;
		}

		static const bool false_constant = false;

		return false_constant;
	}

	const bool& Element::b() const {
		return get_bool();
	}
	
	bool& Element::b() {
		if (type_ != Type::Bool) {
			throw MazeException("Cannot get reference to bool value from a non-bool element. Use set_bool instead to set value and change type.");
		}

		return val_bool_;
	}

	Element::operator bool() const {
		return get_bool();
	}

	void Element::set_bool(bool val) {
		val_bool_ = val;
		type_ = Type::Bool;
	}

	void Element::operator=(bool val) {
		set_bool(val);
	}

	void Element::b(bool val) {
		set_bool(val);
	}
#pragma endregion

#pragma region Integer
	const int& Element::get_int() const {
		if (type_ == Type::Int) {
			return val_int_;
		}

		static const int zero_constant = 0;

		return zero_constant;
	}

	const int& Element::i() const {
		return get_int();
	}

	int& Element::i() {
		if (type_ != Type::Int) {
			throw MazeException("Cannot get reference to int value from a non-int element. Use set_int instead to set value and change type.");
		}

		return val_int_;
	}

	Element::operator int() const {
		return get_int();
	}

	void Element::set_int(int val) {
		val_int_ = val;
		type_ = Type::Int;
	}

	void Element::i(int val) {
		set_int(val);
	}

	void Element::operator=(int val) {
		set_int(val);
	}
#pragma endregion

#pragma region Double
	const double& Element::get_double() const {
		if (type_ == Type::Double) {
			return val_double_;
		}

		static const double zero_constant = 0;

		return zero_constant;
	}

	const double& Element::d() const {
		return get_double();
	}

	double& Element::d() {
		if (type_ != Type::Double) {
			throw MazeException("Cannot get reference to double value from a non-double element. Use set_double instead to set value and change type.");
		}

		return val_double_;
	}

	Element::operator double() const {
		return get_double();
	}

	void Element::set_double(double val) {
		val_double_ = val;
		type_ = Type::Double;
	}

	void Element::d(double val) {
		set_double(val);
	}

	void Element::operator=(double val) {
		set_double(val);
	}
#pragma endregion

#pragma region String
	const std::string& Element::get_string() const {
		if (type_ == Type::String) {
			return val_string_;
		}

		static const std::string empty_string_constant = "";

		return empty_string_constant;
	}

	const std::string& Element::s() const {
		return get_string();
	}

	std::string& Element::s() {
		if (type_ != Type::String) {
			throw MazeException("Cannot get reference to string value from a non-string element. Use set_string instead to set value and change type.");
		}

		return val_string_;
	}

	Element::operator std::string() const {
		return get_string();
	}

	void Element::set_string(const std::string& val) {
		val_string_ = val;
		type_ = Type::String;
	}

	void Element::s(const std::string& val) {
		set_string(val);
	}

	void Element::operator=(const std::string& val) {
		set_string(val);
	}

	void Element::operator=(const char* val) {
		set_string(val);
	}
#pragma endregion

#pragma region Array
	const Element& Element::get(int index) const {
		if (type_ == Type::Array || type_ == Type::Object) {
			if (index < children_.size()) {
				return children_[index];
			}
		}

		static const Element empty_element_constant = Element();

		return empty_element_constant;
	}
	
	const Element& Element::get(int index, const Element& fallback_value) const {
		if (type_ == Type::Array || type_ == Type::Object) {
			if (index < children_.size()) {
				return children_[index];
			}
		}

		return fallback_value;
	}

	Element& Element::get(int index) {
		return *get_ptr(index);
	}

	Element& Element::get(int index, Element& fallback_value) {
		if (type_ == Type::Array || type_ == Type::Object) {
			if (index < children_.size()) {
				return children_[index];
			}
		}

		return fallback_value;
	}

	Element* Element::get_ptr(int index) {
		if (type_ != Type::Array && type_ != Type::Object) {
			throw MazeException("Cannot access array value by index on non-array or non-object element.");
		}

		if (index >= children_.size()) {
			throw MazeException("Array index out of range.");
		}

		return &children_[index];
	}

	const Element& Element::operator[](int index) const {
		return get(index);
	}

	Element& Element::operator[](int index) {
		return get(index);
	}

	void Element::set_array(const std::vector<Element>& val) {
		type_ = Type::Array;
		children_.clear();
		children_keys_.clear();

		children_ = val;
		
		children_keys_.reserve(val.size());
		for (int i = 0; i < val.size(); ++i) {
			const std::string child_key = array_index_prefix_char + std::to_string(children_keys_.size());

			children_[i].set_key(child_key);
			children_keys_[i] = child_key;
		}
	}

	Element& Element::push_back(const Element& value) {
		if (type_ != Type::Array && type_ != Type::Object) {
			throw MazeException("Unable push_back element into non-array or non-object type");
		}

		const std::string child_key = array_index_prefix_char + std::to_string(children_keys_.size());

		if (exists(child_key)) {
			throw MazeException("Unable to determine element index. Values map already contains an element with key " + child_key);
		}

		Element value_copy = value;
		value_copy.set_key(child_key);
		children_keys_.push_back(child_key);
		children_.push_back(value_copy);

		return *this;
	}

	Element& Element::push_back(const std::string& value) {
		return push_back(Element(value));
	}

	Element& Element::push_back(const char* value) {
		return push_back(Element(value));
	}
	
	Element& Element::push_back(bool value) {
		return push_back(Element(value));
	}
	
	Element& Element::push_back(int value) {
		return push_back(Element(value));
	}
	
	Element& Element::push_back(double value) {
		return push_back(Element(value));
	}

	Element& Element::operator<<(const Element& value) {
		return push_back(value);
	}

	Element& Element::operator<<(const std::string& value) {
		return push_back(value);
	}

	Element& Element::operator<<(const char* value) {
		return push_back(value);
	}
	
	Element& Element::operator<<(bool value) {
		return push_back(value);
	}
	
	Element& Element::operator<<(int value) {
		return push_back(value);
	}
	
	Element& Element::operator<<(double value) {
		return push_back(value);
	}

	void Element::remove_at(int index, bool update_string_indexes) {
		if (index >= children_.size()) {
			throw MazeException("Array index out of range.");
		}

		children_.erase(children_.begin() + index);
		children_keys_.erase(children_keys_.begin() + index);

		if (update_string_indexes) {
			for (int i = children_keys_.size() - 1; i > index; --i) {
				std::string key = children_keys_[i];

				if (key.length() > 0 && key[0] == array_index_prefix_char) {
					std::string new_key = array_index_prefix_char + std::to_string(i);

					if (key != new_key) {
						children_keys_[i] = new_key;
					}
				}
			}
		}
	}

	void Element::remove_all_children() {
		children_.clear();
		children_keys_.clear();
	}

	size_t Element::count_children() const {
		return children_keys_.size();
	}

	bool Element::has_children() const {
		return children_keys_.size() > 0;
	}

	const std::vector<Element>& Element::get_children() const {
		return children_;
	}

	const std::vector<Element>::const_iterator Element::begin() const {
		return children_.begin();
	}

	const std::vector<Element>::const_iterator Element::end() const {
		return children_.end();
	}
	
	std::vector<Element>::iterator Element::begin() {
		return children_.begin();
	}
	
	std::vector<Element>::iterator Element::end() {
		return children_.end();
	}
#pragma endregion

#pragma region Object
	const Element& Element::get(const std::string& key) const {
		if (type_ == Type::Object) {
			int value_index = index_of(key);

			if (value_index != -1) {
				return children_[value_index];
			}
		}

		static const Element empty_element_constant = Element();

		return empty_element_constant;
	}

	Element& Element::get(const std::string& key) {
		return *get_ptr(key);
	}

	Element* Element::get_ptr(const std::string& key) {
		if (type_ != Type::Object) {
			throw MazeException("Cannot access object value by key on non-object element.");
		}

		int value_index = index_of(key);

		if (value_index == -1) {
			set(key, Element(Type::Null));

			value_index = index_of(key);
		}

		return &children_[value_index];
	}

	const Element& Element::operator[](const std::string& key) const {
		return get(key);
	}

	const Element& Element::operator[](const char* key) const {
		return get(key);
	}

	Element& Element::operator[](const std::string& key) {
		return get(key);
	}

	Element& Element::operator[](const char* key) {
		return get(key);
	}

	void Element::set_object(const std::vector<std::string>& keys, const std::vector<Element>& values) {
		if (keys.size() != values.size()) {
			throw MazeException("Keys and values do not have the same size.");
		}

		type_ = Type::Object;
		children_.clear();
		children_keys_.clear();

		children_ = values;
		children_keys_ = keys;

		for (int i = 0; i < children_keys_.size(); ++i) {
			children_[i].set_key(children_keys_[i]);
		}
	}

	void Element::set(const std::string& key, const Element& value) {
		if (type_ != Type::Object) {
			throw MazeException("Cannot set element into non-object type.");
		}

		int value_index = index_of(key);
		Element value_copy = value;
		value_copy.set_key(key);

		if (value_index != -1) {
			children_[value_index] = value_copy;
		}
		else {
			children_.push_back(value_copy);
			children_keys_.push_back(key);
		}
	}

	void Element::set(const std::string& key, const std::string& value) {
		set(key, Element(value));
	}

	void Element::set(const std::string& key, const char* value) {
		set(key, Element(value));
	}

	void Element::set(const std::string& key, bool value) {
		set(key, Element(value));
	}

	void Element::set(const std::string& key, int value) {
		set(key, Element(value));
	}

	void Element::set(const std::string& key, double value) {
		set(key, Element(value));
	}

	void Element::remove(const std::string& key, bool update_string_indexes) {
		if (type_ != Type::Object) {
			throw MazeException("Cannot remove an element from non-object type.");
		}

		int value_index = index_of(key);
		if (value_index != -1) {
			children_.erase(children_.begin() + value_index);
			children_keys_.erase(children_keys_.begin() + value_index);

			if (update_string_indexes) {
				for (int i = children_keys_.size() - 1; i > value_index; --i) {
					std::string key = children_keys_[i];

					if (key.length() > 0 && key[0] == array_index_prefix_char) {
						std::string new_key = array_index_prefix_char + std::to_string(i);

						if (key != new_key) {
							children_keys_[i] = new_key;
						}
					}
				}
			}
		}
	}

	bool Element::exists(const std::string& key) const {
		if (children_keys_.size() != children_.size()) {
			throw MazeException("Element corrupted, size of keys is different than size of element vector");
		}

		for (const auto& it : children_keys_) {
			if (it == key)
				return true;
		}

		return false;
	}

	int Element::index_of(const std::string& key) const {
		if (children_keys_.size() != children_keys_.size()) {
			throw MazeException("Element corrupted, size of keys is different than size of element vector");
		}

		for (int i = children_keys_.size() - 1; i >= 0; --i) {
			if (children_keys_[i] == key)
				return i;
		}

		return -1;
	}

	const std::vector<std::string>& Element::get_keys() const {
		return children_keys_;
	}

	const std::vector<std::string>::const_iterator Element::keys_begin() const {
		return children_keys_.begin();
	}

	const std::vector<std::string>::const_iterator Element::keys_end() const {
		return children_keys_.end();
	}

	std::vector<std::string>::iterator Element::keys_begin() {
		return children_keys_.begin();
	}

	std::vector<std::string>::iterator Element::keys_end() {
		return children_keys_.end();
	}
#pragma endregion

#pragma region Type checks
	bool Element::is_null() const {
		return is(Type::Null);
	}

	bool Element::is_bool() const {
		return is(Type::Bool);
	}

	bool Element::is_int() const {
		return is(Type::Int);
	}

	bool Element::is_double() const {
		return is(Type::Double);
	}

	bool Element::is_string() const {
		return is(Type::String);
	}

	bool Element::is_array() const {
		return is(Type::Array);
	}

	bool Element::is_object() const {
		return is(Type::Object);
	}

	bool Element::is(Type type) const {
		return (type_ == type);
	}
	
	bool Element::is_null(int index) const {
		return is(index, Type::Null);
	}

	bool Element::is_bool(int index) const {
		return is(index, Type::Bool);
	}

	bool Element::is_int(int index) const {
		return is(index, Type::Int);
	}

	bool Element::is_double(int index) const {
		return is(index, Type::Double);
	}

	bool Element::is_string(int index) const {
		return is(index, Type::String);
	}

	bool Element::is_array(int index) const {
		return is(index, Type::Array);
	}

	bool Element::is_object(int index) const {
		return is(index, Type::Object);
	}

	bool Element::is(int index, Type type) const {
		return get(index).is(type);
	}

	bool Element::is_null(const std::string& key) const {
		return is(key, Type::Null);
	}

	bool Element::is_bool(const std::string& key) const {
		return is(key, Type::Bool);
	}

	bool Element::is_int(const std::string& key) const {
		return is(key, Type::Int);
	}

	bool Element::is_double(const std::string& key) const {
		return is(key, Type::Double);
	}

	bool Element::is_string(const std::string& key) const {
		return is(key, Type::String);
	}

	bool Element::is_array(const std::string& key) const {
		return is(key, Type::Array);
	}

	bool Element::is_object(const std::string& key) const {
		return is(key, Type::Object);
	}

	bool Element::is(const std::string& key, Type type) const {
		return get(key).is(type);
	}
#pragma endregion

	void Element::apply(const Element& new_element) {
		switch (new_element.get_type()) {
		case Type::Null:
			set_as_null();
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
			set_array(new_element.get_children());
			break;
		case Type::Object:
			set_object(new_element.get_keys(), new_element.get_children());
			break;
		}
	}

	std::string Element::to_json(int spacing) const {
		return Helpers::Element::to_json_element(this).dump(spacing);
	}

	void Element::apply_json(const std::string& json_string) {
		Helpers::Element::apply_json(*this, nlohmann::json::parse(json_string));
	}

	Element Element::from_json(const std::string& json_string) {
		return Helpers::Element::from_json(nlohmann::json::parse(json_string));
	}

	const Element& Element::get_null_element() {
		static const Element null_element = Element(Type::Null);

		return null_element;
	}
}  // namespace Maze
