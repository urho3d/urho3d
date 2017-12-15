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

#include <SPARK_Core.h>
#include "Extensions/Modifiers/SPK_Collider.h"

namespace SPK
{
	void Collider::setElasticity(float elasticity)
	{
		if (elasticity < 0.0f)
		{
			SPK_LOG_WARNING("Collider::setElasticity(float) - The elasticity cannot be negative, 1.0f is set")
			elasticity = 1.0f;
		}

		this->elasticity = elasticity;
	}

	void Collider::modify(Group& group,DataSet* dataSet,float deltaTime) const
	{
		float groupSqrRadius = group.getPhysicalRadius() * group.getPhysicalRadius();
		SPK_ASSERT(group.getOctree() != NULL,"GLQuadRenderer::render(const Group&,const DataSet*,RenderBuffer*) - renderBuffer must not be NULL");
		const Octree& octree = *group.getOctree();

		for (GroupIterator particleIt0(group); !particleIt0.end(); ++particleIt0)
		{
			Particle& particle0 = *particleIt0;
			float radius0 = particle0.getParam(PARAM_SCALE);
			float m0 = particle0.getParam(PARAM_MASS);

			size_t index0 = particle0.getIndex();

			const Octree::Array<size_t>& neighborCells = octree.getNeighborCells(index0);
			size_t nbCells = neighborCells.size();

			for (size_t i = 0; i < nbCells; ++i) // For each neighboring cell in the octree
			{
				const Octree::Cell& cell = octree.getCell(neighborCells[i]);
				size_t nbParticleInCells = cell.particles.size();

				for (size_t j = 0; j < nbParticleInCells; ++j) // for each particles in the cell
				{
					size_t index1 = cell.particles[j];
					if (index1 >= index0)
						break; // as particle are ordered

					Particle particle1 = group.getParticle(index1);
					float radius1 = particle1.getParam(PARAM_SCALE);

					float sqrRadius = radius0 + radius1;
					sqrRadius *= sqrRadius * groupSqrRadius;

					// Gets the normal of the collision plane
					Vector3D normal = particle0.position() - particle1.position();
					float sqrDist = normal.getSqrNorm();

					if (sqrDist < sqrRadius) // particles are intersecting each other
					{
						Vector3D delta = particle0.velocity() - particle1.velocity();

						if (dotProduct(normal,delta) < 0.0f) // particles are moving towards each other
						{
							float oldSqrDist = getSqrDist(particle0.oldPosition(),particle1.oldPosition());
							if (oldSqrDist > sqrDist)
							{
								// Disables the move from this frame
								particle0.position() = particle0.oldPosition();
								particle1.position() = particle1.oldPosition();

								normal = particle0.position() - particle1.position();

								if (dotProduct(normal,delta) >= 0.0f)
									continue;
							}

							normal.normalize();

							// Gets the normal components of the velocities
							Vector3D normal0 = normal * dotProduct(normal,particle0.velocity());
							Vector3D normal1 = normal * dotProduct(normal,particle1.velocity());

							// Resolves collision
							float m1 = particle1.getParam(PARAM_MASS);

							if (oldSqrDist < sqrRadius && sqrDist < sqrRadius)
							{
								// Tweak to separate particles that intersects at both t - deltaTime and t
								// In that case the collision is no more considered as punctual
								if (dotProduct(normal,normal0) < 0.0f)
								{
									particle0.velocity() -= normal0;
									particle1.velocity() += normal0;
								}

								if (dotProduct(normal,normal1) > 0.0f)
								{
									particle1.velocity() -= normal1;
									particle0.velocity() += normal1;
								}
							}
							else
							{
								// Else classic collision equations are applied
								// Tangent components of the velocities are left untouched
								float elasticityM0 = elasticity * m0;
								float elasticityM1 = elasticity * m1;
								float invM01 = 1 / (m0 + m1);

								particle0.velocity() -= (1.0f + (elasticityM1 - m0) * invM01) * normal0;
								particle1.velocity() -= (1.0f + (elasticityM0 - m1) * invM01) * normal1;

								normal0 *= (elasticityM0 + m0) * invM01;
								normal1 *= (elasticityM1 + m0) * invM01;

								particle0.velocity() += normal1;
								particle1.velocity() += normal0;
							}
						}
					}
				}
			}
		}
	}

	void Collider::innerImport(const IO::Descriptor& descriptor)
	{
		Modifier::innerImport(descriptor);

		const IO::Attribute* attrib = NULL;
        if ((attrib = descriptor.getAttributeWithValue("elasticity")))
			setElasticity(attrib->getValue<float>());
	}

	void Collider::innerExport(IO::Descriptor& descriptor) const
	{
		Modifier::innerExport(descriptor);
		descriptor.getAttribute("elasticity")->setValue(getElasticity());
	}
}
