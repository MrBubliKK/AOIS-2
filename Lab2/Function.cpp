#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include "SubFunction.cpp"
using namespace std;

class Function {
private:
	string func = "";
	map<int, string> dict_signs; //int - позиция знака, string - сам знак
	vector<SubFunction> list_subfunc; //Список подфункций, на которые разбивается функция
	vector<vector<SubFunction>> matrix_subfunc;


public:
	Function(string func, int n) :
		func(func),
		matrix_subfunc(1, vector<SubFunction>(n)) {}
	
	//Находит все знаки в функции
	bool find_all_signs() {
		for (int i = 0; i < func.size(); i++) {
			if ((func[i] == '+') || (func[i] == '*') || (func[i] == '\'') || (func[i] == '>') || (func[i] == '~')) {
				dict_signs[i] = func[i];
			}
		}
		return true;
	}

	bool make_left_part_subfunc(int* left_pos, string* subfunc, string* left_part_subfunc, int* count_bracket) {
		// Проверяем на отрицание в левой части
		if (func[*left_pos] == '\'') {
			*subfunc = func[*left_pos] + *subfunc;
			*left_part_subfunc = func[*left_pos] + *left_part_subfunc;
			(*left_pos)--;
		}
		// Создаем левую часть подфункции
		if (func[*left_pos] == ')') {
			*subfunc = string(1, func[*left_pos]) + *subfunc;
			*left_part_subfunc = string(1, func[*left_pos]) + *left_part_subfunc;
			(*left_pos)--;
			(*count_bracket)++;
			while (*count_bracket > 0) {
				*subfunc = string(1, func[*left_pos]) + *subfunc;
				*left_part_subfunc = string(1, func[*left_pos]) + *left_part_subfunc;
				if (func[*left_pos] == '(') {
					(*count_bracket)--;
				}
				if (func[*left_pos] == ')') {
					(*count_bracket)++;
				}
				(*left_pos)--;
			}
		}
		else {
			*subfunc = string(1, func[*left_pos]) + *subfunc;
			*left_part_subfunc = string(1, func[*left_pos]) + *left_part_subfunc;
			*subfunc = string(1, func[--(*left_pos)]) + *subfunc;
			*left_part_subfunc = string(1, func[*left_pos]) + *left_part_subfunc;
			*subfunc = "(" + *subfunc;
			*left_part_subfunc = "(" + *left_part_subfunc;
		}

		if (((*left_part_subfunc).size() > 4) && ((*left_part_subfunc)[(*left_part_subfunc).size() - 1] == '\'')) {
			*left_part_subfunc = "(" + * left_part_subfunc;
			*left_part_subfunc += ")";

		}
		return true;
	}

	bool make_right_part_subfunc(int* right_pos, string* subfunc, string* right_part_subfunc, int* count_bracket) {
		*count_bracket = 0;

		if (func[*right_pos] == '(') {
			*subfunc = *subfunc + string(1, func[*right_pos]);
			*right_part_subfunc = *right_part_subfunc + string(1, func[*right_pos]);
			(*count_bracket)++;
			(*right_pos)++;

			while (*count_bracket > 0) {
				*subfunc = *subfunc + string(1, func[*right_pos]);
				*right_part_subfunc = *right_part_subfunc + string(1, func[*right_pos]);

				if (func[*right_pos] == ')') {
					(*count_bracket)--;
				}
				if (func[*right_pos] == '(') {
					(*count_bracket)++;
				}
				(*right_pos)++;
			}

			if (func[*right_pos] == '\'') {
				*subfunc = *subfunc + func[*right_pos];
				*right_part_subfunc = *right_part_subfunc + func[*right_pos];
			}
		}
		else {
			*subfunc = *subfunc + string(1, func[*right_pos]);
			*right_part_subfunc = *right_part_subfunc + string(1, func[*right_pos]);
			*subfunc = *subfunc + string(1, func[++(*right_pos)]);
			*right_part_subfunc = *right_part_subfunc + string(1, func[*right_pos]);
			(*right_pos)++;

			if (func[*right_pos] == '\'') {
				*subfunc = *subfunc + func[*right_pos];
				*right_part_subfunc = *right_part_subfunc + func[*right_pos];
			}

			*subfunc = *subfunc + ")";
			*right_part_subfunc = *right_part_subfunc + ")";
		}

		if (((*right_part_subfunc).size() > 4) && ((*right_part_subfunc)[(*right_part_subfunc).size() - 1] == '\'')) {
			*right_part_subfunc = "(" + *right_part_subfunc;
			*right_part_subfunc += ")";

		}

		return true;
	}

	bool align_brackets(string* subfunc, int* open_num, int* close_num) {
		for (int i = 0; i < (*subfunc).size(); i++) {
			if ((*subfunc)[i] == '(') {
				(*open_num)++;
			}
			else if ((*subfunc)[i] == ')') {
				(*close_num)++;
			}
		}

		while (*close_num != *open_num) {
			if (*close_num < *open_num) {
				(*subfunc) += ")";
				(*close_num)++;
			}
			else {
				(*subfunc) = "(" + (*subfunc);
				(*open_num)++;
			}
		}

		return true;
	}

	bool make_additional_brackets(string* subfunc, string* left_part_subfunc, string* right_part_subfunc, int* left_open_close_num, int* right_open_close_num) {
		for (int i = 0; i < (*left_part_subfunc).size(); i++) {
			if (((*left_part_subfunc)[i] == '(') || ((*left_part_subfunc)[i] == ')')) {
				(*left_open_close_num)++;
			}
		}

		for (int i = 0; i < (*right_part_subfunc).size(); i++) {
			if (((*right_part_subfunc)[i] == '(') || ((*right_part_subfunc)[i] == ')')) {
				(*right_open_close_num)++;
			}
		}

		if ((*right_open_close_num >= 2) && (*left_open_close_num >= 2)) {
			*subfunc = "(" + *subfunc + ")";
		}

		return true;
	}

	bool make_denial_subfunc(int* left_pos, int* count_bracket, string* subfunc, string* left_part_subfunc) {
		if (func[*left_pos] == ')') {
			(*count_bracket)++;
			*subfunc = func[*left_pos] + *subfunc;
			*left_part_subfunc = func[*left_pos] + *left_part_subfunc;
			(*left_pos)--;
			while (*count_bracket > 0) {
				*subfunc = func[*left_pos] + *subfunc;
				*left_part_subfunc = func[*left_pos] + *left_part_subfunc;
				if (func[*left_pos] == '(') {
					(*count_bracket)--;
				}
				if (func[*left_pos] == ')') {
					(*count_bracket)++;
				}
				(*left_pos)--;
			}
		}
		else {
			*subfunc = func[*left_pos] + *subfunc; // Преобразуем символ в строку
			*left_part_subfunc = func[*left_pos] + *left_part_subfunc;
			*subfunc = func[--(*left_pos)] + *subfunc; // Преобразуем символ в строку
			*left_part_subfunc = func[*left_pos] + *left_part_subfunc;
		}
		return true;
	}

	//Находим подфункцию, опираясь на основной знак
	bool find_subfunc_on_sign(int pos, string sign) {
		string left_part_subfunc = "";
		string right_part_subfunc = "";
		string subfunc;
		subfunc = sign;
		if ((sign == "+") || (sign == "*") || (sign == ">") || (sign == "~")) {
			int count_bracket = 0;
			int left_pos = pos - 1;
			int right_pos = pos + 1;

			//Создаем левую часть подфункции
			make_left_part_subfunc(&left_pos, &subfunc, &left_part_subfunc, &count_bracket);

			//Создаем правую часть подфункции
			make_right_part_subfunc(&right_pos, &subfunc, &right_part_subfunc, &count_bracket);

			int open_num = 0;
			int close_num = 0;
			//Выравниваем скобки в подфункции
			align_brackets(&subfunc, &open_num, &close_num);

			int left_open_close_num = 0;
			int right_open_close_num = 0;

			//Добавляем дополнительные скобки, если надо
			make_additional_brackets(&subfunc, &left_part_subfunc, &right_part_subfunc, &left_open_close_num, &right_open_close_num);

			list_subfunc.push_back(SubFunction(subfunc, sign, left_part_subfunc, right_part_subfunc));
			return true;
		}
		else {
			int left_pos = pos-1;
			int count_bracket = 0;
			//Если знак отрицания
			make_denial_subfunc(&left_pos, &count_bracket, &subfunc, &left_part_subfunc);
			if (subfunc.size() > 3) {
				subfunc = "(" + subfunc + ")";
			}


			list_subfunc.push_back(SubFunction(subfunc, sign, left_part_subfunc, right_part_subfunc));
			return true;
		}
	}

	//Для каждого знака делает его подфункцию
	bool find_all_subfuncs(int n) {
		for (int i = 0; i < n; i++) {
			string name = "x" + to_string(i + 1);
			list_subfunc.push_back(SubFunction(name));
		}
		
		for (auto it = dict_signs.begin(); it != dict_signs.end(); ++it) {
			find_subfunc_on_sign(it->first, it->second);
		}

		std::sort(list_subfunc.begin(), list_subfunc.end(),
			[](SubFunction& a, SubFunction& b) {
				return a.get_subfunc().length() < b.get_subfunc().length();
			}
		);
		return true;
	}

	//Обычный вывод подфункций
	bool print_all_subfuncs() {
		for (int i = 0; i < list_subfunc.size(); i++) {
			cout << list_subfunc[i].get_subfunc() << endl;
		}
		return true;
	}

	//Вывод всех подфункций с ее левой и правой частью
	bool print_subfuncs_with_parts() {
		for (int i = 0; i < list_subfunc.size(); i++) {
			cout << list_subfunc[i].get_subfunc() << endl;
			cout << "Левая часть: " << list_subfunc[i].get_left_subfunc() << endl;
			cout << "Правая часть: " << list_subfunc[i].get_right_subfunc() << endl;
			cout << "---------\n";
		}
		return true;
	}

	string transfer_10_to_2(int temp_decimal_number) {
		int decimal_number = temp_decimal_number;
		string binary_number = "";

		while (decimal_number != 0) {
			binary_number += to_string(abs(decimal_number % 2));
			decimal_number /= 2;
		}
		reverse(binary_number.begin(), binary_number.end());
		return binary_number;
	}

	int transfer_2_to_10(std::string temp_binary_number) {
		int decimal_number = 0;
		string binary_number = temp_binary_number;
		reverse(binary_number.begin(), binary_number.end());


		for (int i = 0; i < binary_number.size(); i++) {
			decimal_number += (binary_number[i] - '0') * pow(2, i);
		}

		return decimal_number;
	}

	bool add_in_matrix_all_subfuncs(int n) {
		for (int i = 0; i < matrix_subfunc.size(); i++) {
			for (int j = n; j < list_subfunc.size(); j++) {
				matrix_subfunc[i].push_back(list_subfunc[j]);
			}
		}
		return true;
	}

	//Прокидываю в матрицы переменные со знаками для всех вариантов
	bool fill_little_subfunc(int n) {
		string binary_num = "";
		int decimal_num = 0;
		int temp_decimal_number = 0;
		string temp_binary_number;

		for (int i = 0; i < n; i++) {
			binary_num += "1";
		}

		for (int i = 0; i < n; i++) {
			string name_func = "x" + to_string(i + 1);
			matrix_subfunc[0][i] = SubFunction(name_func);
		}

		decimal_num = transfer_2_to_10(binary_num);

		for (int i = 1; i < decimal_num+1; i++) {
			vector<SubFunction> new_subfunc_vector;
			matrix_subfunc.push_back(new_subfunc_vector);
			temp_binary_number = transfer_10_to_2(i);

			while (temp_binary_number.size() < n) {
				temp_binary_number = "0" + temp_binary_number;
			}

			for (int j = 0; j < temp_binary_number.size(); j++) {
				string name_func = "x" + to_string(j+1);
				matrix_subfunc[i].push_back(SubFunction(name_func));

				if (temp_binary_number[j] == '0') {
					matrix_subfunc[i][j].zero_logic_num();
				}

				else {
					matrix_subfunc[i][j].one_logic_num();
				}
			}
		}
		return true;
	}

	//Находит индекс подфункции
	int find_index_subfunc(string subfunc) {
		for (int i = 0; i < list_subfunc.size(); i++) {
			if (subfunc == list_subfunc[i].get_subfunc()) {
				return i;
			}
		}
		return -1;
	}

	bool make_4_size_subfunc(string* left_subfunc, int i, int j) {
		if ((matrix_subfunc[i][j].get_left_subfunc())[0] == '(') {
			*left_subfunc += (matrix_subfunc[i][j].get_left_subfunc())[1];
			*left_subfunc += (matrix_subfunc[i][j].get_left_subfunc())[2];
			*left_subfunc += (matrix_subfunc[i][j].get_left_subfunc())[3];
		}
		else {
			*left_subfunc += (matrix_subfunc[i][j].get_left_subfunc())[0];
			*left_subfunc += (matrix_subfunc[i][j].get_left_subfunc())[1];
			*left_subfunc += (matrix_subfunc[i][j].get_left_subfunc())[2];
		}
		return true;
	}

	bool find_denial_subfunc(string* left_subfunc, int i, int j) {
		if ((matrix_subfunc[i][j].get_left_subfunc()[matrix_subfunc[i][j].get_left_subfunc().size() - 1] != ')')) {
			*left_subfunc += matrix_subfunc[i][j].get_left_subfunc()[matrix_subfunc[i][j].get_left_subfunc().size() - 2];
			*left_subfunc += matrix_subfunc[i][j].get_left_subfunc()[matrix_subfunc[i][j].get_left_subfunc().size() - 1];
		}
		else {
			*left_subfunc = matrix_subfunc[i][j].get_left_subfunc();
		}
		return true;
	}

	bool find_left_subfunc(string* left_subfunc, int i, int j) {
		if (matrix_subfunc[i][j].get_left_subfunc().size() == 3) {
			*left_subfunc += matrix_subfunc[i][j].get_left_subfunc()[1];
			*left_subfunc += matrix_subfunc[i][j].get_left_subfunc()[2];
		}
		else if (matrix_subfunc[i][j].get_left_subfunc().size() == 4) {
			make_4_size_subfunc(left_subfunc, i, j);
		}
		// Если отрицание
		else if (matrix_subfunc[i][j].get_main_sign() == "'") {
			find_denial_subfunc(left_subfunc, i, j);
		}
		// Иначе просто берем подфункцию
		else {
			*left_subfunc = matrix_subfunc[i][j].get_left_subfunc();
		}
		return true;
	}

	bool find_right_part(string* right_subfunc, int i, int j) {
		// Если переменная, берем конкретно ее
		if (matrix_subfunc[i][j].get_right_subfunc().size() == 3) {
			*right_subfunc += matrix_subfunc[i][j].get_right_subfunc()[0];
			*right_subfunc += matrix_subfunc[i][j].get_right_subfunc()[1];
		}
		else if (matrix_subfunc[i][j].get_right_subfunc().size() == 4) {
			*right_subfunc += matrix_subfunc[i][j].get_right_subfunc()[0];
			*right_subfunc += matrix_subfunc[i][j].get_right_subfunc()[1];
			*right_subfunc += matrix_subfunc[i][j].get_right_subfunc()[2];
		}
		else if ((matrix_subfunc[i][j].get_right_subfunc().size() != 0) && (matrix_subfunc[i][j].get_right_subfunc()[matrix_subfunc[i][j].get_right_subfunc().size() - 1] == '\'')) {
			*right_subfunc += "(";
			*right_subfunc += matrix_subfunc[i][j].get_right_subfunc();
			*right_subfunc += ")";
		}
		// Иначе оставляем как есть
		else {
			*right_subfunc += matrix_subfunc[i][j].get_right_subfunc();
		}
		return true;
	}

	bool fill_logic_number_in_subfunc(string* left_subfunc, string* right_subfunc, int i, int j) {
		if (matrix_subfunc[i][j].get_main_sign() == "'") {
			if (matrix_subfunc[i][find_index_subfunc(*left_subfunc)].get_logic_num() == 0) {
				matrix_subfunc[i][j].one_logic_num();
			}
			else {
				matrix_subfunc[i][j].zero_logic_num();
			}
		}
		else if (matrix_subfunc[i][j].get_main_sign() == "+") {
			if ((matrix_subfunc[i][find_index_subfunc(*left_subfunc)].get_logic_num() == 0)
				&& (matrix_subfunc[i][find_index_subfunc(*right_subfunc)].get_logic_num() == 0)) {
				matrix_subfunc[i][j].zero_logic_num();
			}
			else {
				matrix_subfunc[i][j].one_logic_num();
			}
		}
		else if (matrix_subfunc[i][j].get_main_sign() == "*") {
			if ((matrix_subfunc[i][find_index_subfunc(*left_subfunc)].get_logic_num() == 1)
				&& (matrix_subfunc[i][find_index_subfunc(*right_subfunc)].get_logic_num() == 1)) {
				matrix_subfunc[i][j].one_logic_num();
			}
			else {
				matrix_subfunc[i][j].zero_logic_num();
			}
		}
		else if (matrix_subfunc[i][j].get_main_sign() == ">") {
			if ((matrix_subfunc[i][find_index_subfunc(*left_subfunc)].get_logic_num() == 1)
				&& (matrix_subfunc[i][find_index_subfunc(*right_subfunc)].get_logic_num() == 0)) {
				matrix_subfunc[i][j].zero_logic_num();
			}
			else {
				matrix_subfunc[i][j].one_logic_num();
			}
		}
		else if (matrix_subfunc[i][j].get_main_sign() == "~") {
			if (((matrix_subfunc[i][find_index_subfunc(*left_subfunc)].get_logic_num() == 1)
				&& (matrix_subfunc[i][find_index_subfunc(*right_subfunc)].get_logic_num() == 1)) ||
				((matrix_subfunc[i][find_index_subfunc(*left_subfunc)].get_logic_num() == 0)
					&& (matrix_subfunc[i][find_index_subfunc(*right_subfunc)].get_logic_num() == 0))) {
				matrix_subfunc[i][j].one_logic_num();
			}
			else {
				matrix_subfunc[i][j].zero_logic_num();
			}
		}
		else {
			cout << "Знак некорректный. Разобраться\n";
			return false;
		}
		return true;
	}

	//Вычисляет знаки подфункций
	bool fill_all_subfuncs(int n) {
		for (int i = 0; i < matrix_subfunc.size(); i++) {
			for (int j = n; j < list_subfunc.size(); j++) {
				string left_subfunc = "";
				string right_subfunc = "";

				//Выделяем корректную левую подфункцию
				find_left_subfunc(&left_subfunc, i, j);


				//Выделяем корректную правую подфункцию
				find_right_part(&right_subfunc, i, j);

				//Составляем знак
				fill_logic_number_in_subfunc(&left_subfunc, &right_subfunc, i, j);
			}
		}
		return true;
	}

	bool print_matrix() {
		for (int i = 0; i < matrix_subfunc.size(); i++) {
			for (int j = 0; j < matrix_subfunc[i].size(); j++) {
				cout << matrix_subfunc[i][j].get_logic_num() << " ";
			}
			cout << endl;
		}
		return true;
	}

	bool make_sign_in_sdnf(string* result, int i, int j, int n) {
		if (matrix_subfunc[i][j].get_logic_num() == 1) {
			*result += matrix_subfunc[i][j].get_subfunc();
		}
		else {
			*result += matrix_subfunc[i][j].get_subfunc();
			*result += "'";
		}
		if (j < n - 1) {
			*result += "*";
		}
		return true;
	}

	bool print_sdnf(int n) {
		cout << "Индексный вывод СДНФ:\n";
		string result = "";
		for (int i = 0; i < matrix_subfunc.size(); i++) {
			if (matrix_subfunc[i][matrix_subfunc[i].size() - 1].get_logic_num() == 1) {
				result += "(";
				for (int j = 0; j < n; j++) {
					make_sign_in_sdnf(&result, i, j, n);
				}
				result += ")+";
			}
		}
		result.pop_back();
		cout << result << endl;
		return true;
	}

	bool make_sign_in_sknf(string* result, int i, int j, int n) {
		if (matrix_subfunc[i][j].get_logic_num() == 0) {
			*result += matrix_subfunc[i][j].get_subfunc();
		}
		else {
			*result += matrix_subfunc[i][j].get_subfunc();
			*result += "'";
		}
		if (j < n - 1) {
			*result += "+";
		}
		return true;
	}


	bool print_sknf(int n) {
		cout << "Индексный метод СКНФ:\n";
		string result = "";
		for (int i = 0; i < matrix_subfunc.size(); i++) {
			if (matrix_subfunc[i][matrix_subfunc[i].size() - 1].get_logic_num() == 0) {
				result += "(";
				for (int j = 0; j < n; j++) {
					make_sign_in_sknf(&result, i, j, n);
				}
				result += ")*";
			}
		}
		result.pop_back();
		cout << result << endl;
		return true;
	}


	bool print_list_func() {
		cout << "Вывод списка подфункций:\n";
		for (int i = 0; i < list_subfunc.size(); i++) {
			cout << list_subfunc[i].get_subfunc() << endl;
		}
		return true;
	}

	bool print_index_form() {
		cout << endl;
		string binary_num = "";
		int decimal_num = 0;
		for (int i = 0; i < matrix_subfunc.size(); i++) {
			cout << matrix_subfunc[i][matrix_subfunc[i].size() - 1].get_logic_num();
			binary_num += to_string(matrix_subfunc[i][matrix_subfunc[i].size()-1].get_logic_num());
		}
		decimal_num = transfer_2_to_10(binary_num);
		cout << " = " << decimal_num;
		return true;
	}


};