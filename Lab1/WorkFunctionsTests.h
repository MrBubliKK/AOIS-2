#pragma once
#include "pch.h"
#include "CppUnitTest.h"
#include "PointNumbersTests.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WorkFunctionstests
{
	TEST_CLASS(WorkFunctionsTests)
	{
	public:

		TEST_METHOD(sum_int_num_test) {
			Massive one(23);
			Massive two(19);
			Massive three(-89);
			Massive four(18);
			Massive five(126);
			bool res = sum_numbers(&one, &two);
			Assert::IsTrue(res);
			res = sum_numbers(&one, &two);
			Assert::IsTrue(res);
			res = sum_numbers(&five, &four);
			Assert::IsTrue(res);
		}

		TEST_METHOD(composition_test) {
			Massive one(34);
			Massive two(-19);
			one.make_transfer_number();
			two.make_transfer_number();
			bool res = composition_numbers(&one, &two);
			Assert::IsTrue(res);
		}

		TEST_METHOD(division_number_test) {
			Massive one(45);
			Massive two(-18);
			one.transfer_direct(one.get_num());
			two.transfer_direct(two.get_num());
			bool res = division_numbers(&one, &two);
			Assert::IsTrue(res);
		}

		TEST_METHOD(sum_point_numbers_test) {
			PointNumber one(13.45);
			PointNumber two(-12.54);
			one.transfer_direct();
			two.transfer_direct();
			sum_point_numbers(&one, &two);
		}

		TEST_METHOD(transfer_point_number_test) {
			PointNumber one(32.625);
			PointNumber two(12.5);
			one.transfer_direct();
			two.transfer_direct();
			bool res = sum_transfer_ieee754(&one, &two);
			Assert::IsTrue(res);
		}
};
}
