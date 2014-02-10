
#include <exeng/Config.hpp>
#include <exeng.main/Main.hpp>

#if !defined(EXENG_WINDOWS) 
int main(int argc, char** argv) {
	return exeng::main::main(argc, argv);
}
#else

#include <Windows.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow) {
	// TODO: Append the command line.
	return exeng::main::main(0, nullptr);
}
#endif
