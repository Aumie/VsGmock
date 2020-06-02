#include "Stack.h"

int Stack::pop() {
	if (!vstack.empty()) {
		int value = vstack.back();
		vstack.pop_back();
		return value;
	}
	return -1;

}