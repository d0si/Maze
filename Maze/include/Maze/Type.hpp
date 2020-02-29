#ifndef MAZE_TYPE_HPP
#define MAZE_TYPE_HPP

#include <string>

namespace Maze {

enum class Type {
  Null = 0,
  Bool = 1,
  Int = 2,
  Double = 3,
  String = 4,
  Array = 5,
  Object = 6
};

const std::string to_string(const Type& type);

}  // namespace Maze

#endif  // MAZE_TYPE_HPP
