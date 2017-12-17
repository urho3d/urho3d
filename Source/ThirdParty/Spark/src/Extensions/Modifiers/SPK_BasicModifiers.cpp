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

#include <algorithm> // for min

#include <SPARK_Core.h>
#include "Extensions/Modifiers/SPK_BasicModifiers.h"

namespace SPK
{
	void Gravity::modify(Group& group,DataSet* dataSet,float deltaTime) const
	{
		const Vector3D discreteGravity = tValue * deltaTime;
		for (GroupIterator particleIt(group); !particleIt.end(); ++particleIt)
			particleIt->velocity() += discreteGravity;
	}

	void Friction::modify(Group& group,DataSet* dataSet,float deltaTime) const
	{
		const float discreteFriction = value * deltaTime;

		if (group.isEnabled(PARAM_MASS))
		{
			for (GroupIterator particleIt(group); !particleIt.end(); ++particleIt)
				particleIt->velocity() *= 1.0f - std::min(1.0f,discreteFriction / particleIt->getParamNC(PARAM_MASS));
		}
		else
		{
			const float ratio =  1.0f - std::min(1.0f,discreteFriction);
			for (GroupIterator particleIt(group); !particleIt.end(); ++particleIt)
				particleIt->velocity() *= ratio;
		}
	}

	void Gravity::innerImport(const IO::Descriptor& descriptor)
	{
		Modifier::innerImport(descriptor);

		const IO::Attribute* attrib = NULL;
        if ((attrib = descriptor.getAttributeWithValue("value")))
			setValue(attrib->getValue<Vector3D>());
	}

	void Gravity::innerExport(IO::Descriptor& descriptor) const
	{
		Modifier::innerExport(descriptor);
		descriptor.getAttribute("value")->setValue(getValue());
	}

	void Friction::innerImport(const IO::Descriptor& descriptor)
	{
		Modifier::innerImport(descriptor);

		const IO::Attribute* attrib = NULL;
        if ((attrib = descriptor.getAttributeWithValue("value")))
			value = attrib->getValue<float>();
	}

	void Friction::innerExport(IO::Descriptor& descriptor) const
	{
		Modifier::innerExport(descriptor);
		descriptor.getAttribute("value")->setValue(value);
	}
}
