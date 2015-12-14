
#include <exeng/Config.hpp>
#include <exeng.main/Main.hpp>

int main(int argc, char** argv) {
	return exeng::main::main(argc, argv);
}

#if defined(EXENG_WINDOWS) 
#include <Windows.h>
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow) {
	// TODO: Append the command line.
	return exeng::main::main(0, nullptr);
}
#endif
