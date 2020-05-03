#include <Maze/Helpers.hpp>
#include <Maze/Maze.hpp>

namespace Maze {
	namespace Helpers {
		namespace Element {
			Json to_json_element(const Maze::Element* el) {
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
					Maze::Array arr = el->get_array();
					json_el = Helpers::Array::to_json_array(&arr);
					break;
				}
				case Type::Object: {
					Maze::Object obj = el->get_object();
					json_el = Helpers::Object::to_json_object(&obj);
					break;
				}
				}

				return json_el;
			}

			void apply_json(Maze::Element* el, const Json json) {
				el->apply(from_json(json));
			}

			Maze::Element from_json(const Json json) {
				Maze::Element el;

				if (json.is_boolean()) {
					el = json.get<bool>();
				}
				else if (json.is_number_integer()) {
					el = json.get<int>();
				}
				else if (json.is_number_float()) {
					el = json.get<double>();
				}
				else if (json.is_string()) {
					el = json.get<std::string>();
				}
				else if (json.is_array()) {
					el = Helpers::Array::from_json(json);
				}
				else if (json.is_object()) {
					el = Helpers::Object::from_json(json);
				}
				else if (json.is_null()) {
					el.set_as_null();
				}

				return el;
			}
		}  // namespace Element

		namespace Array {
			Json to_json_array(const Maze::Array* array) {
				Json json_arr = Json::array();

				auto mazes = array->get_mazes();
				for (unsigned int i = 0; i < mazes.size(); i++) {
					Maze::Element maze = mazes[i];
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
						Maze::Array arr = maze.get_array();
						json_arr.push_back(Helpers::Array::to_json_array(&arr));
						break;
					}
					case Type::Object: {
						Maze::Object obj = maze.get_object();
						json_arr.push_back(Helpers::Object::to_json_object(&obj));
						break;
					}
					}
				}

				return json_arr;
			}

			Maze::Array from_json(const Json json_array) {
				Maze::Array arr;

				for (auto it = json_array.begin(); it != json_array.end(); it++) {
					if (it->is_string()) {
						arr.push(it->get<std::string>());
					}
					else if (it->is_number_integer()) {
						arr.push(it->get<int>());
					}
					else if (it->is_number_float()) {
						arr.push(it->get<double>());
					}
					else if (it->is_boolean()) {
						arr.push(it->get<bool>());
					}
					else if (it->is_array()) {
						arr.push(Helpers::Array::from_json(*it));
					}
					else if (it->is_object()) {
						arr.push(Helpers::Object::from_json(*it));
					}
					else if (it->is_null()) {
						arr.push_maze(Maze::Element(Type::Null));
					}
				}

				return arr;
			}
		}  // namespace Array

		namespace Object {
			Json to_json_object(const Maze::Object* object) {
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
						Maze::Array arr = maze.get_array();
						json_obj[index] = Helpers::Array::to_json_array(&arr);
						break;
					}
					case Type::Object: {
						Maze::Object obj = maze.get_object();
						json_obj[index] = Helpers::Object::to_json_object(&obj);
						break;
					}
					}
				}

				return json_obj;
			}

			Maze::Object from_json(const Json json_object) {
				Maze::Object obj;

				for (auto it = json_object.begin(); it != json_object.end(); it++) {
					if (it->is_string()) {
						obj.set(it.key(), it->get<std::string>());
					}
					else if (it->is_number_integer()) {
						obj.set(it.key(), it->get<int>());
					}
					else if (it->is_number_float()) {
						obj.set(it.key(), it->get<double>());
					}
					else if (it->is_boolean()) {
						obj.set(it.key(), it->get<bool>());
					}
					else if (it->is_array()) {
						obj.set(it.key(), Helpers::Array::from_json(*it));
					}
					else if (it->is_object()) {
						obj.set(it.key(), Helpers::Object::from_json(*it));
					}
					else if (it->is_null()) {
						obj.set_maze(it.key(), Maze::Element(Type::Null));
					}
				}

				return obj;
			}
		}  // namespace Object
	}  // namespace Helpers
}  // namespace Maze
