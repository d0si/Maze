#include <gtest/gtest.h>
#include <Maze/Maze.hpp>

class MazeExceptionTest : public ::testing::Test {};

TEST(MazeExceptionTest, ExceptionWhat_MatchesMessage) {
	const std::string exception_message = "t43qtn3nkj4r3lnqjk";
	Maze::MazeException exception(exception_message);

	EXPECT_EQ(exception.what(), exception_message);
}

TEST(MazeExceptionTest, TryCatch_CorrectWhat) {
	const std::string exception_message = "t43qtn3nkj4r3lnqjk";

	try {
		Maze::MazeException exception(exception_message);
		throw exception;
	}
	catch (Maze::MazeException exception) {
		EXPECT_EQ(exception.what(), exception_message);
	}
}

TEST(MazeExceptionTest, TryCatch_ConstRef_CorrectWhat) {
	const std::string exception_message = "t43qtn3nkj4r3lnqjk";

	try {
		Maze::MazeException exception(exception_message);
		throw exception;
	}
	catch (const Maze::MazeException& exception) {
		EXPECT_EQ(exception.what(), exception_message);
	}
}

TEST(MazeExceptionTest, TryCatch_Ref_CorrectWhat) {
	const std::string exception_message = "t43qtn3nkj4r3lnqjk";

	try {
		Maze::MazeException exception(exception_message);
		throw exception;
	}
	catch (Maze::MazeException& exception) {
		EXPECT_EQ(exception.what(), exception_message);
	}
}

TEST(MazeExceptionTest, TryCatch_Ptr_CorrectWhat) {
	const std::string exception_message = "t43qtn3nkj4r3lnqjk";

	try {
		Maze::MazeException* exception = new Maze::MazeException(exception_message);
		throw exception;
	}
	catch (Maze::MazeException* exception) {
		EXPECT_EQ(exception->what(), exception_message);

		delete exception;
	}
}

// Do not catch std::exception by value as object will be copied and what() function will resolve to "Unknown error".

TEST(MazeExceptionTest, TryCatch_AsStdException_ConstRef_CorrectWhat) {
	const std::string exception_message = "t43qtn3nkj4r3lnqjk";

	try {
		Maze::MazeException exception(exception_message);
		throw exception;
	}
	catch (const std::exception& exception) {
		EXPECT_EQ(exception.what(), exception_message);
	}
}

TEST(MazeExceptionTest, TryCatch_AsStdException_Ref_CorrectWhat) {
	const std::string exception_message = "t43qtn3nkj4r3lnqjk";

	try {
		Maze::MazeException exception(exception_message);
		throw exception;
	}
	catch (std::exception& exception) {
		EXPECT_EQ(exception.what(), exception_message);
	}
}
