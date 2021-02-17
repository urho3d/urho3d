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

// EventReceiverGroup::EventReceiverGroup() | File: ../Core/Context.h
static EventReceiverGroup* EventReceiverGroup_EventReceiverGroup_void()
{
    return new EventReceiverGroup();
}

void ASRegisterGenerated_Members_E(asIScriptEngine* engine)
{
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Engine", asBEHAVE_ADDREF, "void f()", asMETHODPR(Engine, AddRef, (), void), asCALL_THISCALL);
    // void Engine::ApplyFrameLimit() | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "void ApplyFrameLimit()", asMETHODPR(Engine, ApplyFrameLimit, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // Console* Engine::CreateConsole() | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "Console@+ CreateConsole()", asMETHODPR(Engine, CreateConsole, (), Console*), asCALL_THISCALL);
    // DebugHud* Engine::CreateDebugHud() | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "DebugHud@+ CreateDebugHud()", asMETHODPR(Engine, CreateDebugHud, (), DebugHud*), asCALL_THISCALL);
    // void Engine::DumpMemory() | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "void DumpMemory()", asMETHODPR(Engine, DumpMemory, (), void), asCALL_THISCALL);
    // void Engine::DumpProfiler() | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "void DumpProfiler()", asMETHODPR(Engine, DumpProfiler, (), void), asCALL_THISCALL);
    // void Engine::DumpResources(bool dumpFileName=false) | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "void DumpResources(bool = false)", asMETHODPR(Engine, DumpResources, (bool), void), asCALL_THISCALL);
    // explicit Engine::Engine(Context* context) | File: ../Engine/Engine.h
    engine->RegisterObjectBehaviour("Engine", asBEHAVE_FACTORY, "Engine@+ f()", asFUNCTION(Engine_Engine_Context), asCALL_CDECL);
    // void Engine::Exit() | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "void Exit()", asMETHODPR(Engine, Exit, (), void), asCALL_THISCALL);
    // bool Engine::GetAutoExit() const | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "bool GetAutoExit() const", asMETHODPR(Engine, GetAutoExit, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "bool get_autoExit() const", asMETHODPR(Engine, GetAutoExit, () const, bool), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "bool GetBlockEvents() const", asMETHODPR(Engine, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "const String& GetCategory() const", asMETHODPR(Engine, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "const String& get_category() const", asMETHODPR(Engine, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "VariantMap& GetEventDataMap() const", asMETHODPR(Engine, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "Object@+ GetEventSender() const", asMETHODPR(Engine, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Engine, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Engine, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "const VariantMap& GetGlobalVars() const", asMETHODPR(Engine, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "const VariantMap& get_globalVars() const", asMETHODPR(Engine, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // int Engine::GetMaxFps() const | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "int GetMaxFps() const", asMETHODPR(Engine, GetMaxFps, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "int get_maxFps() const", asMETHODPR(Engine, GetMaxFps, () const, int), asCALL_THISCALL);
    // int Engine::GetMaxInactiveFps() const | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "int GetMaxInactiveFps() const", asMETHODPR(Engine, GetMaxInactiveFps, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "int get_maxInactiveFps() const", asMETHODPR(Engine, GetMaxInactiveFps, () const, int), asCALL_THISCALL);
    // int Engine::GetMinFps() const | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "int GetMinFps() const", asMETHODPR(Engine, GetMinFps, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "int get_minFps() const", asMETHODPR(Engine, GetMinFps, () const, int), asCALL_THISCALL);
    // float Engine::GetNextTimeStep() const | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "float GetNextTimeStep() const", asMETHODPR(Engine, GetNextTimeStep, () const, float), asCALL_THISCALL);
    // static const Variant& Engine::GetParameter(const VariantMap& parameters, const String& parameter, const Variant& defaultValue=Variant::EMPTY) | File: ../Engine/Engine.h
    engine->SetDefaultNamespace("Engine");
    engine->RegisterGlobalFunction("const Variant& GetParameter(const VariantMap&in, const String&in, const Variant&in = Variant::EMPTY)", asFUNCTIONPR(Engine::GetParameter, (const VariantMap&, const String&, const Variant&), const Variant&), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // bool Engine::GetPauseMinimized() const | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "bool GetPauseMinimized() const", asMETHODPR(Engine, GetPauseMinimized, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "bool get_pauseMinimized() const", asMETHODPR(Engine, GetPauseMinimized, () const, bool), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Engine, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // int Engine::GetTimeStepSmoothing() const | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "int GetTimeStepSmoothing() const", asMETHODPR(Engine, GetTimeStepSmoothing, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "int get_timeStepSmoothing() const", asMETHODPR(Engine, GetTimeStepSmoothing, () const, int), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "StringHash GetType() const", asMETHODPR(Engine, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "StringHash get_type() const", asMETHODPR(Engine, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "const String& GetTypeName() const", asMETHODPR(Engine, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "const String& get_typeName() const", asMETHODPR(Engine, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "bool HasEventHandlers() const", asMETHODPR(Engine, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // static bool Engine::HasParameter(const VariantMap& parameters, const String& parameter) | File: ../Engine/Engine.h
    engine->SetDefaultNamespace("Engine");
    engine->RegisterGlobalFunction("bool HasParameter(const VariantMap&in, const String&in)", asFUNCTIONPR(Engine::HasParameter, (const VariantMap&, const String&), bool), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Engine, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Engine, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Engine::Initialize(const VariantMap& parameters) | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "bool Initialize(const VariantMap&in)", asMETHODPR(Engine, Initialize, (const VariantMap&), bool), asCALL_THISCALL);
    // bool Engine::InitializeResourceCache(const VariantMap& parameters, bool removeOld=true) | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "bool InitializeResourceCache(const VariantMap&in, bool = true)", asMETHODPR(Engine, InitializeResourceCache, (const VariantMap&, bool), bool), asCALL_THISCALL);
    // bool Engine::IsExiting() const | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "bool IsExiting() const", asMETHODPR(Engine, IsExiting, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "bool get_exiting() const", asMETHODPR(Engine, IsExiting, () const, bool), asCALL_THISCALL);
    // bool Engine::IsHeadless() const | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "bool IsHeadless() const", asMETHODPR(Engine, IsHeadless, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "bool get_headless() const", asMETHODPR(Engine, IsHeadless, () const, bool), asCALL_THISCALL);
    // bool Engine::IsInitialized() const | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "bool IsInitialized() const", asMETHODPR(Engine, IsInitialized, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "bool get_initialized() const", asMETHODPR(Engine, IsInitialized, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "bool IsInstanceOf(StringHash) const", asMETHODPR(Engine, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Engine, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // static VariantMap Engine::ParseParameters(const Vector<String>& arguments) | File: ../Engine/Engine.h
    engine->SetDefaultNamespace("Engine");
    engine->RegisterGlobalFunction("VariantMap ParseParameters(Array<String>@+)", asFUNCTION(Engine_ParseParameters_VectorString), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Engine", "int Refs() const", asMETHODPR(Engine, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "int get_refs() const", asMETHODPR(Engine, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Engine", asBEHAVE_RELEASE, "void f()", asMETHODPR(Engine, ReleaseRef, (), void), asCALL_THISCALL);
    // void Engine::Render() | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "void Render()", asMETHODPR(Engine, Render, (), void), asCALL_THISCALL);
    // void Engine::RunFrame() | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "void RunFrame()", asMETHODPR(Engine, RunFrame, (), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "void SendEvent(StringHash)", asMETHODPR(Engine, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Engine, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Engine::SetAutoExit(bool enable) | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "void SetAutoExit(bool)", asMETHODPR(Engine, SetAutoExit, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "void set_autoExit(bool)", asMETHODPR(Engine, SetAutoExit, (bool), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "void SetBlockEvents(bool)", asMETHODPR(Engine, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Engine, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Engine, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Engine::SetMaxFps(int fps) | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "void SetMaxFps(int)", asMETHODPR(Engine, SetMaxFps, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "void set_maxFps(int)", asMETHODPR(Engine, SetMaxFps, (int), void), asCALL_THISCALL);
    // void Engine::SetMaxInactiveFps(int fps) | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "void SetMaxInactiveFps(int)", asMETHODPR(Engine, SetMaxInactiveFps, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "void set_maxInactiveFps(int)", asMETHODPR(Engine, SetMaxInactiveFps, (int), void), asCALL_THISCALL);
    // void Engine::SetMinFps(int fps) | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "void SetMinFps(int)", asMETHODPR(Engine, SetMinFps, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "void set_minFps(int)", asMETHODPR(Engine, SetMinFps, (int), void), asCALL_THISCALL);
    // void Engine::SetNextTimeStep(float seconds) | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "void SetNextTimeStep(float)", asMETHODPR(Engine, SetNextTimeStep, (float), void), asCALL_THISCALL);
    // void Engine::SetPauseMinimized(bool enable) | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "void SetPauseMinimized(bool)", asMETHODPR(Engine, SetPauseMinimized, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "void set_pauseMinimized(bool)", asMETHODPR(Engine, SetPauseMinimized, (bool), void), asCALL_THISCALL);
    // void Engine::SetTimeStepSmoothing(int frames) | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "void SetTimeStepSmoothing(int)", asMETHODPR(Engine, SetTimeStepSmoothing, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "void set_timeStepSmoothing(int)", asMETHODPR(Engine, SetTimeStepSmoothing, (int), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "void UnsubscribeFromAllEvents()", asMETHODPR(Engine, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Engine_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Engine, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Engine, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Engine", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Engine, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // void Engine::Update() | File: ../Engine/Engine.h
    engine->RegisterObjectMethod("Engine", "void Update()", asMETHODPR(Engine, Update, (), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Engine", "int WeakRefs() const", asMETHODPR(Engine, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Engine", "int get_weakRefs() const", asMETHODPR(Engine, WeakRefs, () const, int), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("EventProfiler", asBEHAVE_ADDREF, "void f()", asMETHODPR(EventProfiler, AddRef, (), void), asCALL_THISCALL);
    // void EventProfiler::BeginBlock(StringHash eventID) | File: ../Core/EventProfiler.h
    engine->RegisterObjectMethod("EventProfiler", "void BeginBlock(StringHash)", asMETHODPR(EventProfiler, BeginBlock, (StringHash), void), asCALL_THISCALL);
    // void Profiler::BeginFrame() | File: ../Core/Profiler.h
    engine->RegisterObjectMethod("EventProfiler", "void BeginFrame()", asMETHODPR(EventProfiler, BeginFrame, (), void), asCALL_THISCALL);
    // void Profiler::BeginInterval() | File: ../Core/Profiler.h
    engine->RegisterObjectMethod("EventProfiler", "void BeginInterval()", asMETHODPR(EventProfiler, BeginInterval, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Profiler::EndBlock() | File: ../Core/Profiler.h
    engine->RegisterObjectMethod("EventProfiler", "void EndBlock()", asMETHODPR(EventProfiler, EndBlock, (), void), asCALL_THISCALL);
    // void Profiler::EndFrame() | File: ../Core/Profiler.h
    engine->RegisterObjectMethod("EventProfiler", "void EndFrame()", asMETHODPR(EventProfiler, EndFrame, (), void), asCALL_THISCALL);
    // explicit EventProfiler::EventProfiler(Context* context) | File: ../Core/EventProfiler.h
    engine->RegisterObjectBehaviour("EventProfiler", asBEHAVE_FACTORY, "EventProfiler@+ f()", asFUNCTION(EventProfiler_EventProfiler_Context), asCALL_CDECL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "bool GetBlockEvents() const", asMETHODPR(EventProfiler, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "const String& GetCategory() const", asMETHODPR(EventProfiler, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("EventProfiler", "const String& get_category() const", asMETHODPR(EventProfiler, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // const ProfilerBlock* Profiler::GetCurrentBlock() | File: ../Core/Profiler.h
    // Error: type "ProfilerBlock" can not automatically bind bacause have @nobind mark
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "VariantMap& GetEventDataMap() const", asMETHODPR(EventProfiler, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "Object@+ GetEventSender() const", asMETHODPR(EventProfiler, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(EventProfiler, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("EventProfiler", "const Variant& get_globalVar(StringHash) const", asMETHODPR(EventProfiler, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "const VariantMap& GetGlobalVars() const", asMETHODPR(EventProfiler, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("EventProfiler", "const VariantMap& get_globalVars() const", asMETHODPR(EventProfiler, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // const ProfilerBlock* Profiler::GetRootBlock() | File: ../Core/Profiler.h
    // Error: type "ProfilerBlock" can not automatically bind bacause have @nobind mark
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(EventProfiler, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "StringHash GetType() const", asMETHODPR(EventProfiler, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("EventProfiler", "StringHash get_type() const", asMETHODPR(EventProfiler, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "const String& GetTypeName() const", asMETHODPR(EventProfiler, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("EventProfiler", "const String& get_typeName() const", asMETHODPR(EventProfiler, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "bool HasEventHandlers() const", asMETHODPR(EventProfiler, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(EventProfiler, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(EventProfiler, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // static bool EventProfiler::IsActive() | File: ../Core/EventProfiler.h
    engine->SetDefaultNamespace("EventProfiler");
    engine->RegisterGlobalFunction("bool IsActive()", asFUNCTIONPR(EventProfiler::IsActive, (), bool), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "bool IsInstanceOf(StringHash) const", asMETHODPR(EventProfiler, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(EventProfiler, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // const String& Profiler::PrintData(bool showUnused=false, bool showTotal=false, unsigned maxDepth=M_MAX_UNSIGNED) const | File: ../Core/Profiler.h
    engine->RegisterObjectMethod("EventProfiler", "const String& PrintData(bool = false, bool = false, uint = M_MAX_UNSIGNED) const", asMETHODPR(EventProfiler, PrintData, (bool, bool, unsigned) const, const String&), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("EventProfiler", "int Refs() const", asMETHODPR(EventProfiler, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("EventProfiler", "int get_refs() const", asMETHODPR(EventProfiler, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("EventProfiler", asBEHAVE_RELEASE, "void f()", asMETHODPR(EventProfiler, ReleaseRef, (), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "void SendEvent(StringHash)", asMETHODPR(EventProfiler, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(EventProfiler, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // static void EventProfiler::SetActive(bool newActive) | File: ../Core/EventProfiler.h
    engine->SetDefaultNamespace("EventProfiler");
    engine->RegisterGlobalFunction("void SetActive(bool)", asFUNCTIONPR(EventProfiler::SetActive, (bool), void), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "void SetBlockEvents(bool)", asMETHODPR(EventProfiler, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(EventProfiler, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("EventProfiler", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(EventProfiler, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "void UnsubscribeFromAllEvents()", asMETHODPR(EventProfiler, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(EventProfiler_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(EventProfiler, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(EventProfiler, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("EventProfiler", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(EventProfiler, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("EventProfiler", "int WeakRefs() const", asMETHODPR(EventProfiler, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("EventProfiler", "int get_weakRefs() const", asMETHODPR(EventProfiler, WeakRefs, () const, int), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("EventReceiverGroup", "void Add(Object@+)", asMETHODPR(EventReceiverGroup, Add, (Object*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("EventReceiverGroup", asBEHAVE_ADDREF, "void f()", asMETHODPR(EventReceiverGroup, AddRef, (), void), asCALL_THISCALL);
    // void EventReceiverGroup::BeginSendEvent() | File: ../Core/Context.h
    engine->RegisterObjectMethod("EventReceiverGroup", "void BeginSendEvent()", asMETHODPR(EventReceiverGroup, BeginSendEvent, (), void), asCALL_THISCALL);
    // void EventReceiverGroup::EndSendEvent() | File: ../Core/Context.h
    engine->RegisterObjectMethod("EventReceiverGroup", "void EndSendEvent()", asMETHODPR(EventReceiverGroup, EndSendEvent, (), void), asCALL_THISCALL);
    // EventReceiverGroup::EventReceiverGroup() | File: ../Core/Context.h
    engine->RegisterObjectBehaviour("EventReceiverGroup", asBEHAVE_FACTORY, "EventReceiverGroup@+ f()", asFUNCTION(EventReceiverGroup_EventReceiverGroup_void), asCALL_CDECL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("EventReceiverGroup", "int Refs() const", asMETHODPR(EventReceiverGroup, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("EventReceiverGroup", "int get_refs() const", asMETHODPR(EventReceiverGroup, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("EventReceiverGroup", asBEHAVE_RELEASE, "void f()", asMETHODPR(EventReceiverGroup, ReleaseRef, (), void), asCALL_THISCALL);
    // void EventReceiverGroup::Remove(Object* object) | File: ../Core/Context.h
    engine->RegisterObjectMethod("EventReceiverGroup", "void Remove(Object@+)", asMETHODPR(EventReceiverGroup, Remove, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("EventReceiverGroup", "int WeakRefs() const", asMETHODPR(EventReceiverGroup, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("EventReceiverGroup", "int get_weakRefs() const", asMETHODPR(EventReceiverGroup, WeakRefs, () const, int), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(EventReceiverGroup, "EventReceiverGroup")
#endif
#ifdef REGISTER_MANUAL_PART_EventReceiverGroup
    REGISTER_MANUAL_PART_EventReceiverGroup(EventReceiverGroup, "EventReceiverGroup")
#endif
    RegisterSubclass<RefCounted, EventReceiverGroup>(engine, "RefCounted", "EventReceiverGroup");

}

}
