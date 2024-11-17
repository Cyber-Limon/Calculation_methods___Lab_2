#include <iostream>
#include <cmath>



using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");

	cout << "n\t" << "K_d\t\t" << "d_точное\t" << "d_Рунге\t\t" << "d_теор\n";
	for (int i = 0; i < 70; i++) cout << "-";
	cout << "\n";

	

	double J_old = 0;
	double J_old_old = 0;

	double K_d = 0;
	int pr = 1;
	double K_Run = 0;



	for (int count_segments = 1; count_segments < 66000; count_segments *= 2) {
		double h = 1.0 / count_segments;



		double* array_x = new double[count_segments + 1];
		double* array_y = new double[count_segments + 1];

		for (int i = 0; i <= count_segments; i++) {
			array_x[i] = h * i;
			array_y[i] = 6 * pow(h * i, 5);
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



		double d_pr = pr - J;



		if (J_old != 0)
			K_Run = (J- J_old) / (16 - 1);
		


		double d_th = 0;

		for (int i = 0; i <= count_segments; i++)
			if (720 * array_x[i] / 2880 > d_th)
				d_th = 720 * array_x[i] / 2880;

		d_th *= pow(h, 4);



		J_old_old = J_old;
		J_old = J;



		cout << "\t\t\t\t\t\t\t" << d_th << "\r";

		if (K_Run != 0) cout << "\t\t\t\t\t" << K_Run << "\r";
		else cout << "\t\t\t\t\t" << "-\r";

		cout << "\t\t\t" << d_pr  << "\r";

		if (K_d != 0) cout << "\t" << K_d << "\r";
		else cout << "\t" << "-\r";

		cout << count_segments << "\n";

		
		
		delete[] array_x;
		delete[] array_y;
	}
}