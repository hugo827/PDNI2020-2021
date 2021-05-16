#include "Headers.h"

void array2DFilling(int realClasses[], int estimateClasses[], int resultsPerClass[NB_CLASSES][NB_CLASSES], int nbTests) {
	// Précondition : les numéros de classe sont compris entre [1, NB_CLASSES]
	for (int i = 0; i < nbTests; i++) {
		resultsPerClass[estimateClasses[i] - 1][realClasses[i] - 1]++;
	}
}

void resultsForEachClasses(int theoricalAppearencePerClass[], int correctResultsPerClass[], int resultsPerClass[NB_CLASSES][NB_CLASSES]) {
	for (int i = 0; i < NB_CLASSES; i++) {
		// La classe x est dans la colonne x-1
		for (int j = 0; j < NB_CLASSES; j++) {
			theoricalAppearencePerClass[i] += resultsPerClass[j][i];
			if (i == j) {
				correctResultsPerClass[i] += resultsPerClass[i][i];
			}
			
		}
	}
}

void percentageAccuracyPerClass(double percentageCorrectResultPerClass[], int theoricalResultsPerClass[], int measuredResultsPerClass[], double* overallAccuracy) {
	int sumTheoricalResult = 0, sumMeasuredResult = 0;
	for (int i = 0; i < NB_CLASSES; i++) {
		if (theoricalResultsPerClass[i] != 0) {
			percentageCorrectResultPerClass[i] = (double)measuredResultsPerClass[i] / theoricalResultsPerClass[i]*100;
		}
		else {
			percentageCorrectResultPerClass[i] = -1;
		}
		sumTheoricalResult += theoricalResultsPerClass[i];
		sumMeasuredResult += measuredResultsPerClass[i];
	}
	*overallAccuracy = (double)sumMeasuredResult / sumTheoricalResult*100;
}