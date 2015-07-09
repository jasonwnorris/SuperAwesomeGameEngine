// Console.cpp

// STD Includes
#include <iostream>
#include <stdio.h>
#include <stdarg.h>
// SAGE Includes
#include <SAGE\Console.hpp>

namespace SAGE
{
	// static
	void Console::Write(const char* pText, ...)
	{
		va_list args;
		va_start(args, pText);
		vprintf(pText, args);
		va_end(args);
	}

	// static
	void Console::WriteLine(const char* pText, ...)
	{
		va_list args;
		va_start(args, pText);
		vprintf(pText, args);
		va_end(args);
		printf("\n");
	}

	// static
	void Console::Write(const std::string& pText)
	{
		std::cout << pText;
	}

	// static
	void Console::WriteLine(const std::string& pText)
	{
		std::cout << pText << std::endl;
	}

	// static
	void Console::WriteLine()
	{
		std::cout << std::endl;
	}
}
