#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>
#include <cstdlib>
using namespace std;

template <typename T>
string to_string(T value)
{
	std::ostringstream os ;
	os << value ;
	return os.str() ;
}

struct Data { string make; string model; string date; int id; int cost; int year; };
struct P { int carNum; string p = "-1"; };

unique_ptr<Data> ptr(new Data);
unique_ptr<P> priceX(new P);
unique_ptr<P> priceY(new P);

void createNewCar(int counter) {
	string fileName = "car" + to_string(counter) + ".txt";
	ofstream file;
	file.open(fileName);

	string cmake, cmodel, cdate;
	int cyear, ccost;
	cout << "enter the maker of car:";
	cin >> cmake;
	cout << "enter the model of car:";
	cin >> cmodel;
	cout << "enter the year of car:";
	cin >> cyear;
	cout << "enter the date of car:";
	cin >> cdate;
	cout << "enter the cost of car:";
	cin >> ccost;
	cout << "saving a data to file" << endl;

	file << (ptr->id = counter) << ',';
	file << (ptr->make = cmake) << ',';
	file << (ptr->model = cmodel) << ',';
	file << (ptr->year = cyear) << ',';
	file << (ptr->date = cdate) << ',';
	file << (ptr->cost = ccost);
	file.close();

	if (priceX->p == "-1") {
		priceX->carNum = counter;
		priceX->p = to_string(ccost);
	}
	else if (priceY->p == "-1") {
		priceY->carNum = counter;
		priceY->p = to_string(ccost);
	}
	else {
		priceX->p = priceY->p;
		priceX->carNum = priceY->carNum;

		priceY->p = to_string(ccost);
		priceY->carNum = counter;
	}
}

string listAllCarsHelper(string fileName) {
	ifstream file(fileName);
	string line, make, model, date, cost, year, id;

	while (getline(file, line)) {
		stringstream ss(line);
		getline(ss, id, ',');
		getline(ss, make, ',');
		getline(ss, model, ',');
		getline(ss, year, ',');
		getline(ss, date, ',');
		getline(ss, cost, ',');
		cout << id << "\t" << make << "\t" << model << "\t" << year << "\t" << date << "\t" << cost << endl;
	}
	return cost;
}

void listAllCars() {
	int i;
	string line;
	cout << "id" << "\t" << "make" << "\t" << "model" << "\t" << "year" << "\t" << "date" << "\t" << "cost" << endl;
	for (i = 1; i < 6; i++) {
		string p = to_string(i);
		string fileName = "car" + p + ".txt";
		ifstream file(fileName);
		if (file.good()) {
			string currentCost = listAllCarsHelper(fileName);
		}
	}
	cout << endl;
}

void carLoad(int carNum){
	string fileName = "car" + to_string(carNum) + ".txt";
	ifstream file(fileName);

	string line, make, model, date, cost, year, id;
	while (getline(file, line)) {
		stringstream ss(line);
		getline(ss, id, ',');
		getline(ss, make, ',');
		getline(ss, model, ',');
		getline(ss, year, ',');
		getline(ss, date, ',');
		getline(ss, cost, ',');
	}

	if (priceX->p == "-1") {
		priceX->carNum = carNum;
		priceX->p = cost;
	}
	else if (priceY->p == "-1") {
		priceY->carNum = carNum;
		priceY->p = cost;
	}
	else {
		priceX->p = priceY->p;
		priceX->carNum = priceY->carNum;

		priceY->p = cost;
		priceY->carNum = carNum;
	}
}

void changePrice() {
	int newPrice = 0;
	cin >> newPrice;
	priceY->p = to_string(newPrice);
	cout << priceY->p;
}

void saveAll(){
	string fileName1 = "car" + to_string(priceX->carNum) + ".txt";
	string fileName2 = "car" + to_string(priceY->carNum) + ".txt";

	ifstream file1(fileName1);
	string line, make, model, date, cost, year, id;
	while (getline(file1, line)) {
		stringstream ss(line);
		getline(ss, id, ',');
		getline(ss, make, ',');
		getline(ss, model, ',');
		getline(ss, year, ',');
		getline(ss, date, ',');
		getline(ss, cost, ',');
	}

	ofstream filee1;
	filee1.open(fileName1);

	filee1 << id << ',';
	filee1 << make << ',';
	filee1 << model << ',';
	filee1 << year << ',';
	filee1 << date << ',';
	filee1 << priceX->p;
	filee1.close();

	ifstream file2(fileName2);
	while (getline(file2, line)) {
		stringstream sss(line);
		getline(sss, id, ',');
		getline(sss, make, ',');
		getline(sss, model, ',');
		getline(sss, year, ',');
		getline(sss, date, ',');
		getline(sss, cost, ',');
	}

	ofstream filee2;
	filee2.open(fileName2);

	filee2 << id << ',';
	filee2 << make << ',';
	filee2 << model << ',';
	filee2 << year << ',';
	filee2 << date << ',';
	filee2 << priceY->p;
	filee2.close();
}

int main() {
	int counter = 1;
	char command;
	string mk, mdl, dt;
	cout << "Welcome to car dealership directory" << endl;
	cout << "enter command to perform action:" << endl;

	cin >> command;
	while (true) {
		switch (command) {
			case 'c': if (counter < 6) { createNewCar(counter); counter ++; };	break;

			case 'l': cout << "list of cars:" << endl;	listAllCars();	break;

			case 'p': cout << "enter price:";	changePrice();	break;

			case 's': cout << "saving data" << endl;	saveAll();	break;

			case '1': cout << "loading car 1" << endl;	carLoad(1);	break;

			case '2': cout << "loading car 2" << endl;	carLoad(2);	break;

			case '3': cout << "loading car 3" << endl;	carLoad(3);	break;

			case '4': cout << "loading car 4" << endl;	carLoad(4);	break;

			case '5': cout << "loading car 5" << endl;	carLoad(5); break;

			case 'q': cout << "existing" << endl;	exit; return 0;

			default: cout << "enter right character" << endl;
		}
		cout << endl;
		cout << "enter command to perform action:" << endl;
		cin >> command;
	}
	return 0;
}
