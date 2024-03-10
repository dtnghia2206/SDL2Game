#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group		  = std::size_t;

inline ComponentID GetNewComponentTypeID()
{
	static ComponentID lastID = 0u;
	return lastID++;
}

template <typename T> inline ComponentID GetComponentTypeID() noexcept
{
	static_assert (std::is_base_of<Component, T>::value, "");
	static ComponentID typeID = GetNewComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet	= std::bitset<maxComponents>;
using GroupBitset		= std::bitset<maxGroups>;
using ComponentArray	= std::array<Component*, maxComponents>;

class Component
{
public: 
	Entity* entity;

	virtual void Initialize() {}
	virtual void Update() {}
	virtual void Draw() {}
	virtual ~Component() {}
};

class Entity
{
private:
	Manager& manager;
	bool vbActive = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray	voComponentArray;
	ComponentBitSet voComponentBitset;
	GroupBitset		voGroupBitset;

public:
	Entity(Manager& mManager) : manager(mManager) {}

	void Update()
	{
		for (auto& c : components) c->Update();
	}
	void Draw() 
	{
		for (auto& c : components) c->Draw();
	}

	bool IsActive() const { return vbActive; }
	void Destroy() { vbActive = false; }

	bool HasGroup(Group mGroup)
	{
		return voGroupBitset[mGroup];
	}

	void AddGroup(Group mGroup);
	void DeleteGroup(Group mGroup)
	{
		voGroupBitset[mGroup] = false;
	}

	template <typename T> bool HasComponent() const
	{
		return voComponentBitset[GetComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs>
	T& AddComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component>uPtr { c };
		components.emplace_back(std::move(uPtr));

		voComponentArray[GetComponentTypeID<T>()] = c;
		voComponentBitset[GetComponentTypeID<T>()] = true;

		c->Initialize();
		return *c;
	}

	template<typename T> T& GetComponent() const
	{
		auto ptr(voComponentArray[GetComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
};

class Manager
{
private:
	std::vector<std::unique_ptr<Entity>>		voEntities;
	std::array<std::vector<Entity*>, maxGroups> voGroupedEntities;

public:
	void Update()
	{
		for (auto& e : voEntities) e->Update();
	}
	void Draw()
	{
		for (auto& e : voEntities) e->Draw();
	} 
	void Refresh()
	{
		
		for (auto i(0u); i < maxGroups; i++)
		{
			auto& v(voGroupedEntities[i]);
			v.erase(
				std::remove_if(std::begin(v), std::end(v),
					[i](Entity* mEntity)
			{
				return !mEntity->IsActive() || !mEntity->HasGroup(i);
			}),
				std::end(v));
		}
		
		
		voEntities.erase(std::remove_if(std::begin(voEntities), std::end(voEntities),
			[](const std::unique_ptr<Entity> &mEntity)
		{
			return !mEntity->IsActive();
		}),
			std::end(voEntities));
		
	}

	void AddToGroup(Entity* mEntity, Group mGroup)
	{
		voGroupedEntities[mGroup].emplace_back(mEntity);
	}

	std::vector<Entity*>& GetGroup(Group mGroup)
	{
		return voGroupedEntities[mGroup];
	}

	Entity& AddEntity()
	{
		Entity *e = new Entity(*this);
		std::unique_ptr<Entity> uPtr { e };
		voEntities.emplace_back(std::move(uPtr));
		return *e;
	}

	Entity* AddEntity_Pointer()
	{
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{ e };
		voEntities.emplace_back(std::move(uPtr));
		return e;
	}
};