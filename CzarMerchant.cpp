/*
 * Class that compares a query image to template image and prints out the ten closest template images to the query image
 * CSCE 350 F14 Programming Assignment
 * Copyright (C) 2014 Do Not Use Without Permission
 * Created and modified by:
 * @author Christian Merchant <merchane@email.sc.edu>
 * @author Mateusz Czarnocki <czarnock@email.sc.edu>
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <cmath>
#include <stdlib.h>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>
#include <stdio.h>

using namespace std;

//List of functions
double ComputeSimilarity(vector<double> q, vector<double>tempImg);
void qsrt (vector<int>& idx, vector<double>& simTbl, int left, int right);

int main () {

	//Runtime timer declaration and start
	clock_t finaltimer;
	finaltimer = clock();

	string queryNames[] = {
	"Data/001_AU01_query.dat","Data/001_AU12_query.dat","Data/001_AU17_query.dat",
	"Data/002_AU01_query.dat","Data/002_AU12_query.dat","Data/002_AU17_query.dat",
	"Data/003_AU01_query.dat","Data/003_AU12_query.dat","Data/003_AU17_query.dat",
	"Data/004_AU01_query.dat","Data/004_AU12_query.dat","Data/004_AU17_query.dat",
	"Data/005_AU01_query.dat","Data/005_AU12_query.dat","Data/005_AU17_query.dat",
	"Data/006_AU01_query.dat","Data/006_AU12_query.dat","Data/006_AU17_query.dat",
	"Data/007_AU01_query.dat","Data/007_AU12_query.dat","Data/007_AU17_query.dat",
	"Data/008_AU01_query.dat","Data/008_AU12_query.dat","Data/008_AU17_query.dat",
	"Data/009_AU01_query.dat","Data/009_AU12_query.dat","Data/009_AU17_query.dat",
	"Data/010_AU01_query.dat","Data/010_AU12_query.dat","Data/010_AU17_query.dat",
	"Data/011_AU01_query.dat","Data/011_AU12_query.dat","Data/011_AU17_query.dat",
	"Data/012_AU01_query.dat","Data/012_AU12_query.dat","Data/012_AU17_query.dat",
	"Data/013_AU01_query.dat","Data/013_AU12_query.dat","Data/013_AU17_query.dat",
	"Data/014_AU01_query.dat","Data/014_AU12_query.dat","Data/014_AU17_query.dat",
	"Data/015_AU01_query.dat","Data/015_AU12_query.dat","Data/015_AU17_query.dat",
	"Data/016_AU01_query.dat","Data/016_AU12_query.dat","Data/016_AU17_query.dat",
	"Data/017_AU01_query.dat","Data/017_AU12_query.dat","Data/017_AU17_query.dat",
	"Data/018_AU01_query.dat","Data/018_AU12_query.dat","Data/018_AU17_query.dat",
	"Data/019_AU01_query.dat","Data/019_AU12_query.dat","Data/019_AU17_query.dat",
	"Data/020_AU01_query.dat","Data/020_AU12_query.dat","Data/020_AU17_query.dat",
	"Data/021_AU01_query.dat","Data/021_AU12_query.dat","Data/021_AU17_query.dat",
	"Data/022_AU01_query.dat","Data/022_AU12_query.dat","Data/022_AU17_query.dat",
	"Data/023_AU01_query.dat","Data/023_AU12_query.dat","Data/023_AU17_query.dat",
	"Data/024_AU01_query.dat","Data/024_AU12_query.dat","Data/024_AU17_query.dat",
	"Data/025_AU01_query.dat","Data/025_AU12_query.dat","Data/025_AU17_query.dat",
	"Data/026_AU01_query.dat","Data/026_AU12_query.dat","Data/026_AU17_query.dat",
	"Data/027_AU01_query.dat","Data/027_AU12_query.dat","Data/027_AU17_query.dat",
	"Data/028_AU01_query.dat","Data/028_AU12_query.dat","Data/028_AU17_query.dat",
	"Data/029_AU01_query.dat","Data/029_AU12_query.dat","Data/029_AU17_query.dat",
	"Data/030_AU01_query.dat","Data/030_AU12_query.dat","Data/030_AU17_query.dat",
	"Data/031_AU01_query.dat","Data/031_AU12_query.dat","Data/031_AU17_query.dat",
	"Data/032_AU01_query.dat","Data/032_AU12_query.dat","Data/032_AU17_query.dat",
	"Data/033_AU01_query.dat","Data/033_AU12_query.dat","Data/033_AU17_query.dat",
	"Data/034_AU01_query.dat","Data/034_AU12_query.dat","Data/034_AU17_query.dat",
	"Data/035_AU01_query.dat","Data/035_AU12_query.dat","Data/035_AU17_query.dat",
	"Data/036_AU01_query.dat","Data/036_AU12_query.dat","Data/036_AU17_query.dat",
	"Data/037_AU01_query.dat","Data/037_AU12_query.dat","Data/037_AU17_query.dat",
	"Data/038_AU01_query.dat","Data/038_AU12_query.dat","Data/038_AU17_query.dat",
	"Data/039_AU01_query.dat","Data/039_AU12_query.dat","Data/039_AU17_query.dat",
	"Data/040_AU01_query.dat","Data/040_AU12_query.dat","Data/040_AU17_query.dat",
	"Data/041_AU01_query.dat","Data/041_AU12_query.dat","Data/041_AU17_query.dat",
	"Data/042_AU01_query.dat","Data/042_AU12_query.dat","Data/042_AU17_query.dat",
	"Data/043_AU01_query.dat","Data/043_AU12_query.dat","Data/043_AU17_query.dat",
	"Data/044_AU01_query.dat","Data/044_AU12_query.dat","Data/044_AU17_query.dat",
	"Data/045_AU01_query.dat","Data/045_AU12_query.dat","Data/045_AU17_query.dat",
	"Data/046_AU01_query.dat","Data/046_AU12_query.dat","Data/046_AU17_query.dat",
	"Data/047_AU01_query.dat","Data/047_AU12_query.dat","Data/047_AU17_query.dat"};

	string templateNames[] = {
	"Data/001_template.dat","Data/002_template.dat","Data/003_template.dat",
	"Data/004_template.dat","Data/005_template.dat","Data/006_template.dat",
	"Data/007_template.dat","Data/008_template.dat","Data/009_template.dat",
	"Data/010_template.dat","Data/011_template.dat","Data/012_template.dat",
	"Data/013_template.dat","Data/014_template.dat","Data/015_template.dat",
	"Data/016_template.dat","Data/017_template.dat","Data/018_template.dat",
	"Data/019_template.dat","Data/020_template.dat","Data/021_template.dat",
	"Data/022_template.dat","Data/023_template.dat","Data/024_template.dat",
	"Data/025_template.dat","Data/026_template.dat","Data/027_template.dat",
	"Data/028_template.dat","Data/029_template.dat","Data/030_template.dat",
	"Data/031_template.dat","Data/032_template.dat","Data/033_template.dat",
	"Data/034_template.dat","Data/035_template.dat","Data/036_template.dat",
	"Data/037_template.dat","Data/038_template.dat","Data/039_template.dat",
	"Data/040_template.dat","Data/041_template.dat","Data/042_template.dat",
	"Data/043_template.dat","Data/044_template.dat","Data/045_template.dat",
	"Data/046_template.dat","Data/047_template.dat"};

	const int BLOCK_SIZE = 5632;
	const int BLOCKS_PER_TEMPLATE = 138;

	//Variables for QUERY input
	vector<vector<double> > queries;
	vector<double> query;
	ifstream queryFile;
	string currentQuery = "";
	string qLine = "";
	double nextQVal;
	int queriesSize = (sizeof(queryNames)/sizeof(*queryNames));

	//Variables for TEMPLATE input
	vector<vector<double> > tempBlockVector;
	ifstream templateFile;
	string currentTemplate = "";
	string tLine = "";
	double nextTempVal;
	int templatesSize = (sizeof(templateNames)/sizeof(*templateNames));

	vector<int> index; 
	vector<double> similarity;
	double similarityValue = 0.0;
	vector<double> tempImage;

	string thisTemp = "";
	string thisQuery = "";
	int queryPosition = 0;

	//Open output file and print initial information to it
	ofstream output;
	output.open("results.txt");
	output << "NOTE: Indexed 1-Up, list is in decreasing order of similarity" << endl;
	output << "Formatted as: Index (Similarity Value)" << endl;
	output << "--------------------------------------------------------------" << endl;

	/*
	 * This is where we handle all of the input, output, similarity
	 * calculation, and sorting operations.
	 * (Similarities and sorting are results of separate functions
	 * that do this for us.)
	*/

	for (int a = 0; a < templatesSize; a++) {

		currentTemplate = templateNames[a];
		templateFile.open(currentTemplate.c_str());

                nextTempVal = 0.0;
                //templateFile >> nextTempVal;		
		vector<double> tempVector;

		for (int y = 0; y < BLOCKS_PER_TEMPLATE; y++) {

			getline(templateFile, tLine);
			istringstream stream2(tLine);

			while (stream2 >> nextTempVal) {

				tempVector.push_back(nextTempVal);

			}

			tempBlockVector.push_back(tempVector);
			tempVector.clear();

		}

		//Read in query files
		for (int b = queryPosition; b < (queryPosition + 3); b++) {

			//Open each file sequentially from array of file names
			currentQuery = queryNames[b];
			queryFile.open(currentQuery.c_str());

			nextQVal = 0.0;

			//Since each query file is only one line we can read in all of the
			//data as one line
			getline(queryFile, qLine);
			istringstream stream1(qLine);

			while (stream1 >> nextQVal) {

				query.push_back(nextQVal);

			}

			//Calculate similarity of each query compared to each
			//template block
			for (int c  = 0; c < BLOCKS_PER_TEMPLATE; c++) {	

				tempImage = tempBlockVector[c];

				similarityValue = ComputeSimilarity(query, tempImage);
				similarity.push_back(similarityValue);
				similarityValue = 0.0;

				index.push_back(c);
				tempImage.clear();

			}

			//Clear query variables/input
			query.clear();
			queryFile.close();

			//Quicksort indexes based on similarity values they point to
			qsrt(index, similarity, 0, index.size() - 1);
			
			//Assign file names to strings for printing
			thisTemp = templateNames[a];
			thisQuery = queryNames[b];

			//Print results
			output << "Template: " << thisTemp.substr(5, 12)
			  << " Query: " << thisQuery.substr(5, 14) << endl; 

			//Print indices of 10 closest neighbors after sorting
			//along with their corresponding sim. values
			for (int j = (index.size() - 1); j > 127; j--) {

		        	if (j > 128) {
	
	       				output << index[j] + 1 << "(" << similarity[index[j]] << "), ";

	       			}
	       			else {

					output << index[j] + 1 << "(" << similarity[index[j]] << ") ";

				}
	
			}

			output << endl << endl;

			index.clear();
			similarity.clear();

		}

		//Start next similarity calculation with the correct set of queries
		queryPosition += 3;

		//Clear template variables/input
		currentTemplate = "";
		tempBlockVector.clear();
		templateFile.close();

	}

	//Output Time
	output << "--------------------------------------------------------------" << endl;
	finaltimer = clock() - finaltimer;
	cout << "DONE!" << endl
	  << "Total CPU runtime was: " << ((float)finaltimer/CLOCKS_PER_SEC) << " seconds." << endl;
	output << "Total CPU runtime was: " << ((float)finaltimer/CLOCKS_PER_SEC) << " seconds." << endl;

	return 0;

}

/****************FUNCTIONS**************/

//Two vectors of doubles (queries and templates) as arguments to calculate
//similarity by first finding magnitude and dot product
double ComputeSimilarity(vector<double> q, vector<double> tempImg) {

	double similarity = 0.0;
	double dotProduct = 0.0;

	//Used in calculation of magnitude
	double sum = 0.0;
	double power = 0.0;
	double currentNum = 0.0;

	//Query and template magnitude
	double qMag = 0.0;
	double tempMag = 0.0;

	for (int i = 0; i < q.size(); i++) {
		if (q[i] != 0.0 && tempImg[i] != 0.0)
		{	
			dotProduct += (q[i] * tempImg[i]);
		}
		if (q[i] != 0.0)
		{	
			currentNum = q.at(i);
			power = (currentNum * currentNum);
			sum += power;
		}
	
	}

	qMag = sqrt(sum);

	//Clear variables for template calculations
	sum = 0.0;
	power = 0.0;
	currentNum = 0.0;

	for (int i = 0; i < tempImg.size(); i++) 
	{	
		if (tempImg[i]  != 0.0)
		{	
			currentNum = tempImg.at(i);
			power = (currentNum * currentNum);
			sum += power;
		}	
		

	}

	tempMag = sqrt(sum);

	//Use magnitude of query and template to calculate similarity
	similarity = (dotProduct/(qMag*tempMag));

	return similarity;

}

/* 
	* Quicksort Function 
	* Based on an idea by Lars Vogel (c) 2010
	* (http://www.vogella.com/tutorials/JavaAlgorithmsQuicksort/article.html)
	* Unlike the source code, we have ported this to C++ and also
	* adapted it to use indexing: we index into the similarity table
	* without actually shifting the data around so that we can preserve
	* the index number of the template images
*/
void qsrt(vector<int>& idx, vector<double>& simTbl, int left, int right) {

	int i = left;
	int j = right;
	int k = (left + (right-left)/ 2);

	double pivot = simTbl[idx[k]];

	while (i <= j)
	{

		while (simTbl[idx[i]] < pivot) {

			i++;

		}

		while (simTbl[idx[j]] > pivot) {

			j--;

		}

		if (i <= j) {

	    		swap(idx[i], idx[j]);
	        	i++;
	        	j--;

		}

	}
	if (left < j) {

		qsrt(idx, simTbl, left, j);

	}
	if (i < right) {

		qsrt(idx, simTbl, i, right);

	}
}

//Copyright (C) 2014 by Christian Merchant & Mateusz Czarnocki
