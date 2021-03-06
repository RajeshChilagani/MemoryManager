#include "MemoryManager/MemoryInterface.h"
#include "Engine.h"

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
using namespace std;
using namespace Engine;

//#define MonsterChase //->MonsterChase without component system
#define ECMonsterChase //->MonsterChase with component system
//#define PlacementNEW
#ifdef MonsterChase
#include "GameObject\GameObject.h"
using namespace Math;
#endif
#ifdef ECMonsterChase
#include "GameObject\EC.h"
#include "Components.h"
#endif 
int main(int argc, char* argv[])
{
	Engine::Init();
	const size_t 		sizeHeap = 1024 * 1024;
	const unsigned int 	numDescriptors = 2048;

	void* pHeapMemory = HeapAlloc(GetProcessHeap(), 0, sizeHeap);
	InitMemoryManager(pHeapMemory,sizeHeap,numDescriptors);
#ifdef MonsterChase
	
	int AddorDelInd = 5;
	cout << "How Many Monsters Do You Want In The Game:";
	int numberOfMonsters;
	cin >> numberOfMonsters;
	while (!cin)
	{
		cout << "Bad Input try again \n";
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "How Many Monsters Do You Want In The Game:";
		cin >> numberOfMonsters;

	}
	cin.ignore();

	//Monsters
	GameObject **m = static_cast<GameObject**>(alloc(pHeapManager, numberOfMonsters * sizeof(GameObject*)));
	for (int i = 0; i < numberOfMonsters; i++)
	{
		m[i] = new GameObject(Point2D(rand() % +200 - 100 + i, rand() % +200 - 100 + i));
		cout << "Enter The Name Of The Monster" << i + 1 << ":";
		m[i]->getName();
	}

	// Player
	cout << "Enter The Player Name:";
	GameObject *p = new GameObject(Point2D(0, 0));
	p->getName();


	// GameLoop 
	char keyBoardInput;
	do {
		for (int i = 0; i < numberOfMonsters; i++)
		{
			m[i]->getPositions();
		}
		p->getPositions();
		if (AddorDelInd == 0 && m != nullptr)
		{
			delete(m[numberOfMonsters - 1]);
			numberOfMonsters -= 1;
			GameObject** t = static_cast<GameObject**>(realloc(pHeapManager, m, numberOfMonsters* (sizeof(GameObject*))));
			m = t;
			cout << "A monster was deleted \n";
			AddorDelInd = 5;
		}
		if (AddorDelInd == 4)
		{
			numberOfMonsters += 1;
			GameObject** t = static_cast<GameObject**>(realloc(pHeapManager, m, numberOfMonsters* (sizeof(GameObject*))));
			cout << "Adding New Monster enter name \n";
			if (t != nullptr)
			{
				t[numberOfMonsters - 1] = new GameObject(Point2D(rand() % +200 - 100, rand() % +200 - 100));
				t[numberOfMonsters - 1]->getName();
				m = t;
			}
		}
		AddorDelInd--;
		for (int i = 0; i < numberOfMonsters; i++)
		{
			m[i]->move(Point2D(rand() % +200 - 100, rand() % +200 - 100));
		}
		cout << "Press A to move LEFT Press D to move RIGHT Press W to move UP Press S to move DOWN Q to QUIT\n";
		keyBoardInput = _getch();
		switch (keyBoardInput)
		{
		case 'a':
			p->move(Point2D(-1, 0));
			break;
		case 'd':
			p->move(Point2D(1, 0));
			break;
		case 'w':
			p->move(Point2D(0, 1));
			break;
		case 's':
			p->move(Point2D(0, -1));
			break;
		default:
			break;
		}
	} while (keyBoardInput != 'q');
	delete p;
	for (int i = 0; i < numberOfMonsters; i++)
	{
		delete(m[i]);
	}
	free(pHeapManager, m);
	_CrtDumpMemoryLeaks();
#endif
#ifdef ECMonsterChase
#ifdef PlacementNEW
	void* PlacmentT = malloc(sizeof(Manager));
	Manager * manager = new (static_cast<uint8_t*>(PlacmentT)) Manager();
#else
	Manager * manager = new (NEW_ALIGN_32) Manager();
#endif
	
	cout << "How Many Monsters Do You Want In The Game:";
	int numberOfMonsters;
	cin >> numberOfMonsters;
	while (!cin)
	{
		cout << "Bad Input try again \n";
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "How Many Monsters Do You Want In The Game:";
		cin >> numberOfMonsters;

	}
	cin.ignore();
	for (int i = 0; i < numberOfMonsters; i++)
	{
		Entity *monster = new Entity();
		monster->getactive() = true;
		EntityInfo *monsterInfo = new EntityInfo("monster");
		monster->AddComponent(monsterInfo);
		printf("enter name of monster %d :", i);
		//cout << "enter name of monster "<<i<< ": ";
		monsterInfo->getInfo();
		Transform*  transform = new Transform();
		monster->AddComponent(transform);
		EnemyController *enemyCon = new EnemyController();
		monster->AddComponent(enemyCon);
		enemyCon->init();
		manager->AddEntity(monster);
	}
	Entity *player = new Entity();
	player->getactive() = true;

	EntityInfo *playerInfo = new EntityInfo("player");
	player->AddComponent(playerInfo);
	cout << "enter name of player :";
	playerInfo->getInfo();
	
	Transform*  playerTransform = new Transform();
	player->AddComponent(playerTransform);

	PlayerController * playerCon = new PlayerController();
	player->AddComponent(playerCon);
	playerCon->init();

	manager->AddEntity(player);
	while (player->getComponent<PlayerController>()->getGameOver()!=true)
	{
		vector<Entity*> allEntities = manager->getEntities();
		for (size_t i = 0; i < allEntities.size(); ++i)
		{
			if (strcmp(allEntities[i]->getComponent<EntityInfo>()->Tag(), "monster")==0)
			{
				Entity* e = allEntities[i];
				if (allEntities[i]->getComponent<Transform>()->getPosition().x() > 1000 || allEntities[i]->getComponent<Transform>()->getPosition().y() > 1000)
				{
					allEntities[i]->getactive() = false;
				}
			}
		}
		if (static_cast<int>(allEntities.size() - 1) < numberOfMonsters)
		{
			Entity *monster = new Entity();
			monster->getactive() = true;
			EntityInfo *monsterInfo = new EntityInfo("monster");
			monster->AddComponent(monsterInfo);
			cout << "enter name of new monster :";
			monsterInfo->getInfo();
			Transform*  transform = new Transform();
			monster->AddComponent(transform);
			ChasePlayer *chasePlayerMon = new ChasePlayer();
			monster->AddComponent(chasePlayerMon);
			chasePlayerMon->init();
			chasePlayerMon->chase(player);
			manager->AddEntity(monster);
		}
		manager->update();
	}
	
#ifdef PlacementNEW
	manager->~Manager();
	free(PlacmentT);
#else
	delete(manager);
#endif	
#endif // ECMonsterChase
_CrtDumpMemoryLeaks();
Engine::ShutDown();
}


