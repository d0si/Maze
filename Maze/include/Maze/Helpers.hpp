#ifndef MAZE_HELPERS_HPP
#define MAZE_HELPERS_HPP

#include <nlohmann/json.hpp>

namespace Maze {

class Element;
class Array;
class Object;
using Json = nlohmann::json;

namespace Helpers {
namespace Element {

Json to_json_element(Maze::Element* el);
void apply_json(Maze::Element* el, Json json);
Maze::Element from_json(Json json);

}  // namespace Element
namespace Array {

Json to_json_array(Maze::Array* arr);
Maze::Array from_json(Json json_array);

}  // namespace Array
namespace Object {

Json to_json_object(Maze::Object* obj);
Maze::Object from_json(Json json_object);

}  // namespace Object
}  // namespace Helpers
}  // namespace Maze

#endif  // MAZE_HELPERS_HPP
