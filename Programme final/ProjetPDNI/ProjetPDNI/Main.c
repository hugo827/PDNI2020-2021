#include "Headers.h"

void main(void) {

	// ==========   PARTIE CR�ATION DES 2 FICHIERS DATASETS   ===================
	//createDatasets();

	// ==========   PARTIE CR�ATION DES 3 FICHIERS MODELES   ===================
	//createModels();

	// ==========   PARTIE REMPLISSAGE DE REALCLASSES ET ESTIMATECLASSES  ===================
	// Nous avons cod� la phase 2 et non la phase 3

	// ==========   PARTIE TRAITEMENT DES RESULTATS   ===================

	// Donn�es fictives pour le moment
	int realClasses[8] = { 5, 2, 5, 3, 5, 3, 2, 4 };
	int estimateClasses[8] = { 5, 5, 1, 2, 1, 3, 2, 4 };


	// Traitement

	int resultsPerClass[NB_CLASSES][NB_CLASSES] = { 0 };

	/*
		Nous allons � partir des donn�es, garnir resultsPerClass et ensuite garnir les variables suivantes
		� partir de ce tableau : petite redondance d'information, certes mais utile si l'affichage se fait plusieurs fois

		resultsPerClass est un tableau 2D o� chaque cellule identifi�e par x et y. O� chaque couple correspond
		� une situation pr�cise (X : real class et Y : estimated class)
		Par exemple, si la cellule (1,2) contient 5 :  il y a eu 5 tests qui aurait du �tre classe 2
		qui a �t� identifi� par la machine comme �tant classe 3. (numCellule-1 : ne pas oublier)
	*/
	array2DFilling(realClasses, estimateClasses, resultsPerClass);

	/*
	theoricalAppearencePerClass contient, pour chaque classe, le nombre de fois que chaque classe devrait apparaitre
	correctResultsPerClass contient, pour chaque classe, le nombre de fois que le programme l'a identifi� correctement
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
