#include <maze/array.hpp>
#include <maze/element.hpp>
#include <maze/object.hpp>
#include <maze/helpers.hpp>
#include <nlohmann/json.hpp>

namespace maze {

Array* Array::push(Element &maze) {
  mazes_.push_back(maze);

  return this;
}

Array* Array::push_maze(Element maze) {
  mazes_.push_back(maze);

  return this;
}

Array Array::operator<<(Element maze) {
  push_maze(maze);

  return *this;
}

Array* Array::push(std::string value) {
  return push_maze(std::move(Element(value)));
}

Array Array::operator<<(std::string value) {
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

Array* Array::push(Array value) {
  return push_maze(std::move(Element(value)));
}

Array Array::operator<<(Array value) {
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

Array* Array::push(Object value) {
  return push_maze(std::move(Element(value)));
}

Array Array::operator<<(Object value) {
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

Element Array::get(int index, Type type) {
  if ((unsigned int) index >= size()) {
    return Element();
  }

  return mazes_[index];
}

Element Array::get(int index) {
  return get(index, Type::Bool);
}

Element Array::operator[](int index) {
  return get(index);
}

std::vector<Element>::iterator Array::begin() {
  return mazes_.begin();
}

std::vector<Element>::iterator Array::end() {
  return mazes_.end();
}

std::vector<Element> Array::get_mazes() {
  return mazes_;
}

int Array::remove(int index) {
  mazes_.erase(mazes_.begin() + index);
  return 0;
}

void Array::clear() {
  mazes_.clear();
}

size_t Array::size() {
  return mazes_.size();
}

bool Array::is_empty() {
  return mazes_.empty();
}

std::string Array::to_json(int indentation_spacing) {
  return helpers::array::to_json_array(this).dump(indentation_spacing);
}

Array Array::from_json(std::string json_string) {
  return helpers::array::from_json(nlohmann::json::parse(json_string));
}

}  // namespace maze
