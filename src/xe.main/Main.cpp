
#include <xe/Config.hpp>
#include <xe.main/Main.hpp>

int main(int argc, char** argv) {
	return xe::main(argc, argv);
}

#if defined(EXENG_WINDOWS) 
#include <Windows.h>
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow) {
	// TODO: Append the command line.
	return xe::main(0, nullptr);
}
#endif
