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

#ifndef H_SPK_TRANSFORMABLE
#define H_SPK_TRANSFORMABLE

namespace SPK
{
	class SPK_PREFIX Transformable : public SPKObject
	{
	friend class Transform;

	SPK_START_DESCRIPTION
	SPK_PARENT_ATTRIBUTES(SPKObject)
	SPK_ATTRIBUTE("transform",ATTRIBUTE_TYPE_FLOATS)
	SPK_END_DESCRIPTION

	public :

		virtual ~Transformable() {}

		/**
		* @brief Gets the transform of this transformable
		* @return the transform of this transformable
		*/
		Transform& getTransform();

		/**
		* @brief Gets the transform of this transformable
		* This is the const version of getTransform()
		* @return the transform of this transformable
		*/
		const Transform& getTransform() const;

		/**
		* @brief Updates the transform of this transformable
		* @param parent : the parent transformable of this transformable, NULL if it has no parent
		*/
		void updateTransform(const Ref<Transformable>& parent = SPK_NULL_REF);

        ///////////////////////
        // Transform helpers //
        ///////////////////////
        /// TODO: See Transform
        void setTransformPosition(const Vector3D& pos);
        const Vector3D& getTransformPosition() const;
        void setTransformLookLH(const Vector3D& pos);
        const Vector3D& getTransformLookLH() const;
        void setTransformUp(const Vector3D& pos);
        const Vector3D& getTransformUp() const;

	protected :

		// abstract class
		Transformable(SharePolicy SHARE_POLICY = SHARE_POLICY_CUSTOM) : SPKObject(SHARE_POLICY) {}
		Transformable(const Transformable& obj) : 
			SPKObject(obj),
			transform(obj.transform) {}

		/**
		* @brief Updates all the parameters in the world coordinates
		*
		* This method can be overriden in derived classes of Transformable (By default it does nothing).<br>
		* It is this method task to compute all parameters of the class that are dependent of the world transform.
		*/
		virtual void innerUpdateTransform() {}

		/**
		* @brief Propagates the update of the transform to transformable's children of this transformable
		*
		* This method can be overriden in derived classes of Transformable (By default it does nothing).<br>
		* It is this method task to call the updateTransform method of the transformable's children of this transformable.
		*/
		virtual void propagateUpdateTransform() {}

		/**
		* @brief Transforms a position in this object's space
		* @param tPos : the transformed position
		* @param pos : the position to transform
		*/
		void transformPos(Vector3D& tPos,const Vector3D& pos);

		/**
		* @brief Transforms a direction in this object's space
		* @param tPos : the transformed direction
		* @param pos : the direction to transform
		*/
		void transformDir(Vector3D& tDir,const Vector3D& dir);

        virtual void innerImport(const IO::Descriptor& descriptor) override;
        virtual void innerExport(IO::Descriptor& descriptor) const override;

	private :

		Transform transform;
	};

	inline Transform& Transformable::getTransform()
	{
		return transform;
	}

	inline const Transform& Transformable::getTransform() const
	{
		return transform;
	}

	inline void Transformable::transformPos(Vector3D& tPos,const Vector3D& pos)
	{
		transform.transformPos(tPos,pos);
	}

	inline void Transformable::transformDir(Vector3D& tDir,const Vector3D& dir)
	{
		transform.transformDir(tDir,dir);
	}

    inline void Transformable::setTransformPosition(const Vector3D& pos)
    {
        transform.setPosition(pos);
    }

    inline const Vector3D& Transformable::getTransformPosition() const
    {
        /// TODO: improve Transform in order to remove this hack
        static Vector3D v = transform.getLocalPos();
        return v;
    }

    inline void Transformable::setTransformLookLH(const Vector3D& look)
    {
        transform.setOrientationLH(look, transform.getLocalUp());
    }

    inline const Vector3D& Transformable::getTransformLookLH() const
    {
        /// TODO: improve Transform in order to remove this hack
        static Vector3D v = transform.getLocalLookLH();
        return v;
    }

    inline void Transformable::setTransformUp(const Vector3D& up)
    {
        transform.setOrientationLH(transform.getLocalLookLH(), up);
    }

    inline const Vector3D& Transformable::getTransformUp() const
    {
        /// TODO: improve Transform in order to remove this hack
        static Vector3D v = transform.getLocalUp();
        return v;
    }
}

#endif


