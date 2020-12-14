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

    Element::Element(FunctionCallback callback) {
        set_function(callback);
    }

    Element::Element(Type type) {
        set_type(type);
    }

    Element::~Element() {}

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
        case Type::Function:
            set_function(val.get_callback());
            break;
        default:
            set_as_null();
            break;
        }
    }

    void Element::operator=(const Element& val) {
        copy_from_element(val);
    }

    void Element::set_type(const Type& type) {
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

    const Type& Element::get_type() const {
        return _type;
    }

    Type& Element::get_type_ref() {
        return _type;
    }

    void Element::set_key(const std::string& key) {
        _val_key = key;
    }

    const std::string& Element::get_key() const {
        return _val_key;
    }

    std::string& Element::get_key_ref() {
        return _val_key;
    }

    void Element::set_as_null(bool clear_existing_values) {
        _type = Type::Null;

        if (clear_existing_values) {
            _val_bool = false;
            _val_int = 0;
            _val_double = 0;
            _val_string = "";
            _children.clear();
            _children_keys.clear();
        }
    }

#pragma region Boolean

    bool Element::b() const {
        return get_bool();
    }

    Element::operator bool() const {
        return get_bool();
    }

    bool Element::get_bool() const {
        return get_bool(false);
    }

    bool Element::get_bool(bool fallback_value) const {
        if (_type == Type::Bool)
            return _val_bool;

        return fallback_value;
    }

    bool& Element::get_bool_ref() {
        if (_type != Type::Bool)
            throw MazeException("Cannot get reference to bool value from a non-bool element. Use set_bool instead to set value and change type.");

        return _val_bool;
    }


    void Element::b(bool val) {
        set_bool(val);
    }

    void Element::operator=(bool val) {
        set_bool(val);
    }

    void Element::set_bool(bool val) {
        _val_bool = val;
        _type = Type::Bool;
    }


#pragma endregion


#pragma region Integer

    int Element::i() const {
        return get_int();
    }

    Element::operator int() const {
        return get_int();
    }

    int Element::get_int() const {
        return get_int(0);
    }

    int Element::get_int(int fallback_value) const {
        if (_type == Type::Int)
            return _val_int;

        return fallback_value;
    }

    int& Element::get_int_ref() {
        if (_type != Type::Int)
            throw MazeException("Cannot get reference to int value from a non-int element. Use set_int instead to set value and change type.");

        return _val_int;
    }


    void Element::i(int val) {
        set_int(val);
    }

    void Element::operator=(int val) {
        set_int(val);
    }

    void Element::set_int(int val) {
        _val_int = val;
        _type = Type::Int;
    }

#pragma endregion


#pragma region Double

    double Element::d() const {
        return get_double();
    }

    double Element::get_double() const {
        return get_double(0);
    }

    Element::operator double() const {
        return get_double();
    }

    double Element::get_double(double fallback_value) const {
        if (_type == Type::Double)
            return _val_double;

        return fallback_value;
    }

    double& Element::get_double_ref() {
        if (_type != Type::Double)
            throw MazeException("Cannot get reference to double value from a non-double element. Use set_double instead to set value and change type.");

        return _val_double;
    }


    void Element::d(double val) {
        set_double(val);
    }

    void Element::operator=(double val) {
        set_double(val);
    }

    void Element::set_double(double val) {
        _val_double = val;
        _type = Type::Double;
    }

#pragma endregion


#pragma region String

    const std::string& Element::s() const {
        return get_string();
    }

    Element::operator const std::string& () const {
        return get_string();
    }

    const std::string& Element::get_string() const {
        static const std::string empty_string_constant = "";

        return get_string_const_ref(empty_string_constant);
    }

    const std::string& Element::get_string_const_ref(const std::string& fallback_value) const {
        if (_type == Type::String)
            return _val_string;

        return fallback_value;
    }

    std::string Element::get_string(const std::string& fallback_value) const {
        if (_type == Type::String)
            return _val_string;

        return fallback_value;
    }

    std::string& Element::get_string_ref() {
        if (_type != Type::String)
            throw MazeException("Cannot get reference to string value from a non-string element. Use set_string instead to set value and change type.");

        return _val_string;
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

    void Element::set_string(const std::string& val) {
        _val_string = val;
        _type = Type::String;
    }

#pragma endregion

#pragma region Array

    const Element& Element::operator[](int index) const {
        return get(index);
    }

    const Element& Element::get(int index) const {
        static const Element empty_element_constant = Element();

        return get_const_ref(index, empty_element_constant);
    }

    const Element& Element::get_const_ref(int index, const Element& fallback_value) const {
        if ((_type == Type::Array || _type == Type::Object) && index < _children.size())
            return _children[index];

        return fallback_value;
    }

    Element Element::get(int index, const Element& fallback_value) const {
        if ((_type == Type::Array || _type == Type::Object) && index < _children.size())
            return _children[index];

        return fallback_value;
    }

    Element& Element::operator[](int index) {
        return get_ref(index);
    }

    Element& Element::get_ref(int index) {
        return *get_ptr(index);
    }

    Element* Element::get_ptr(int index) {
        if (_type != Type::Array && _type != Type::Object)
            throw MazeException("Cannot access array value by index on non-array or non-object element.");

        if (index >= _children.size())
            throw MazeException("Array index out of range.");

        return &_children[index];
    }


    void Element::set_array(const std::vector<Element>& val) {
        _type = Type::Array;
        _children.clear();
        _children_keys.clear();

        _children = val;

        _children_keys.reserve(val.size());
        for (int i = 0; i < val.size(); ++i) {
            const std::string child_key = array_index_prefix_char + std::to_string(_children_keys.size());

            _children[i].set_key(child_key);
            _children_keys.push_back(child_key);
        }
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

    Element& Element::operator<<(const Element& value) {
        return push_back(value);
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

    Element& Element::push_back(const Element& value) {
        if (_type != Type::Array && _type != Type::Object)
            throw MazeException("Unable push_back element into non-array or non-object type");

        const std::string child_key = array_index_prefix_char + std::to_string(_children_keys.size());

        if (exists(child_key))
            throw MazeException("Unable to determine element index. Values map already contains an element with key " + child_key);

        Element value_copy = value;
        value_copy.set_key(child_key);
        _children_keys.push_back(child_key);
        _children.push_back(value_copy);

        return *this;
    }


    void Element::remove_at(int index, bool update_string_indexes) {
        if (index >= _children.size())
            throw MazeException("Array index out of range.");

        _children.erase(_children.begin() + index);
        _children_keys.erase(_children_keys.begin() + index);

        if (update_string_indexes) {
            for (int i = (int)_children_keys.size() - 1; i > index; --i) {
                const std::string& key = _children_keys[i];

                if (key.length() > 0 && key[0] == array_index_prefix_char) {
                    const std::string new_key = array_index_prefix_char + std::to_string(i);

                    if (key != new_key) {
                        _children_keys[i] = new_key;
                    }
                }
            }
        }
    }

    void Element::remove_all_children() {
        _children.clear();
        _children_keys.clear();
    }

    size_t Element::count_children() const {
        return _children_keys.size();
    }

    bool Element::has_children() const {
        return _children_keys.size() > 0;
    }

    const std::vector<Element>& Element::get_children() const {
        return _children;
    }

    const std::vector<Element>::const_iterator Element::begin() const {
        return _children.begin();
    }

    const std::vector<Element>::const_iterator Element::end() const {
        return _children.end();
    }

    std::vector<Element>::iterator Element::begin() {
        return _children.begin();
    }

    std::vector<Element>::iterator Element::end() {
        return _children.end();
    }

#pragma endregion


#pragma region Object

    const Element& Element::operator[](const std::string& key) const {
        return get(key);
    }

    const Element& Element::operator[](const char* key) const {
        return get(key);
    }

    const Element& Element::get(const std::string& key) const {
        static const Element empty_element_constant = Element();

        return get_const_ref(key, empty_element_constant);
    }

    const Element& Element::get_const_ref(const std::string& key, const Element& fallback_value) const {
        if (_type == Type::Object) {
            int value_index = index_of(key);

            if (value_index != -1) {
                return _children[value_index];
            }
        }

        return fallback_value;
    }

    Element Element::get(const std::string& key, const Element& fallback_value) const {
        if (_type == Type::Object) {
            int value_index = index_of(key);

            if (value_index != -1)
                return _children[value_index];
        }

        return fallback_value;
    }

    Element& Element::operator[](const std::string& key) {
        return get_ref(key);
    }

    Element& Element::operator[](const char* key) {
        return get_ref(key);
    }

    Element& Element::get_ref(const std::string& key) {
        return *get_ptr(key);
    }

    Element* Element::get_ptr(const std::string& key) {
        if (_type != Type::Object)
            throw MazeException("Cannot access object value by key on non-object element.");

        int value_index = index_of(key);

        if (value_index == -1) {
            set(key, Element(Type::Null));

            value_index = index_of(key);
        }

        return &_children[value_index];
    }


    void Element::set_object(const std::vector<std::string>& keys, const std::vector<Element>& values) {
        if (keys.size() != values.size())
            throw MazeException("Keys and values do not have the same size.");

        _type = Type::Object;
        _children.clear();
        _children_keys.clear();

        _children = values;
        _children_keys = keys;

        for (int i = 0; i < _children_keys.size(); ++i) {
            _children[i].set_key(_children_keys[i]);
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

    void Element::set(const std::string& key, const Element& value) {
        if (_type != Type::Object)
            throw MazeException("Cannot set element into non-object type.");

        int value_index = index_of(key);
        Element value_copy = value;
        value_copy.set_key(key);

        if (value_index != -1) {
            _children[value_index] = value_copy;
        }
        else {
            _children.push_back(value_copy);
            _children_keys.push_back(key);
        }
    }


    void Element::remove(const std::string& key, bool update_string_indexes) {
        if (_type != Type::Object)
            throw MazeException("Cannot remove an element from non-object type.");

        int value_index = index_of(key);
        if (value_index != -1) {
            _children.erase(_children.begin() + value_index);
            _children_keys.erase(_children_keys.begin() + value_index);

            if (update_string_indexes) {
                for (int i = (int)_children_keys.size() - 1; i > value_index; --i) {
                    std::string key = _children_keys[i];

                    if (key.length() > 0 && key[0] == array_index_prefix_char) {
                        std::string new_key = array_index_prefix_char + std::to_string(i);

                        if (key != new_key) {
                            _children_keys[i] = new_key;
                        }
                    }
                }
            }
        }
    }

    bool Element::exists(const std::string& key) const {
        if (_children_keys.size() != _children.size())
            throw MazeException("Element corrupted, size of keys is different than size of element vector");

        for (const auto& it : _children_keys) {
            if (it == key)
                return true;
        }

        return false;
    }

    int Element::index_of(const std::string& key) const {
        if (_children_keys.size() != _children_keys.size())
            throw MazeException("Element corrupted, size of keys is different than size of element vector");

        for (int i = (int)_children_keys.size() - 1; i >= 0; --i) {
            if (_children_keys[i] == key)
                return i;
        }

        return -1;
    }

    const std::vector<std::string>& Element::get_keys() const {
        return _children_keys;
    }

    const std::vector<std::string>::const_iterator Element::keys_begin() const {
        return _children_keys.begin();
    }

    const std::vector<std::string>::const_iterator Element::keys_end() const {
        return _children_keys.end();
    }

    std::vector<std::string>::iterator Element::keys_begin() {
        return _children_keys.begin();
    }

    std::vector<std::string>::iterator Element::keys_end() {
        return _children_keys.end();
    }

#pragma endregion


#pragma region Function

    void Element::set_function(FunctionCallback callback) {
        _type = Type::Function;
        _callback = callback;
    }

    Element Element::execute_function(const Element& value) const {
        if (_type == Type::Function)
            return _callback(value);

        return Element();
    }

    Element Element::e(const Element& value) const {
        return execute_function(value);
    }

    FunctionCallback Element::get_callback() const {
        return _callback;
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

    bool Element::is_function() const {
        return is(Type::Function);
    }

    bool Element::is(Type type) const {
        return (_type == type);
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

    bool Element::is_function(int index) const {
        return is(index, Type::Function);
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

    bool Element::is_function(const std::string& key) const {
        return is(key, Type::Function);
    }

    bool Element::is(const std::string& key, Type type) const {
        return get(key).is(type);
    }
#pragma endregion

    void Element::apply(const Element& new_element) {
        switch (new_element.get_type()) {
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
            if (_type == Type::Object) {
                for (const std::string& key : new_element._children_keys) {
                    if (exists(key)) {
                        get_ref(key).apply(new_element.get(key));
                    }
                    else {
                        set(key, new_element.get(key));
                    }
                }
            }
            else {
                set_object(new_element.get_keys(), new_element.get_children());
            }
            break;
        case Type::Function:
            set_function(new_element.get_callback());
            break;
        default:
            set_as_null();
        }
    }

    std::string Element::to_json(int spacing) const {
        return Helpers::Element::to_json_element(*this).dump(spacing);
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
