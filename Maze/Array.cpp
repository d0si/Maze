#include <Maze/Maze.hpp>
#include <Maze/Helpers.hpp>
#include <nlohmann/json.hpp>

namespace Maze {
	Array* Array::push(Element& maze) {
		mazes_.push_back(maze);

		return this;
	}

	Array* Array::push_maze(const Element& maze) {
		mazes_.push_back(maze);

		return this;
	}

	Array Array::operator<<(const Element& maze) {
		push_maze(maze);

		return *this;
	}

	Array* Array::push(const std::string& value) {
		return push_maze(std::move(Element(value)));
	}

	Array Array::operator<<(const std::string& value) {
		push(value);

		return *this;
	}

	Array* Array::push(const char* value) {
		return push_maze(std::move(Element(value)));
	}

	Array Array::operator<<(const char* value) {
		push(value);

		return *this;
	}

	Array* Array::push(int value) {
		return push_maze(std::move(Element(value)));
	}

	Array Array::operator<<(int value) {
		push(value);

		return *this;
	}

	Array* Array::push(double value) {
		return push_maze(std::move(Element(value)));
	}

	Array Array::operator<<(double value) {
		push(value);

		return *this;
	}

	Array* Array::push(bool value) {
		return push_maze(std::move(Element(value)));
	}

	Array Array::operator<<(bool value) {
		push(value);

		return *this;
	}

	Array* Array::push(const Array& value) {
		return push_maze(std::move(Element(value)));
	}

	Array Array::operator<<(const Array& value) {
		push(value);

		return *this;
	}

	Array* Array::push(Array* value) {
		return push_maze(std::move(Element(value)));
	}

	Array Array::operator<<(Array* value) {
		push(value);

		return *this;
	}

	Array* Array::push(const Object& value) {
		return push_maze(std::move(Element(value)));
	}

	Array Array::operator<<(const Object& value) {
		push(value);

		return *this;
	}

	Array* Array::push(Object* value) {
		return push_maze(std::move(Element(value)));
	}

	Array Array::operator<<(Object* value) {
		push(value);

		return *this;
	}

	Element* Array::get_ptr(int index) {
		if ((unsigned int)index >= size()) {
			return nullptr;
		}

		return &mazes_.at(index);
	}

	Element Array::get(int index, Type type) const {
		if ((unsigned int)index >= size()) {
			return Element();
		}

		return mazes_[index];
	}

	Element Array::get(int index) const {
		return get(index, Type::Bool);
	}

	Element Array::operator[](int index) const {
		return get(index);
	}

	std::vector<Element>::iterator Array::begin() {
		return mazes_.begin();
	}

	std::vector<Element>::iterator Array::end() {
		return mazes_.end();
	}

	std::vector<Element> Array::get_mazes() const {
		return mazes_;
	}

	int Array::remove(int index) {
		mazes_.erase(mazes_.begin() + index);
		return 0;
	}

	void Array::clear() {
		mazes_.clear();
	}

	size_t Array::size() const {
		return mazes_.size();
	}

	bool Array::is_empty() const {
		return mazes_.empty();
	}

	std::string Array::to_json(int indentation_spacing) const {
		return Helpers::Array::to_json_array(this).dump(indentation_spacing);
	}

	Array Array::from_json(const std::string& json_string) {
		return Helpers::Array::from_json(nlohmann::json::parse(json_string));
	}
}  // namespace Maze