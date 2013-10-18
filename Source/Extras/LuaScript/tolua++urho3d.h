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

#pragma once

#include "Vector2.h"

struct lua_State;

namespace Urho3D
{
    class UIElement;
}

using namespace Urho3D;

/// Check is String.
#define tolua_isurho3dstring tolua_isstring
/// Push String.
#define tolua_pushurho3dstring(x, y) tolua_pushstring(x, y.CString())
/// Convert to String.
const char* tolua_tourho3dstring(lua_State* L, int narg, const char* def);
const char* tolua_tourho3dstring(lua_State* L, int narg, const String& def);

/// Convert to HttpRequest.
void* tolua_tourho3dhttprequest(lua_State* L, int reg, void* def);

/// Push const PODVector<IntVector2>.
int tolua_pushurho3dconstpodvectorintvector2(lua_State* L, void* data, const char* type);

/// Push const PODVector<UIElement*>.
int tolua_pushurho3dpodvectoruielement(lua_State* L, void* data, const char* type);

/// Check is const PODVector<unsigned>.
int tolua_isurho3dconstpodvectorunsigned(lua_State* L, int lo, const char* type, int def, tolua_Error* err);
/// Convert to const PODVector<unsigned>.
void* tolua_tourho3dconstpodvectorunsigned(lua_State* L, int narg, void* def);
/// Push const PODVector<unsigned>.
int tolua_pushurho3dconstpodvectorunsigned(lua_State* L, void* data, const char* type);

/// Check is const Vector<String>.
int tolua_isurho3dconstvectorstring(lua_State* L, int lo, const char* type, int def, tolua_Error* err);
/// Convert to const Vector<String>.
void* tolua_tourho3dconstvectorstring(lua_State* L, int narg, void* def);
/// Push const Vector<String>.
int tolua_pushurho3dconstvectorstring(lua_State* L, void* data, const char* type);