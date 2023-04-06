#pragma once

#include <cstdint>
#include <stack>
#include <vector>

namespace Junia {

// -----------------------------------------------------------------------------
// -------------------------------- Declarations -------------------------------
// -----------------------------------------------------------------------------

/**
 * @brief A stack with an accessible container
 * @tparam T the type of data to store in the stack
*/
template<typename T>
class IdPoolStackAdapter : public std::stack<T, std::vector<T>> {
public:
	/**
	 * @brief Get the underlying container
	 * @return a reference to the container the stack has been built on top
	 *         of
	*/
	std::vector<T>& GetContainer();
};

/**
 * @brief A pool of IDs
 * @tparam T the numerical data type to use for the IDs
*/
template<typename T>
class IdPool {
private:
	IdPoolStackAdapter<T> freeIds{ };
	T start;
	T current;
	T step;

public:
	static const size_t DEFAULT_FREES = 32;

	/**
	 * @brief Create a new ID pool
	 * @param start the minimum value at which the pool starts handing out
	 *              IDs (defaults to 0)
	 * @param step the numerical difference between each ID (defaults to 1)
	 * @param reservedFrees amount of IDs that can be returned to the pool
	 *                      before a reallocation happens (defaults to 32)
	*/
	explicit IdPool(T start = static_cast<T>(0), T step = static_cast<T>(1), size_t reservedFrees = DEFAULT_FREES);

	/**
	 * @brief Get an unused ID from the pool
	 * @return a valid ID
	*/
	T Next();

	/**
	 * @brief Return an ID to the pool (unchecked).
	 * @param id the ID to put back into the pool. In order to maintain
	 *           uniqueness of IDs only pass IDs that have been returned by
	 *           the IdPool::Next() function of this IdPool
	*/
	void Free(T poolId);
};

// -----------------------------------------------------------------------------
// ------------------------------ Implementations ------------------------------
// -----------------------------------------------------------------------------

template<typename T>
inline std::vector<T>& Junia::IdPoolStackAdapter<T>::GetContainer() {
	return this->c;
}

template<typename T>
inline Junia::IdPool<T>::IdPool(T start, T step, size_t reservedFrees)
	: start(start), current(start), step(step) {
	freeIds.GetContainer().reserve(reservedFrees);
}

template<typename T>
inline T Junia::IdPool<T>::Next() {
	T poolId{ };
	if (freeIds.empty()) {
		poolId = current;
		current = current + step;
		return poolId;
	}
	poolId = freeIds.top();
	freeIds.pop();
	return poolId;
}

template<typename T>
inline void IdPool<T>::Free(T poolId) {
	if (poolId == current - step)
		current = current - step;
	else freeIds.push(poolId);
}

} // namespace Junia
