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
#include "APITemplates.h"
#include "Navigable.h"
#include "NavigationMesh.h"

namespace Urho3D
{

void RegisterNavigable(asIScriptEngine* engine)
{
    RegisterComponent<Navigable>(engine, "Navigable");
}

void RegisterNavigationMesh(asIScriptEngine* engine)
{
    RegisterComponent<NavigationMesh>(engine, "NavigationMesh");
    engine->RegisterObjectMethod("NavigationMesh", "bool Build()", asMETHOD(NavigationMesh, Build), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_cellSize(float)", asMETHOD(NavigationMesh, SetCellSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_cellSize() const", asMETHOD(NavigationMesh, GetCellSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_cellHeight(float)", asMETHOD(NavigationMesh, SetCellHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_cellHeight() const", asMETHOD(NavigationMesh, GetCellHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_agentHeight(float)", asMETHOD(NavigationMesh, SetAgentHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_agentHeight() const", asMETHOD(NavigationMesh, GetAgentHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_agentRadius(float)", asMETHOD(NavigationMesh, SetAgentRadius), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_agentRadius() const", asMETHOD(NavigationMesh, GetAgentRadius), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_agentMaxClimb(float)", asMETHOD(NavigationMesh, SetAgentMaxClimb), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_agentMaxClimb() const", asMETHOD(NavigationMesh, GetAgentMaxClimb), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_agentMaxSlope(float)", asMETHOD(NavigationMesh, SetAgentMaxSlope), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_agentMaxSlope() const", asMETHOD(NavigationMesh, GetAgentMaxSlope), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_regionMinSize(float)", asMETHOD(NavigationMesh, SetRegionMinSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_regionMinSize() const", asMETHOD(NavigationMesh, GetRegionMinSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_regionMergeSize(float)", asMETHOD(NavigationMesh, SetRegionMergeSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_regionMergeSize() const", asMETHOD(NavigationMesh, GetRegionMergeSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_edgeMaxLength(float)", asMETHOD(NavigationMesh, SetEdgeMaxLength), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_edgeMaxLength() const", asMETHOD(NavigationMesh, GetEdgeMaxLength), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_edgeMaxError(float)", asMETHOD(NavigationMesh, SetEdgeMaxError), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_edgeMaxError() const", asMETHOD(NavigationMesh, GetEdgeMaxError), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_detailSampleDistance(float)", asMETHOD(NavigationMesh, SetDetailSampleDistance), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_detailSampleDistance() const", asMETHOD(NavigationMesh, GetDetailSampleDistance), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_detailSampleMaxError(float)", asMETHOD(NavigationMesh, SetDetailSampleMaxError), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_detailSampleMaxError() const", asMETHOD(NavigationMesh, GetDetailSampleMaxError), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "const BoundingBox& get_worldBoundingBox()", asMETHOD(NavigationMesh, GetWorldBoundingBox), asCALL_THISCALL);
}

void RegisterNavigationAPI(asIScriptEngine* engine)
{
    RegisterNavigable(engine);
    RegisterNavigationMesh(engine);
}

}
