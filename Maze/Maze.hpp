#ifndef MAZE_MAZE_HPP
#define MAZE_MAZE_HPP

#include <string>
#include <memory>
#include <vector>

namespace Maze {
	std::string get_version();

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

	std::string to_string(const Type& type);

	class MazeException : public std::exception {
	public:
		std::string message;

		MazeException(const std::string& message) : message(message) {

		}
	};

	class Element {
	private:
		Type type_ = Type::Null;

		bool val_bool_;
		int val_int_;
		double val_double_;
		std::string val_string_;
		std::vector<std::string> children_keys_;
		std::vector<Element> children_;

		std::string val_key_;
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
		Element(Type val);
		~Element();
#pragma endregion

		void copy_from_element(const Element& val);
		void operator=(const Element& val);

		void set_type(Type type);
		Type get_type() const;

		void set_key(const std::string& key);
		const std::string& get_key() const;

		void set_as_null(bool clear_existing_values = true);

#pragma region Boolean
		//   Getters
		const bool& get_bool() const;
		const bool& b() const;
		bool& b();
		operator bool() const;
		//   Setters
		void set_bool(bool val);
		void b(bool val);
		void operator=(bool val);
#pragma endregion

#pragma region Integer
		//   Getters
		const int& get_int() const;
		const int& i() const;
		int& i();
		operator int() const;
		//   Setters
		void set_int(int val);
		void i(int val);
		void operator=(int val);
#pragma endregion

#pragma region Double
		//   Getters
		const double& get_double() const;
		const double& d() const;
		double& d();
		operator double() const;
		//   Setters
		void set_double(double val);
		void d(double val);
		void operator=(double val);
#pragma endregion

#pragma region String
		//   Getters
		const std::string& get_string() const;
		const std::string& s() const;
		std::string& s();
		operator std::string() const;
		//   Setters
		void set_string(const std::string& val);
		void s(const std::string& val);
		void operator=(const std::string& val);
		void operator=(const char* val);
#pragma endregion

#pragma region Array
		static const char array_index_prefix_char = '~';

		//   Getters
		const Element& get(int index) const;
		Element& get(int index);
		Element* get_ptr(int index);
		const Element& operator[](int index) const;
		Element& operator[](int index);

		//   Setters
		void set_array(const std::vector<Element>& val);
		Element& push_back(const Element& value);
		Element& push_back(const std::string& value);
		Element& push_back(const char* value);
		Element& push_back(bool value);
		Element& push_back(int value);
		Element& push_back(double value);
		Element& operator<<(const Element& value);
		Element& operator<<(const std::string& value);
		Element& operator<<(const char* value);
		Element& operator<<(bool value);
		Element& operator<<(int value);
		Element& operator<<(double value);

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
		const Element& get(const std::string& key) const;
		Element& get(const std::string& key);
		Element* get_ptr(const std::string& key);
		const Element& operator[](const std::string& key) const;
		const Element& operator[](const char* key) const;
		Element& operator[](const std::string& key);
		Element& operator[](const char* key);

		//   Setters
		void set_object(const std::vector<std::string>& keys, const std::vector<Element>& values);
		void set(const std::string& key, const Element& value);
		void set(const std::string& key, const std::string& value);
		void set(const std::string& key, const char* value);
		void set(const std::string& key, bool value);
		void set(const std::string& key, int value);
		void set(const std::string& key, double value);

		void remove(const std::string& key, bool update_string_indexes = true);
		bool exists(const std::string& key) const;
		int index_of(const std::string& key) const;
		const std::vector<std::string>& get_keys() const;

		const std::vector<std::string>::const_iterator keys_begin() const;
		const std::vector<std::string>::const_iterator keys_end() const;
		std::vector<std::string>::iterator keys_begin();
		std::vector<std::string>::iterator keys_end();
#pragma endregion

#pragma region Type checks
		bool is_null() const;
		bool is_bool() const;
		bool is_int() const;
		bool is_double() const;
		bool is_string() const;
		bool is_array() const;
		bool is_object() const;
		bool is(Type type) const;

		bool is_null(int index) const;
		bool is_bool(int index) const;
		bool is_int(int index) const;
		bool is_double(int index) const;
		bool is_string(int index) const;
		bool is_array(int index) const;
		bool is_object(int index) const;
		bool is(int index, Type type) const;

		bool is_null(const std::string& key) const;
		bool is_bool(const std::string& key) const;
		bool is_int(const std::string& key) const;
		bool is_double(const std::string& key) const;
		bool is_string(const std::string& key) const;
		bool is_array(const std::string& key) const;
		bool is_object(const std::string& key) const;
		bool is(const std::string& key, Type type) const;
#pragma endregion

		void apply(const Element& new_element);

		std::string to_json(int indentation_spacing = 2) const;

		void apply_json(const std::string& json_string);

		static Element from_json(const std::string& json_string);

		static const Element& get_null_element();
	};
}  // namespace Maze

#endif  // MAZE_MAZE_HPP
