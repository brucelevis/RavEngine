//
//  Entity.hpp
//  RavEngine_Static
//
//  Copyright © 2020 Ravbug. 
//

#pragma once
#include "SharedObject.hpp"
#include "Component.hpp"
#include "Transform.hpp"
#include "WeakRef.hpp"
#include "PhysicsBodyComponent.hpp" 
#include "ComponentStore.hpp"

/**
 This class defines an Entity for the Entity Component System.
 */
namespace RavEngine {
	class PhysicsBodyComponent;
	class World;

	class Entity : public SharedObject {
	protected:
		//store the components on this Entity
		ComponentStore components;

		ComponentStore addBuffer;
		ComponentStore removalBuffer;

		WeakRef<World> worldptr;  //non-owning

	public:

		//required virtual destructor for SharedObject
		virtual ~Entity();

		/**
		Get a const reference to the components in this entity
		@return the components in this Entity
		*/
		inline ComponentStore& Components() {
			return components;
		}

		/**
		 Get a pointer to the world that this entity is in. May be nullptr.
		 @return the pointer to the world, or nullptr if there is no world
		 */
		inline WeakRef<World> GetWorld() const {
			return worldptr;
		}

		/**
		 Called by the world on Spawn and Destroy.
		 @param world the pointer to the current world
		 */
		inline void SetWorld(const WeakRef<World>& world) {
			worldptr = world;
		}

		/**
		 Check if this Entity has been spawned
		 @return true if the entity is in the world, false otherwise
		 @note Does not investigate dangling pointer
		 */
		inline bool IsInWorld() const {
			return !worldptr.isNull();
		}

		/**
		Add a component to this entity. Use this call to ensure the component post-add hook gets invoked, and ownership is set correctly.
		@param componentRef the component to add
		*/
		template<class T>
		Ref<T> AddComponent(Ref<T> componentRef) {
			componentRef->SetOwner(this);
			Ref<Component> c(componentRef);
			c->AddHook(this);

			//synchronize with world
			if (IsInWorld()) {
				addBuffer.AddComponent(componentRef);
				SyncAdds();
			}

			return components.AddComponent<T>(componentRef);
		}

		template<class T>
		Ref<T> RemoveComponent(Ref<T> componentRef) {
			Ref<Component> c(componentRef);
			c->RemoveHook(this);
			componentRef->SetOwner(nullptr);

			if (IsInWorld()) {
				removalBuffer.AddComponent(componentRef);
				SyncRemovals();
			}
		}

		/**
		Invoked by the world when the entity is added to the World
		*/
		virtual void Start() {}

		/**
		Invoked by the world when the entity is despawned, but despawning has not happened yet. Use to preemptively clean up data.
		*/
		virtual void Stop() {}

		/**
		 Create an Entity. This constructor will add the components and their default values to the Entity.
		 */
		Entity();

		/**
		 @return a reference to the transform component, which all entities possess
		 */
		Ref<Transform> transform();

		/**
		Remove this entity from the world. If there are no more references, it will be destroyed.
		*/
		void Destroy();

	protected:
		void SyncAdds();
		void SyncRemovals();
	};
}
