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

#include <cmath> // for sqrt

#include <SPARK_Core.h>
#include "Extensions/Emitters/SPK_RandomEmitter.h"

namespace SPK
{
	void RandomEmitter::generateVelocity(Particle& particle,float speed) const
	{
		float sqrNorm;
		
		do 
		{
			particle.velocity().set(SPK_RANDOM(-1.0f,1.0f),SPK_RANDOM(-1.0f,1.0f),SPK_RANDOM(-1.0f,1.0f));
			sqrNorm = particle.velocity().getSqrNorm();
		}
		while((sqrNorm > 1.0f) || (sqrNorm == 0.0f));

		particle.velocity() *= speed / std::sqrt(sqrNorm);
	}
}
