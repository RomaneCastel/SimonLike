#include "constantes.h" // fichier contenant toutes les constantes du projet
#include <stdint.h>
#include <stdbool.h>

// mettez ici toutes les "extern" correspondant aux déclarations contenues dans globadec.h

#define MILI_2_TICKS(x, y) x*1000/y
#define MICRO_2_TICKS(x, y) (1/(float)x*1000000)/y

extern char chaine[30]; // buffer pour l'affichage sur le LCD
extern uint16_t touch_x, touch_y ;

extern touche currentKey;
extern state appState;

extern int soundTimer;
extern int playerWaitTimer;
extern int playerSkipTimer;
extern int noteSpacingTimer;
extern int noteDuration;

extern bool flagTouch;
extern bool flagSequenceOverflow;

extern int sequencePosition;
extern int sequenceSize;
extern int highScore;
extern touche sequence[MAX_SEQUENCE_SIZE];
