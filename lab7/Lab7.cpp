#include <iostream>
#include <string>
#include <vector>
#include "Matrix.cpp"

using namespace std;

int main() {
	system("chcp 1251");
	Matrix matr;

	matr.fill_word_matrix();
	matr.add_word_in_matrix(0, { 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0 });
	matr.add_word_in_matrix(1, { 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0 });
	matr.add_word_in_matrix(2, { 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1 });
	matr.add_word_in_matrix(3, { 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0 });
	matr.add_word_in_matrix(4, { 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1 });
	matr.add_word_in_matrix(5, { 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0 });
	matr.add_word_in_matrix(6, { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0 });
	matr.add_word_in_matrix(7, { 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 });
	matr.add_word_in_matrix(8, { 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0 });
	matr.add_word_in_matrix(9, { 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0 });
	matr.add_word_in_matrix(10, { 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0 });
	matr.add_word_in_matrix(11, { 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0 });
	matr.add_word_in_matrix(12, { 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0 });
	matr.add_word_in_matrix(13, { 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0 });
	matr.add_word_in_matrix(14, { 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0 });
	matr.add_word_in_matrix(15, { 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0 });

	matr.print_word_matrix();
	cout << endl << endl;

	matr.compare_min_word({ 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0 });
	matr.compare_max_word({ 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1 });
}