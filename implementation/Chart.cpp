#include "Chart.h"

Chart::Chart(int v) {
	variables = v;
	rowCounter = 0;
	columns = 0;
	rows = 0;
}

void Chart::setColumns(int c) {
	columns = c;

	for (int i = 0; i < c; i++)
		addresses.push_back(-1);
	if (rows != 0) {

		for (int i = 0; i < rows; i++)
			chart.push_back(new vector<char>);

		for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			(*chart[i]).push_back(' ');
	}
}

void Chart::setRows(int r) {
	rows = r;

	for (int i = 0; i < r; i++)
		covered.push_back(false);

	if (columns != 0) {

		for (int i = 0; i < rows; i++)
			chart.push_back(new vector<char>);

		for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			(*chart[i]).push_back(' ');

	}
}

void Chart::addColumnName(int value) {
	for (size_t i = 0; i < addresses.size(); i++)
		if (addresses[i] == -1) {
			addresses[i] = value;
			return;
		}
}

void Chart::addTerm(Minterm* t) {
	terms.push_back(t);

	vector<int> values = (*terms.back()).getValues();

	for (size_t i = 0; i < values.size(); i++) {
		for (size_t j = 0; j < addresses.size(); j++) {
			if (values[i] == addresses[j])
				(*chart[rowCounter])[j] = 'X';
		}
	}
	rowCounter++;
}

void Chart::crossChart() {
	int max;
	int cross;
	
	do {
		max = -1;
		cross = -1;
		int XsKilled[2];

		for (int r = 0; r < rows; r++) {
			if (max < countRowXs(r)) {
				cross = r;
				max = countRowXs(r);
			} else if (max == countRowXs(r)) {
				// Get Prime Implicants for each row
				XsKilled[0] = getPrimeImplicants(cross);
				XsKilled[1] = getPrimeImplicants(r);
				
				if (XsKilled[0] < XsKilled[1])
					cross = r;
				// If both rows have the same amount of Prime Implicants
				// then cross out row that gets rid of the most Xs
				if (XsKilled[0] == XsKilled[1]) {
					XsKilled[0] = getKilledXs(cross);
					XsKilled[1] = getKilledXs(r);

					if (XsKilled[0] < XsKilled[1])
						cross = r;
				}
			}

		}
		//Safe Check
		if (cross != -1) {
		covered[cross] = true;
		clearSection(cross);
		printChart();
		}

	} while (chartIsNotEmpty());

	//----------------------------------Print the formula----------------------------------------------//
	string formula = "";
	cout << endl;

	for (size_t i = 0; i < covered.size(); i++){
		if (covered[i]){
			if (formula.compare("") == 0)
				formula = printToFormula((*terms[i]).getBinary());
			else
				formula = formula + " + " + printToFormula((*terms[i]).getBinary());
		}
	}

	cout << "F(";
	for (int i = 0; i < variables; i++){
		if (!i)
			cout << (char)(i + 97);
		else
			cout << "," << (char)(i + 97);
	}
	cout << ") = " + formula;
	//-------------------------------------------------------------------------------------------------//
}

void Chart::printChart() {
	cout << "\n\n----Chart----\n";
	for (size_t i = 0; i < addresses.size(); i++)
		cout << addresses[i] << " ";
	for (int r = 0; r < rows; r++) {
		cout << endl;
		for (int c = 0; c < columns; c++)
			cout << (*chart[r])[c] << " ";
	}
}

int Chart::countRowXs(int r) {
	int count = 0;
	for (int c = 0; c < columns; c++)
	if ((*chart[r])[c] == 'X')
		count++;
	return count;
}

int Chart::countColumnXs(int c) {
	int count = 0;
	for (int r = 0; r < rows; r++)
	if ((*chart[r])[c] == 'X')
		count++;
	return count;
}

void Chart::clearSection(int section) {
	for (int c = 0; c < columns; c++) {
		if ((*chart[section])[c] == 'X')
		for (int r = 0; r < rows; r++)
			(*chart[r])[c] = ' ';
	}
}

bool Chart::chartIsNotEmpty() {
	bool notEmpty = false;

	for (int c = 0; c < columns; c++)
	for (int r = 0; r < rows; r++)
	if ((*chart[r])[c] == 'X')
		notEmpty = true;
	return notEmpty;
}

string Chart::printToFormula(string binary) {
	string formula = "";
	for (int i = 0; i < variables; i++) {

		if (binary.at(i) == '1')
			formula = formula + (char)(i+97);
		else if (binary.at(i) == '0')
			formula = formula + (char)(i+97) + "'";
		
	}
	return formula;
}

int Chart::getKilledXs(int row) {
	int count = 0;

	for (int c = 0; c < columns; c++)
		if ((*chart[row])[c] == 'X')
			for (int r = 0; r < rows; r++)
				if ((*chart[r])[c] == 'X')
					count++;

	return count;
}

int Chart::getPrimeImplicants(int row) {
	int count = 0;

	for (int c = 0; c < columns; c++)
		if ((*chart[row])[c] == 'X')
			if (countColumnXs(c) == 1)
				count++;

	return count;
}
Chart::~Chart()
{
}
