// Console.cpp

// SAGE Includes
#include <SAGE/Console.hpp>
// STD Includes
#include <iostream>
#include <stdio.h>
#include <stdarg.h>

namespace SAGE
{
	// static
	void Console::Write(const char* p_Text, ...)
	{
		va_list args;
		va_start(args, p_Text);
		vprintf(p_Text, args);
		va_end(args);
	}

	// static
	void Console::WriteLine(const char* p_Text, ...)
	{
		va_list args;
		va_start(args, p_Text);
		vprintf(p_Text, args);
		va_end(args);
		printf("/n");
	}

	// static
	void Console::Write(const std::string& p_Text)
	{
		std::cout << p_Text;
	}

	// static
	void Console::WriteLine(const std::string& p_Text)
	{
		std::cout << p_Text << std::endl;
	}

	// static
	void Console::WriteLine()
	{
		std::cout << std::endl;
	}
}
