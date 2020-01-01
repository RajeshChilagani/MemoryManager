#pragma once
#include "GameObject/EC.h"
#include "Math/Point2D.h"
#include "Utilities/Utilities.h"

#include <conio.h>
#include <time.h>
class EntityInfo : public Component
{
public:
	EntityInfo(const char* tagName):m_Tag(tagName?_strdup(tagName):nullptr)
	{}
	void init() override
	{

	}
	inline const char* Tag()
	{
		return m_Tag;
	}
	void getInfo()
	{
		Name = GenString();
	}
	void showInfo()
	{
		//cout<<this->Name;
		printf("%s",this->Name);
	}
	void  update() override
	{
	}
	~EntityInfo()
	{
		free(this->Name);
		free(const_cast<char*>(this->m_Tag));
	}
private:
	char*                Name = nullptr;
	const char*          m_Tag = nullptr;
};
class Transform : public Component
{
public:
	Transform():position(Point2D(0,0)),velocity(Point2D(0,0))
	{}
	inline Point2D & getPosition()
	{
		return position;
	}
	inline Point2D & getVelocity()
	{
		return velocity;
	}
	void init() override
	{

	}
	void update() override
	{
		position += velocity;
		show();
	}
	void show()
	{
		entity->getComponent<EntityInfo>()->showInfo();
		printf(" is at ( %d,%d) \n", position.x(), position.y());
		//cout << " is at " << position<<endl;
	}
private:
	Point2D          position;
	Point2D          velocity;
};
class PlayerController : public Component
{
public:
	PlayerController():userInput(NULL),transformCom(nullptr),isGameOver(false)
	{
	}
	bool getGameOver() const
	{
		return this->isGameOver;
	}
	void init() override
	{
		transformCom = entity->getComponent<Transform>();
	}
	void update() override
	{
		cout << "Press A to move LEFT Press D to move RIGHT Press W to move UP Press S to move DOWN Q to QUIT\n";
		userInput = _getch();
		switch (userInput)
		{
		case 'a':
			transformCom->getVelocity() =  Point2D(-1, 0);
			break;
		case 'd':
			transformCom->getVelocity() = Point2D(1, 0);
			break;
		case 'w':
			transformCom->getVelocity() = Point2D(0, 1);
			break;
		case 's':
			transformCom->getVelocity() = Point2D(0, -1);
			break;
		case 'q':
			this->isGameOver = true;
			break;
		default:
			break;
		}
	}
private:
	Transform *           transformCom;
	char                  userInput;
	bool                  isGameOver;
};
class EnemyController : public Component
{
public:
	EnemyController():transformcom(nullptr)
	{
		srand(static_cast<unsigned int>(time(0)));
	}
	void init() override
	{
		transformcom = entity->getComponent<Transform>();
	}
	void update() override
	{
		transformcom->getVelocity() = Point2D(rand() % 200, rand() % 200);
	}
private:
	Transform*          transformcom;
};
class ChasePlayer : public Component
{
public:
	ChasePlayer() :transformcom(nullptr), player(nullptr)
	{}
	void init() override
	{
		transformcom = entity->getComponent<Transform>();
	}
	inline void chase(Entity* player)
	{
		this->player = player;
	}
	void update() override
	{
		transformcom->getPosition() = this->player->getComponent<Transform>()->getPosition();
	}
private:
	Transform*          transformcom;
	Entity*             player;
};