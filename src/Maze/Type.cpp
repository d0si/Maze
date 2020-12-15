#include <Maze/Maze.hpp>

namespace Maze {

	const std::string bool_type = "bool";
	const std::string int_type = "int";
	const std::string double_type = "double";
	const std::string string_type = "string";
	const std::string array_type = "array";
	const std::string object_type = "object";
	const std::string function_type = "function";
	const std::string null_type = "null";

	const std::string& to_string(const Type& type) {
		switch (type) {
		case Type::Bool:
			return bool_type;
		case Type::Int:
			return int_type;
		case Type::Double:
			return double_type;
		case Type::String:
			return string_type;
		case Type::Array:
			return array_type;
		case Type::Object:
			return object_type;
		case Type::Function:
			return function_type;
		default:
			return null_type;
		}
	}

}  // namespace Maze
