#pragma once
#include "pch.h"
#include "CppUnitTest.h"
#include "../Function.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FunctionTests
{
	TEST_CLASS(FunctionTests)
	{
	public:

		TEST_METHOD(TestFinderSign)
		{
			Function func("x1+x2", 2);
			bool res = func.find_all_signs();
			Assert::IsTrue(res);
		}

		TEST_METHOD(TestMakerLeftPart) {
			Function func("(x1+x2')+x1", 2);
			int pos = 7;
			string subfunc = "";
			string left_part_subfunc = "";
			int bracket = 0;
			bool res = func.make_left_part_subfunc(&pos, &subfunc, &left_part_subfunc, &bracket);
			Assert::IsTrue(res);
			Function func2("(x1+x2')'", 2);
			pos = 6;
			res = func2.make_left_part_subfunc(&pos, &subfunc, &left_part_subfunc, &bracket);
			Assert::IsTrue(res);
			Function fun3("(x3'", 1);
			pos = 3;
			res = fun3.make_left_part_subfunc(&pos, &subfunc, &left_part_subfunc, &bracket);
			Assert::IsTrue(res);
		}

		TEST_METHOD(TestMakerRightPart) {
			Function func("(x1+x2')+x1", 2);
			int pos = 0;
			string subfunc = "";
			string right_part_subfunc = "";
			int bracket = 0;
			bool res = func.make_right_part_subfunc(&pos, &subfunc, &right_part_subfunc, &bracket);
			Assert::IsTrue(res);
			Function func2("(x1+x2')'", 2);
			pos = 1;
			res = func2.make_right_part_subfunc(&pos, &subfunc, &right_part_subfunc, &bracket);
			Assert::IsTrue(res);
		}

		TEST_METHOD(TEstsAlignBracket) {
			Function func1("((x1+x2)", 2);
			Function func2("(x1+x2))", 2);

			string subfunc = "((x1 + x2)";
			int open_num = 0;
			int close_num = 0;

			bool res = func1.align_brackets(&subfunc, &open_num, &close_num);
			Assert::IsTrue(res);

			subfunc = "(x1 + x2))";
			open_num = 0;
			close_num = 0;

			res = func2.align_brackets(&subfunc, &open_num, &close_num);
			Assert::IsTrue(res);
		}

		TEST_METHOD(TestMakeAdditionalBrackets) {
			Function func("x1+x2", 2);
			string subfunc = "";
			string left_part_subfunc = "(())";
			string right_part_subfunc = "(())";
			int left_open_close_num = 0;
			int right_open_close_num = 0;
			bool res = func.make_additional_brackets(&subfunc, &left_part_subfunc, &right_part_subfunc, &left_open_close_num, &right_open_close_num);
			Assert::IsTrue(res);
		}

		TEST_METHOD(TestMakeDenialSubfunc) {
			Function func("(())", 2);
			string subfunc = "";
			int left_pos = 3;
			string left_part_subfunc = "";
			int count_bracket = 0;
			bool res = func.make_denial_subfunc(&left_pos, &count_bracket, &subfunc, &left_part_subfunc);
			Assert::IsTrue(res);

			Function func2("x2", 1);
			left_pos = 1;
			res = func.make_denial_subfunc(&left_pos, &count_bracket, &subfunc, &left_part_subfunc);
			Assert::IsTrue(res);
		}

		TEST_METHOD(TestFindAllSubfuncs) {
			int num = 5;
			Function func = Function("((x1+x2)*x3)>(x4~x5)'", num);
			func.find_all_signs();
			bool res = func.find_all_subfuncs(num);
			Assert::IsTrue(res);

			res = func.print_all_subfuncs();
			Assert::IsTrue(res);
			res = func.print_subfuncs_with_parts();
			Assert::IsTrue(res);
		}

		TEST_METHOD(TestTransfer) {
			Function func("X1+x2", 2);
			int decimal_num = 2;
			string binary_num = func.transfer_10_to_2(decimal_num);
			string res = "10";
			Assert::AreEqual(binary_num, res);
			decimal_num = func.transfer_2_to_10(binary_num);
			Assert::AreEqual(decimal_num, 2);
		}

		TEST_METHOD(TestAddInMatrix) {
			int num = 5;
			Function func = Function("((x1+x2)*x3)>(x4~x5)'", num);
			func.find_all_signs();
			func.find_all_subfuncs(num);
			func.fill_little_subfunc(num);
			func.print_subfuncs_with_parts();
			bool res = func.add_in_matrix_all_subfuncs(num);
			Assert::IsTrue(res);
		}

		TEST_METHOD(TestFillSubfuncs) {
			int num = 5;
			Function func = Function("((x1+x2)*x3)>(x4~x5)'", num);
			func.find_all_signs();
			func.find_all_subfuncs(num);
			func.fill_little_subfunc(num);
			func.print_subfuncs_with_parts();
			func.add_in_matrix_all_subfuncs(num);
			func.print_list_func();
			bool res = func.fill_all_subfuncs(num);
			Assert::IsTrue(res);
		}

		TEST_METHOD(TestPrint) {
			int num = 5;
			Function func = Function("((x1+x2)*x3)>(x4~x5)'", num);
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
			bool res = func.print_index_form();
			Assert::IsTrue(res);
		}

		TEST_METHOD(test_check_empty_sknf) {
			int num = 3;
			Function func = Function("(x1+(x2*x3))", num);
			func.find_all_signs();
			func.find_all_subfuncs(num);
			func.fill_little_subfunc(num);
			func.print_subfuncs_with_parts();
			func.add_in_matrix_all_subfuncs(num);
			func.print_list_func();
			func.fill_all_subfuncs(num);
			Assert::IsTrue(func.check_empty_sknf());
		}

		TEST_METHOD(test_check_empty_sdnf) {
			int num = 3;
			Function func = Function("(x1+(x2*x3))", num);
			func.find_all_signs();
			func.find_all_subfuncs(num);
			func.fill_little_subfunc(num);
			func.print_subfuncs_with_parts();
			func.add_in_matrix_all_subfuncs(num);
			func.print_list_func();
			func.fill_all_subfuncs(num);
			Assert::IsTrue(func.check_empty_sdnf());
		}

		TEST_METHOD(test_fill_list_elements) {
			int num = 3;
			Function func = Function("(x1+(x2*x3))", num);
			func.find_all_signs();
			func.find_all_subfuncs(num);
			func.fill_little_subfunc(num);
			func.print_subfuncs_with_parts();
			func.add_in_matrix_all_subfuncs(num);
			func.print_list_func();
			func.fill_all_subfuncs(num);
			vector<vector<int>> list_el_sdnf;
			vector<vector<int>> list_el_sknf;
			vector<vector<int>> del_list;
			Assert::IsTrue(func.fill_list_elements(&list_el_sdnf, 1));
			Assert::IsTrue(func.fill_list_elements(&list_el_sknf, 0));
			Assert::IsFalse(func.fill_list_elements(&del_list, 2));
		}

		TEST_METHOD(test_check_exist_element) {
			int num = 3;
			Function func = Function("(x1+(x2*x3))", num);
			vector<vector<int>> main_list = { {1, 2, 3}, {2, 3, 4}, {3, 4, 5} };
			vector<int> true_list = { 1, 2, 3 };
			vector<int> false_list = { 1, 3, 4 };

			Assert::IsTrue(func.check_exist_element(true_list, main_list));
			Assert::IsFalse(func.check_exist_element(false_list, main_list));
		}

		TEST_METHOD(test_check_exist_delete_element) {
			int num = 3;
			Function func = Function("(x1+(x2*x3))", num);
			vector<vector<int>> main_list = { {1, 2, 3}, {2, 3, 4}, {3, 4, 5} };
			vector<int> true_list = { 1, 2, 3 };
			vector<int> false_list = { 1, 3, 4 };
			vector<vector<int>> false_main_list = {};

			Assert::IsTrue(func.check_exist_delete_element(true_list, main_list));
			Assert::IsFalse(func.check_exist_delete_element(false_list, main_list));
			Assert::IsFalse(func.check_exist_delete_element(true_list, false_main_list));
		}

		TEST_METHOD(test_equall_elements) {
			int num = 3;
			Function func = Function("(x1+(x2*x3))", num);

			vector<vector<int>> main_list = { {1, 2, 3}, {-1, 2, 3}, {2, 3, 4} };
			Assert::IsTrue(func.equall_elements(0, 1, main_list));
			Assert::IsFalse(func.equall_elements(0, 2, main_list));
		}

		TEST_METHOD(test_gluing_elements) {
			int num = 3;
			Function func = Function("(x1+(x2*x3))", num);
			func.find_all_signs();
			func.find_all_subfuncs(num);
			func.fill_little_subfunc(num);
			func.print_subfuncs_with_parts();
			func.add_in_matrix_all_subfuncs(num);
			func.print_list_func();
			func.fill_all_subfuncs(num);

			vector<vector<int>> main_list;
			Assert::IsTrue(func.gluing_elements(&main_list, 1));
		}

		TEST_METHOD(test_delete_unnecessary_elements) {
			int num = 3;
			Function func = Function("(x1+(x2*x3))", num);
			func.find_all_signs();
			func.find_all_subfuncs(num);
			func.fill_little_subfunc(num);
			func.print_subfuncs_with_parts();
			func.add_in_matrix_all_subfuncs(num);
			func.print_list_func();
			func.fill_all_subfuncs(num);

			vector<vector<int>> main_list;
			func.gluing_elements(&main_list, 1);
			Assert::IsTrue(func.delete_unnecessary_elements(&main_list));
			vector<vector<int>> small_list = {};
			Assert::IsFalse(func.delete_unnecessary_elements(&small_list));
		}

		TEST_METHOD(test_printing_math_method) {
			int num = 3;
			Function func = Function("(x1+(x2*x3))", num);
			func.find_all_signs();
			func.find_all_subfuncs(num);
			func.fill_little_subfunc(num);
			func.print_subfuncs_with_parts();
			func.add_in_matrix_all_subfuncs(num);
			func.print_list_func();
			func.fill_all_subfuncs(num);

			vector<vector<int>> list_elements_sdnf;  // Получаем список элементов
			func.gluing_elements(&list_elements_sdnf, 1);
			func.delete_unnecessary_elements(&list_elements_sdnf);
			Assert::IsTrue(func.print_method(list_elements_sdnf, 1));

			vector<vector<int>> list_elements_sknf;  // Получаем список элементов
			func.gluing_elements(&list_elements_sknf, 0);
			func.delete_unnecessary_elements(&list_elements_sknf);
			Assert::IsTrue(func.print_method(list_elements_sknf, 0));

			Assert::IsFalse(func.print_method(list_elements_sdnf, 2));
		}

		TEST_METHOD(test_table_math_method) {
			int num = 3;
			Function func = Function("(x1+(x2*x3))", num);
			func.find_all_signs();
			func.find_all_subfuncs(num);
			func.fill_little_subfunc(num);
			func.print_subfuncs_with_parts();
			func.add_in_matrix_all_subfuncs(num);
			func.print_list_func();
			func.fill_all_subfuncs(num);

			vector<vector<int>> table_math_list_sdnf;
			func.make_table_elements(&table_math_list_sdnf, 1);
			Assert::IsTrue(func.print_method(table_math_list_sdnf, 1));

			vector<vector<int>> table_math_list_sknf;
			func.make_table_elements(&table_math_list_sknf, 0);
			Assert::IsTrue(func.print_method(table_math_list_sknf, 0));
		}

		TEST_METHOD(test_check_table_method) {
			int num = 3;
			Function func = Function("(x1+(x2*x3))", num);
			func.find_all_signs();
			func.find_all_subfuncs(num);
			func.fill_little_subfunc(num);
			func.print_subfuncs_with_parts();
			func.add_in_matrix_all_subfuncs(num);
			func.print_list_func();
			func.fill_all_subfuncs(num);

			func.print_karno_table(num);
			Assert::IsTrue(func.print_table_answer());
		}

	};
}