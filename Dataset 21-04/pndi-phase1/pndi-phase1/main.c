#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>


#define TRAINSET "trainSet.csv"
#define TESTSET "testSet.csv"
#define DSI "D:\\archive\\data_subjects_info.csv"


typedef struct dataSetLine DataSetLine;

struct dataSetLine {
	int id; 
	double accX;
	double accY;
	double accZ; 
	int movement; 
	int gender; 
};


void main(void) {
	
	FILE* trainSet;
	FILE* testSet;
	FILE* dsi;

	DataSetLine dsl; 
	


	fopen_s(&trainSet, TRAINSET, "w");
	//fwrite_s(&trainSet, "%s,%s,%s,%s,%s,%s", "identifiant", "accelleration.x", "accelleration.y", "accelleration.z", "movement", "gender");
	fclose(trainSet);

	fopen_s(&dsi, DSI, "r");
	if (dsi == NULL) {
		printf("non open");
	}
	else
	{
		printf("open");
	}

}