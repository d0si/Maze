#ifndef MAZE_OBJECT_H
#define MAZE_OBJECT_H

#include <string>
#include <vector>
#include <maze/element.h>

namespace maze {

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

  Object* set(std::string index, Element &maze);
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

  Object* insert(std::string index, Element &maze);
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

  Element get(std::string index, Type type);
  Element get(std::string index);
  Element operator[](std::string index);
  Element operator[](int index);

  int remove(std::string index);
  void clear();

  std::vector<std::pair<std::string, Element>>::iterator begin();
  std::vector<std::pair<std::string, Element>>::iterator end();

  std::vector<std::pair<std::string, Element>> get_mazes();

  int index_of(std::string index);
  int first_index_of(std::string index);
  bool exists(std::string index);
  size_t size();
  bool is_empty();

  bool is_string(std::string index);
  bool is_int(std::string index);
  bool is_double(std::string index);
  bool is_bool(std::string index);
  bool is_array(std::string index);
  bool is_object(std::string index);

  void apply(Object new_obj);

  std::string to_json(int indentation_spacing = 2);

  static Object from_json(const std::string& json_string);
};

}  // namespace maze

#endif  // MAZE_OBJECT_H
