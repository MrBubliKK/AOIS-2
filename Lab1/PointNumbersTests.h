#pragma once
#include "pch.h"
#include "CppUnitTest.h"
#include "MassiveTests.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PointNumbersTests
{
	TEST_CLASS(PointNumbersTests)
	{
	public:

		TEST_METHOD(transfer_firect_test) {
			PointNumber one(23.45);
			one.transfer_direct();
			string num = one.get_direct_mas()[2];
			string res = "0";
			Assert::AreEqual(num, res);
		}

		TEST_METHOD(func_test) {
			PointNumber one(23.45);
			one.transfer_direct();
			one.push_direct("1");
			one.reverse_direct();
			one.print_direct_mas();
		}
	};
}
