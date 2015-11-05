#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <math.h>
#include "Minterm.h"
#include "Group.h"
#include "Column.h"
#include "Chart.h"
using namespace std;
string toBinary(int value);
vector<Column*>* compareGroups(vector<Column*> *columns);
vector<Column*>* getNewColumns(vector<Column*> *columns);
int variables;
char choice;

int main() {
	cout << "-----Welcome to the QuineMcCluskey Simplifier-----\n";
	do{
		vector<Column*> *columns = new vector<Column*>;
		Chart *chart;


		cout << "\nPlease enter the number of Bits (1-26), (0 to Exit): ";

		while (!(cin >> variables)) {
			cout << "Invalid Input!" << endl;
			cout << "\nPlease enter the number of Bits (1-26), (0 to Exit): ";
			cin.clear();
			cin.ignore(10000, '\n');
		}

		// Close out if there are no variables
		if (!variables)
			return 0;

		(*columns).push_back(new Column(variables));
		chart = new Chart(variables);

		cout << "\nEnter how many Min-Terms to Simplify (Max: " << pow(2, variables) << "), (0 to Exit) : ";

		int turns;

		// Checks for valid input
		while (!(cin >> turns)) {
			cout << "Invalid Input!" << endl;
			cout << "\nEnter how many Min-Terms to Simplify (Max: " << pow(2, variables) << "), (0 to Exit) : ";
			cin.clear();
			cin.ignore(10000, '\n');
		}

		// Checks that the limit of variables is not reached.
		while (turns > pow(2, variables)) {
			cout << "\nTOO MANY VARIABLES! MAX: " << pow(2, variables) << "\nEnter again: ";
			while (!(cin >> turns)) {
				cout << "Invalid Input!" << endl;
				cout << "\nEnter how many Min-Terms to Simplify (Max: " << pow(2, variables) << "), (0 to Exit) : ";
				cin.clear();
				cin.ignore(10000, '\n');
			}
		}
		
		// Terminates program if there are no minterms
		if (turns == 0)
			return 0;

		// Set Chart Columns
		(*chart).setColumns(turns);	

		// Get Initial Terms from User
		//---------------------------------------------------------------------------------------------------------------------
		int value[100];

		cout << "\nEnter Terms from 0-" << (pow(2, variables) - 1) << " (Seperate Numbers By Spaces) : " << endl;
		for (int i = 0; i < turns; i++){
			cin >> value[i];

			// If the term reaches beyond the valid boundaries request again
			while (value[i] > (pow(2, variables) - 1)) {
				cout << "\nValue: " << value[i] << " is not a valid term." << endl;
				cout << "Enter " << turns - i << " term(s) starting at term #" << i + 1;
				cin.ignore(10000, '\n');
				cout << endl;
				cin >> value[i];
			}

			(*chart).addColumnName(value[i]);												// Set the column Name to value.
			Minterm* term = new Minterm(toBinary(value[i]));								// Create Minterm.
			(*term).storeValue(value[i]);
			cout << "MinTerm: " << (*chart).printToFormula(toBinary(value[i])) << endl;

			(*(*(*columns).back()).getGroups()).at((*term).getIndex()).add(term);			// Store to appropriate Group.
		}
		//---------------------------------------------------------------------------------------------------------------------

		do {
			columns = getNewColumns(columns);
		} while ((*(*columns).back()).getGroupsWithTerms().size() != 0);

		// Print The Minterms!
		cout << "\n\n----MinTerms----" << endl;
		int rowsForChart = 0;
		for (Column *column : (*columns))
		for (Group group : (*column).getGroupsWithTerms())
		for (Minterm* minTerm : group.getTerms())
		if (!(*minTerm).isChecked()) {
			cout << "\nMinTerm: " + (*minTerm).getBinary();
			rowsForChart++;											// Count how many minterms are left.
		}

		(*chart).setRows(rowsForChart);								// Set Rows for the Chart.

		// Add the Minterm object to the Chart
		for (Column *column : (*columns))
		for (Group group : (*column).getGroupsWithTerms())
		for (Minterm* minTerm : group.getTerms())
		if (!(*minTerm).isChecked()) {
			(*chart).addTerm(minTerm);
		}

		(*chart).printChart();
		(*chart).crossChart();

		delete chart;
		delete columns;

		cout << "\n\nAnother? (y/n)" << endl;
		if (!(cin >> choice)) {
			return 0;
		}
	} while (choice == 'y' || choice == 'Y');

	return 0;
}

/**
* turns int value into a binary string;
*
* @param value integer to convert
* @return the binary value as a string;
*/
string toBinary(int value) {
	string binary = "";
	int quotient = value / 2;
	int remainder = value % 2;
	binary = to_string(remainder);

	while (quotient != 0) {
		remainder = quotient % 2;
		quotient = quotient / 2;
		binary = to_string(remainder) + binary;
	}

	if (binary.size() < variables) {
		long zeros = variables - binary.size();
		for (int i = 0; i < zeros; i++)
			binary = "0" + binary;
	}

	return binary;
}
//------------------------------------------------------------------

/**
* Compares the groups in the column and creates a new column with all the 1
* bit flip values
*
* @param columns the current columns
* @return a new list of columns.
*/

vector<Column*>* compareGroups(vector<Column*>* columns) {
	Column *lastColumn = (*columns).back();
	(*columns).push_back(new Column(variables));

	//repeat for how many groups
	for (size_t i = 0; i < (*(*lastColumn).getGroups()).size(); i++) {
		Group *groupA = &(*(*lastColumn).getGroups()).at(i);
		Group *groupB = NULL;

		// Checks to see that it does not assign a nonexisting group.
		if (i != (*(*lastColumn).getGroups()).size() - 1){
			groupB = &(*(*lastColumn).getGroups()).at(i + 1);
		}


		if (groupA != NULL && groupB != NULL)
		for (Minterm *termA : (*groupA).getTerms())
		for (Minterm *termB : (*groupB).getTerms()){
			string newMintermBinary = "";
			int flips = 0;

			for (int x = 0; x < variables; x++) {
				if ((*termA).getBinary().at(x) == (*termB).getBinary().at(x))
					newMintermBinary = newMintermBinary + (*termA).getBinary().at(x);
				else {
					newMintermBinary = newMintermBinary + '-';
					flips++;
				}
			}

			if (flips == 1) {
				(*termA).checkOff();
				(*termB).checkOff();
				Minterm* term = new Minterm(newMintermBinary);

				(*term).storeValue((*termA).getValues());
				(*term).storeValue((*termB).getValues());
				bool isIn = false;

				// Check to see if the term is already in the column
				for (size_t z = 0; z < (*(*(*columns).back()).getGroups()).at((*term).getIndex()).getTerms().size(); z++)
				if ((*(*(*(*columns).back()).getGroups()).at((*term).getIndex()).getTerms().at(z)).getBinary().compare((*term).getBinary()) == 0)
					isIn = true;

				// If it is not, then add it.
				if (!isIn)
					(*(*(*columns).back()).getGroups()).at((*term).getIndex()).add(term);
			}
		}
	}

	return columns;
}
/**
* Helper method to create new Columns and Print them out.
*
* @param columns the current columns
* @return a new list of columns.
*/
vector<Column*>* getNewColumns(vector<Column*>* columns) {
	if ((*(*columns).back()).getGroupsWithTerms().size() != 0)
		cout << "---Column " << (*columns).size() << "---\n";

	for (Group group : (*(*(*columns).back()).getGroups()))
	for (Minterm* minterm : group.getTerms())
		cout << (*minterm).getBinary() << endl;

	columns = compareGroups(columns);

	return columns;
}