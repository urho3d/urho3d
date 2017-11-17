#include "../../Core/Object.h"

using namespace Urho3D;

typedef void (__cdecl*HandleEventFunction)(VariantMap& eventData);

class EventHandlerImplDotNet : public EventHandler
{
public:
    EventHandlerImplDotNet(HandleEventFunction function) : EventHandler(nullptr, nullptr)
    {
        function_ = function;
    }

    virtual void Invoke(VariantMap& eventData) override
    {
        if (function_)
            function_(eventData);
    }

    virtual EventHandler* Clone() const override
    {
        return new EventHandlerImplDotNet(function_);
    }

private:
    HandleEventFunction function_;
};




extern "C"
{

/*URHO3D_API EventHandlerImplDotNet* EventHandlerImplDotNet_EventHandlerImplDotNet(HandleEventFunction function)
{
    return new EventHandlerImplDotNet(function);
}*/

URHO3D_API void Object_SubscribeToEvent(Object* nativeInstance, StringHash eventType, HandleEventFunction function)
{
    EventHandlerImplDotNet* eventHandler = new EventHandlerImplDotNet(function);
    nativeInstance->SubscribeToEvent(eventType, eventHandler);
}

}
