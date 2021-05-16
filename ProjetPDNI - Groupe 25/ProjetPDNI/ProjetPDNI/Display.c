#include "Headers.h"

void displayResultsForEachClasses(int theoricalAppearencePerClass[], int correctResultsPerClass[], double percentageCorrectResultPerClass[]) {
	printf("         classe        |       bien classes    |          total        |       Pourcentage    \n");
	// 20 charactères par colonne
	
	for (int i = 0; i < NB_CLASSES; i++) {
		if (theoricalAppearencePerClass[i] != 0) {
			printf("         %4d          |         %4d          |         %4d          |         %.2f%%         ", i+1, correctResultsPerClass[i], theoricalAppearencePerClass[i], percentageCorrectResultPerClass[i]);
			printf("\n");
		}
	}
}

void displayAccuracy(double* averagePercentageCorrectResult) {
	printf("\nL'accuracy est de %.2f%%\n", *averagePercentageCorrectResult);
}

void displayClass(int theoricalAppearencePerClass[], int resultsPerClass[NB_CLASSES][NB_CLASSES]) {
	printf("\nA classer            |  ");
	for (int i = 0; i < NB_CLASSES; i++) {
		printf("        %d  ", i+1);
	}
	printf("\n====================================================================================\n");
	printf("Numclasse    Nombre  |\n");
	for (int i = 0; i < NB_CLASSES; i++) {
		printf("    %d       %4d     |", i + 1, theoricalAppearencePerClass[i]);
		for (int j = 0; j < NB_CLASSES; j++) {
			printf("       %4d", resultsPerClass[j][i]);
		}
		printf("\n");
	}
}

