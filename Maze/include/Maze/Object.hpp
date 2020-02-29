#ifndef MAZE_OBJECT_HPP
#define MAZE_OBJECT_HPP

#include <string>
#include <vector>
#include <Maze/Element.hpp>

namespace Maze {
	class Object {
	private:
		std::vector<std::pair<std::string, Element>> mazes_;
	public:
		Object();
		Object(std::string index);
		Object(std::string index, Element maze);
		Object(std::string index, std::string value);
		Object(std::string index, const char* value);
		Object(std::string index, int value);
		Object(std::string index, double value);
		Object(std::string index, bool value);
		Object(std::string index, Array value);
		Object(std::string index, Array* value);
		Object(std::string index, Object value);
		Object(std::string index, Object* value);

		Object* set(std::string index, Element& maze);
		Object* set_maze(std::string index, Element maze);
		Object* set(std::string index, std::string value);
		Object* set(std::string index, const char* value);
		Object* set(std::string index, int value);
		Object* set(std::string index, double value);
		Object* set(std::string index, bool value);
		Object* set(std::string index, Array value);
		Object* set(std::string index, Array* value);
		Object* set(std::string index, Object value);
		Object* set(std::string index, Object* value);
		Object* set_null(std::string index);

		Object* insert(std::string index, Element& maze);
		Object* insert_maze(std::string index, Element maze);
		Object* insert(std::string index, std::string value);
		Object* insert(std::string index, const char* value);
		Object* insert(std::string index, int value);
		Object* insert(std::string index, double value);
		Object* insert(std::string index, bool value);
		Object* insert(std::string index, Array value);
		Object* insert(std::string index, Array* value);
		Object* insert(std::string index, Object value);
		Object* insert(std::string index, Object* value);
		Object* insert_null(std::string index);

		Element* get_ptr(std::string index);
		Element* get_ptr(int index);
		Element get(std::string index, Type type) const;
		Element get(std::string index) const;
		Element operator[](std::string index) const;
		Element operator[](int index) const;

		int remove(std::string index);
		void clear();

		std::vector<std::pair<std::string, Element>>::iterator begin();
		std::vector<std::pair<std::string, Element>>::iterator end();

		std::vector<std::pair<std::string, Element>> get_mazes() const;

		int index_of(std::string index) const;
		int first_index_of(std::string index) const;
		bool exists(std::string index) const;
		size_t size() const;
		bool is_empty() const;

		bool is_string(std::string index) const;
		bool is_int(std::string index) const;
		bool is_double(std::string index) const;
		bool is_bool(std::string index) const;
		bool is_array(std::string index) const;
		bool is_object(std::string index) const;

		void apply(Object new_obj);

		std::string to_json(int indentation_spacing = 2) const;

		static Object from_json(const std::string& json_string);
	};
}  // namespace Maze

#endif  // MAZE_OBJECT_HPP
