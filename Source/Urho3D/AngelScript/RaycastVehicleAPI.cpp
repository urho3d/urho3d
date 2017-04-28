#ifdef URHO3D_PHYSICS

#include "../Precompiled.h"

#include "../AngelScript/APITemplates.h"
#include "../RaycastVehicle/RaycastVehicle.h"
#include "../IO/Log.h"

namespace Urho3D
{

void RegisterRaycastVehicleAPI(asIScriptEngine* engine)
{
    URHO3D_LOGINFO("RegisterRaycastVehicleAPI");
    RegisterComponent<RaycastVehicle>(engine, "RaycastVehicle");
    engine->RegisterObjectMethod("RaycastVehicle", "void Init()", asMETHOD(RaycastVehicle, Init), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "void AddWheel(Node@+, Vector3, Vector3, Vector3, float, float, bool)", asMETHOD(RaycastVehicle, AddWheel), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "void ResetSuspension()", asMETHOD(RaycastVehicle, ResetSuspension), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "void UpdateWheelTransform(int, bool)", asMETHOD(RaycastVehicle, UpdateWheelTransform), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "Vector3 GetWheelPosition(int)", asMETHOD(RaycastVehicle, GetWheelPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "int get_numWheels()", asMETHOD(RaycastVehicle, GetNumWheels), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "void SetWheelSuspensionStiffness(int, float)", asMETHOD(RaycastVehicle, SetWheelSuspensionStiffness), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "void SetWheelDampingRelaxation(int, float)", asMETHOD(RaycastVehicle, SetWheelDampingRelaxation), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "void SetWheelDampingCompression(int, float)", asMETHOD(RaycastVehicle, SetWheelDampingCompression), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "void SetWheelFrictionSlip(int, float)", asMETHOD(RaycastVehicle, SetWheelFrictionSlip), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "void SetWheelRollInfluence(int, float)", asMETHOD(RaycastVehicle, SetWheelRollInfluence), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "Quaternion GetWheelRotation(int)", asMETHOD(RaycastVehicle, GetWheelRotation), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "Node@+ GetWheelNode(int)", asMETHOD(RaycastVehicle, GetWheelNode), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "Vector3 GetWheelConnectionPoint(int)", asMETHOD(RaycastVehicle, GetWheelConnectionPoint), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "void SetSteeringValue(int, float)", asMETHOD(RaycastVehicle, SetSteeringValue), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "void SetEngineForce(int, float)", asMETHOD(RaycastVehicle, SetEngineForce), asCALL_THISCALL);
}

}
#endif
