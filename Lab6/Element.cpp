#include <vector>
#include <string>
#include <cctype>
#include <iostream>
using namespace std;

class Element {
private:
	string id = ""; //�������������
	int V = -1; //�������� ��������
	int h = -1; //���-�����
	int C = 0; //������ ��������
	int U = 0; //������ "������"
	int T = 0; //������������ ������
	int L = 0; //������ �����
	int D = 0; //������ ������������
	int Po = -1; //��������� �� ���� �������
	string Pi = ""; //��������
	Element* previous = nullptr;
	Element* next = nullptr;

public:
	Element(string id, string Pi) :
		id(id),
		Pi(Pi) {}

	Element* get_next() {
		return next;
	}

	Element* get_prev() {
		return previous;
	}

	void set_h(int num) {
		h = num;
	}

	void set_V(int num) {
		V = num;
	}

	void set_prev(Element* el) {
		previous = el;
	}

	void set_next(Element* el) {
		next = el;
	}

	void set_C(int num) {
		C = num;
	}

	void set_U(int num) {
		U = num;
	}

	void set_T(int num) {
		T = num;
	}

	void set_L(int num) {
		L = num;
	}

	void set_D(int num) {
		D = num;
	}

	void set_Po(int num) {
		Po = num;
	}

	string get_id() {
		return id;
	}

	string get_Pi() {
		return Pi;
	}

	int get_V() {
		return V;
	}

	int get_h() {
		return h;
	}

	int get_C() {
		return C;
	}

	int get_U() {
		return U;
	}

	int get_T() {
		return T;
	}

	int get_L() {
		return L;
	}

	int get_D() {
		return D;
	}

	int get_Po() {
		return Po;
	}
};