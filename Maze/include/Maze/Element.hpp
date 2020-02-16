#ifndef MAZE_ELEMENT_HPP
#define MAZE_ELEMENT_HPP

#include <string>
#include <memory>
#include <maze/type.hpp>

namespace maze {

class Array;
class Object;

class Element {
 private:
  Type type_ = Type::Null;

  bool val_bool_;
  int val_int_;
  std::shared_ptr<double> ptr_double_;
  std::shared_ptr<std::string> ptr_string_;
  std::shared_ptr<Array> ptr_array_;
  std::shared_ptr<Object> ptr_object_;

  std::shared_ptr<std::string> ptr_key_;
 public:
  Element();
  Element(bool val);
  Element(int val);
  Element(double val);
  Element(std::string& val);
  Element(const char* val);
  Element(Array val);
  Element(Object val);
  Element(Type val);
  ~Element();

  void set_type(Type type);
  Type get_type();

  void set_key(std::string key);
  std::string get_key();

  void set_null();

  void set_bool(bool val);
  void operator=(bool val);
  bool get_bool();
  operator bool();

  void set_int(int val);
  void operator=(int val);
  int get_int();
  operator int();

  void set_double(double val);
  void operator=(double val);
  double get_double();
  operator double();

  void set_string(std::string val);
  void operator=(std::string val);
  void operator=(const char* val);
  std::string get_string();
  operator std::string();

  void set_array(Array value);
  void operator=(Array value);
  Array get_array();
  operator Array();

  void set_object(Object value);
  void operator=(Object value);
  Object get_object();
  operator Object();

  bool is_null();
  bool is_bool();
  bool is_int();
  bool is_double();
  bool is_string();
  bool is_array();
  bool is_object();
  bool is(Type type);

  void apply(Element new_element);

  std::string to_json(int indentation_spacing = 2);

  void apply_json(std::string json_string);

  static Element from_json(std::string json_string);

  static Element get_null();
};

}  // namespace maze

#endif  // MAZE_ELEMENT_HPP
