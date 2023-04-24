#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <Windows.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <conio.h>

#pragma warning(disable : 4996)
#define SIZE 15      // Taille du tableau
#define MAXSHIP 10   

const char PORTE_AVION = 'P';
const char CROISEUR = 'C';
const char DESTOYER = 'D';
const char SOUSMARIN = 'S';

// Longueur de bateau
const int L_PORTE_AVION = 7;
const int L_CROISEUR = 5;
const int L_DESTOYER = 3;
const int L_SOUSMARIN = 1;

// Nombre maximum de bateau
const int MAX_PORTE_AVION = 1;
const int MAX_CROISEUR = 2;
const int MAX_DESTOYER = 3;
const int MAX_SOUSMARIN = 4;

const char* SAVE_DIR = "SavedGames";


typedef struct {
    int row;      // Ligne
    int col;      // Colonne
}Coords;


typedef struct {
    char type;          // Type du bateau
    int length;         // Longueur du bateau
    char orientation;   // Orientation du bateau
    int life;           // Vie(s) du bateau
    int* states;        // Etat de chaque partie du bateau (0:détruit, 1:intact)
    Coords coord;       // Coordonn�es du bateau
}Ship;


typedef struct {
    Ship* ships;        // Bateau(x) du joueur
    int nShip;          //  Nombre de bateaux
    char** tab1;        // Grille 1 du joueur
    char** tab2;        // Grille 2 (celle de l'adversaire)
}Player;


// Prototypes 
void displayGap();
void displayColumnIndex();
void displayLine();
void displayFirstLine();
void displayTabContent(char** tab, int row);
void display2(void (*display)());
void display(Player* player);
int sameCoords(Coords coord1, Coords coord2);
void attack(Player* attacker, Player* target, Coords coord);
int getCorespondingShipIndex(Player* target, Coords coord);
int belongToShip(Ship* ship, Coords coord);
Player newPlayer();
Ship newShip(char type);
void attackSucceed(Ship* ship);
int placeShip(char** tab, Ship* ship, Coords coord, char orientation);
void placePlayerShips(Player* player);
char** newTab();
int sameCoords(Coords coord1, Coords coord2);

//
void reveal(Player* attacker, Player* target, Coords coord);
void move(Player* target, Coords coord);
void step(Ship* ship, Player* player, char dir);

void IAattack(Player* attacker, Player* target, Coords coord);
void play(Player player1, Player computer, bool is_new_game);
void Save(Player player, Player computer);
void savePlayer(Player p, FILE* fp);
void saveShip(Ship ship, FILE* fp);
void saveCoord(Coords coord, FILE* fp);
bool Load(Player* player, Player* computer);
int LoadPlayer(FILE* fp, Player* player, int pos);
int LoadShip(FILE* fp, Ship* ship, int pos);
int LoadCoordone(FILE* fp, Coords* coord, int pos);