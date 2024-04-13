#include <string>
#include <vector>
#include <iostream>
using namespace std;

class CA {
private:
	vector<vector<int>> transition_table;
	vector<vector<int>> ca_matrix;

	vector<vector<int>> list_h1;
	vector<vector<int>> list_h2;
	vector<vector<int>> list_h3;

public:
	vector<vector<int>> get_list_h1() {
		return list_h1;
	}

	vector<vector<int>> get_list_h2() {
		return list_h2;
	}

	vector<vector<int>> get_list_h3() {
		return list_h3;
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
	bool fill_departure_part() {
		string binary_num = "";
		int decimal_num = -1;

		for (int i = 0; i < 10; i++) {
			vector<int> new_vec(16);
			ca_matrix.push_back(new_vec);
		}

		for (int j = 0; j < 16; j++) {
			decimal_num++;
			binary_num = transfer_10_to_2(decimal_num);
			while (binary_num.size() < 4) {
				binary_num = "0" + binary_num;
			}
			int temp_num = binary_num[0] - '0';
			ca_matrix[0][j] = temp_num;
			temp_num = binary_num[1] - '0';
			ca_matrix[1][j] = temp_num;
			temp_num = binary_num[2] - '0';
			ca_matrix[2][j] = temp_num;
			temp_num = binary_num[3] - '0';
			ca_matrix[3][j] = temp_num;
		}
		return true;
	}

	bool fill_arrival_part() {
		string binary_num = "";
		int decimal_num = 1;
		int count = 0;
		for (int i = 1; i < 16; i++) {
			if (count >= 2) {
				decimal_num++;
				count = 0;
			}
			binary_num = transfer_10_to_2(decimal_num);
			while (binary_num.size() < 4) {
				binary_num = "0" + binary_num;
			}
			int temp_num = binary_num[1] - '0';
			ca_matrix[4][i] = temp_num;
			temp_num = binary_num[2] - '0';
			ca_matrix[5][i] = temp_num;
			temp_num = binary_num[3] - '0';
			ca_matrix[6][i] = temp_num;
			count++;
		}
		return true;
	}

	bool fill_excitement_part() {
		for (int i = 0; i < 16; i++) {
			for (int j = 0; j < 3; j++) {
				if (ca_matrix[j][i] != ca_matrix[j + 4][i]) {
					ca_matrix[j + 7][i] = 1;
				}
			}
		}
		return true;
	}

	//Отрисовка матрицы
	void print_matrix() {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 16; j++) {
				cout << ca_matrix[i][j] << " ";
			}
			cout << endl;
		}
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

	bool fill_list_h1() {
		int counter = -1;
		for (int i = 0; i < 16; i++) {
			if (ca_matrix[9][i] == 1) {
				int index_count = 0;
				counter++;
				list_h1.push_back({});
				for (int j = 3; j >= 0; j--) {
					index_count++;
					if (ca_matrix[j][i] == 1) {
						list_h1[counter].push_back(index_count);
					}
					else {
						list_h1[counter].push_back(index_count * (-1));
					}
				}
			}
		}
		return true;
	}

	bool fill_list_h2() {
		int counter = -1;
		for (int i = 0; i < 16; i++) {
			if (ca_matrix[8][i] == 1) {
				int index_count = 0;
				counter++;
				list_h2.push_back({});
				for (int j = 3; j >= 0; j--) {
					index_count++;
					if (ca_matrix[j][i] == 1) {
						list_h2[counter].push_back(index_count);
					}
					else {
						list_h2[counter].push_back(index_count * (-1));
					}
				}
			}
		}
		return true;
	}

	bool fill_list_h3() {
		int counter = -1;
		for (int i = 0; i < 16; i++) {
			if (ca_matrix[7][i] == 1) {
				int index_count = 0;
				counter++;
				list_h3.push_back({});
				for (int j = 3; j >= 0; j--) {
					index_count++;
					if (ca_matrix[j][i] == 1) {
						list_h3[counter].push_back(index_count);
					}
					else {
						list_h3[counter].push_back(index_count * (-1));
					}
				}
			}
		}
		return true;
	}

	//ИСПРАВИТЬ КОРРЕКТНЫЙ ВЫВОД. ОН ЩА ВЫВОДИТ ПРОСТО ПО ИНДЕКСАМ
	//Вывод списка в СДНФ виде
	bool print_method_sdnf(vector<vector<int>> list_el) {
		string result = "";
		string index = "";
		for (int i = 0; i < list_el.size(); i++) {
			for (int j = 0; j < list_el[i].size(); j++) {
				if (list_el[i][j] == 1) {
					index = "V";
				}
				else {
					index = "q\"" + to_string(list_el[i][j]-1);
				}
				result += index;
				if (j != list_el[i].size() - 1) {
					result += "*";
				}
			}
			if (i == list_el.size() - 1) {
				result += "";
			}
			else {
				result += "+";
			}
		}
		cout << result << endl;
		return true;
	}
};