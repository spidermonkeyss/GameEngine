#include <iostream>
#include "windows.h"
#include <filesystem>

int main()
{
	LPCTSTR lpApplicationName;

	// additional information
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	// set the size of the structures
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));


	std::string filePath = std::filesystem::current_path().string() + "\\..\\..OpenGL\OpenGL.exe";
	std::cout << filePath << std::endl;
	std::wstring widestr = std::wstring(filePath.begin(), filePath.end());
	const wchar_t* str = widestr.c_str();
	// start the program up
	CreateProcess(str,   // the path
		NULL,			// Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi             // Pointer to PROCESS_INFORMATION structure (removed extra parentheses)
	);
	// Close process and thread handles. 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}