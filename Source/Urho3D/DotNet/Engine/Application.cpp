#include "../../Engine/Application.h"
#include "../../DotNet/Defines.h"

using void_function_void = void __CDECL();

class ApplicationEXT : public Application
{
public:
    using Application::Application;

    void_function_void* callbackSetup_ = nullptr;
    void_function_void* callbackStart_ = nullptr;
    void_function_void* callbackStop_ = nullptr;

    virtual void Setup() override
    {
        if (callbackSetup_)
            callbackSetup_();
    }

    virtual void Start() override
    {
        if (callbackStart_)
            callbackStart_();
    }

    virtual void Stop() override
    {
        if (callbackStop_)
            callbackStop_();
    }

    VariantMap* GetEngineParametersPtr()
    {
        return &engineParameters_;
    }
};

extern "C"
{

URHO3D_API ApplicationEXT* ApplicationEXT_ApplicationEXT(Context* nativeContext)
{
    return new ApplicationEXT(nativeContext);
}

URHO3D_API int ApplicationEXT_Run(ApplicationEXT* nativeInstance)
{
    return nativeInstance->Run();
}

URHO3D_API void ApplicationEXT_SetCallback_Setup(ApplicationEXT* nativeInstance, void_function_void* callback)
{
    nativeInstance->callbackSetup_ = callback;
}

URHO3D_API void ApplicationEXT_SetCallback_Start(ApplicationEXT* nativeInstance, void_function_void* callback)
{
    nativeInstance->callbackStart_ = callback;
}

URHO3D_API void ApplicationEXT_SetCallback_Stop(ApplicationEXT* nativeInstance, void_function_void* callback)
{
    nativeInstance->callbackStop_ = callback;
}

URHO3D_API VariantMap* ApplicationEXT_GetEngineParametersPtr(ApplicationEXT* nativeInstance)
{
    return nativeInstance->GetEngineParametersPtr();
}

}
