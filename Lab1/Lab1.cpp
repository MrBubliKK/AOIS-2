#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "WorkFunctions.h"
using namespace std;


int main() {
	system("chcp 1251");
	int f_num, s_num;
	vector<int> two_num;
	cout << "Введите первое число: ";
	cin >> f_num;
	Massive first(f_num);
	cout << "Введите второе число: ";
	cin >> s_num;
	Massive second(s_num);

	first.transfer_direct(f_num);
	first.transfer_reverse();
	first.transfer_additional();
	first.make_transfer_number();

	second.transfer_direct(s_num);
	second.transfer_reverse();
	second.transfer_additional();
	second.make_transfer_number();



	cout << "----------\n";
	sum_numbers(&first, &second);
	cout << "----------\n";
	
	first.print_transfer_mas();
	first.print_direct_mas();
	first.print_reverse_mas();
	first.print_additional_mas();

	second.print_transfer_mas();
	second.print_direct_mas();
	second.print_reverse_mas();
	second.print_additional_mas();

	cout << "----------\n";
	composition_numbers(&first, &second);
	cout << "----------\n";

	cout << "Деление\n";
	division_numbers(&first, &second);

	float f_p_num, s_p_num;
	cout << "Введите первое число с точкой: ";
	cin >> f_p_num;
	cout << "Введите второе число с точкой: ";
	cin >> s_p_num;
	PointNumber first_point(f_p_num);
	PointNumber second_point(s_p_num);
	first_point.transfer_direct();
	second_point.transfer_direct();

	first_point.print_direct_mas();
	second_point.print_direct_mas();
	sum_transfer_ieee754(&first_point, &second_point);

}