# Aras_Kardous_Haouanah (1)

=======================================Projet Bataille Navale============================

Le projet consiste en un jeu de bataille navale développé en C avec Visual Studio Community 2022 et est compilé sous Windows. Il est sous licence GNU General Public License (GPL) et a été développé par Aras Muhamet-Emre.

=======================================Installation======================================
      Clonez le projet à partir du dépôt GitHub.

=======================================Utilisation=======================================
- Compilez le projet en utilisant Visual Studio Community 2022 ou en utilisant la commande msbuild dans le répertoire racine du projet.
- Exécutez le fichier exécutable généré situé dans le répertoire Project_Battleship\x64\Debug\Project_Battleship_ArasKardousHaouanah.exe.
- Suivez les instructions à l'écran pour jouer au jeu de bataille navale.

=======================================Fonctionnalités===================================
- Placement aléatoire des bateaux sur la grille pour le joueur et l'IA
- Possibilité de déplacer les bateaux du joueur
- Possibilité d'utiliser des fusées éclairantes pour dévoiler des cases ennemies (4 par partie)
- Différents types de bateaux (porte-avion, croiseurs, destroyers, sous-marins)
- La partie se termine lorsque l'un des joueurs n'a plus de navires
- Possibilité de sauvegarder et de charger une partie en cours
- Interface utilisateur simple en ligne de commande

=======================================Instructions du jeu===============================
Au début du jeu, les bateaux sont placés aléatoirement sur la grille, que ce soit pour le joueur ou pour l'IA. Bien entendu, le joueur ne voit pas la grille de son adversaire.

Une fois tous les bateaux en jeu, la partie peut commencer. Le joueur et l'IA ont à leur disposition chacun :

1°) Porte-Avion (ayant une taille de 7 cases)
2°) Croiseurs (ayant une taille de 5 cases)
3°) Destroyers (ayant une taille de 3 cases)
4°) Sous-marins (ayant une taille de 1 case)

Une fois tous les bateaux en jeu, la partie peut commencer ou bien les joueurs peuvent utiliser une fusée éclairante (4 par partie) permettant de dévoiler 4 cases du joueur adverse.

Une partie de bataille navale se termine lorsque le joueur ou l'IA n'a plus de navires.

=======================================Menu principal====================================
- Pour débuter une nouvelle partie, sélectionnez '1' dans le menu principal
- Pour reprendre une partie qui n'a pas été finie, sélectionnez '2' dans le menu principal
- Pour quitter le jeu, sélectionnez '5' dans le menu principal

=======================================Menu de jeu=======================================
- Pour tirer un missile, sélectionnez '1' dans le menu et choisissez la case de l'adversaire que vous souhaitez toucher de la manière suivante : lettre de la case + espace + numéro de la case. Exemple : si vous voulez tirer sur h5, écrivez "h 5"
- Pour déplacer un navire, sélectionnez '2' dans le menu. Cette option permet de dévoiler 4 cases de l'ennemi. La fusée éclairante fonctionne comme suit : sélectionnez la case en haut à gauche du carré (4x4) que vous voulez dévoiler.
- Pour sauvegarder une partie en cours, sélectionnez '4' dans le menu principal et n'oubliez pas d'ajouter ".txt" à la fin du nom du fichier
- 
=======================================Contribution======================================
Les contributions au projet sont les bienvenues. Pour contribuer, veuillez suivre les étapes suivantes :

- Clonez le projet à partir du dépôt GitHub.
- Créez une branche de fonctionnalité à partir de la branche principale.
- Effectuez vos modifications et testez-les.
- Soumettez une demande d'extraction (Pull Request) pour que vos modifications soient examinées et fusionnées avec la branche principale.

=======================================Licence===========================================
Ce projet est sous licence GNU General Public License (GPL). Veuillez consulter le fichier LICENSE.md pour plus d'informations.

=======================================Auteur============================================
Aras Muhamet-Emre

N'hésitez pas à personnaliser ce fichier README.md pour qu'il corresponde à votre projet et à vos besoins.
