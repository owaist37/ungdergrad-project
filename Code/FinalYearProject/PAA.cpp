//#include "PAA.h"
#include <iostream>
#include <string>
//Library for random number generation
#include <cstdlib>
//include arrays
#include <array>
#include <vector>
#include<chrono>
using namespace std::chrono;
using namespace std;



class PAA {
private:

	//numbers of points we want to average to
	int N;
	//vector of all the averaged points
	vector<double> PAAvector;
	//vector of all the averaged points
	vector<double> PAAdtw;
	//the remainder
	int modulo;
	//length without the modulo#
	int LengthFrames;
	//number of frames in the main
	int mainFrames;
	//to store time algorithm took to run
	float tiktokPAA;

	//original implementation not currentl being used
	vector<double> averageN(vector<double> orginialSeries, int numberOfFrames) {


		double value = 0; //the  y current value
		//vector<double> PAAvector(numberOfFrames);
		int lengthOfFrame; //length of each of the main frames
		int lengthOfSpare; //Length of the spare frame
		int lengthNew; //length when ts - modulo 


		int lengthOfSeries = orginialSeries.size();
		modulo = lengthOfSeries % numberOfFrames;

		if (modulo == 0) {
			lengthOfFrame = lengthOfSeries / numberOfFrames;
		}
		else {
			lengthNew = lengthOfSeries - modulo;  //length of series that can be equaly split
			lengthOfFrame = lengthNew / numberOfFrames;//length of each of the frames
			lengthOfSpare = modulo; //length of the final frame
		}


		//cout << "lengthOfFrame" << lengthOfFrame << endl;
		int currentFrame = 0;
		//loop through the main frames
		for (int i = 0; i < numberOfFrames; i++) {
			for (int p = 0; p < lengthOfFrame; p++) {
				value += orginialSeries[i + p];
			}
			value = value / lengthOfFrame;
			//PAAvector[i] = value;
			PAAvector.push_back(value);
			value = 0;

		}
		//loop through the rest if the modulo is not 0
		if (modulo != 0) {
			int valueTwo = 0;
			for (int j = 0; j < lengthOfSpare; j++) {
				valueTwo += orginialSeries[lengthNew + j];
			}
			valueTwo = valueTwo / lengthOfSpare;
			PAAvector.push_back(valueTwo);
		}
		return PAAvector;
	}


	vector <double> paaViaFrames(vector<double> originalSeries, int numberOfFrames) {
		int lengthOfExtra = originalSeries.size() % numberOfFrames;
		int lengthOfSeriesPaa = originalSeries.size();
		vector<double> vectPaa;
	
		int lengthOfMainPaa = originalSeries.size() - lengthOfExtra;
		int LengthOfFramesPaa = lengthOfMainPaa / numberOfFrames;

		//declaring the global variables used in other opertaions
		modulo = lengthOfSeriesPaa % LengthOfFramesPaa;
		LengthFrames = LengthOfFramesPaa;
		mainFrames = numberOfFrames;

		double value = 0; //value of section
		int pos = 0; //postion in the vector
		for (int i = 0; i < numberOfFrames; i++) {
			for (int k = 0; k < LengthOfFramesPaa; k++) {
				value += originalSeries[pos];
				pos++;
			}
			value = value / LengthOfFramesPaa;
			vectPaa.push_back(value);
			value = 0;
		}

		//adding the final one for any remainders
		if (modulo != 0) {
			int valueTwo = 0;
			for (int j = lengthOfMainPaa; j < lengthOfSeriesPaa; j++) {
				valueTwo += originalSeries[pos];
				pos++;
			}
			valueTwo = valueTwo / modulo;
			vectPaa.push_back(valueTwo);
		}
		return vectPaa;
	}

	//Length 1,2,3,4,5,6,7 value frames of length 2 = 1

	vector<double> averageNTWO(vector<double> originalSeries, int LengthOfFrames) {
		//Setting the variable
		LengthFrames = LengthOfFrames;
		vector<double> vect;
		int lengthOfSeries = originalSeries.size();
		//get the remainder
		modulo = lengthOfSeries % LengthOfFrames;
		int numberOfFrames; //Number of frames with a given length
		int lengthOfMain;//modulo minus the remainder
		lengthOfMain = lengthOfSeries - modulo;
		numberOfFrames = lengthOfMain / LengthOfFrames;
		//set the private var
		mainFrames = numberOfFrames;


		//cout << "Length of series " << lengthOfMain << endl;

		//sum up for the main frames
		double value = 0; //value of section
		int pos = 0; //postion in the vector
		for (int i = 0; i < numberOfFrames; i++) {
			for (int k = 0; k < LengthOfFrames; k++) {
				value += originalSeries[pos];
				pos++;
			}
			value = value / LengthOfFrames;
			vect.push_back(value);
			value = 0;
		}

		//adding the final one for any remainders
		if (modulo != 0) {
			int valueTwo = 0;
			for (int j = lengthOfMain; j < lengthOfSeries; j++) {
				valueTwo += originalSeries[pos];
				pos++;
			}
			valueTwo = valueTwo / modulo;
			vect.push_back(valueTwo);
		}
		return vect;
	}

	//for the export to file
	vector<double> createPAAVect(vector<double> PAApoints, int numberOfFrames, int PAAlengthOfFrames, int PAAmodulo) {
		//vector to be returned
		vector<double> paavect;
		//original variables 
		//for the PAA points
		//need method for if modulo is zero or not zero
		//int testCount=0; //for testing
		//Attempt 3 05/03/2019
		if (PAAmodulo == 0) {
			for (int k = 0; k<PAApoints.size(); k++) {
				for (int l = 0; l < PAAlengthOfFrames; l++) {
					paavect.push_back(PAApoints[k]);
					//testCount++;
				}
			}
		}
		if (PAAmodulo > 0) {
			for (int k = 0;  k< PAApoints.size()-1; k++) {
				for (int l = 0; l < PAAlengthOfFrames; l++) {
					paavect.push_back(PAApoints[k]);
					//testCount++;
				}
			}
			for (int s = 0; s < PAAmodulo; s++) {
				paavect.push_back(PAApoints[PAApoints.size() - 1]);
				//testCount++;
			}

		}

		//cout << "test count paa:" << testCount << endl;

		//Atempt 2 05/03/2019
		//Loop through the number of frames
		//compare each of them with the number of frames
		/*
		for (int i = 0; i < numberOfFrames; i++) {
			for (int j = 0; j < PAAlengthOfFrames; j++) {
				paavect.push_back(PAApoints[i]);
			}
		}

		//for the final frame if modulo is not zero
		if (modulo > 0) {
			int lastIndex = PAApoints.size() - 1;
			for (int k = 0; k < modulo; k++) {
				paavect.push_back(PAApoints[lastIndex]);
			}
		}*/

		/*Orginial 
		if (modulo == 0) {
			//add the points from the vector
			for (int i = 0; i < PAAvector.size(); i++) {
				for (int j = 0; j < LengthFrames; j++) {
					paavect.push_back(PAAvector[i]);
				}
			}
		}
		else {
			//add the points for the non modulo values
			for (int i = 0; i < PAAvector.size() - 1; i++) {
				for (int j = 0; j < LengthFrames; j++) {
					paavect.push_back(PAAvector[i]);
				}
			}
			//add the modulo item in
			for (int k = 0; k < modulo; k++) {
				paavect.push_back(PAAvector.size() - 1);
			}
		}*/
		return paavect;
	}


public:
	PAA(vector<double> tsO, int LengthOfFrames) {
		auto startPAA = high_resolution_clock::now(); // time at start
		PAAvector = paaViaFrames(tsO, LengthOfFrames);//  averageNTWO(tsO, LengthOfFrames);
		auto stopPAA = high_resolution_clock::now(); //time at end
		auto duration = duration_cast<microseconds>(stopPAA - startPAA);
		tiktokPAA = duration.count();
		PAAdtw = createPAAVect(PAAvector,mainFrames,LengthFrames,modulo);
	}

	/* old method
	PAA(int LengthOfFrames, vector<double> tsO) {
		auto startPAA = high_resolution_clock::now(); // time at start
		PAAvector = averageNTWO(tsO, LengthOfFrames);
		auto stopPAA = high_resolution_clock::now(); //time at end
		auto duration = duration_cast<microseconds>(stopPAA - startPAA);
		tiktokPAA = duration.count();
		PAAdtw = createPAAVect(PAAvector, mainFrames, LengthFrames, modulo);
	}*/

	//return the duration
	float getDurationPAA() {
		return tiktokPAA;
	}

	vector<double> getPAAdtw() {
		return PAAdtw;
	}

	int getFrameLength() {
		return LengthFrames;
	}

	vector<double> getPAAvector() {
		return PAAvector;
	}

	int getModulo() {
		return modulo;
	}

	int getNumberOfMainFrames() {
		return mainFrames;
	}

	int getNumberOfFrames() {
		return PAAvector.size();
	}

};
