#ifndef MAZE_ARRAY_HPP
#define MAZE_ARRAY_HPP

#include <string>
#include <vector>
#include <Maze/Element.hpp>

namespace Maze {
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
}  // namespace Maze

#endif  // MAZE_ARRAY_HPP
