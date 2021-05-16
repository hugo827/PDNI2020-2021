# include <stdio.h>
# define MAXTESTS 10000
# define MAXCLASSES 20
typedef struct classe Class;
struct classe
{
	int nbTimes;
	int countClass[MAXCLASSES];
};
typedef struct intermediaryAccuracy IntermAccuracy;
struct intermediaryAccuracy
{
	int nbWellClassified;
	int nbTotal;
};

void displayResultsForEachClass(int realClasses[], int estimateClasses[], int nbTests);
void displayClass(int realClasses[], int estimateClasses[], int nbTests);
int classDetailsCalculation(int estimateClasses[], int realClasses[], int nbTests, Class classDetails[MAXCLASSES]);
void displayAccuracy(int realClasses[], int estimateClasses[], int nbTests);
int classAccuracy(int estimateClasses[], int realClasses[], int nbTests, IntermAccuracy classes[]);
