#pragma once
#include <vector>

class Stack {
	std::vector<int> vstack = {};
public:
	void push(int value) { vstack.push_back(value); }
	int pop();
	int size() { return vstack.size(); }

};
