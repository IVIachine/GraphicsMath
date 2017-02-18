#include "Quaternion.h"
#include <iostream>

int main()
{
	Quaternion test = Quaternion(-.75, -.02, -.73, .24);
	Quaternion xyz = Quaternion::makeXYZRotation(2, 5, 8);
	Quaternion result1 = Quaternion::concatenate(test, xyz);

	result1.print();
	Quaternion first = Quaternion(-.75, -.02, -.73, .24);
	Quaternion second = Quaternion(.23, .1, .8, .22);
	Quaternion result2 = Quaternion::lerp(first, second, .25f);
	result2.print();

	Matrix result = Quaternion::convertToMatrix(first);
	Quaternion multResult = Quaternion::multVec(second, Vector3(2, 3, 1));
	multResult.print();
	system("pause");
	return 0;
}