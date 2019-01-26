#include "constantes.h" // fichier contenant toutes les constantes du projet
#include <stdint.h>
#include "lpc17xx_i2c.h"

// mettez ici toutes les déclarations de variables globales

char chaine[30]; // buffer pour l'affichage sur le LCD
uint16_t touch_x, touch_y ;

touche currentKey = aucun;
state appState = menuState;

int soundTimer = 0;
int noteSpacingTimer = 0;
int playerWaitTimer = 0;
int playerSkipTimer = 0;
int noteDuration = -1;

bool flagTouch = false;
bool flagSequenceOverflow = false;

int sequencePosition = 0;
int sequenceSize = 0;
int highScore = 0;
touche sequence[MAX_SEQUENCE_SIZE];
