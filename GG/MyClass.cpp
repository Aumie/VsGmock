#include "MyClass.h"

void MyClass::Increment(int byValue) {
	baseVal += byValue;
}

int MyClass::getValue()
{
	return baseVal;
}