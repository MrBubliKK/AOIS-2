#include <iostream>
#include <vector>
#include <string>
#include "Function.cpp"
using namespace std;

int main() {
	system("chcp 1251");
	Function func;
	func.fill_matrix();
	func.print_matrix();
	func.fill_list_P();
	func.fill_list_S();
	cout << "Лист P:\n";
	func.print_method_sknf(func.get_list_P());
	cout << "\nЛист S:\n";
	func.print_method_sknf(func.get_list_S());
	vector<vector<int>> list_P = func.get_list_P();
	vector<vector<int>> list_S = func.get_list_S();
	func.gluing_elements(&list_P);
	cout << "\nТКНФ P:\n";
	func.print_method_sknf(list_P);
	func.gluing_elements(&list_S);
	cout << "\nТКНФ S:\n";
	func.print_method_sknf(list_S);


	//Синтез матрицы Д8421 -> Д8422
	func.fill_synthesis_matrix_little_subfunc();
	func.fill_result_synthesis_matrix();
	cout << "\nМатрица синтеза:\n";
	func.print_synthesis_matrix();
	func.fill_lists_synthesis_matrix();
	vector<vector<int>> list_y1 = func.get_list_y1();
	vector<vector<int>> list_y2 = func.get_list_y2();
	vector<vector<int>> list_y3 = func.get_list_y3();
	vector<vector<int>> list_y4 = func.get_list_y4();
	func.gluing_elements(&list_y1);
	func.gluing_elements(&list_y2);
	func.gluing_elements(&list_y3);
	func.gluing_elements(&list_y4);

	cout << "\ny1:\n";
	func.print_method_sknf(list_y1);
	cout << "\ny2:\n";
	func.print_method_sknf(list_y2);
	cout << "\ny3:\n";
	func.print_method_sknf(list_y3);
	cout << "\ny4:\n";
	func.print_method_sknf(list_y4);
}