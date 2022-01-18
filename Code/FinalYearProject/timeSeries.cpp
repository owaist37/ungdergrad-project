//#include "timeSeries.h"
#include <iostream>
#include <string>
//Library for random number generation
#include <cstdlib>
#include <cmath>
#include <ctime>
//include arrays
#include <array>
#include <random>
//include vectors
#include <vector>
using namespace std;
//Look into storing as a vector rather than an array since vectors are more dynamic

//Creating a class for generating a random set of numbers into an array (any general time series functions)
class timeSeries {

	//All methods in this section will be private
private:
	//Array of size 100 since we want to generate 100 numbers
	int length = 0;
	vector<double> pointsTS;

	//bassic vector methods
	//vector<double> vectorname
	//vector.resize(size)
	//vector.size for length
	//vector[pos] = value or vector.at(pos) = value


	//Creating dynamic Arrays in ++ using pointers
	//double *foo;
	//int length=n; 
	//foo = new double[length];
	//function to return a pointer to the x and y points arrays
	/* When using this I will fist need to
	int *XPoints = getAllX(); to get the pointer
	xPoints[index]; to use the points
	*/

	//Method to generate all n points
	vector<double> generatePoints(int numberOfPoints, double m, double var) {
		vector<double> points(numberOfPoints);
		int count = 0;
		while (count < numberOfPoints) {
			points[count] = normalRandom(m, var);
			count++;
		}
		return points;
	}

	//return a uniformally distributed number
	double uniformRandom() {
		//seed with time for truly random number
		srand(time(NULL));
		return ((double)(rand()) + 1.0) / ((double)(RAND_MAX)+1.0);
	}

	double normalRandom(double mean, double sd)
	{
		double u1 = uniformRandom();
		double u2 = uniformRandom();
		double value = cos(8.*atan(1.)*u2)*sqrt(-2.*log(u1));
		return value * sd + mean;
	}

	vector<double> generateSTDPoints(int number, int mean, int variance) {
		//vector to be returned
		vector<double> points;
		// random device class instance, source of 'true' randomness for initializing random seed
		random_device rd;
		// Mersenne twister PRNG, initialized with seed from previous random device instance
		mt19937 gen(rd());
		// instance of class std::normal_distribution with specific mean and stddev
		normal_distribution<float> distribution(mean, variance);
		for (int i = 0; i < number; i++) {
			//keep as positive number for now
			double value = distribution(gen);
			double point = sqrt(value*value);
			points.push_back(point);
		}
		return points;
	}

public:
	/*
	double normalRandom(double mean, double standardDeviation) {
		double uOne = uniformRandom();
		double uTwo = uniformRandom();
		const double pi = 3.14159265358979323846;
		static double zTwo;
		static int useLast = 0;

		if (useLast) {
			return zTwo;
			useLast = 0;
		}
		else {

			double zOne;

			zOne = sqrt(-2.0 * log(uOne)) * cos(2 * pi * uTwo);
			zTwo = sqrt(-2.0 * log(uOne)) * sin(2 * pi * uTwo);

			useLast = 0;

			return zOne * standardDeviation + mean;
		}

	}*/


	timeSeries(int numberOfPoints, double mean, double variance) {
		pointsTS = generateSTDPoints(numberOfPoints, mean, variance);
	}

	vector<double>   getPointsTS() {
		return pointsTS;
	}

	int  getlength() {
		return pointsTS.size();
	}
};

