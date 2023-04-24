#include "header.h"


/*
Muhammed Aras :
https://waytolearnx.com/2019/09/lister-les-fichiers-dans-un-repertoire-en-c.html

Forum :

https://www.developpez.net/forums/
https://stackoverflow.com/
https://openclassrooms.com/forum/categorie/langage-c
https://learn.microsoft.com/fr-fr/certifications/frequently-asked-questions

*/



size_t getline(char** lineptr, FILE* stream)
{
    char buffer[2048];
    int count = 0;
    char c;
    do {
        c = getc(stream);
        buffer[count] = c;
        count++;
    } while (c != '\n');

    buffer[count] = '\0';
    (*lineptr) = buffer;
    return count;
}




void ReadGridFromText(char** grid, FILE* fp)
{
    char* grid_str;
    int size = getline(&grid_str, fp);
    //grid_str = E,E,E,E,E.......
    int line = 0;
    int col = 0;
    char* c = grid_str + 6;
    sscanf(c, "%c", &grid[0][0]);
    c += 1;
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            if (i == 0 && j == 0) continue;
            sscanf(c, ",%c", &grid[i][j]);
            c += 2;
        }
    }

}

//vide le buffer en lisant un à un les caractères présent dans celui-ci
void vider_buffer(void)
{
    int c;

    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

int main() {

    bool quit = false;
    Player player;       // Création du joueur humain (jeu solo)
    Player computer;      // Création de l'IA en tant que joueur

    while (quit != true)
    {
        //il faut demander s'il veut démmarer un nouveau jeu ou charger un jeu existant
        printf("Menu\n");
        printf("   -1- New game\n");
        printf("   -2- Load game\n");
        printf("   -3- Help\n");
        printf("   -4- Exit\n");
        printf("Enter your choice : ");
        int choicee;
        scanf("%d", &choicee);

        switch (choicee)
        {
        case 1:
        {
            player = newPlayer();       // Création du joueur humain (jeu solo)
            computer = newPlayer();      // Création de l'IA en tant que joueur

            srand(time(NULL));                  // Initialisation du temps
            play(player, computer, true);
        }
        case 2:
        {
            if (Load(&player, &computer))  // Chargement d'un jeu
                play(player, computer, false);
        }break;
        case 4:
        {
            quit = true;
            exit(0);
        }break;
        default:
            break;
        }
        if (choicee == 3)
        {
            printf("\t\t\t\t\t\tHELP\n\n\n");
            printf("\tAu debut du jeu, les bateaux  sont places aleatoirement sur la grille, que ce soit pour le joueur ou pour l'IA\n\n");
            printf("\tBien entendu, le joueur ne voit pas la grille de son adversaire\n\n");
            printf("\tUne fois tous les bateaux en jeu, la partie peut commencer\n\n");
            printf("\tUne fois tous les bateaux en jeu, la partie peut commencer\n\tou bien peuvent utiliser une fusee eclairante (4 par partie) permettant de devoiler 4 cases du joueur adversaire\n\n");
            printf("\tLe joueur et l'IA ont a leur dispostion chacun:\n");
            printf("\t\t - 1 - Porte-Avion (ayant une taille de 7 cases)\n");
            printf("\t\t - 2 - Croiseurs (ayant une taille de 5 cases)\n");
            printf("\t\t - 3 - Destroyers (ayant une taille de 3 cases)\n");
            printf("\t\t - 4 - Sous marin (ayant une taille de 1 cases)\n\n");
            printf("\tUne partie de bataille navale se termine lorsque le joueur ou l'IA n’a plus de navires\n\n");
            printf("\t----- Pour debuter une nouvelle partie selectionnez '1' dans le menu principal                ------\n");
            printf("\t----- Pour reprendre une partie qui n'a pas ete finit selectionnez '2' dans le menu principal ------\n");
            printf("\t----- Pour quitter le jeu sélectionnez '4' dans le menu principal                             ------\n\n\n");
            printf("-----------------        VOUS AVEZ LANCE UNE NOUVELLE PARTIE OU CHARGER UNE EXISTANTE         ------------------\n\n\n");
            printf("\tPour tirer un missile selectionnez '1' dans le menu et choisissez la case de l'adversaire que vous souhaite toucher de la maniere suivante:lettre de la case + SPACE + numero de la case\n");
            printf("\tExemple si vous voulez tirer sur h5 ecrivez (h 5)\n\n");
            printf("\tPour deplacer un navire selectionnez '2' dans le menu\n");
            printf("\tCette option permet de devoiler 4 cases de l'ennemi la fusee eclairante fonctionne comme suit: selectionnez la case en haut a gauche du carre(4*4) que vous voulez devoiler\n\n");
            printf("\tPour sauvegarder une partie en cours selectionnez '4' dans le menu en ,'oubliant pas de mettre .txt à la fin du nom du fichier\n");
            printf("\tVous aurez la possibilite de reprendre cette partie plus tard\n");
            printf("\tPour quitter selectionnez '5' dans le menu\n\n");
            quit = false;
        }
        return 0;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

// Fonction qui crée un espace entre les tableaux

void displayGap() {
    int gapBetweenTab = 3;
    for (int col = 0; col < gapBetweenTab; col++) {
        printf(" ");
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

// Construction de la premi�re ligne du tableau (Index)


void displayColumnIndex() {
    for (int col = 0; col < SIZE + 1; col++) {
        if (col == 0) {
            printf("| / ");
        }
        else {
            printf("|%2d ", col - 1);
        }

        if (col == SIZE + 1 - 1) {
            printf("|");
        }
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

// Fonction qui cr�� une des lignes de s�paration des cases

void displayLine() {
    for (int col = 0; col < SIZE + 1; col++) {
        printf("|___");
        if (col == SIZE + 1 - 1) {
            printf("|");
        }
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

// Affiche la toute premi�re ligne qui ferme le tableau 


void displayFirstLine() {
    for (int col = 0; col < SIZE + 1; col++) {
        printf(" ___");
        if (col == SIZE + 1 - 1) {
            printf(" ");
        }
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

// Fonction qui affiche le contenu du tableau

void displayTabContent(char** tab, int row) {
    for (int col = 0; col < SIZE + 1; col++) {
        if (col == 0) {
            printf("|%2c ", 'a' + row / 2 - 1);
        }
        else {
            printf("|%2c ", tab[row / 2 - 1][col - 1]);
        }
        if (col == SIZE + 1 - 1) {
            printf("|");
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

// Fonction qui appelle les deux fonctions d'affichages ainsi que la fonction qui cr�� l'espace entre les tableaux

void display2(void (*display)()) {
    (*display)();
    displayGap();
    (*display)();
}




///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

// Fonction qui g�re l'affichage 


void display(Player* player) {
    int tabSize = SIZE + 1;

    // Une case correspond à 2 lignes, pour cela on regarde les lignes impaires pour les délimiter
    for (int row = 0; row < 2 * tabSize; row++) {
        if (row % 2 != 0) {
            if (row == 1) {
                display2(displayColumnIndex);
            }
            else {
                displayTabContent(player->tab1, row);
                displayGap();
                displayTabContent(player->tab2, row);
            }
            printf("\n");
        }
        else {
            if (row != 0) {
                display2(displayLine);
            }
            else {
                display2(displayFirstLine);
            }
            printf("\n");
        }
    }
    display2(displayLine);
    printf("\n");
}


///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

// Fonction qui cr�� un nouveau joueur

Player newPlayer() {
    Player player;
    int totalNumberOfShip = MAX_CROISEUR + MAX_DESTOYER + MAX_PORTE_AVION + MAX_SOUSMARIN;  // Bateaux � avoir initialement
    player.ships = malloc(totalNumberOfShip * sizeof(Ship));                               // Allocation dynamique du tableau de bateaux
    int shipIndex = 0;
    for (int i = 0; i < MAX_PORTE_AVION; i++) {
        player.ships[shipIndex++] = newShip(PORTE_AVION);
    }
    for (int i = 0; i < MAX_CROISEUR; i++) {
        player.ships[shipIndex++] = newShip(CROISEUR);
    }
    for (int i = 0; i < MAX_DESTOYER; i++) {
        player.ships[shipIndex++] = newShip(DESTOYER);
    }
    for (int i = 0; i < MAX_SOUSMARIN; i++) {
        player.ships[shipIndex++] = newShip(SOUSMARIN);
    }
    player.nShip = totalNumberOfShip;    // Sauvegarde du nombre total de bateaux
    player.tab1 = newTab();              // Appel de la fonction qui cr�� le tableau 1
    player.tab2 = newTab();              // Idem pour le tableau 2
    return player;
}

///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

// Fonction qui cr�� un nouveau bateau

Ship newShip(char type) {
    Ship ship;
    ship.type = type;                // Sauvegarde du type entr� en param�tre
    if (type == PORTE_AVION) {
        ship.length = L_PORTE_AVION;
    }
    else if (type == DESTOYER) {
        ship.length = L_DESTOYER;
    }
    else if (type == CROISEUR) {
        ship.length = L_CROISEUR;
    }
    else if (type == SOUSMARIN) {
        ship.length = L_SOUSMARIN;
    }
    ship.life = ship.length;                             // La vie vaut le nombre de case que prend le bateau
    ship.states = malloc(ship.length * sizeof(int));     // Allocation dynamique du tableau de l'�tat de chaque partie

    for (int i = 0; i < ship.length; i++) {
        ship.states[i] = 1;                             // Initialisation de l'�tat
    }
    return ship;
}

///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

// Fonction qui place le bateau d'un joueur al�atoirement dans la grille

void placePlayerShips(Player* player) {
    for (int shipIndex = 0; shipIndex < player->nShip; shipIndex++) {   // Pour i allant de 0 au nombre de bateaux du joueur :
        char orientation;
        int row;
        int col;
        do {
            // printf("i : %d %c\n", shipIndex, player->ships[shipIndex].type);
            if (rand() % 2 == 0) { // vertical orientation
                orientation = 'h';
                row = rand() % SIZE;
                col = rand() % (SIZE - player->ships[shipIndex].length + 1);
            }
            else { // horizontal orientation
                orientation = 'v';
                row = rand() % (SIZE - player->ships[shipIndex].length + 1);
                col = rand() % SIZE;
            }
            // printf("Coords : %c-%d-%c\n", 'a' + row, col, orientation);
        } while (!placeShip(player->tab1, &player->ships[shipIndex], (Coords) { row, col }, orientation));  // Placement du bateau
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

// Fonction qui sauvegarde et �crit le placement de chaque bateau dans la grille du joueur

int placeShip(char** tab, Ship* ship, Coords coord, char orientation) {
    int shipPlaced = 0;                 // Boolean permettant de savoir si le bateau a bien �t� plac�
    int count = 0;                      // Initialisation du compteur � 0
    if (orientation == 'h') {
        while (count < ship->length && tab[coord.row][coord.col + count] == ' ') {   // Incrementation sur la colonne car horizontal
            count++;
        }
        if (count == ship->length) {                      // Si le compteur repr�sente bien la longueur du bateau horizontalement :
            ship->coord = coord;                        // Sauvegarde des coordon�es du bateau
            ship->orientation = orientation;            // Sauvegarde de l'orientation du tableau
            for (int i = 0; i < ship->length; i++) {
                tab[coord.row][coord.col + i] = ship->type;  // Ecriture de la lettre du type dans les cases correspondantes au placement 
            }
            shipPlaced = 1;    // Bateau plac�
        }
    }
    else if (orientation == 'v') {
        while (count < ship->length && tab[coord.row + count][coord.col] == ' ') {  // Incrementation sur la colonne car vertical
            count++;
        }
        if (count == ship->length) {
            ship->coord = coord;
            ship->orientation = orientation;
            for (int i = 0; i < ship->length; i++) {
                tab[coord.row + i][coord.col] = ship->type;
            }
            shipPlaced = 1;
        }
    }
    return shipPlaced;
}

///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

// Fonction qui cr�� un tableau dynamique

char** newTab() {
    char** tab = malloc(SIZE * sizeof(char*));
    for (int row = 0; row < SIZE; row++) {
        tab[row] = malloc(SIZE * sizeof(char));
    }
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            tab[row][col] = ' ';            // Le tableau est compl�tement vide initialement
        }
    }
    return tab;
}

///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


// Fonction qui traite l'attaque d'un joueur sur une cible | 'a' vaut 97 transtyp� en int on initialisera � cette valeur par facilit�

void attack(Player* attacker, Player* target, Coords coord) {
    printf("Enter attack's coordinates : ");
    char row;
    getchar();
    scanf("%c %d", &row, &coord.col);
    coord.row = row - 'a';                 // Initialisation de la ligne des coordonnées

    printf("Attack at %c%d : ", 'a' + coord.row, coord.col);
    if (target->tab1[coord.row][coord.col] != ' ') {              // Si la case est non-vide
        attacker->tab2[coord.row][coord.col] = 'T';             // Touché
        int Index = getCorespondingShipIndex(target, coord);
        attackSucceed(&target->ships[Index]); // Sauvegarde de la perte de vie           
        printf("Touched\n");
        printf("The ship number %d is under attack !\n", Index);
        if (target->ships[Index].life == 0)
        {
            printf("The ship number %d is destroyed\n", Index);
        }
    }
    else {
        attacker->tab2[coord.row][coord.col] = 'E';
        printf("Missed\n");                                    // Raté
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

// Fonction qui compare les coordonn�es entr�es en param�tre et renvoie le bool�en correspondant

int sameCoords(Coords coord1, Coords coord2) {
    // printf("%c%d %c%d\n", 'a' + coord1.row, coord1.col, 'a' + coord2.row, coord2.col);
    return (coord1.col == coord2.col && coord1.row == coord2.row);
}


///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

//  Fonction qui renvoie l'index du bateau touch�

int getCorespondingShipIndex(Player* target, Coords coord) {
    int index = 0;
    while (!belongToShip(&target->ships[index], coord)) {
        if (index > 9)
        {
            printf("No ship here.\n");
            break;
        }
        index++;
    }
    return index;
}


///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

// Fonction qui prend en compte la r�duction de vie du bateau et change l'�tat de la partie concern�e

void attackSucceed(Ship* ship) {
    // ship->states[shipPartIndex] = 0;
    if (ship->life > 0) {
        ship->life--;
    }

}

///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

// Fonction qui permet de d�tecter si la case concern�e appartient � un bateau

int belongToShip(Ship* ship, Coords coord) {
    // printf("type : %c, length : %d", ship->type, ship->length);
    // printf(", orientation : %c, coord : %c%d\n",ship->orientation, 'a' + ship->coord.row, ship->coord.col);

    int belong = 0;                  // Booléen sur l'appartenance

    // Deux cas à traiter : vertical et horizontal
    if (ship->orientation == 'v') {
        for (int i = 0; i < ship->length; i++) {
            if (sameCoords(coord, (Coords) { ship->coord.row + i, ship->coord.col })) {
                // attackSucceed(ship, i);          
                belong = 1;
            }
        }
    }
    else if (ship->orientation == 'h') {
        for (int i = 0; i < ship->length; i++) {
            if (sameCoords(coord, (Coords) { ship->coord.row, ship->coord.col + i })) {
                //  attackSucceed(ship, i);
                belong = 1;
            }
        }
    }
    return belong;
}


///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


// Fonction qui va gérer l'affichage de 2*2 case "FLARE" 
void reveal(Player* attacker, Player* target, Coords coord) {

    int effacer[4][4];
    char row;

    // Blindage pour éviter les bugs sur extremum
    do {
        printf("Your flash will reveal a 2*2 zone, enter the up-left coordinate of the square that you want to reveal.\n");
        getchar();
        scanf("%c %d", &row, &coord.col);
        coord.row = row;
        if (coord.row == 'o' || coord.row == 'n' || coord.row == 'm' || coord.col == 14 || coord.col == 13 || coord.col == 12)
        {
            printf("Wrong coordinates.\n");
        }
    } while (coord.row == 'o' || coord.row == 'n' || coord.row == 'm' || coord.col == 14 || coord.col == 13 || coord.col == 12);

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (attacker->tab2[coord.row - 'a' + i][coord.col + j] != 'E' && attacker->tab2[coord.row - 'a' + i][coord.col + j] != 'T')
            {
                attacker->tab2[coord.row - 'a' + i][coord.col + j] = target->tab1[coord.row - 'a' + i][coord.col + j];
                effacer[i][j] = 1;        // Boolean sur l'effacement
            }
        }
    }

    display(attacker);
    Sleep(3000);
    system("cls");

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (effacer[i][j] == 1)
            {
                attacker->tab2[coord.row - 'a' + i][coord.col + j] = ' ';
            }
        }
    }
}


/////////////////////////////////////////////////////



void move(Player* target, Coords coord) {
    char d = 'x';
    coord.row = 'x';
    coord.col = -1;
    while (d != 'n' && d != 's' && d != 'e' && d != 'o')
    {
        printf("Type the letter of the direction.\n");
        scanf("%s", &d);
        if (d != 'n' && d != 's' && d != 'e' && d != 'o')
        {
            printf("Wrong direction.\n");
        }
    }
    int Index = 10;
    while (Index > 9 || (coord.row > 'a' + 'o' || coord.row < 'a' + 'a') && (coord.col < 0 || coord.col > 14)) {
        printf("Type one of the coordinates of the ship that you want to move.\n");
        char row;
        getchar();
        scanf("%c %d", &row, &coord.col);
        coord.row = row - 'a';
        if ((coord.row > 'a' + 'o' || coord.row < 'a' + 'a') && (coord.col < 0 || coord.col > 14))
        {
            printf("Wrong coordinates.\n");
        }
        Index = getCorespondingShipIndex(target, coord);
    }

    step(&target->ships[Index], target, d);
}


/////////////////////////////////////////////////////
void step(Ship* ship, Player* player, char dir)
{
    char s[7];
    if (ship->orientation == 'h')
    {
        if (dir == 'e' && ship->coord.col + ship->length - 1 == 14)
        {
            printf("You can't move to this direction, you have reached the limit of the map !\n");
        }
        else if (dir == 'e')
        {
            if (player->tab1[ship->coord.row][ship->coord.col + ship->length] == 'P' || player->tab1[ship->coord.row][ship->coord.col + ship->length] == 'C' || player->tab1[ship->coord.row][ship->coord.col + ship->length] == 'D' || player->tab1[ship->coord.row][ship->coord.col + ship->length] == 'S')
            {
                printf("You can't move here, a ship is already there !\n");
            }
            else
            {
                for (int i = 0; i < ship->length; i++)
                {
                    s[i] = player->tab1[ship->coord.row][ship->coord.col + i];  // Tableau qui sauvegarde
                    player->tab1[ship->coord.row][ship->coord.col + i + 1] = s[i]; // Décalage de 1
                }
                player->tab1[ship->coord.row][ship->coord.col] = ' '; // Suppression de la première case
                ship->coord.col++; // Actualisation de la nouvelle coordonnée de construction (Avancer)
            }
        }
        else if (dir == 'o' && ship->coord.col == 0)
        {
            printf("You can't move to this direction, you have reached the limit of the map !\n");
        }
        else if (dir == 'o')
        {
            if (player->tab1[ship->coord.row][ship->coord.col - 1] == 'P' || player->tab1[ship->coord.row][ship->coord.col - 1] == 'C' || player->tab1[ship->coord.row][ship->coord.col - 1] == 'D' || player->tab1[ship->coord.row][ship->coord.col - 1] == 'S')
            {
                printf("You can't move here, a ship is already there !\n");
            }
            else
            {
                for (int i = 0; i < ship->length; i++)
                {
                    s[i] = player->tab1[ship->coord.row][ship->coord.col + i];  // Tableau qui sauvegarde
                    player->tab1[ship->coord.row][ship->coord.col + i - 1] = s[i]; // Décalage de 1
                }

                player->tab1[ship->coord.row][ship->coord.col + ship->length - 1] = ' '; // Suppression de la dernière case
                ship->coord.col--; // Actualisation de la nouvelle coordonnée de construction (Reculer)
            }

        }
        else
        {
            printf("You have chosen the wrong direction !\n");
        }
    }

    else if (ship->orientation == 'v')
    {
        if (dir == 's' && 'a' + ship->coord.row + ship->length - 1 == 'o')
        {
            printf("You can't move to this direction, you have reached the limit of the map !\n");
        }
        else if (dir == 's')
        {
            if (player->tab1[ship->coord.row + ship->length][ship->coord.col] == 'P' || player->tab1[ship->coord.row + ship->length][ship->coord.col] == 'C' || player->tab1[ship->coord.row + ship->length][ship->coord.col] == 'D' || player->tab1[ship->coord.row + ship->length][ship->coord.col] == 'S')
            {
                printf("You can't move here, a ship is already there !\n");
            }
            else
            {
                for (int i = 0; i < ship->length; i++)
                {
                    s[i] = player->tab1[ship->coord.row + i][ship->coord.col];  // Tableau qui sauvegarde
                    player->tab1[ship->coord.row + i + 1][ship->coord.col] = s[i]; // Décalage de 1
                }

                player->tab1[ship->coord.row][ship->coord.col] = ' '; // Suppression de la première case
                ship->coord.row++; // Actualisation de la nouvelle coordonnée de construction (Descendre)
            }

        }
        else if (dir == 'n' && 'a' + ship->coord.row == 'a')
        {
            printf("You can't move to this direction, you have reached the limit of the map !\n");
        }
        else if (dir == 'n')
        {
            if (player->tab1[ship->coord.row - 1][ship->coord.col] == 'P' || player->tab1[ship->coord.row - 1][ship->coord.col] == 'C' || player->tab1[ship->coord.row - 1][ship->coord.col] == 'D' || player->tab1[ship->coord.row - 1][ship->coord.col] == 'S')
            {
                printf("You can't move here, a ship is already there !\n");
            }
            else
            {
                for (int i = 0; i < ship->length; i++)
                {
                    s[i] = player->tab1[ship->coord.row + i][ship->coord.col];  // Tableau qui sauvegarde
                    player->tab1[ship->coord.row + i - 1][ship->coord.col] = s[i]; // Décalage de 1
                }

                player->tab1[ship->coord.row + ship->length - 1][ship->coord.col] = ' '; // Suppression de la dernière case
                ship->coord.row--; // Actualisation de la nouvelle coordonnée de construction (Monter)
            }

        }
        else
        {
            printf("You have chosen the wrong direction !\n");
        }
    }
}


/////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

// Fonction qui g�re le tour de l'IA

void IAattack(Player* attacker, Player* target, Coords coord) {

    char row = rand() % SIZE;
    coord.col = rand() % SIZE;
    coord.row = row;

    printf("Your opponent attacks at %c%d : ", 'a' + coord.row, coord.col);
    if (target->tab1[coord.row][coord.col] != ' ') {              // Si la case est non-vide
        target->tab1[coord.row][coord.col] = 'T';             // Touché
        printf("Touched\n");
        int Index = getCorespondingShipIndex(target, coord);
        printf("Your ship number %d is under attack !\n", Index);
        attackSucceed(&target->ships[Index]); // Sauvegarde de la perte de vie 
        if (target->ships[Index].life == 0)
        {
            printf("Your ship number %d is destroyed\n", Index);
        }
    }
    else {
        target->tab1[coord.row][coord.col] = 'E';
        printf("Missed\n");                                    // Raté
    }

}


///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void play(Player player1, Player computer, bool is_new_game)
{
    srand(time(NULL));                  // Initialisation du temps
    if (is_new_game)
    {
        placePlayerShips(&player1);         // Appel de la fonction qui place les bateaux du joueur humain
        placePlayerShips(&computer);        // Appel de la fonction qui place les bateaux de l'IA
    }

    char ch;
    int choice;
    bool tourIA = false;                                                            // L'humain commnce au début
    int flares = 0, dia = 0, dp = 0;                                                                  // On a le droit à 4 flares

    do {
        Sleep(2000);
        system("cls");
        // Compter le nombre de bateaux detruits pour chaque joueur
        for (int i = 0; i < MAXSHIP; i++)
        {
            if (computer.ships[i].life == 0)
            {
                dia++;

            }
            else if (player1.ships[i].life == 0)
            {
                dp++;
            }
        }

        if (dp == 10)  // Si les 10 bateaux du joueur humain sont detruits (Defaite)
        {
            printf("Défaite !\n");
            exit(0);
        }
        else if (dia == 10)  // Si les 10 bateaux de l'IA sont detruits (Victoire)
        {
            printf("Victoire !\n");
            exit(1);
        }

        // Reinitialisation des compteurs
        dp = 0;
        dia = 0;
        display(&player1);                                                          // Afficher les bateaux du joueur humain (ceux de l'IA sont cach�s)
        if (tourIA == false)
        {
            printf("\nAppuez sur n'importe quelle touche pour ouvrir le menu\n");
            if (!kbhit())
            {
                ch = getch();
                if ((int)ch == 118)
                {
                    printf("Cheat mode : ON\n");
                    for (int i = 0; i < SIZE; i++)
                    {
                        for (int j = 0; j < SIZE; j++)
                        {
                            player1.tab2[i][j] = computer.tab1[i][j];
                        }
                    }
                }
            }
            printf("It's your turn to play !\n\n\n");
            printf("\t\t------- Menu -------\n\n\n");
            printf("\t\t-1- Missile\n");
            printf("\t\t-2- Move the Ship \n");
            printf("\t\t-3- Flare\n");
            printf("\t\t-4- Save the Game\n");
            printf("\t\t-5- Exit \n\n\n");
            printf("What Option you selected ? : ");
            scanf("%d", &choice);

            switch (choice) {
            case 1:
            {
                attack(&player1, &computer, (Coords) { 5, 5 });               // Appel de la fonction qui permet d'attaquer l'IA 
                printf("Your turn is over. Your opponent is attacking !\n");
                tourIA = true;                                                // C'est au tour de l'IA une fois l'attaque terminée
            }break;
            case 2:
            {
                move(&player1, (Coords) { 5, 5 });                           // Appel de la fonction qui permet de faire bouger un bateau
                tourIA = true;                                               // C'est au tour de l'IA une fois l'attaque terminée
            }break;
            case 3:
            {
                // RAPPEL ON A LE DROIT QU'A 4 FLARES
                if (flares == 4)
                {
                    printf("You don't have any more flares !\n");
                    break;
                }
                reveal(&player1, &computer, (Coords) { 5, 5 });             // Appel de la fonction qui révèle une partie des cases     
                flares++;
                tourIA = true;                                             // C'est au tour de l'IA une fois l'attaque terminée
            }
            break;
            case 4:
            {

                Save(player1, computer);                                   // Appel de la fonction qui sauvegarde la partie en cours
            }break;
            case 5:
                exit(0);                                                   // Arrête le programme
                break;
            default:
                break;
            }
        }
        else
        {
            IAattack(&computer, &player1, (Coords) { 5, 5 });              // Quand TourIA == true, on appelle la fonction IA Attack
            tourIA = false;                                               // Tour de l'humain
        }
    } while (choice != 5);                                                // Blindage du choix du menu
}


///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

// Fonction qui sauvegarde les coordonées de chaque bateau
void saveCoord(Coords coord, FILE* fp)
{
    // Ecriture dans le fichier
    fprintf(fp, "{\n");
    fprintf(fp, "row=%d\ncol=%d\n", coord.row, coord.col);
    fprintf(fp, "}\n");
}

// Fonction qui reconstruit les coordonée de chaque Ships
int LoadCoordone(FILE* fp, Coords* coord, int pos)
{
    char* line;
    //fseek(fp, pos, SEEK_SET);
    int count = 1;
    count += getline(&line, fp);//{\n
    count += getline(&line, fp);
    sscanf(line, "row=%d\n", &coord->row);
    count += getline(&line, fp);
    sscanf(line, "col=%d\n", &coord->col);
    count += getline(&line, fp);//}\n
    return count;
}

///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

// Fonction qui sauvegarde chaque navires avec ses caractéristiques
void saveShip(Ship ship, FILE* fp)
{
    // Ecriture dans le fichier des caracteritiques du bateau
    fprintf(fp, "{\n");
    fprintf(fp, "type=%c\nlength=%d\norientation=%c\nlife=%d\n", ship.type, ship.length, ship.orientation, ship.life);

    // Sauvegarde du premier bateau pour ouvrir l'accolade 
    fprintf(fp, "states=[");
    fprintf(fp, "%d", ship.states[0]);

    // Sauvegarde de chaque bateau sauf la première
    for (int j = 1; j < ship.length; ++j)
        fprintf(fp, ",%d", ship.states[j]);
    fprintf(fp, "]\n");
    fprintf(fp, "coord=\n");
    // Appel de la fonction SaveCoord qui écrire les coordonnées de chaque bateau sur la grille
    saveCoord(ship.coord, fp);
    fprintf(fp, "}\n");
}

// Fonction qui va reconstruire l'objet Ship à partir du fichier de sauvegarde
int LoadShip(FILE* fp, Ship* ship, int pos)
{
    int count = 2;
    pos += count;
    //fseek(fp, pos, SEEK_SET);

    char* line;
    count += getline(&line, fp);//{\n
    count += getline(&line, fp);//type=....
    sscanf(line, "type=%c\n", &ship->type);

    count += getline(&line, fp);
    sscanf(line, "length=%d\n", &ship->length);

    count += getline(&line, fp);
    sscanf(line, "orientation=%c\n", &ship->orientation);

    count += getline(&line, fp);
    sscanf(line, "life=%d\n", &ship->life);

    //states
    count += getline(&line, fp);

    // On enregistre les informations sur chaque navires 
    switch (ship->life)
    {
    case 7:
    {
        ship->states = (int*)malloc(sizeof(int) * 7);
        sscanf(line, "states=[%d,%d,%d,%d,%d,%d,%d]\n", ship->states, ship->states + 1, ship->states + 2, ship->states + 3, ship->states + 4, ship->states + 5, ship->states + 6);
    }break;
    case 5:
    {
        ship->states = (int*)malloc(sizeof(int) * 5);
        sscanf(line, "states=[%d,%d,%d,%d,%d]\n", ship->states, ship->states + 1, ship->states + 2, ship->states + 3, ship->states + 4);
    }break;
    case 3:
    {
        ship->states = (int*)malloc(sizeof(int) * 3);
        sscanf(line, "states=[%d,%d,%d]\n", ship->states, ship->states + 1, ship->states + 2);
    }break;
    case 1:
    {
        ship->states = (int*)malloc(sizeof(int) * 1);
        sscanf(line, "states=[%d]\n", ship->states);
    }break;
    }

    count += getline(&line, fp);//coord=
    count += LoadCoordone(fp, &ship->coord, count + pos + 1);
    count += getline(&line, fp);//}\n
    return count;
}


///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

// Fonction qui enregistre tous les informations sur l'objets Player
void savePlayer(Player p, FILE* fp)
{
    fprintf(fp, "{\n");
    fprintf(fp, "nShip=%d\n", p.nShip);
    fprintf(fp, "ships=[\n");
    saveShip(p.ships[0], fp);
    for (int i = 1; i < p.nShip; ++i)
    {
        fprintf(fp, ",\n");
        saveShip(p.ships[i], fp);
    }
    fprintf(fp, "]\n");
    // SAuvgarde de la grille tab 1
    fprintf(fp, "tab1=[");
    fprintf(fp, "%c", p.tab1[0][0]);
    for (int i = 0; i < 15; ++i)
    {
        for (int j = 0; j < 15; ++j)
        {
            if (i == 0 && j == 0) continue;
            fprintf(fp, ",%c", p.tab1[i][j]);
        }
    }
    fprintf(fp, "]\n");
    //SAuvgarde de la grille  tab 2 
    fprintf(fp, "tab2=[");
    fprintf(fp, "%c", p.tab2[0][0]);
    for (int i = 0; i < 15; ++i)
    {
        for (int j = 0; j < 15; ++j)
        {
            if (i == 0 && j == 0) continue;
            fprintf(fp, ",%c", p.tab2[i][j]);
        }
    }
    fprintf(fp, "]\n");
    fprintf(fp, "}\n");
}

// Fonction qui va reconstruire l'objet Player à partir du fichier de sauvegarde
int LoadPlayer(Player* player, FILE* fp, int pos)
{
    //pos += 3;
    //fseek(fp, pos, SEEK_SET);
    int nb_char = 0;
    char* line;

    nb_char += getline(&line, fp);//{\n
    // Recupere le nombre de Ship
    nb_char += getline(&line, fp);
    sscanf(line, "nShip=%d\n", &player->nShip);

    //Reconstrution des ships
    nb_char += getline(&line, fp);
    if (player->nShip > 0)
    {
        player->ships = (Ship*)malloc(sizeof(Ship) * player->nShip);
        for (int i = 0; i < player->nShip; ++i)
        {
            int count = LoadShip(fp, player->ships + i, pos + nb_char + 1);
            nb_char += count;
            nb_char += getline(&line, fp);//,\n ou ] pour le dernier élément
        }
    }
    player->tab1 = (char**)malloc(sizeof(char*) * SIZE);
    player->tab2 = (char**)malloc(sizeof(char*) * SIZE);
    for (int i = 0; i < SIZE; ++i)
    {
        player->tab1[i] = (char*)malloc(sizeof(char) * SIZE);
        player->tab2[i] = (char*)malloc(sizeof(char) * SIZE);
    }
    // Boucle sur line jusqu'a 15 
    ReadGridFromText(player->tab1, fp);

    ReadGridFromText(player->tab2, fp);
    return nb_char + 1;
}

///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


bool Load(Player* player, Player* computer)
{
    //lister afficher les fichiers dans le repertoire de sauvegarde
    dirent* dir;
    DIR* d = opendir("./SAVED_DIR");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            printf("\t _ %s\n", dir->d_name);
        }
        closedir(d);

        //demander à l'utilsateur de taper le nom du fichier
        char file_name[256];
        printf("Sauvegarde a loader : ");
        scanf("%s", file_name);

        char path[256];
        sprintf(path, "SAVED_DIR/%s", file_name);
        //char* path = strcat(", file_name);
        FILE* fp = fopen(path, "r");
        if (fp != NULL)
        {
            long count = LoadPlayer(player, fp, 0);
            char* line;
            count += getline(&line, fp);//}\n
            //fseek(fp, count, SEEK_SET);
            count += LoadPlayer(computer, fp, count);
            return true;
        }
        else
        {
            printf("Impossible de loader le sauvegard %s", file_name);
        }
    }
    else
    {
        printf("Aucun fichier sauvegarde trouvé sur ce PC");
    }
    return false;
}

// Fonction qui enregistre tous les informations sur l'objets Player

void Save(Player player, Player computer)
{
    char file_name[256];
    printf("Donnez un nom a votre fichier de sauvegarde : ");
    int vv = scanf("%s", file_name);

    //vérifier que le dossier de sauvegarde existe
    struct stat st = { 0 };
    if (stat("SAVED_DIR", &st) == -1) {
        //crée le dossier s'il n'existe pas
        system("mkdir SAVED_DIR");
    }
    int name_size = strlen(file_name);
    char path[256];
    sprintf(path, "SAVED_DIR/%s", file_name);

    // Ouverture du fichier
    FILE* fichier = fopen(path, "w");
    // Condition d'ouverture
    if (fichier == NULL)
    {
        printf("Impossible d'ouvrir le fichier de sauvegarde");
    }
    else
    {
        // On sauvegarde tout
        savePlayer(player, fichier);
        savePlayer(computer, fichier);
        fclose(fichier);
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


