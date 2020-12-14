#include <Maze/Maze.hpp>

namespace Maze {

    MazeException::MazeException(const std::string& message)
        : _message(message) {}

    const char* MazeException::what() const noexcept {
        return _message.c_str();
    }

}  // namespace Maze
