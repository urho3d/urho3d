//
// Copyright (c) 2008-2016 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

/*
 * TODO
 *  - Add support for manually updating initial pose.
 *  - Lua script bindings crash.
 *  - Implement inherit parent rotations in IKEffector.
 *  - Optimise.
 *  - Profile.
 *  - Documentation.
 *  - Move log callback into context init function.
 *  - Bug when enabling continuous mode and IKSolver is placed somewhere
 *    on part of the model's bones.
 *
 * FUTURE
 *  - Support for "stretchiness" with min/max lengths.
 *  - Support for "stiffness" factor, describes how well a bone rotates.
 *  - Apply bullet constraints to joints.
 */

namespace Urho3D
{

class Context;

/// Registers all IK systems to the specified context.
void RegisterIKLibrary(Context* context);

} // namespace Urho3D
