#include "../../Core/Object.h"
#include "../Defines.h"

using namespace Urho3D;

using void_function_VariantMap = void __CDECL(VariantMap& eventData);

class EventHandlerImplDotNet : public EventHandler
{
public:
    EventHandlerImplDotNet(void_function_VariantMap* function) : EventHandler(nullptr, nullptr)
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

    ~EventHandlerImplDotNet()
    {
    }

private:
    void_function_VariantMap* function_;
};

extern "C"
{

URHO3D_API void Object_SubscribeToEvent(Object* nativeInstance, StringHash eventType, void_function_VariantMap function)
{
    EventHandlerImplDotNet* eventHandler = new EventHandlerImplDotNet(function);
    nativeInstance->SubscribeToEvent(eventType, eventHandler);
}

}
