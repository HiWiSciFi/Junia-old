#pragma once

#include <type_traits>

namespace gsl {

	template<class T, class = std::enable_if_t<std::is_pointer<T>::value>>
	using owner = T;

} // namespace gsl
