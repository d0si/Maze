#include <Maze/Maze.hpp>

namespace Maze {
	std::string to_string(const Type& type) {
		switch (type) {
		case Type::Bool:
			return "bool";
		case Type::Int:
			return "int";
		case Type::Double:
			return "double";
		case Type::String:
			return "string";
		case Type::Array:
			return "array";
		case Type::Object:
			return "object";
		case Type::Function:
			return "function";
		default:
			return "null";
		}
	}
}  // namespace Maze
