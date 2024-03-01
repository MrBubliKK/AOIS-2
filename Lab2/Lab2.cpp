#include <iostream>
#include <vector>
#include <string>
#include "Function.cpp"
using namespace std;

int main() {
	system("chcp 1251");
	int num = 2;
	// x7~(x6~((((x5+x3)>(x2+x1))~(((x1'+x2')'>x3)~x4))+x5'))+(x9'>(x7*x8))'>(x6~((((x5+x3)>(x2+x1))~(((x1'+x2')'>x3)~x4))+x5'))+(x9'>(x7*x8))'
	// ((x1+x2)*x3)>(x4~x5)'
	Function func = Function("(x1>x2)+(x1>(x2*x1))", num);
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
}