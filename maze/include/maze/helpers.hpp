#ifndef MAZE_HELPERS_HPP
#define MAZE_HELPERS_HPP

#include <nlohmann/json.hpp>

namespace maze {

class Element;
class Array;
class Object;
using Json = nlohmann::json;

namespace helpers {
namespace element {

Json to_json_element(Element* el);
void apply_json(Element* el, Json json);
Element from_json(Json json);

}  // namespace element
namespace array {

Json to_json_array(Array* arr);
Array from_json(Json json_array);

}  // namespace array
namespace object {

Json to_json_object(Object* obj);
Object from_json(Json json_object);

}  // namespace object
}  // namespace helpers
}  // namespace maze

#endif  // MAZE_HELPERS_HPP
