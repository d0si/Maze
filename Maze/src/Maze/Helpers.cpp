#include <Maze/Helpers.hpp>
#include <Maze/Element.hpp>
#include <Maze/Array.hpp>
#include <Maze/Object.hpp>

namespace maze {
namespace helpers {
namespace element {

Json to_json_element(Element* el) {
  Json json_el;

  switch (el->get_type()) {
    case Type::Null:
      break;
    case Type::Bool:
      json_el = el->get_bool();
      break;
    case Type::Int:
      json_el = el->get_int();
      break;
    case Type::Double:
      json_el = el->get_double();
      break;
    case Type::String:
      json_el = el->get_string();
      break;
    case Type::Array: {
      Array arr = el->get_array();
      json_el = helpers::array::to_json_array(&arr);
      break;
    }
    case Type::Object: {
      Object obj = el->get_object();
      json_el = helpers::object::to_json_object(&obj);
      break;
    }
  }

  return json_el;
}

void apply_json(Element* el, Json json) {
  el->apply(from_json(json));
}

Element from_json(Json json) {
  Element el;

  if (json.is_boolean()) {
    el = json.get<bool>();
  } else if (json.is_number_integer()) {
    el = json.get<int>();
  } else if (json.is_number_float()) {
    el = json.get<double>();
  } else if (json.is_string()) {
    el = json.get<std::string>();
  } else if (json.is_array()) {
    el = helpers::array::from_json(json);
  } else if (json.is_object()) {
    el = helpers::object::from_json(json);
  } else if (json.is_null()) {
    el.set_null();
  }

  return el;
}

}  // namespace element
namespace array {

Json to_json_array(Array* array) {
  Json json_arr = Json::array();

  auto mazes = array->get_mazes();
  for (unsigned int i = 0; i < mazes.size(); i++) {
    Element maze = mazes[i];
    switch (maze.get_type()) {
      case Type::String:
        json_arr.push_back(maze.get_string());
        break;
      case Type::Int:
        json_arr.push_back(maze.get_int());
        break;
      case Type::Double:
        json_arr.push_back(maze.get_double());
        break;
      case Type::Bool:
        json_arr.push_back(maze.get_bool());
        break;
      case Type::Null:
        json_arr.push_back(nullptr);
        break;
      case Type::Array: {
        Array arr = maze.get_array();
        json_arr.push_back(helpers::array::to_json_array(&arr));
        break;
      }
      case Type::Object: {
        Object obj = maze.get_object();
        json_arr.push_back(helpers::object::to_json_object(&obj));
        break;
      }
    }
  }

  return json_arr;
}

Array from_json(Json json_array) {
  Array arr;

  for (auto it = json_array.begin(); it != json_array.end(); it++) {
    if (it->is_string()) {
      arr.push(it->get<std::string>());
    } else if (it->is_number_integer()) {
      arr.push(it->get<int>());
    } else if (it->is_number_float()) {
      arr.push(it->get<double>());
    } else if (it->is_boolean()) {
      arr.push(it->get<bool>());
    } else if (it->is_array()) {
      arr.push(helpers::array::from_json(*it));
    } else if (it->is_object()) {
      arr.push(helpers::object::from_json(*it));
    } else if (it->is_null()) {
      arr.push_maze(Element(Type::Null));
    }
  }

  return arr;
}

}  // namespace array
namespace object {

Json to_json_object(Object* object) {
  Json json_obj = Json::object();
  auto mazes = object->get_mazes();

  for (auto m : mazes) {
    std::string index = m.first;
    auto maze = m.second;

    switch (maze.get_type()) {
      case Type::String:
        json_obj[index] = maze.get_string();
        break;
      case Type::Int:
        json_obj[index] = maze.get_int();
        break;
      case Type::Double:
        json_obj[index] = maze.get_double();
        break;
      case Type::Bool:
        json_obj[index] = maze.get_bool();
        break;
      case Type::Null:
        json_obj[index] = nullptr;
        break;
      case Type::Array: {
        Array arr = maze.get_array();
        json_obj[index] = helpers::array::to_json_array(&arr);
        break;
      }
      case Type::Object: {
        Object obj = maze.get_object();
        json_obj[index] = helpers::object::to_json_object(&obj);
        break;
      }
    }
  }

  return json_obj;
}

Object from_json(Json json_object) {
  Object obj;

  for (auto it = json_object.begin(); it != json_object.end(); it++) {
    if (it->is_string()) {
      obj.set(it.key(), it->get<std::string>());
    } else if (it->is_number_integer()) {
      obj.set(it.key(), it->get<int>());
    } else if (it->is_number_float()) {
      obj.set(it.key(), it->get<double>());
    } else if (it->is_boolean()) {
      obj.set(it.key(), it->get<bool>());
    } else if (it->is_array()) {
      obj.set(it.key(), helpers::array::from_json(*it));
    } else if (it->is_object()) {
      obj.set(it.key(), helpers::object::from_json(*it));
    } else if (it->is_null()) {
      obj.set_maze(it.key(), Element(Type::Null));
    }
  }

  return obj;
}

}  // namespace object
}  // namespace helpers
}  // namespace maze
