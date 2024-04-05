#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Function {
private:
	vector<vector<int>> ODS_3_matrix;
	vector<vector<int>> synthesis_matrix;
	vector<vector<int>> list_P;
	vector<vector<int>> list_S;

	vector<vector<int>> list_y1;
	vector<vector<int>> list_y2;
	vector<vector<int>> list_y3;
	vector<vector<int>> list_y4;


public:
	vector<vector<int>> get_ODS_3_matrix() {
		return ODS_3_matrix;
	}

	vector<vector<int>> get_list_P() {
		return list_P;
	}

	vector<vector<int>> get_list_S() {
		return list_S;
	}

	vector<vector<int>> get_list_y1() {
		return list_y1;
	}

	vector<vector<int>> get_list_y2() {
		return list_y2;
	}

	vector<vector<int>> get_list_y3() {
		return list_y3;
	}

	vector<vector<int>> get_list_y4() {
		return list_y4;
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

	//Прокидываю в матрицы переменные со знаками для всех вариантов
	bool fill_little_subfunc() {
		string binary_num = "";
		int decimal_num = -1;

		for (int i = 0; i < 5; i++) {
			vector<int> new_vec(8);
			ODS_3_matrix.push_back(new_vec);
		}

		for (int j = 0; j < 8; j++) {
			decimal_num++;
			binary_num = transfer_10_to_2(decimal_num);
			while (binary_num.size() < 3) {
				binary_num = "0" + binary_num;
			}
			int temp_num = binary_num[0] - '0';
			ODS_3_matrix[0][j] = temp_num;
			temp_num = binary_num[1] - '0';
			ODS_3_matrix[1][j] = temp_num;
			temp_num = binary_num[2] - '0';
			ODS_3_matrix[2][j] = temp_num;
		}
		return true;
	}

	//Заполняет результаты S и P в матрице
	bool fill_func_cells() {
		for (int i = 0; i < 8; i++) {
			int counter = 0;
			for (int j = 0; j < 3; j++) {
				if (ODS_3_matrix[j][i] == 1) {
					counter++;
				}
			}

			if ((counter == 2) || (counter == 3)) {
				ODS_3_matrix[3][i] = 1;
			}

			if ((counter == 1) || (counter == 3)) {
				ODS_3_matrix[4][i] = 1;
			}
		}
		return true;
	}

	//Функция заполнения матрицы
	bool fill_matrix() {
		ODS_3_matrix.clear();
		fill_little_subfunc();
		fill_func_cells();
		return true;
	}

	//Отрисовка матрицы
	void print_matrix() {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 8; j++) {
				cout << ODS_3_matrix[i][j] << " ";
			}
			cout << endl;
		}
	}

	//Заполняет первоначально лист Р
	bool fill_list_P() {
		int counter = -1;
		list_P.clear();
		for (int i = 0; i < 8; i++) {
			if (ODS_3_matrix[3][i] == 0) {
				int index_counter = 0;
				list_P.push_back({});
				counter++;
				for (int j = 2; j >= 0; j--) {
					index_counter++;
					if (ODS_3_matrix[j][i] > 0) {
						list_P[counter].push_back(index_counter);
					}
					else {
						list_P[counter].push_back(index_counter * (-1));
					}
				}
			}

		}
		return true;
	}

	//Заполняет первоначально лист S
	bool fill_list_S() {
		int counter = -1;
		list_S.clear();
		for (int i = 0; i < 8; i++) {
			if (ODS_3_matrix[4][i] == 0) {
				int index_counter = 0;
				list_S.push_back({});
				counter++;
				for (int j = 2; j >= 0; j--) {
					index_counter++;
					if (ODS_3_matrix[j][i] > 0) {
						list_S[counter].push_back(index_counter);
					}
					else {
						list_S[counter].push_back(index_counter* (-1));
					}
				}
			}

		}
		return true;
	}

	//Вывод списка в СКНФ виде
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

	void check_equall_length(vector<vector<int>>* list_el, vector<vector<int>>* list_delete_elements, int i, bool* flag) {
		for (int j = 0; j < list_el->size(); j++) {
			// Проверяем на одинаковую длину двух элементов
			if ((*list_el)[i].size() == (*list_el)[j].size()) {
				// Если хоть какие-то 2 индекса равны между собой, запихиваем элементы в функцию обработки
				if (add_new_element(i, j, list_el, list_delete_elements)) {
					*flag = true;
				}
			}
		}
	}

	bool gluing_elements(vector<vector<int>>* list_el) {
		vector<vector<int>> list_delete_elements;
		bool flag = true;
		// Прогоняем, пока есть, что склеивать
		while (flag) {
			flag = false;
			// Прогоняем по каждому элементу
			for (int i = 0; i < list_el->size() - 1; i++) {
				// Для каждого элемента прогоняем другие, чтобы проверить проверку на склеивание
				check_equall_length(list_el, &list_delete_elements, i, &flag);
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

	bool fill_synthesis_matrix_little_subfunc() {
		synthesis_matrix.clear();
		string binary_num = "";
		int decimal_num = -1;

		for (int i = 0; i < 8; i++) {
			vector<int> new_vec(16);
			synthesis_matrix.push_back(new_vec);
		}

		for (int j = 0; j < 16; j++) {
			decimal_num++;
			binary_num = transfer_10_to_2(decimal_num);
			while (binary_num.size() < 4) {
				binary_num = "0" + binary_num;
			}
			int temp_num = binary_num[0] - '0';
			synthesis_matrix[0][j] = temp_num;
			temp_num = binary_num[1] - '0';
			synthesis_matrix[1][j] = temp_num;
			temp_num = binary_num[2] - '0';
			synthesis_matrix[2][j] = temp_num;
			temp_num = binary_num[3] - '0';
			synthesis_matrix[3][j] = temp_num;
		}
		return true;
	}

	bool print_synthesis_matrix() {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 16; j++) {
				cout << synthesis_matrix[i][j] << " ";
			}
			cout << endl;
		}
		return true;
	}

	//Упрощает функцию подсчета суммы
	bool sum_numbers_check_sign(vector<int> first, vector<int> second, vector<int>* sum_mas, int add_num) {
		for (int i = 0; i < first.size(); i++) {
			if ((first[i] == 0) && (second[i] == 0)) {
				if (add_num >= 3) {
					sum_mas->push_back(1);
					add_num -= 2;
				}
				else if (add_num == 2) {
					sum_mas->push_back(0);
					add_num--;
				}
				else if (add_num == 1) {
					sum_mas->push_back(1);
					add_num--;
				}
				else {
					sum_mas->push_back(0);
				}
			}
			else if ((first[i] == 1) && (second[i] == 1)) {
				if (add_num >= 1) {
					sum_mas->push_back(1);
				}
				else {
					sum_mas->push_back(0);
					add_num++;
				}
			}
			else {
				if (add_num >= 2) {
					sum_mas->push_back(1);
					add_num--;
				}
				else if (add_num == 1) {
					sum_mas->push_back(0);
				}
				else {
					sum_mas->push_back(1);
				}
			}
		}

		while (add_num > 0) {
			if (add_num >= 2) {
				sum_mas->push_back(0);
				add_num--;
			}
			else if (add_num == 1) {
				sum_mas->push_back(1);
				add_num--;
			}
		}
		return true;
	}

	//Суммирует два целых числа
	vector<int> sum_numbers(vector<int> first, vector<int> second) {
		int add_num = 0;
		vector<int> sum_mas;
		reverse(first.begin(), first.end());
		reverse(second.begin(), second.end());

		sum_numbers_check_sign(first, second, &sum_mas, add_num);

		reverse(sum_mas.begin(), sum_mas.end());
		return sum_mas;
	}

	bool fill_result_synthesis_matrix() {
		vector<int> const_list = { 0, 0, 0, 1 };
		for (int i = 0; i < 16; i++) {
			vector<int> subfunc_list = {};
			for (int j = 0; j < 4; j++) {
				subfunc_list.push_back(synthesis_matrix[j][i]);
			}
			vector<int> result_list = sum_numbers(subfunc_list, const_list);
			int counter = 0;
			for (int j = 4; j < 8; j++) {
				synthesis_matrix[j][i] = result_list[counter];
				counter++;
			}
			
		}
		return true;
	}

	bool fill_one_llist_synthesis_matrix(vector<vector<int>>* list_el, int index) {
		list_el->push_back({});
		int counter = 1;
		for (int i = 3; i >= 0; i--) {
			if (synthesis_matrix[i][index] == 1) {
				(*list_el)[list_el->size() - 1].push_back(counter);
			}
			else {
				(*list_el)[list_el->size() - 1].push_back(counter * (-1));
			}
			counter++;
		}
		return true;
	}

	bool fill_lists_synthesis_matrix() {
		list_y1.clear();
		list_y2.clear();
		list_y3.clear();
		list_y4.clear();

		for (int i = 0; i < 16; i++) {
			if (synthesis_matrix[4][i] == 0) {
				fill_one_llist_synthesis_matrix(&list_y4, i);
			}
			if (synthesis_matrix[5][i] == 0) {
				fill_one_llist_synthesis_matrix(&list_y3, i);
			}
			if (synthesis_matrix[6][i] == 0) {
				fill_one_llist_synthesis_matrix(&list_y2, i);
			}
			if (synthesis_matrix[7][i] == 0) {
				fill_one_llist_synthesis_matrix(&list_y1, i);
			}
		}
		return true;
	}


};