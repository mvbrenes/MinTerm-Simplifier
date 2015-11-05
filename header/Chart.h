#pragma once

#include "Minterm.h"
#include <iostream>
using namespace std;

class Chart {

public:
	Chart(int v);							// Creates a new Chart.

	void setColumns(int c);					// Set the Columns of the chart
	void setRows(int r);					// Set the rows for the chart.
	void addColumnName(int value);			// adds the MinTerm Row Names
	void addTerm(Minterm* t);				// Adds a minterm into the chart
	void crossChart();						// Cross out the chart
	void printChart();						// Prints out the chart
	virtual ~Chart();
	string printToFormula(string binary);	// Prints the minterms as a Formula

private:
	vector<vector<char>*> chart;			// Two Dimensional Vector of Charaters represents Chart
	int columns, rows, variables;			// Holds the number of rows and columns, as well as bit variables
	int rowCounter;							// Used for marking the next row in which to add a Term (see addTerm menthod)
	vector<Minterm*> terms;					// Holds a referece to all the terms used in the chart
	vector<int> addresses;					// Vector holds the name of the Columns in the chart
	vector<bool> covered;					// Marks which rows are to be included in the final formula

	int countRowXs(int r);					// Counts Xs in a row
	int countColumnXs(int c);				// Count  Xs in a column
	void clearSection(int section);			// Clears a section
	bool chartIsNotEmpty();					// Checks to see if the chart is empty
	int getKilledXs(int row);				// Count how many Xs will be cleared by that row.
	int getPrimeImplicants(int row);		// Count how many Prime Implicants per row;
};

