#include <maze/object.h>
#include <maze/element.h>
#include <maze/array.h>
#include <maze/helpers.h>
#include <nlohmann/json.hpp>

namespace maze {

Object::Object() {

}

Object::Object(std::string index) {
  insert_null(index);
}

Object::Object(std::string index, Element maze) {
  insert(index, maze);
}

Object::Object(std::string index, std::string value) {
  insert(index, value);
}

Object::Object(std::string index, const char* value) {
  insert(index, value);
}

Object::Object(std::string index, int value) {
  insert(index, value);
}

Object::Object(std::string index, double value) {
  insert(index, value);
}

Object::Object(std::string index, bool value) {
  insert(index, value);
}

Object::Object(std::string index, Array value) {
  insert(index, value);
}

Object::Object(std::string index, Array* value) {
  insert(index, value);
}

Object::Object(std::string index, Object value) {
  insert(index, value);
}

Object::Object(std::string index, Object* value) {
  insert(index, value);
}

Object* Object::set(std::string index, Element &maze) {
  maze.set_key(index);
  int i = index_of(index);
  if (i < 0) {
    return insert(index, maze);
  }

  mazes_[i] = make_pair(index, maze);

  return this;
}

Object* Object::set_maze(std::string index, Element maze) {
  maze.set_key(index);
  int i = index_of(index);
  if (i < 0) {
    return insert(index, maze);
  }

  mazes_[i] = std::make_pair(index, maze);

  return this;
}

Object* Object::set(std::string index, std::string value) {
  return set_maze(index, Element(value));
}

Object* Object::set(std::string index, const char* value) {
  return set_maze(index, Element(value));
}

Object* Object::set(std::string index, int value) {
  return set_maze(index, Element(value));
}

Object* Object::set(std::string index, double value) {
  return set_maze(index, Element(value));
}

Object* Object::set(std::string index, bool value) {
  return set_maze(index, Element(value));
}

Object* Object::set_null(std::string index) {
  Element el;
  el.set_null();

  return set_maze(index, el);
}

Object* Object::set(std::string index, Array value) {
  return set_maze(index, Element(value));
}

Object* Object::set(std::string index, Array* value) {
  return set_maze(index, Element(value));
}

Object* Object::set(std::string index, Object value) {
  return set_maze(index, Element(value));
}

Object* Object::set(std::string index, Object* value) {
  return set_maze(index, Element(value));
}

Object* Object::insert(std::string index, Element &maze) {
  maze.set_key(index);
  mazes_.push_back(make_pair(index, maze));

  return this;
}

Object* Object::insert_maze(std::string index, Element maze) {
  maze.set_key(index);
  mazes_.push_back(make_pair(index, maze));

  return this;
}

Object* Object::insert(std::string index, std::string value) {
  return insert_maze(index, Element(value));
}

Object* Object::insert(std::string index, const char* value) {
  return insert_maze(index, Element(value));
}

Object* Object::insert(std::string index, int value) {
  return insert_maze(index, Element(value));
}

Object* Object::insert(std::string index, double value) {
  return insert_maze(index, Element(value));
}

Object* Object::insert(std::string index, bool value) {
  return insert_maze(index, Element(value));
}

Object* Object::insert_null(std::string index) {
  Element el;
  el.set_null();

  return insert_maze(index, el);
}

Object* Object::insert(std::string index, Array value) {
  return insert_maze(index, Element(value));
}

Object* Object::insert(std::string index, Array* value) {
  return insert_maze(index, Element(value));
}

Object* Object::insert(std::string index, Object value) {
  return insert_maze(index, Element(value));
}

Object* Object::insert(std::string index, Object* value) {
  return insert_maze(index, Element(value));
}

Element Object::get(std::string index, Type type) {
  int i = index_of(index);
  if (i < 0) {
    return Element();
  }

  return mazes_[i].second;
}

Element Object::get(std::string index) {
  return get(index, Type::Bool);
}

Element Object::operator[](std::string index) {
  return get(index);
}

Element Object::operator[](int index) {
  if (index >= mazes_.size()) {
    return Element();
  }

  return mazes_[index].second;
}

int Object::remove(std::string index) {
  int i = index_of(index);
  if (i < 0) {
    return -1;
  } else {
    mazes_.erase(mazes_.begin() + i);

    return 0;
  }
}

void Object::clear() {
  mazes_.clear();
}

unsigned int Object::size() {
  return (unsigned int) mazes_.size();
}

bool Object::is_empty() {
  return mazes_.empty();
}

std::vector<std::pair<std::string, Element>>::iterator Object::begin() {
  return mazes_.begin();
}

std::vector<std::pair<std::string, Element>>::iterator Object::end() {
  return mazes_.end();
}

std::vector<std::pair<std::string, Element>> Object::get_mazes() {
  return mazes_;
}

int Object::index_of(std::string index) {
  if (mazes_.size() > 0) {
    for (int i = mazes_.size() - 1; i >= 0; --i) {
      if (mazes_[i].first == index) {
        return i;
      }
    }
  }

  return -1;
}

int Object::first_index_of(std::string index) {
  for (unsigned int i = 0; i < mazes_.size(); ++i) {
    if (mazes_[i].first == index) {
      return i;
    }
  }

  return -1;
}

bool Object::exists(std::string index) {
  return index_of(index) >= 0;
}

bool Object::is_string(std::string index) {
  return (exists(index) && get(index).is_string());
}

bool Object::is_int(std::string index) {
  return (exists(index) && get(index).is_int());
}

bool Object::is_double(std::string index) {
  return (exists(index) && get(index).is_double());
}

bool Object::is_bool(std::string index) {
  return (exists(index) && get(index).is_bool());
}

bool Object::is_array(std::string index) {
  return (exists(index) && get(index).is_array());
}

bool Object::is_object(std::string index) {
  return (exists(index) && get(index).is_object());
}

void Object::apply(Object new_obj) {
  for (auto maze : new_obj) {
    if (exists(maze.first)) {
      get(maze.first).apply(maze.second);
    } else {
      insert(maze.first, maze.second);
    }
  }
}

std::string Object::to_json(int indentation_spacing) {
  return helpers::object::to_json_object(this).dump(indentation_spacing);
}

Object Object::from_json(const std::string& json_string) {
  return helpers::object::from_json(nlohmann::json::parse(json_string));
}

}  // namespace maze
