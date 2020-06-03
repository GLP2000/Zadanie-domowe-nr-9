#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "winbgi2.h"
#include "rk4.h"

int N = 2; //wartosc N-liczba rownan
double krokc = 0.001; // krok calkowania
double t0 = 0.0; //zalozenia ze zaczynamy od miejsca zerowe
double m, k1, k2;
void funkcja(double t, double* X, double* X1);
double energia(double t,double* X, double* X1);




int main()
{	
	FILE* p;
	p = fopen("zad9.txt", "w");
	if (p == NULL)
		printf("BLAD");

	printf("Zadanie nr 9 - Sprezyna o charakterystyce nieliniowej - Informatyka II\n");
	fprintf(p,"Zadanie nr 9 - Sprezyna o charakterystyce nieliniowej - Informatyka II\n");
	int w;
	double x0, v0,t,t2,emech, ampli, ampliv,amplim;
	
	printf("podaj warunki poczatkowe x0\n");
	scanf("%lf", &x0);
	while (x0 == 0) // sprawdza czy dane x0 spelnia warunki poczatkowe
	{
		printf("Probuj znowu x0 !=0\n");
		scanf("%lf", &x0);
	}
	printf("podaj warunki poczatkowe v0\n");
	scanf("%lf", &v0);
	while (v0 == 0)
	{
		printf("Probuj znowu v0 !=0\n");
		scanf("%lf", &v0);
	}
	printf("podaj masa\n");
	scanf("%lf", &m);
	while (m == 0)
	{
		printf("Probuj znowu m !=0\n");
		scanf("%lf", &m);
	}
	printf("Podaj K1 sprezyny\n");
	scanf("%lf", &k1);
	while (k1 < 0) 
	{
		printf("Probuj znowu K1 nie moze byc ujemne\n");
		scanf("%lf", &k1);
	}
	printf("Podaj K2 sprezyny\n");
	scanf("%lf", &k2);
	while (k2 < 0)
	{
		printf("Probuj znowu K2 nie moze byc ujemne\n");
		scanf("%lf", &k2);
	}

	printf("Wybierz wykres, ktory chcesz 1. x(t) , 2. v(t) lub 3. EMech(t):\n");
	scanf("%d", &w);

	double w0 = sqrt(k1 / m);
	t = t0;
	t2 = ((2.0*3.1415)*w0)/10;//okres podzielone przez 10 
	ampli = (x0 / (cos(w0*t2*10)));
	ampliv = (x0*m*k1*k2);
	amplim = (m*x0*v0*k1*k2);

	double X[2] = {x0,v0}, X1[2];
	
	graphics(800, 600);

	if(w==1)
	{
		scale(t, -ampli, t2, ampli);//skala dla x(t)
	}
	else if (w == 2)
	{
		scale(t,-ampliv, t2, ampliv);//skala dla v(t)
	}
	else if(w==3)
	{
		scale(t, 0, t2, amplim);//skala dla Emech(t)
	}
	else
	{
		printf("Probuj znowu\n");
		scanf("%d", &w);
	}

	
	
	fprintf(p, "x0=%lf\tv0=%lf\tm=%lf\tk1=%lf\tk2=%lf\n\n", x0, v0, m, k1, k2);
	fprintf(p, "Czas[s]\t\tX\t\tV\t\t Energia Mechaniczna\n");

	while(t<t2)
	{
		vrk4(t, X, krokc, N, funkcja, X1);

		X[0] = X1[0];
		X[1] = X1[1];
		t += krokc;

		emech = energia(t, X, X1);
		
		//printf( "%lf\t%lf\t%lf\t%lf\t\n", t, X[0], X[1], emech);
		
		fprintf(p, "%lf\t%lf\t%lf\t%lf\t\n",t,X[0],X[1],emech);// zapisuje do pliku 

		if (w == 1)// x(t)
		{
			
			title("t ", " X ", "Wykres x(t) ");
			setcolor(1.0);// czerwone
			lineto(t, X[0]);
		}
		if (w == 2)// v(t)
		{
			title("t", "V ", "Wykres Vx(t) ");
			setcolor(0.5);//zielone
			lineto(t, X[1]);
		}
		if (w == 3)// Emech(t)
		{

			title("t", "Emech ", "Wykres Emech(t)");
			setcolor(0.1);//niebielski
			lineto(t, emech);
		}
		
	}




	fclose(p);

	wait();
}

void funkcja(double t, double* X, double* X1) //funckja obliczajaca prawe strony
{
	X1[0] = X[1];
	X1[1] = (1/m)*(-k1*(1+k2*pow(X[0],2.0))*X[0]);
}

double energia(double t,double* X, double* X1)
{
	return ((m * pow(X[1], 2.0))/2 + (k1 * pow(X[0], 2.0))/2 + (k1 * k2 * pow(X[0], 4.0))/4 );

}


