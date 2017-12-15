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

#ifndef H_SPK_GROUP
#define H_SPK_GROUP

#include <cstring> // for memcpy
#include <vector>
#include <list>
#include <deque>

namespace SPK
{
	class Particle;
	class System;
	class Octree;

	/**
	* @brief Group of particles
	*
	* The group is the core class of SPARK.<br>
	* It is responsible for holding particle data, emitting and updating particles.<br>
	* <br>
	* A group has some objects attached to it that will define the general behaviour of particles.
	* The objects are :
	* <ul>
	* <li>0..n Emitter : How many particles to emit in which directions and with which frequency ?</li>
	* <li>0..n Interpolator : How particles parameters (size,color,mass,angle...) will evolve during their lifetime ?</li>
 	* <li>0..n Modifier : How will behave particles over time and what will interact with them ?</li>
	* <li>0..1 Renderer : How particles will be represented graphically ?</li>
	* <li>0..2 Action : What will happen at precise moments in the life of a particle (birth,death...) ?</li>
	* </ul>
	* Groups are contained within a System which commands their update and rendering.
	*/
	class SPK_PREFIX Group : public Transformable
	{
	friend class Particle;
	friend class System;
	friend class DataSet;

	SPK_IMPLEMENT_OBJECT(Group)

	SPK_START_DESCRIPTION
	SPK_PARENT_ATTRIBUTES(Transformable)
	SPK_ATTRIBUTE("capacity",ATTRIBUTE_TYPE_UINT32)
	SPK_ATTRIBUTE("life time",ATTRIBUTE_TYPE_FLOATS)
	SPK_ATTRIBUTE("immortal",ATTRIBUTE_TYPE_BOOL)
	SPK_ATTRIBUTE("still",ATTRIBUTE_TYPE_BOOL)
	SPK_ATTRIBUTE("distance computation enabled",ATTRIBUTE_TYPE_BOOL)
	SPK_ATTRIBUTE("sorting enabled",ATTRIBUTE_TYPE_BOOL)
	SPK_ATTRIBUTE("radius",ATTRIBUTE_TYPE_FLOATS)
	SPK_ATTRIBUTE("color interpolator",ATTRIBUTE_TYPE_REF)
	SPK_ATTRIBUTE("scale interpolator",ATTRIBUTE_TYPE_REF)
	SPK_ATTRIBUTE("mass interpolator",ATTRIBUTE_TYPE_REF)
	SPK_ATTRIBUTE("angle interpolator",ATTRIBUTE_TYPE_REF)
	SPK_ATTRIBUTE("texture index interpolator",ATTRIBUTE_TYPE_REF)
	SPK_ATTRIBUTE("rotation speed interpolator",ATTRIBUTE_TYPE_REF)
	SPK_ATTRIBUTE("emitters",ATTRIBUTE_TYPE_REFS)
	SPK_ATTRIBUTE("modifiers",ATTRIBUTE_TYPE_REFS)
	SPK_ATTRIBUTE("birth action",ATTRIBUTE_TYPE_REF)
	SPK_ATTRIBUTE("death action",ATTRIBUTE_TYPE_REF)
	SPK_ATTRIBUTE("renderer",ATTRIBUTE_TYPE_REF)
	SPK_END_DESCRIPTION

	public :

		static Ref<Group> create(size_t capacity = 100);
		~Group();

		bool isInitialized() const;

		void setLifeTime(float minLife,float maxLife);
		void setImmortal(bool immortal);
		void setStill(bool still);

		void setColorInterpolator(const Ref<ColorInterpolator>& interpolator);
		const Ref<ColorInterpolator>& getColorInterpolator() const;

		void setParamInterpolator(Param param,const Ref<FloatInterpolator>& interpolator);
		const Ref<FloatInterpolator>& getParamInterpolator(Param param) const;

        void setScaleInterpolator(const Ref<FloatInterpolator>& interpolator);
        void setMassInterpolator(const Ref<FloatInterpolator>& interpolator);
        void setAngleInterpolator(const Ref<FloatInterpolator>& interpolator);
        void setTextureIndexInterpolator(const Ref<FloatInterpolator>& interpolator);
        void setRotationSpeedInterpolator(const Ref<FloatInterpolator>& interpolator);
        const Ref<FloatInterpolator>& getScaleInterpolator() const;
        const Ref<FloatInterpolator>& getMassInterpolator() const;
        const Ref<FloatInterpolator>& getAngleInterpolator() const;
        const Ref<FloatInterpolator>& getTextureIndexInterpolator() const;
        const Ref<FloatInterpolator>& getRotationSpeedInterpolator() const;

		float getMinLifeTime() const;
		float getMaxLifeTime() const;
		bool isImmortal() const;
		bool isStill() const;

		bool isEnabled(Param param) const;

		size_t getNbParticles() const;
		size_t getCapacity() const;

		Particle getParticle(size_t index);
		const Particle getParticle(size_t index) const;

		void reallocate(size_t capacity);
		void empty();

		void addEmitter(const Ref<Emitter>& emitter);
		void removeEmitter(const Ref<Emitter>& emitter);
        void removeAllEmitters();
		const Ref<Emitter>& getEmitter(size_t index) const;
		size_t getNbEmitters() const;

		void addModifier(const Ref<Modifier>& modifier);
		void removeModifier(const Ref<Modifier>& modifier);
        void removeAllModifiers();
		const Ref<Modifier>& getModifier(size_t index) const;
		size_t getNbModifiers() const;

		void setRenderer(const Ref<Renderer>& renderer);
		const Ref<Renderer>& getRenderer() const;

		void enableDistanceComputation(bool distanceComputation);
		bool isDistanceComputationEnabled() const;

		void enableSorting(bool sorting);
		bool isSortingEnabled() const;

		const void* getColorAddress() const;
		const void* getPositionAddress() const;
		const void* getVelocityAddress() const;
		const void* getParamAddress(Param param) const;

		void setRadius(float radius);
		void setGraphicalRadius(float radius);
		void setPhysicalRadius(float radius);
		float getGraphicalRadius() const;
		float getPhysicalRadius() const;

		/**
		* @brief Gets a Vector3D holding the minimum coordinates of the AABB of the Group.
		*
		* Note that this method is only useful when the AABB computation of the system holding the Group is enabled.
		*
		* @return a Vector3D holding the minimum coordinates of the AABB of the Group
		*/
		const Vector3D& getAABBMin() const;

		/**
		* @brief Gets a Vector3D holding the maximum coordinates of the AABB of the Group.
		*
		* Note that this method is only useful when the AABB computation of the system holding the Group is enabled.
		*
		* @return a Vector3D holding the maximum coordinates of the AABB of the Group
		*/
		const Vector3D& getAABBMax() const;

		///////////////////
		// Add Particles //
		///////////////////

		/**
		* @brief Adds some Particles to this Group
		*
		* This method and all the methods of type addParticles will add a given number of Particles at the given position with the given velocity.<br>
		* <br>
		* In case a Zone is passed, Zone::generatePosition(Particle,bool) is used to generate the position.<br>
		* In case an Emitter is passed, Emitter::generateVelocity(Particle) with a mass of 1 is used to generate the velocity.
		* In case a delta time is passed instead of a fixed number, the number will be computed thanks to the flow of the Emitter passed.<br>
		* <br>
		* Particles will be added to the Group at the next call to update(unsigned int) or flushAddedParticles().<br>
		* This is why any Emitter and Zone used to generate particles must be valid at the next call of either update(unsigned int) or flushAddedParticles().<br>
		* <br>
		* On some methods addParticles, the full variable is present. This variable defines where to generate positions in a Zone :
		* <ul>
		* <li>true to generate position somewhere within the whole Zone.</li>
		* <li>false to generate position somewhere on the Zone border.</li>
		* </ul>
		*
		* @param nb : the number of Particles to add
		* @param position : the position where the Particles will be added
		* @param velocity : the velocity of the Particles
		*/
		void addParticles(unsigned int nb,const Vector3D& position,const Vector3D& velocity);

		/**
		* @brief Adds some Particles to this Group
		*
		* See addParticles(unsigned int,const Vector3D&,const Vector3D&) for a complete description.
		*
		* @param nb : the number of Particles to add
		* @param zone : the Zone that will be used to generate the position
		* @param emitter : the Emitter that will be used to generate the velocity
		* @param full : true to generate a position within the whole Zonz, false only at its borders
		*/
		void addParticles(unsigned int nb,const Ref<Zone>& zone,const Ref<Emitter>& emitter,bool full = true);

		/**
		* @brief Adds some Particles to this Group
		*
		* See addParticles(unsigned int,const Vector3D&,const Vector3D&) for a complete description.
		*
		* @param nb : the number of Particles to add
		* @param zone : the Zone that will be used to generate the position
		* @param velocity : the velocity of the Particles
		* @param full : true to generate a position within the whole Zonz, false only at its borders
		*/
		void addParticles(unsigned int nb,const Ref<Zone>& zone,const Vector3D& velocity,bool full = true);

		/**
		* @brief Adds some Particles to this Group
		*
		* See addParticles(unsigned int,const Vector3D&,const Vector3D&) for a complete description.
		*
		* @param nb : the number of Particles to add
		* @param position : the position where the Particles will be added
		* @param emitter : the Emitter that will be used to generate the velocity
		*/
		void addParticles(unsigned int nb,const Vector3D& position,const Ref<Emitter>& emitter);

		/**
		* @brief Adds some Particles to this Group
		*
		* See addParticles(unsigned int,const Vector3D&,const Vector3D&) for a complete description.
		*
		* @param nb : the number of Particles to add
		* @param emitter : the Emitter that will be used to generate the velocity and whose Zone will be used to generate the position
		*/
		void addParticles(unsigned int nb,const Ref<Emitter>& emitter);

		/**
		* @brief Adds some Particles to this Group
		*
		* See addParticles(unsigned int,const Vector3D&,const Vector3D&) for a complete description.
		*
		* @param zone : the Zone that will be used to generate the position
		* @param emitter : the Emitter that will be used to generate the velocity
		* @param deltaTime : the step time that will be used to determine how many particles to generate
		* @param full : true to generate a position within the whole Zonz, false only at its borders
		*/
		void addParticles(const Ref<Zone>& zone,const Ref<Emitter>& emitter,float deltaTime,bool full = true);

		/**
		* @brief Adds some Particles to this Group
		*
		* See addParticles(unsigned int,const Vector3D&,const Vector3D&) for a complete description.
		*
		* @param position : the position where the Particles will be added
		* @param emitter : the Emitter that will be used to generate the velocity
		* @param deltaTime : the step time that will be used to determine how many particles to generate
		*/
		void addParticles(const Vector3D& position,const Ref<Emitter>& emitter,float deltaTime);

		/**
		* @brief Adds some Particles to this Group
		*
		* See addParticles(unsigned int,const Vector3D&,const Vector3D&) for a complete description.
		*
		* @param emitter : the Emitter that will be used to generate the velocity and whose Zone will be used to generate the position
		* @param deltaTime : the step time that will be used to determine how many particles to generate
		*/
		void addParticles(const Ref<Emitter>& emitter,float deltaTime);

		/**
		* @brief Adds some Particles to this Group
		*
		* This method is slightly different to other addParticles methods as Particles are generated not at a point but on a line defined by start and end.<br>
		* The step is the distance between each Particle on the line and the offset is the starting distance to compute the first Particle's position.<br>
		* The offset is useful to generate equidistant particles on several lines. the returned offset has to be used as the passed offset for the next line.<br>
		* <br>
		* This method is useful to generate equidistant particles on lines no matter the framerate.<br>
		* <br>
		* See addParticles(unsigned int,const Vector3D&,const Vector3D&) for some complementary information.
		*
		* @param start : the position of the start of the line
		* @param end : the position of the end of the line
		* @param emitter : the Emitter that will be used to generate the velocity
		* @param step : the distance between each generated Particle
		* @param offset : the starting distance of the beginning of the line
		* @return the new offset at the end of the line
		*/
		float addParticles(const Vector3D& start,const Vector3D& end,const Ref<Emitter>& emitter,float step,float offset = 0.0f);

		/**
		* @brief Adds some Particles to this Group
		*
		* See addParticles(const Vector3D&,const Vector3D&,const Emitter*,float,float) for a complete description.
		*
		* @param start : the position of the start of the line
		* @param end : the position of the end of the line
		* @param velocity : the velocity of the Particles
		* @param step : the distance between each generated Particle
		* @param offset : the starting distance of the beginning of the line
		* @return the new offset at the end of the line
		*/
		float addParticles(const Vector3D& start,const Vector3D& end,const Vector3D& velocity,float step,float offset = 0.0f);

		void flushBufferedParticles();

		Ref<System> getSystem() const;

		/////////////
		// Actions //
		/////////////

		/**
		* 
		*
		*/
		void setBirthAction(const Ref<Action>& action);
		const Ref<Action>& getBirthAction() const;

		void setDeathAction(const Ref<Action>& action);
		const Ref<Action>& getDeathAction() const;

		//////////////////////
		// Advanced methods //
		//////////////////////

		/**
		* @brief Destroys the render buffer of the group
		* A new render buffer will be created by the renderer of the group whenever it is needed.
		*/
		void destroyRenderBuffer();

		/**
		* @brief Destroys all additionnal data held by the group
		* This includes the render buffer and all the data sets
		*/
		void destroyAllAdditionnalData();

		/**
		* @brief Gets the data set used by the given modifier
		* @return the data set or NULL if the modifier does not use data set or is not part of the group
		*/
		DataSet* getModifierDataSet(const Ref<Modifier>& modifier);

		/**
		* @brief Gets the data set used by the interpolator of the given parameter
		* @return the data set or NULL if the interpolator does not use data set or does not exist
		*/
		DataSet* getParamInterpolatorDataSet(Param param);

		/**
		* @brief Gets the data set used by the color interpolator
		* @return the data set or NULL if the color interpolator does not use data set or does not exist
		*/
		DataSet* getColorInterpolatorDataSet();

		/**
		* @brief Gets the data set used by the renderer
		* @return the data set or NULL if the renderer does not use data set or does not exist
		*/
		DataSet* getRendererDataSet();

		/**
		* @brief Gets the render buffer
		* @return the render buffer or NULL if the group does not use a render buffer
		*/
		RenderBuffer* getRenderBuffer();

		/**
		* @brief Gets the octree
		* A group will have an octree only if at least one of its modifiers has requested it.
		* @return the octree if some or NULL otherwise
		*/
		Octree* getOctree();

		///////////////////////
		// Virtual interface //
		///////////////////////

		virtual Ref<SPKObject> findByName(const std::string& name) override;
	
	protected :

		virtual void innerImport(const IO::Descriptor& descriptor) override;
		virtual void innerExport(IO::Descriptor& descriptor) const override;

	private :

		static const size_t NB_PARAMETERS = 5;
		static const float DEFAULT_VALUES[NB_PARAMETERS];

		// This holds the structure of arrays (SOA) containing data of particles
		struct ParticleData
		{
			bool initialized;

			size_t nbParticles;
			size_t maxParticles;

			// Particles attributes
			Vector3D* positions;
			Vector3D* velocities;
			Vector3D* oldPositions;

			float* ages;
			float* energies;
			float* lifeTimes;
			float* sqrDists;

			// Particles parameters
			Color* colors;
			float* parameters[NB_PARAMETERS];

			ParticleData() :
				initialized(false),
				nbParticles(0),
				maxParticles(0),
				positions(NULL),
				velocities(NULL),
				oldPositions(NULL),
				ages(NULL),
				energies(NULL),
				lifeTimes(NULL),
				sqrDists(NULL),
				colors(NULL)
			{
				for (size_t i = 0; i < NB_PARAMETERS; ++i)
					parameters[i] = NULL;
			}
		};

		struct WeakEmitterPair
		{
			Emitter* obj;
			size_t nbBorn;

			WeakEmitterPair(const Ref<Emitter>& obj,size_t nbBorn) :
				obj(obj.get()),
				nbBorn(nbBorn)
			{}
		};

		template<class T>
		struct DataHandlerDef
		{
			T obj;
			DataSet* dataSet;

			DataHandlerDef() :
				obj(),
				dataSet(NULL)
			{}

			DataHandlerDef(const T& obj,DataSet* dataSet) :
				obj(obj),
				dataSet(dataSet)
			{}
		};

		template<class T>
		struct WeakDataHandlerDef
		{
			T* obj;
			DataSet* dataSet;

			WeakDataHandlerDef() :
				obj(NULL),
				dataSet(NULL)
			{}

			WeakDataHandlerDef(T* obj,DataSet* dataSet) :
				obj(obj),
				dataSet(dataSet)
			{}

			WeakDataHandlerDef(const DataHandlerDef<Ref<T> >& def) :
				obj(def.obj.get()),
				dataSet(def.dataSet)
			{}

			WeakDataHandlerDef& operator=(const DataHandlerDef<Ref<T> >& def)	
			{
				obj = def.obj.get();
				dataSet = def.dataSet;
				return *this;
			}
		};

		struct RendererDef
		{
			Ref<Renderer> obj;
			DataSet* dataSet;
			RenderBuffer* renderBuffer;

			RendererDef() :
				obj(),
				dataSet(NULL),
				renderBuffer(NULL)
			{}
		};

		typedef DataHandlerDef<Ref<Modifier> > ModifierDef;
		typedef WeakDataHandlerDef<Modifier> WeakModifierDef;

		typedef DataHandlerDef<Ref<ColorInterpolator> > ColorInterpolatorDef;
		typedef DataHandlerDef<Ref<FloatInterpolator> > FloatInterpolatorDef;

		// Functor used to sort modifiers by priority
		struct CompareModifierPriority
		{
			bool operator()(const WeakModifierDef& modifier0, const WeakModifierDef& modifier1) const
			{
				return modifier0.obj->getPriority() < modifier1.obj->getPriority();
			}
		};

		struct CreationData
		{
			unsigned int nb;
			Vector3D position;
			Vector3D velocity;
			Ref<Zone> zone;
			Ref<Emitter> emitter;
			bool full;
		};

		System* system;

		ParticleData particleData;
		size_t enabledParamIndices[NB_PARAMETERS];
		size_t nbEnabledParameters;

		ColorInterpolatorDef colorInterpolator;
		FloatInterpolatorDef paramInterpolators[NB_PARAMETERS];

		std::vector<Ref<Emitter> > emitters;
		mutable std::vector<WeakEmitterPair> activeEmitters;

		std::vector<ModifierDef> modifiers;
		std::vector<WeakModifierDef> sortedModifiers;
		mutable std::vector<WeakModifierDef> activeModifiers;
		mutable std::vector<WeakModifierDef> initModifiers;

		RendererDef renderer;

		Ref<Action> birthAction;
		Ref<Action> deathAction;

		std::list<DataSet> dataSets;

		float minLifeTime;
		float maxLifeTime;
		bool immortal;
		bool still;

		bool distanceComputationEnabled;
		bool sortingEnabled;

		Vector3D AABBMin;
		Vector3D AABBMax;

		float physicalRadius;
		float graphicalRadius;

		Octree* octree;

		Group(const Ref<System>& system = SPK_NULL_REF,size_t capacity = 100);
		Group(const Group& group);

		bool updateParticles(float deltaTime);
		void renderParticles();

		bool initParticle(size_t index,size_t& emitterIndex,size_t& nbManualBorn);
		void swapParticles(size_t index0,size_t index1);

		void recomputeEnabledParamIndices();

		template<typename T>
		void reallocateArray(T*& t,size_t newSize,size_t copySize);

		DataSet* attachDataSet(DataHandler* dataHandler);
		void detachDataSet(DataSet* dataHandler);

		void sortParticles(int start,int end);
		virtual void propagateUpdateTransform() override;

		void sortParticles();
		void computeAABB();

		void addParticles(
			unsigned int nb,
			const Vector3D& position,
			const Vector3D& velocity,
			const Ref<Zone>& zone,
			const Ref<Emitter>& emitter,
			bool full = false);

		void emptyBufferedParticles();

		// creation data
		std::deque<CreationData> creationBuffer;
		unsigned int nbBufferedParticles;

		void prepareAdditionnalData();
		void manageOctreeInstance(bool needsOctree);

		void initData();
	};

	inline Ref<Group> Group::create(size_t capacity)
	{
		return SPK_NEW(Group,SPK_NULL_REF,capacity);
	}

	template<typename T>
	void Group::reallocateArray(T*& t,size_t newSize,size_t copySize)
	{
		T* oldT = t;
		t = SPK_NEW_ARRAY(T,newSize);
		if (oldT != NULL && copySize != 0)
			std::memcpy(oldT,t,copySize * sizeof(T));
		SPK_DELETE_ARRAY(oldT);
	}
		
	inline bool Group::isInitialized() const
	{
		return system != NULL && system->isInitialized();
	}

    inline void Group::removeAllEmitters()
    {
        emitters.clear();
    }

    inline void Group::setScaleInterpolator(const Ref<FloatInterpolator>& interpolator)
    {
        setParamInterpolator(PARAM_SCALE, interpolator);
    }

    inline void Group::setMassInterpolator(const Ref<FloatInterpolator>& interpolator)
    {
        setParamInterpolator(PARAM_MASS, interpolator);
    }

    inline void Group::setAngleInterpolator(const Ref<FloatInterpolator>& interpolator)
    {
        setParamInterpolator(PARAM_ANGLE, interpolator);
    }

    inline void Group::setTextureIndexInterpolator(const Ref<FloatInterpolator>& interpolator)
    {
        setParamInterpolator(PARAM_TEXTURE_INDEX, interpolator);
    }

    inline void Group::setRotationSpeedInterpolator(const Ref<FloatInterpolator>& interpolator)
    {
        setParamInterpolator(PARAM_ROTATION_SPEED, interpolator);
    }

    inline const Ref<FloatInterpolator>& Group::getScaleInterpolator() const
    {
        return getParamInterpolator(PARAM_SCALE);
    }

    inline const Ref<FloatInterpolator>& Group::getMassInterpolator() const
    {
        return getParamInterpolator(PARAM_MASS);
    }

    inline const Ref<FloatInterpolator>& Group::getAngleInterpolator() const
    {
        return getParamInterpolator(PARAM_ANGLE);
    }

    inline const Ref<FloatInterpolator>& Group::getTextureIndexInterpolator() const
    {
        return getParamInterpolator(PARAM_TEXTURE_INDEX);
    }

    inline const Ref<FloatInterpolator>& Group::getRotationSpeedInterpolator() const
    {
        return getParamInterpolator(PARAM_ROTATION_SPEED);
    }

	inline void Group::setImmortal(bool immortal)
	{
		this->immortal = immortal;
	}

	inline void Group::setStill(bool still)
	{
		this->still = still;
	}

	inline const Ref<FloatInterpolator>& Group::getParamInterpolator(Param param) const
	{
		return paramInterpolators[param].obj;
	}

	inline const Ref<ColorInterpolator>& Group::getColorInterpolator() const
	{
		return colorInterpolator.obj;
	}

	inline float Group::getMinLifeTime() const
	{
		return minLifeTime;
	}

	inline float Group::getMaxLifeTime() const
	{
		return maxLifeTime;
	}

	inline bool Group::isImmortal() const
	{
		return immortal;
	}

	inline bool Group::isStill() const
	{
		return still;
	}

	inline bool Group::isEnabled(Param param) const
	{
		return particleData.parameters[param] != NULL;
	}

	inline size_t Group::getNbParticles() const
	{
		return particleData.nbParticles;
	}

	inline size_t Group::getCapacity() const
	{
		return particleData.maxParticles;
	}

	inline void Group::empty()
	{
		particleData.nbParticles = 0;
	}

	inline const Ref<Emitter>& Group::getEmitter(size_t index) const
	{
		SPK_ASSERT(index < getNbEmitters(),"Group::getEmitter(size_t) - Index of emitter is out of bounds : " << index);
		return emitters[index];
	}

	inline size_t Group::getNbEmitters() const
	{
		return emitters.size();
	}

	inline const Ref<Modifier>& Group::getModifier(size_t index) const
	{
		SPK_ASSERT(index < getNbModifiers(),"Group::geModifier(size_t) - Index of modifier is out of bounds : " << index);
		return modifiers[index].obj;
	}

	inline size_t Group::getNbModifiers() const
	{
		return modifiers.size();
	}

	inline const Ref<Renderer>& Group::getRenderer() const
	{
		return renderer.obj;
	}

	inline void Group::enableDistanceComputation(bool distanceComputation)
	{
		distanceComputationEnabled = distanceComputation;
	}

	inline bool Group::isDistanceComputationEnabled() const
	{
		return distanceComputationEnabled;
	}

	inline void Group::enableSorting(bool sorting)
	{
		sortingEnabled = distanceComputationEnabled = sorting;
	}

	inline bool Group::isSortingEnabled() const
	{
		return sortingEnabled;
	}

	inline const void* Group::getColorAddress() const
	{
		return particleData.colors;
	}

	inline const void* Group::getPositionAddress() const
	{
		return particleData.positions;
	}

	inline const void* Group::getVelocityAddress() const
	{
		return particleData.velocities;
	}

	inline const void* Group::getParamAddress(Param param) const
	{
		return particleData.parameters[param];
	}

	inline const Vector3D& Group::getAABBMin() const
	{
		return AABBMin;
	}

	inline const Vector3D& Group::getAABBMax() const
	{
		return AABBMax;
	}

	inline void Group::setRadius(float radius)
	{
		setGraphicalRadius(radius);
		setPhysicalRadius(radius);
	}

	inline float Group::getGraphicalRadius() const
	{
		return graphicalRadius;
	}

	inline float Group::getPhysicalRadius() const
	{
		return physicalRadius;
	}

	inline void Group::addParticles(unsigned int nb,const Vector3D& position,const Vector3D& velocity)
	{
		addParticles(nb,position,velocity,SPK_NULL_REF,SPK_NULL_REF);
	}

	inline Ref<System> Group::getSystem() const
	{
		return system;
	}

	inline const Ref<Action>& Group::getBirthAction() const
	{
		return birthAction;
	}

	inline const Ref<Action>& Group::getDeathAction() const
	{
		return deathAction;
	}

	inline DataSet* Group::getParamInterpolatorDataSet(Param param)
	{
		return paramInterpolators[param].dataSet;
	}

	inline DataSet* Group::getColorInterpolatorDataSet()
	{
		return colorInterpolator.dataSet;
	}

	inline DataSet* Group::getRendererDataSet()
	{
		return renderer.dataSet;
	}

	inline RenderBuffer* Group::getRenderBuffer()
	{
		return renderer.renderBuffer;
	}
}

#endif
