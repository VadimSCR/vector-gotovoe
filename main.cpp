#include <clocale>
#include "Vector.h"


int main() {
	using namespace std;
	
	setlocale(LC_ALL, "ru");

	cout << "Пустой вектор (v) с 6-ю элементами: "
		 << v << endl << endl;

	for (int i = 0; i < 6; i++) v[i] = i;
	cout << "Вектор v после присвоения ему натуральных чисел до 6:\n" 
		 << v << endl << endl;

	v.resize(16);
	cout << "Вектор v после изменения размера до 16 элементов:\n" 
		 << v << endl << endl;

	v.insert(3, v);
	cout << v << endl;

	return 0;
}
