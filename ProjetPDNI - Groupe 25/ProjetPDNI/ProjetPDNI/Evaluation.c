#include "Headers.h"

void testSetEvaluation(void) {

	FILE* fiTestSet;
	FILE* fiModel;

	fopen_s(&fiTestSet, TESTSET, "r");
	fopen_s(&fiModel, MODEL, "r");

	if (fiTestSet != NULL && fiModel != NULL) {

		Models models[NB_MOVEMENTS] = { 0,{0} };

		convertFileToTable(fiModel, models);

		int lineTestSet = 1, iLigne = 0;
		char value[MAX_VALUE_STRING_SIZE];
		double acc;

		int nbTests = nbTestsCalculation(fiTestSet);

		int estimateClasses[NB_TESTS_MAX] = { 0 };
		int realClasses[NB_TESTS_MAX] = { 0 };

		while (fgetc(fiTestSet) != '\n');

		while (!feof(fiTestSet) && iLigne < nbTests) {
			// Seconde condition afin d'éviter de prendre la dernière du fichier (vide)
			// En principe, pas obligatoire de calculer le nombre de tests avant mais ça nous aide ici.

			int mvt, gender, id, iVacc = 0, nb_acc = 600;
			double euclidianDistances[NB_MOVEMENTS] = { 0 };

			mvt = getValueFile(fiTestSet);
			gender = getValueFile(fiTestSet);
			id = getValueFile(fiTestSet);

			bool hasValue = true;
			while (iVacc < nb_acc && hasValue) {
				acc = getValueFile(fiTestSet);
				hasValue = acc != -1;
				if (hasValue) {
					for (int iModel = 0; iModel < NB_MOVEMENTS; iModel++) {
						double difference = acc - models[iModel].v_acc[iVacc];
						euclidianDistances[iModel] += difference * difference;
					}
					iVacc++;
				}
			}

			while (!feof(fiTestSet) && fgetc(fiTestSet) != '\n');

			int bestMovement = 0;
			double bestEucilidianDistance = DBL_MAX;
			for (int iMovement = 0; iMovement < NB_MOVEMENTS; iMovement++) {
				euclidianDistances[iMovement] = sqrt(euclidianDistances[iMovement]);
				if (bestEucilidianDistance > euclidianDistances[iMovement]) {
					bestMovement = iMovement + 1;
					bestEucilidianDistance = euclidianDistances[iMovement];
				}
			}
			if (iLigne < nbTests) {
				realClasses[iLigne] = mvt;
				estimateClasses[iLigne] = bestMovement;
			}
			//printf("iLigne : %d -  mvt : %d - gender : %d - id : %d - bestMvt : %d\n",iLigne, mvt, gender, id, bestMovement);
			iLigne++;
		}

		printf("\n===== Enter display functions =====\n\n");

		int resultsPerClass[NB_CLASSES][NB_CLASSES] = { 0 };
		int theoricalAppearencePerClass[NB_CLASSES] = { 0 };
		int correctResultsPerClass[NB_CLASSES] = { 0 };

		double percentageCorrectResultPerClass[NB_CLASSES] = { 0 };
		double averagePercentageCorrectResult;

		array2DFilling(realClasses, estimateClasses, resultsPerClass, nbTests);
		resultsForEachClasses(theoricalAppearencePerClass, correctResultsPerClass, resultsPerClass);
		percentageAccuracyPerClass(percentageCorrectResultPerClass, theoricalAppearencePerClass, correctResultsPerClass, &averagePercentageCorrectResult);
		displayResultsForEachClasses(theoricalAppearencePerClass, correctResultsPerClass, percentageCorrectResultPerClass);
		displayAccuracy(&averagePercentageCorrectResult);
		displayClass(theoricalAppearencePerClass, resultsPerClass);


		fclose(fiModel);
		fclose(fiTestSet);
	}
	else {
		if (fiTestSet == NULL) {
			printf("testsSet failed to open	%s\n", TESTSET);
		}
		if (fiModel == NULL) {
			printf("model failed to open %s\n", TESTSET);
		}
	}

}

void convertFileToTable(FILE* file, Models models[]) {
	int lineModel = 1;
	int iVacc;
	while (fgetc(file) != '\n');
	while (!feof(file) && lineModel <= NB_MOVEMENTS) {
		iVacc = 1;
		models[lineModel - 1].move = getValueFile(file);
		while (iVacc <= 601 && fgetc(file) != '\n') {
			models[lineModel - 1].v_acc[iVacc - 1] = getValueFile(file);
			iVacc++;
		}
		lineModel++;
	}
}

int nbTestsCalculation(FILE* fiTestSet) {
	int nbTests = 0;
	while (!feof(fiTestSet)) {
		while (!feof(fiTestSet) && fgetc(fiTestSet) != '\n');
		nbTests++;
	}
	fseek(fiTestSet, 0, SEEK_SET); // Remet le pointeur au début du fichier
	return nbTests - 2; // -2 car moins la dernière ligne vide et la ligne du nom des colonnes
}

// Version améliorée de la fonction "readValueDataSet", elle permet de lire directement la valeur réelle
// Si la valeur renvoyée est -1 --> la ligne se termine
double getValueFile(FILE* file) {
	char result[MAX_VALUE_STRING_SIZE] = "";
	char character = fgetc(file);
	while (!feof(file) && character != '\n' && character != ',') {
		strncat_s(result, MAX_VALUE_STRING_SIZE, &character, 1);
		character = fgetc(file);
	}
	if (character == '\n') {
		return -1;
	}
	return strtod(result, NULL);
}

