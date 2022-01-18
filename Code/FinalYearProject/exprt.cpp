//#include "exprt.h"


//#include "imp.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


class exprt{

private:

	

public:

	void createfileComp(bool paat, bool apcat, bool tst, vector<double> PAApoints, int PAAlengthOfFrames, int PAAmodulo, vector<double> APCAlengths, vector<double> APCApoints, vector<double> TSpoitns) {
		//create an ofstream for the file outputs
		ofstream outFile;
		//creating a file to output to
		string fileName = "points.csv";
		outFile.open(fileName);

		//set up file headers
		outFile << "class" << "," << "x" << "," << "y" << endl;

		/*
		EACH CLASS HAS NULL CHECK SO THAT WE CAN OMMIT THEM IF THEY ARE NOT BEING USED
		*/

		/*FOR THE ORIGINAL TIME SERIES*/
		//if ts data has been included
		if (tst == true) {
			int TScount = 0;
			for (int y = 0; y < TSpoitns.size(); y++) {
				outFile << "TS" << "," << TScount << "," << TSpoitns[y] << endl;
				TScount++;
			}
		}

		/*FOR THE PAA POINTS*/
		if (paat == true) {
			//need method for if modulo is zero or not zero
			int paaCount = 0;
			if (PAAmodulo == 0) {
				//add the points from the vector
				for (int i = 0; i < PAApoints.size(); i++) {
					for (int j = 0; j < PAAlengthOfFrames; j++) {
						outFile << "PAA" << "," << paaCount << "," << PAApoints[i] << endl;
						paaCount++;
					}
				}
			}
			else {
				//add the points for the non modulo values
				for (int i = 0; i < PAApoints.size() - 1; i++) {
					for (int j = 0; j < PAAlengthOfFrames; j++) {
						outFile << "PAA" << "," << paaCount << "," << PAApoints[i] << endl;
						paaCount++;
					}
				}
				//add the modulo item in
				for (int k = 0; k < PAAmodulo; k++) {
					outFile << "PAA" << "," << paaCount << "," << PAApoints[PAApoints.size() - 1] << endl;
					paaCount++;
				}
			}
		}
		/*FOR THE APCA POINTS*/
		if (apcat == true) {
			int APCAcount = 0;
			for (int m = 0; m < APCApoints.size(); m++) {
				for (int h = 0; h < APCAlengths[m]; h++) {
					outFile << "APCA" << APCAcount << "," << APCApoints[m] << endl;
					APCAcount++;
				}
			}
		}
		outFile.close();
	}

	/*Simple export*/
	void createfileSimp(bool paat, bool apcat, bool tst, vector<double> APCAvect, vector<double> PAAfullVect, vector<double> TSvect) {
		//create an ofstream for the file outputs
		ofstream outFile;
		
		//creating a file to output to
		string fileName = "points.csv";
		outFile.open(fileName);

		//set up file headers
		outFile << "class" << "," << "x" << "," << "y" << endl;

		/*
		EACH CLASS HAS NULL CHECK SO THAT WE CAN OMMIT THEM IF THEY ARE NOT BEING USED
		*/

		/*FOR THE ORIGINAL PAA Object*/
		//if ts data has been included
		if (tst == true) {
			int TScount = 0;
			for (int y = 0; y < TSvect.size(); y++) {
				outFile << "TS" << "," << TScount << "," << TSvect[y] << endl;
				TScount++;
			}
		}
		//cout << "APCAvect input size:" << APCAvect.size() << endl;
		/*FOR THE ORIGINAL TIME SERIES*/
		//if ts data has been included
		if (tst == true) {
			int apcacCount = 0;
			for (int j = 0; j < APCAvect.size(); j++) {
				outFile << "APCA" << "," << apcacCount << "," << APCAvect[j] << endl;
				apcacCount++;
			}
		}

		/*FOR THE ORIGINAL TIME SERIES*/
		//if ts data has been included
		if (tst == true) {
			int paaCount = 0;
			for (int i = 0; i < PAAfullVect.size(); i++) {
				outFile << "PAA" << "," << paaCount << "," << PAAfullVect[i] << endl;
				paaCount++;
			}
		}

		outFile.close();

	}

	/*exportOfDifferent APCA M Vlaues*/
	void createFileAPCAM(int lowestM, int highestM, int steps, vector< vector<double> > allAPCAPoints) {
		//create an ofstream for the file outputs
		ofstream outFile;

		//creating a file to output to
		string fileName = "APCAm.csv";
		outFile.open(fileName);

		//set up file headers
		outFile << "frame length" << "," << "x" << "," << "y" << endl;

		//cout << "APCAvect input size:" << APCAvect.size() << endl;
		/*FOR THE ORIGINAL TIME SERIES*/
		//if ts data has been included
		int m = lowestM;

		for (int i = 0; i < allAPCAPoints.size(); i++) {
			
			int apcacCount = 0;
			for (int j = 0; j < allAPCAPoints[i].size(); j++) {
				outFile << m << "," << apcacCount << "," << allAPCAPoints[i][j] << endl;
				apcacCount++;
			}
			//incrase m to next one
			m+=steps;
		}

	
		outFile.close();

	}

	/*exportOfDifferent APCA M Vlaues*/
	void createFilePAAM(int lowestM, int highestM, int steps, vector< vector<double> > allAPCAPoints) {
		//create an ofstream for the file outputs
		ofstream outFile;

		//creating a file to output to
		string fileName = "PAAm.csv";
		outFile.open(fileName);

		//set up file headers
		outFile << "frame length" << "," << "x" << "," << "y" << endl;

		//cout << "APCAvect input size:" << APCAvect.size() << endl;
		/*FOR THE ORIGINAL TIME SERIES*/
		//if ts data has been included
		int m = lowestM;

		for (int i = 0; i < allAPCAPoints.size(); i++) {

			int apcacCount = 0;
			for (int j = 0; j < allAPCAPoints[i].size(); j++) {
				outFile << m << "," << apcacCount << "," << allAPCAPoints[i][j] << endl;
				apcacCount++;
			}
			//incrase m to next one
			m += steps;
		}


		outFile.close();

	}


	vector<double> createPAAVect(vector<double> PAApoints, int PAAlengthOfFrames, int PAAmodulo) {
		//create an ofstream for the file outputs
		ofstream outFile;
		ofstream fs;
		//creating a file to output to
		string fileName = "points.csv";

		//set up file headers
		outFile << "class" << "x" << "," << "y" << endl;

		//for the PAA points
		//need method for if modulo is zero or not zero
		int paaCount = 0;
		if (PAAmodulo == 0) {
			//add the points from the vector
			for (int i = 0; i < PAApoints.size(); i++) {
				for (int j = 0; j < PAAlengthOfFrames; j++) {
					outFile << "PAA" << paaCount << "," << PAApoints[i] << endl;
					paaCount++;
				}
			}
		}
		else {
			//add the points for the non modulo values
			for (int i = 0; i < PAApoints.size() - 1; i++) {
				for (int j = 0; j < PAAlengthOfFrames; j++) {
					outFile << "PAA" << paaCount << "," << PAApoints[i] << endl;
					paaCount++;
				}
			}
			//add the modulo item in
			for (int k = 0; k < PAAmodulo; k++) {
				outFile << "PAA" << paaCount << "," << PAApoints[PAApoints.size() - 1] << endl;
				paaCount++;
			}
		}
	}
	
	void createFileForAPCA(vector<double> APCAlengths, vector<double> APCApoints) {
		//create an ofstream for the file outputs
		ofstream outFile;
		ofstream fs;
		//creating a file to output to
		string fileName = "points.csv";

		//set up file headers
		outFile << "class" << "length" << "," << "value" << endl;

	
		/*FOR THE APCA POINTS*/
		int APCAcount = 0;
		for (int m = 0; m < APCApoints.size(); m++) {
			for (int h = 0; h < APCAlengths[m]; h++) {
				outFile << "APCA" << APCAcount << "," << APCApoints[m] << endl;
				APCAcount++;
			}
		}
	}
	

	void createFileForDTW(vector< vector<int> > path) {

		//create an ofstream for the file outputs
		ofstream outFile;
		ofstream fs;
		//creating a file to output to
		string fileName = "points.csv";

		//set up file headers
		outFile << "vect1" << "," << "vect2" << endl;

		/*
		0,0 0,1
		1,0 1,1
		2,0 2,1
		3,0 3,1
		*/

		for (int i = 0; i < path.size(); i++) {
			outFile << path[i][0] << "," << path[i][1] << endl;
		}  
	}


};