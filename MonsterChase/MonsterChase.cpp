// MonsterChase.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <Windows.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include "Engine.h"
#include "HeapManager.h"
#include "HeapManager_UnitTest.h"
#include "GameObject\GameObject.h"
#define Point2D_UnitTest
#define MonsterChase
#define HeapManagerUnitTest
//#define myTestForHM
using std::cin;
using std::cout;
using namespace Engine;
using namespace Math;
using namespace HeapManagerProxy;

int main(int argc, char* argv[])
{
#ifdef Point2D_UnitTest
	const Point2D P1(4.0f, 5.0f);
	Point2D P2(1.0f, 2.0f);
	cout << "p1 is " << P1 << "P2 is " << P2 << std::endl;
	Point2D P3 = P1 + P2;
	cout << "p3 is " << P3 << std::endl;
	P3 = P1 - P2;
	cout << "p3 is after sub" << P3 << std::endl;
	Point2D P4 = P1 * 0.5f;
	cout << "p4 is " << P4 << std::endl;
	Point2D P5 = P1 / 2.0f;
	cout << "p5 is " << P5 << std::endl;
	Point2D P6 = -P4;
	cout << "p6 is " << P6 << std::endl;
	P2 *= P1;
	cout <<"P2 is "<< P2<<std::endl;
	P6 *= 2.0f;
	P5 /= 4.0f;
	cout << "p6 & P5 is " << P6 << " " << P5 << std::endl;
	P2 += P1;
	P3 -= P1;
	cout << "p2 & P3 is " << P2 << " " << P3 << std::endl;
	Point2D P7 = (((P1 + P2) * 2.0f) - -P3) / 2.0f;
	cout << "p7 is " << P7 << std::endl;
	bool bArentEqual = P6 != P4;
	cout << bArentEqual<<std::endl;
	cout << "P1 is " << P1;
#endif // Point2D_UnitTest & ConstCorrectness_UnitTest
#ifdef MonsterChase
	const size_t 		sizeHeap = 1024 * 1024;
	const unsigned int 	numDescriptors = 2048;
	void* pHeapMemory = HeapAlloc(GetProcessHeap(), 0, sizeHeap);
	HeapManager * pHeapManager = CreateHeapManager(pHeapMemory, sizeHeap, numDescriptors);
	Init();
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
	//GameObject **m = static_cast<GameObject**>(calloc(numberOfMonsters, sizeof(GameObject*)));
	GameObject **m = static_cast<GameObject**>(alloc(pHeapManager, numberOfMonsters * sizeof(GameObject*)));
	for (int i = 0; i < numberOfMonsters; i++)
	{
		m[i] = new GameObject(Point2D(rand() % +200 - 100 + i, rand() % +200 - 100 + i));
		//new (m + i) GameObject(Point2D(rand() % +200 - 100 + i, rand() % +200 - 100 + i));
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
			//m[numberOfMonsters - 1]->~GameObject();
			delete(m[numberOfMonsters - 1]);
			numberOfMonsters -= 1;
			//GameObject** t = static_cast<GameObject**>(realloc(m, numberOfMonsters* (sizeof(GameObject*))));
			GameObject** t = static_cast<GameObject**>(realloc(pHeapManager, m, numberOfMonsters* (sizeof(GameObject*))));
			m = t;
			cout << "A monster was deleted \n";
			AddorDelInd = 5;
		}
		if (AddorDelInd == 4)
		{
			numberOfMonsters += 1;
			//GameObject** t = static_cast<GameObject**>(realloc(m, numberOfMonsters*(sizeof(GameObject*))));
			GameObject** t = static_cast<GameObject**>(realloc(pHeapManager, m, numberOfMonsters* (sizeof(GameObject*))));
			cout << "Adding New Monster enter name \n";
			if (t != nullptr)
			{
				t[numberOfMonsters - 1] = new GameObject(Point2D(rand() % +200 - 100, rand() % +200 - 100));
				//new (t + numberOfMonsters - 1)GameObject(Point2D(rand() % +200 - 100, rand() % +200 - 100));
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
#endif // MonsterChase
#ifdef HeapManagerUnitTest
	HeapManager_UnitTest();
#endif // HeapManagerUnitTest
#ifdef myTestForHM
	const size_t 		sizeHeap = 1024 * 1024;
	const unsigned int 	numDescriptors = 2048;
	void* pHeapMemory = HeapAlloc(GetProcessHeap(), 0, sizeHeap);
	HeapManager * pHeapManager = CreateHeapManager(pHeapMemory, sizeHeap, numDescriptors);
	int *P = (int*)alloc(pHeapManager, 13, 4);
	for (int i = 0; i < 5; i++)
	{
		P[i] = 1;
	}
	free(pHeapManager,P);
#endif

exit(1);
	
}


