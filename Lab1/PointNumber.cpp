#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

class PointNumber {
private:
	float num;
	vector<string> direct_mas;
	vector<int> ieee754_mas;


public:
	PointNumber(float num) :
		num(num) {}

	float get_num() {
		return num;
	}

	//Перевод в прямой код
	void transfer_direct() {
		int counter = 0;
		int first = static_cast<int>(num);
		cout << first << endl;
		float second = abs(num) - abs(static_cast<int>(num));
		direct_mas.clear();
		if (first > 0) {
			direct_mas.push_back("0");
		}
		else {
			direct_mas.push_back("1");
		}

		while (first != 0) {
			direct_mas.push_back(to_string(abs(first % 2)));
			first /= 2;
		}
		reverse(direct_mas.begin() + 1, direct_mas.end());
		direct_mas.push_back(".");

		while ((second != 0) && (direct_mas.size() < 26)) {
			second = second * 2;
			first = static_cast<int>(second);
			direct_mas.push_back(to_string(first));
			second = second - static_cast<int>(second);
			counter++;
		}
	}

	vector<string> get_direct_mas() {
		return direct_mas;
	}


	void print_direct_mas() {
		cout << "Прямой код\n";
		for (string num : direct_mas) {
			cout << num;
		}
		cout << endl;
	}

	void push_direct(string num) {
		direct_mas.push_back(num);
	}


	void reverse_direct() {
		reverse(direct_mas.begin(), direct_mas.end());
	}
};