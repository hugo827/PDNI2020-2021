#include <stdio.h>
#include "IncludePrototype.h"

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
	printf("\nA classer            |    Jogging      Marche      Assis      Monter     Descendre\n");
	printf("====================================================================================\n");
	printf("Libelle      Nombre  |\n");
	printf("Jogging      %4d    |     %4d       %4d        %4d        %4d        %4d\n", theoricalAppearencePerClass[JOGGING], resultsPerClass[JOGGING][JOGGING], resultsPerClass[MARCHE][JOGGING], resultsPerClass[ASSIS][JOGGING], resultsPerClass[MONTEE][JOGGING], resultsPerClass[DESCENTE][JOGGING]);
	printf("Marche       %4d    |     %4d       %4d        %4d        %4d        %4d\n", theoricalAppearencePerClass[MARCHE], resultsPerClass[JOGGING][MARCHE], resultsPerClass[MARCHE][MARCHE], resultsPerClass[ASSIS][MARCHE], resultsPerClass[MONTEE][MARCHE], resultsPerClass[DESCENTE][MARCHE]);
	printf("Assis        %4d    |     %4d       %4d        %4d        %4d        %4d\n", theoricalAppearencePerClass[ASSIS], resultsPerClass[JOGGING][ASSIS], resultsPerClass[MARCHE][ASSIS], resultsPerClass[ASSIS][ASSIS], resultsPerClass[MONTEE][ASSIS], resultsPerClass[DESCENTE][ASSIS]);
	printf("Montee       %4d    |     %4d       %4d        %4d        %4d        %4d\n", theoricalAppearencePerClass[MONTEE], resultsPerClass[JOGGING][MONTEE], resultsPerClass[MARCHE][MONTEE], resultsPerClass[ASSIS][MONTEE], resultsPerClass[MONTEE][MONTEE], resultsPerClass[DESCENTE][MONTEE]);
	printf("Descendre    %4d    |     %4d       %4d        %4d        %4d        %4d\n", theoricalAppearencePerClass[DESCENTE], resultsPerClass[JOGGING][DESCENTE], resultsPerClass[MARCHE][DESCENTE], resultsPerClass[ASSIS][DESCENTE], resultsPerClass[MONTEE][DESCENTE], resultsPerClass[DESCENTE][DESCENTE]);
}
