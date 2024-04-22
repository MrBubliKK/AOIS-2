#include "pch.h"
#include "CppUnitTest.h"
#include "../HashTable.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab6Tests
{
	TEST_CLASS(HashTableTests)
	{
	public:
		
		TEST_METHOD(create_table_test)
		{
			HashTable ht;
			ht.create_hash_table();
			
			string id = "";
			string Pi = "";

			ht.get_hash_table()[1].set_h(1);
			ht.get_hash_table()[1].set_V(19);
			ht.get_hash_table()[1].set_prev(&Element("", ""));
			ht.get_hash_table()[1].set_next(&Element("", ""));
			ht.get_hash_table()[1].set_C(1);
			ht.get_hash_table()[1].set_U(1);
			ht.get_hash_table()[1].set_T(1);
			ht.get_hash_table()[1].set_D(1);
			ht.get_hash_table()[1].set_Po(1);

			Assert::AreEqual(ht.get_hash_table()[0].get_id(), id);
			Assert::AreEqual(ht.get_hash_table()[0].get_V(), -1);
			Assert::AreEqual(ht.get_hash_table()[0].get_h(), -1);
			Assert::AreEqual(ht.get_hash_table()[0].get_C(), 0);
			Assert::AreEqual(ht.get_hash_table()[0].get_U(), 0);
			Assert::AreEqual(ht.get_hash_table()[0].get_T(), 0);
			Assert::AreEqual(ht.get_hash_table()[0].get_L(), 0);
			Assert::AreEqual(ht.get_hash_table()[0].get_D(), 0);
			Assert::AreEqual(ht.get_hash_table()[0].get_Po(), -1);
			Assert::AreEqual(ht.get_hash_table()[0].get_Pi(), Pi);
		}

		TEST_METHOD(calculate_V_test) {
			HashTable ht;
			int V = ht.calculate_V("Дом");
			Assert::AreEqual(V, 147);
		}

		TEST_METHOD(get_letter_test) {
			HashTable ht;
			Assert::AreEqual(ht.to_lower('d'), -100);
			Assert::AreEqual(ht.get_position_alphabet('g'), -1);
		}

		TEST_METHOD(calculate_h_test) {
			HashTable ht;
			int h = ht.calculate_h("Дом");
			Assert::AreEqual(h, 7);
		}

		TEST_METHOD(add_el_test) {
			HashTable ht;
			ht.create_hash_table();
			Assert::IsTrue(ht.add_element("Ковбой", "1234"));
			Assert::IsFalse(ht.add_element("Ковбой", "1234"));
			Assert::IsTrue(ht.add_element("Кобас", "1234"));
		}

		TEST_METHOD(add_start_end_el_test) {
			HashTable ht;
			ht.create_hash_table();
			ht.add_element("Ковбой", "1234");
			ht.add_element("Кобас", "1234");

			ht.delete_el_in_table("Ковбой");
			ht.add_element("Ковбой", "2134");

			ht.delete_el_in_table("Кобас");
			ht.add_element("Кобас", "2134");

			ht.add_element("Колбаса", "1234");
			ht.delete_el_in_table("Кобас");
			ht.add_element("Кобас", "2134");
		}

		TEST_METHOD(print_test) {
			HashTable ht;
			ht.create_hash_table();
			ht.add_element("Ковбой", "1234");
			ht.print_chain_in_table(ht.get_hash_table()[18]);
			ht.print_all_table();
		}
	};
}
