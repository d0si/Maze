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

	Element::Element(const Array& val) {
		set_array(val);
	}

	Element::Element(const Object& val) {
		set_object(val);
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
			set_array(val.get_array());
			break;
		case Type::Object:
			set_object(val.get_object());
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
			set_array(Array());
			break;
		case Type::Object:
			set_object(Object());
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
			ptr_array_.reset();
			ptr_object_.reset();
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
	const Array& Element::get_array() const {
		if (type_ == Type::Array) {
			return *ptr_array_;
		}

		static const Array empty_array_constant = Array();

		return empty_array_constant;
	}

	const Array& Element::a() const {
		return get_array();
	}

	Array& Element::a() {
		if (type_ != Type::Array) {
			throw MazeException("Cannot get reference to array value from a non-arrary element. Use set_array instead to set value and change type.");
		}

		return *ptr_array_;
	}

	Array* Element::a_ptr() const {
		return ptr_array_.get();
	}

	Element::operator Array() const {
		return get_array();
	}

	void Element::set_array(const Array& val) {
		ptr_array_ = std::make_unique<Array>(val);
		type_ = Type::Array;
	}

	void Element::a(const Array& val) {
		set_array(val);
	}

	void Element::operator=(const Array& val) {
		set_array(val);
	}

	void Element::push_back(const Element& value) {
		if (element_map_.find(std::to_string(element_map_.size())) != element_map_.end()) {
			// We have a problem. An index based key was used to set the value that is not at its index.
			throw MazeException("Unable to determine element index. Values map already contains an element with key " + std::to_string(element_map_.size()));
		}

		element_map_[/*array_index_prefix_char + */std::to_string(element_map_.size())] = std::make_unique<Element>(value);
	}

	const Element& Element::get(int index) const {
		if (type_ == Type::Array || type_ == Type::Object) {
			if (index < element_map_.size()) {
				return *(element_map_.begin(index)->second);
			}
		}

		static const Element empty_element_constant = Element();

		return empty_element_constant;
	}

	/*Element& Element::get(int index) {
		if (type_ != Type::Array && type_ != Type::Object) {
			throw MazeException("Cannot access array value by index on non-array or non-object element.");
		}

		if (index < element_map_.size()) {
			return element_map_.begin(index)->second;
		}

		throw MazeException("Array index out of range.");
	}*/

	void Element::remove_at(int index/*, bool update_string_indexes*/) {
		if (index >= element_map_.size()) {
			throw MazeException("Array index out of range.");
		}

		// TODO
		// ElementMap::local_iterator it = element_map_.begin(index);
		// element_map_.erase(it);

		/*if (update_string_indexes) {
			int current_index = 0;

			for (auto& it : element_map_) {
				if (it.first.length() > 0 && it.first[0] == array_index_prefix_char) {
					auto el = element_map_.extract(it.first);
					el.key() = array_index_prefix_char + current_index;
					element_map_.insert(std::move(el));
				}

				++current_index;
			}
		}*/
	}
#pragma endregion

#pragma region Object
	const Object& Element::get_object() const {
		if (type_ == Type::Object) {
			return *ptr_object_;
		}

		static const Object empty_object_constant = Object();

		return empty_object_constant;
	}

	const Object& Element::o() const {
		return get_object();
	}

	Object& Element::o() {
		if (type_ != Type::Object) {
			throw MazeException("Cannot get reference to object value from a non-object element. Use set_object instead to set value and change type.");
		}

		return *ptr_object_;
	}

	Object* Element::o_ptr() const {
		return ptr_object_.get();
	}

	Element::operator Object() const {
		return get_object();
	}

	void Element::set_object(const Object& val) {
		ptr_object_ = std::make_unique<Object>(val);
		type_ = Type::Object;
	}

	void Element::o(const Object& val) {
		set_object(val);
	}

	void Element::operator=(const Object& val) {
		set_object(val);
	}


	void Element::set(const std::string& key, const Element& value) {
		if (type_ != Type::Object) {
			throw MazeException("Cannot set element into non-object type.");
		}

		element_map_[key] = std::make_unique<Element>(value);
	}

	const Element& Element::get(const std::string& key) const {
		if (type_ == Type::Object) {
			const auto& it = element_map_.find(key);
			if (it != element_map_.end()) {
				return *(it->second);
			}
		}

		static const Element empty_element_constant = Element();

		return empty_element_constant;
	}

	void Element::remove(const std::string& key) {
		if (type_ != Type::Object) {
			throw MazeException("Cannot remove an element from non-object type.");
		}

		const auto& it = element_map_.find(key);
		if (it != element_map_.end()) {
			element_map_.erase(it);
		}
	}

	bool Element::exists(const std::string& key) const {
		return element_map_.find(key) != element_map_.end();
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
			set_array(new_element.get_array());
			break;
		case Type::Object:
			ptr_object_->apply(new_element.get_object());
			break;
		}
	}

	std::string Element::to_json(int spacing) const {
		return Helpers::Element::to_json_element(this).dump(spacing);
	}

	void Element::apply_json(const std::string& json_string) {
		Helpers::Element::apply_json(this, nlohmann::json::parse(json_string));
	}

	Element Element::from_json(const std::string& json_string) {
		return Helpers::Element::from_json(nlohmann::json::parse(json_string));
	}

	const Element& Element::get_null_element() {
		static const Element null_element = Element(Type::Null);

		return null_element;
	}
}  // namespace Maze
