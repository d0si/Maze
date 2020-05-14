#include <Maze/Helpers.hpp>
#include <Maze/Maze.hpp>

namespace Maze {
	namespace Helpers {
		namespace Element {
			Json to_json_element(const Maze::Element& el) {
				Json json_el;

				switch (el.get_type()) {
				case Type::Null:
					break;
				case Type::Bool:
					json_el = el.get_bool();
					break;
				case Type::Int:
					json_el = el.get_int();
					break;
				case Type::Double:
					json_el = el.get_double();
					break;
				case Type::String:
					json_el = el.get_string();
					break;
				case Type::Array:
					json_el = Array::to_json_array(el);
					break;
				case Type::Object:
					json_el = Object::to_json_object(el);
					break;
				}

				return json_el;
			}

			void apply_json(Maze::Element& el, const Json& json) {
				el.apply(from_json(json));
			}

			Maze::Element from_json(const Json& json) {
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
			Json to_json_array(const Maze::Element& array_el) {
				Json json_arr = Json::array();

				auto children = array_el.get_children();
				for (const auto& it : children) {
					json_arr.push_back(Element::to_json_element(it));
				}

				return json_arr;
			}

			Maze::Element from_json(const Json& json_array) {
				Maze::Element array_el(Maze::Type::Array);

				for (const auto& it : json_array) {
					if (it.is_string()) {
						array_el.push_back(it.get<std::string>());
					}
					else if (it.is_number_integer()) {
						array_el.push_back(it.get<int>());
					}
					else if (it.is_number_float()) {
						array_el.push_back(it.get<double>());
					}
					else if (it.is_boolean()) {
						array_el.push_back(it.get<bool>());
					}
					else if (it.is_array()) {
						array_el.push_back(Helpers::Array::from_json(it));
					}
					else if (it.is_object()) {
						array_el.push_back(Helpers::Object::from_json(it));
					}
					else if (it.is_null()) {
						array_el.push_back(Maze::Element(Type::Null));
					}
				}

				return array_el;
			}
		}  // namespace Array

		namespace Object {
			Json to_json_object(const Maze::Element& object_el) {
				const auto& keys = object_el.get_keys();
				const auto& val = object_el.get_children();
				
				Json json_obj = Json::object();

				for (int i = 0; i < object_el.count_children(); ++i) {
					json_obj[keys[i]] = Element::to_json_element(val[i]);
				}
				
				return json_obj;
			}

			Maze::Element from_json(const Json& json_object) {
				Maze::Element object_el(Maze::Type::Object);

				for (auto it = json_object.begin(); it != json_object.end(); it++) {
					if (it->is_string()) {
						object_el.set(it.key(), it->get<std::string>());
					}
					else if (it->is_number_integer()) {
						object_el.set(it.key(), it->get<int>());
					}
					else if (it->is_number_float()) {
						object_el.set(it.key(), it->get<double>());
					}
					else if (it->is_boolean()) {
						object_el.set(it.key(), it->get<bool>());
					}
					else if (it->is_array()) {
						object_el.set(it.key(), Helpers::Array::from_json(*it));
					}
					else if (it->is_object()) {
						object_el.set(it.key(), Helpers::Object::from_json(*it));
					}
					else if (it->is_null()) {
						object_el.set(it.key(), Maze::Element(Type::Null));
					}
				}

				return object_el;
			}
		}  // namespace Object
	}  // namespace Helpers
}  // namespace Maze
