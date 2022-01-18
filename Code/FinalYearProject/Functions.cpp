#include <iostream>
#include <vector>
#include "timeSeries.cpp";
//Two Below are included with the distnaces class
//#include "PAA.cpp";
//#include "APCA.cpp";
#include "distances.cpp";
#include "imp.cpp";
#include "exprt.cpp";
using namespace std;


class Functions {
private:

public:
	/*METHOD USED IN CREATION OF THE APCA VS PAA TEST*/
	//Method that was used to create the tests
	//To create tests use the appropriate file name (check report for avaiable datasets)
	//Results will be in a csv file within the project folder
	void runTest(string fileWithData, int PAAFrames, int APCAFrames) {
		string fileToUse = fileWithData + ".txt";
		string exportName = fileWithData + "Results.txt";
		imp impor(fileToUse, true, false);
		vector < vector<double> > data = impor.getUCRData();
		//opening file to write to
		ofstream outFile;
		//creating a file to output to
		string fileName = exportName;
		outFile.open(fileName);
		//outFile << "frame" << "," << "apcaDur" << "," << "paaDur" << "," << "difDue" << endl; //headers for csv
		outFile << "vector" << "," << "PAA Frames" << "," << "APCA Frames" << "," << "PAA Eu" << "," << "APCAA Eu" << "," << "Dif Eu" << "," << "PAA Dtw" << "," << "APCA Dtw" << "," << "Dif Dtw" << "," << "PAA tik" << "," << "APCA tik" << "," << "Dif tik" << endl; //header
		//M and N options
		int paaFrame = PAAFrames;
		int apcaFrame = APCAFrames;
		//looping through working out all metrics and then comparing
		int maxSize = data.size();
		for (int i = 0; i < maxSize; i++) {
			vector<double> ts = data[i];

			//Construct PAA
			PAA paaRep(ts, paaFrame);
			vector<double> paaVectN = paaRep.getPAAdtw();

			//construct apca
			APCA apcaRep(ts, apcaFrame);
			vector<double> apcaVect = apcaRep.getDtwVector();

			std::cout << "paaNF: " << paaRep.getNumberOfFrames() << " apcaF:" << apcaRep.getApcaRepresentation().size() << "count :" << i << " of: " << maxSize << endl;

			//work out Eu distances

			distances paaEu(ts, paaVectN);
			double paaEuVN = paaEu.getEuclidianDistance();

			distances apcaEu(ts, apcaVect);
			double apcaEuV = apcaEu.getEuclidianDistance();

			double difEu = paaEuVN - apcaEuV;

			//DTW distances
			DTW paaDtw(ts, paaVectN);
			double paaDtwV = paaDtw.returnDTWDistance();

			DTW apcaDtw(ts, apcaVect);
			double apcaDtwV = apcaDtw.returnDTWDistance();

			double difDtw = paaDtwV - apcaDtwV;

			//tik
			long paaDur = paaRep.getDurationPAA();
			long apcaDur = apcaRep.getDuration();
			long difDur = paaDur - apcaDur;

			//outFile << i << "," << apcaDur << "," << paaDur << "," << difDur << endl; was used for the time frame measures

			outFile << i << "," << paaRep.getNumberOfFrames() << "," << apcaRep.getApcaRepresentation().size() << "," << paaEuVN << "," << apcaEuV << "," << difEu << "," << paaDtwV << "," << apcaDtwV << "," << difDtw << "," << paaDur << "," << apcaDur << "," << difDur << endl;
			//std::cout << "EU dif:" << difEu << " DTW diff:" << difDtw << " APCA dtw: "<< paaDtwV << " PAA dwt: " << paaDtwV<< endl;
		}

		std::cout << "end" << endl;
		outFile.close();
	}

	//when generating examples from the UCR data
	//datapoint: which vector/row inside the UCR file do you wish to run the algorithms for
	void runCompareUCR(string filename, int PAAFrames, int APCAFrames, int datapoint) {
		cout << "STARTING" << endl;
		imp impor(filename, true, false);
		vector < vector<double> > data = impor.getUCRData();
		vector<double> dataRow = data[datapoint];
		cout << "Data has been imported" << endl;

		//Creating the PAA representation and vector
		PAA paaRep(dataRow, PAAFrames);
		vector<double> paaVect = paaRep.getPAAdtw();

		//Creating APCA representation and vector
		APCA apcaRep(dataRow, APCAFrames);
		vector<double> apcaVect = apcaRep.getDtwVector();

		cout << "Dimensionality reduction methods run, working out distances" << endl;

		//work out Eu distances
		distances paaEu(dataRow, paaVect);
		double paaEuD = paaEu.getEuclidianDistance();

		distances apcaEu(dataRow, apcaVect);
		double apcaEuD = apcaEu.getEuclidianDistance();

		double difEu = paaEuD - apcaEuD;

		//DTW distances
		DTW paaDtw(dataRow, paaVect);
		double paaDtwV = paaDtw.returnDTWDistance();

		DTW apcaDtw(dataRow, apcaVect);
		double apcaDtwV = apcaDtw.returnDTWDistance();

		double difDtw = paaDtwV - apcaDtwV;

		//tik
		long paaDur = paaRep.getDurationPAA();
		long apcaDur = apcaRep.getDuration();
		long difDur = paaDur - apcaDur;

		//printing the differences to console

		cout << "PAA Euclidean Distance:" << paaEuD << " PAA DTW Distance:" << paaDtwV << " PAA Duration:" << paaDur << endl; //paa values
		cout << "APCA Euclidean Distance:" << apcaEuD << " APCA DTW Distance:" << apcaDtwV << " APCA Duration:" << apcaDur << endl; //apca values
		cout << "Euclidean Distance Difference (PAA-APCA):" << difEu << " DTW Distance Difference (PAA-APCA):" << difDtw << " PAA Duration Difference (PAA-APCA):" << difDur << endl; //difference values
		cout << endl;
		cout << endl;
		cout << endl;

		exprt expor; // to export the data to draw the graphs
		expor.createfileSimp(true, true, true, apcaVect, paaVect, dataRow); // creating points file for points

		//run the python sctipt
		system("t2.py"); 
		cout << "Finished" << endl; //once the algorithym has run 
	}

	//when generating using examples from normal CSV files
	//input filename including extension, the numbner of paa frames, the apca coeffient and a boolean if the data has is normalised or not
	void runCompareCSV(string filename, int PAAFrames, int APCAFrames, bool normalized) {
		vector<double> valuesN; // vector to store the values
		imp impor = imp("mean2var3.txt", false, false);
		if (normalized == true) {
			valuesN = impor.getDataOriginal(); // if the data is normalised
		}
		else {
			valuesN = impor.getDataNormalised(); // if the data is not normalised
		}

		//Creating the PAA representation and vector
		PAA paaRep(valuesN, PAAFrames);
		vector<double> paaVect = paaRep.getPAAdtw();

		//Creating APCA representation and vector
		APCA apcaRep(valuesN, APCAFrames);
		vector<double> apcaVect = apcaRep.getDtwVector();

		//work out Eu distances
		distances paaEu(valuesN, paaVect);
		double paaEuD = paaEu.getEuclidianDistance();

		distances apcaEu(valuesN, apcaVect);
		double apcaEuD = apcaEu.getEuclidianDistance();

		double difEu = paaEuD - apcaEuD;

		//DTW distances
		DTW paaDtw(valuesN, paaVect);
		double paaDtwV = paaDtw.returnDTWDistance();

		DTW apcaDtw(valuesN, apcaVect);
		double apcaDtwV = apcaDtw.returnDTWDistance();

		double difDtw = paaDtwV - apcaDtwV;

		//tik
		long paaDur = paaRep.getDurationPAA();
		long apcaDur = apcaRep.getDuration();
		long difDur = paaDur - apcaDur;

		//printing the differences to console

		cout << "PAA Euclidean Distance:" << paaEuD << " PAA DTW Distance:" << paaDtwV << " PAA Duration:" << paaDur << endl; //paa values
		cout << "APCA Euclidean Distance:" << apcaEuD << " APCA DTW Distance:" << apcaDtwV << " APCA Duration:" << apcaDur << endl; //apca values
		cout << "Euclidean Distance Difference (PAA-APCA):" << difEu << " DTW Distance Difference (PAA-APCA):" << difDtw << " PAA Duration Difference (PAA-APCA):" << difDur << endl; //difference values

		exprt expor; // to export the data to draw the graphs
		expor.createfileSimp(true, true, true, apcaVect, paaVect, valuesN); // creating points file for points

		//run the python sctipt
		system("t2.py");
		cout << "Finished" << endl; //once the algorithym has run 
	}
	
	//using a synthetic time series rather than a real dataset
	//the length of the time series, number of paa frames and the apca coefficent 
	void runCompareSynth(int tsLength, int PAAFrames, int APCAFrames) {
		timeSeries ts = timeSeries(tsLength, 0, 1);
		vector<double> vect = ts.getPointsTS();

		//Creating the PAA representation and vector
		PAA paaRep(vect, PAAFrames);
		vector<double> paaVect = paaRep.getPAAdtw();

		//Creating APCA representation and vector
		APCA apcaRep(vect, APCAFrames);
		vector<double> apcaVect = apcaRep.getDtwVector();

		//work out Eu distances
		distances paaEu(vect, paaVect);
		double paaEuD = paaEu.getEuclidianDistance();

		distances apcaEu(vect, apcaVect);
		double apcaEuD = apcaEu.getEuclidianDistance();

		double difEu = paaEuD - apcaEuD;

		//DTW distances
		DTW paaDtw(vect, paaVect);
		double paaDtwV = paaDtw.returnDTWDistance();

		DTW apcaDtw(vect, apcaVect);
		double apcaDtwV = apcaDtw.returnDTWDistance();

		double difDtw = paaDtwV - apcaDtwV;

		//tik
		long paaDur = paaRep.getDurationPAA();
		long apcaDur = apcaRep.getDuration();
		long difDur = paaDur - apcaDur;

		//printing the differences to console

		cout << "PAA Euclidean Distance:" << paaEuD << " PAA DTW Distance:" << paaDtwV << " PAA Duration:" << paaDur << endl; //paa values
		cout << "APCA Euclidean Distance:" << apcaEuD << " APCA DTW Distance:" << apcaDtwV << " APCA Duration:" << apcaDur << endl; //apca values
		cout << "Euclidean Distance Difference (PAA-APCA):" << difEu << " DTW Distance Difference (PAA-APCA):" << difDtw << " PAA Duration Difference (PAA-APCA):" << difDur << endl; //difference values

		exprt expor; // to export the data to draw the graphs
		expor.createfileSimp(true, true, true, apcaVect, paaVect, vect); // creating points file for points

		//run the python sctipt
		system("t2.py");
		cout << "Finished" << endl; //once the algorithym has run 
	}

};
