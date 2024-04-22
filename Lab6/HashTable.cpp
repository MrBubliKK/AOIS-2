#include <vector>
#include <string>
#include <iostream>
#include "Element.cpp"
using namespace std;

class HashTable {
private:
	vector<Element> hash_table;

public:
	vector<Element> get_hash_table() {
		return hash_table;
	}
	
	void create_hash_table() {
		for (int i = 0; i < 20; i++) {
			hash_table.push_back(Element("", ""));
		}
	}

	int to_lower(char letter) {
		if (letter >= 'А' && letter <= 'Я') {
			return letter + 32;
		}
		else if (letter >= 'а' && letter <= 'я') {
			return letter;
		}
		else return -100;
	}

	int get_position_alphabet(char letter) {
		// Приводим букву к нижнему регистру для удобства работы с алфавитом
		letter = to_lower(letter);

		// Проверяем, является ли символ русской буквой
		if (letter < 'а' || letter > 'я') {
			cout << "Это не русская буква!\n";
			return -1; // Возвращаем -1 в случае неверного символа
		}

		// Возвращаем позицию буквы в алфавите (от 1 до 33)
		if (letter >= 'а' && letter <= 'е') {
			return letter - 'а';
		}
		else {
			return letter - 'а' + 1;
		}
	}

	int calculate_V(string id) {
		char first = id[0];
		char second = id[1];
		int first_num = get_position_alphabet(first);
		int second_num = get_position_alphabet(second);
		return first_num * 33 + second_num * 1;
	}

	int calculate_h(string id) {
		int V = calculate_V(id);
		return V % 20;
	}

	//Проверяет, есть ли элемент в цепочке
	bool check_exist_el_in_chain(Element el, Element hash_el) {
		Element exist_el = hash_el;
		while (exist_el.get_next() != nullptr) {
			if ((exist_el.get_id() == el.get_id()) && (exist_el.get_U() == 1)) {
				return true;
			}
			exist_el = *exist_el.get_next();
		}

		if ((exist_el.get_id() == el.get_id()) && (exist_el.get_U() == 1)) {
			return true;
		}
		return false;
	}


	void correct_settings_elements_in_add(Element* new_element, Element* exist_el) {
		new_element->set_U(1);
		new_element->set_D(0);
		new_element->set_prev(exist_el->get_prev());
		if (exist_el->get_next()->get_U() == 0) {
			new_element->set_T(1);
		}
		//exist_el->set_T(13);
		new_element->set_next(exist_el->get_next());
		new_element->get_prev()->set_next(new_element);
		new_element->get_next()->set_prev(new_element);

		Element* start_el = &hash_table[new_element->get_h()];
		Element* chain_el = hash_table[new_element->get_h()].get_next();
		if (chain_el->get_id() == exist_el->get_id()) {
			chain_el = new_element;
		}
		start_el->set_next(chain_el);
		while (chain_el->get_next() != nullptr) {
			if (chain_el->get_id() == exist_el->get_id()) {
				chain_el = new_element;
			}
			chain_el = chain_el->get_next();
		}
		hash_table[new_element->get_h()] = *start_el;
	}

	void correct_start_settings_el_add(Element* new_element, Element* exist_el) {
		new_element->set_U(1);
		new_element->set_D(0);
		new_element->set_C(1);
		if (exist_el->get_next() == nullptr) {
			new_element->set_T(1);
		}
		else if (exist_el->get_next()->get_U() == 0) {
			new_element->set_T(1);
			new_element->set_next(exist_el->get_next());
			new_element->get_next()->set_prev(new_element);
		}
		else {
			new_element->set_next(exist_el->get_next());
			new_element->get_next()->set_prev(new_element);
		}
	}

	void correct_final_settings_el_add(Element* new_element, Element* exist_el) {
		Element* start_el = &hash_table[new_element->get_h()];
		Element* chain_el = hash_table[new_element->get_h()].get_next();

		new_element->set_U(1);
		new_element->set_D(0);
		new_element->set_prev(exist_el->get_prev());
		exist_el->get_prev()->set_next(new_element);

		if (chain_el->get_id() == exist_el->get_id()) {
			chain_el = new_element;
		}

		start_el->set_next(chain_el);
		while (chain_el->get_next() != nullptr) {
			chain_el = chain_el->get_next();
		}
		chain_el = new_element;
		hash_table[new_element->get_h()] = *start_el;
	}

	//Добавляем элемент в конец цепочки
	void add_el_in_chain(string id, string Pi) {
		Element* new_element = new Element(id, Pi); // Динамически выделяем память
		new_element->set_V(calculate_V(id));
		new_element->set_h(calculate_h(id));
		Element* exist_el = &hash_table[new_element->get_h()];
		int count = 0;
		while (exist_el->get_next() != nullptr) {
			//Если какая-то ячейка пустая, добавляем в нее
			if ((exist_el->get_U() == 0) && (count == 0)) {
				correct_start_settings_el_add(new_element, exist_el);
				hash_table[calculate_h(id)] = *new_element;
				return;
			}
			else if ((exist_el->get_U() == 0) && (count > 0)) {
				correct_settings_elements_in_add(new_element, exist_el);
				return;
			}
			//Иначе идем в конец цепочки и добавляем туда
			exist_el = exist_el->get_next();
			count++;
		}
		if (exist_el->get_U() == 0) {
			correct_final_settings_el_add(new_element, exist_el);
			return;
		}
		exist_el->set_Po(count + 1);
		exist_el->set_T(0);
		new_element->set_T(1);
		new_element->set_U(1);
		exist_el->set_next(new_element);
		new_element->set_prev(exist_el);
	}

	//Общий метод добавления
	bool add_element(string id, string Pi) {
		Element el(id, Pi);
		el.set_V(calculate_V(id));
		el.set_h(calculate_h(id));

		//Проверка на существование элемента
		if (check_exist_el_in_chain(el, hash_table[el.get_h()])) {
			cout << "Такой элемент уже есть.\n";
			return false;
		}

		//Проверка 
		if ((hash_table[el.get_h()].get_U() == 0) && (hash_table[el.get_h()].get_next() == nullptr)) {
			el.set_U(1);
			el.set_C(1);
			el.set_T(1);
			el.set_Po(-1);
			hash_table[el.get_h()] = el;
		}
		else {
			add_el_in_chain(id, Pi);
		}
		return true;
	}

	//Поиск элемента
	bool search_element(string id) {
		int h = calculate_h(id);
		
		//Прогоняем цепочку до конца, чтобы найти элемент
		Element* exist_el = &hash_table[h];
		while (exist_el->get_next() != nullptr) {
			if (exist_el->get_id() == id) {
				cout << "• " << exist_el->get_Pi() << endl;
				return true;
			}
			exist_el = exist_el->get_next();
		}

		if (exist_el->get_id() == id) {
			cout << "• " << exist_el->get_Pi() << endl;
			return true;
		}
		else {
			cout << "• Такого элемента нет.\n";
			return false;
		}
	}

	//Выводит элементы определенной цепочки
	void print_chain_in_table(Element el) {
		Element* exist_el = &el;
		while (exist_el->get_next() != nullptr) {
			if (exist_el->get_U() != 0) {
				cout << exist_el->get_id() << " - " << exist_el->get_Pi() << endl;
			}
			else {
				cout << "Пустое звено цепочки\n";
			}
			exist_el = exist_el->get_next();
		}
		if (exist_el->get_U() != 0) {
			cout << exist_el->get_id() << " - " << exist_el->get_Pi() << endl;
		}
		else {
			cout << "Пустое звено цепочки\n";
		}
	}

	//Выводит элементы все таблицы
	void print_all_table() {
		for (int i = 0; i < hash_table.size(); i++) {
			cout << "\n-------ЯЧЕЙКА " << i << "-------\n";
			if ((hash_table[i].get_U() == 0) && (hash_table[i].get_next() == nullptr)) {
				cout << "Пустая ячейка\n";
			}
			else {
				print_chain_in_table(hash_table[i]);
			}
		}
	}

	void correct_settings_in_del(Element* del_el) {

	}

	bool delete_el_in_table(string id) {
		int h = calculate_h(id);
		Element* del_el = &hash_table[h];
		int count = 0;
		while (del_el->get_next() != nullptr) {
			if (del_el->get_id() == id) {
				del_el->set_U(0);
				del_el->set_D(1);
				if (count == 0) {
					del_el->set_C(0);
					del_el->get_next()->set_C(1);
				}
				else {
					del_el->get_prev()->set_T(1);
					del_el->get_next()->set_C(1);
				}
				return true;
			}
			del_el = del_el->get_next();
			count++;
		}

		if (del_el->get_id() == id) {
			del_el->set_U(0);
			del_el->set_D(1);
			if (count == 0) {
				del_el->set_C(0);
				del_el->set_T(0);
			}
			else {
				del_el->set_T(0);
				del_el->get_prev()->set_T(1);
			}
			return true;
		}
		return false;
	}
};