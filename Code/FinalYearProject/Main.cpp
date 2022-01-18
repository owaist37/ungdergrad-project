
#include "Functions.cpp";
/*Incldued with the functions class*/
/*
#include <iostream>
#include <vector>
#include "timeSeries.cpp";
//Two Below are included with the distnaces class
//#include "PAA.cpp";
//#include "APCA.cpp";
#include "distances.cpp";
#include "imp.cpp";
#include "exprt.cpp";
//#include "visual.cpp";
//#include "DTW.cpp";
using namespace std;
*/


//main function
int main()
{
	/* TEST TO SEE IF TS WORKED
	timeSeries ts;
	for (int i = 0; i < 100; i++) {
	cout << " x_i = " << ts.normalRandom(1,1) << endl;
	}*/

	/*TEST FOR PAA
	vector<double> original = {7,5,5,3,3,3,4,6};
	PAA paa = PAA(orginial,4);
	vector<double> transformedPAA = paa.getPAAvector();
	for (int i = 0; i < transformedPAA.size(); i++) {
	cout << " x_i = " << transformedPAA[i] << endl;
	}*/

	/*TESTS FOR APCA*/
	/* TEST FOR PADDING - PADDING WORKS
	test padding
	vector<double> padTest = { 1,2,3,4,5,6 };
	vector<double> padded = apca.paddTimeSeries(padTest);
	for (int i = 0; i < padded.size(); i++) {
	cout << " x_i = " << padded[i] << endl;
	}*/
	/*TEST FOR DISCRETE HAAR WAVELET TRANSFORM*/
	//vector<double> original = { 7,5,5,3,3,3,4,6 };
	//vector<double> orginalToHaar = apca.DHWT(original); Haar works gives result below
	//vector<double> Haar = apca.runDHWT(original);//{ 4.5,0.5,1,-1,1,1,0,-1 };
	//vector<double> normalised = apca.normalise(original); normalising does not yet work
	//vector<double> transformed = apca.inverseHDWTC(Haar); //Invrse Haar Transform works
	//vector<double> normalisedVAlues = apca.getNormalised();
	//vector<double> transformed = apca.getHighestM(Haar); //works
	//vector<double> apcaVector = apca.runAPCA(original);
	//vector<double> repalced = apca.replaceApproxWithExact(apcaVector, original); replace works
	//for (int i = 0; i < apcaVector.size(); i++) {
	//	cout << " x_i = " << apcaVector[i] << endl;
	//}
	//ALL APCA METHODS WORKING


	/*
	//TEST TOGTHER
	timeSeries ts = timeSeries(1000, 2, 3);
	APCA apcaObj = APCA( ts.getPointsTS(),500);
	vector<double> apcaRep = apcaObj.getApcaRepresentation();

	//PAA paa = PAA(ts.getPointsTS(), 25);
	//vector<double> paaRep = paa.getPAAvector();
	int c = 0;
	for (int i = 0; i < apcaRep.size(); i++) {
		cout << c <<"= " << apcaRep[i] << endl;
		c++;
	}
	*/


	/*
	//Test for new PAA
	vector<double> vect = {1,1,2,2,3,3,4,6};
	cout << "vectLength " << vect.size() << endl;
	PAA paaTwo = PAA(vect, 3);
	cout << "MODULO " << paaTwo.getModulo() << endl;
	vector<double> paaTwoV = paaTwo.getPAAvector();
	for (int i = 0; i < paaTwoV.size(); i++) {
		cout << " x_i = " << paaTwoV[i] << endl;
	}
	*/

	/* EU DISTANCE BETWEEN ORIGINAL AND PAA WORKS
	vector<double> vect = {1,2,3,4,5,6,7};
	PAA paaTwo = PAA(vect, 2);
	cout << "MODULO " << paaTwo.getModulo() << endl;

	distances distanceTest = distances(paaTwo, vect);
	vector<double> paaTwoV = paaTwo.getPAAvector();

	cout << "PAA" << endl;
	for (int i = 0; i < paaTwoV.size(); i++) {
		cout << " x_i = " << paaTwoV[i] << endl;
	}

	vector<double> distTest = distanceTest.getallDistances();
	cout << "TOTALAVERAGE" << distanceTest.getAverageDistances() << endl;

	for (int i = 0; i < distTest.size(); i++) {
		cout << " x_i = " << distTest[i] << endl;
	}
	*/

	/* EU DISTNACE FOR APCA WORKS
	vector<double> vect = {1,2,3,4,5,6,7,8};
	APCA apcaOBj = APCA(4, vect);
	vector<double> apcaRep = apcaOBj.getApcaRepresentation();

	for (int i = 0; i < apcaRep.size(); i++) {
		cout << " APCAREP: = " << apcaRep[i] << endl;
	}

	distances dist = distances(apcaOBj, vect);
	double distTotal = dist.getAverageDistances();
	cout << " AVGDIST" << distTotal << endl;

	vector<double> distancesVect = dist.getallDistances();
	for (int j = 0; j < distancesVect.size(); j++) {
		cout << " x_i = " << distancesVect[j] << endl;
	}
	*/

	//APCA representation doesnt work with a low number of frames?
	/*  APCA Produces lower EU
	timeSeries ts = timeSeries(1000, 0, 1);
	vector<double> vect = ts.getPointsTS();

	PAA paaObj = PAA(vect, 50);

	//Make sure APCA segments = PAA segments/2
	int numberOfSegments = paaObj.getPAAvector().size();
	int numberOfAPCASegmetns = numberOfSegments / 2;

	APCA apcaObj = APCA(vect, numberOfAPCASegmetns);

	//calculate the distances between the two
	distances distOne = distances(apcaObj, vect);
	distances distTwo = distances(paaObj, vect);

	//work out the difference between the two points, negative number needed
	double diffBetweenTwo = distOne.getAverageDistances() - distTwo.getAverageDistances();

	cout << " APCA EuDist " << distOne.getAverageDistances() << endl;
	cout << " PAA EuDist " << distTwo.getAverageDistances() << endl;
	cout << " Difference " << diffBetweenTwo << endl;
	*/

	/* reading txt and csv files works
	string file = "data.txt";
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
	cout << " size " << valuesD.size() << endl;
	for (int j = 0; j < valuesD.size(); j++) {
		cout << valuesD[j] << endl;
	}
		*/


	/* IMPORT AND Z NORMALISATION WORK
	//timeSeries ts = timeSeries(1000, 2, 3);
	//vector<double> vect = ts.getPointsTS();
	imp impor = imp("data.csv");



	double originalMean=impor.getOriginalMean();
	cout << " OMEAN" << originalMean << endl;
	double originalVariance=impor.getOriginalVariance();
	cout << " OVAR" << originalVariance << endl;
	double zMean= impor.getZMean();
	cout << " ZMEAN " << zMean << endl;
	double zVariance=impor.getZVariance();
	cout << " ZVAR " << zVariance << endl;


	vector<double> valuesO = impor.getDataOriginal();
	for (int m = 0; m < valuesO.size(); m++) {
		cout << "ORGINIAL" << valuesO[m] << endl;
	}


	vector<double> valuesN = impor.getDataNormalised();
	for (int jk = 0; jk < valuesN.size(); jk++) {
		cout << "NORMALISED" << valuesN[jk] << endl;
	}*/


	/*TEST RUN FOR MEETING*//*
	timeSeries ts = timeSeries(10000, 0, 1);
	vector<double> vect = ts.getPointsTS();

	PAA paaObj = PAA(vect, 350);

	//Make sure APCA segments = PAA segments/2
	int numberOfSegments = paaObj.getPAAvector().size();
	int numberOfAPCASegmetns = numberOfSegments / 2;

	APCA apcaObj = APCA(vect, numberOfAPCASegmetns);

	//calculate the distances between the two
	distances distOne = distances(apcaObj, vect);
	distances distTwo = distances(paaObj, vect);

	//work out the difference between the two points, negative number needed
	double diffBetweenTwo = distTwo.getAverageDistances() - distOne.getAverageDistances();

	cout << " APCA EuDist " << distOne.getAverageDistances() << endl;
	cout << " PAA EuDist " << distTwo.getAverageDistances() << endl;
	cout << " Difference " << diffBetweenTwo << endl;
	*/

	/*TEST OF IMPORTED FILES*/
	//file1: mean2var3.txt
	//file2: mean4var3.txt
	/*
	//import an normalise the data
	imp impor = imp("mean2var3.txt");
	vector<double> valuesN = impor.getDataNormalised();

	//compare the original and new means and variances
	double originalMean = impor.getOriginalMean();
	cout << " OMEAN" << originalMean << endl;
	double originalVariance = impor.getOriginalVariance();
	cout << " OVAR" << originalVariance << endl;
	double zMean = impor.getZMean();
	cout << " ZMEAN " << zMean << endl;
	double zVariance = impor.getZVariance();
	cout << " ZVAR " << zVariance << endl;

	//create a paa object
	PAA paaObj = PAA(valuesN, 500);

	//Make sure APCA segments = PAA segments/2
	int numberOfSegments = paaObj.getPAAvector().size();
	int numberOfAPCASegmetns = numberOfSegments / 2;

	APCA apcaObj = APCA(valuesN, numberOfAPCASegmetns);

	//calculate the distances between the two
	distances distOne = distances(apcaObj, valuesN);
	distances distTwo = distances(paaObj, valuesN);

	//work out the difference between the two points, negative number needed
	double diffBetweenTwo = distTwo.getAverageDistances() - distOne.getAverageDistances();

	cout << " APCA EuDist " << distOne.getAverageDistances() << endl;
	cout << " PAA EuDist " << distTwo.getAverageDistances() << endl;
	cout << " Difference " << diffBetweenTwo << endl;*/

	/*TESTING FOR DTW*//*
	vector<double> vect1 = { 1,1,2,3,2,0 };
	vector<double> vect2 = { 0,1,1,2,3,2 };
	DTW dtw = DTW(vect1, vect2);
	cout << " DTW distance " << dtw.returnDTWDistance() << endl;*/

	/*DTW testing for APCA and PAA WITH SHRUNK VECTORS*//*
	imp impor = imp("mean2var3.txt");
	vector<double> valuesN = impor.getDataNormalised();

	// create a paa object
	PAA paaObj = PAA(valuesN, 500);

	//Make sure APCA segments = PAA segments/2
	int numberOfSegments = paaObj.getPAAvector().size();
	int numberOfAPCASegmetns = numberOfSegments / 2;
	APCA apcaObj = APCA(valuesN, numberOfAPCASegmetns);

	//checking for DTW against PAA (different lengths)
	vector<double> PAAdtw = paaObj.getPAAdtw();
	DTW dtwPAA = DTW(valuesN, PAAdtw);
	cout << " DTW distance PPA shrunk " << dtwPAA.returnDTWDistance() << endl;

	//checking for DTW against APCA (different lengths)
	vector<double> APCAdtw = apcaObj.getApcaRepresentation();
	DTW dtwAPCA = DTW(valuesN, APCAdtw);
	cout << " DTW distance APCA shrunk " << dtwAPCA.returnDTWDistance() << endl;*/


	/*DTW testing using the orginal length of the vectors*//*
	imp impor = imp("mean2var3.txt");
	vector<double> valuesN = impor.getDataNormalised();
	// create a paa object
	PAA paaObj = PAA(valuesN, 500);
	//same size check complete
	//cout << " impor size " << valuesN.size() << endl;
	//cout << " PAA size " << paaObj.getPAAinOrginalLength().size()<< endl;
	DTW dtwAPCA = DTW(valuesN, paaObj.getPAAinOrginalLength());
	cout << " DTW distance PAA same size" << dtwAPCA.returnDTWDistance() << endl;*/

	/*
	timeSeries ts = timeSeries(100, 0, 1);
	vector<double> vect = ts.getPointsTS();

	PAA paaObj = PAA(vect, 50);

	//Make sure APCA segments = PAA segments/2
	int numberOfSegments = paaObj.getPAAvector().size();
	int numberOfAPCASegmetns = numberOfSegments / 2;

	APCA apcaObj = APCA(vect, numberOfAPCASegmetns);

	//calculate the distances between the two
	distances distOne = distances(apcaObj, vect);
	distances distTwo = distances(paaObj, vect);

	//work out the difference between the two points, negative number needed 
	double diffBetweenTwo = distOne.getAverageDistances() - distTwo.getAverageDistances();

	cout << " APCA size " << distOne.getallDistances().size() << endl;
	cout << " PAA size " << distTwo.getallDistances().size() << endl;
	cout << " Difference " << diffBetweenTwo << endl;
	*/

	/*TESTS FOR FILE CREATION/Exporting*/
	/*FILE CREATION WORKING
	timeSeries ts = timeSeries(1000, 0, 1);
	vector<double> vect = ts.getPointsTS();

	PAA paaObj = PAA(vect, 250);
	vector<double> paaVect = paaObj.createPAAVector();

	
	APCA apcaObj = APCA(vect, 100);
	vector<double> apcaVect = apcaObj.getDtwVector();

	for (int g = 0; g < apcaVect.size();g++) {
		cout << " APCA value " << apcaVect[g] << endl;
	}

	exprt exporting;
	exporting.createfileSimp(true,true,true,paaVect,apcaVect,vect);*/

	/*TEST FOR THE VISUAL CLASS*/
	//timeSeries ts = timeSeries(1000, 0, 1);
	/*
	imp impor("Fungi.txt", true, false);
	vector < vector<double> > data = impor.getUCRData();
	vector<double> vect = data[10];// ts.getPointsTS();

	PAA paaObj = PAA(vect, 10);
	vector<double> paaVect = paaObj.getPAAdtw();


	APCA apcaObj = APCA(vect, 11);
	vector<double> apcaVect = apcaObj.getDtwVector();

	cout << "Apca segments: " << apcaObj.getApcaRepresentation().size() << endl;
	int paasegs = paaObj.getNumberOfMainFrames();
	if (paaObj.getModulo() > 0) { paasegs++; }
	cout << "paa segments: " << paasegs << endl;

	cout << "APCA rep size: "<< apcaObj.getApcaRepresentation().size() << endl;
	cout << "APCA dtw/rep in full size: " << apcaVect.size() << endl;
	//cout << "APCA graphic size: " << apcaObj.getRepFull().size() << endl; not used anymore
	cout << "vect size: " <<  vect.size() << endl;
	exprt exporting;
	exporting.createfileSimp(true, true, true, apcaVect, paaVect, vect);
	*/
	/*WE WANT APCA BEFORE TRUNCATION FOR GRAPH*/

	//visuals vis;
	//vis.runPy();

	//runs the python scrypt
	//system("ts.py");
	//system("t2.py");
	
	/*TEST FOR UCR IMPORT, import ucr works into double vector*/
	/*imp impor;
	string file = "C:\/Dev\/DataToBeTested\/Chinatown\/Chinatown_TRAIN.tsv";
	//need to make sure i put an escape character for the functions
	vector < vector<double> > items = impor.readUCR(file);

	/*APCA and PAA functions with dynamic time warping algorithm*/	

	/*FIRST TESTS NOT USED IN FINAL */

	//5 datasets test 2
	//BME, length:128, paa frames:12 apca frames:7      paa framelength:10
	//Chinatown length:24 paa frames:6 apca frames:3    paa framelength:4
	//Fungi length:201 paa frames:64 apca frames:32     paa framelength:14
	//BirdChicken: 512, 22,11                           paa framelength:22
	//BeetleFly: 512, 22,11                             paa framelength:25
	//Ham: 431,30, 25                                   paa framelength:
	//PowerCons: 144,14, 8                              paa framelength:10
	//Synthetic: 1000,20, 10							paa framelength:200


	//imp impor("FordA.txt",true,false);
	//vector < vector<double> > data = impor.getUCRData();
	/*
	vector < vector<double> > data;
	for (int p = 0; p < 200; p++) {
		timeSeries ts = timeSeries(1000, 0, 1);
		vector<double> temp = ts.getPointsTS();
		data.push_back(temp);
	}
	
	// not running code when checking how large to make the frames
	bool runApcaVPaa =  true;//false;;//
	bool runApcaVPaaT = false; // stop the below method from running 
	if (runApcaVPaaT == true) {
		vector<double> datatest = data[0];
		//print data size
		cout << "ts length:" << datatest.size() << endl;
	}
	
	//opening file to write to
	ofstream outFile;
	//creating a file to output to
	string fileName = "FordAResults.csv";
	outFile.open(fileName);

	//set up file headers
	outFile << "vector" << "," << "PAA frames" << "," << "APCA frames" << "," << "paaEu" << "," << "apcaEu" << "," << "diffEu" << "," << "paaDTW" << "," << "apcaDTW" << "," << "diffDTW" << "," << "paaTik" << "," << "apcaTik" << "," << "diffTik" << endl;
	if (runApcaVPaa == true) {
		//get the length of the paa frames, in this case we want (depends on length of ts)
		int paaFrameLength = 50;
		int numberOfAPCASegmetns = 10;// set to around apca segements / 2;

		int testSize = data.size(); // data.size() to test all
		//Loop for the data
		for (int i = 1; i < testSize; i++) {

			PAA paaObj(data[i], paaFrameLength);
			//create the APCA Object
			APCA apcaObj = APCA(data[i], numberOfAPCASegmetns);
			int numberOfSegments = paaObj.getNumberOfMainFrames();

			//for the distances and for the graphs
			vector < double > apcaVecorFull = apcaObj.getDtwVector();
			vector<double> paaVectorFull = paaObj.getPAAdtw();

			//for distance metrics
			//calculate the distances between the two Euclidean 
			distances distAPCA = distances(apcaVecorFull, data[i]); //distances(apcaObj, data[i]);
			double apcaEU = distAPCA.getAverageDistances();
			distances distPAA = distances(paaVectorFull, data[i]);
			double paaEU = distPAA.getAverageDistances();
			double euDifference = paaEU - apcaEU;
			

			//cout << "apcaAVECTORFULL SIZE:" << apcaVecorFull.size() << endl;

			DTW dtwPAA(data[i], paaVectorFull);
			double paaDtw = dtwPAA.returnDTWDistance();
			DTW dtwAPCA(data[i], apcaVecorFull);
			double apcaDtw = dtwAPCA.returnDTWDistance();
			double dtwDifference = paaDtw - apcaDtw;

			float apcatik = apcaObj.getDuration();
			float paatik = paaObj.getDurationPAA();
			float tikDif = paatik - apcatik;

			int apcaFrames = apcaObj.getApcaRepresentation().size();

			//order
			cout << i << endl;
			//run (aka vecotr in file) paa frames, apca frames, paa eu distance, apca eu distance, eu difference, paa dtw, apca dtw, dtw diff, paa time, apca time, difference time
			outFile << i << "," << numberOfSegments << "," << apcaFrames << "," << paaEU << "," << apcaEU << "," << euDifference << "," << paaDtw << "," << apcaDtw << "," << dtwDifference << "," << paatik << "," << apcatik << "," << tikDif << endl;
			cout << i << "," << numberOfSegments << "," << apcaFrames << "," << paaEU << "," << apcaEU << "," << euDifference << "," << paaDtw << "," << apcaDtw << "," << dtwDifference << "," << paatik << "," << apcatik << "," << tikDif << endl;

		}

	}
	//outFile.close();
	cout << "end" << endl;
	*/
	/*
	imp impor("Ham.txt", true, false);
	vector < vector<double> > data = impor.getUCRData();
	bool runM = true;
	int mStart=1; //starting value of m
	int mCurrent =  mStart;
	int steps = 40; //number of frames increasing in steps steps
	int mEnd= 431; //ending value of m
	if (mCurrent == mEnd) { mCurrent = mEnd; }//do not go over the limit of the number of points
	vector<double> dataRow = data[5]; //row of the data to be operated on
	if (runM == true) {
		cout << "running paam" << endl;
		vector<vector<double> > APCAFinals;

		while (mCurrent < mEnd) {
			
			APCA apcats(dataRow, mCurrent);
			distances APCAdists = distances(apcats, dataRow);
			double apcaEuc = APCAdists.getAverageDistances();
			vector<double> apcaVectF = apcats.getDtwVector();
			DTW APCAdtw(dataRow, apcaVectF);
			double apcaDtw = APCAdtw.returnDTWDistance();
			float tikapca = apcats.getDuration();
			APCAFinals.push_back(apcaVectF);
			int sizeapca = apcats.getApcaRepresentation().size();
			cout << sizeapca << "," << apcaEuc << "," << apcaDtw << "," << tikapca << endl;
			
			
			PAA paats(dataRow, mCurrent);
			distances paaDist = distances(paats, dataRow);
			double paaEuc = paaDist.getAverageDistances();
			vector<double> apcaVectF = paats.getPAAdtw();
			DTW PAAdtw(dataRow, apcaVectF);
			double paaDtw = PAAdtw.returnDTWDistance();
			float tikapca = paats.getDurationPAA();
			APCAFinals.push_back(apcaVectF);
			int sizepaa = paats.getNumberOfMainFrames();
			if (paats.getModulo() > 0) { sizepaa++; }
			cout << sizepaa << "," << paaEuc << "," << paaDtw << "," << tikapca << endl;
			
			mCurrent += steps; // increase by steps

			
		}
		exprt exp; 
		//exp.createFileAPCAM(mStart, mEnd,steps, APCAFinals);	
		exp.createFilePAAM(mStart, mEnd, steps, APCAFinals);
	}

	cout << "end" << endl;
	*/

	/*Graphics*//*
	exprt exporting;
	exporting.createfileSimp(true, true, true, apcaVecorFull, paaVectorFull, data[0]);
	//runs the python scrypt
	system("ts.py");*/

	/* CREATING A TEST*/
	//DataSets Used, DatasetLength, PAA Frames, APCA frames
	//Approximation for APCA uses 2 point for 100 and paa uses 4
	//FordA, 500 ,20,10 : DONE FOR APCAvsPAA completed first 400
	//MixedShapesRegularTrain, 1024,41,21 : DONE FOR APCAvsPAA completed first 400, done for 20 and 10 frames
	//PigArtPressure,2000,80,40                                              , done for 20 and 10 frames
	/* TO BE RUN AND CREATE THE TABLES FROM THESE TESTS*/
	/*

	imp impor("PigArtPressure.txt", true, false);
	vector < vector<double> > data = impor.getUCRData();
	//opening file to write to
	ofstream outFile;
	//creating a file to output to
	string fileName = "PigArtPressureResults.csv";
	outFile.open(fileName);
	//outFile << "frame" << "," << "apcaDur" << "," << "paaDur" << "," << "difDue" << endl; //headers for csv
	outFile << "vector" << "," << "PAA Frames"<< "," << "APCA Frames" << "," << "PAA Eu" << "," << "APCAA Eu" << "," << "Dif Eu" << "," << "PAA Dtw" << "," << "APCA Dtw"  << "," << "Dif Dtw" << "," << "PAA tik" << "," << "APCA tik" << "," << "Dif tik" << endl; //header
	//M and N options
	int paaFrame = 80;
	int apcaFrame = 40;
	//looping through working out all metrics and then comparing
	int maxSize = data.size();
	for (int i = 0; i< maxSize; i++) {
		vector<double> ts = data[i];

		//Construct PAA
		PAA paaRep(ts, paaFrame);
		vector<double> paaVectN = paaRep.getPAAdtw();

		//construct apca
		APCA apcaRep(ts, apcaFrame);
		vector<double> apcaVect = apcaRep.getDtwVector();

		std::cout << "paaNF: " << paaRep.getNumberOfFrames() << " apcaF:" << apcaRep.getApcaRepresentation().size() << "count :" << i << " of: " << maxSize <<  endl;

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
	*/

	Functions funct;
	funct.runApcaCompareUCR("PigArtPressure.txt", 80, 40, 36);// function works correctly



	std::cin.get();
	return 0;





	/* 13/03/2019
		changes:
		- Add distance measures to figures need
		- Fix each algorihtm the coeffiecnts and vary for the other and see the acuracy
		- 3 datasets in the report for each of the two aobve
		- Y axis is accuracy
		- Matlab or glublot to make the accuracy plots
		- tikz pgf latex package to make graphs for experimental results
		- look at sigmod paper for 1 row with 3 columns and each column is one dataset
		- look at time efficeny, y is time in milliseconds
		- show how time changes with different coefficents
		- for compuational time fix N but increase dataset, to show increasing tendency, scalability testing

		-small paragraph to describe the results and then explain the reason. 100 at most per plot

		-table to compare the two algorithms in the different areas, i.e kind of data used

		-maybe build an interface, functions with changeable variables

		-look at vdb and acm sigmod confernece papers, DBLP for papers
	*/


	/*
	Feb 6th
	Send weiren term 1 report just to take a look at

	Working on: Measure execution time of a function

	Output file (excel) as cvs, APCA and PAA points in the original dimension
	timestap|RAW|PAA|APCA|
	use different sheet names as the table name
	synsatic data and real datasets  (weiren)
	based on the cvs file,

	option 1) use c++ to control the excel file by using macros to draw the graph

	option 2) port the code to win console and use MFC to build a window for graphics
	win console project for options and try mfc

	option 3) call matlab package and use plot

	to visualise the data, choose one or two options

	Statistical Tests on real data;
	may need to modify import to read the data
	need to chcek the reconstrution error from each real data (accuracy; DTW and euclidean distance)
	tic toc to test cpu time for each of the algorithms
	vary n for paa and apca and compare and describe the effect

	Final report also needs to complete the results and use PGF in combination with latex to visualise experimental data
	How many plots will need to be included in the report and design the experimental settings for each section on how to organise the experiment

	Go through visualistation in next meeting

	FOR DTW
	The paths shows the mapping between the two points
	After which you measure the differnce between the two mapped points
	*/
}

