#include <iostream>
#include <cmath>



using namespace std;

double func(int n, double x) {
	if (n == 1)
		return 6 * pow(x, 5);
	else
		return pow(x, 1 / 30) * pow(1 + pow(x, 2), 0.5);
}



double deriv(int n, double x) {
	if (n == 1)
		return 720 * x / 2880;
	else
		return 0;
}



void integral(int func_num, double pr, double a, double b, bool check) {
	cout << "n\t" << "K_d\t\t" << "d_точное\t" << "d_Рунге\t\t" << "d_теор\n";
	for (int i = 0; i < 70; i++) cout << "-";
	cout << "\n";



	double J_old = 0;
	double J_old_old = 0;

	double K_d = 0;
	double d_pr = 0;
	double K_Run = 0;



	for (int count_segments = 1; count_segments < 66000; count_segments *= 2) {
		double h = (b - a) / count_segments;



		double* array_x = new double[count_segments + 1];
		double* array_y = new double[count_segments + 1];

		for (int i = 0; i <= count_segments; i++) {
			array_x[i] = h * i + a;
			array_y[i] = func(func_num, array_x[i]);
		}



		double sum_x_1 = 0;
		double sum_x_2 = 0;

		for (int i = 0; i < count_segments; i++) {
			if (i != 0)
				sum_x_1 += array_y[i];

			sum_x_2 += 6 * pow(array_x[i] + h / 2, 5);
		}

		double J = (h / 6) * (array_y[0] + array_y[count_segments] + 2 * sum_x_1 + 4 * sum_x_2);



		if (J_old_old != 0)
			K_d = (J_old - J_old_old) / (J - J_old);


		
		if (check) 
			d_pr = pr - J;



		if (J_old != 0)
			K_Run = (J - J_old) / (16 - 1);



		double d_th = 0;

		if (check) 
			for (int i = 0; i <= count_segments; i++)
				if (deriv(func_num, array_x[i]) > d_th)
					d_th = deriv(func_num, array_x[i]);

		d_th *= pow(h, 4);



		J_old_old = J_old;
		J_old = J;



		cout << count_segments << "\r";

		if (K_d != 0) 
			cout << "\t" << K_d << "\r";
		else 
			cout << "\t" << "-\r";

		if (check) 
			cout << "\t\t\t" << d_pr << "\r";
		else 
			cout << "\t\t\t" << "-\r";

		if (K_Run != 0) 
			cout << "\t\t\t\t\t" << K_Run << "\r";
		else 
			cout << "\t\t\t\t\t" << "-\r";

		if (check) 
			cout << "\t\t\t\t\t\t\t" << d_th << "\n";
		else 
			cout << "\t\t\t\t\t\t\t" << "-\n";



		delete[] array_x;
		delete[] array_y;
	}

	cout << "\n\n\n";
}



int main() {
	setlocale(LC_ALL, "Russian");

	cout << "Функция y = 6 * x^5 на отрезке [0, 1]\n\n";
	integral(1, 1, 0, 1, true);

	cout << "Функция y = x^(1/m) * (1+x^2)^(1/2) на отрезке [0, 1.5]\n\n";
	integral(2, 0, 0, 1.5, false);

	cout << "Функция y = x^(1/m) * (1+x^2)^(1/2) на отрезке [0.001, 1.5]\n\n";
	integral(2, 0, 0.001, 1.5, false);
}
