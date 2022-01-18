//#include "APCA.h"
#include <iostream>
#include <string>
//Library for random number generation
#include <cstdlib>
//include arrays
#include <array>
#include <vector>
#include <algorithm>
#include<chrono>
using namespace std::chrono;
using namespace std;
/*
STEPS
STEP 1 PART 1 CHECKS IF A NUMBER IS A POWER OF 2 (PRIVATE)
STEP 1 PART 2 PADDS A VECTOR SO IT IS A LENGTH OF 2 (PRIVATE)


*/
class APCA {
	//todo re do with vectors may ber much simpler at later stages 
private:
	//how much it is padded
	int paddding = 0;
	//M aka the number of segments and the number of detail coefficents
	int M = 0;
	//store normalised arrays as you go along since it is much harder to work out after;
	vector<double> apcaRep;
	//store normalised arrays as you go along since it is much harder to work out after;
	vector<double> normalised;
	//Store the array contaning the length of each of the frames aka number of points in each frame
	vector<double> numberOfPoints;
	vector<double>  forDTWAPCA; //to perform DTW
	float tiktokAPCA; //time it took to run
	int sizeOrg; //orignial size of the vector

	//STEP 1 part 1: length(C) is not a power of two,
	bool checkPowerOfTwo(int n) {
		double value = log(n) / log(2);
		double powered = 1;
		for (int i = 0; i < value; i++) {
			powered = powered * 2;
		}
		if (powered == n) {
			return true;
		}
		else {
			return false;
		}
	}

	//STEP 1 Part 2: Pad C until it is of a length that is a power of two
	vector<double> paddTimeSeries(vector<double> unpaddedArray) {
		vector<double> paddedArray = unpaddedArray;
		int count = 0;
		//gets the orginial length

		int orginialLength = unpaddedArray.size();
		int length = orginialLength;

		while (!checkPowerOfTwo(length)) {
			length++;
			count++;
		}

		//resize the padded array
		//paddedArray.resize(length);
		//fill in the remaining places with 0
		for (int i = orginialLength; i < length; i++) {
			//paddedArray.at(i) = 0;
			paddedArray.push_back(0);
		}

		//sets the padding vairable to count
		paddding = count;
		//returns the array so it is padded to the length of 2^n
		return paddedArray;
	}

	vector<double> DHWT(vector<double> orginalArray) {
		//vector to be returned (will be the same length as the orginial array)
		vector<double> DHWT(orginalArray.size());
		//clear and recreate the normal vector
		normalised.clear();
		normalised.resize(orginalArray.size());
		int DHWTPOS = 0; //position in the HDWT array
						 //The number resoutions it will go down by aka 
						 //for a starting array of 8 it will need 3 resolutions to go from 3,2,1 (need to take 1 away later)
		int numberOfResolutions = (log(orginalArray.size()) / log(2));
		int currentResoultion = numberOfResolutions; // remove 1 from each time										 
													 //current resolution is the previous one, for the first iteration,
		vector<double> previousRes = orginalArray;
		//repeat until we get to the 0th resolution
		while (currentResoultion != 0) {

			//current resolution is the previous resolution size divided by two
			vector<double> currentRes(previousRes.size() / 2);
			int pos = 0; //stores the postion in the array to be added

			vector<double> differences(currentRes.size());
			int dpos = 0;
			for (int i = 0; i < previousRes.size() - 1; i = i + 2) {
				//the current resolution value is the the sum of the two and then take the average
				currentRes[pos] = (previousRes[i] + previousRes[i + 1]) / 2;
				//the difference needs to go into the HDWT array
				differences[dpos] = currentRes[pos] - previousRes[i + 1];
				//incrase the position counters by 1
				pos++;
				dpos++;
			}
			//revrse and then add into array so it adds in the correct order
			reverse(differences.begin(), differences.end());
			for (int j = 0; j < differences.size(); j++) {
				DHWT[DHWTPOS] = differences[j];

				//add into the normal vector
				double useRes = currentResoultion - 1;
				if (useRes > 0) {
					double toDiv = pow(2, (useRes / 2));
					double value = differences[j] / toDiv;
					normalised[DHWTPOS] = value;
				}
				else {
					normalised[DHWTPOS] = differences[j];
				}

				//end of notmal vector stuff


				DHWTPOS++;
			}

			//need to reassign the previous array to the current one
			previousRes = currentRes;
			//decrease the resolution by one
			currentResoultion--;
		}
		//need to add the last remaing item in the current res into the DHWT array
		DHWT[DHWT.size() - 1] = previousRes[0];
		//revrse so it is order of lowest to highest resolution
		reverse(DHWT.begin(), DHWT.end());


		//added on 26/11/2018 normalised needs to be reversed as well
		//does not need to be normalised since it will be divided by 1 since it is at the 0th resolution
		normalised[DHWTPOS] = previousRes[0];
		reverse(normalised.begin(), normalised.end());
		//end added on 26/11/2018

		return DHWT;
	}

	//takes an input of the harr and keeps the best M WORKS
	vector<double> getHighestM(vector<double> DHWTArray) {
		vector<double> highestMOnly(DHWTArray.size());
		vector<double> normsSquared = normalised;

		for (int i = 0; i < normsSquared.size(); i++) {
			normsSquared[i] = sqrt(normsSquared[i] * normsSquared[i]);
		}
		//sort from highest to lowest
		sort(normsSquared.rbegin(), normsSquared.rend());
		//store the best values
		vector<double> best(M);
		for (int j = 0; j < M; j++) {
			best[j] = normsSquared[j];
		}
		//Loop through comparing the best values and only keeping those that belong to the orginal
		for (int k = 0; k < normalised.size(); k++) {
			double tempValue = sqrt(normalised[k] * normalised[k]);
			bool isInBest = false;

			//comapre the the best list
			for (int p = 0; p < best.size(); p++) {
				if (best[p] == tempValue) {
					isInBest = true;
					break;
				}
				else {
					isInBest = false;
				}
			}

			if (isInBest == true) {
				highestMOnly[k] = DHWTArray[k];
			}
			else {
				highestMOnly[k] = 0;
			}
		}

		return highestMOnly;
	}

	//inverse harr transform
	vector<double> inverseHDWTC(vector<double> HDWTCarray) {
		int length = HDWTCarray.size();
		vector<double> reconstructed(length);
		vector<double> x = HDWTCarray;

		int k = 1;
		while (k * 2 <= length) {
			for (int i = 0; i < k; i++) {
				reconstructed[2 * i] = (x[i] + x[i + k]);
				reconstructed[(2 * i) + 1] = (x[i] - x[i + k]);
			}
			for (int j = 0; j < k * 2; j++) {
				x[j] = reconstructed[j];
			}
			k = k * 2;
		}

		return x;
	}

	//truncate by padding
	vector<double> truncateByPadding(vector<double> paddedArray) {
		vector<double>  unpaddedArray(paddedArray.size() - paddding);

		for (int i = 0; i < unpaddedArray.size(); i++) {
			unpaddedArray[i] = paddedArray[i];
		}
		return unpaddedArray;
	}


	//REMOVE PADDING METHOD 2
	vector<double> removePaddingTwo(vector<double> padded) {
		vector<double> unPadded;
		for (int k = 0; k < sizeOrg; k++) {
			unPadded.push_back(padded[k]);
		}
		return unPadded;
	}

	//method to obtain APCA representation from a vector
	vector<double> basicAPCA(vector<double> recostructed) { //result needs to be 5.5,3.5,5.5
		vector<double> APCAarray;
		int i = 0;
		while (i < recostructed.size()) {
			double current = recostructed[i];

			int count = 1;
			while (count + i < recostructed.size()) {
				if (recostructed[count + i] == current) {
					count++;
				}
				else {
					break;
				}
			}

			APCAarray.push_back(current);
			numberOfPoints.push_back(count);

			if (count == 0) {
				i++;
			}
			else {
				if (i + count > recostructed.size()) {
					break;
				}
				else {
					i = i + count;
				}
			}
		}
		return APCAarray;
	}

	//STEP 7 Replace Approximate segments with the exact ones
	vector<double> replaceApproxWithExact(vector<double> reconstruced, vector<double> orignial) {
		vector<double> replaced;
		int posInOrginial = 0;
		for (int i = 0; i < reconstruced.size(); i++) {

			double avg = 0;
			for (int j = 0; j < numberOfPoints[i]; j++) {
				avg += orignial[posInOrginial + j];
			}
			avg = avg / numberOfPoints[i];
			replaced.push_back(avg);
			posInOrginial += numberOfPoints[i];
		}
		return replaced;
	}

	//STEP 8 replace the segments until we have M segments of minimum distance
	//method commented out is an old method which does not work correctly
	/*
	vector<double> replaceUntilM(vector<double> approximatedTo) {
		vector<double> approximated = approximatedTo;
		//while we have more than M segments
		int m = approximated.size();
		//if the numebr of segments is already less than M
		if (M > m) {
			return approximatedTo;
		}
		while (m != M) {
				//find the lowest pair
				double diff = INT_MAX;
				int ipos = 0;
				for (int i = 0; i < approximated.size() - 1; i++) {
					double diffTemp = abs(approximated[i] - approximated[i + 1]);
					if (diffTemp < diff) {
						diff = diffTemp;
						ipos = i;
					}

				}
				vector<double> merged;
				vector<double> numberOfPointsNew;
				//merge the ipos and ipos+1 segment, in both the apaca array and the numberOfPoints Array
				for (int j = 0; j < approximated.size() - 1; j++) {
					if (j == ipos) {
						double value = (approximated[j] + approximated[j + 1]) / 2;
						merged.push_back(value);
						numberOfPointsNew.push_back(numberOfPoints[j] + numberOfPoints[j + 1]);
						j++;
						//need to 

					}
					else {
						merged.push_back(approximated[j]);
						numberOfPointsNew.push_back(numberOfPoints[j]);
					}
				}
				//replace all the vectors for the next iteration
				approximated = merged;
				numberOfPoints = numberOfPointsNew;
				m--;
		}
		return approximated;
	}
	*/

	//replace method 2
	vector<double> replacetilM(vector<double> notRep) {
		vector<double> replacedVect= notRep;
		vector<double> replacedVectnumberOfPoints = numberOfPoints;
		int currentMSize = notRep.size();
		if (currentMSize <= M) {
			return notRep;
		}
		else{
			while (currentMSize > M) {

				double maxDiff = abs(replacedVect[0] - replacedVect[1]);; //setting the maximum difference to the difference of the first two points  to allow for comparision
				int posDiff=0; // position of the differenced value also set to the first element

				for (int i = 1; i < currentMSize-1; i++) {
					double tempDiff = abs(replacedVect[i] - replacedVect[i + 1]);
					if (maxDiff < tempDiff) {
						maxDiff = tempDiff; // max diff is set to max diff
						posDiff = i; //position is set to current possition in the array
					}
				}
				//now that we have the position of the max diff need to colapse the vector by removing elements and selecting the specific vector
				double combOne = replacedVect[posDiff]; //first element to combine
				double combTwo = replacedVect[posDiff + 1]; // the second element to combine
				double valRep = (combOne + combTwo) / 2; //new value is equal to halfway between the two
				double pointsRep = replacedVectnumberOfPoints[posDiff] + replacedVectnumberOfPoints[posDiff + 1]; //equal to replaced one and in one ahead

				//replace value at posDiff
				replacedVect[posDiff] = valRep;
				replacedVectnumberOfPoints[posDiff] = pointsRep; //add the new number of points
				//drop the posDiff +1 points
				int ePos = posDiff + 1;
				replacedVect.erase(replacedVect.begin()+ePos);
				replacedVectnumberOfPoints.erase(replacedVectnumberOfPoints.begin() + ePos);

				currentMSize = replacedVect.size();
			}
			numberOfPoints = replacedVectnumberOfPoints;
			return replacedVect;
		}
	}

	//method to get orginial vector
	vector<double> getAPCADTW() {
		vector<double> dtwapca;
		
		for (int i = 0; i < apcaRep.size(); i++) {
			for (int j = 0; j < numberOfPoints[i]; j++) {
				dtwapca.push_back(apcaRep[i]); 
			}
		}


		return dtwapca;
	}


	//vector<double> apcaForGraphandDtw; // no longer required

public:


	vector<double> runAPCA(vector<double> arr) {
		vector<double> temp = arr; 
		sizeOrg = arr.size(); // adding into size variable for later
		auto startAPCA = high_resolution_clock::now(); // getting time at start of algorithm
		temp = paddTimeSeries(temp);
		temp = DHWT(temp);
		temp = getHighestM(temp);
		temp = inverseHDWTC(temp);
		temp = removePaddingTwo(temp); //new padding method noit using old method truncateByPadding
		temp = basicAPCA(temp);
		temp = replaceApproxWithExact(temp, arr);
		temp = replacetilM(temp); //new method, old method was replaceUntilM(temp);
		auto stopAPCA = high_resolution_clock::now(); // getting time at end
		auto duration = duration_cast<microseconds>(stopAPCA - startAPCA); //works out the time
		tiktokAPCA = duration.count();
		return temp;
	}

	//gets the duration
	float getDuration() {
		return tiktokAPCA;
	}

	//return the for graph varaible
	/* No longer required
	vector<double> getRepFull() {
		return apcaForGraphandDtw;
	}*/

	//get the vector
	vector<double> getDtwVector() {
		return forDTWAPCA;
	}

	//returns the number of points
	vector<double> getSegments() { return numberOfPoints; }
	//returns the apacaRepresentation
	vector<double> getApcaRepresentation() { return apcaRep; }

	//constructor 
	APCA(vector<double> toBeApprox, int ENTERm) {
		M = ENTERm;
		apcaRep = runAPCA(toBeApprox);
		forDTWAPCA = getAPCADTW();
	}

};
