//#include "distances.h"
#include "PAA.cpp";
#include "APCA.cpp";
using namespace std;

/*HOW TO MEASURE HOW LONG A FUNCTION TAKES TO RUN
	code:

	#include<chrono>
	usig namespace std::chrono;

	//GET THE TIME BEFORE THE FUNCTION IS CALLED
	auto start = high_resolution_clock::now();

	//GET THE TIME AFTER THE FUNCTION IS CALLED
	auto stop high_resolution_clock::now();

	//GET THE DIFFERENCE IN TIME POINTS AND CAST TO REQUIRED UNITS
	auto duration = duration_cast<microseconds>(start-stop)

	//GET THE VALUE OF THE DURATION
	//to get the value of the duration we need to use the count function
	//will print out duration
	cout << duration.count() << endl;

	NOTES:
	//auto type can be used when the initialisation is obvious and the complier will work out the type
	//in this istance it is declaring one to store time

*/

class distances {
private:

	//average distance between all the points
	double euclidianDistance;
	//average distance between all the points
	double euclidianDistanceAverage;
	//the distances stored in a vector aka the differences between every point
	vector<double> allDistances;

	//Calculates the Eucldiean Distance between two points
	double calcDistance(double firstPoint, double secondPoint) {

		double value = (firstPoint - secondPoint) * (firstPoint - secondPoint);
		double valueSqrt = sqrt(value);
		return valueSqrt;
	}

	/*OLD methods do not use*/
	/*
	double euclideanDistance(APCA apca, PAA paa) {
		vector<double> apcaPoints = apca.getApcaRepresentation();
		vector<double> apcaSegemnts = apca.getSegments();

		vector<double> paaPoints = paa.getPAAvector();
		int paaModulo = paa.getModulo();

		int apcaSize = apcaPoints.size();
		int paaSize = paaPoints.size();

		int length;
		if (apcaSize > paaSize) {
			length = apcaSize;
		}
		else {
			length = paaSize;
		}


	}

	vector<double> euclideanDistance(APCA apca, vector<double> originalSeries) {
		vector<double> euDistances;

		vector<double> apcaPoints = apca.getApcaRepresentation();
		vector<double> apcaSegemnts = apca.getSegments();
		//Looping via original series points
		//get the vector before truncation, works by including the extra zeroes before truncation
		vector<double> apcaVectOr = apca.getDtwVector();
		for (int i = 0; i < originalSeries.size(); i++) {
			double val = calcDistance(originalSeries[i], apcaVectOr[i]);
			euDistances.push_back(val);
		}
		return euDistances;
	}

	vector<double> euclideanDistanceShort(APCA apca, vector<double> originalSeries) {
		vector<double> euDistances;

		vector<double> apcaPoints = apca.getApcaRepresentation();
		vector<double> apcaSegemnts = apca.getSegments();

		int pos = 0;//pos in the original series

		for (int i = 0; i < apcaPoints.size(); i++) {
			for (int j = 0; j < apcaSegemnts[i]; j++) {
				double val = calcDistance(originalSeries[pos], apcaPoints[i]);
				euDistances.push_back(val);
				pos++;
			}
		}
		cout << " pos" << pos << endl;
		return euDistances;
	}


	*/

	vector<double> euclideanDistanceGenPoints(vector<double> vect, vector<double> originalSeries) {
		vector<double> euDistances;

		for (int i = 0; i < originalSeries.size(); i++) {
			double val = calcDistance(originalSeries[i], vect[i]);
			euDistances.push_back(val);
		}
		return euDistances;
	}

	/*Method to calucalte euclidean distance*/
	double calcEuclideanDistance(vector<double> vect, vector<double> originalSeries) {
		double finalDistance=0;
		for (int i = 0; i < originalSeries.size(); i++) {
			double tempVal = (originalSeries[i] - vect[i]) * (originalSeries[i] - vect[i]);
			finalDistance += tempVal;
		}
		finalDistance = sqrt(finalDistance);
		return finalDistance;
	}
	

	/*
	//Euclidean distance between a paa representation and the original series
	vector<double> euclideanDistance(PAA paa, vector<double> originalSeries) {
		vector<double> euDistances;

		vector<double> paaPoints = paa.getPAAvector();
		int modulo = paa.getModulo();
		int lengthOfFrame = paa.getFrameLength();
		int numberOfFrames = paa.getNumberOfMainFrames();

		int pos = 0;//pos in the original series

		//Loop through the number of frames
		//compare each of them with the number of frames
		for (int i = 0; i < numberOfFrames; i++) {
			for (int j = 0; j < lengthOfFrame; j++) {
				//work out the eu distance 
				double val = calcDistance(originalSeries[pos], paaPoints[i]);
				euDistances.push_back(val);
				pos++;
			}
		}

		//for the final frame if modulo is not zero
		if (modulo > 0) {
			int lastIndex = paaPoints.size() - 1;
			for (int k = 0; k < modulo; k++) {
				double valTwo = calcDistance(originalSeries[pos], paaPoints[lastIndex]);
				//cout << " VALTWO  " << valTwo << endl;
				euDistances.push_back(valTwo);
				pos++;
			}
		}

		return euDistances;
	}
	*/

	//calculates the averageof all points in a vector
	/* METHOD NOT TO BE USED, INCORRECT APPRAOCH
	double calcAverageDistance(vector<double> dist) {
		double value = 0;
		for (int i = 0; i < dist.size(); i++) {
			value += dist[i];
		}
		value = value / dist.size();
		return value;
	}
	*/

	/*Nearest Neighbour Algorithm aka Similarity*/
	//uses dtw and eu
	//This method given a query (vector) and a set of base vectors
	//It will first compress the vectors using the APCA 
	//It will then compress the query vector using APCA
	//It will then use the input query to order the base set based on similiarity 
	//It will then order the compressed base set against the compressed query
	//the output will be a 2d vector contaning the order of the two sets in order of most to least similar
	vector<vector<double> > similarity(vector<double> query, vector<vector<double> > comparision, int M) {
		//Compress the query
		APCA qAPCA(query,M);
		//Compression storage for the 2d vector
		vector<vector<double> > compAPCA; //the points in the array
		vector<vector<double> > compAPCApoints; //the points in the corresponding comp apca points array
		//compress the comparision 2d vecotor
		for (int i = 0; i < comparision.size(); i++) {
			//temp vector to store 
			APCA temp(comparision[i], M);
			vector<double> tempAPCA = temp.getApcaRepresentation();
			vector<double> tempAPCAPoints = temp.getSegments();
		}
		//compute the similarity between the query and all of the vectors and rank
		vector<int> unCompOrder; //storage for the orders
		for (int k = 0; k < comparision.size(); k++) {
			
		}
	}

	 




public:
	/* OLD Constructors do not use
	distances(PAA paaObj, vector<double> OS) {
		allDistances = euclideanDistance(paaObj, OS);
		averageDistance = calcAverageDistance(allDistances);
	}


	distances(APCA apcaObj, vector<double> OS) {
		allDistances = euclideanDistance(apcaObj, OS);
		averageDistance = calcAverageDistance(allDistances);
	}
	*/

	distances(vector<double> VS, vector<double> OS) {
		//distances between indivudal points in each of the vectors
		allDistances = euclideanDistanceGenPoints(VS, OS);
		euclidianDistance = calcEuclideanDistance(VS, OS);
		euclidianDistanceAverage = euclidianDistance / OS.size();
	}

	double getEuclidianDistance() {
		return euclidianDistance;
	}

	double getEuclidianDistanceAverage() {
		return euclidianDistanceAverage;
	}

	vector<double> getallDistances() {
		return allDistances;
	}

};

class DTW {
private:
	double dtwDistance;


	//create a vector v1 in size, for the number of rows
	vector< vector<double> > createTable(int rowLength, int columnLength) {
		vector<double> columns;
		columns.resize(columnLength); //create a vector on number of columns
		//Creatinga vector or number of rows where each element is a copy of the number of columns vector
		vector<vector<double> > table(rowLength, columns);
		//return the table
		return table;
	}

	//method to measure the distance between two points (Euclidean distance)
	double distanceEU(double a, double b) {
		double dist = a - b;
		dist = dist * dist;
		dist = sqrt(dist);
		return dist;
	}

	//Method to fill out the distances within the table
	//orgiTable is a table that the final method needs to create to input into this table
	vector< vector<double> > tableFill(vector< vector<double> > origTable, vector<double> vect1, vector<double> vect2) {
		vector< vector<double> > tableToFill = origTable;

		//loop through every ce ll working out the distance between vect 1 and vect 2 at each point

		//travelling one row at a time (working out the distance for every column before moving onto the next column)
		for (int i = 0; i < tableToFill.size(); i++) { //travelling row by row
			for (int j = 0; j < (int)tableToFill[i].size(); j++) { //going through each column in the row
				tableToFill[i][j] = distanceEU(vect1[i], vect2[j]);
			}
		}

		return tableToFill;
	}

	//Creating a warping path table (accumlated cost of travel to generate a warping path next)
	vector< vector<double> > tableAccumTable(vector<vector<double> > costsTable) {
		//creating a table the same size as the costs table
		vector< vector<double> > accumTable = createTable(costsTable.size(), costsTable[0].size());
		//value in first cell is equal to the first cell
		//cout << costsTable[0][0] << endl;
		
		accumTable[0][0] =costsTable[0][0];

		//First row is the sum of all the element values previous to it and same for column
		//For columns
		for (int c = 1; c < (int)accumTable[0].size(); c++) {
			accumTable[0][c] = costsTable[0][c] + accumTable[0][c - 1];
		}
		//For rows
		for (int r = 1; r < (int)accumTable[0].size(); r++) {
			accumTable[r][0] = costsTable[r][0] + accumTable[r - 1][0];
		}

		//To fill in the table we need to use the formula:
		//Accumlated Cost(D(i,j))= min{D(i-1,j-1),D(i-1,j),D(i,j-1)+Distance(i,j)}
		for (int i = 1; i < (int)accumTable.size(); i++) { //looping through rows
			for (int j = 1; j < (int)accumTable[i].size(); j++) { //looping through each column within the row
				//previous steps in either straight or diagonals
				//add into vector
				vector<double> lessValues;
				double bothless = accumTable[i - 1][j - 1];
				lessValues.push_back(bothless);
				double iless = accumTable[i - 1][j - 1];
				lessValues.push_back(iless);
				double jless = accumTable[i][j - 1];
				lessValues.push_back(jless);
				//find the smallest item in the vector
				sort(lessValues.begin(), lessValues.end());
				double lowestValue = lessValues[0]; //gets the first item in the vector once it has been sorted from lowest to highest
				//Add into accum cost table 
				accumTable[i][j] = lowestValue + costsTable[i][j];
			}
		}
		return accumTable;
	}

	//back tracking to find optimal warping path
	vector< vector<int> > path(vector< vector<double> > accTable) {
		//To store the path we need to work out the path in a 1D vector and then convert into a 2D vector
		vector < vector<int> > twoDPath;
		vector<int> first = { (int)accTable.size() - 1, (int)accTable[0].size() - 1 }; //adding the first element
		twoDPath.push_back(first);

		/*
		vector<int> path;
		path.push_back((int) accTable.size() - 1);//First item is the last element in the accum table
		path.push_back((int) accTable[0].size() - 1); //using (int) to cast to int*/
		/* DYNAMIC 2D v1 ATTEMPT NOT WORKING
		vector< vector<double> > path; //Need to dynamically create this vector, will be a n (rows) by 2 ( columns) 2d vector
		the first element is the vector is the last element in the accumTable since we are going backwards
		vector<int> firstPoint = { (int) accTable.size() - 1, (int) accTable[0].size() - 1 }; //using (int) to cast to unsigned int
		path.push_back(firstPoint);*/
		int i = (int)accTable.size() - 1; //set variable for loop
		int j = (int)accTable[0].size() - 1; //set variable for loop
		while (i > 0 && j > 0) {
			if (i == 0) {
				j = j - 1;
			}
			else if (j == 0) {
				i = i - 1;
			}
			else {

				//Less values from previous method
				vector<double> lessValue;
				double bless = accTable[i - 1][j - 1];
				lessValue.push_back(bless);
				double iles = accTable[i - 1][j - 1];
				lessValue.push_back(iles);
				double jles = accTable[i][j - 1];
				lessValue.push_back(jles);
				//find the smallest item in the vector
				sort(lessValue.begin(), lessValue.end());
				double smallestValue = lessValue[0]; //gets the first item in the vector once it has been sorted from lowest to highest

				if (accTable[i - 1][j] == smallestValue) {
					i = i - 1;
				}
				else if (accTable[i][j - 1] == smallestValue) {
					j = j - 1;
				}
				else {
					i = i - 1;
					j = j - 1;
				}
			}

			vector<int> points = { i,j };
			twoDPath.push_back(points);

			//1D-2D method
			//path.push_back(i);
			//path.push_back(j); //adding in the new path value
		}

		//adding in the final value, the first element in the accumTable
		/*DYNAMIC CREATION OF 2D ARRAY*/
		vector<int> lastItem = { 0,0 };
		twoDPath.push_back(lastItem);
		//Invert vector so it is in the right order
		reverse(twoDPath.begin(), twoDPath.end());

		/* NON DYNAMIC CREATING 1D-2D
		path.push_back(0);
		path.push_back(0);

		//Convert the 1D vector into a 2D vector
		int length = path.size();
		double DLength = length / 2;
		//position in 1d vector
		int pos = 0;
		//Create a 2D vector
		vector< vector<double> > finalPath = createTable(DLength, 2);
		for (int i = 0; i < DLength; i++) { //looping through rows
			for (int j = 0; j < 2; j++) { //looping through columns
				finalPath[i][j] = path[pos];
				pos++;
			}
		}*/
		return twoDPath;
	}

	//Method to use the final path 2D array to work out the euclidean distances of the mapped points
	//posible to use the orginial distances table to find the distances between the two points and add them all up
	double DTWDistance(vector< vector<int> > DTWPath, vector< vector<double> > tableaccumTable) {
		double distance = 0;

		for (int i = 0; i < (int)DTWPath.size(); i++) {
			//retrive points from the ith vector
			int x = DTWPath[i][0]; //row
			int y = DTWPath[i][1]; //column
			//get value from the table
			double cost = tableaccumTable[x][y];
			distance += cost; //add to distance
			cost = 0; // clear

		}
		return distance;
	}




public:
	DTW(vector<double> v1, vector<double> v2) {
		vector< vector<double> > blankTable = createTable(v1.size(), v2.size());
		vector< vector<double> > fillTable = tableFill(blankTable, v1, v2);
		vector< vector<double> > accumTable = tableAccumTable(fillTable);
		vector< vector<int> > DTWpath = path(accumTable);
		double distance = DTWDistance(DTWpath, fillTable);
		dtwDistance = distance;

	}

	double returnDTWDistance() {
		return dtwDistance;
	}

	//displaying a 2d vector
	void printVect(vector< vector<double> > vect) {
		for (int i = 0; i < (int)vect.size(); i++) {
			for (int j = 0; j < (int)vect[i].size(); j++) {
				cout << vect[i][j] << " ";
			}
		}
	}

	void printVect(vector< vector<int> > vect) {
		for (int i = 0; i < (int)vect.size(); i++) {
			for (int j = 0; j < (int)vect[i].size(); j++) {
				cout << vect[i][j] << " ";
			}
		}
	}


}; ;