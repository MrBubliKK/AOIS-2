#include <string>
#include <vector>
#include <iostream>
#include "CA.cpp"
using namespace std;

int main() {
	system("chcp 1251");
	CA ca;
	ca.fill_departure_part();
	ca.fill_arrival_part();
	ca.fill_excitement_part();
	cout << "Таблица цифрового аппарата:\n";
	ca.print_matrix();

	ca.fill_list_h1();
	ca.fill_list_h2();
	ca.fill_list_h3();

	vector<vector<int>> list_h1 = ca.get_list_h1();
	vector<vector<int>> list_h2 = ca.get_list_h2();
	vector<vector<int>> list_h3 = ca.get_list_h3();

	ca.gluing_elements(&list_h1);
	ca.gluing_elements(&list_h2);
	ca.gluing_elements(&list_h3);

	cout << "\nВывод h1:\n";
	ca.print_method_sdnf(list_h1);

	cout << "\nВывод h2:\n";
	ca.print_method_sdnf(list_h2);

	cout << "\nВывод h3:\n";
	ca.print_method_sdnf(list_h3);
}