# PDNI2020-2021
Membres du groupe : 
Robin Leclercq,
Alexandre Lambert,
Hugo Janssens

Partie traitement des résultats : 
D.A : remis / Code : terminé et fonctionnel

Phase 1 création de datasets :
D.A : remis / Code : terminé et fonctionnel (attention à bien modifier le répertoire des fichiers de données)

Phase 2 création des modèles :
D.A : remis / Code : terminé et fonctionnel

Phase 3 évaluation du testSet :
D.A : remis / Code : terminé et fonctionnel

Nous avons également ajouté les fichiers "classificationStatistics", cependant le programme ne fonctionne plus sur ma machine car
le .obj est configuré en 32 bits alors que ma machine tourne en 64 bits (Erreur : LNK1112 : type d'ordinateur module 'x86' en conflit avec le type d'ordinateur
cible 'x64').

Nous avons codé en multifichiers : 
- les fichiers "Treatment.c" et "Display.c" assurent le traitement des résultats
- le fichier "CreateDatasets.c" se charge de créer les 2 datasets
- le fichier "CreateModels.c" crée les 3 fichiers modèles.
- le fichier "Evaluation.c" se charge de l'évaluation du testSet et de l'affichage des résultats
