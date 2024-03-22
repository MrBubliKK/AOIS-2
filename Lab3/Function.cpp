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

	//Третья лаба
	vector<vector<int>> list_delete_elements_sdnf; //Список для проверки, какие элементы уже использовались
	vector<vector<int>> list_elements_sdnf; //Рабочий вектор сднф
	vector<vector<int>> list_delete_elements_sknf;
	vector<vector<int>> list_elements_sknf;


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

	vector<vector<int>> get_list_elements_sdnf() {
		return list_elements_sdnf;
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
		int ind = 0;
		cout << "Индексный вывод СДНФ:\n";
		for (int i = 0; i < matrix_subfunc.size(); i++) {
			if (matrix_subfunc[i][matrix_subfunc[i].size() - 1].get_logic_num() == 1) {
				ind++;
			}
		}

		if (ind <= 0) {
			cout << "ничего\n";
			return false;
		}

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
		int ind = 0;
		cout << "Индексный метод СКНФ:\n";

		for (int i = 0; i < matrix_subfunc.size(); i++) {
			if (matrix_subfunc[i][matrix_subfunc[i].size() - 1].get_logic_num() == 0) {
				ind++;
			}
		}

		if (ind <= 0) {
			cout << "ничего\n";
			return false;
		}

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

	//ПОШЛИ МЕТОДЫ ДЛЯ ТРЕТЬЕЙ ЛАБОРАТОРНОЙ

	bool check_empty_sknf() {
		int ind = 0;
		for (int i = 0; i < matrix_subfunc.size(); i++) {
			if (matrix_subfunc[i][matrix_subfunc[i].size() - 1].get_logic_num() == 0) {
				ind++;
			}
		}

		if (ind <= 0) {
			return false;
		}
		return true;
	}

	bool check_empty_sdnf() {
		int ind = 0;
		for (int i = 0; i < matrix_subfunc.size(); i++) {
			if (matrix_subfunc[i][matrix_subfunc[i].size() - 1].get_logic_num() == 1) {
				ind++;
			}
		}

		if (ind <= 0) {
			return false;
		}
		return true;
	}

	//Берет элемент матрицы и, если 0, возвращает отрицательный индекс, если 1 - положительный индекс
	int get_correct_number_element(int y_pos, int x_pos) {
		int res;
		if (matrix_subfunc[y_pos][x_pos].get_logic_num() == 0) {
			res = (x_pos + 1) * (-1);
			return res;
		}
		else {
			res = x_pos + 1;
			return res;
		}
	}

	//Заполняет первый раз СДНФ индексами для работы
	bool fill_list_elements(vector<vector<int>>* list_el, int num) {
		(*list_el).clear();
		if (num == 1) {
			for (int i = 0; i < matrix_subfunc.size(); i++) {
				if (matrix_subfunc[i][matrix_subfunc[i].size() - 1].get_logic_num() == 1) {
					(*list_el).push_back({ get_correct_number_element(i, 0) , get_correct_number_element(i, 1) , get_correct_number_element(i, 2) });
				}
			}
			return true;
		}
		else if (num == 0) {
			for (int i = 0; i < matrix_subfunc.size(); i++) {
				if (matrix_subfunc[i][matrix_subfunc[i].size() - 1].get_logic_num() == 0) {
					(*list_el).push_back({ get_correct_number_element(i, 0) , get_correct_number_element(i, 1) , get_correct_number_element(i, 2) });
				}
			}
			return true;
		}
		return false;
	}

	//Проверяет, существует ли такой элемент уже в списке
	bool check_exist_element(vector<int> elem, vector<vector<int>> main_elem) {
		for (int i = 0; i < main_elem.size(); i++) {
			if (elem == main_elem[i]) {
				return true;
			}
		}
		return false;
	}

	//Проверяет, есть ли элемент уже в списке на удаление
	bool check_exist_delete_element(vector<int> elem, vector<vector<int>> delete_list) {
		if (delete_list.size() > 0) {
			for (int i = 0; i < delete_list.size(); i++) {
				if (delete_list[i] == elem) {
					return true;
				}
			}
			return false;
		}
		return false;
	}

	bool equall_elements(int first_x, int second_x, vector<vector<int>> list_el) {
		for (int i = 0; i < list_el[first_x].size(); i++) {
			if (abs(list_el[first_x][i]) != abs(list_el[second_x][i])) {
				return false;
			}
		}
		return true;
	}

	//Создает новый элемент слияния
	bool add_new_element(int first_x, int second_x, vector<vector<int>>* list_el, vector<vector<int>>* delete_list) {
		vector<int> new_element;

		for (int i = 0; i < (*list_el)[first_x].size(); i++) {
			if ((*list_el)[first_x][i] == (*list_el)[second_x][i]) {
				new_element.push_back((*list_el)[first_x][i]);
			}
		}

		if (new_element.size() == (*list_el)[first_x].size() - 1 && new_element.size() != 0 && equall_elements(first_x, second_x, *list_el)) {
			if (!check_exist_delete_element((*list_el)[first_x], *delete_list)) {
				delete_list->push_back((*list_el)[first_x]);
			}
			if (!check_exist_delete_element((*list_el)[second_x], *delete_list)) {
				delete_list->push_back((*list_el)[second_x]);
			}
			if (!check_exist_element(new_element, *list_el)) {
				list_el->push_back(new_element);
				return true;
			}
		}
		return false;
	}


	//ПЕРВЫЙ ЭТАП РАСЧЕТНОГО МЕТОДА
	bool gluing_elements(vector<vector<int>>* list_el, int num) {
		vector<vector<int>> list_delete_elements;
		fill_list_elements(list_el, num);
		bool flag = true;
		// Прогоняем, пока есть, что склеивать
		while (flag) {
			flag = false;
			// Прогоняем по каждому элементу
			for (int i = 0; i < list_el->size() - 1; i++) {
				// Для каждого элемента прогоняем другие, чтобы проверить проверку на склеивание
				for (int j = 0; j < list_el->size(); j++) {
					// Проверяем на одинаковую длину двух элементов
					if ((*list_el)[i].size() == (*list_el)[j].size()) {
						// Если хоть какие-то 2 индекса равны между собой, запихиваем элементы в функцию обработки
						if (add_new_element(i, j, list_el, &list_delete_elements)) {
							flag = true;
						}
					}
				}
			}
		}
		// Удаление использованных элементов
		int counter = 0;
		while (counter < list_el->size()) {
			if (check_exist_delete_element((*list_el)[counter], list_delete_elements)) {
				list_el->erase(list_el->begin() + counter);
				counter = 0;
				continue;
			}
			counter++;
		}
		return true;
	}

	bool check_include_element_in_main(int main_x, int additional_x, vector<vector<int>> list_el) {
		if (list_el[main_x].size() < list_el[additional_x].size()) {
			return false;
		}
		for (int i = 0; i < list_el[additional_x].size(); i++) {
			auto it = find(list_el[main_x].begin(), list_el[main_x].end(), list_el[additional_x][i]);
			if (it == list_el[main_x].end()) {
				return false;
			}
		}
		return true;
	}

	//ВТОРОЙ ЭТАП РАСЧЕТНОГО МЕТОДА
	bool delete_unnecessary_elements(vector<vector<int>>* list_el) {
		if (list_el->size() > 1) {
			int counter = 0;
			int num_include = 0;
			while (counter < list_el->size()) {
				for (int j = 0; j < list_el->size(); j++) {
					if (check_include_element_in_main(counter, j, *list_el)) {
						num_include++;
				}
				}
				if (num_include >= 2) {
					list_el->erase(list_el->begin() + counter);
					if (list_el->size() == 1) {
						return true;
					}
					num_include = 0;
					counter = 0;
					continue;
				}
				counter++;
				num_include = 0;
			}
			return true;
		}
		return false;
	}

	bool print_method(vector<vector<int>> list_el, int num) {
		if (num == 0) {
			print_method_sknf(list_el);
			return true;
		}
		else if (num == 1) {
			print_method_sdnf(list_el);
			return true;
		}
		return false;
	}

	bool print_method_sdnf(vector<vector<int>> list_el) {
		string result = "";
		string index = "";
		for (int i = 0; i < list_el.size(); i++) {
			result += "(";
			for (int j = 0; j < list_el[i].size(); j++) {
				if (list_el[i][j] > 0) {
					index = "x" + to_string(list_el[i][j]);
				}
				else {
					index = "x" + to_string(abs(list_el[i][j])) + "'";
				}

				result += index;
				if (j != list_el[i].size() - 1) {
					result += "*";
				}
			}
			if (i == list_el.size() - 1) {
				result += ")";
			}
			else {
				result += ")+";
			}
		}
		cout << result << endl;
		return true;
	}

	bool print_method_sknf(vector<vector<int>> list_el) {
		string result = "";
		string index = "";
		for (int i = 0; i < list_el.size(); i++) {
			result += "(";
			for (int j = 0; j < list_el[i].size(); j++) {
				if (list_el[i][j] > 0) {
					index = "x" + to_string(list_el[i][j]) + "'";
				}
				else {
					index = "x" + to_string(abs(list_el[i][j]));
				}

				result += index;
				if (j != list_el[i].size() - 1) {
					result += "+";
				}
			}
			if (i == list_el.size() - 1) {
				result += ")";
			}
			else {
				result += ")*";
			}
		}
		cout << result << endl;
		return true;
	}

	//РАСЧТЕНО-ТАБЛИЧНЫЙ МЕТОД

	bool check_exist_min_el_in_origin_el(vector<int> list_min_el, vector<int> list_origin_el) {
		int counter = 0;
		for (int i = 0; i < list_min_el.size(); i++) {
			for (int j = 0; j < list_origin_el.size(); j++) {
				if (list_min_el[i] == list_origin_el[j]) {
					counter++;
					break;
				}
			}
		}
		if (counter == list_min_el.size()) {
			return true;
		}
		else {
			return false;
		}
	}

	bool check_exist_el_in_min_list(vector<vector<int>> table_math_list, vector<int> new_element) {
		if (table_math_list.size() > 0) {
			for (int i = 0; i < table_math_list.size(); i++) {
				if (new_element == table_math_list[i]) {
					return true;
				}
			}
			return false;
		}
		else {
			return false;
		}
	}

	bool find_min_elements(vector<vector<vector<int>>> table_elements, vector<vector<int>>* table_math_list) {
		for (int i = 1; i < table_elements.size(); i++) {
			int counter = 0;
			int pos = 0;
			for (int j = 1; j < table_elements[i].size(); j++) {
				if (table_elements[i][j][0] == 1) {
					counter++;
					pos = j;
				}
			}
			if ((counter == 1) && (!check_exist_el_in_min_list(*table_math_list, table_elements[0][pos]))) {
				table_math_list->push_back(table_elements[0][pos]);
			}
		}
		return true;
	}

	bool print_table(vector<vector<vector<int>>> table_elements) {
		cout << "\nТаблица таблично-расчетного метода:\n";
		for (int i = 1; i < table_elements[1].size(); i++) {
			for (int j = 1; j < table_elements.size(); j++) {
				for (int k = 0; k < table_elements[j][i].size(); k++) {
					cout << table_elements[j][i][k];
				}
				cout << " ";
			}
			cout << endl;
		}
		return true;
	}
	
	//ПЕРВЫЙ ЭТАП gluing
	
	//ВТОРОЙ ЭТАП - ТАБЛИЦА
	bool make_table_elements(vector<vector<int>>* table_math_list, int num) {
		vector<vector<vector<int>>> table_elements;
		vector<vector<int>> origin_list_sdnf;
		vector<vector<int>> min_list_el;
		gluing_elements(&min_list_el, num);
		fill_list_elements(&origin_list_sdnf, num);
		table_elements.push_back({});
		table_elements[0].push_back({});

		// Добавил все элементы СДНФ/СКНФ
		for (int i = 0; i < origin_list_sdnf.size(); i++) {
			table_elements.push_back(vector<vector<int>>(1, origin_list_sdnf[i]));
		}

		// Добавил элементы сокращенной функции
		for (int i = 0; i < min_list_el.size(); i++) {
			table_elements.at(0).push_back(min_list_el[i]);
		}

		// Для каждого сокращенного элемента проверяем включение
		for (int i = 1; i < table_elements[0].size(); i++) {
			for (int j = 1; j < table_elements.size(); j++) {
				if (check_exist_min_el_in_origin_el(table_elements[0][i], table_elements[j][0])) {
					table_elements[j].push_back({ 1 });
				}
				else {
					table_elements[j].push_back({ 0 });
				}
			}
		}

		print_table(table_elements);
		find_min_elements(table_elements, table_math_list);

		//*table_math_list = table_elements;
		return true;
	}

	//ТАБЛИЧНЫЙ СПОСОБ КАРНО

	// Преобразование числа в бинарный массив
	vector<int> decimalToBinary(int decimal, int n) {
		vector<int> binary(n, 0);
		int index = n - 1;
		while (decimal > 0) {
			binary[index] = decimal % 2;
			decimal /= 2;
			index--;
		}
		return binary;
	}

	// Функция для генерации последовательности Грея
	void generateGrayCode(int hor_num, int vert_num, vector<vector<vector<int>>>* karno_table) {
		for (int i = 0; i < pow(2, hor_num); ++i) {
			int gray = i ^ (i >> 1);
			vector<int> binary = decimalToBinary(gray, hor_num);

			// Заполняем горизонтальную полоску
			karno_table->push_back({});
			karno_table->back().push_back(binary);
		}

		for (int i = 0; i < pow(2, vert_num); ++i) {
			int gray = i ^ (i >> 1);
			vector<int> binary = decimalToBinary(gray, vert_num);
			// Заполняем вертикальную полоску
			(*karno_table)[0].push_back(binary);
		}
	}

	bool print_table_answer() {
		vector<vector<int>> list_elements_sdnf;  // Получаем список элементов
		gluing_elements(&list_elements_sdnf, 1);
		delete_unnecessary_elements(&list_elements_sdnf);
		vector<vector<int>> list_elements_sknf;  // Получаем список элементов
		gluing_elements(&list_elements_sknf, 0);
		delete_unnecessary_elements(&list_elements_sknf);
		cout << "Минимизированная СДНФ:\n";
		print_method(list_elements_sdnf, 1);
		cout << "Минимизированная СКНФ:\n";
		print_method(list_elements_sknf, 0);
		return true;
	}

	int get_x_pos_table_karno(vector<vector<vector<int>>> karno_table, vector<int> hor_el) {
		for (int i = 1; i < karno_table.size(); i++) {
			if (karno_table[i][0] == hor_el) {
				return i;
			}
		}
		return 0;
	}

	int get_y_pos_table_karno(vector<vector<vector<int>>> karno_table, vector<int> vert_el) {
		for (int i = 1; i < karno_table[0].size(); i++) {
			if (karno_table[0][i] == vert_el) {
				return i;
			}
		}
	}

	void fill_karno_meaning(vector<vector<vector<int>>>* karno_table, int vert_num, int index, int num) {
		vector<int> hor_el;
		vector<int> vert_el;
		for (int i = 0; i < num; i++) {
			if (i < vert_num) {
				vert_el.push_back(matrix_subfunc[index][i].get_logic_num());
			}
			else {
				hor_el.push_back(matrix_subfunc[index][i].get_logic_num());
			}
		}
		int x_pos = get_x_pos_table_karno(*karno_table, hor_el);
		int y_pos = get_y_pos_table_karno(*karno_table, vert_el);
		(*karno_table)[x_pos][y_pos].clear();
		(*karno_table)[x_pos][y_pos].push_back(1);
	}


	vector<vector<vector<int>>> generate_karno_table(int num) {
		vector<vector<vector<int>>> karno_table;
		karno_table.push_back({});
		karno_table[0].push_back({});
		int hor_num = 0;
		int vert_num = 0;
		if (num % 2 == 0) {
			hor_num = num / 2;
			vert_num = num / 2;
		}
		else {
			hor_num = num / 2 + 1;
			vert_num = num / 2;
		}
		generateGrayCode(hor_num, vert_num, &karno_table);
		for (int i = 1; i < karno_table.size(); i++) {
			for (int j = 1; j < karno_table[0].size(); j++) {
				karno_table[i].push_back({ 0 });
			}
		}
		for (int i = 0; i < matrix_subfunc.size(); i++) {
			if (matrix_subfunc[i][matrix_subfunc[i].size() - 1].get_logic_num() == 1) {
				fill_karno_meaning(&karno_table, vert_num, i, num);
			}
		}

		return karno_table;
	}

	bool print_karno_table(int num) {
		vector<vector<vector<int>>> karno_table = generate_karno_table(num);
		for (int i = 1; i < karno_table[0].size(); i++) {
			for (int j = 1; j < karno_table.size(); j++) {
				cout << karno_table[j][i][0] << " ";
			}
			cout << endl;
		}
		return true;
	}

};