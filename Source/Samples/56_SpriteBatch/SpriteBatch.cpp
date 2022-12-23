#include <Urho3D/Urho3DAll.h>

#include <Urho3D/Graphics/SpriteBatch.h>

class Game : public Application
{
    URHO3D_OBJECT(Game, Application);

public:
    SharedPtr<Scene> scene_;
    SharedPtr<Node> cameraNode_;
    float yaw_ = 0.0f;
    float pitch_ = 0.0f;
    SharedPtr<SpriteBatch> worldSpaceSpriteBatch_;
    SharedPtr<SpriteBatch> screenSpaceSpriteBatch_;
    SharedPtr<SpriteBatch> virtualSpriteBatch_;
    float fpsTimeCounter_ = 0.0f;
    i32 fpsFrameCounter_ = 0;
    i32 fpsValue_ = 0;
    i32 currentTest_ = 1;
    float angle_ = 0.0f;
    float scale_ = 0.0f;

    Game(Context* context) : Application(context)
    {
    }

    void Setup()
    {
        engineParameters_[EP_WINDOW_RESIZABLE] = true;
        engineParameters_[EP_FULL_SCREEN] = false;
        engineParameters_[EP_WINDOW_WIDTH] = 1200;
        engineParameters_[EP_WINDOW_HEIGHT] = 900;
        engineParameters_[EP_FRAME_LIMITER] = false;
        engineParameters_[EP_LOG_NAME] = GetSubsystem<FileSystem>()->GetAppPreferencesDir("urho3d", "logs") + "56_SpriteBatch.log";
    }

    void Start()
    {
        //GetSubsystem<Engine>()->SetMaxFps(10);

        CreateScene();
        SetupViewport();
        SubscribeToEvents();

        XMLFile* xmlFile = GetSubsystem<ResourceCache>()->GetResource<XMLFile>("UI/DefaultStyle.xml");
        DebugHud* debugHud = engine_->CreateDebugHud();
        debugHud->SetDefaultStyle(xmlFile);

        screenSpaceSpriteBatch_ = new SpriteBatch(context_);
        
        worldSpaceSpriteBatch_ = new SpriteBatch(context_);
        worldSpaceSpriteBatch_->camera_ = cameraNode_->GetComponent<Camera>();
        worldSpaceSpriteBatch_->compareMode_ = CMP_LESSEQUAL;

        virtualSpriteBatch_ = new SpriteBatch(context_);
        virtualSpriteBatch_->virtualScreenSize_ = IntVector2(700, 600);
    }

    void SetupViewport()
    {
        SharedPtr<Viewport> viewport(new Viewport(context_, scene_, cameraNode_->GetComponent<Camera>()));
        GetSubsystem<Renderer>()->SetViewport(0, viewport);
    }

    void CreateScene()
    {
        ResourceCache* cache = GetSubsystem<ResourceCache>();

        scene_ = new Scene(context_);
        scene_->CreateComponent<Octree>();

        Node* planeNode = scene_->CreateChild("Plane");
        planeNode->SetScale(Vector3(100.0f, 1.0f, 100.0f));
        StaticModel* planeObject = planeNode->CreateComponent<StaticModel>();
        planeObject->SetModel(cache->GetResource<Model>("Models/Plane.mdl"));
        planeObject->SetMaterial(cache->GetResource<Material>("Materials/StoneTiled.xml"));

        Node* lightNode = scene_->CreateChild("DirectionalLight");
        lightNode->SetDirection(Vector3(0.6f, -1.0f, 0.8f));
        Light* light = lightNode->CreateComponent<Light>();
        light->SetColor(Color(0.5f, 0.5f, 0.5f));
        light->SetLightType(LIGHT_DIRECTIONAL);
        light->SetCastShadows(true);
        light->SetShadowBias(BiasParameters(0.00025f, 0.5f));
        light->SetShadowCascade(CascadeParameters(10.0f, 50.0f, 200.0f, 0.0f, 0.8f));
        //light->SetShadowIntensity(0.5f);

        Node* zoneNode = scene_->CreateChild("Zone");
        Zone* zone = zoneNode->CreateComponent<Zone>();
        zone->SetBoundingBox(BoundingBox(-1000.0f, 1000.0f));
        zone->SetAmbientColor(Color(0.5f, 0.5f, 0.5f));
        zone->SetFogColor(Color(0.4f, 0.5f, 0.8f));
        zone->SetFogStart(100.0f);
        zone->SetFogEnd(300.0f);

        constexpr i32 NUM_OBJECTS = 20;
        for (i32 i = 0; i < NUM_OBJECTS; ++i)
        {
            Node* mushroomNode = scene_->CreateChild("Mushroom");
            mushroomNode->SetPosition(Vector3(Random(90.0f) - 45.0f, 0.0f, Random(90.0f) - 45.0f));
            mushroomNode->SetRotation(Quaternion(0.0f, Random(360.0f), 0.0f));
            mushroomNode->SetScale(0.5f + Random(2.0f));
            StaticModel* mushroomObject = mushroomNode->CreateComponent<StaticModel>();
            mushroomObject->SetModel(cache->GetResource<Model>("Models/Mushroom.mdl"));
            mushroomObject->SetMaterial(cache->GetResource<Material>("Materials/Mushroom.xml"));
            mushroomObject->SetCastShadows(true);
        }

        cameraNode_ = scene_->CreateChild("Camera");
        cameraNode_->CreateComponent<Camera>();
        cameraNode_->SetPosition(Vector3(0.0f, 2.0f, -5.0f));
    }

    void MoveCamera(float timeStep)
    {
        constexpr float MOVE_SPEED = 20.0f;
        constexpr float MOUSE_SENSITIVITY = 0.1f;

        Input* input = GetSubsystem<Input>();

        IntVector2 mouseMove = input->GetMouseMove();
        yaw_ += MOUSE_SENSITIVITY * mouseMove.x_;
        pitch_ += MOUSE_SENSITIVITY * mouseMove.y_;
        pitch_ = Clamp(pitch_, -90.0f, 90.0f);
        cameraNode_->SetRotation(Quaternion(pitch_, yaw_, 0.0f));

        if (input->GetKeyDown(KEY_W))
            cameraNode_->Translate(Vector3::FORWARD * MOVE_SPEED * timeStep);
        if (input->GetKeyDown(KEY_S))
            cameraNode_->Translate(Vector3::BACK * MOVE_SPEED * timeStep);
        if (input->GetKeyDown(KEY_A))
            cameraNode_->Translate(Vector3::LEFT * MOVE_SPEED * timeStep);
        if (input->GetKeyDown(KEY_D))
            cameraNode_->Translate(Vector3::RIGHT * MOVE_SPEED * timeStep);

    }

    void SubscribeToEvents()
    {
        SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(Game, HandleUpdate));
        SubscribeToEvent(E_ENDVIEWRENDER, URHO3D_HANDLER(Game, HandleEndViewRender));
    }

    void HandleUpdate(StringHash eventType, VariantMap& eventData)
    {
        using namespace Update;
        float timeStep = eventData[P_TIMESTEP].GetFloat();

        Input* input = GetSubsystem<Input>();
        Time* time = GetSubsystem<Time>();

        if (input->GetKeyDown(KEY_1))
            currentTest_ = 1;
        else if (input->GetKeyDown(KEY_2))
            currentTest_ = 2;
        else if (input->GetKeyDown(KEY_3))
            currentTest_ = 3;

        if (input->GetMouseButtonDown(MOUSEB_RIGHT))
        {
            input->SetMouseVisible(false);
            MoveCamera(timeStep);
        }
        else
        {
            input->SetMouseVisible(true);
        }

        fpsTimeCounter_ += timeStep;
        fpsFrameCounter_++;

        if (fpsTimeCounter_ >= 1.0f)
        {
            fpsTimeCounter_ = 0.0f;
            fpsValue_ = fpsFrameCounter_;
            fpsFrameCounter_ = 0;
        }

        angle_ += timeStep * 100.0f;
        angle_ = fmod(angle_, 360.0f);

        scale_ = 1.0f + Sin(time->GetElapsedTime() * 200.0f) * 0.3f;
    }

    bool collide_ = true;

    void HandleEndViewRender(StringHash eventType, VariantMap& eventData)
    {
        Input* input = GetSubsystem<Input>();
        ResourceCache* cache = GetSubsystem<ResourceCache>();
        Graphics* graphics = GetSubsystem<Graphics>();

        // Размер текстуры должен быть степенью двойки (64, 128, 256, ...),
        // иначе она не будет работать в GL ES 1.0 (в вебе).
        // В некоторых случаях (например для "Urho2D/Stretchable.png" - 200x200) может помочь
        // Texture2D* head = cache->GetResource<Texture2D>("Urho2D/Stretchable.png");
        // if (head->GetAddressMode(COORD_U) == ADDRESS_WRAP)
        // {
        //     head->SetAddressMode(COORD_U, ADDRESS_CLAMP);
        //     head->SetAddressMode(COORD_V, ADDRESS_CLAMP);
        // }
        // как это сделано в Sprite2D.cpp.
        // В других случаях ("Urho2D/imp/imp_head.png" - 238x149) и это не помогает.

        Texture2D* head = cache->GetResource<Texture2D>("Textures/FishBoneLogo.png");
        Font* font = cache->GetResource<Font>("Fonts/Anonymous Pro.ttf");

        // Очистка экрана. Если сцена пустая, то можно просто задать цвет зоны
        //GetSubsystem<Graphics>()->Clear(CLEAR_COLOR, Color::GREEN);

        String str;

        if (currentTest_ == 1)
        {
            screenSpaceSpriteBatch_->SetShapeColor(0xFFFF0000);
            screenSpaceSpriteBatch_->DrawCircle(500.f, 200.f, 200.f);

            Vector2 origin = Vector2(head->GetWidth() * 0.5f, head->GetHeight() * 0.5f);
            screenSpaceSpriteBatch_->DrawSprite(head, Vector2(200.0f, 200.0f), nullptr, 0xFFFFFFFF, angle_, origin, Vector2(scale_, scale_));

            str = "QqWЙйр";
            screenSpaceSpriteBatch_->DrawString(str, font, 20.f, Vector2(4.0f, 60.f), 0xFF00FF00, 0.0f, Vector2::ZERO, Vector2::ONE, FlipModes::None);
            screenSpaceSpriteBatch_->DrawString(str, font, 20.f, Vector2(104.0f, 60.f), 0xFF00FF00, 0.0f, Vector2::ZERO, Vector2::ONE, FlipModes::Horizontally);
            screenSpaceSpriteBatch_->DrawString(str, font, 20.f, Vector2(4.0f, 100.f), 0xFF00FF00, 0.0f, Vector2::ZERO, Vector2::ONE, FlipModes::Vertically);
            screenSpaceSpriteBatch_->DrawString(str, font, 20.f, Vector2(104.0f, 100.f), 0xFF00FF00, 0.0f, Vector2::ZERO, Vector2::ONE, FlipModes::Vertically | FlipModes::Both);

            // screenSpaceSpriteBatch_->Flush(); не вызываем, так как еще текст будем выводить
        }
        else if (currentTest_ == 2)
        {
            worldSpaceSpriteBatch_->DrawSprite(head, Vector2(0.0f, 0.0f), nullptr, 0xFFFFFFFF, 0.0f, Vector2::ZERO, Vector2(0.01f, 0.01f));
            worldSpaceSpriteBatch_->Flush();
        }
        else if (currentTest_ == 3)
        {
            virtualSpriteBatch_->SetShapeColor(0x90FF0000);
            virtualSpriteBatch_->DrawAABBSolid(Vector2::ZERO, (Vector2)virtualSpriteBatch_->virtualScreenSize_);
            virtualSpriteBatch_->DrawSprite(head, Vector2(200.0f, 200.0f));
            // Преобразуем координаты мыши из оконных координат в виртуальные координаты
            Vector2 virtualMousePos = virtualSpriteBatch_->GetVirtualPos(Vector2(GetSubsystem<Input>()->GetMousePosition()));
            virtualSpriteBatch_->SetShapeColor(0xFFFFFFFF);
            virtualSpriteBatch_->DrawArrow({100.0f, 100.f}, virtualMousePos, 10);
            virtualSpriteBatch_->Flush();
        }

        // Выводим индекс текущего теста
        str = "Текущий тест: " + String(currentTest_) + " (используйте 1, 2, 3 для переключения)";
        screenSpaceSpriteBatch_->DrawString(str, font, 20.f, Vector2(4.0f, 0.f), 0xFFFFFFFF);

        // Выводим описание текущего теста
        if (currentTest_ == 1)
        {
            str = "Рисование в экранном пространстве";
            screenSpaceSpriteBatch_->DrawString(str, font, 20.f, Vector2(4.0f, 24.f), 0xFFFFFFFF);
        }
        else if (currentTest_ == 2)
        {
            str = "Рисование в пространстве сцены";
            screenSpaceSpriteBatch_->DrawString(str, font, 20.f, Vector2(4.0f, 24.f), 0xFFFFFFFF);
        }
        else if (currentTest_ == 3)
        {
            str = "Использование виртуальных координат";
            screenSpaceSpriteBatch_->DrawString(str, font, 20.f, Vector2(4.0f, 24.f), 0xFFFFFFFF);

            str = "Синий прямоугольник - границы виртуального экрана (700x600 виртуальных пикселей)";
            screenSpaceSpriteBatch_->DrawString(str, font, 20.f, Vector2(4.0f, 48.f), 0xFFFFFFFF);

            str = "Меняйте размеры окна, чтобы увидеть, как виртуальный экран вписывается в окно";
            screenSpaceSpriteBatch_->DrawString(str, font, 20.f, Vector2(4.0f, 72.f), 0xFFFFFFFF);
        }

        // Выводим подсказку про ПКМ
        str = "Зажмите ПКМ для перемещения по сцене";
        Vector2 pos{graphics->GetWidth() - 550.f, graphics->GetHeight() - 36.f}; // TODO: Добавить MeasureString
        screenSpaceSpriteBatch_->DrawString(str, font, 20.f, pos, 0xFFFFFFFF);

        // Выводим FPS
        str = "FPS: " + String(fpsValue_);
        pos = {10.f, graphics->GetHeight() - 56.f};
        screenSpaceSpriteBatch_->DrawString(str, font, 40.f, pos, 0xFF0000FF);

        screenSpaceSpriteBatch_->Flush();
    }
};

URHO3D_DEFINE_APPLICATION_MAIN(Game)
