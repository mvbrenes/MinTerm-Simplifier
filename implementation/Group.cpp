#include "Group.h"


Group::Group(int i) {
	index = i;
	bhasTerms = false;
}

int Group::getIndex() {
	return index;
}

void Group::add(Minterm* minterm) {
	terms.push_back(minterm);
	bhasTerms = true;
}

vector<Minterm*> Group::getTerms() {
	return terms;
}

bool Group::hasTerms() {
	return bhasTerms;
}

Group::~Group()
{
}
