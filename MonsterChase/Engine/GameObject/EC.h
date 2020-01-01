#pragma once
#include <vector>
#include <array>
#include <bitset>
#include <string>
using namespace std;
class Entity;
class Component;

inline size_t getComponentTypeID()
{
	static size_t lastID = 0;
	return lastID++;
}
template<typename T>
inline size_t getComponentTypeID() noexcept
{
	static size_t typeID = getComponentTypeID();
	return typeID;
}
constexpr size_t maxComponents = 32;
using ComponentBitset = bitset<maxComponents>;
using ComponentArray = array<Component*, maxComponents>;
class Component
{
public:
	Entity *entity=nullptr;
	virtual void init() = 0;
	virtual void update()=0;
	virtual ~Component() {}
private:
	
};
class Entity
{
public:
	Entity() :componentArray({nullptr})
	{}
	bool& getactive()
	{
		return active;
	}
	template<typename T>
	void AddComponent(T *i_Component)
	{
		if (i_Component)
		{
			i_Component->entity = this;
			m_Components.push_back(i_Component);
			componentArray[getComponentTypeID<T>()] = i_Component;
		}
	}
	template<typename T>
	T* getComponent()
	{
		T*  ptr = static_cast<T*>(componentArray[getComponentTypeID<T>()]);
		return ptr;
	}
	void update()
	{
		for (size_t i = 0; i < m_Components.size(); i++)
		{
			m_Components[i]->update();
		}
	}
	~Entity()
	{
		for (size_t i = 0; i < m_Components.size(); i++)
		{
			delete m_Components[i];
		}
	}
private:
	bool                      active = true;
	std::vector<Component*>   m_Components;
	ComponentArray            componentArray;
	ComponentBitset           componentBitset;
};
class Manager
{
public:
	/*Manager()
	{}*/
	inline vector<Entity*>& getEntities()
	{
		return m_Entities;
	}
	void AddEntity(Entity* i_Entity)
	{
		if (i_Entity)
			m_Entities.push_back(i_Entity);
	}
	void update()
	{
		refresh();
		for (size_t i = 0; i < m_Entities.size(); i++)
		{	
			m_Entities[i]->update();
		}
	}
	void refresh()
	{
		for (size_t i = 0; i < m_Entities.size(); i++)
		{
			if (m_Entities[i]->getactive() == false)
			{
				m_Entities[i]->~Entity();
				m_Entities.erase(m_Entities.begin()+i);
				
			}
		}
	}
	~Manager()
	{
		for (size_t i = 0; i < m_Entities.size(); i++)
		{
			delete m_Entities[i];
		}
	}
private:
	vector<Entity*>        m_Entities;
};

