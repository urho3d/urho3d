#include "../../Core/Object.h"
#include "../../DotNet/Defines.h"

using void_function_StringHash_VariantMap = void __CDECL(StringHash, VariantMap&);

class EventHandlerImplDotNet : public EventHandler
{
public:
    EventHandlerImplDotNet(void_function_StringHash_VariantMap* function) : EventHandler(nullptr, nullptr)
    {
        function_ = function;
    }

    virtual void Invoke(VariantMap& eventData) override
    {
        if (function_)
            function_(eventType_, eventData);
    }

    virtual EventHandler* Clone() const override
    {
        return new EventHandlerImplDotNet(function_);
    }

private:
    void_function_StringHash_VariantMap* function_;
};

extern "C"
{

URHO3D_API void Object_SubscribeToEvent(Object* nativeInstance, StringHash eventType, void_function_StringHash_VariantMap* function)
{
    EventHandlerImplDotNet* eventHandler = new EventHandlerImplDotNet(function);
    nativeInstance->SubscribeToEvent(eventType, eventHandler);
}

}
