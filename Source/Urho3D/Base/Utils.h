// Copyright (c) 2008-2023 the Urho3D project
// License: MIT

#pragma once

#include "PrimitiveTypes.h"

#include <type_traits>

namespace Urho3D
{

/// Converts enum class to u8 if underlying type is u8
template<typename EnumClass>
inline constexpr std::enable_if_t<std::is_same_v<std::underlying_type_t<EnumClass>, u8>, u8> ToU8(EnumClass enumClass)
{
	return static_cast<u8>(enumClass);
}

/// Converts enum class to u32 if underlying type is u32
template<typename EnumClass>
inline constexpr std::enable_if_t<std::is_same_v<std::underlying_type_t<EnumClass>, u32>, u32> ToU32(EnumClass enumClass)
{
	return static_cast<u32>(enumClass);
}

} // namespace Urho3D
