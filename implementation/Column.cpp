#include "Column.h"


Column::Column(int v){
	for (int i = 0; i < v + 1; i++)
		groups.push_back(Group(i));
}

vector<Group>* Column::getGroups() {
	return &groups;
}

vector<Group> Column::getGroupsWithTerms() {
	vector<Group> groupsWithTerms;

	for (size_t i = 0; i < groups.size(); i++) {
		if (groups.at(i).hasTerms())
			groupsWithTerms.push_back(groups.at(i));
	}
	
	return groupsWithTerms;
}


Column::~Column()
{
}
