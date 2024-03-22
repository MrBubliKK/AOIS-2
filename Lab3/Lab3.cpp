#include <iostream>
#include <vector>
#include <string>
#include "Function.cpp"
using namespace std;

int main() {
	system("chcp 1251");
	int num = 3;
	// x7~(x6~((((x5+x3)>(x2+x1))~(((x1'+x2')'>x3)~x4))+x5'))+(x9'>(x7*x8))'>(x6~((((x5+x3)>(x2+x1))~(((x1'+x2')'>x3)~x4))+x5'))+(x9'>(x7*x8))'
	// ((x1+x2)*x3)>(x4~x5)'
	Function func = Function("(x1+(x2*x3))", num);
	func.find_all_signs();
	func.find_all_subfuncs(num);
	func.fill_little_subfunc(num);
	func.print_subfuncs_with_parts();
	func.add_in_matrix_all_subfuncs(num);
	func.print_list_func();
	func.fill_all_subfuncs(num);
	func.print_matrix();
	func.print_sdnf(num);
	func.print_sknf(num);
	func.print_index_form();

	vector<vector<int>> list_elements_sdnf;  // Получаем список элементов
	func.gluing_elements(&list_elements_sdnf, 1);
	func.delete_unnecessary_elements(&list_elements_sdnf);
	cout << "\n----------------------\n";
	cout << "\nРасчетный метод СДНФ:\n";
	func.print_method(list_elements_sdnf, 1);
	cout << "\n----------------------\n";

	vector<vector<int>> list_elements_sknf;  // Получаем список элементов
	func.gluing_elements(&list_elements_sknf, 0);
	func.delete_unnecessary_elements(&list_elements_sknf);
	cout << "\n----------------------\n";
	cout << "\nРасчетный метод СКНФ:\n";
	func.print_method(list_elements_sknf, 0);
	cout << "\n----------------------\n";

	vector<vector<int>> table_math_list_sdnf;
	func.make_table_elements(&table_math_list_sdnf, 1);
	cout << "\n----------------------\n";
	cout << "\nТаблично-расчетный метод СДНФ:\n";
	func.print_method(table_math_list_sdnf, 1);
	cout << "\n----------------------\n";

	vector<vector<int>> table_math_list_sknf;
	func.make_table_elements(&table_math_list_sknf, 0);
	cout << "\n----------------------\n";
	cout << "\nТаблично-расчетный метод СКНФ:\n";
	func.print_method(table_math_list_sknf, 0);
	cout << "\n----------------------\n";

	cout << "\n----------------------\n";
	cout << "\nТаблица Карно для СДНФ и СКНФ:\n";
	func.print_karno_table(num);
	func.print_table_answer();
	cout << "\n----------------------\n";

}
