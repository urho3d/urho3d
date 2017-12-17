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
#include <cstring> // for memcpy

namespace SPK
{
	const float Transform::IDENTITY[] =
	{
		1.0f,	0.0f,	0.0f,	0.0f,
		0.0f,	1.0f,	0.0f,	0.0f,
		0.0f,	0.0f,	1.0f,	0.0f,
		0.0f,	0.0f,	0.0f,	1.0f,
	};

	Transform::Transform() :
		currentUpdate(0),
		lastUpdate(0),
		lastParentUpdate(0),		
        localIdentity(true),
        parent(NULL)
	{
		std::memcpy(local,IDENTITY,sizeof(float) * TRANSFORM_LENGTH);
		std::memcpy(world,IDENTITY,sizeof(float) * TRANSFORM_LENGTH);
	}

	Transform::Transform(const Transform& transform) :
		currentUpdate(0),
		lastUpdate(0),
		lastParentUpdate(0),		
        localIdentity(transform.localIdentity),
        parent(NULL)
	{
		std::memcpy(local,transform.local,sizeof(float) * TRANSFORM_LENGTH);
		std::memcpy(world,transform.local,sizeof(float) * TRANSFORM_LENGTH); // Sets to local as it is created with no parent
	}

	void Transform::setNC(const float* transform)
	{
		for (size_t i = 0; i < TRANSFORM_LENGTH; ++i)
			local[i] = transform[(i >> 2) + ((i & 3) << 2)];	// conversion

		localIdentity = false;
		notifyForUpdate();
	}

	void Transform::setPosition(const Vector3D& pos)
	{
		local[12] = pos.x;
		local[13] = pos.y;
		local[14] = pos.z;

		localIdentity = false;
		notifyForUpdate();
	}

    void Transform::set(const float* transform)
    {
        std::memcpy(local,transform,sizeof(float) * TRANSFORM_LENGTH);
        localIdentity = false;
        notifyForUpdate();
    }

	void Transform::setOrientationRH(Vector3D look,Vector3D up)
	{
		look.normalize();
		up.normalize();

        Vector3D side = crossProduct(up,look);
		side.normalize();

        up = crossProduct(look,side);

		local[0] = side.x;
		local[1] = side.y;
		local[2] = side.z;
		local[4] = up.x;
		local[5] = up.y;
		local[6] = up.z;
		local[8] = -look.x;
		local[9] = -look.y;
		local[10] = -look.z;

		localIdentity = false;
		notifyForUpdate();
	}

	void Transform::setOrientationLH(Vector3D look,Vector3D up)
	{
		look.normalize();

		Vector3D side = crossProduct(look,up);
		side.normalize();

		up = crossProduct(side,look);

		local[0] = side.x;
		local[1] = side.y;
		local[2] = side.z;
		local[4] = up.x;
		local[5] = up.y;
		local[6] = up.z;
		local[8] = look.x;
		local[9] = look.y;
		local[10] = look.z;

		localIdentity = false;
		notifyForUpdate();
	}

	void Transform::setOrientation(Vector3D axis,float angle)
	{
		axis.normalize();
		float c = std::cos(angle);
		float s = std::sin(angle);
		float a = 1 - c;
		Vector3D axis2(axis.x * axis.x,axis.y * axis.y,axis.z * axis.z);

		local[0] = axis2.x + (1.0f - axis2.x) * c;
		local[1] = axis.x * axis.y * a + axis.z * s;
		local[2] = axis.x * axis.z * a - axis.y * s;
		local[4] = axis.x * axis.y * a - axis.z * s;
		local[5] = axis2.y + (1.0f - axis2.y) * c;
		local[6] = axis.y * axis.z * a + axis.x * s;
		local[8] = axis.x * axis.z * a + axis.y * s;
		local[9] = axis.y * axis.z * a - axis.x * s;
		local[10] = axis2.z + (1.0f - axis2.z) * c;

		localIdentity = false;
		notifyForUpdate();
	}

	void Transform::setOrientationX(float angle)
	{
		float cosA = std::cos(angle);
		float sinA = std::sin(angle);

		local[0] = 1.0f;
		local[1] = 0.0f;
		local[2] = 0.0f;
		local[4] = 0.0f;
		local[5] = cosA;
		local[6] = sinA;
		local[8] = 0.0f;
		local[9] = -sinA;
		local[10] = cosA;

		localIdentity = false;
		notifyForUpdate();
	}

	void Transform::setOrientationY(float angle)
	{
		float cosA = std::cos(angle);
		float sinA = std::sin(angle);

		local[0] = cosA;
		local[1] = 0.0f;
		local[2] = -sinA;
		local[4] = 0.0f;
		local[5] = 1.0f;
		local[6] = 0.0f;
		local[8] = sinA;
		local[9] = 0.0f;
		local[10] = cosA;

		localIdentity = false;
		notifyForUpdate();
	}

	void Transform::setOrientationZ(float angle)
	{
		float cosA = std::cos(angle);
		float sinA = std::sin(angle);

		local[0] = cosA;
		local[1] = sinA;
		local[2] = 0.0f;
		local[4] = -sinA;
		local[5] = cosA;
		local[6] = 0.0f;
		local[8] = 0.0f;
		local[9] = 0.0f;
		local[10] = 1.0f;

		localIdentity = false;
		notifyForUpdate();
	}

	void Transform::update(const Ref<Transformable>& parent,Transformable& owner)
	{
		if (isUpdateNotified() ||												// the local transform or instance param have been updated
			parent != this->parent ||											// the parent has changed
			(parent && lastParentUpdate != parent->transform.currentUpdate))	// the parent transform has been modified
		{
			if (!parent)
				std::memcpy(world,local,sizeof(float) * TRANSFORM_LENGTH);
			else if (isLocalIdentity())
			{
				std::memcpy(world,parent->transform.world,sizeof(float) * TRANSFORM_LENGTH);
				lastParentUpdate = parent->transform.lastUpdate;
			}
			else
			{
				multiply(world,parent->transform.world,local);
				lastParentUpdate = parent->transform.lastUpdate;
			}

			this->parent = parent.get();
			lastUpdate = ++currentUpdate;

			owner.innerUpdateTransform();
		}

		owner.propagateUpdateTransform();
	}

	void Transform::transformPos(Vector3D& tPos,const Vector3D& pos)
	{
		multiply(tPos,pos,world);
	}

	void Transform::transformDir(Vector3D& tDir,const Vector3D& dir)
	{
		rotate(tDir,dir,world); // To transform a direction, the translation is ignored
	}
}
