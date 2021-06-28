//
// Copyright (c) 2008-2020 the Urho3D project.
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

#include "../Precompiled.h"

#include "../AngelScript/APITemplates.h"
#include "../Core/ProcessUtils.h"
#include "../Core/Spline.h"

namespace Urho3D
{

void ArrayToVariantVector(CScriptArray* arr, VariantVector& dest)
{
    unsigned size = arr->GetSize();
    dest.Resize(size);
    for (unsigned i = 0; i < size; ++i)
        dest[i] = *(static_cast<Variant*>(arr->At(i)));
}

void ArrayToStringVector(CScriptArray* arr, StringVector& dest)
{
    unsigned size = arr->GetSize();
    dest.Resize(size);
    for (unsigned i = 0; i < size; ++i)
        dest[i] = *(static_cast<String*>(arr->At(i)));
}

static void RegisterVariant(asIScriptEngine* engine)
{
    engine->RegisterGlobalFunction("VariantType GetVariantTypeFromName(const String&in)", AS_FUNCTIONPR(Variant::GetTypeFromName, (const String&), VariantType), AS_CALL_CDECL);
    engine->RegisterGlobalFunction("String GetVariantTypeName(VariantType)", AS_FUNCTIONPR(Variant::GetTypeName, (VariantType), String), AS_CALL_CDECL);
}

static String StringJoined(CScriptArray* arr, const String& glue)
{
    Vector<String> subStrings = ArrayToVector<String>(arr);
    return String::Joined(subStrings, glue);
}

static void RegisterStringUtils(asIScriptEngine* engine)
{
    engine->RegisterObjectMethod("String", "bool ToBool() const", AS_FUNCTIONPR_OBJFIRST(ToBool, (const String&), bool), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("String", "float ToFloat() const", AS_FUNCTIONPR_OBJFIRST(ToFloat, (const String&), float), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("String", "double ToDouble() const", AS_FUNCTIONPR_OBJFIRST(ToDouble, (const String&), double), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("String", "int ToInt(int base = 10) const", AS_FUNCTIONPR_OBJFIRST(ToInt, (const String&, int), int), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("String", "uint ToUInt(int base = 10) const", AS_FUNCTIONPR_OBJFIRST(ToUInt, (const String&, int), unsigned), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("String", "int64 ToInt64(int base = 10) const", AS_FUNCTIONPR_OBJFIRST(ToInt64, (const String&, int), long long), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("String", "uint64 ToUInt64(int base = 10) const", AS_FUNCTIONPR_OBJFIRST(ToUInt64, (const String&, int), unsigned long long), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("String", "Color ToColor() const", AS_FUNCTIONPR_OBJFIRST(ToColor, (const String&), Color), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("String", "IntRect ToIntRect() const", AS_FUNCTIONPR_OBJFIRST(ToIntRect, (const String&), IntRect), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("String", "IntVector2 ToIntVector2() const", AS_FUNCTIONPR_OBJFIRST(ToIntVector2, (const String&), IntVector2), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("String", "IntVector3 ToIntVector3() const", AS_FUNCTIONPR_OBJFIRST(ToIntVector3, (const String&), IntVector3), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("String", "Quaternion ToQuaternion() const", AS_FUNCTIONPR_OBJFIRST(ToQuaternion, (const String&), Quaternion), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("String", "Vector2 ToVector2() const", AS_FUNCTIONPR_OBJFIRST(ToVector2, (const String&), Vector2), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("String", "Vector3 ToVector3() const", AS_FUNCTIONPR_OBJFIRST(ToVector3, (const String&), Vector3), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("String", "Vector4 ToVector4(bool allowMissingCoords = false) const", AS_FUNCTIONPR_OBJFIRST(ToVector4, (const String&, bool), Vector4), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("String", "Variant ToVectorVariant() const", AS_FUNCTIONPR_OBJFIRST(ToVectorVariant, (const String&), Variant), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("String", "Matrix3 ToMatrix3() const", AS_FUNCTIONPR_OBJFIRST(ToMatrix3, (const String&), Matrix3), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("String", "Matrix3x4 ToMatrix3x4() const", AS_FUNCTIONPR_OBJFIRST(ToMatrix3x4, (const String&), Matrix3x4), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("String", "Matrix4 ToMatrix4() const", AS_FUNCTIONPR_OBJFIRST(ToMatrix4, (const String&), Matrix4), AS_CALL_CDECL_OBJFIRST);

    //engine->RegisterGlobalFunction("String ToStringHex(int)", asFUNCTION(ToStringHex), asCALL_CDECL);
    engine->RegisterGlobalFunction("String Join(String[]&, const String&in glue)", AS_FUNCTION(StringJoined), AS_CALL_CDECL);
}

static Object* CreateObject(const String& objectType)
{
    if (Context* context = GetScriptContext())
    {
        if (SharedPtr<Object> object = context->CreateObject(objectType))
        {
            object->AddRef();
            return object;
        }
    }
    return nullptr;
}

static void SendEvent(const String& eventType, VariantMap& eventData)
{
    Object* sender = GetScriptContextEventListenerObject();
    if (sender)
        sender->SendEvent(eventType, eventData);
}

static void SubscribeToEvent(const String& eventType, const String& handlerName)
{
    ScriptEventListener* listener = GetScriptContextEventListener();
    if (listener)
        listener->AddEventHandler(eventType, handlerName);
}

static void SubscribeToSenderEvent(Object* sender, const String& eventType, const String& handlerName)
{
    ScriptEventListener* listener = GetScriptContextEventListener();
    if (listener)
        listener->AddEventHandler(sender, eventType, handlerName);
}

static void UnsubscribeFromEvent(const String& eventType)
{
    ScriptEventListener* listener = GetScriptContextEventListener();
    if (listener)
        listener->RemoveEventHandler(eventType);
}

static void UnsubscribeFromSenderEvent(Object* sender, const String& eventType)
{
    ScriptEventListener* listener = GetScriptContextEventListener();
    if (listener)
        listener->RemoveEventHandler(sender, eventType);
}

static void UnsubscribeFromSenderEvents(Object* sender)
{
    ScriptEventListener* listener = GetScriptContextEventListener();
    if (listener)
        listener->RemoveEventHandlers(sender);
}

static void UnsubscribeFromAllEvents()
{
    ScriptEventListener* listener = GetScriptContextEventListener();
    if (listener)
        listener->RemoveEventHandlers();
}

static void UnsubscribeFromAllEventsExcept(CScriptArray* exceptions)
{
    ScriptEventListener* listener = GetScriptContextEventListener();
    if (!listener || !exceptions)
        return;

    unsigned numExceptions = exceptions->GetSize();
    PODVector<StringHash> destExceptions(numExceptions);
    for (unsigned i = 0; i < numExceptions; ++i)
        destExceptions[i] = StringHash(*(static_cast<String*>(exceptions->At(i))));

    listener->RemoveEventHandlersExcept(destExceptions);
}

static bool HasSubscribedToEvent(const String& eventType)
{
    ScriptEventListener* listener = GetScriptContextEventListener();
    return listener ? listener->HasEventHandler(StringHash(eventType)) : false;
}

static bool HasSubscribedToSenderEvent(Object* sender, const String& eventType)
{
    ScriptEventListener* listener = GetScriptContextEventListener();
    return listener ? listener->HasEventHandler(sender, StringHash(eventType)) : false;
}

static void RegisterEventName(const String& eventName)
{
    GetEventNameRegister().RegisterString(eventName.CString());
}

static Object* GetEventSender()
{
    return GetScriptContext()->GetEventSender();
}

static const String& GetTypeName(StringHash type)
{
    return GetScriptContext()->GetTypeName(type);
}

static void SetGlobalVar(const String& key, const Variant& value)
{
    GetScriptContext()->SetGlobalVar(key, value);
}

static Variant GetGlobalVar(const String& key)
{
    return GetScriptContext()->GetGlobalVar(key);
}

static VariantMap& GetGlobalVars()
{
    return const_cast<VariantMap&>(GetScriptContext()->GetGlobalVars());
}

void RegisterObject(asIScriptEngine* engine)
{
    engine->RegisterGlobalFunction("Object@ CreateObject(const String&in)", AS_FUNCTION(CreateObject), AS_CALL_CDECL);
    engine->RegisterGlobalFunction("void SendEvent(const String&in, VariantMap& eventData = VariantMap())", AS_FUNCTION(SendEvent), AS_CALL_CDECL);
    engine->RegisterGlobalFunction("void SubscribeToEvent(const String&in, const String&in)", AS_FUNCTION(SubscribeToEvent), AS_CALL_CDECL);
    engine->RegisterGlobalFunction("void SubscribeToEvent(Object@+, const String&in, const String&in)", AS_FUNCTION(SubscribeToSenderEvent), AS_CALL_CDECL);
    engine->RegisterGlobalFunction("void UnsubscribeFromEvent(const String&in)", AS_FUNCTION(UnsubscribeFromEvent), AS_CALL_CDECL);
    engine->RegisterGlobalFunction("void UnsubscribeFromEvent(Object@+, const String&in)", AS_FUNCTION(UnsubscribeFromSenderEvent), AS_CALL_CDECL);
    engine->RegisterGlobalFunction("void UnsubscribeFromEvents(Object@+)", AS_FUNCTION(UnsubscribeFromSenderEvents), AS_CALL_CDECL);
    engine->RegisterGlobalFunction("void UnsubscribeFromAllEvents()", AS_FUNCTION(UnsubscribeFromAllEvents), AS_CALL_CDECL);
    engine->RegisterGlobalFunction("void UnsubscribeFromAllEventsExcept(Array<String>@+)", AS_FUNCTION(UnsubscribeFromAllEventsExcept), AS_CALL_CDECL);
    engine->RegisterGlobalFunction("bool HasSubscribedToEvent(const String&in)", AS_FUNCTION(HasSubscribedToEvent), AS_CALL_CDECL);
    engine->RegisterGlobalFunction("bool HasSubscribedToEvent(Object@+, const String&in)", AS_FUNCTION(HasSubscribedToSenderEvent), AS_CALL_CDECL);
    engine->RegisterGlobalFunction("void RegisterEventName(const String&in)", AS_FUNCTION(RegisterEventName), AS_CALL_CDECL);
    engine->RegisterGlobalFunction("Object@+ GetEventSender()", AS_FUNCTION(GetEventSender), AS_CALL_CDECL);
    engine->RegisterGlobalFunction("const String& GetTypeName(StringHash)", AS_FUNCTION(GetTypeName), AS_CALL_CDECL);
    engine->RegisterGlobalFunction("void SetGlobalVar(const String&in, Variant&in)", AS_FUNCTION(SetGlobalVar), AS_CALL_CDECL);
    engine->RegisterGlobalFunction("Variant GetGlobalVar(const String&in)", AS_FUNCTION(GetGlobalVar), AS_CALL_CDECL);
    engine->RegisterGlobalFunction("VariantMap& get_globalVars()", AS_FUNCTION(GetGlobalVars), AS_CALL_CDECL);
}

void RegisterCoreAPI(asIScriptEngine* engine)
{
    RegisterVariant(engine);
    RegisterStringUtils(engine);
    RegisterObject(engine);
}

}
