#pragma once
#include <vector>
#include "Group.h"
using namespace std;

class Column {

public:
	Column(int v);							// Creates Column

	vector<Group>* getGroups();				// Returns all the groups
	vector<Group> getGroupsWithTerms();		// Returns only groups with Terms.
	virtual ~Column();						// Destructor.

private:
	vector<Group> groups;
};

