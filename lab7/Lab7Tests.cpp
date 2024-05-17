#include "pch.h"
#include "CppUnitTest.h"
#include "../Matrix.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab7Tests
{
	TEST_CLASS(Matrixtests)
	{
	public:
		
		TEST_METHOD(CheckSizeTest)
		{
			Matrix matr;
			matr.fill_word_matrix();
			int result = matr.get_word_matrix().size();
			Assert::AreEqual(result, 16);
		}

		TEST_METHOD(CheckPrintTest) {
			Matrix matr;
			matr.fill_word_matrix();
			matr.print_word_matrix();
		}

		TEST_METHOD(AddWordTest) {
			Matrix matr;
			matr.fill_word_matrix();
			bool bool_res = matr.add_word_in_matrix(16, { 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0 });
			Assert::IsFalse(bool_res);
			bool_res = matr.add_word_in_matrix(0, { 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0 });
			matr.add_word_in_matrix(7, { 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0 });
			matr.add_word_in_matrix(14, { 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0 });
			int result = matr.get_word_matrix()[0][14];
			Assert::IsTrue(bool_res);
			Assert::AreEqual(result, 1);
			result = matr.get_word_matrix()[7][5];
			Assert::AreEqual(result, 1);
			result = matr.get_word_matrix()[14][12];
			Assert::AreEqual(result, 1);
		}

		TEST_METHOD(AddColumnTest) {
			Matrix matr;
			matr.fill_word_matrix();
			bool bool_res = matr.add_adress_column(16, { 0, 1 });
			Assert::IsFalse(bool_res);
			bool_res = matr.add_adress_column(3, { 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0 });
			Assert::IsTrue(bool_res);
			Assert::AreEqual(matr.get_word_matrix()[0][3], 1);
			Assert::AreEqual(matr.get_word_matrix()[7][10], 0);
			Assert::AreEqual(matr.get_word_matrix()[15][2], 0);
		}

		TEST_METHOD(FindWordTest) {
			Matrix matr;
			matr.fill_word_matrix();
			matr.add_word_in_matrix(5, { 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0 });
			vector<int> temp_list = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
			vector<int> res_list = matr.find_word(0);
			Assert::AreEqual(res_list[5], temp_list[5]);
			temp_list = { 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0 };
			res_list = matr.find_word(5);
			Assert::AreEqual(res_list[7], temp_list[7]);
		}

		TEST_METHOD(FindColumnTest) {
			Matrix matr;
			matr.fill_word_matrix();
			matr.add_adress_column(3, { 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0 });
			Assert::AreEqual(matr.find_adress_column(3)[0], 1);
			Assert::AreEqual(matr.find_adress_column(3)[7], 0);
			Assert::AreEqual(matr.find_adress_column(3)[15], 0);
		}

		TEST_METHOD(MakeF1Test) {
			Matrix matr;
			matr.fill_word_matrix();
			matr.add_word_in_matrix(7, { 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0 });
			matr.add_adress_column(3, { 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0 });

			matr.make_f1(7, 3, 0);
			Assert::AreEqual(matr.get_word_matrix()[0][0], 1);
			Assert::AreEqual(matr.get_word_matrix()[0][5], 1);
			Assert::AreEqual(matr.get_word_matrix()[0][15], 0);
		}

		TEST_METHOD(MakeF3Test) {
			Matrix matr;
			matr.fill_word_matrix();
			matr.add_word_in_matrix(7, { 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0 });
			matr.add_adress_column(3, { 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0 });

			matr.make_f3(7, 3, 0);
			Assert::AreEqual(matr.get_word_matrix()[0][0], 1);
			Assert::AreEqual(matr.get_word_matrix()[0][5], 1);
			Assert::AreEqual(matr.get_word_matrix()[0][15], 0);
		}

		TEST_METHOD(MakeF12Test) {
			Matrix matr;
			matr.fill_word_matrix();
			matr.add_word_in_matrix(7, { 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0 });
			matr.add_adress_column(3, { 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0 });

			matr.make_f12(7, 3, 0);
			Assert::AreEqual(matr.get_word_matrix()[0][0], 0);
			Assert::AreEqual(matr.get_word_matrix()[0][5], 0);
			Assert::AreEqual(matr.get_word_matrix()[0][15], 1);
		}

		TEST_METHOD(MakeF14Test) {
			Matrix matr;
			matr.fill_word_matrix();
			matr.add_word_in_matrix(7, { 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0 });
			matr.add_adress_column(3, { 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0 });

			matr.make_f14(7, 3, 0);
			Assert::AreEqual(matr.get_word_matrix()[0][0], 0);
			Assert::AreEqual(matr.get_word_matrix()[0][5], 0);
			Assert::AreEqual(matr.get_word_matrix()[0][15], 1);
		}

		TEST_METHOD(SumNumbersTest) {
			Matrix matr;
			vector<int> res_list = matr.sum_numbers({ 1, 1, 0, 1 }, {0, 0, 1, 0});
			vector<int> need_list = { 1, 1, 1, 1 };
			for (int i = 0; i < res_list.size(); i++) {
				Assert::AreEqual(res_list[i], need_list[i]);
			}

			res_list = matr.sum_numbers({ 0, 1, 1, 1, 0 }, { 1, 1, 1, 1, 0 });
			need_list = { 1, 0, 1, 1, 0, 0 };
			for (int i = 0; i < res_list.size(); i++) {
				Assert::AreEqual(res_list[i], need_list[i]);
			}
		}

		TEST_METHOD(FindAllWordsVTest) {
			Matrix matr;
			matr.fill_word_matrix();
			matr.add_word_in_matrix(0, { 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
			matr.add_word_in_matrix(10, { 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });

			bool result = matr.find_all_words_V("101");
			Assert::IsFalse(result);

			result = matr.find_all_words_V("111");
			Assert::IsTrue(result);
		}

		TEST_METHOD(Transfer10To2Test) {
			Matrix matr;
			string result = matr.transfer_10_to_2(3);
			string need_res = "11";
			Assert::AreEqual(result, need_res);
		}

		TEST_METHOD(Transfer2To10Test) {
			Matrix matr;
			int result = matr.transfer_2_to_10("11");
			int need_res = 3;
			Assert::AreEqual(result, need_res);
		}

		TEST_METHOD(FindMinWordTest) {
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

			vector<int> res_list = matr.find_min_word({ 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0 });
			vector<int> need_list = { 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0 };

			for (int i = 0; i < need_list.size(); i++) {
				Assert::AreEqual(res_list[i], need_list[i]);
			}
		}

		TEST_METHOD(FindMaxWordTest) {
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

			vector<int> res_list = matr.find_max_word({ 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0 });
			vector<int> need_list = { 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0 };

			for (int i = 0; i < need_list.size(); i++) {
				Assert::AreEqual(res_list[i], need_list[i]);
			}
		}

		TEST_METHOD(CompareMinMaxWordTest) {
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

			matr.compare_min_word({ 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1 });
			matr.compare_max_word({ 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1 });

			vector<int> min_word = matr.find_min_word({ 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0 });
			int result = matr.calculate_final_g_l({ 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0 }, min_word);
			Assert::AreEqual(result, 1);

			min_word = matr.find_min_word({ 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1 });
			result = matr.calculate_final_g_l({ 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1 }, min_word);
			Assert::AreEqual(result, 3);

			vector<int> max_word = matr.find_max_word({ 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1 });
			result = matr.calculate_final_g_l({ 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1 }, max_word);
			Assert::AreEqual(result, 2);



		}
	};
}
