// Delegate.hpp

#ifndef __SAGE_DELEGATE_HPP__
#define __SAGE_DELEGATE_HPP__

// STD Includes
#include <functional>
#include <vector>

namespace SAGE
{
	template<typename Ret, typename... Args> class Delegate
	{
		public:
			template<typename U> Delegate& Add(const U& p_Function)
			{
				m_Functions.push_back(std::function<Ret(Args...)>(p_Function));

				return *this;
			}

			template<typename U> Delegate& Remove(const U& p_Function)
			{
				m_Functions.erase(m_Functions.remove(m_Functions.begin(), m_Functions.end(), p_Function), m_Functions.end());

				return *this;
			}

			template<typename U> Delegate& RemoveAll()
			{
				m_Functions.clear();

				return *this;
			}

			std::vector<Ret> operator()(Args... p_Parameters)
			{
				std::vector<Ret> ret;
				for (auto func : m_Functions)
					m_Functions.push_back(func(p_Parameters...));

				return ret;
			}

		private:
			std::vector<std::function<Ret(Args...)>> m_Functions;
	};

	template<typename... Args> class Delegate<void, Args...>
	{
		public:
			template<typename U> Delegate& Add(const U& p_Function)
			{
				m_Functions.push_back(std::function<void(Args...)>(p_Function));

				return *this;
			}

			template<typename U> Delegate& Remove(const U& p_Function)
			{
				m_Functions.erase(m_Functions.remove(m_Functions.begin(), m_Functions.end(), p_Function), m_Functions.end());

				return *this;
			}

			template<typename U> Delegate& RemoveAll()
			{
				m_Functions.clear();

				return *this;
			}

			void operator()(Args... params)
			{
				for (auto func : m_Functions)
					func(params...);
			}

		private:
			std::vector<std::function<void(Args...)>> m_Functions;
	};
}

#endif
