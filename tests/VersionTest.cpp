#include <gtest/gtest.h>
#include <Maze/Maze.hpp>
//#include <Maze/Version.hpp>

//const char* actual_maze_version = MAZE_VERSION;
//const char* fake_maze_version = "unknown";

class VersionTest : public ::testing::Test {};

TEST(VersionTest, GetVersion_CorrectVersion) {
	/*const std::string& version = */Maze::get_version();

	//EXPECT_EQ(Maze::get_version(), MAZE_VERSION);
}

TEST(VersionTest, GetVersion_CorrectBuildVersion_IncorrectMacro) {
//#undef MAZE_VERSION
//#define MAZE_VERSION fake_maze_version

	//EXPECT_EQ(Maze::get_version(), actual_maze_version);
	//EXPECT_NE(Maze::get_version(), "unknown");

//#undef MAZE_VERSION
//#define MAZE_VERSION actual_maze_version;
}
