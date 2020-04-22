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
		Object = 6
	};

	std::string to_string(const Type& type);

	class Array;
	class Object;

	class Element {
	private:
		Type type_ = Type::Null;

		bool val_bool_;
		int val_int_;
		double val_double_;
		std::string val_string_;
		std::unique_ptr<Array> ptr_array_;
		std::unique_ptr<Object> ptr_object_;

		std::string val_key_;
	public:
		Element();
		Element(const Element& val);
		Element(bool val);
		Element(int val);
		Element(double val);
		Element(const std::string& val);
		Element(const char* val);
		Element(const Array& val);
		Element(const Object& val);
		Element(Type val);
		~Element();

		void set_element(const Element& val);
		void operator=(const Element& val);

		void set_type(Type type);
		Type get_type() const;

		void set_key(std::string key);
		std::string get_key() const;

		void set_null();

		void set_bool(bool val);
		void operator=(bool val);
		bool get_bool() const;
		bool b() const;
		operator bool() const;

		void set_int(int val);
		void operator=(int val);
		int get_int() const;
		int i() const;
		operator int() const;

		void set_double(double val);
		void operator=(double val);
		double get_double() const;
		double d() const;
		operator double() const;

		void set_string(const std::string& val);
		void operator=(const std::string& val);
		void operator=(const char* val);
		std::string get_string() const;
		std::string s() const;
		operator std::string() const;

		void set_array(const Array& value);
		void operator=(const Array& value);
		Array get_array() const;
		Array a() const;
		Array* a_ptr() const;
		operator Array() const;

		void set_object(const Object& value);
		void operator=(const Object& value);
		Object get_object() const;
		Object o() const;
		Object* o_ptr() const;
		operator Object() const;

		bool is_null() const;
		bool is_bool() const;
		bool is_int() const;
		bool is_double() const;
		bool is_string() const;
		bool is_array() const;
		bool is_object() const;
		bool is(Type type) const;

		void apply(const Element& new_element);

		std::string to_json(int indentation_spacing = 2) const;

		void apply_json(const std::string& json_string);

		static Element from_json(const std::string& json_string);

		static Element get_null();
	};

	class Array {
	private:
		std::vector<Element> mazes_;
	public:
		Array* push(Element& maze);
		Array* push_maze(const Element& maze);
		Array operator<<(const Element& maze);
		Array* push(const std::string& value);
		Array operator<<(const std::string& value);
		Array* push(const char* value);
		Array operator<<(const char* value);
		Array* push(int value);
		Array operator<<(int value);
		Array* push(double value);
		Array operator<<(double value);
		Array* push(bool value);
		Array operator<<(bool value);
		Array* push(const Array& value);
		Array operator<<(const Array& value);
		Array* push(Array* value);
		Array operator<<(Array* value);
		Array* push(const Object& value);
		Array operator<<(const Object& value);
		Array* push(Object* value);
		Array operator<<(Object* value);

		Element* get_ptr(int index);
		Element get(int index, Type type) const;
		Element get(int index) const;
		Element operator[](int index) const;

		std::vector<Element>::iterator begin();
		std::vector<Element>::iterator end();

		std::vector<Element> get_mazes() const;

		int remove(int index);
		void clear();
		size_t size() const;

		bool is_empty() const;

		std::string to_json(int indentation_spacing = 2) const;

		static Array from_json(const std::string& json_string);
	};

	class Object {
	private:
		std::vector<std::pair<std::string, Element>> mazes_;
	public:
		Object();
		Object(const std::string& index);
		Object(const std::string& index, const Element& maze);
		Object(const std::string& index, const std::string& value);
		Object(const std::string& index, const char* value);
		Object(const std::string& index, int value);
		Object(const std::string& index, double value);
		Object(const std::string& index, bool value);
		Object(const std::string& index, const Array& value);
		Object(const std::string& index, Array* value);
		Object(const std::string& index, const Object& value);
		Object(const std::string& index, Object* value);

		Object* set(const std::string& index, const Element& maze);
		Object* set_maze(const std::string& index, const Element& maze);
		Object* set(const std::string& index, const std::string& value);
		Object* set(const std::string& index, const char* value);
		Object* set(const std::string& index, int value);
		Object* set(const std::string& index, double value);
		Object* set(const std::string& index, bool value);
		Object* set(const std::string& index, const Array& value);
		Object* set(const std::string& index, Array* value);
		Object* set(const std::string& index, const Object& value);
		Object* set(const std::string& index, Object* value);
		Object* set_null(const std::string& index);

		Object* insert(const std::string& index, const Element& maze);
		Object* insert_maze(const std::string& index, const Element& maze);
		Object* insert(const std::string& index, const std::string& value);
		Object* insert(const std::string& index, const char* value);
		Object* insert(const std::string& index, int value);
		Object* insert(const std::string& index, double value);
		Object* insert(const std::string& index, bool value);
		Object* insert(const std::string& index, const Array& value);
		Object* insert(const std::string& index, Array* value);
		Object* insert(const std::string& index, const Object& value);
		Object* insert(const std::string& index, Object* value);
		Object* insert_null(const std::string& index);

		Element* get_ptr(const std::string& index);
		Element* get_ptr(int index);
		Element get(const std::string& index, Type type) const;
		Element get(const std::string& index) const;
		Element operator[](const std::string& index) const;
		Element operator[](int index) const;

		int remove(const std::string& index);
		void clear();

		std::vector<std::pair<std::string, Element>>::iterator begin();
		std::vector<std::pair<std::string, Element>>::iterator end();

		std::vector<std::pair<std::string, Element>> get_mazes() const;

		int index_of(const std::string& index) const;
		int first_index_of(const std::string& index) const;
		bool exists(const std::string& index) const;
		size_t size() const;
		bool is_empty() const;

		bool is_string(const std::string& index) const;
		bool is_int(const std::string& index) const;
		bool is_double(const std::string& index) const;
		bool is_bool(const std::string& index) const;
		bool is_array(const std::string& index) const;
		bool is_object(const std::string& index) const;

		void apply(const Object& new_obj);

		std::string to_json(int indentation_spacing = 2) const;

		static Object from_json(const std::string& json_string);
	};
}  // namespace Maze

#endif  // MAZE_MAZE_HPP
