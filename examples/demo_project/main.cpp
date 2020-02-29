#include <Maze/Maze.hpp>
#include <iostream>

int main() {
	Maze::Object obj;
	obj.set("test", "works");

	std::cout << obj.to_json(2) << std::endl;

	return 0;
}
