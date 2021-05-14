#include "Headers.h"

void createDatasets(void) {
	FILE* fiTrainSet;	//pour le fichier : trainSet.csv
	FILE* fiTestSet;	//pour le fichier : testSet.csv
	FILE* fiDsi;		//pour le fichier : data_subjects_info.csv
	FILE* fiAFile;		//pour les fichiers : sub_x.csv

	srand(time(NULL));

	// Tableau contenant les nom des repertoires
	char nameFolder[][7] = { "dws_1", "dws_2", "dws_11",
							"ups_3", "ups_4", "ups_12",
							"jog_9", "jog_16",
							"sit_5", "sit_13",
							"std_6", "std_14",
							"wlk_7", "wlk_8", "wlk_15" };

	// Chaine correspondant a la premier ligne dans les fichier csv
	char firstLineString[] = "movement, gender, id, acceleration, acceleration, acceleration, ..., acceleration\n";

	// Création du fichier trainset.csv & ouverture // NOTE:  a => mode d'ajout a la fin du fichier sans ecraser le fichier// w => ecrase le fichier existant
	fopen_s(&fiTrainSet, TRAINSET, "w");
	// Création du fichier testSet.csv & ouverture
	fopen_s(&fiTestSet, TESTSET, "w");
	// Ouverture du fichier data_subjects_info.csv
	fopen_s(&fiDsi, DSI, "r");

	if (fiTrainSet != NULL && fiTestSet != NULL && fiDsi != NULL) {

		// Écriture de la ligne la premier ligne (titre)
		fwrite(&firstLineString, strlen(firstLineString), 1, fiTrainSet);
		fwrite(&firstLineString, strlen(firstLineString), 1, fiTestSet);

		char nameFileOpen[MAX_SIZE_FILE];	// Chaine de caractere qui va contenir le chemin d'acces au fichier.
		char nameFolderOpen[7];				// Chaine de caractere qui va contenir le nom du dossier acctuelle. (pas necessaire mais plus lisible)
		char iFileChar[3];					// Chaine de caractere qui va servir pour la conversion d'un int en char
		char line[SIZE];					// Chaine qui va contenir temporaiment une ligne X d'un fichier sub_x.csv
		char write[20];						// Chaine qui va etre utilise pour ecrire dans le document trainSet.csv et testSet.csv
		double acc;							// Calcul de l'accelaration avant l'ajout dans le fichier.
		int iLineSub;
		bool fileInTestSet;					// Variable qui regarde si on prend le fichier dans testSet ou non.
		DataSubFile DSF;					// Struct pour recupere les données d'une ligne des fichiers Sub_X.csv afin de pouvoir les traiters

			// Boucle sur les dossier
		for (int iFolder = 0; iFolder < NB_FOLDER; iFolder++) {
			strcpy_s(nameFolderOpen, 7, nameFolder[iFolder]); // Recuperation du nom du dossier pour le chemin d'acces au fichier
			fseek(fiDsi, 0, SEEK_SET);
			while (fgetc(fiDsi) != '\n'); // On passe la 1ere ligne

				// Boucle sur les fichier
			for (int iFile = 1; iFile <= NB_FILE; iFile++) {

				// Creation de nameFileOpen => la chemin d'acces au fichier .csv 
				strcpy_s(nameFileOpen, MAX_SIZE_FILE, "");
				strcat_s(nameFileOpen, MAX_SIZE_FILE, DIRECTORY);
				strcat_s(nameFileOpen, MAX_SIZE_FILE, nameFolderOpen);
				strcat_s(nameFileOpen, MAX_SIZE_FILE, NAME_FILE);
				sprintf_s(iFileChar, 3, "%d", iFile);
				strcat_s(nameFileOpen, MAX_SIZE_FILE, iFileChar);
				strcat_s(nameFileOpen, MAX_SIZE_FILE, EXTENSION);

				fileInTestSet = rand() % 100 < 10;

				// Ouverture du fichier sub_I.csv en lecture uniquement
				fopen_s(&fiAFile, nameFileOpen, "r");
				if (fiAFile == NULL) {
					printf("An error occur when try to open %s\n", nameFileOpen);
				}
				else
				{
					// Saute la premiere ligne : on lit caractere par caractère de la 1ère ligne jusque caractere \n
					while (fgetc(fiAFile) != '\n');
					snprintf(write, 14, "%d,%d,%d,", getMovement(iFolder), getGender(fiDsi), iFile);
					// 15 : nombres d'octets nécessaires pour le format ci dessus (mouvement, genre, numéro de fichier)
					if (fileInTestSet) {
						fwrite(&write, strlen(write), 1, fiTestSet);
					}
					else {
						fwrite(&write, strlen(write), 1, fiTrainSet);
					}
					iLineSub = 0;
					while ((!feof(fiAFile)) && (iLineSub < NB_VAC_READ)) {
						fgets(line, SIZE, fiAFile); // Obtention d'une ligne complete du fichier. 
						// Enregistrement des valeurs de la ligne dans DSF
						sscanf_s(line, "%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf", &DSF.line, &DSF.b, &DSF.c, &DSF.d, &DSF.e, &DSF.f, &DSF.g, &DSF.h, &DSF.i, &DSF.j, &DSF.accX, &DSF.accY, &DSF.accZ);
						acc = sqrt(pow(DSF.accX, 2) + pow(DSF.accY, 2) + pow(DSF.accZ, 2));
						snprintf(write, 10, "%lf,", acc);
						if (fileInTestSet) {
							fwrite(&write, strlen(write), 1, fiTestSet);
						}
						else {
							fwrite(&write, strlen(write), 1, fiTrainSet);
						}
						iLineSub++;
					}
					if (fileInTestSet) {
						fwrite("\n", sizeof(char), 1, fiTestSet);
					}
					else {
						fwrite("\n", sizeof(char), 1, fiTrainSet);
					}
					fclose(fiAFile);
				}
			}
		}
		fclose(fiTrainSet);
		fclose(fiTestSet);
		fclose(fiDsi);
	}
	else {
		if (fiTrainSet == NULL) {
			printf("trainset failed to open %s\n", TRAINSET);
		}
		if (fiTestSet == NULL) {
			printf("testsSet failed to open	%s\n", TESTSET);
		}
		if (fiDsi == NULL) {
			printf("Failed to open %s", DSI);
		}
	}
}

// Renvoie le type de mouvement
int getMovement(int iFolder) {
	int mvt;
	switch (iFolder)
	{
	case 0: case 1: case 2: mvt = 1;
		break;
	case 3: case 4: case 5: mvt = 2;
		break;
	case 6: case 7: mvt = 3;
		break;
	case 8: case 9: mvt = 4;
		break;
	case 10: case 11: mvt = 5;
		break;
	case 12: case 13: case 14: mvt = 6;
		break;
	}
	return mvt;
}

// Renvoie le genre de la personne 0 ou 1
int getGender(FILE* file) {
	DataSubjectsInfo data;
	char line[SIZE];
	fgets(line, SIZE, file);
	sscanf_s(line, "%d,%d,%d,%d,%d", &data.code, &data.age, &data.height, &data.weight, &data.gender);
	return data.gender;
}