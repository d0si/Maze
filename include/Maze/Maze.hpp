#pragma once

#include <string>
#include <memory>
#include <vector>

#define MAZE_ARRAY_INDEX_PREFIX_CHAR '~'

namespace Maze {

    const std::string& get_version();


    enum class Type {
        Null = 0,
        Bool = 1,
        Int = 2,
        Double = 3,
        String = 4,
        Array = 5,
        Object = 6,
        Function = 7
    };

    const std::string& to_string(const Type& type);


    class MazeException : public std::exception {
    public:
        inline MazeException(const std::string& message)
            : _message(message) {}

        inline const char* what() const noexcept override {
            return _message.c_str();
        }

    protected:
        const std::string _message;
    };


    class Element;
    typedef Element(*FunctionCallback) (const Element& value);


    class Element {
    public:
#pragma region Constructors/destructor

        inline Element() { set_as_null(); }
        inline Element(const Element& val) { copy_from_element(val); }
        inline Element(bool val) { set_bool(val); }
        inline Element(int val) { set_int(val); }
        inline Element(double val) { set_double(val); }
        inline Element(const std::string& val) { set_string(val); }
        inline Element(const char* val) { set_string(val); }
        inline Element(const std::vector<Element>& val) { set_array(val); }
        inline Element(const std::vector<std::string>& keys, const std::vector<Element>& val) { set_object(keys, val); }
        inline Element(FunctionCallback callback) { set_function(callback); }
        inline Element(Type val) { set_type(val); }
        inline ~Element() {}

#pragma endregion


        inline void operator=(const Element& val) { copy_from_element(val); }
        void copy_from_element(const Element& val);

        void set_type(const Type& type);
        inline const Type& get_type() const { return _type; }
        inline Type& get_type_ref() { return _type; }

        inline void set_key(const std::string& key) { _val_key = key; }
        inline const std::string& get_key() const { return _val_key; }
        inline std::string& get_key_ref() { return _val_key; }

        void set_as_null(bool clear_existing_values = true);


#pragma region Boolean

        //   Getters
        inline bool b() const { return get_bool(); }
        inline operator bool() const { return get_bool(); }
        inline bool get_bool() const { return get_bool(false); }
        bool get_bool(bool fallback_value) const;
        bool& get_bool_ref();

        //   Setters
        inline void b(bool val) { set_bool(val); }
        inline void operator=(bool val) { set_bool(val); }
        inline void set_bool(bool val) { _val_bool = val; _type = Type::Bool; }

#pragma endregion


#pragma region Integer

        //   Getters
        inline int i() const { return get_int(); }
        inline operator int() const { return get_int(); }
        inline int get_int() const { return get_int(0); }
        int get_int(int fallback_value) const;
        int& get_int_ref();

        //   Setters
        inline void i(int val) { set_int(val); }
        inline void operator=(int val) { set_int(val); }
        inline void set_int(int val) { _val_int = val; _type = Type::Int; }

#pragma endregion

#pragma region Double

        //   Getters
        inline double d() const { return get_double(); }
        inline operator double() const { return get_double(); }
        inline double get_double() const { return get_double(0); }
        double get_double(double fallback_value) const;
        double& get_double_ref();

        //   Setters
        inline void d(double val) { set_double(val); }
        inline void operator=(double val) { set_double(val); }
        inline void set_double(double val) { _val_double = val; _type = Type::Double; }

#pragma endregion


#pragma region String

        //   Getters
        inline const std::string& s() const { return get_string(); }
        inline operator const std::string& () const { return get_string(); }
        const std::string& get_string() const;
        const std::string& get_string_const_ref(const std::string& fallback_value) const;
        std::string get_string(const std::string& fallback_value) const;
        std::string& get_string_ref();

        //   Setters
        inline void s(const std::string& val) { set_string(val); }
        inline void operator=(const std::string& val) { set_string(val); }
        inline void operator=(const char* val) { set_string(val); }
        inline void set_string(const std::string& val) { _val_string = val; _type = Type::String; }

#pragma endregion


#pragma region Array

        static const char array_index_prefix_char = MAZE_ARRAY_INDEX_PREFIX_CHAR;

        //   Getters
        inline const Element& operator[](int index) const { return get(index); }
        const Element& get(int index) const;
        const Element& get_const_ref(int index, const Element& fallback_value) const;
        Element get(int index, const Element& fallback_value) const;
        inline Element& operator[](int index) { return get_ref(index); }
        inline Element& get_ref(int index) { return *get_ptr(index); }
        Element* get_ptr(int index);

        //   Setters
        void set_array(const std::vector<Element>& val);
        inline Element& operator<<(const std::string& value) { return push_back(value); }
        inline Element& operator<<(const char* value) { return push_back(value); }
        inline Element& operator<<(bool value) { return push_back(value); }
        inline Element& operator<<(int value) { return push_back(value); }
        inline Element& operator<<(double value) { return push_back(value); }
        inline Element& operator<<(const Element& value) { return push_back(value); }
        inline Element& push_back(const std::string& value) { return push_back(Element(value)); }
        inline Element& push_back(const char* value) { return push_back(Element(value)); }
        inline Element& push_back(bool value) { return push_back(Element(value)); }
        inline Element& push_back(int value) { return push_back(Element(value)); }
        inline Element& push_back(double value) { return push_back(Element(value)); }
        Element& push_back(const Element& value);

        void remove_at(int index, bool update_string_indexes = true);
        inline void remove_all_children() { _children.clear(); _children_keys.clear(); }
        inline size_t count_children() const { return _children_keys.size(); }
        inline bool has_children() const { return _children_keys.size() > 0; }
        inline const std::vector<Element>& get_children() const { return _children; }

        inline const std::vector<Element>::const_iterator begin() const { return _children.begin(); }
        inline const std::vector<Element>::const_iterator end() const { return _children.end(); }
        inline std::vector<Element>::iterator begin() { return _children.begin(); }
        inline std::vector<Element>::iterator end() { return _children.end(); }

#pragma endregion


#pragma region Object

        //   Getters
        inline const Element& operator[](const std::string& key) const { return get(key); }
        inline const Element& operator[](const char* key) const { return get(key); }
        const Element& get(const std::string& key) const;
        const Element& get_const_ref(const std::string& key, const Element& fallback_value) const;
        Element get(const std::string& key, const Element& fallback_value) const;
        inline Element& operator[](const std::string& key) { return get_ref(key); }
        inline Element& operator[](const char* key) { return get_ref(key); }
        inline Element& get_ref(const std::string& key) { return *get_ptr(key); }
        Element* get_ptr(const std::string& key);

        //   Setters
        void set_object(const std::vector<std::string>& keys, const std::vector<Element>& values);
        inline void set(const std::string& key, const std::string& value) { set(key, Element(value)); }
        inline void set(const std::string& key, const char* value) { set(key, Element(value)); }
        inline void set(const std::string& key, bool value) { set(key, Element(value)); }
        inline void set(const std::string& key, int value) { set(key, Element(value)); }
        inline void set(const std::string& key, double value) { set(key, Element(value)); }
        void set(const std::string& key, const Element& value);

        void remove(const std::string& key, bool update_string_indexes = true);
        bool exists(const std::string& key) const;
        int index_of(const std::string& key) const;
        inline const std::vector<std::string>& get_keys() const { return _children_keys; }

        inline const std::vector<std::string>::const_iterator keys_begin() const { return _children_keys.begin(); }
        inline const std::vector<std::string>::const_iterator keys_end() const { return _children_keys.end(); }
        inline std::vector<std::string>::iterator keys_begin() { return _children_keys.begin(); }
        inline std::vector<std::string>::iterator keys_end() { return _children_keys.end(); }

#pragma endregion


#pragma region Function

        inline void set_function(FunctionCallback callback) { _callback = callback; _type = Type::Function; }

        inline Element e(const Element& value) const { return execute_function(value); }
        Element execute_function(const Element& value) const;

        inline FunctionCallback get_callback() const { return _callback; }

#pragma endregion

#pragma region Type checks

        inline bool is_null() const { return is(Type::Null); }
        inline bool is_bool() const { return is(Type::Bool); }
        inline bool is_int() const { return is(Type::Int); }
        inline bool is_double() const { return is(Type::Double); }
        inline bool is_string() const { return is(Type::String); }
        inline bool is_array() const { return is(Type::Array); }
        inline bool is_object() const { return is(Type::Object); }
        inline bool is_function() const { return is(Type::Function); }
        inline bool is(Type type) const { return _type == type; }

        inline bool is_null(int index) const { return is(index, Type::Null); }
        inline bool is_bool(int index) const { return is(index, Type::Bool); }
        inline bool is_int(int index) const { return is(index, Type::Int); }
        inline bool is_double(int index) const { return is(index, Type::Double); }
        inline bool is_string(int index) const { return is(index, Type::String); }
        inline bool is_array(int index) const { return is(index, Type::Array); }
        inline bool is_object(int index) const { return is(index, Type::Object); }
        inline bool is_function(int index) const { return is(index, Type::Function); }
        inline bool is(int index, Type type) const { return get(index).is(type); }

        inline bool is_null(const std::string& key) const { return is(key, Type::Null); }
        inline bool is_bool(const std::string& key) const { return is(key, Type::Bool); }
        inline bool is_int(const std::string& key) const { return is(key, Type::Int); }
        inline bool is_double(const std::string& key) const { return is(key, Type::Double); }
        inline bool is_string(const std::string& key) const { return is(key, Type::String); }
        inline bool is_array(const std::string& key) const { return is(key, Type::Array); }
        inline bool is_object(const std::string& key) const { return is(key, Type::Object); }
        inline bool is_function(const std::string& key) const { return is(key, Type::Function); }
        inline bool is(const std::string& key, Type type) const { return get(key).is(type); }

#pragma endregion


        void apply(const Element& new_element);

        std::string to_json(int indentation_spacing = 2) const;

        void apply_json(const std::string& json_string);

        static Element from_json(const std::string& json_string);

        static const Element& get_null_element();

    protected:
        Type _type = Type::Null;

        bool _val_bool;
        int _val_int;
        double _val_double;
        std::string _val_string;
        std::vector<std::string> _children_keys;
        std::vector<Element> _children;
        FunctionCallback _callback;

        std::string _val_key;
    };

}  // namespace Maze
