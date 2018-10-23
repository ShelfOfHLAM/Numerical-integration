#include "stdafx.h" 
#include <iostream>
#include <iomanip>
#include "math.h" 

using namespace std;

long double eps = 0.000001;

long double func2(long double x)
{
	return pow(x,1/5)*sqrt(1+pow(x,2));


}

long double func1(long double x)
{
	return 6 * pow(x, 5);


}

long double teor(long double c, long double h, int k)
{
	return c*pow(h, k);

}

long double runge(long double jh, long double jhw, int k)
{
	return (jhw - jh) / (pow(2, k) - 1);

}

long double kpogr(long double jhw, long double jh, long double jhf, long double k)
{
	return (jhw - jh) / (jhf - jhw);

}

long double step(long double a, long double b, int n)
{
	return (b - a) / n;

}

long double parabol(long double h, int n, long double a, long double b , long double (*func)(long double x))
{
	long double j = 0;
	long double j1 = 0;
	long double j2 = 0;

	for (int i = 1; i < n; i++)
	{
		j1 += func(h*i + a);

	}

	for (int i = 0; i < n; i++)
	{
		j2 += func(h*i + a + (h / 2));

	}

	j = h*(func(a) + func(b) + 2 * j1 + 4 * j2)/6;

	return j;

}

int main()
{
	long double a = 0;
	long double b = 1;
	long double m = 720 * (b - a)*b;
	long double c = m / 2880;
	int k = 4;
	long double accur = 1;

	for (int n = 2; n <= 65536; n *= 2)
	{
		long double h = step(a, b, n);
		long double h2 = step(a, b, n * 2);
		long double h4 = step(a, b, n * 4);
		long double hd = step(a, b, n / 2);
		long double jhw = parabol(h2, n * 2, a, b,func1);
		long double jh = parabol(h, n, a, b,func1);
		long double jhf = parabol(h4, n * 4, a, b,func1);
		long double jhd = parabol(hd, n / 2, a, b,func1);

		cout << setw(6) << n << " " << setw(8) << kpogr(jhw , jh, jhf , k)
			<< "  " << setprecision(6) << accur - jh << "  " << setprecision(6) << runge(jhd, jh, k)
				<< "  " << setprecision(6) << teor(c, h, k) << "  " << setprecision(6) << endl;
	}

	cout << endl << endl << "func2[0,1.5] = " << parabol(step(a, b, 128), 128, 0.000, 1.5,func2) << endl;
	cout << endl << endl << "func2[0.001,1.5] = " << parabol(step(a, b, 128), 128, 0.001, 1.5,func2) << endl;

	return 0;

}