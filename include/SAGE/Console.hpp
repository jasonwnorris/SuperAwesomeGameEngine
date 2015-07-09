// Console.hpp

#ifndef __SAGE_CONSOLE_HPP__
#define __SAGE_CONSOLE_HPP__

// STD Includes
#include <string>

namespace SAGE
{
	class Console
	{
		public:
			static void Write(const char* pText, ...);
			static void WriteLine(const char* pText, ...);
			static void Write(const std::string& pText);
			static void WriteLine(const std::string& pText);
			static void WriteLine();

		private:
			Console() = delete;
			~Console() = delete;
	};
}

#endif
