#include "Headers.h"

void main(void) {

	// ==========   PARTIE CRÉATION DES 2 FICHIERS DATASETS   ===================
	//createDatasets();

	// ==========   PARTIE CRÉATION DES 3 FICHIERS MODELES   ===================
	//createModels();

	// ==========   PARTIE REMPLISSAGE DE REALCLASSES ET ESTIMATECLASSES  ===================
	// Nous avons codé la phase 2 et non la phase 3

	// ==========   PARTIE TRAITEMENT DES RESULTATS   ===================

	// Données fictives pour le moment
	int realClasses[8] = { 5, 2, 5, 3, 5, 3, 2, 4 };
	int estimateClasses[8] = { 5, 5, 1, 2, 1, 3, 2, 4 };


	// Traitement

	int resultsPerClass[NB_CLASSES][NB_CLASSES] = { 0 };

	/*
		Nous allons à partir des données, garnir resultsPerClass et ensuite garnir les variables suivantes
		à partir de ce tableau : petite redondance d'information, certes mais utile si l'affichage se fait plusieurs fois

		resultsPerClass est un tableau 2D où chaque cellule identifiée par x et y. Où chaque couple correspond
		à une situation précise (X : real class et Y : estimated class)
		Par exemple, si la cellule (1,2) contient 5 :  il y a eu 5 tests qui aurait du être classe 2
		qui a été identifié par la machine comme étant classe 3. (numCellule-1 : ne pas oublier)
	*/
	array2DFilling(realClasses, estimateClasses, resultsPerClass);

	/*
	theoricalAppearencePerClass contient, pour chaque classe, le nombre de fois que chaque classe devrait apparaitre
	correctResultsPerClass contient, pour chaque classe, le nombre de fois que le programme l'a identifié correctement
	*/

	int theoricalAppearencePerClass[NB_CLASSES] = { 0 };
	int correctResultsPerClass[NB_CLASSES] = { 0 };
	

	double percentageCorrectResultPerClass[NB_CLASSES] = { 0 };
	double averagePercentageCorrectResult;

	/* Appels des fonctions 
	resultsForEachClasses(theoricalAppearencePerClass, correctResultsPerClass, resultsPerClass);

	percentageAccuracyPerClass(percentageCorrectResultPerClass, theoricalAppearencePerClass, correctResultsPerClass, &averagePercentageCorrectResult);

	displayResultsForEachClasses(theoricalAppearencePerClass, correctResultsPerClass, percentageCorrectResultPerClass);
	displayAccuracy(&averagePercentageCorrectResult);
	displayClass(theoricalAppearencePerClass, resultsPerClass);
	*/
}
