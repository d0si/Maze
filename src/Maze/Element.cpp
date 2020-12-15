#include <Maze/Maze.hpp>
#include <Maze/Helpers.hpp>
#include <nlohmann/json.hpp>

namespace Maze {

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

#pragma endregion


#pragma region Integer

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

#pragma endregion


#pragma region Double

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

#pragma endregion


#pragma region String

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

#pragma endregion

#pragma region Array

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

#pragma endregion


#pragma region Object

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

#pragma endregion


#pragma region Function

    Element Element::execute_function(const Element& value) const {
        if (_type == Type::Function)
            return _callback(value);

        return Element();
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
