#ifndef MAZE_MAZE_HPP
#define MAZE_MAZE_HPP

#include <string>

namespace Maze {
	std::string get_version();

	enum class Type {
		Null = 0,
		Bool = 1,
		Int = 2,
		Double = 3,
		String = 4,
		Array = 5,
		Object = 6
	};

	std::string to_string(const Type& type);
}  // namespace Maze

#endif  // MAZE_MAZE_HPP
