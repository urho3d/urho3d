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

#include <vector>
#include <limits> // for max float value

#include <SPARK_Core.h>

namespace SPK
{
	// TODO Allows to tweak this
	const size_t Octree::MAX_LEVEL_INDEX = 4; // A too high number will be highly memory comsuming
	const size_t Octree::MAX_PARTICLES_NB_PER_CELL = 32;
	const float Octree::OPTIMAL_CELL_SIZE_FACTOR = 4.0f; // optimal cell size is defined as : factor * mean radius
	const float Octree::MIN_CELL_SIZE = 0.001f;

	Octree::Octree(const Ref<Group>& group) :
		group(*group),
		cells(64),
		nbCells(0),		
		particleCells(NULL),
        nbParticles(0),
		minPos(NULL),
		maxPos(NULL)
	{}

	Octree::~Octree()
	{
		SPK_DELETE_ARRAY(particleCells);
		SPK_DELETE_ARRAY(minPos);
		SPK_DELETE_ARRAY(maxPos);
	}

	void Octree::update()
	{
		// Reallocates if necessary
		if (group.getCapacity() != nbParticles)
		{
			nbParticles = group.getCapacity();
			SPK_DELETE_ARRAY(particleCells);
			SPK_DELETE_ARRAY(minPos);
			SPK_DELETE_ARRAY(maxPos);

			particleCells = SPK_NEW_ARRAY(Array<size_t>,nbParticles);
			minPos = SPK_NEW_ARRAY(Triplet,nbParticles);
			maxPos = SPK_NEW_ARRAY(Triplet,nbParticles);
		}

		const float MAX_FLOAT = std::numeric_limits<float>::max();
		AABBMin.set(MAX_FLOAT,MAX_FLOAT,MAX_FLOAT);
		AABBMax.set(-MAX_FLOAT,-MAX_FLOAT,-MAX_FLOAT);

		// First traversal in O(n) needed to init the octree
		float meanRadius = 0.0f;
		for (ConstGroupIterator particleIt(group); !particleIt.end(); ++particleIt)
		{
			const Particle& particle = *particleIt;
			float radius = particle.getRadius();
			AABBMin.setMin(particle.position());
			AABBMax.setMax(particle.position());
			meanRadius += radius;
			particleCells[particle.getIndex()].clear();
		}

		// Tries to minimize the number of particles that belongs to several cell by setting minimum cell size function of the mean radius
		meanRadius /= group.getNbParticles();
		float minCellSize = meanRadius * OPTIMAL_CELL_SIZE_FACTOR;
		if (minCellSize < MIN_CELL_SIZE)
			minCellSize = MIN_CELL_SIZE;

		// Initial dimensions
		Vector3D dimensions = AABBMax - AABBMin;
		Vector3D offset = AABBMin;

		// Maximizes the possibilities of seperation
		Vector3D cellSizes = dimensions / Vector3D(static_cast<float>(1 << MAX_LEVEL_INDEX));
		cellSizes.setMin(Vector3D(minCellSize));
		Vector3D ratios = Vector3D(minCellSize) / cellSizes;

		// Optimizes if possible by scaling down the octree in order to use less levels
		size_t maxLevel = MAX_LEVEL_INDEX;
		while (ratios.getMin() >= 2.0f && maxLevel > 0)
		{
			ratios /= 2.0f;
			--maxLevel;
		}

		// Updates the dimensions
		offset -= dimensions * ((ratios + 1.0f) * 0.5f - 1.0f);
		dimensions *= ratios;
		AABBMin = offset;
		AABBMax = offset + dimensions;

		// Inits root
		nbCells = 0;
		initNextCell(0,0,0,0);

		// Adds particles to correct cells
		Vector3D ratio = Vector3D(static_cast<float>(1 << maxLevel)) / dimensions;
		for (ConstGroupIterator particleIt(group); !particleIt.end(); ++particleIt)
		{
			const Particle& particle = *particleIt;
			const Vector3D position = particle.position() - offset;
			const float radius = particle.getRadius();

			size_t particleIndex = particle.getIndex();

			Vector3D minPosf = (position - radius) * ratio;
			Vector3D maxPosf = (position + radius) * ratio;

			minPos[particleIndex].set(minPosf);
			maxPos[particleIndex].set(maxPosf);

			addToCell(0,particleIndex,maxLevel);
		}

		// Fills results (particle/cell relationship)
		activeCells.clear();
		for (size_t i = 0; i < nbCells; ++i)
			if (!cells[i].particles.empty())
			{
				activeCells.push(i);
				size_t nbParticlesInCells = cells[i].particles.size();
				for (size_t j = 0; j < nbParticlesInCells; ++j)
					particleCells[cells[i].particles[j]].push(i);
			}
	}

	size_t Octree::initNextCell(size_t level,size_t offsetX,size_t offsetY,size_t offsetZ)
	{
		if (nbCells == cells.size())
			cells.push(Cell(level,offsetX,offsetY,offsetZ));
		else
			cells[nbCells].init(level,offsetX,offsetY,offsetZ);
		return nbCells++;
	}

	void Octree::addToCell(size_t cellIndex,size_t particleIndex,size_t maxLevel)
	{
		Cell& cell = cells[cellIndex];
		if (!cell.hasChildren && (cell.particles.size() < MAX_PARTICLES_NB_PER_CELL || cell.level == maxLevel))
			cell.particles.push(particleIndex);
		else
		{
			// Creates children if necessary
			if (!cell.hasChildren)
			{
				for (size_t i = 0; i < 8; ++i)
				{

					size_t childIndex = initNextCell(
						cells[cellIndex].level + 1,
						(cells[cellIndex].offsetX << 1) + ((i >> 2) & 1),
						(cells[cellIndex].offsetY << 1) + ((i >> 1) & 1),
						(cells[cellIndex].offsetZ << 1) + (i & 1));
					cells[cellIndex].children[i] = childIndex;
				}

				cells[cellIndex].hasChildren = true;

				// Redistributes particles in this cell to its newly created children
				size_t nbParticlesInCell = cells[cellIndex].particles.size();
				for (size_t i = 0; i < nbParticlesInCell; ++i)
					addToChildrenCells(cellIndex,cells[cellIndex].particles[i],maxLevel);
				cells[cellIndex].particles.clear();
			}

			addToChildrenCells(cellIndex,particleIndex,maxLevel);
		}
	}

	void Octree::addToChildrenCells(size_t parentIndex,size_t particleIndex,size_t maxLevel) // TODO This code may be optimized ?
	{
		const Cell& parent = cells[parentIndex];
		size_t childLevel = parent.level + 1;
		size_t divisor = maxLevel - childLevel;

		Triplet& min = minPos[particleIndex];
		Triplet& max = maxPos[particleIndex];

		int offsetX = cells[parentIndex].offsetX << 1;
		int offsetY = cells[parentIndex].offsetY << 1;
		int offsetZ = cells[parentIndex].offsetZ << 1;

		int minIndexX = (min.value[0] >> divisor) <= offsetX ? 0 : 1;
		int minIndexY = (min.value[1] >> divisor) <= offsetY ? 0 : 1;
		int minIndexZ = (min.value[2] >> divisor) <= offsetZ ? 0 : 1;

		int maxIndexX = (max.value[0] >> divisor) <= offsetX ? 0 : 1;
		int maxIndexY = (max.value[1] >> divisor) <= offsetY ? 0 : 1;
		int maxIndexZ = (max.value[2] >> divisor) <= offsetZ ? 0 : 1;

		for (int x = minIndexX; x <= maxIndexX; ++x)
			for (int y = minIndexY; y <= maxIndexY; ++y)
				for (int z = minIndexZ; z <= maxIndexZ; ++z)
					addToCell(parent.children[(x << 2) | (y << 1) | z],particleIndex,maxLevel);
	}
}
