#pragma once
class MyClass {
	int baseVal;
public:
	MyClass(int _bv) : baseVal(_bv) {}
	void Increment(int byValue);
	int getValue();
};
