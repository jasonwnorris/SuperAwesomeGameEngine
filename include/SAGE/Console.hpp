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
			static void Write(const char* p_Text, ...);
			static void WriteLine(const char* p_Text, ...);
			static void Write(const std::string& p_Text);
			static void WriteLine(const std::string& p_Text);
			static void WriteLine();

		private:
			Console() = delete;
			~Console() = delete;
	};
}

#endif
