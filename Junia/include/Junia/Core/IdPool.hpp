#pragma once

#include <stack>
#include <vector>

namespace Junia
{
	/**
	 * @brief A stack with an accessible container
	 * @tparam T the type of data to store in the stack
	*/
	template<typename T>
	class IdPoolStackAdapter : public std::stack<T, std::vector<T>>
	{
	public:
		/**
		 * @brief Get the underlying container
		 * @return a reference to the container the stack has been built on top
		 *         of
		*/
		std::vector<T>& GetContainer() { return this->c; }
	};

	/**
	 * @brief A pool of IDs
	 * @tparam T the numerical data type to use for the IDs
	*/
	template<typename T>
	class IdPool
	{
	private:
		IdPoolStackAdapter<T> freeIds{ };
		T start;
		T current;
		T step;

	public:
		/**
		 * @brief Create a new ID pool
		 * @param start the minimum value at which the pool starts handing out
		 *              IDs (defaults to 0)
		 * @param step the numerical difference between each ID (defaults to 1)
		 * @param reservedFrees amount of IDs that can be returned to the pool
		 *                      before a reallocation happens (defaults to 32)
		*/
		IdPool(T start = static_cast<T>(0), T step = static_cast<T>(1), size_t reservedFrees = 32) :
			start(start), current(start), step(step)
		{
			freeIds.GetContainer().reserve(reservedFrees);
		}

		/**
		 * @brief Get an unused ID from the pool
		 * @return a valid ID
		*/
		T Next()
		{
			T id{ };
			if (freeIds.empty())
			{
				id = current;
				current = current + step;
				return id;
			}
			id = freeIds.top();
			freeIds.pop();
			return id;
		}

		/**
		 * @brief Return an ID to the pool (unchecked).
		 * @param id the ID to put back into the pool. In order to maintain
		 *           uniqueness of IDs only pass IDs that have been returned by
		 *           the IdPool::Next() function of this IdPool
		*/
		void Free(T id)
		{
			if (id == current - step) current = current - step;
			else freeIds.push(id);
		}
	};
}
