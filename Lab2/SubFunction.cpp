#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

class SubFunction {
private:
	string subfunc;
	string main_sign;
	string left_subfunc;
	string right_subfunc;
	int logic_num = 0;
	//vector<SubFunction*> list_subfunc;

public:
	SubFunction() : subfunc(""), main_sign(""), left_subfunc(""), right_subfunc("") {}

	SubFunction(string subfunc, string main_sign = "", string left_subfunc="", string right_subfunc = "") :
		subfunc(subfunc),
		main_sign(main_sign),
		left_subfunc(left_subfunc),
		right_subfunc(right_subfunc) {}

	string get_subfunc() {
		return subfunc;
	}

	string get_main_sign() {
		return main_sign;
	}

	string get_left_subfunc() {
		return left_subfunc;
	}

	string get_right_subfunc() {
		return right_subfunc;
	}

	int get_logic_num() {
		return logic_num;
	}

	bool one_logic_num() {
		logic_num = 1;
		return true;
	}

	bool zero_logic_num() {
		logic_num = 0;
		return true;
	}
};