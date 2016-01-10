// String.hpp

#ifndef __STRING_HPP__
#define __STRING_HPP__

// STL Includes
#include <string>
#include <vector>

namespace SAGE
{
	class String
	{
		public:
			static void Split(const std::string& p_Text, const std::string& p_Delimiter, std::vector<std::string>& p_Results);
	};
}

#endif
