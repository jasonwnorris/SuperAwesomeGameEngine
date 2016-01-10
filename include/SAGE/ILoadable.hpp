// ILoadable.hpp

#ifndef __ILOADABLE_HPP__
#define __ILOADABLE_HPP__

// STL Includes
#include <string>

namespace SAGE
{
	template<typename T> class ILoadable
	{
		public:
			ILoadable() : m_IsLoaded(false) { }
			virtual ~ILoadable() { }

			virtual bool Load(const std::string& p_Filename, const T& p_Options) = 0;
			virtual bool Unload() = 0;

		protected:
			bool m_IsLoaded;
	};
}

#endif
