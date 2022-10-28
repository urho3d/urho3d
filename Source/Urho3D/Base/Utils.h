// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "PrimitiveTypes.h"

#include <type_traits>

namespace Urho3D
{

/// Converts enum class to u32 if underlying type is u32
template<typename EnumClass>
inline constexpr std::enable_if_t<std::is_same_v<std::underlying_type_t<EnumClass>, u32>, u32> ToU32(EnumClass enumClass)
{
	return static_cast<u32>(enumClass);
}

} // namespace Urho3D
