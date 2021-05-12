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
		fwrite(&firstLineString, sizeof(firstLineString), 1, fiModel);
		fwrite(&firstLineString, sizeof(firstLineString), 1, fiModelMen);
		fwrite(&firstLineString, sizeof(firstLineString), 1, fiModelWomen);

		// On passe la première ligne dans le fichier trainSet
		while (fgetc(fiTrainSet) != '\n');

		for (int mvt = 1; mvt <= MOVEMENTS; mvt++) {
			int numColumsTrainSet = NB_VAC_READ + 4; // Représente le numéro de colonne le plus grand (en commencant à 1)
			int numColumn = 4; // Le compteur de colonnes àpd de la première contenant un VAC.
			char value[MAX_VALUE_STRING_SIZE]; // Variable tampon permettant la lecture de valeur dans le fichier fiTrainSet.csv
			double acceleration; 
			int nbLinesMen = 0, nbLinesWomen = 0;
			
			char charMovement[3];
			snprintf(charMovement, 3, "%d,", mvt);
			fwrite(&charMovement, 3, 1, fiModel);
			fwrite(&charMovement, 3, 1, fiModelWomen);
			fwrite(&charMovement, 3, 1, fiModelMen);

			// savePoint permet de revenir à ce point si le mouvementEnCours n'est plus le mouvement observé -> la colonne du mouvement se termine
			// On reviendra tout le temps à ce savePoint SAUF si le mouvement que l'on traite se termine (plus de colonne à traiter)
			long savePoint = ftell(fiTrainSet);

			while (numColumn < numColumsTrainSet) {
				int movement = mvt, gender;
				double sumAccMen = 0, sumAccWomen = 0;
				
				while (!feof(fiTrainSet) && movement == mvt) {
					// Au début de la ligne
					// On obtient le mouvement en cours
					readValueDataSet(fiTrainSet, value);
					sscanf_s(value, "%d", &movement);

					if (movement == mvt) {
						// Si on est toujours sur une ligne du même mouvement
						// On obtient le genre en cours
						readValueDataSet(fiTrainSet, value);
						sscanf_s(value, "%d", &gender);
						// On passe l'ID
						readValueDataSet(fiTrainSet, value);

						// On ajuste le curseur à la bonne colonne (attention il peut ne pas y avoir de valeur) !!!!
						int iColumn = 4;
						// Traiter le cas si y a pas assez de données !!!
						bool hasValue = true;
						while (iColumn < numColumn && hasValue) {
							readValueDataSet(fiTrainSet, value);
							hasValue = strcmp(value, "");
							iColumn++;
						}
						if (hasValue) {
							// On lit la valeur souhaitée à la bonne colonne
							readValueDataSet(fiTrainSet, value);
							sscanf_s(value, "%lf", &acceleration);

							if (gender == 1) {
								sumAccWomen += acceleration;
							}
							else {
								sumAccMen += acceleration;
							}

							if (numColumn == 4) {
								// On ne lit qu'une fois par mouvement le nombre de lignes
								gender == 1 ? nbLinesWomen++ : nbLinesMen++;
							}
						}
						// On passe à la ligne suivante
						while (!feof(fiTrainSet) && fgetc(fiTrainSet) != '\n');
					}
				}
				// Une fois que la colonne du mvt est terminée
				double averageAcc = (sumAccMen + sumAccWomen) / (nbLinesMen + nbLinesWomen);
				double averageAccWomen = sumAccWomen / nbLinesWomen;
				double averageAccMen = sumAccMen / nbLinesMen;

				char charAverage[20]; 

				// Ecriture fiModel
				snprintf(charAverage, 20, "%lf,", averageAcc);
				fwrite(&charAverage, 10, 1, fiModel);

				// Ecriture fiModelWomen
				snprintf(charAverage, 20, "%lf,", averageAccWomen);
				fwrite(&charAverage, 10, 1, fiModelWomen);

				// Ecriture fiModelMen
				snprintf(charAverage, 20, "%lf,", averageAccMen);
				fwrite(&charAverage, 10, 1, fiModelMen);
				
				printf("Acc moyenne mvt %d au temps t%d : %lf\n", mvt, numColumn -3, averageAcc);

				if (numColumn + 1 != numColumsTrainSet) {
					// On se remet au début du mvt si et seulement si il reste des colonnes à traiter pour le mouvement en cours
					fseek(fiTrainSet, savePoint, SEEK_SET);
				}
				else {
					// Si le mouvement en cours est terminé, on passe à la ligne afin de commencer le mouvement suivant
					while (!feof(fiTrainSet) && fgetc(fiTrainSet) != '\n');
					char nextLine[2];
					snprintf(nextLine, 2, "%c", '\n');
					fwrite(&nextLine, 2, 1, fiModel);
					fwrite(&nextLine, 2, 1, fiModelMen);
					fwrite(&nextLine, 2, 1, fiModelWomen);
				}
				numColumn++;
			}
		}
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

void readValueDataSet(FILE* file, char result[]) {

	strcpy_s(result, MAX_VALUE_STRING_SIZE, "");
	char character = fgetc(file);
	while (!feof(file) && character != '\n' && character != ',') {
		strncat_s(result, MAX_VALUE_STRING_SIZE, &character, 1);
		character = fgetc(file);
	}
	// On saute directement à la ligne ou la virgule
}
