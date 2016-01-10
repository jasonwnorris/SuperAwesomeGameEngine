// String.cpp

// SAGE Includes
#include <SAGE/String.hpp>

namespace SAGE
{
	void String::Split(const std::string& p_Text, const std::string& p_Delimiter, std::vector<std::string>& p_Results)
	{
		std::string::size_type step = p_Delimiter.size();
		std::string::size_type current = 0;
		std::string::size_type previous = 0;

		while ((current = p_Text.find(p_Delimiter, previous)) != std::string::npos)
		{
			p_Results.push_back(p_Text.substr(previous, current - previous));

			previous = current + step;
		}

		p_Results.push_back(p_Text.substr(previous));
	}
}
