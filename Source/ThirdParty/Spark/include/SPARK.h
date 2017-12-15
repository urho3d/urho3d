//
// SPARK particle engine
//
// Copyright (C) 2008-2011 - Julien Fryer - julienfryer@gmail.com
// Copyright (C) 2017 - Frederic Martin - fredakilla@gmail.com
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//

#ifndef H_SPARK
#define H_SPARK

// Core
#include "SPARK_Core.h"

// Interpolators
#include "Extensions/Interpolators/SPK_DefaultInitializer.h"
#include "Extensions/Interpolators/SPK_RandomInitializer.h"
#include "Extensions/Interpolators/SPK_SimpleInterpolator.h"
#include "Extensions/Interpolators/SPK_RandomInterpolator.h"
#include "Extensions/Interpolators/SPK_GraphInterpolator.h"

// Zones
#include "Extensions/Zones/SPK_Point.h"
#include "Extensions/Zones/SPK_Sphere.h"
#include "Extensions/Zones/SPK_Plane.h"
#include "Extensions/Zones/SPK_Ring.h"
#include "Extensions/Zones/SPK_Box.h"
#include "Extensions/Zones/SPK_Cylinder.h"

// Emitters
#include "Extensions/Emitters/SPK_StaticEmitter.h"
#include "Extensions/Emitters/SPK_RandomEmitter.h"
#include "Extensions/Emitters/SPK_StraightEmitter.h"
#include "Extensions/Emitters/SPK_SphericEmitter.h"
#include "Extensions/Emitters/SPK_NormalEmitter.h"

// Modifiers
#include "Extensions/Modifiers/SPK_BasicModifiers.h"
#include "Extensions/Modifiers/SPK_Obstacle.h"
#include "Extensions/Modifiers/SPK_Rotator.h"
#include "Extensions/Modifiers/SPK_Collider.h"
#include "Extensions/Modifiers/SPK_Destroyer.h"
#include "Extensions/Modifiers/SPK_Vortex.h"
#include "Extensions/Modifiers/SPK_EmitterAttacher.h"
#include "Extensions/Modifiers/SPK_PointMass.h"
#include "Extensions/Modifiers/SPK_RandomForce.h"
#include "Extensions/Modifiers/SPK_LinearForce.h"

// Actions
#include "Extensions/Actions/SPK_ActionSet.h"
#include "Extensions/Actions/SPK_SpawnParticlesAction.h"

// Renderers
#include "Extensions/Renderers/SPK_PointRenderBehavior.h"
#include "Extensions/Renderers/SPK_LineRenderBehavior.h"
#include "Extensions/Renderers/SPK_QuadRenderBehavior.h"
#include "Extensions/Renderers/SPK_Oriented3DRenderBehavior.h"

// IOConverters
#include "Extensions/IOConverters/SPK_IO_XMLSaver.h"
#include "Extensions/IOConverters/SPK_IO_XMLLoader.h"
#include "Extensions/IOConverters/SPK_IO_SPKSaver.h"
#include "Extensions/IOConverters/SPK_IO_SPKLoader.h"

#endif
