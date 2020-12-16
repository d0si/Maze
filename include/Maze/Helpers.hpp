#pragma once

#include <nlohmann/json.hpp>
#include <Maze/DLLSupport.hpp>

namespace Maze {
    class Element;
    using Json = nlohmann::json;
}


namespace Maze::Helpers::Element {
    
    MAZE_API Json to_json_element(const Maze::Element& el);
    MAZE_API void apply_json(Maze::Element& el, const Json& json);
    MAZE_API Maze::Element from_json(const Json& json);

}  // namespace Maze::Helpers::Element


namespace Maze::Helpers::Array {
    
    MAZE_API Json to_json_array(const Maze::Element& array_el);
    MAZE_API Maze::Element from_json(const Json& json_array);

}  // namespace Maze::Helpers::Array


namespace Maze::Helpers::Object {

    MAZE_API Json to_json_object(const Maze::Element& obj);
    MAZE_API Maze::Element from_json(const Json& json_object);

}  // namespace Maze::Helpers::Object
