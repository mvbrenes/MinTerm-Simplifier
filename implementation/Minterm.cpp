#include "Minterm.h"

Minterm::Minterm(string minterm) {
	binary = minterm;
	check = false;

	assignGroup();
}

void Minterm::checkOff() {
	check = true;
}

bool Minterm::isChecked() {
	return check;
}

void Minterm::storeValue(vector<int> n) {
	for (int number: n)
		value.push_back(number);
}

void Minterm::storeValue(int n) {
	value.push_back(n);
}

vector<int> Minterm::getValues() {
	return value;
}

int Minterm::getIndex() {
	return groupIndex;
}

string Minterm::getBinary() {
	return binary;
}

void Minterm::assignGroup() {
	int count = 0;
	for(size_t i = 0; i < binary.length(); i++)
		if (binary.at(i) == '1')
			count++;
	groupIndex = count;
}


Minterm::~Minterm()
{
}
