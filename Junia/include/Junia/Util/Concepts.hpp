#pragma once

#include <concepts> // std::derived_from<T, U>

namespace Junia {

template<typename T, typename Base>
concept TypenameDerivedFrom = std::derived_from<T, Base>;

} // namespace Junia
