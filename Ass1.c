/****************************************************************************************************************************************
File Name:						Ass1.c
Version:						1.0
Auther/Student Name:			Jason Waid
Student Number:					040912687
Couse Name and Number:			Numerical Computing CST8233
Lab Section:					303
Assignment Number:				Assignment #1
Assignment Name:				Building Motion Simulation
Due Date:						06/12/2020
Submission Date of Assignment:	06/12/2020
Professor's Name:				Abdullah Kadri
Purpose:						Demonstrate Maclaurin Series approximation via a Building Motion Simulator
******************************************************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


//Function Prototypes
double calc_Exact_Value(double);
double calc_Trunc_Error(int, double, double);
double calc_Error(double, double);
double calc_Series(int x, double t);
void calculate(double*, double*);

/****************************************************************************************************************************************
Function Name:						calc_Exact_Value
Purpose:							Calculates Exact Value of e^-t * cos(t), used to determine other calculations
In parameters:						(double) t: value of t
Out parameters:						(double) exact calculation
Version:							1.0
Author:								Jason Waid
****************************************************************************************************************************************/

double calc_Exact_Value(double t) {
	//Actual calcualtion of e^-t * cos(t)
	return exp(-t) * cos(t);
}

/****************************************************************************************************************************************
Function Name:						calc_Trunc_Error
Purpose:							Calculates the truncate error
In parameters:
									(int) x: iteration of the loop
									(double) t: value of t
									(double) series: value of series

Out parameters:						(double) truncError: value of truncate error after calculation
Version:							1.0
Author:								Jason Waid
****************************************************************************************************************************************/
double calc_Trunc_Error(int x, double t, double series) {
	
	//declare variables
	double truncate = 0;
	double truncError = 0;
	//Switch case designed to handle specific calculations depending on the term (x)
	switch (x) {

	case 1:
		truncate = -t;
		break;

	case 2:
		truncate = t * t * t / 3.0;
		break;

	case 3:
		truncate = -t * t * t * t / 6.0;
		break;

	case 4:
		truncate = t * t * t * t * t / 30.0;
		break;
	case 5:
		truncate = -t * t * t * t * t * t * t / 630.0;
		break;
	}
	
	truncError = 100 * truncate / series;

	if (truncError == -0.0) {
		truncError = 0;
	}
	//The final result of the truncate error
	return truncError;
}


/****************************************************************************************************************************************
Function Name:							calc_Error
Purpose:								Calculates the error value
In parameters:
										(double) exactValue: exact calculation of e^-t * cos(t)
										(double) series: value of series

Out parameters:							(double): value of error after calculation
Version:								1.0
Author:									Jason Waid
****************************************************************************************************************************************/
double calc_Error(double exactValue, double series) {
	//The value of the exact error by comparing the series to the exactValue
	return 100 * (exactValue - series) / exactValue;

}


/****************************************************************************************************************************************
Function Name:							calc_Series
Purpose:								Calculates series value
In parameters:
										(int) x: terms
										(double) t: value of t

Out parameters:							(double): value of error after calculation
Version:								1.0
Author:									Jason Waid
****************************************************************************************************************************************/
double calc_Series(int x, double t) {
	
	//declare variables
	double series = 0;
	//Switch case designed to handle specific calculations depending on the term (x)
	switch (x) {
	case 1: 
		series = 1;
		break;
	case 2: 
		series = 1 - t;
		break;
	case 3: 
		series = 1 - t + (t * t * t / 3);
		break;
	case 4: 
		series = 1 - t + (t * t * t / 3.0) - (t * t * t * t / 6.0);
		break;
	case 5: 
		series = 1 - t + (t * t * t / 3.0) - (t * t * t * t / 6.0) + (t * t * t * t * t / 30.0);
		break;
	}
	//The final results after he series has been calculated
	return series;
}


/****************************************************************************************************************************************
Function Name:							calculate
Purpose:								Performs all of the calculations and prints each row
In parameters:
										(double) numTerms: number of terms
										(double) rangeOfT: range of t

Out parameters:							n/a
Version:								1.0
Author:									Jason Waid
****************************************************************************************************************************************/
void calculate(double* numTerms, double* rangeOfT) {
	
	//declare variables
	double t = 0;
	double series = 0;
	double newRangeOfT = *rangeOfT / 10;
	int x = *numTerms / 1;
	int i;

	//Loop prints a line for every value of t up till the desired range (rangeOfT) the user entered in the menu
	while (t <= *rangeOfT) {
		double series = calc_Series(x, t);
		double exact = calc_Exact_Value(t);
		double exactError = calc_Error(exact, series);
		double truncError = calc_Trunc_Error(x, t, series);

		printf("%.3e\t%.5e\t%.5e\t%.5e\t%.5e\n",t, series, exact, exactError, truncError);

		t += newRangeOfT;

	}
}


/****************************************************************************************************************************************
Function Name:							Main
Purpose:								Provide menu and take user input
In parameters:							N/A
Out parameters:							Int on success
Version:								1.0
Author:									Jason Waid
****************************************************************************************************************************************/
int main(void) {

	//Declare variables
	double numTerms = 0;
	double rangeOfT = 0;
	int menu = 0;

	//The main menu for accepting user inputs
	for (;;) {
		printf("Evaluate the Maclaurin Series approximation to exp(-t)*cos(t)\n");
		printf("\n");
		printf("1: Evaluate the series\n");
		printf("2: quit\n");

		//Error handing for incorect input
		while (scanf("%d", &menu) != 1 || (menu != 1 && menu != 2)) {

			printf("\nInvalid input. \n");
			printf("1: Evaluate the series\n");
			printf("2: quit\n");
			scanf("%*[^\n]");
		}


		switch (menu) {

		case 1:
			//The begining of menu option 1
			printf("Evaluating the series\n");
			printf("Please enter the number of terms in the series(max 5 terms) : ");

			//Error handing for incorect input
			while (scanf("%lf", &numTerms) != 1 || numTerms < 1 || numTerms > 5) {

				printf("\nInvalid input. Please enter valid integer (1 - 5)\n");
				scanf("%*[^\n]");
			}

			printf("Please enter the range of t to evaluate in 10 increments (0.0 < t < +2.0): ");
			
			//Error handing for incorect input
			while (scanf("%lf", &rangeOfT) != 1 || rangeOfT < 0 || rangeOfT > 2.0) {

				printf("\nInvalid input. Please enter valid value of t (0.0 < t < +2.0)\n");
				scanf("%*[^\n]");
			}

			//Handles a very specific error by incorrect user input for -0.0
			if (rangeOfT == -0.0) {
				rangeOfT = 0.0;
			}

			//The header of the table that is to be populated by the proceeding functions
			printf("\n\nMACLAURIN SERIES\n\n");
			printf("  t\t\tSeries\t\tExact\t\tExact %% Error\tTrunc. %% Error\n\n");

			//Proceeds to run calculations
			calculate(&numTerms, &rangeOfT);
			printf("\n\n");
			break;


		case 2:
			//Menu option 2, which will simplly return 0 exiting the program
			return 0;

		}
	}
}