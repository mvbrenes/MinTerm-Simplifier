#pragma once
#include <vector>
#include <string>
using namespace std;

class Minterm {

public:
	Minterm(string minTerm);		// Assigns Binary Value when created

	void checkOff();				// Makes Term checked off.
	bool isChecked();				// Checks if term is checked.
	void storeValue(vector<int> n);	// Stores multiple values to the term.
	void storeValue(int n);			// Stores a value to the term.
	vector<int> getValues();		// Returns the values of the term.
	int getIndex();					// Returns which Group the Termn belongs in.
	string getBinary();				// Returns the binary value of th term.
	virtual ~Minterm();				// Destructor

private:
	vector<int> value;				// The Integer values of the term.
	int groupIndex;					// The Group # it belongs in.
	string binary;					// Binary value as a string.
	bool check;						// Boolean value for term.

	void assignGroup();				// Helping function to assign group.

};

