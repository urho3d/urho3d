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

struct lua_State;

using namespace Urho3D;

#define tolua_isurho3dstring tolua_isstring
#define tolua_pushurho3dstring(x,y)	tolua_pushstring(x,y.CString())

/// Convert Lua string to Urho3D string.
const char* tolua_tourho3dstring(lua_State* L, int narg, const char* def);
const char* tolua_tourho3dstring(lua_State* L, int narg, const String& def);

/// Check is const Vector<String>.
int tolua_isurho3dconstvectorstring(lua_State* L, int lo, const char* type, int def, tolua_Error* err);
/// Convert to const Vector<String>.
void* tolua_tourho3dconstvectorstring(lua_State* L, int narg, void* def);
/// Push const Vector<String>.
int tolua_pushurho3dconstvectorstring(lua_State* L, void* data, const char* type);