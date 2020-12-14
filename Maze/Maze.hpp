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
		MazeException(const std::string& message);

		virtual const char* what() const override;

	protected:
		const std::string _message;
	};


	class Element;
	typedef Element(*FunctionCallback) (Element value);


	class Element {
	public:
#pragma region Constructors/destructors

		Element();
		Element(const Element& val);
		Element(bool val);
		Element(int val);
		Element(double val);
		Element(const std::string& val);
		Element(const char* val);
		Element(const std::vector<Element>& val);
		Element(const std::vector<std::string>& keys, const std::vector<Element>& val);
		Element(FunctionCallback callback);
		Element(Type val);
		~Element();

#pragma endregion


		void copy_from_element(const Element& val);
		void operator=(const Element& val);

		void set_type(const Type& type);
		const Type& get_type() const;
		Type& get_type_ref();

		void set_key(const std::string& key);
		const std::string& get_key() const;
		std::string& get_key_ref();

		void set_as_null(bool clear_existing_values = true);


#pragma region Boolean

		//   Getters
		bool b() const;
		operator bool() const;
		bool get_bool() const;
		bool get_bool(bool fallback_value) const;
		bool& get_bool_ref();

		//   Setters
		void b(bool val);
		void operator=(bool val);
		void set_bool(bool val);

#pragma endregion


#pragma region Integer

		//   Getters
		int i() const;
		operator int() const;
		int get_int() const;
		int get_int(int fallback_value) const;
		int& get_int_ref();
		
		//   Setters
		void i(int val);
		void operator=(int val);
		void set_int(int val);

#pragma endregion

#pragma region Double

		//   Getters
		double d() const;
		operator double() const;
		double get_double() const;
		double get_double(double fallback_value) const;
		double& get_double_ref();

		//   Setters
		void d(double val);
		void operator=(double val);
		void set_double(double val);

#pragma endregion


#pragma region String
		
		//   Getters
		const std::string& s() const;
		operator const std::string&() const;
		const std::string& get_string() const;
		const std::string& get_string_const_ref(const std::string& fallback_value) const;
		std::string get_string(const std::string& fallback_value) const;
		std::string& get_string_ref();

		//   Setters
		void s(const std::string& val);
		void operator=(const std::string& val);
		void operator=(const char* val);
		void set_string(const std::string& val);

#pragma endregion


#pragma region Array

		static const char array_index_prefix_char = MAZE_ARRAY_INDEX_PREFIX_CHAR;

		//   Getters
		const Element& operator[](int index) const;
		const Element& get(int index) const;
		const Element& get_const_ref(int index, const Element& fallback_value) const;
		Element get(int index, const Element& fallback_value) const;
		Element& operator[](int index);
		Element& get_ref(int index);
		Element* get_ptr(int index);

		//   Setters
		void set_array(const std::vector<Element>& val);
		Element& push_back(const std::string& value);
		Element& push_back(const char* value);
		Element& push_back(bool value);
		Element& push_back(int value);
		Element& push_back(double value);
		Element& operator<<(const std::string& value);
		Element& operator<<(const char* value);
		Element& operator<<(bool value);
		Element& operator<<(int value);
		Element& operator<<(double value);
		Element& operator<<(const Element& value);
		Element& push_back(const Element& value);

		void remove_at(int index, bool update_string_indexes = true);
		void remove_all_children();
		size_t count_children() const;
		bool has_children() const;
		const std::vector<Element>& get_children() const;

		const std::vector<Element>::const_iterator begin() const;
		const std::vector<Element>::const_iterator end() const;
		std::vector<Element>::iterator begin();
		std::vector<Element>::iterator end();

#pragma endregion


#pragma region Object

		//   Getters
		const Element& operator[](const std::string& key) const;
		const Element& operator[](const char* key) const;
		const Element& get(const std::string& key) const;
		const Element& get_const_ref(const std::string& key, const Element& fallback_value) const;
		Element get(const std::string& key, const Element& fallback_value) const;
		Element& operator[](const std::string& key);
		Element& operator[](const char* key);
		Element& get_ref(const std::string& key);
		Element* get_ptr(const std::string& key);

		//   Setters
		void set_object(const std::vector<std::string>& keys, const std::vector<Element>& values);
		void set(const std::string& key, const std::string& value);
		void set(const std::string& key, const char* value);
		void set(const std::string& key, bool value);
		void set(const std::string& key, int value);
		void set(const std::string& key, double value);
		void set(const std::string& key, const Element& value);

		void remove(const std::string& key, bool update_string_indexes = true);
		bool exists(const std::string& key) const;
		int index_of(const std::string& key) const;
		const std::vector<std::string>& get_keys() const;

		const std::vector<std::string>::const_iterator keys_begin() const;
		const std::vector<std::string>::const_iterator keys_end() const;
		std::vector<std::string>::iterator keys_begin();
		std::vector<std::string>::iterator keys_end();

#pragma endregion


#pragma region Function
		
		void set_function(FunctionCallback callback);
		
		Element execute_function(const Element& value) const;
		Element e(const Element& value) const;

		FunctionCallback get_callback() const;

#pragma endregion

#pragma region Type checks

		bool is_null() const;
		bool is_bool() const;
		bool is_int() const;
		bool is_double() const;
		bool is_string() const;
		bool is_array() const;
		bool is_object() const;
		bool is_function() const;
		bool is(Type type) const;

		bool is_null(int index) const;
		bool is_bool(int index) const;
		bool is_int(int index) const;
		bool is_double(int index) const;
		bool is_string(int index) const;
		bool is_array(int index) const;
		bool is_object(int index) const;
		bool is_function(int index) const;
		bool is(int index, Type type) const;

		bool is_null(const std::string& key) const;
		bool is_bool(const std::string& key) const;
		bool is_int(const std::string& key) const;
		bool is_double(const std::string& key) const;
		bool is_string(const std::string& key) const;
		bool is_array(const std::string& key) const;
		bool is_object(const std::string& key) const;
		bool is_function(const std::string& key) const;
		bool is(const std::string& key, Type type) const;

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
