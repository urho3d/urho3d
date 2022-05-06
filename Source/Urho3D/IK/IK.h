// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

/*
 * TODO
 *  - Optimise.
 *  - Profile.
 *  - Documentation.
 *
 * FUTURE
 *  - Support for "stretchiness" with min/max lengths.
 *  - Support for "stiffness" factor, describes how well a bone rotates.
 *  - Implement constraints.
 *  - Skip bones when building the tree.
 *  - Mass/Spring/Damper solver.
 */

namespace Urho3D
{

class Context;

/// Registers all IK systems to the specified context.
/// @nobind
void RegisterIKLibrary(Context* context);

} // namespace Urho3D
