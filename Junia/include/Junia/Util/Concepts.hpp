#pragma once

#include <concepts>

namespace Junia {

template<typename T, typename Base>
concept TypenameDerivedFrom = std::derived_from<T, Base>;

} // namespace Junia
