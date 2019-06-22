#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <Windows.h>
#include <fstream>


using namespace std;

//Insertion sort
void Insertion_Sort(int A[], int n)
{
	for (int j = 1; j < n; j++)
	{
		int key = A[j];
		int i = j - 1;

		while (i > 0 && A[i] > key)
		{
			A[i + 1] = A[i];
			i = i - 1;
		}
		A[i + 1] = key;
	}
}

//Merge algortithm used for merge sort
void Merge(int A[], int p, int q, int r)
{
	int n1 = q - p + 1;
	int n2 = r - q;

	int *L = new int[n1];
	int *R = new int[n2];

	for (int i = 0; i < n1; i++)
	{
		L[i] = A[p + i];
	}
	for (int j = 0; j < n2; j++)
	{
		R[j] = A[q + j + 1];
	}

	L[n1] = 40000;
	R[n2] = 40000;


	int i = 0;
	int j = 0;


	for (int k = p; k <= r; k++)
	{
		if (L[i] <= R[j])
		{
			A[k] = L[i];
			i = i + 1;
		}
		else
		{
			A[k] = R[j];
			j = j + 1;
		}
	}
}

//Merge Sort
void Merge_Sort(int A[], int p, int r)
{
	if (p < r)
	{
		int q = floor((p + r) / 2);
		Merge_Sort(A, p, q);
		Merge_Sort(A, q + 1, r);
		Merge(A, p, q, r);
	}
}


//Partition algorithm used for quick sort
int Partition(int A[], int p, int r)
{
	int x = A[r];
	int i = p - 1;

	for (int j = p; j < r; j++)
	{
		if (A[j] <= x)
		{
			i = i + 1;
			int temp = A[j];
			A[j] = A[i];
			A[i] = temp;
		}
	}
	int temp = A[i + 1];
	A[i + 1] = A[r];
	A[r] = temp;
	return i + 1;
}


//quicksort
void Quicksort(int A[], int p, int r)
{
	if (p < r)
	{
		int q = Partition(A, p, r);
		Quicksort(A, p, q - 1);
		Quicksort(A, q + 1, r);
	}
}




int main()
{
	SYSTEMTIME gettime;

	ofstream fOutput;
	fOutput.open("Vail_Output.txt");


	const int ns = 1000;
	const int nf = 20000;
	const int delta = 1000;
	const int m = 10;

	int B[nf + 1];

	long time1;
	long time2;

	int talg1[11][21] = { 0 };
	double talg1AVG[21] = { 0 };


	//array generation - default rand max for visual studios c++ is 32767

	int A[11][20001];

	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= nf; j++)
		{
			A[i][j] = rand();
		}
	}

//measurements for Insertion algorithm

	cout << "Insertion-Sort Algorithm\n";
	cout << "************************\n\n";
	cout << "  " << "n" << "      " << "Average Run Time\n";

	fOutput << "Insertion-Sort Algorithm\n";
	fOutput << "************************\n\n";
	fOutput << "  " << "n" << "      " << "Average Run Time\n";


	for (int n = ns; n <= nf; n = n + delta)
	{
		for (int i = 1; i <= m; i++)
		{

			//copies current line into array B
			for (int c = 1; c <= n; c++)
			{
				B[c] = A[i][c];
			}

			//get time
			GetSystemTime(&gettime);
			time1 = (gettime.wSecond * 1000) + gettime.wMilliseconds;

			//call Insertion Sort
			Insertion_Sort(B, n);

			GetSystemTime(&gettime);
			time2 = (gettime.wSecond * 1000) + gettime.wMilliseconds;

			//stores time takenfor insertion sort on current array
			talg1[i][n / 1000] = time2 - time1;
		}

		//Averages the running time for the previous 10 iterations of length n insertion sorts
		for (int i = 1; i <= m; i++)
		{
			talg1AVG[n / 1000] = talg1AVG[n / 1000] + talg1[i][n / 1000];
		}

		talg1AVG[n / 1000] = talg1AVG[n / 1000] / m;

		cout << n << "         " << talg1AVG[n / 1000] << endl;
		fOutput << n << "         " << talg1AVG[n / 1000] << endl;
	}



	int talg2[11][21] = { 0 };
	double talg2AVG[21] = { 0 };

	//measurements for merge-sort algorithm

	cout << "\n\nMerge-Sort Algorithm\n";
	cout << "************************\n\n";
	cout << "  " << "n" << "      " << "Average Run Time\n";

	fOutput << "\n\nMerge-Sort Algorithm\n";
	fOutput << "************************\n\n";
	fOutput << "  " << "n" << "      " << "Average Run Time\n";


	for (int n = ns; n <= nf; n = n + delta)
	{
		for (int i = 1; i <= m; i++)
		{

			//copies current line into array B
			for (int c = 1; c <= n; c++)
			{
				B[c] = A[i][c];
			}

			//get time
			GetSystemTime(&gettime);
			time1 = (gettime.wSecond * 1000) + gettime.wMilliseconds;

			//call Insertion Sort
			Merge_Sort(B, 1, n);

			GetSystemTime(&gettime);
			time2 = (gettime.wSecond * 1000) + gettime.wMilliseconds;

			//stores time takenfor insertion sort on current array
			talg2[i][n / 1000] = time2 - time1;
		}

		//Averages the running time for the previous 10 iterations of length n merge sorts
		for (int i = 1; i <= m; i++)
		{
			talg2AVG[n / 1000] = talg2AVG[n / 1000] + talg2[i][n / 1000];
		}

		talg2AVG[n / 1000] = talg2AVG[n / 1000] / m;

		cout << n << "         " << talg2AVG[n / 1000] << endl;
		fOutput << n << "         " << talg2AVG[n / 1000] << endl;

	}


	int talg3[11][21] = { 0 };
	double talg3AVG[21] = { 0 };

	//measurements for quicksort algorithm

	cout << "\n\nQuicksort Algorithm\n";
	cout << "************************\n\n";
	cout << "  " << "n" << "      " << "Average Run Time\n";

	fOutput << "\n\nQuicksort Algorithm\n";
	fOutput << "************************\n\n";
	fOutput << "  " << "n" << "      " << "Average Run Time\n";


	for (int n = ns; n <= nf; n = n + delta)
	{
		for (int i = 1; i <= m; i++)
		{

			//copies current line into array B
			for (int c = 1; c <= n; c++)
			{
				B[c] = A[i][c];
			}

			//get time
			GetSystemTime(&gettime);
			time1 = (gettime.wSecond * 1000) + gettime.wMilliseconds;

			//call Insertion Sort
			Quicksort(B, 1, n);

			GetSystemTime(&gettime);
			time2 = (gettime.wSecond * 1000) + gettime.wMilliseconds;

			//stores time takenfor insertion sort on current array
			talg3[i][n / 1000] = time2 - time1;

		}

		//Averages the running time for the previous 10 iterations of length n quicksorts
		for (int i = 1; i <= m; i++)
		{
			talg3AVG[n / 1000] = talg3AVG[n / 1000] + talg3[i][n / 1000];
		}

		talg3AVG[n / 1000] = talg3AVG[n / 1000] / m;

		cout << n << "         " << talg3AVG[n / 1000] << endl;
		fOutput << n << "         " << talg3AVG[n / 1000] << endl;

	}

	fOutput.close();
	return 0;
}