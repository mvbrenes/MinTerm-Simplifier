#pragma once
#include <vector>
#include "Minterm.h"
using namespace std;

class Group {

public:
	Group(int i);					// Constructor assigns Group value.

	int getIndex();					// Returns the value of the group.
	void add(Minterm* minterm);		// Adds a Minterm Object to the Group.
	vector<Minterm*> getTerms();	// Returns all the terms in the Group.
	bool hasTerms();				// Checks if it contains any terms.

	virtual ~Group();				// Destructor

private:
	vector<Minterm*> terms;			// The Terms in the group.
	int index;						// The Group Number.
	bool bhasTerms;					// True if it contains terms.
};

