#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab4.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab4Tests
{
	TEST_CLASS(FunctionTests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Function func;
			bool result = func.fill_matrix();
			Assert::IsTrue(result);
			int num = func.get_ODS_3_matrix().size();
			Assert::AreEqual(5, num);
			num = func.get_ODS_3_matrix()[0].size();
			Assert::AreEqual(8, num);
		}

		TEST_METHOD(TestFillListsPS) {
			Function func;
			func.fill_matrix();
			func.print_matrix();
			Assert::IsTrue(func.fill_list_P());
			Assert::IsTrue(func.fill_list_S());
		}

		TEST_METHOD(TestPrintSKNF) {
			Function func;
			func.fill_matrix();
			func.print_matrix();
			func.fill_list_P();
			func.fill_list_S();
			Assert::IsTrue(func.print_method_sknf(func.get_list_P()));
			Assert::IsTrue(func.print_method_sknf(func.get_list_S()));
		}

		TEST_METHOD(TestGluingSKNF) {
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
			Assert::IsTrue(func.gluing_elements(&list_P));
			cout << "\nТКНФ P:\n";
			func.print_method_sknf(list_P);
			Assert::IsTrue(func.gluing_elements(&list_S));
			cout << "\nТКНФ S:\n";
			func.print_method_sknf(list_S);
		}

		TEST_METHOD(TestFillSynthesisMatrix) {
			Function func;
			Assert::IsTrue(func.fill_synthesis_matrix_little_subfunc());
			Assert::IsTrue(func.fill_result_synthesis_matrix());
			cout << "\nМатрица синтеза:\n";
			Assert::IsTrue(func.print_synthesis_matrix());
			Assert::IsTrue(func.fill_lists_synthesis_matrix());
		}

		TEST_METHOD(TestGetters) {
			Function func;
			Assert::IsTrue(func.fill_synthesis_matrix_little_subfunc());
			Assert::IsTrue(func.fill_result_synthesis_matrix());
			cout << "\nМатрица синтеза:\n";
			Assert::IsTrue(func.print_synthesis_matrix());
			Assert::IsTrue(func.fill_lists_synthesis_matrix());
			func.get_list_y1();
			func.get_list_y2();
			func.get_list_y3();
			func.get_list_y4();
		}
	};
}
