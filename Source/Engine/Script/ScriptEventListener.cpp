//
// Copyright (c) 2008-2013 the Urho3D project.
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

#include "Precompiled.h"
#include "ScriptEventListener.h"

#include <angelscript.h>

namespace Urho3D
{

ScriptEventData::ScriptEventData(asIScriptFunction* function, asIScriptObject* object) :
    sharedbool_(0),
    function_(function),
    object_(object)
{
    if (object_)
    {
        sharedbool_ = object_->GetEngine()->GetWeakRefFlagOfScriptObject(object_, object_->GetObjectType());
        if (sharedbool_)
            sharedbool_->AddRef();
    }
}

ScriptEventData::~ScriptEventData()
{
    if (sharedbool_)
        sharedbool_->Release();

    sharedbool_ = 0;
    function_ = 0;
    object_ = 0;
}

bool ScriptEventData::IsObjectAlive() const
{
    if (sharedbool_)
    {
        // Return inverse as Get returns true when an asIScriptObject is dead.
        return !sharedbool_->Get();
    }

    return true;
}

}