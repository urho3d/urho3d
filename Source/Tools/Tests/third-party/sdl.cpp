// Copyright (c) 2022-2023 the Dviglo project
// Copyright (c) 2008-2023 the Urho3D project
// License: MIT

// Тестируем прямой вызов из сторонней библиотеки

#include "../ForceAssert.h"

#include <SDL/SDL.h>

#include <Urho3D/Urho3D.h> // URHO3D_STATIC_DEFINE

void test_third_party_sdl()
{
    // Если собрать движок как dll, то не будет доступа к функциям SDL
    // (см. дефайн SDL_EXPORTS в модифицированном SDL).
    // В Unix доступ есть всегда для любого типа библиотеки
#if defined (_WIN32) && defined (URHO3D_STATIC_DEFINE)
    assert(SDL_abs(-1) == 1);
#endif
}
