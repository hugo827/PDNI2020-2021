#pragma once
#include <stdio.h>
#define NB_CLASSES 5
#define NB_CLASSES_MAX 20
#define NB_TESTS 8
#define NB_CHAR_MAX_CLASS 20

void array2DFilling(int realClasses[], int estimateClasses[], int resultsPerClass[NB_CLASSES][NB_CLASSES]);
void resultsForEachClasses(int theoricalAppearencePerClass[], int correctResultsPerClass[], int resultsPerClass[NB_CLASSES][NB_CLASSES]);
void percentageAccuracyPerClass(double percentageCorrectResultPerClass[], int theoricalResultsPerClass[], int measuredResultsPerClass[], double* overallAccuracy);
void displayResultsForEachClasses(int theoricalAppearencePerClass[], int correctResultsPerClass[], double percentageCorrectResultPerClass[]);
void displayAccuracy(double* averagePercentageCorrectResult);
void displayClass(int theoricalAppearencePerClass[], int resultsPerClass[NB_CLASSES][NB_CLASSES]);

enum class { JOGGING, MARCHE, ASSIS, MONTEE, DESCENTE };