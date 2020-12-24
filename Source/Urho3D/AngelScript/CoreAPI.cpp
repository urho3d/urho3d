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
    engine->RegisterGlobalFunction("VariantType GetVariantTypeFromName(const String&in)", asFUNCTIONPR(Variant::GetTypeFromName, (const String&), VariantType), asCALL_CDECL);
    engine->RegisterGlobalFunction("String GetVariantTypeName(VariantType)", asFUNCTIONPR(Variant::GetTypeName, (VariantType), String), asCALL_CDECL);
}

static String StringJoined(CScriptArray* arr, const String& glue)
{
    Vector<String> subStrings = ArrayToVector<String>(arr);
    return String::Joined(subStrings, glue);
}

static void RegisterStringUtils(asIScriptEngine* engine)
{
    engine->RegisterObjectMethod("String", "bool ToBool() const", asFUNCTIONPR(ToBool, (const String&), bool), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "float ToFloat() const", asFUNCTIONPR(ToFloat, (const String&), float), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "double ToDouble() const", asFUNCTIONPR(ToDouble, (const String&), double), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "int ToInt(int base = 10) const", asFUNCTIONPR(ToInt, (const String&, int), int), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("String", "uint ToUInt(int base = 10) const", asFUNCTIONPR(ToUInt, (const String&, int), unsigned), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("String", "int64 ToInt64(int base = 10) const", asFUNCTIONPR(ToInt64, (const String&, int), long long), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("String", "uint64 ToUInt64(int base = 10) const", asFUNCTIONPR(ToUInt64, (const String&, int), unsigned long long), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("String", "Color ToColor() const", asFUNCTIONPR(ToColor, (const String&), Color), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "IntRect ToIntRect() const", asFUNCTIONPR(ToIntRect, (const String&), IntRect), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "IntVector2 ToIntVector2() const", asFUNCTIONPR(ToIntVector2, (const String&), IntVector2), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "IntVector3 ToIntVector3() const", asFUNCTIONPR(ToIntVector3, (const String&), IntVector3), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "Quaternion ToQuaternion() const", asFUNCTIONPR(ToQuaternion, (const String&), Quaternion), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "Vector2 ToVector2() const", asFUNCTIONPR(ToVector2, (const String&), Vector2), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "Vector3 ToVector3() const", asFUNCTIONPR(ToVector3, (const String&), Vector3), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "Vector4 ToVector4(bool allowMissingCoords = false) const", asFUNCTIONPR(ToVector4, (const String&, bool), Vector4), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("String", "Variant ToVectorVariant() const", asFUNCTIONPR(ToVectorVariant, (const String&), Variant), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "Matrix3 ToMatrix3() const", asFUNCTIONPR(ToMatrix3, (const String&), Matrix3), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "Matrix3x4 ToMatrix3x4() const", asFUNCTIONPR(ToMatrix3x4, (const String&), Matrix3x4), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "Matrix4 ToMatrix4() const", asFUNCTIONPR(ToMatrix4, (const String&), Matrix4), asCALL_CDECL_OBJLAST);

    //engine->RegisterGlobalFunction("String ToStringHex(int)", asFUNCTION(ToStringHex), asCALL_CDECL);
    engine->RegisterGlobalFunction("String Join(String[]&, const String&in glue)", asFUNCTION(StringJoined), asCALL_CDECL);
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
    engine->RegisterGlobalFunction("Object@ CreateObject(const String&in)", asFUNCTION(CreateObject), asCALL_CDECL);
    engine->RegisterGlobalFunction("void SendEvent(const String&in, VariantMap& eventData = VariantMap())", asFUNCTION(SendEvent), asCALL_CDECL);
    engine->RegisterGlobalFunction("void SubscribeToEvent(const String&in, const String&in)", asFUNCTION(SubscribeToEvent), asCALL_CDECL);
    engine->RegisterGlobalFunction("void SubscribeToEvent(Object@+, const String&in, const String&in)", asFUNCTION(SubscribeToSenderEvent), asCALL_CDECL);
    engine->RegisterGlobalFunction("void UnsubscribeFromEvent(const String&in)", asFUNCTION(UnsubscribeFromEvent), asCALL_CDECL);
    engine->RegisterGlobalFunction("void UnsubscribeFromEvent(Object@+, const String&in)", asFUNCTION(UnsubscribeFromSenderEvent), asCALL_CDECL);
    engine->RegisterGlobalFunction("void UnsubscribeFromEvents(Object@+)", asFUNCTION(UnsubscribeFromSenderEvents), asCALL_CDECL);
    engine->RegisterGlobalFunction("void UnsubscribeFromAllEvents()", asFUNCTION(UnsubscribeFromAllEvents), asCALL_CDECL);
    engine->RegisterGlobalFunction("void UnsubscribeFromAllEventsExcept(Array<String>@+)", asFUNCTION(UnsubscribeFromAllEventsExcept), asCALL_CDECL);
    engine->RegisterGlobalFunction("bool HasSubscribedToEvent(const String&in)", asFUNCTION(HasSubscribedToEvent), asCALL_CDECL);
    engine->RegisterGlobalFunction("bool HasSubscribedToEvent(Object@+, const String&in)", asFUNCTION(HasSubscribedToSenderEvent), asCALL_CDECL);
    engine->RegisterGlobalFunction("void RegisterEventName(const String&in)", asFUNCTION(RegisterEventName), asCALL_CDECL);
    engine->RegisterGlobalFunction("Object@+ GetEventSender()", asFUNCTION(GetEventSender), asCALL_CDECL);
    engine->RegisterGlobalFunction("const String& GetTypeName(StringHash)", asFUNCTION(GetTypeName), asCALL_CDECL);
    engine->RegisterGlobalFunction("void SetGlobalVar(const String&in, Variant&in)", asFUNCTION(SetGlobalVar), asCALL_CDECL);
    engine->RegisterGlobalFunction("Variant GetGlobalVar(const String&in)", asFUNCTION(GetGlobalVar), asCALL_CDECL);
    engine->RegisterGlobalFunction("VariantMap& get_globalVars()", asFUNCTION(GetGlobalVars), asCALL_CDECL);
}

void RegisterCoreAPI(asIScriptEngine* engine)
{
    RegisterVariant(engine);
    RegisterStringUtils(engine);
    RegisterObject(engine);
}

}
