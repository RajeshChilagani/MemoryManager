#include "Math/Point2D.h"
#include "HeapManager_UnitTest.h"

#include <iostream>
using namespace std;

#define Point2D_UnitTest
int main()
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
	cout << "P2 is " << P2 << std::endl;
	P6 *= 2.0f;
	P5 /= 4.0f;
	cout << "p6 & P5 is " << P6 << " " << P5 << std::endl;
	P2 += P1;
	P3 -= P1;
	cout << "p2 & P3 is " << P2 << " " << P3 << std::endl;
	Point2D P7 = (((P1 + P2) * 2.0f) - -P3) / 2.0f;
	cout << "p7 is " << P7 << std::endl;
	bool bArentEqual = P6 != P4;
	cout << bArentEqual << std::endl;
	cout << "P1 is " << P1 << "\n";
#endif // Point2D_UnitTest & ConstCorrectness_UnitTest
#ifdef myTestForHM
	int *P = (int*)alloc(pHeapManager, 13, 4);
	for (int i = 0; i < 5; i++)
	{
		P[i] = 1;
	}
	free(pHeapManager, P);
#endif
	
	HeapManager_UnitTest();
}