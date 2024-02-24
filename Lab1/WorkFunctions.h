#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "Massive.cpp"
#include "PointNumber.cpp"
using namespace std;

//Упрощает функцию подсчета суммы
bool sum_numbers_check_sign(Massive* first, Massive* second, vector<int>* sum_mas, int add_num) {
	for (int i = 0; i < first->get_transfer_mas().size(); i++) {
		if ((first->get_transfer_mas()[i] == 0) && (second->get_transfer_mas()[i] == 0)) {
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
		else if ((first->get_transfer_mas()[i] == 1) && (second->get_transfer_mas()[i] == 1)) {
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
bool sum_numbers(Massive* first, Massive* second) {
	int add_num = 0;
	vector<int> sum_mas;
	first->reverse_transfer();
	second->reverse_transfer();

	sum_numbers_check_sign(first, second, &sum_mas, add_num);

	reverse(sum_mas.begin(), sum_mas.end());
	for (int num : sum_mas) {
		cout << num;
	}
	cout << endl;

	first->make_transfer_number();

	second->make_transfer_number();
	return true;
}

bool sum_for_comp_check_sign(vector<int>* first, vector<int>* second, vector<int>* sum_mas, int add_num) {
	for (int i = 0; i < first->size(); i++) {
		if ((*first)[i] == 0 && (*second)[i] == 0) {
			if (add_num >= 3) {
				(*sum_mas).push_back(1);
				add_num -= 2;
			}
			else if (add_num == 2) {
				(*sum_mas).push_back(0);
				add_num--;
			}
			else if (add_num == 1) {
				(*sum_mas).push_back(1);
				add_num--;
			}
			else {
				(*sum_mas).push_back(0);
			}
		}
		else if ((*first)[i] == 1 && (*second)[i] == 1) {
			if (add_num >= 1) {
				(*sum_mas).push_back(1);
			}
			else {
				(*sum_mas).push_back(0);
				add_num++;
			}
		}
		else {
			if (add_num >= 2) {
				(*sum_mas).push_back(1);
				add_num--;
			}
			else if (add_num == 1) {
				(*sum_mas).push_back(0);
			}
			else {
				(*sum_mas).push_back(1);
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

bool sum_for_comp(vector<int>* first, vector<int>* second) {
	int add_num = 0;
	vector<int> sum_mas;
	if (first->size() > second->size()) {
		for (int i = second->size(); i < first->size(); i++) {
			second->push_back(0);
		}
	}
	else if (first->size() < second->size()) {
		for (int i = first->size(); i < second->size(); i++) {
			first->push_back(0);
		}
	}

	sum_for_comp_check_sign(first, second, &sum_mas, add_num);

	first->clear();
	for (int num : sum_mas) {
		first->push_back(num);
	}
	return true;
}

bool composition_transfer(Massive* first, Massive* second, vector<int>* first_comp_list, vector<int>* second_comp_list) {
	for (int i = 1; i < first->get_transfer_mas().size(); i++) {
		if (first->get_transfer_mas()[i] == 1) {
			for (int num : second->get_transfer_mas()) {
				(*second_comp_list).push_back(num);
			}
			for (int j = 0; j < i; j++) {
				(*second_comp_list).insert((*second_comp_list).begin(), 0);
			}
		}
		else {
			for (int num : second->get_transfer_mas()) {
				(*second_comp_list).push_back(0);
			}
			for (int j = 0; j < i; j++) {
				(*second_comp_list).insert((*second_comp_list).begin(), 0);
			}
		}
		sum_for_comp(first_comp_list, second_comp_list);
		(*second_comp_list).clear();
	}
	return true;
}

//Умножает два целых числа
bool composition_numbers(Massive* first, Massive* second) {
	first->reverse_transfer();
	second->reverse_transfer();
	int counter = 0;
	vector<int> first_comp_list;
	vector<int> second_comp_list;
	if (first->get_transfer_mas()[0] == 1) {
		for (int num : second->get_transfer_mas()) {
			first_comp_list.push_back(num);
		}
	}
	else {
		for (int num : second->get_transfer_mas()) {
			first_comp_list.push_back(0);
		}
	}

	composition_transfer(first, second, &first_comp_list, &second_comp_list);

	reverse(first_comp_list.begin(), first_comp_list.end());
	for (int i = 0; i < first_comp_list.size(); i++) {
		if (first_comp_list[i] != 0) {
			first_comp_list.erase(first_comp_list.begin(), first_comp_list.begin() + i);
			break;
		}
	}
	cout << "Произведениие дву целых чисел:\n";
	for (int num : first_comp_list) {
		cout << num;
	}
	cout << endl;

	first->transfer_direct_op(first->get_num());
	first->transfer_reverse_op();
	first->transfer_additional_op();

	second->transfer_direct_op(second->get_num());
	second->transfer_reverse_op();
	second->transfer_additional_op();
	return true;
}

string difference_numbers(string first, string second) {
	vector<int> result;
	string str_res;
	int num;
	for (int i = 0; i < first.length(); i++) {
		if (((first[i] == '1') && (second[i] == '1')) || ((first[i] == '0') && (second[i] == '0'))) {
			result.push_back(0);
		}
		else if ((first[i] == '1') && (second[i] == '0')) {
			result.push_back(1);
		}
		else {
			num = i;
			result.push_back(0);
			while (result[num] != 1) {
				result[num] = 1;
				num--;
			}
			result[num] = 0;
		}
	}

	for (int count : result) {
		str_res += to_string(count);
	}
	return to_string(stoi(str_res));
}

bool divis_int_transfer(string* first, string* second, string* temp_number, string* res_number) {
	for (int i = 0; i < (*second).length(); i++) {
		(*temp_number) += (*first)[i];
	}
	// если она больше/равна, делаем разность
	if (*temp_number >= *second) {
		(*temp_number) = difference_numbers(*temp_number, *second);
		(*res_number) += '1';
	}
	// прогоняем оставшиеся разы для обработки всех цифр
	for (int i = (*second).size(); i < ((*first).size() - (*second).size()); i++) {
		(*temp_number) += (*first)[i];
		while ((*temp_number).length() != (*second).length()) {
			if ((*temp_number).length() < (*second).length()) {
				(*temp_number).insert(0, "0");
			}
			else {
				(*second).insert(0, "0");
			}
		}
		if (*temp_number >= *second) {
			(*temp_number) = difference_numbers(*temp_number, *second);
			(*res_number) += '1';
		}
		else {
			(*res_number) += '0';
			*temp_number = to_string(stoi(*temp_number));
			*second = to_string(stoi(*second));
		}
	}
	return true;
}

bool divis_float_transfer(string* first, string* second, string* temp_number, string* res_number) {
	*first = to_string(stoi(*first));
	*second = to_string(stoi(*second));
	*res_number += ".";
	for (int i = 0; i < 5; i++) {
		*temp_number += '0';
		while ((*temp_number).length() != (*second).length()) {
			if ((*temp_number).length() < (*second).length()) {
				(*temp_number).insert(0, "0");
			}
			else {
				(*second).insert(0, "0");
			}
		}
		if (*temp_number >= *second) {
			*temp_number = difference_numbers(*temp_number, *second);
			*res_number += '1';
		}
		else {
			*res_number += '0';
			*temp_number = to_string(stoi(*temp_number));
			*second = to_string(stoi(*second));
		}
	}
	return true;
}

//Основная функция деления чисел
bool division_numbers(Massive* first_mas, Massive* second_mas) {
	string first, second, temp_number, res_number;
	int counter;
	bool flag = false;
	for (int i = 1; i < first_mas->get_direct_mas().size(); i++) {
		first += to_string(first_mas->get_direct_mas()[i]);
	}
	for (int i = 1; i < second_mas->get_direct_mas().size(); i++) {
		second += to_string(second_mas->get_direct_mas()[i]);
	}

	while (first.length() != second.length()) {
		if (first.length() < second.length()) {
			first.insert(0, "0");
		}
		else {
			second.insert(0, "0");
		}
	}

	if (first >= second) {
		divis_int_transfer(&first, &second, &temp_number, &res_number);
	}
	if (res_number.length() == 0) {
		res_number += "0";
		temp_number = first;
	}

	divis_float_transfer(&first, &second, &temp_number, &res_number);

	cout << res_number << endl;
	return true;
}

bool sum_point_numbers_check_sign(vector<int>* first, vector<int>* second, vector<int>* sum_mas, int add_num) {
	for (int i = 0; i < (*first).size(); i++) {
		if (((*first)[i] == 0) && ((*second)[i] == 0)) {
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
		else if (((*first)[i] == 1) && ((*second)[i] == 1)) {
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

bool make_parts_number(PointNumber* first, PointNumber* second, bool* flag, vector<int>* first_num, vector<int>* second_num,
	string* f_int, string* f_float, string* s_int, string* s_float, int* f_counter, int* s_counter) {
	for (string num : first->get_direct_mas()) {
		if (num != ".") {
			first_num->push_back(stoi(num));
		}
		else if (num == ".") {
			*flag = true;
		}
		if (*flag) {
			(*f_counter)++;
			*f_float += num;
		}
		else {
			*f_int += num;
		}
	}
	(*f_counter) -= 2;
	*flag = false;
	for (string num : second->get_direct_mas()) {
		if (num != ".") {
			second_num->push_back(stoi(num));
		}
		else if (num == ".") {
			*flag = true;
		}
		if (*flag) {
			(*s_counter)++;
			*s_float += num;
		}
		else {
			*s_int += num;
		}
	}
	(*s_counter) -= 2;
	return true;
}

bool balance_parts(string* f_int, string* s_int, string* f_float, string* s_float, vector<int>* first_num, vector<int>* second_num) {
	while (f_int->size() != s_int->size()) {
		if (f_int->size() < s_int->size()) {
			first_num->insert(first_num->begin(), 0);
			*f_int += "0";
		}
		else {
			second_num->insert(second_num->begin(), 0);
			*s_int += "0";
		}
	}

	while (f_float->size() != s_float->size()) {
		if (f_float->size() < s_float->size()) {
			first_num->push_back(0);
			*f_float += "0";
		}
		else {
			second_num->push_back(0);
			*s_float += "0";
		}
	}
	return true;
}



//Основная функция суммы чисел с точками
vector<string> sum_point_numbers(PointNumber* first, PointNumber* second) {
	vector<string> result;
	string f_int, f_float, s_int, s_float;
	vector<int> first_num, second_num;
	bool flag = false;
	int f_counter = 0;
	int s_counter = 0;

	make_parts_number(first, second, &flag, &first_num, &second_num, &f_int, &f_float, &s_int, &s_float, &f_counter, &s_counter);
	balance_parts(&f_int, &s_int, &f_float, &s_float, &first_num, &second_num);

	int counter = (f_counter > s_counter) ? f_counter : s_counter;

	//Основная часть
	int add_num = 0;
	vector<int> sum_mas;
	reverse(first_num.begin(), first_num.end());
	reverse(second_num.begin(), second_num.end());

	sum_point_numbers_check_sign(&first_num, &second_num, &sum_mas, add_num);
	for (int i = 0; i < sum_mas.size(); i++) {
		result.push_back(to_string(sum_mas[i]));
		if (i == counter) {
			result.push_back(".");
		}
	}

	reverse(result.begin(), result.end());
	for (string num : result) {
		cout << num;
	}
	cout << endl;
	return result;
}

bool sum_transfer_ieee754(PointNumber* first, PointNumber* second) {
	vector<string>sum_num = sum_point_numbers(first, second);
	vector<int> exp_mas;
	vector<int> result;
	int num = 2;
	int count = 0;
	while (sum_num[num] != ".") {
		count++;
		num++;
	}
	int exp = 127 + count;
	while (exp != 0) {
		exp_mas.push_back(abs(exp % 2));
		exp /= 2;
	}
	reverse(exp_mas.begin(), exp_mas.end());
	result.push_back(0);
	for (int el : exp_mas) {
		result.push_back(el);
	}
	for (int i = 2; i < sum_num.size(); i++) {
		if (sum_num[i] != ".") {
			result.push_back(stoi(sum_num[i]));
		}
	}
	while (result.size() < 32) {
		result.push_back(0);
	}
	cout << "Сумма двух чисел с плавающей точкой:\n";
	for (int el : result) {
		cout << el;
	}
	cout << endl;
	return true;
}