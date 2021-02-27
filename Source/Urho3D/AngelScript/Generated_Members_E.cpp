// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

void FakeAddRef(void* ptr);
void FakeReleaseRef(void* ptr);

// explicit Engine::Engine(Context* context) | File: ../Engine/Engine.h
static Engine* Engine_Engine_Context()
{
    return new Engine(GetScriptContext());
}

// static VariantMap Engine::ParseParameters(const Vector<String>& arguments) | File: ../Engine/Engine.h
static VariantMap Engine_ParseParameters_VectorString(CScriptArray* arguments_conv)
{
    Vector<String> arguments = ArrayToVector<String>(arguments_conv);
    VariantMap result = Engine::ParseParameters(arguments);
    return result;
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Engine_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Engine* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// explicit EventProfiler::EventProfiler(Context* context) | File: ../Core/EventProfiler.h
static EventProfiler* EventProfiler_EventProfiler_Context()
{
    return new EventProfiler(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void EventProfiler_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(EventProfiler* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

void ASRegisterGenerated_Members_E(asIScriptEngine* engine)
{
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Engine", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Engine, AddRef, (), void), AS_CALL_THISCALL);
    // void Engine::ApplyFrameLimit() | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "void ApplyFrameLimit()", AS_METHODPR(Engine, ApplyFrameLimit, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // Console* Engine::CreateConsole() | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "Console@+ CreateConsole()", AS_METHODPR(Engine, CreateConsole, (), Console*), AS_CALL_THISCALL);
    // DebugHud* Engine::CreateDebugHud() | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "DebugHud@+ CreateDebugHud()", AS_METHODPR(Engine, CreateDebugHud, (), DebugHud*), AS_CALL_THISCALL);
    // void Engine::DumpMemory() | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "void DumpMemory()", AS_METHODPR(Engine, DumpMemory, (), void), AS_CALL_THISCALL);
    // void Engine::DumpProfiler() | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "void DumpProfiler()", AS_METHODPR(Engine, DumpProfiler, (), void), AS_CALL_THISCALL);
    // void Engine::DumpResources(bool dumpFileName=false) | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "void DumpResources(bool = false)", AS_METHODPR(Engine, DumpResources, (bool), void), AS_CALL_THISCALL);
    // explicit Engine::Engine(Context* context) | File: ../Engine/Engine.h
    engine->RegisterObjectBehaviour("Engine", asBEHAVE_FACTORY, "Engine@+ f()", AS_FUNCTION(Engine_Engine_Context), AS_CALL_CDECL);
    // void Engine::Exit() | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "void Exit()", AS_METHODPR(Engine, Exit, (), void), AS_CALL_THISCALL);
    // bool Engine::GetAutoExit() const | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "bool GetAutoExit() const", AS_METHODPR(Engine, GetAutoExit, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "bool get_autoExit() const", AS_METHODPR(Engine, GetAutoExit, () const, bool), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "bool GetBlockEvents() const", AS_METHODPR(Engine, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "const String& GetCategory() const", AS_METHODPR(Engine, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "const String& get_category() const", AS_METHODPR(Engine, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "VariantMap& GetEventDataMap() const", AS_METHODPR(Engine, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "Object@+ GetEventSender() const", AS_METHODPR(Engine, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Engine, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Engine, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Engine, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "const VariantMap& get_globalVars() const", AS_METHODPR(Engine, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // int Engine::GetMaxFps() const | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "int GetMaxFps() const", AS_METHODPR(Engine, GetMaxFps, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "int get_maxFps() const", AS_METHODPR(Engine, GetMaxFps, () const, int), AS_CALL_THISCALL);
    // int Engine::GetMaxInactiveFps() const | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "int GetMaxInactiveFps() const", AS_METHODPR(Engine, GetMaxInactiveFps, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "int get_maxInactiveFps() const", AS_METHODPR(Engine, GetMaxInactiveFps, () const, int), AS_CALL_THISCALL);
    // int Engine::GetMinFps() const | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "int GetMinFps() const", AS_METHODPR(Engine, GetMinFps, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "int get_minFps() const", AS_METHODPR(Engine, GetMinFps, () const, int), AS_CALL_THISCALL);
    // float Engine::GetNextTimeStep() const | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "float GetNextTimeStep() const", AS_METHODPR(Engine, GetNextTimeStep, () const, float), AS_CALL_THISCALL);
    // static const Variant& Engine::GetParameter(const VariantMap& parameters, const String& parameter, const Variant& defaultValue=Variant::EMPTY) | File: ../Engine/Engine.h
    engine->SetDefaultNamespace("Engine");
    engine->RegisterGlobalFunction("const Variant& GetParameter(const VariantMap&in, const String&in, const Variant&in = Variant::EMPTY)", AS_FUNCTIONPR(Engine::GetParameter, (const VariantMap&, const String&, const Variant&), const Variant&), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // bool Engine::GetPauseMinimized() const | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "bool GetPauseMinimized() const", AS_METHODPR(Engine, GetPauseMinimized, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "bool get_pauseMinimized() const", AS_METHODPR(Engine, GetPauseMinimized, () const, bool), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Engine, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // int Engine::GetTimeStepSmoothing() const | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "int GetTimeStepSmoothing() const", AS_METHODPR(Engine, GetTimeStepSmoothing, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "int get_timeStepSmoothing() const", AS_METHODPR(Engine, GetTimeStepSmoothing, () const, int), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "StringHash GetType() const", AS_METHODPR(Engine, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "StringHash get_type() const", AS_METHODPR(Engine, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "const String& GetTypeName() const", AS_METHODPR(Engine, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "const String& get_typeName() const", AS_METHODPR(Engine, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "bool HasEventHandlers() const", AS_METHODPR(Engine, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // static bool Engine::HasParameter(const VariantMap& parameters, const String& parameter) | File: ../Engine/Engine.h
    engine->SetDefaultNamespace("Engine");
    engine->RegisterGlobalFunction("bool HasParameter(const VariantMap&in, const String&in)", AS_FUNCTIONPR(Engine::HasParameter, (const VariantMap&, const String&), bool), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Engine, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Engine, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Engine::Initialize(const VariantMap& parameters) | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "bool Initialize(const VariantMap&in)", AS_METHODPR(Engine, Initialize, (const VariantMap&), bool), AS_CALL_THISCALL);
    // bool Engine::InitializeResourceCache(const VariantMap& parameters, bool removeOld=true) | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "bool InitializeResourceCache(const VariantMap&in, bool = true)", AS_METHODPR(Engine, InitializeResourceCache, (const VariantMap&, bool), bool), AS_CALL_THISCALL);
    // bool Engine::IsExiting() const | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "bool IsExiting() const", AS_METHODPR(Engine, IsExiting, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "bool get_exiting() const", AS_METHODPR(Engine, IsExiting, () const, bool), AS_CALL_THISCALL);
    // bool Engine::IsHeadless() const | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "bool IsHeadless() const", AS_METHODPR(Engine, IsHeadless, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "bool get_headless() const", AS_METHODPR(Engine, IsHeadless, () const, bool), AS_CALL_THISCALL);
    // bool Engine::IsInitialized() const | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "bool IsInitialized() const", AS_METHODPR(Engine, IsInitialized, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "bool get_initialized() const", AS_METHODPR(Engine, IsInitialized, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Engine, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Engine, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // static VariantMap Engine::ParseParameters(const Vector<String>& arguments) | File: ../Engine/Engine.h
    engine->SetDefaultNamespace("Engine");
    engine->RegisterGlobalFunction("VariantMap ParseParameters(Array<String>@+)", AS_FUNCTION(Engine_ParseParameters_VectorString), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Engine", "int Refs() const", AS_METHODPR(Engine, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "int get_refs() const", AS_METHODPR(Engine, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Engine", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Engine, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Engine::Render() | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "void Render()", AS_METHODPR(Engine, Render, (), void), AS_CALL_THISCALL);
    // void Engine::RunFrame() | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "void RunFrame()", AS_METHODPR(Engine, RunFrame, (), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "void SendEvent(StringHash)", AS_METHODPR(Engine, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Engine, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Engine::SetAutoExit(bool enable) | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "void SetAutoExit(bool)", AS_METHODPR(Engine, SetAutoExit, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "void set_autoExit(bool)", AS_METHODPR(Engine, SetAutoExit, (bool), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "void SetBlockEvents(bool)", AS_METHODPR(Engine, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Engine, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Engine, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Engine::SetMaxFps(int fps) | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "void SetMaxFps(int)", AS_METHODPR(Engine, SetMaxFps, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "void set_maxFps(int)", AS_METHODPR(Engine, SetMaxFps, (int), void), AS_CALL_THISCALL);
    // void Engine::SetMaxInactiveFps(int fps) | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "void SetMaxInactiveFps(int)", AS_METHODPR(Engine, SetMaxInactiveFps, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "void set_maxInactiveFps(int)", AS_METHODPR(Engine, SetMaxInactiveFps, (int), void), AS_CALL_THISCALL);
    // void Engine::SetMinFps(int fps) | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "void SetMinFps(int)", AS_METHODPR(Engine, SetMinFps, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "void set_minFps(int)", AS_METHODPR(Engine, SetMinFps, (int), void), AS_CALL_THISCALL);
    // void Engine::SetNextTimeStep(float seconds) | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "void SetNextTimeStep(float)", AS_METHODPR(Engine, SetNextTimeStep, (float), void), AS_CALL_THISCALL);
    // void Engine::SetPauseMinimized(bool enable) | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "void SetPauseMinimized(bool)", AS_METHODPR(Engine, SetPauseMinimized, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "void set_pauseMinimized(bool)", AS_METHODPR(Engine, SetPauseMinimized, (bool), void), AS_CALL_THISCALL);
    // void Engine::SetTimeStepSmoothing(int frames) | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "void SetTimeStepSmoothing(int)", AS_METHODPR(Engine, SetTimeStepSmoothing, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "void set_timeStepSmoothing(int)", AS_METHODPR(Engine, SetTimeStepSmoothing, (int), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "void UnsubscribeFromAllEvents()", AS_METHODPR(Engine, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Engine_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Engine, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Engine, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Engine, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // void Engine::Update() | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "void Update()", AS_METHODPR(Engine, Update, (), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Engine", "int WeakRefs() const", AS_METHODPR(Engine, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "int get_weakRefs() const", AS_METHODPR(Engine, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Engine, "Engine")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Engine, "Engine")
#endif
#ifdef REGISTER_MANUAL_PART_Engine
    REGISTER_MANUAL_PART_Engine(Engine, "Engine")
#endif
    RegisterSubclass<Object, Engine>(engine, "Object", "Engine");
    RegisterSubclass<RefCounted, Engine>(engine, "RefCounted", "Engine");

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("EventProfiler", asBEHAVE_ADDREF, "void f()", AS_METHODPR(EventProfiler, AddRef, (), void), AS_CALL_THISCALL);
    // void EventProfiler::BeginBlock(StringHash eventID) | File: ../Core/EventProfiler.h
    engine->RegisterObjectMethod("EventProfiler", "void BeginBlock(StringHash)", AS_METHODPR(EventProfiler, BeginBlock, (StringHash), void), AS_CALL_THISCALL);
    // void Profiler::BeginFrame() | File: ../Core/Profiler.h
    engine->RegisterObjectMethod("EventProfiler", "void BeginFrame()", AS_METHODPR(EventProfiler, BeginFrame, (), void), AS_CALL_THISCALL);
    // void Profiler::BeginInterval() | File: ../Core/Profiler.h
    engine->RegisterObjectMethod("EventProfiler", "void BeginInterval()", AS_METHODPR(EventProfiler, BeginInterval, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Profiler::EndBlock() | File: ../Core/Profiler.h
    engine->RegisterObjectMethod("EventProfiler", "void EndBlock()", AS_METHODPR(EventProfiler, EndBlock, (), void), AS_CALL_THISCALL);
    // void Profiler::EndFrame() | File: ../Core/Profiler.h
    engine->RegisterObjectMethod("EventProfiler", "void EndFrame()", AS_METHODPR(EventProfiler, EndFrame, (), void), AS_CALL_THISCALL);
    // explicit EventProfiler::EventProfiler(Context* context) | File: ../Core/EventProfiler.h
    engine->RegisterObjectBehaviour("EventProfiler", asBEHAVE_FACTORY, "EventProfiler@+ f()", AS_FUNCTION(EventProfiler_EventProfiler_Context), AS_CALL_CDECL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "bool GetBlockEvents() const", AS_METHODPR(EventProfiler, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "const String& GetCategory() const", AS_METHODPR(EventProfiler, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("EventProfiler", "const String& get_category() const", AS_METHODPR(EventProfiler, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // const ProfilerBlock* Profiler::GetCurrentBlock() | File: ../Core/Profiler.h
    // Error: type "ProfilerBlock" can not automatically bind bacause have @nobind mark
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "VariantMap& GetEventDataMap() const", AS_METHODPR(EventProfiler, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "Object@+ GetEventSender() const", AS_METHODPR(EventProfiler, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(EventProfiler, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("EventProfiler", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(EventProfiler, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "const VariantMap& GetGlobalVars() const", AS_METHODPR(EventProfiler, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("EventProfiler", "const VariantMap& get_globalVars() const", AS_METHODPR(EventProfiler, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // const ProfilerBlock* Profiler::GetRootBlock() | File: ../Core/Profiler.h
    // Error: type "ProfilerBlock" can not automatically bind bacause have @nobind mark
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(EventProfiler, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "StringHash GetType() const", AS_METHODPR(EventProfiler, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("EventProfiler", "StringHash get_type() const", AS_METHODPR(EventProfiler, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "const String& GetTypeName() const", AS_METHODPR(EventProfiler, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("EventProfiler", "const String& get_typeName() const", AS_METHODPR(EventProfiler, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "bool HasEventHandlers() const", AS_METHODPR(EventProfiler, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(EventProfiler, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(EventProfiler, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // static bool EventProfiler::IsActive() | File: ../Core/EventProfiler.h
    engine->SetDefaultNamespace("EventProfiler");
    engine->RegisterGlobalFunction("bool IsActive()", AS_FUNCTIONPR(EventProfiler::IsActive, (), bool), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "bool IsInstanceOf(StringHash) const", AS_METHODPR(EventProfiler, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(EventProfiler, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // const String& Profiler::PrintData(bool showUnused=false, bool showTotal=false, unsigned maxDepth=M_MAX_UNSIGNED) const | File: ../Core/Profiler.h
    engine->RegisterObjectMethod("EventProfiler", "const String& PrintData(bool = false, bool = false, uint = M_MAX_UNSIGNED) const", AS_METHODPR(EventProfiler, PrintData, (bool, bool, unsigned) const, const String&), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("EventProfiler", "int Refs() const", AS_METHODPR(EventProfiler, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("EventProfiler", "int get_refs() const", AS_METHODPR(EventProfiler, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("EventProfiler", asBEHAVE_RELEASE, "void f()", AS_METHODPR(EventProfiler, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "void SendEvent(StringHash)", AS_METHODPR(EventProfiler, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(EventProfiler, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // static void EventProfiler::SetActive(bool newActive) | File: ../Core/EventProfiler.h
    engine->SetDefaultNamespace("EventProfiler");
    engine->RegisterGlobalFunction("void SetActive(bool)", AS_FUNCTIONPR(EventProfiler::SetActive, (bool), void), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "void SetBlockEvents(bool)", AS_METHODPR(EventProfiler, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(EventProfiler, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("EventProfiler", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(EventProfiler, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "void UnsubscribeFromAllEvents()", AS_METHODPR(EventProfiler, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(EventProfiler_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(EventProfiler, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(EventProfiler, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(EventProfiler, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("EventProfiler", "int WeakRefs() const", AS_METHODPR(EventProfiler, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("EventProfiler", "int get_weakRefs() const", AS_METHODPR(EventProfiler, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Profiler
    REGISTER_MANUAL_PART_Profiler(EventProfiler, "EventProfiler")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(EventProfiler, "EventProfiler")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(EventProfiler, "EventProfiler")
#endif
#ifdef REGISTER_MANUAL_PART_EventProfiler
    REGISTER_MANUAL_PART_EventProfiler(EventProfiler, "EventProfiler")
#endif
    RegisterSubclass<Profiler, EventProfiler>(engine, "Profiler", "EventProfiler");
    RegisterSubclass<Object, EventProfiler>(engine, "Object", "EventProfiler");
    RegisterSubclass<RefCounted, EventProfiler>(engine, "RefCounted", "EventProfiler");

    // PODVector<Object*> EventReceiverGroup::receivers_ | File: ../Core/Context.h
    // Error: type "PODVector<Object*>" can not automatically bind
    // void EventReceiverGroup::Add(Object* object) | File: ../Core/Context.h
    engine->RegisterObjectMethod("EventReceiverGroup", "void Add(Object@+)", AS_METHODPR(EventReceiverGroup, Add, (Object*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("EventReceiverGroup", asBEHAVE_ADDREF, "void f()", AS_METHODPR(EventReceiverGroup, AddRef, (), void), AS_CALL_THISCALL);
    // void EventReceiverGroup::BeginSendEvent() | File: ../Core/Context.h
    engine->RegisterObjectMethod("EventReceiverGroup", "void BeginSendEvent()", AS_METHODPR(EventReceiverGroup, BeginSendEvent, (), void), AS_CALL_THISCALL);
    // void EventReceiverGroup::EndSendEvent() | File: ../Core/Context.h
    engine->RegisterObjectMethod("EventReceiverGroup", "void EndSendEvent()", AS_METHODPR(EventReceiverGroup, EndSendEvent, (), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("EventReceiverGroup", "int Refs() const", AS_METHODPR(EventReceiverGroup, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("EventReceiverGroup", "int get_refs() const", AS_METHODPR(EventReceiverGroup, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("EventReceiverGroup", asBEHAVE_RELEASE, "void f()", AS_METHODPR(EventReceiverGroup, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void EventReceiverGroup::Remove(Object* object) | File: ../Core/Context.h
    engine->RegisterObjectMethod("EventReceiverGroup", "void Remove(Object@+)", AS_METHODPR(EventReceiverGroup, Remove, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("EventReceiverGroup", "int WeakRefs() const", AS_METHODPR(EventReceiverGroup, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("EventReceiverGroup", "int get_weakRefs() const", AS_METHODPR(EventReceiverGroup, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(EventReceiverGroup, "EventReceiverGroup")
#endif
#ifdef REGISTER_MANUAL_PART_EventReceiverGroup
    REGISTER_MANUAL_PART_EventReceiverGroup(EventReceiverGroup, "EventReceiverGroup")
#endif
    RegisterSubclass<RefCounted, EventReceiverGroup>(engine, "RefCounted", "EventReceiverGroup");

}

}
