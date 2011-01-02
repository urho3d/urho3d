//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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

#ifndef GAMEEVENTS_H
#define GAMEEVENTS_H

#include "Event.h"

// Synchronized properties for multiplayer
DEFINE_PROPERTY(PROP_SCORE, Score);             // int
DEFINE_PROPERTY(PROP_HEALTH, Health);           // int
DEFINE_PROPERTY(PROP_MAXHEALTH, MaxHealth);     // int
DEFINE_PROPERTY(PROP_HISCORES, Hiscores);       // Buffer (VLE count followed by string+int pairs for each hiscore)

// Create event
DEFINE_EVENT(EVENT_CREATE, Create)
{
    EVENT_PARAM(P_OBJECT, Object);              // GameObject pointer
}

// Remove event
DEFINE_EVENT(EVENT_REMOVE, Remove)
{
    EVENT_PARAM(P_OBJECT, Object);              // GameObject pointer
}

// Damage event
DEFINE_EVENT(EVENT_DAMAGE, Damage)
{
    EVENT_PARAM(P_OBJECT, Object);              // GameObject pointer
}

// Heal event
DEFINE_EVENT(EVENT_HEAL, Heal)
{
    EVENT_PARAM(P_OBJECT, Object);              // GameObject pointer
}

// Die event
DEFINE_EVENT(EVENT_DIE, Die)
{
    EVENT_PARAM(P_OBJECT, Object);              // GameObject pointer
}

// Remote player entity spawned event (sent to the player who controls the entity)
DEFINE_EVENT(EVENT_PLAYERSPAWNED, PlayerSpawned)
{
    EVENT_PARAM(P_ENTITYID, EntityID);          // int
}

#endif // GAMEEVENTS_H
