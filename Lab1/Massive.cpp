#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

class Massive {
private:
	int num;
	vector<int> direct_mas;
	vector<int> additional_mas;
	vector<int> reverse_mas;
	vector<int> transfer_mas;
	vector<int> direct_mas_op;
	vector<int> additional_mas_op;
	vector<int> reverse_mas_op;

public:
	Massive(int num) :
		num(num) {}

	int get_num() {
		return num;
	}

	//ОБЫЧНЫЙ ПЕРЕВОД В КОД
	//Перевод в прямой код
	void transfer_direct(int input) {
		direct_mas.clear();
		if (input > 0) {
			direct_mas.push_back(0);
		}
		else {
			direct_mas.push_back(1);
		}

		while (input != 0) {
			direct_mas.push_back(abs(input % 2));
			input /= 2;
		}
		reverse(direct_mas.begin() + 1, direct_mas.end());
	}

	//Перевод в обратный код
	void transfer_reverse() {
		reverse_mas.clear();
		reverse_mas.push_back(direct_mas[0]);
		for (int i = 1; i < direct_mas.size(); i++) {
			if (direct_mas[i] == 0) {
				reverse_mas.push_back(1);
			}
			else {
				reverse_mas.push_back(0);
			}
		}
	}

	//Перевод в дополнительный код
	void transfer_additional() {
		additional_mas.clear();
		bool flag = false;
		for (int i = reverse_mas.size() - 1; i >= 0; i--) {
			if (flag) {
				additional_mas.push_back(reverse_mas[i]);
			}
			else {
				if (reverse_mas[i] == 1) {
					additional_mas.push_back(0);
				}
				else {
					additional_mas.push_back(1);
					flag = true;
				}
			}
		}
		reverse(additional_mas.begin(), additional_mas.end());
	}

	//ПЕРЕВОД ДЛЯ ВЫЧИСЛЕНИЙ
	void transfer_direct_op(int temp_num) {
		direct_mas_op.clear();
		direct_mas_op.push_back(1);
		while (temp_num != 0) {
			direct_mas_op.push_back(abs(temp_num % 2));
			temp_num /= 2;
		}
		reverse(direct_mas_op.begin() + 1, direct_mas_op.end());
		while (direct_mas_op.size() < 8) {
			direct_mas_op.insert(direct_mas_op.begin() + 1, 0);
		}
	}

	void transfer_reverse_op() {
		reverse_mas_op.clear();
		reverse_mas_op.push_back(1);
		for (int i = 1; i < direct_mas_op.size(); i++) {
			if (direct_mas_op[i] == 1) {
				reverse_mas_op.push_back(0);
			}
			else {
				reverse_mas_op.push_back(1);
			}
		}
	}

	void transfer_additional_op() {
		additional_mas_op.clear();
		bool flag = false;
		for (int i = reverse_mas_op.size() - 1; i >= 0; i--) {
			if (flag) {
				additional_mas_op.push_back(reverse_mas_op[i]);
			}
			else {
				if (reverse_mas_op[i] == 1) {
					additional_mas_op.push_back(0);
				}
				else {
					additional_mas_op.push_back(1);
					flag = true;
				}
			}
		}
		reverse(additional_mas_op.begin(), additional_mas_op.end());

	}

	//Функиция для массива операций
	void make_transfer_number() {
		transfer_mas.clear();
		if (num > 0) {
			for (int num : direct_mas) {
				transfer_mas.push_back(num);
			}
			while (transfer_mas.size() < 8) {
				transfer_mas.insert(transfer_mas.begin(), 0);
			}
		}
		else {
			transfer_direct_op(abs(num));
			transfer_reverse_op();
			transfer_additional_op();
			for (int num : additional_mas_op) {
				transfer_mas.push_back(num);
			}
		}
	}

	vector<int> get_transfer_mas() {
		return transfer_mas;
	}

	vector<int> get_direct_mas() {
		return direct_mas;
	}

	vector<int> get_additional_mas() {
		return additional_mas;
	}

	vector<int> get_reverse_mas() {
		return reverse_mas;
	}

	void print_transfer_mas() {
		cout << "Трансформированный код:\n";
		for (int num : transfer_mas) {
			cout << num;
		}
		cout << endl;
	}

	void print_direct_mas() {
		cout << "Прямой код\n";
		for (int num : direct_mas) {
			cout << num;
		}
		cout << endl;
	}

	void print_reverse_mas() {
		cout << "Обратный код\n";
		for (int num : reverse_mas) {
			cout << num;
		}
		cout << endl;
	}

	void print_additional_mas() {
		cout << "Дополнительный код\n";
		for (int num : additional_mas) {
			cout << num;
		}
		cout << endl;
	}

	void push_direct(int num) {
		direct_mas.push_back(num);
	}

	void push_reverse(int num) {
		reverse_mas.push_back(num);
	}

	void push_additional(int num) {
		additional_mas.push_back(num);
	}

	void reverse_direct() {
		reverse(direct_mas.begin(), direct_mas.end());
	}

	void reverse_reverse() {
		reverse(reverse_mas.begin(), reverse_mas.end());
	}

	void reverse_additional() {
		reverse(additional_mas.begin(), additional_mas.end());
	}

	void reverse_transfer() {
		reverse(transfer_mas.begin(), transfer_mas.end());
	}

};