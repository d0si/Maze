#include <maze/maze.hpp>
#include <iostream>

int main() {
    maze::Object obj;
    obj.set("test", "works");

    std::cout << obj.to_json(2) << std::endl;

    return 0;
}
