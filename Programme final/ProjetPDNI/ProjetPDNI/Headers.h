#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "C:\\Users\\Robin\\Google Drive\\IG\\B2\\Q2\\DataIntel\\TDD2021\\EXAM\\Programme final\\classificationStatistics\\classificationStatistics.h"

// ===============    Définition des constantes symboliques    ======================

// Pour la partie traitement des résultats
#define NB_CLASSES 5
#define NB_CLASSES_MAX 20
#define NB_TESTS 8

// Pour la partie création des 2 fichiers datasets
#define TRAINSET "trainSet.csv"
#define TESTSET "testSet.csv"
#define DSI "C:\\Users\\Robin\\Google Drive\\IG\\B2\\Q2\\DataIntel\\TDD2021\\archive\\data_subjects_info.csv"
#define DIRECTORY "C:\\Users\\Robin\\Google Drive\\IG\\B2\\Q2\\DataIntel\\TDD2021\\archive\\A_DeviceMotion_data\\A_DeviceMotion_data\\"
#define NAME_FILE "\\sub_"
#define EXTENSION ".csv"
#define NB_FOLDER 15
#define NB_FILE 24
#define MAX_SIZE_FILE 200
#define SIZE 200
#define NB_VAC_READ 600

// Pour la partie création des 3 fichiers modèles
#define MODEL "fiModel.csv"
#define MODELMEN "fiModelMen.csv"
#define MODELWOMEN "fiModelWomen.csv"
#define MAX_VALUE_STRING_SIZE 30
#define MOVEMENTS 6

// ===============    Prototypes des fonctions et des structures utilisées    ======================

// Pour la partie traitement des résultats
void array2DFilling(int realClasses[], int estimateClasses[], int resultsPerClass[NB_CLASSES][NB_CLASSES]);
void resultsForEachClasses(int theoricalAppearencePerClass[], int correctResultsPerClass[], int resultsPerClass[NB_CLASSES][NB_CLASSES]);
void percentageAccuracyPerClass(double percentageCorrectResultPerClass[], int theoricalResultsPerClass[], int measuredResultsPerClass[], double* overallAccuracy);
void displayResultsForEachClasses(int theoricalAppearencePerClass[], int correctResultsPerClass[], double percentageCorrectResultPerClass[]);
void displayAccuracy(double* averagePercentageCorrectResult);
void displayClass(int theoricalAppearencePerClass[], int resultsPerClass[NB_CLASSES][NB_CLASSES]);

// Pour la partie création des 2 fichiers datasets
void createDatasets(void);
int getMovement(int iFolder);
int getGender(FILE* file);

typedef struct dataSubFileLine DataSubFile;
typedef struct dataSubjectsInfoLine DataSubjectsInfo;

struct dataSubFileLine {
	int line;
	double b;
	double c;
	double d;
	double e;
	double f;
	double g;
	double h;
	double i;
	double j;
	double accX;
	double accY;
	double accZ;
};
struct dataSubjectsInfoLine {
	int code;
	int weight;
	int height;
	int age;
	int gender;
};

// Pour la partie création des 3 fichiers modèles
void createModels();
void readValueDataSet(FILE* fiDataSet, char result[]);