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
 * TODO IK todo
 *  - Break conditions (so maxIteration isn't reached necessarily)
 *  - IKEffector doesn't save target node name when saving scene in editor
 *  - Initial pose is not saved when saving scene in editor. Instead, the
 *    solved state of the chain(s) are saved.
 *  - Target angle in addition to target position -> use weighted angles
 *    approach
 *  - Add an IKEffector weight parameter, so the user can specify
 *    (between [0..1]) how much influence the solved chains have.
 *  - Apply angles from chain objects back to scene nodes (currently only
 *    translations are applied).
 *  - Add support for enabling/disabling initial pose to support animated
 *    models as well as scene nodes.
 *  - Pole targets?
 *  - Add support for manually updating initial pose.
 *  - Add support for having the initial pose update every time it's solved
 *    -> incremental solving so to speak.
 *  - Apply bullet constraints to joints.
 *  - Script bindings.
 *  - Optimise.
 *  - Profile.
 */

namespace Urho3D
{

class Context;

/// Defines the category under which iceweasel specific components can be found in the editor.
extern const char* ICEWEASELMODS_CATEGORY;

/*!
 * Registers all Ice Weasel modifications.
 */
void RegisterIceWeaselMods(Context* context);

} // namespace Urho3D
