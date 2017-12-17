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

#ifndef H_SPK_SYSTEM
#define H_SPK_SYSTEM

#include <vector>

// This define helps implement a wrapper for SPK::System by redirecting the methods
#define SPK_IMPLEMENT_SYSTEM_WRAPPER \
\
private : \
SPK::Ref<SPK::System> SPKSystem; \
public : \
const SPK::Ref<SPK::System>& getSPKSystem() { return SPKSystem; } \
SPK::Ref<SPK::Group> createSPKGroup(size_t capacity) { return SPKSystem->createGroup(capacity); } \
SPK::Ref<SPK::Group> createSPKGroup(SPK::Ref<SPK::Group>& group) { return SPKSystem->createGroup(group); } \
void addSPKGroup(SPK::Ref<SPK::Group>& group) { SPKSystem->addGroup(group); } \
void removeSPKGroup(SPK::Ref<SPK::Group> group) { SPKSystem->removeGroup(group); } \
SPK::Ref<SPK::Group> getSPKGroup(size_t index) const { return SPKSystem->getGroup(index); } \
size_t getNbSPKGroups() const { return SPKSystem->getNbGroups(); } \
size_t getNbParticles() const { return SPKSystem->getNbParticles(); } \
void initializeSPK() { SPKSystem->initialize(); } \
bool isInitializedSPK() const { return SPKSystem->isInitialized(); }

namespace SPK
{
	/**
	* @enum StepMode
	* @brief Enumeration defining how to handle the step time of particle systems
	*/
	enum StepMode
	{
		STEP_MODE_REAL,			/**< The step time is the deltatime passed by the user */
		STEP_MODE_CONSTANT,		/**< The step time is a constant time therefore 0 to many updates may occur in a call */
		STEP_MODE_ADAPTIVE,		/**< The step time is a range between 2 values therefore 0 to many updates may occur in a call */
	};

	/**
	* @brief A class defining a complete system of particles
	*/
	class SPK_PREFIX System : public Transformable
	{
	SPK_IMPLEMENT_OBJECT(System)

	SPK_START_DESCRIPTION
	SPK_PARENT_ATTRIBUTES(Transformable)
	SPK_ATTRIBUTE("groups",ATTRIBUTE_TYPE_REFS)
	SPK_END_DESCRIPTION

	public :

		/////////////////////////////
		// Constructor/Desctructor //
		/////////////////////////////

		static Ref<System> create(bool initialize = true);
		~System();

		///////////////////////
		// Groups management //
		///////////////////////

		/**
		* @brief Adds a group to the system
		* @param group : a pointer on the group to add to the system
		*/
		Ref<Group> createGroup(size_t capacity);

		/**
		* @brief Adds a group to the system which is a copy of an existing group
		*
		*/
		Ref<Group> createGroup(const Ref<Group>& group);

		void addGroup(const Ref<Group>& group);

		/**
		* @brief Removes a group from the system
		*
		* If the group cannot be found, nothing happens.
		*
		* @param group : a pointer on the group to remove from the system
		*/
		void removeGroup(const Ref<Group>& group);

        /**
        * @brief Removes all groups in this system
        */
        void removeAllGroups();

		/**
		* @brief Gets the group at index
		* @param index : the index of the group to get
		* @return the group at index
		*/
		const Ref<Group>& getGroup(size_t index) const;

		/**
		* @brief Gets the number of groups in the system
		* @return the number of groups in the system
		*/
		size_t getNbGroups() const;

		/**
		* @brief Gets the number of particles in the system
		* @return the number of particles in the system
		*/
		size_t getNbParticles() const;

		/////////////////////////////
		// Operations on particles //
		/////////////////////////////

		/**
		* @brief Updates the particles in the system of the current time step
		*
		* Note that this method updates all groups in the system from first to last.<br>
		* A call to updateTransform(const Ref<Transformable>&) of the system is also performed prior to the groups update.
		*
		* @param deltaTime : the time step
		* @return true if the System is still active (has active groups)
		*/
		virtual bool updateParticles(float deltaTime);

		/**
		* @brief Renders particles in the System
		*
		* Note that this method renders all groups in the System from first to last.
		*/
		virtual void renderParticles() const;

		//////////////////
		// Bounding Box //
		//////////////////

		/**
		* @brief Enables or disables the computation of the axis aligned bounding box for this System
		* @param AABB : true to enable the computing of the AABB of this System, false to disable it
		*/
		void enableAABBComputation(bool AABB);

		/**
		* @brief Tells whether the computation of the axis aligned bouding box is enabled
		* @return true if the computation of the AABB is enabled, false if it is disabled
		*/
		bool isAABBComputationEnabled() const;

		/**
		* @brief Gets a Vector3D holding the minimum coordinates of the AABB of this System.
		*
		* Note that this method is only useful when the AABB computation is enabled (see enableAABBComputation(bool)).
		*
		* @return a Vector3D holding the minimum coordinates of the AABB of this System
		*/
		const Vector3D& getAABBMin() const;

		/**
		* @brief Gets a Vector3D holding the maximum coordinates of the AABB of this System.
		*
		* Note that this method is only useful when the AABB computation is enabled (see enableAABBComputation(bool)).
		*
		* @return a Vector3D holding the maximum coordinates of the AABB of this System
		*/
		const Vector3D& getAABBMax() const;

		/////////////////////
		// Camera position //
		/////////////////////

		/**
		* @brief Sets the camera position
		*
		* Note that the camera position is only useful if the distance computation of a group is enabled (when the group must be sorted for instance).<br>
		* In that case this vector will be used as the camera position to derive the distance between the particle and the camera position.<br>
		* The camera position has to be updated before an update of the sorted group and must be in the local space of the system.
		*
		* @param cameraPosition the camera position
		*/
		void setCameraPosition(const Vector3D& cameraPosition);

		/**
		* @brief Gets the camera position
		* @return the camera position
		*/
		const Vector3D& getCameraPosition();

		///////////////
		// Step Mode //
		///////////////

		/**
		* @brief Enables or not the clamping on the deltaTime when updating systems
		*
		* This allows to limit too big delta times which may spoil your particle systems.<br>
		* Basically if the deltaTime is higher than the clamp value, the clamp value is used as the deltaTime.<br>
		* <br>
		* It allows in real step mode to avoid having too big delta times and in the other 2 modes to avoid having too
		* many updates that may slow down the application.<br>
		* <br>
		* Note that setting the clamp value too low may slow down your systems
		*
		* @param useClampStep : true to use a clamp value on the step, false not to
		* @param clamp : the clamp value
		*/
		static void setClampStep(bool useClampStep,float clamp = 1.0f);

		/**
		* @brief Uses a constant step to update the systems
		*
		* This tells the system to be updated with a constant time.<br>
		* Depending on the deltaTime passed for the update, 0 to many updates can occur.<br>
		* For example if the delta time is 1.0 and the constant step is 0.1 then 10 updates of time 0.1 will occur.<br>
		* <br>
		* This mode is useful when the update must be constant (accurate collisions...) but be aware it can be very computationnaly intensive.
		* 
		* @param constantStep : the value of the step
		*/
		static void useConstantStep(float constantStep);

		/**
		* @brief Uses an adaptive step to update the systems
		*
		* This tells the system to be updated with a time between min and max.<br>
		* If the deltaTime passed is higher than maxStep or lower than minStep then this mode operates like the constant step mode with
		* either constant time being maxStep or minStep (respectivally).<br>
		* If the deltaTime lies between minStep and maxStep then this mode performs like the real step mode.<br>
		* <br>
		* This mode is a good alternative between the other two.<br>
		* Combined with the clamp step, it allows to correctly handle the step time without being to much frame rate dependant.
		*
		* @param minStep : the minimal time step
		* @param maxStep : the maximal time step
		*/
		static void useAdaptiveStep(float minStep,float maxStep);

		/**
		* @brief Uses the real step to update the systems
		*
		* This is the basic mode (and the mode per default) to update the systems.<br>
		* One call to update means one update of time deltaTime.<br>
		* <br>
		* This mode is the simpler and the one that allows best performance on low end systems.<br>
		* However the update may be inaccurate (due to too big deltaTime) and it performs badly with frame rate variation.
		*/
		static void useRealStep();

		/**
		* @brief Gets the current step mode
		* @return the current step mode
		*/
		static StepMode getStepMode();

		//////////
		// Misc //
		//////////

		/**
		* @brief Returns whether the system is active or not
		* 
		* A system is active if at least one of its inner groups is active
		* A group is active if it has at least one particle or one active emitter
		*/
		bool isActive() const;

		void initialize();
		bool isInitialized() const;

		virtual Ref<SPKObject> findByName(const std::string& name) override;

	protected :

		std::vector<Ref<Group> > groups; // vector containing all the groups of the system

		System(bool initialize = true);
		System(const System& system);

		virtual void propagateUpdateTransform() override;

		virtual void innerImport(const IO::Descriptor& descriptor) override;
		virtual void innerExport(IO::Descriptor& descriptor) const override;

	private :

		Vector3D cameraPosition;

		// Step mode
		static StepMode stepMode;
		static float constantStep;
		static float minStep;
		static float maxStep;

		static bool clampStepEnabled;
		static float clampStep;

		float deltaStep;

		bool initialized;
		bool active;

		// AABB
		bool AABBComputationEnabled;
		Vector3D AABBMin;
		Vector3D AABBMax;

		bool innerUpdate(float deltaTime);

		static void setGroupSystem(const Ref<Group>& group,System* system,bool remove = true);
	};

	inline Ref<System> System::create(bool initialize) 
	{ 
		return SPK_NEW(System,initialize); 
	}

	inline const Ref<Group>& System::getGroup(size_t index) const
	{
		SPK_ASSERT(index < getNbGroups(),"System::getGroup(size_t) - Index of group is out of bounds : " << index);
		return groups[index];
	}

    inline void System::removeAllGroups()
    {
        groups.clear();
    }

	inline size_t System::getNbGroups() const
	{
		return groups.size();
	}

	inline void System::enableAABBComputation(bool AABB)
	{
		AABBComputationEnabled = AABB;
	}

	inline bool System::isAABBComputationEnabled() const
	{
		return AABBComputationEnabled;
	}

	inline const Vector3D& System::getAABBMin() const
	{
		return AABBMin;
	}

	inline const Vector3D& System::getAABBMax() const
	{
		return AABBMax;
	}

	inline void System::setCameraPosition(const Vector3D& cameraPosition)
	{
		this->cameraPosition = cameraPosition;
	}

	inline const Vector3D& System::getCameraPosition()
	{
		return cameraPosition;
	}

	inline void System::setClampStep(bool enableClampStep,float clamp)
	{
		clampStepEnabled = enableClampStep;
		clampStep = clamp;
	}

	inline void System::useConstantStep(float constantStep)
	{
		stepMode = STEP_MODE_CONSTANT;
		System::constantStep = constantStep;
	}

	inline void System::useAdaptiveStep(float minStep,float maxStep)
	{
		stepMode = STEP_MODE_ADAPTIVE;
		System::minStep = minStep;
		System::maxStep = maxStep;
	}

	inline void System::useRealStep()
	{
		stepMode = STEP_MODE_REAL;
	}

	inline StepMode System::getStepMode()
	{
		return stepMode;
	}

	inline bool System::isInitialized() const
	{
		return initialized;
	}

	inline bool System::isActive() const
	{
		return active;
	}
}

#endif
