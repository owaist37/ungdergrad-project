//#include "imp.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

/*NOTES FOR THE ACTUAL DATASET
First row is a class label with each number being a different class, some files will start with a class 0 (due to leagacy)
 DATA SETS THAT WILL BE USED:
 zip password: someone
C:\Users\owais\Documents\DataToBeTested
*/

class imp {

private:
	vector<double> dataOriginal;
	vector<double> dataZNormalised;

	double originalMean;
	double originalVariance;

	double zMean;
	double zVariance;

	//varibles for the UCR
	vector < vector<double> > allData;
	vector < vector<double> > classesRemoved;
	vector < vector<double> > averaged;
	int numberOfLines;

	//ucr end

	vector<double> read(string file) {
		//read  into string
		vector<string> values;
		ifstream dataFile;
		dataFile.open(file);

		while (dataFile.good()) {
			string line;
			getline(dataFile, line, ',');
			values.push_back(line);
		}
		dataFile.close();
		//convert string into doubles
		vector<double> valuesD;
		for (int i = 0; i < values.size(); i++) {
			double value = stod(values[i]);
			valuesD.push_back(value);
		}
		return valuesD;
	}

	double calcMean(vector<double> vect) {
		double value = 0;
		for (int i = 0; i < vect.size(); i++) {
			value += vect[i];
		}
		value = value / vect.size();
		return value;
	}

	double calcVariance(vector<double> vect) {
		double mean = calcMean(vect);
		double var = 0;
		double value = 0;
		double n = vect.size();
		for (int i = 0; i < n; i++) {
			double temp = (vect[i] - mean)*(vect[i] - mean);
			temp = temp / n;
			value += temp;
		}
		var = sqrt(value);
		return var;
	}

	double calcVariance(vector<double> vect, double mean) {
		double var = 0;
		double value = 0;
		double n = vect.size();
		for (int i = 0; i < n; i++) {
			double temp = (vect[i] - mean)*(vect[i] - mean);
			temp = temp / n;
			value += temp;
		}
		var = sqrt(value);
		return var;
	}

	vector<double> zNormalise(vector<double> vect) {
		vector<double> zNormalised;
		double mean = calcMean(vect);
		double variance = calcVariance(vect, mean);

		for (int i = 0; i < vect.size(); i++) {
			double temp = (vect[i] - mean) / variance;
			zNormalised.push_back(temp);
		}
		return zNormalised;
	}

	void zConstruct(vector<double> vect) {
		//mean and variance of the orgignal data
		originalMean = calcMean(vect);
		originalVariance = calcVariance(vect, originalMean);
		//normalise the data
		dataZNormalised = zNormalise(vect);
		zMean = calcMean(dataZNormalised);
		zVariance = calcVariance(dataZNormalised, zMean);
	}

	/*READ METHODS FOR THE UCR DATA*/
	//Step one get the number of lines in a file to know how many vectors to make

	//STEP 1: GET THE NUMBRER OF LINES, TO KNOW HOW MANY VECTORS AT MOST WILL BE REQUIRED
	int numberOfLine(string file) {
		int numLines = 0;
		string line;
		ifstream lineFile;
		lineFile.open(file);

		while (getline(lineFile, line)) {
			numLines++;
		}
		return numLines;
	}

	//Takes the average of all the datasets per class
	vector<double> UCRreadavg(string file, bool average) {
		//read  into string
		vector<string> values;
		ifstream dataFile;
		dataFile.open(file);

		while (dataFile.good()) {
			string line;
			getline(dataFile, line, ' ');
			values.push_back(line);
		}
		dataFile.close();
		//convert string into doubles
		vector<double> valuesD;
		for (int i = 0; i < values.size(); i++) {
			double value = stod(values[i]);
			valuesD.push_back(value);
		}
		return valuesD;
	}


	/*UCR IMPORT METHOD*/
	vector<double> lineToVector(string line) {
		vector<double> lineVector;
		istringstream linestream(line);
		string element;
		while (getline(linestream, element, '\t'))
		{
			lineVector.push_back(stod(element));
		}
		return lineVector;
	}

	vector<vector<double> > readUCR(string filelocation) {
		vector<vector<double> > fileVector;
		string line;
		ifstream dataFile;
		dataFile.open(filelocation);
		if (dataFile.is_open())
		{
			while (getline(dataFile, line))
			{
				fileVector.push_back(lineToVector(line));
			}
			dataFile.close();
		}
		else {
			cout << "file not found" << endl;
		}

		//for (int i = 0; i < fileVector.at(1).size(); i++) {
			//cout << fileVector.at(1).at(i) << endl;
		//}

		return fileVector;
	}

	/*METHOD TO REMOVE THE CLASS NUMBER FROM EACH OF THE VECTORS*/
	vector < vector<double> > removeClass(vector < vector<double> > origData) {
		vector < vector<double> > removed = origData;
		//loop through the vector removing the first element aka the class value
		for (int i = 0; i < removed.size(); i++) {
			removed[i].erase(removed[i].begin());
		}
		return removed;
	}



public:

	imp(string file, bool UCR, bool avgering) {
		if (UCR == false) {
			vector<double> values = read(file);
			dataOriginal = values;
			zConstruct(values);
		}
		else if(UCR == true && avgering == false) {
			allData = readUCR(file);
			classesRemoved = removeClass(allData);
			numberOfLines = classesRemoved.size();
		}
		else {
			cout << "Averaging not implemented yet" << endl;
		}
		
	}

	/*Return methods for UCR*/
	vector < vector<double> > getUCRData() {
		return classesRemoved;
	}

	int getNumberOfInstances() {
		return numberOfLines;
	}

	
	/*METHOD TO AVERAGE ALL THE VECTORS OF THE SAME CLASS*/
	//will allow for only one vector per class
	vector < vector<double> > reduceToPerOnePerClass(vector < vector<double> > originalData) {
		int count = 0; //count for the current row
		vector< vector<double> > onePc; //one per class double vector
		int lastClass = originalData[originalData.size() - 1][0];
		int start = originalData[0][0]; //the first element so the starting class

		//need to go through summing uo each of the respective elements and then averaging, adding to the onePC and increasing the class number
	}

	

	/*RUN TESTS ON THESE RESULTING VECTORS*/

	vector<double> getDataOriginal() {
		return dataOriginal;
	}

	vector<double> getDataNormalised() {
		return dataZNormalised;
	}

	double getOriginalMean() {
		return originalMean;
	}

	double getOriginalVariance() {
		return originalVariance;
	}

	double getZMean() {
		return zMean;
	}

	double getZVariance() {
		return zVariance;
	}



};
