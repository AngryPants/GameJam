#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "IDGenerator.h"
#include <string>
#include <bitset>
#include <exception>
#include <set>
#include <map>
#include "ComponentManager.h"
#include "GameObjectManager.h"
#include "Script.h"

using namespace std;

typedef std::bitset<MAX_COMPONENTS> ComponentBitset;

class GameObject {

private:
	//Variable(s)
	string space;
	ComponentBitset componentBitset;
	Component* components[MAX_COMPONENTS];
	bool destroyed;

public:
	//Variable(s)
	string name;
	string tag;
	Script* scripts[8];

	//Constructor(s) & Destructor
	GameObject(const string& space, const string& name = "GameObject") : space(space), name(name) {
		destroyed = false;
		for (unsigned int i = 0; i < MAX_COMPONENTS; ++i) {
			this->components[i] = nullptr;
		}
		for (unsigned int i = 0; i < sizeof(scripts)/sizeof(scripts[0]); ++i) {
			scripts[i] = nullptr;
		}
		tag = "Default";
	}
	virtual ~GameObject() {
		for (unsigned int i = 0; i < MAX_COMPONENTS; ++i) {
			if (this->components[i] != nullptr) {
				ComponentManager::GetInstance().RemoveComponent(*components[i], i);
			}
		}
		componentBitset.reset();
		for (unsigned int i = 0; i < sizeof(scripts)/sizeof(scripts[0]); ++i) {
			if (scripts[i] != nullptr) {
				delete scripts[i];
			}
		}
	}

	//Name
	void SetName(const string& name) {
		this->name = name;
	}
	const string& GetName() const {
		return this->name;
	}
	const string& GetSpace() const {
		return this->space;
	}

	//Components
	template <class Type>
	bool HasComponent() const {
		return componentBitset[IDGenerator::GetInstance().GetComponentTypeID<Type>()];
	}

	template <class Type>
	Type& AddComponent() {
		if (HasComponent<Type>()) {
			cout << "This GameObject already has this component." << endl;
			throw std::exception("This GameObject already has this component.");
		}

		ComponentTypeID id = IDGenerator::GetInstance().GetComponentTypeID<Type>();
		componentBitset[id] = 1;
		Component* componentPtr = &ComponentManager::GetInstance().CreateComponent<Type>(*this);
		components[id] = componentPtr;
		
		return *(static_cast<Type*>(componentPtr));
	}

	template <class Type>
	void RemoveComponent() {
		if (!HasComponent<Type>) {
			cout << "This GameObject does not have this component." << endl;
			throw std::exception("This GameObject does not have this component.");
			return;
		}

		ComponentTypeID id = IDGenerator::GetComponentTypeID<Type>();
		componentBitset[id] = 0;
		ComponentManager::GetInstance().RemoveComponent(*components[id]);
		components[id] = nullptr;
	}

	template <class Type>
	Type& GetComponent() {
		if (!HasComponent<Type>()) {
			cout << "This GameObject does not have this component." << endl;
			throw std::exception("This GameObject does not have this component.");
		}

		Component* componentPtr = components[IDGenerator::GetInstance().GetComponentTypeID<Type>()];
		return *(static_cast<Type*>(componentPtr));
	}
	
	const ComponentBitset& GetComponentBitset() const {
		return this->componentBitset;
	}

	//Destruction
	void Destroy() {
		destroyed = true;
		GameObjectManager::GetInstance().RemoveGameObject(*this);
	}
	bool IsDestroyed() const {
		return destroyed;
	}

};

#endif