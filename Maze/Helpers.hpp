#pragma once

#include <nlohmann/json.hpp>

namespace Maze {
    class Element;
    using Json = nlohmann::json;
}


namespace Maze::Helpers::Element {
    
    Json to_json_element(const Maze::Element& el);
    void apply_json(Maze::Element& el, const Json& json);
    Maze::Element from_json(const Json& json);

}  // namespace Maze::Helpers::Element


namespace Maze::Helpers::Array {
    
    Json to_json_array(const Maze::Element& array_el);
    Maze::Element from_json(const Json& json_array);

}  // namespace Maze::Helpers::Array


namespace Maze::Helpers::Object {

    Json to_json_object(const Maze::Element& obj);
    Maze::Element from_json(const Json& json_object);

}  // namespace Maze::Helpers::Object
