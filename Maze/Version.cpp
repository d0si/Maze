#include <Maze/Version.hpp>
#include <string>

namespace Maze {

	const std::string version = MAZE_VERSION;

	const std::string& get_version() {
		return version;
	}

}  // namespace Maze
