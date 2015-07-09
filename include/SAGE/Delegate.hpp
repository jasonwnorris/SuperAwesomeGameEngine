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
			template<typename U> Delegate& Add(const U& pFunction)
			{
				mFunctions.push_back(std::function<Ret(Args...)>(pFunction));

				return *this;
			}

			template<typename U> Delegate& Remove(const U& pFunction)
			{
				mFunctions.erase(mFunctions.remove(mFunctions.begin(), mFunctions.end(), pFunction), mFunctions.end());

				return *this;
			}

			template<typename U> Delegate& RemoveAll()
			{
				mFunctions.clear();

				return *this;
			}

			std::vector<Ret> operator()(Args... pParameters)
			{
				std::vector<Ret> ret;
				for (auto func : mFunctions)
					mFunctions.push_back(func(pParameters...));

				return ret;
			}

		private:
			std::vector<std::function<Ret(Args...)>> mFunctions;
	};

	template<typename... Args> class Delegate<void, Args...>
	{
		public:
			template<typename U> Delegate& Add(const U& pFunction)
			{
				mFunctions.push_back(std::function<void(Args...)>(pFunction));

				return *this;
			}

			template<typename U> Delegate& Remove(const U& pFunction)
			{
				mFunctions.erase(mFunctions.remove(mFunctions.begin(), mFunctions.end(), pFunction), mFunctions.end());

				return *this;
			}

			template<typename U> Delegate& RemoveAll()
			{
				mFunctions.clear();

				return *this;
			}

			void operator()(Args... params)
			{
				for (auto func : mFunctions)
					func(params...);
			}

		private:
			std::vector<std::function<void(Args...)>> mFunctions;
	};
}

#endif
