// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

/* Coverity Scan model
 *
 * This is a modeling file for Coverity Scan. Modeling helps to avoid false
 * positives.
 *
 * - A model file can't import any header files.
 * - Therefore only some built-in primitives like int, char and void are
 *   available but not wchar_t, NULL etc.
 * - Modeling doesn't need full structs and typedefs. Rudimentary structs
 *   and similar types are sufficient.
 * - An uninitialized local pointer is not an error. It signifies that the
 *   variable could be either NULL or have some data.
 *
 * Coverity Scan doesn't pick up modifications automatically. The model file
 * must be uploaded by an admin in the analysis settings of
 * https://scan.coverity.com/projects/urho3d-urho3d?tab=analysis_settings
 */

#define URHO3D_API __attribute__((visibility("default")))

namespace Urho3D
{

// Suppressing false positive due to (ARRAY_VS_SINGLETON) out-of-bound access
//
// FIXME: For some reasons below does not work, probably it generated a different mangled name than the one it supposes to replace
//
class URHO3D_API VectorBase {};
template <class T> class Vector : public VectorBase
{
public:
    void Push(const T& value)
    {
        T array[] = {value};
        Resize(size_ + 1, array);
    }
};

}
