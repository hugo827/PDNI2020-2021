#include <stdio.h>
#include "IncludePrototype.h"

void main(void) {

	// Données
	int realClasses[8] = { 5, 2, 5, 3, 5, 3, 2, 4 };
	int estimateClasses[8] = { 5, 5, 1, 2, 1, 3, 2, 4 };


	// Traitement
	
	int resultsPerClass[NB_CLASSES][NB_CLASSES] = { 0 };
	
	/*
		Nous allons à partir des données, garnir resultsPerClass et ensuite garnir les variables suivantes
		à partir de ce tableau : petite redondance d'information, certes mais permet d'éviter de gagner du 
		temps de calcul

		resultsPerClass est un tableau 2D où chaque cellule identifiée par x et y. Où chaque couple correspond
		à une situation précise (X : real class et Y : estimated class)
		Par exemple, si la cellule (1,2) contient 5 :  il y a eu 5 tests qui aurait du être classe 2 
		qui a été identifié par la machine comme étant classe 3. (nbCellule-1 : ne pas oublier)
	*/
	array2DFilling(realClasses, estimateClasses, resultsPerClass);

	/*
	theoricalAppearencePerClass contient, pour chaque classe, le nombre de fois que chaque classe devrait apparaitre
	correctResultsPerClass contient, pour chaque classe, le nombre de fois que le programme l'a identifié correctement
	*/

	int theoricalAppearencePerClass[NB_CLASSES] = { 0 };
	int correctResultsPerClass[NB_CLASSES] = { 0 };
	resultsForEachClasses(theoricalAppearencePerClass, correctResultsPerClass, resultsPerClass);
	
	double percentageCorrectResultPerClass[NB_CLASSES] = { 0 };
	double averagePercentageCorrectResult;
	percentageAccuracyPerClass(percentageCorrectResultPerClass, theoricalAppearencePerClass, correctResultsPerClass, &averagePercentageCorrectResult);

	displayResultsForEachClasses(theoricalAppearencePerClass, correctResultsPerClass, percentageCorrectResultPerClass);
	displayAccuracy(&averagePercentageCorrectResult);
	displayClass(theoricalAppearencePerClass, resultsPerClass);
	 
	/* Si on décide plus tard d'améliorer la fonction displayClass afin de la rendre moins contraignante à modifier, ce tableau sera nécessaire : char nomClasses[NB_CLASSES_MAX][NB_CHAR_MAX_CLASS] = {
		"Jogging", "Marche", "Assis", "Montee", "Descente", "A def", "A def", "A def", "A def", "A def", "A def", "A def", "A def", "A def", "A def", "A def", "A def", "A def", "A def", "A def"
	};
	   L'idée sera de boucler afin d'afficher les éléments
	*/
	


	// ====   Fonction d'affichage test ====
		// Affichage du tableau resultPerClass
	/*

	for (int i = 0; i < NB_CLASSES; i++) {
		for (int j = 0; j < NB_CLASSES; j++) {
			printf("%d     ", resultsPerClass[i][j]);
		}
		printf("\n");
	}
	*/

	/*
	// Affichage du tableau theorical et correctResultsPerClass
	printf("Theoriquement : ");
	for (int i = 0; i < NB_CLASSES; i++) {
		printf("%d   ", theoricalAppearencePerClass[i]);
	}
	printf("\nEn pratique : ");
	for (int i = 0; i < NB_CLASSES; i++) {
		printf("%d   ", correctResultsPerClass[i]);
	}
	*/

	// Affichage des pourcentages
	/*
	printf("\n Pourcentages : ");
	for (int i = 0; i < NB_CLASSES; i++) {
		printf("%.2f    ", percentageCorrectResultPerClass[i]);
	}
	printf("\nAverage : %.2f", averagePercentageCorrectResult);
	*/


}


// Appel calcul pourcentager au lieu de tableau