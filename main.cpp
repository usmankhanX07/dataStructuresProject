#include<iostream>
#include "destinations.cpp"

using namespace std;
int main() {
	cout << "Welcome to the travel planner system" << endl;
	cout << "All prices are estimates in US Dollar ($)" << endl;
	AVLTree destinations;

	char letter = 'a';
	while (letter != 'M' && letter != 'L' && letter != 'H') {
		cout << "Would you like to search by [M]edian or [L]ow to high or [H]igh to low pricing" << endl;
		cin >> letter;
	}
	if (letter == 'M') {
		destinations.printDecider('A');
	}
	else if (letter == 'L') {
		destinations.printDecider('B');
	}
	else {
		destinations.printDecider('C');
	}

}
