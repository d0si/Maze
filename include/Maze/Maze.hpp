#pragma once

#include <string>
#include <memory>
#include <vector>
#include <Maze/DLLSupport.hpp>

#define MAZE_ARRAY_INDEX_PREFIX_CHAR '~'

namespace Maze {
    
    MAZE_API const std::string& get_version();


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

    MAZE_API const std::string& to_string(const Type& type);


    class MazeException : public std::exception {
    public:
        MAZE_API inline MazeException(const std::string& message)
            : _message(message) {}

        MAZE_API inline const char* what() const noexcept override {
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

        MAZE_API inline Element() { set_as_null(); }
        MAZE_API inline Element(const Element& val) { copy_from_element(val); }
        MAZE_API inline Element(bool val) { set_bool(val); }
        MAZE_API inline Element(int val) { set_int(val); }
        MAZE_API inline Element(double val) { set_double(val); }
        MAZE_API inline Element(const std::string& val) { set_string(val); }
        MAZE_API inline Element(const char* val) { set_string(val); }
        MAZE_API inline Element(const std::vector<Element>& val) { set_array(val); }
        MAZE_API inline Element(const std::vector<std::string>& keys, const std::vector<Element>& val) { set_object(keys, val); }
        MAZE_API inline Element(FunctionCallback callback) { set_function(callback); }
        MAZE_API inline Element(Type val) { set_type(val); }
        MAZE_API inline ~Element() {}

#pragma endregion


        MAZE_API inline void operator=(const Element& val) { copy_from_element(val); }
        MAZE_API void copy_from_element(const Element& val);

        MAZE_API void set_type(const Type& type);
        MAZE_API inline const Type& get_type() const { return _type; }
        MAZE_API inline Type& get_type_ref() { return _type; }

        MAZE_API inline void set_key(const std::string& key) { _val_key = key; }
        MAZE_API inline const std::string& get_key() const { return _val_key; }
        MAZE_API inline std::string& get_key_ref() { return _val_key; }

        MAZE_API void set_as_null(bool clear_existing_values = true);


#pragma region Boolean

        //   Getters
        MAZE_API inline bool b() const { return get_bool(); }
        MAZE_API inline operator bool() const { return get_bool(); }
        MAZE_API inline bool get_bool() const { return get_bool(false); }
        MAZE_API bool get_bool(bool fallback_value) const;
        MAZE_API bool& get_bool_ref();

        //   Setters
        MAZE_API inline void b(bool val) { set_bool(val); }
        MAZE_API inline void operator=(bool val) { set_bool(val); }
        MAZE_API inline void set_bool(bool val) { _val_bool = val; _type = Type::Bool; }

#pragma endregion


#pragma region Integer

        //   Getters
        MAZE_API inline int i() const { return get_int(); }
        MAZE_API inline operator int() const { return get_int(); }
        MAZE_API inline int get_int() const { return get_int(0); }
        MAZE_API int get_int(int fallback_value) const;
        MAZE_API int& get_int_ref();

        //   Setters
        MAZE_API inline void i(int val) { set_int(val); }
        MAZE_API inline void operator=(int val) { set_int(val); }
        MAZE_API inline void set_int(int val) { _val_int = val; _type = Type::Int; }

#pragma endregion

#pragma region Double

        //   Getters
        MAZE_API inline double d() const { return get_double(); }
        MAZE_API inline operator double() const { return get_double(); }
        MAZE_API inline double get_double() const { return get_double(0); }
        MAZE_API double get_double(double fallback_value) const;
        MAZE_API double& get_double_ref();

        //   Setters
        MAZE_API inline void d(double val) { set_double(val); }
        MAZE_API inline void operator=(double val) { set_double(val); }
        MAZE_API inline void set_double(double val) { _val_double = val; _type = Type::Double; }

#pragma endregion


#pragma region String

        //   Getters
        MAZE_API inline const std::string& s() const { return get_string(); }
        MAZE_API inline operator const std::string& () const { return get_string(); }
        MAZE_API const std::string& get_string() const;
        MAZE_API const std::string& get_string_const_ref(const std::string& fallback_value) const;
        MAZE_API std::string get_string(const std::string& fallback_value) const;
        MAZE_API std::string& get_string_ref();

        //   Setters
        MAZE_API inline void s(const std::string& val) { set_string(val); }
        MAZE_API inline void operator=(const std::string& val) { set_string(val); }
        MAZE_API inline void operator=(const char* val) { set_string(val); }
        MAZE_API inline void set_string(const std::string& val) { _val_string = val; _type = Type::String; }

#pragma endregion


#pragma region Array

        static const char array_index_prefix_char = MAZE_ARRAY_INDEX_PREFIX_CHAR;

        //   Getters
        MAZE_API inline const Element& operator[](int index) const { return get(index); }
        MAZE_API const Element& get(int index) const;
        MAZE_API const Element& get_const_ref(int index, const Element& fallback_value) const;
        MAZE_API Element get(int index, const Element& fallback_value) const;
        MAZE_API inline Element& operator[](int index) { return get_ref(index); }
        MAZE_API inline Element& get_ref(int index) { return *get_ptr(index); }
        MAZE_API Element* get_ptr(int index);

        //   Setters
        MAZE_API void set_array(const std::vector<Element>& val);
        MAZE_API inline Element& operator<<(const std::string& value) { return push_back(value); }
        MAZE_API inline Element& operator<<(const char* value) { return push_back(value); }
        MAZE_API inline Element& operator<<(bool value) { return push_back(value); }
        MAZE_API inline Element& operator<<(int value) { return push_back(value); }
        MAZE_API inline Element& operator<<(double value) { return push_back(value); }
        MAZE_API inline Element& operator<<(const Element& value) { return push_back(value); }
        MAZE_API inline Element& push_back(const std::string& value) { return push_back(Element(value)); }
        MAZE_API inline Element& push_back(const char* value) { return push_back(Element(value)); }
        MAZE_API inline Element& push_back(bool value) { return push_back(Element(value)); }
        MAZE_API inline Element& push_back(int value) { return push_back(Element(value)); }
        MAZE_API inline Element& push_back(double value) { return push_back(Element(value)); }
        MAZE_API Element& push_back(const Element& value);

        MAZE_API void remove_at(int index, bool update_string_indexes = true);
        MAZE_API inline void remove_all_children() { _children.clear(); _children_keys.clear(); }
        MAZE_API inline size_t count_children() const { return _children_keys.size(); }
        MAZE_API inline bool has_children() const { return _children_keys.size() > 0; }
        MAZE_API inline const std::vector<Element>& get_children() const { return _children; }

        MAZE_API inline const std::vector<Element>::const_iterator begin() const { return _children.begin(); }
        MAZE_API inline const std::vector<Element>::const_iterator end() const { return _children.end(); }
        MAZE_API inline std::vector<Element>::iterator begin() { return _children.begin(); }
        MAZE_API inline std::vector<Element>::iterator end() { return _children.end(); }

#pragma endregion


#pragma region Object

        //   Getters
        MAZE_API inline const Element& operator[](const std::string& key) const { return get(key); }
        MAZE_API inline const Element& operator[](const char* key) const { return get(key); }
        MAZE_API const Element& get(const std::string& key) const;
        MAZE_API const Element& get_const_ref(const std::string& key, const Element& fallback_value) const;
        MAZE_API Element get(const std::string& key, const Element& fallback_value) const;
        MAZE_API inline Element& operator[](const std::string& key) { return get_ref(key); }
        MAZE_API inline Element& operator[](const char* key) { return get_ref(key); }
        MAZE_API inline Element& get_ref(const std::string& key) { return *get_ptr(key); }
        MAZE_API Element* get_ptr(const std::string& key);

        //   Setters
        MAZE_API void set_object(const std::vector<std::string>& keys, const std::vector<Element>& values);
        MAZE_API inline void set(const std::string& key, const std::string& value) { set(key, Element(value)); }
        MAZE_API inline void set(const std::string& key, const char* value) { set(key, Element(value)); }
        MAZE_API inline void set(const std::string& key, bool value) { set(key, Element(value)); }
        MAZE_API inline void set(const std::string& key, int value) { set(key, Element(value)); }
        MAZE_API inline void set(const std::string& key, double value) { set(key, Element(value)); }
        MAZE_API void set(const std::string& key, const Element& value);

        MAZE_API void remove(const std::string& key, bool update_string_indexes = true);
        MAZE_API bool exists(const std::string& key) const;
        MAZE_API int index_of(const std::string& key) const;
        MAZE_API inline const std::vector<std::string>& get_keys() const { return _children_keys; }

        MAZE_API inline const std::vector<std::string>::const_iterator keys_begin() const { return _children_keys.begin(); }
        MAZE_API inline const std::vector<std::string>::const_iterator keys_end() const { return _children_keys.end(); }
        MAZE_API inline std::vector<std::string>::iterator keys_begin() { return _children_keys.begin(); }
        MAZE_API inline std::vector<std::string>::iterator keys_end() { return _children_keys.end(); }

#pragma endregion


#pragma region Function

        MAZE_API inline void set_function(FunctionCallback callback) { _callback = callback; _type = Type::Function; }

        MAZE_API inline Element e(const Element& value) const { return execute_function(value); }
        MAZE_API Element execute_function(const Element& value) const;

        MAZE_API inline FunctionCallback get_callback() const { return _callback; }

#pragma endregion

#pragma region Type checks

        MAZE_API inline bool is_null() const { return is(Type::Null); }
        MAZE_API inline bool is_bool() const { return is(Type::Bool); }
        MAZE_API inline bool is_int() const { return is(Type::Int); }
        MAZE_API inline bool is_double() const { return is(Type::Double); }
        MAZE_API inline bool is_string() const { return is(Type::String); }
        MAZE_API inline bool is_array() const { return is(Type::Array); }
        MAZE_API inline bool is_object() const { return is(Type::Object); }
        MAZE_API inline bool is_function() const { return is(Type::Function); }
        MAZE_API inline bool is(Type type) const { return _type == type; }

        MAZE_API inline bool is_null(int index) const { return is(index, Type::Null); }
        MAZE_API inline bool is_bool(int index) const { return is(index, Type::Bool); }
        MAZE_API inline bool is_int(int index) const { return is(index, Type::Int); }
        MAZE_API inline bool is_double(int index) const { return is(index, Type::Double); }
        MAZE_API inline bool is_string(int index) const { return is(index, Type::String); }
        MAZE_API inline bool is_array(int index) const { return is(index, Type::Array); }
        MAZE_API inline bool is_object(int index) const { return is(index, Type::Object); }
        MAZE_API inline bool is_function(int index) const { return is(index, Type::Function); }
        MAZE_API inline bool is(int index, Type type) const { return get(index).is(type); }

        MAZE_API inline bool is_null(const std::string& key) const { return is(key, Type::Null); }
        MAZE_API inline bool is_bool(const std::string& key) const { return is(key, Type::Bool); }
        MAZE_API inline bool is_int(const std::string& key) const { return is(key, Type::Int); }
        MAZE_API inline bool is_double(const std::string& key) const { return is(key, Type::Double); }
        MAZE_API inline bool is_string(const std::string& key) const { return is(key, Type::String); }
        MAZE_API inline bool is_array(const std::string& key) const { return is(key, Type::Array); }
        MAZE_API inline bool is_object(const std::string& key) const { return is(key, Type::Object); }
        MAZE_API inline bool is_function(const std::string& key) const { return is(key, Type::Function); }
        MAZE_API inline bool is(const std::string& key, Type type) const { return get(key).is(type); }

#pragma endregion


        MAZE_API void apply(const Element& new_element);

        MAZE_API std::string to_json(int indentation_spacing = 2) const;

        MAZE_API void apply_json(const std::string& json_string);

        MAZE_API static Element from_json(const std::string& json_string);

        MAZE_API static const Element& get_null_element();

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
