#include "Headers.h"




void createModels() {
	FILE* fiTrainSet;
	FILE* fiModel;
	FILE* fiModelMen;
	FILE* fiModelWomen;

	// Chaine correspondant a la premier ligne dans les fichier csv
	char firstLineString[] = "movement, acceleration, acceleration, acceleration, ..., acceleration\n";


	fopen_s(&fiTrainSet, TRAINSET, "r");
	fopen_s(&fiModel, MODEL, "w");
	fopen_s(&fiModelMen, MODELMEN, "w");
	fopen_s(&fiModelWomen, MODELWOMEN, "w");

	if (fiTrainSet != NULL && fiModel != NULL && fiModelMen != NULL && fiModelWomen != NULL) {

		// Ecriture de la première ligne
		fwrite(&firstLineString, strlen(firstLineString), 1, fiModel);
		fwrite(&firstLineString, strlen(firstLineString), 1, fiModelMen);
		fwrite(&firstLineString, strlen(firstLineString), 1, fiModelWomen);

		// On passe la première ligne dans le fichier trainSet
		while (fgetc(fiTrainSet) != '\n');

		DatasetFileLine* datasetFileLines = malloc(LINES_COUNT_TRAINSET * sizeof(DatasetFileLine));
		// Initialisation par sécurité
		datasetLinesInitialisation(datasetFileLines);

		char value[MAX_VALUE_STRING_SIZE];
		int movement, gender;
		double acceleration;
		int lineTrainSet = 0;
		while (!feof(fiTrainSet)) {
			// Lecture par ligne
			readValueDataSet(fiTrainSet, value);
			sscanf_s(value, "%d", &movement);
			datasetFileLines[lineTrainSet].movement = movement;
			readValueDataSet(fiTrainSet, value);
			sscanf_s(value, "%d", &gender);
			datasetFileLines[lineTrainSet].gender = gender;
			// On passe l'ID
			readValueDataSet(fiTrainSet, value);
			int iVac = 0;
			bool hasValue = !readValueDataSet(fiTrainSet, value);
			while (!feof(fiTrainSet) && iVac < NB_VAC_READ && hasValue) {
				sscanf_s(value, "%lf", &acceleration);
				datasetFileLines[lineTrainSet].accelerations[iVac] = acceleration;
				iVac++;
				hasValue = !readValueDataSet(fiTrainSet, value);
			}
			// On sort de la boucle quand les 600 vAcs sont lu ou si le curseur est à la ligne suivante
			lineTrainSet++;
		}

		int iMovement = 1;
		while (iMovement <= NB_MOVEMENTS) {
			char charMovement[3];
			snprintf(charMovement, 3, "%d,", iMovement);
			fwrite(&charMovement, strlen(charMovement), 1, fiModel);
			fwrite(&charMovement, strlen(charMovement), 1, fiModelWomen);
			fwrite(&charMovement, strlen(charMovement), 1, fiModelMen);

			int iTime = 0;
			while (iTime < 600) {
				int iLine = 0;
				double totalAccMen = 0, totalAccWomen = 0;
				int totalLinesMen = 0, totalLinesWomen = 0;
				while (iLine < LINES_COUNT_TRAINSET) {
					if (datasetFileLines[iLine].movement == iMovement && datasetFileLines[iLine].accelerations[iTime] > 0) {
						if (datasetFileLines[iLine].gender == 1) {
							totalAccWomen += datasetFileLines[iLine].accelerations[iTime];
							totalLinesWomen++;
						}
						else {
							totalAccMen += datasetFileLines[iLine].accelerations[iTime];
							totalLinesMen++;
						}
					}
					iLine++;
				}
				double averageAcc = (totalAccMen + totalAccWomen) / (totalLinesMen + totalLinesWomen);
				double averageAccWomen = totalAccWomen / totalLinesWomen;
				double averageAccMen = totalAccMen / totalLinesMen;

				char charAverage[20];
				// Ecriture fiModel
				snprintf(charAverage, 20, "%lf,", averageAcc);
				fwrite(&charAverage, strlen(charAverage), 1, fiModel);

				// Ecriture fiModelWomen
				snprintf(charAverage, 20, "%lf,", averageAccWomen);
				fwrite(&charAverage, strlen(charAverage), 1, fiModelWomen);

				// Ecriture fiModelMen
				snprintf(charAverage, 20, "%lf,", averageAccMen);
				fwrite(&charAverage, strlen(charAverage), 1, fiModelMen);

				iTime++;
			}
			fwrite("\n", sizeof(char), 1, fiModel);
			fwrite("\n", sizeof(char), 1, fiModelMen);
			fwrite("\n", sizeof(char), 1, fiModelWomen);
			iMovement++;
		}

		free(datasetFileLines);
		fclose(fiTrainSet);
		fclose(fiModel);
		fclose(fiModelMen);
		fclose(fiModelWomen);
	}
	else {
		if (fiTrainSet == NULL) {
			printf("trainset failed to open %s\n", TRAINSET);
		}
		if (fiModel == NULL) {
			printf("fiModel failed to open	%s\n", MODEL);
		}
		if (fiModelMen == NULL) {
			printf("fiModelMen failed to open %s", MODELMEN);
		}
		if (fiModelWomen == NULL) {
			printf("fiModelWomen failed to open %s", MODELWOMEN);
		}
	}
}

bool readValueDataSet(FILE* file, char result[]) {
	strcpy_s(result, MAX_VALUE_STRING_SIZE, "");
	char character = fgetc(file);
	while (!feof(file) && character != '\n' && character != ',') {
		strncat_s(result, MAX_VALUE_STRING_SIZE, &character, 1);
		character = fgetc(file);
	}
	// On saute directement à la ligne ou la virgule et la valeur de retour varie si il y a eu changement de ligne
	return character == '\n';
}

void datasetLinesInitialisation(DatasetFileLine* datasetFileLines) {
	for (int i = 0; i < LINES_COUNT_TRAINSET; i++) {
		datasetFileLines[i].movement = -1;
		datasetFileLines[i].gender = -1;
		for (int j = 0; j < NB_VAC_READ; j++) {
			datasetFileLines[i].accelerations[j] = -1;
		}
	}
}
