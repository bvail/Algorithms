#include <iostream>
#include <chrono>
#include <math.h>

using namespace std;

//Brute Force Method
//Find minimum digit in array, returns index of fake coin
int BruteForceFakeCoin(int A[], int n)
{

		for (int i = 0; i < n; i++)
		{
			if (A[i] == 0)
			{
				return i;
			}
		}

	cout << "ERROR: fake coin absent\n";
	return -1;

}


//Divide and Conquer Method
//i is index of the fake coin, used for weighing subarrays
//boolean odd checks only the first function call if array is odd
int DCFakeCoin(int A[], int p, int r, int i, bool odd)
{
	//base case
	if (p == r)
	{
		if (A[p] == 0)
		{
			return p;
		}
		else
		{
			cout << "ERROR: fake coin absent\n";
			return -1;
		}
	}


	//checks even or odd, adds 1 to account for index 0
	//checks only once, boolean flag odd turns to true
	if (odd == 0)
	{
		if ((r + 1 - p) % 2 == 1)
		{
			p = p + 1;
			cout << "It's odd\n";
		}

		odd = 1;
	}

	//Divide remaining array into two even groups
	double q = (double)(p + r) / 2;
	q = floor(q);

	//Weighing two groups, if equal, then returns fake coin index of odd array
	if (i >= p && i <= q)
	{
		DCFakeCoin(A, p, q, i, odd);
	}
	else if (i >= (q + 1) && i <= r)
	{
		DCFakeCoin(A, q + 1, r, i, odd);
	}
	else if ((p - 1) == i)
	{
		return 0;
	}
	else
	{
		cout << "ERROR in Recursion!\n";
		return -1;
	}
}



int main()
{
	int array1[250000];
	fill_n(array1, 250000, 1);

	int x; //index of fake coin

	int BruteForceIndex;
	int DCIndex;

	long long BFtime[11] = { 0 };
	long long DCtime[11] = { 0 };
	long double BFavg[11] = { 0 };
	long double DCavg[11] = { 0 };

	cout << "Calculating Algorithm Run Time, Please Hold...\n";

	//Loop increasing the n value, the number of items in the array
	for (int n = 25000; n <= 250000; n = n + 25000)
	{
		//Loop for each n value 10 times
		//note, the first run of index i will not be used
		for (int i = 0; i < 11; i++)
		{

			//selects random index of array and sets it to zero, i.e the fake coin
			x = rand() % n;
			array1[x] = 0;


			//*******************************
			//BRUTE FORCE FAKE COIN ALGORITHM
			//*******************************

			//starts clock for algorithm timing
			auto start1 = chrono::high_resolution_clock::now();

			//call brute force algorithm to find index of fake coin
			BruteForceIndex = BruteForceFakeCoin(array1, n);

			//calculates elapsed time for algorithm
			auto elapsed1 = chrono::high_resolution_clock::now() - start1;

			//stores elapsed time in array
			BFtime[i] = chrono::duration_cast<::chrono::microseconds>(elapsed1).count();

			//*******************************
			//DIVIDE & CONQUER FAKE COIN ALGORITHM
			//*******************************

			//starts clock for algorithm timing
			auto start2 = chrono::high_resolution_clock::now();

			//call DC algortihm
			DCIndex = DCFakeCoin(array1, 0, n - 1, x, 0);

			//calculates elapsed time for algorithm
			auto elapsed2 = chrono::high_resolution_clock::now() - start2;

			//stores elapsed time in array
			DCtime[i] = chrono::duration_cast<::chrono::microseconds>(elapsed2).count();

			//removes fake coin from index
			array1[x] = 1;



			//delay in algorithm processing
			for (int a = 0; a < 5000000; a++)
			{ }

		}


		//Averages the running time for the previous 10 iterations of length n brute force algorithms
		for (int i = 1; i < 11; i++)
		{
			BFavg[n / 25000] = BFavg[n / 25000] + BFtime[i];
		}

		BFavg[n / 25000] = BFavg[n / 25000] / 10;


		//Averages the running time for the previous 10 iterations of length n divide and conquer algorithms
		for (int i = 1; i < 11; i++)
		{
			DCavg[n / 25000] = DCavg[n / 25000] + DCtime[i];
		}

		DCavg[n / 25000] = DCavg[n / 25000] / 10;

	}

	//prints averages of brute force running times
	cout << "\n\nBrute Force Algorithm\n";
	cout << "************************\n\n";
	cout << "  " << "n" << "      " << "Average Run Time\n";

	for (int i = 1; i < 11; i++)
	{
		cout << (i * 25000) << "         " << BFavg[i] << endl;
	}

	//prints averages of brute force running times
	cout << "\n\nDivide and Conquer Algorithm\n";
	cout << "************************\n\n";
	cout << "  " << "n" << "      " << "Average Run Time\n";

	for (int i = 1; i < 11; i++)
	{
		cout << (i * 25000) << "         " << DCavg[i] << endl;
	}

	return 0;
}
