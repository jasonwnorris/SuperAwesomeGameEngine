// Engine.hpp

#ifndef __ENGINE_HPP__
#define __ENGINE_HPP__

namespace SAGE
{
	class Engine
	{
		public:
			Engine();
			~Engine();

			bool Initialize();
			bool Finalize();

		private:
			bool m_IsInitialized;
	};
}

#endif
