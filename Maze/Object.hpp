#ifndef MAZE_OBJECT_HPP
#define MAZE_OBJECT_HPP

#include <string>
#include <vector>
#include <Maze/Maze.hpp>

namespace Maze {
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

#endif  // MAZE_OBJECT_HPP
