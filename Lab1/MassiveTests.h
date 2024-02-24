#pragma once
#include "pch.h"
#include "CppUnitTest.h"
#include "../WorkFunctions.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MassiveTests
{
	TEST_CLASS(MassiveTests)
	{
	public:

		TEST_METHOD(transfer_direct_test) {
			Massive one(3);
			one.transfer_direct(one.get_num());
			Massive two(-4);
			two.transfer_direct(two.get_num());
		}

		TEST_METHOD(transfer_reverse_test) {
			Massive one(4);
			one.transfer_direct(one.get_num());
			one.transfer_reverse();
		}

		TEST_METHOD(transfer_additional_test) {
			Massive one(-4);
			one.transfer_direct(one.get_num());
			one.transfer_reverse();
			one.transfer_additional();
		}

		TEST_METHOD(transfer_direct_op_test) {
			Massive one(-5);
			one.transfer_direct_op(one.get_num());
		}

		TEST_METHOD(transfer_reverse_op_test) {
			Massive one(-4);
			one.transfer_direct_op(one.get_num());
			one.transfer_reverse_op();
		}

		TEST_METHOD(transfer_additional_op_test) {
			Massive one(-4);
			one.transfer_direct_op(one.get_num());
			one.transfer_reverse_op();
			one.transfer_additional_op();
		}

		TEST_METHOD(make_transfer_number_test) {
			Massive one(-4);
			one.transfer_direct_op(one.get_num());
			one.transfer_reverse_op();
			one.transfer_additional_op();
			one.make_transfer_number();

			Massive two(4);
			two.transfer_direct_op(two.get_num());
			two.transfer_reverse_op();
			two.transfer_additional_op();
			two.make_transfer_number();
		}

		TEST_METHOD(get_transfer_mas_test) {
			Massive one(-4);
			one.transfer_direct_op(one.get_num());
			one.transfer_reverse_op();
			one.transfer_additional_op();
			one.make_transfer_number();
			Assert::AreEqual(one.get_transfer_mas()[7], 0);
		}

		TEST_METHOD(get_direct_mas_test) {
			Massive one(4);
			one.transfer_direct(one.get_num());
			Assert::AreEqual(one.get_direct_mas()[1], 1);
		}

		TEST_METHOD(get_reverse_test) {
			Massive one(4);
			one.transfer_direct(one.get_num());
			one.transfer_reverse();
			Assert::AreEqual(one.get_reverse_mas()[1], 0);
		}

		TEST_METHOD(get_additional_test) {
			Massive one(4);
			one.transfer_direct(one.get_num());
			one.transfer_reverse();
			one.transfer_additional();
			Assert::AreEqual(one.get_additional_mas()[1], 1);
		}

		TEST_METHOD(reverse_transfer_test) {
			Massive one(-4);
			one.transfer_direct_op(one.get_num());
			one.transfer_reverse_op();
			one.transfer_additional_op();
			one.make_transfer_number();
			one.reverse_transfer();
			Assert::AreEqual(one.get_transfer_mas()[0], 0);
		}

		TEST_METHOD(reverse_mas_test) {
			Massive one(4);
			one.transfer_direct(one.get_num());
			one.transfer_reverse();
			one.transfer_additional();
			one.reverse_direct();
			one.reverse_reverse();
			one.reverse_additional();
			Assert::AreEqual(one.get_direct_mas()[0], 0);
			Assert::AreEqual(one.get_reverse_mas()[0], 1);
			Assert::AreEqual(one.get_additional_mas()[0], 0);
		}

		TEST_METHOD(push_mas_test) {
			Massive one(4);
			one.transfer_direct(one.get_num());
			one.transfer_reverse();
			one.transfer_additional();
			one.push_direct(2);
			one.push_reverse(2);
			one.push_additional(2);
			Assert::AreEqual(one.get_direct_mas()[4], 2);
			Assert::AreEqual(one.get_reverse_mas()[4], 2);
			Assert::AreEqual(one.get_additional_mas()[4], 2);
			one.print_direct_mas();
			one.print_reverse_mas();
			one.print_additional_mas();
			one.print_transfer_mas();
		}
	};
}
