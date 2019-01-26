#ifndef CONSTANTES_H
#define CONSTANTES_H

typedef enum {aucun,jaune,vert,rouge,bleu} touche;
typedef enum {newGame, menuState, menuWaitState, highScoreState, highScoreSequenceState, playSequence, playerTurn, addNote, endGame, waitEndGame} state;

// mettez dans ce fichier toutes les constantes et définitions 
// des nouveaux types que vous souhaitez

// ====== Sound ======

// Notes frequency in Hz
#define FREQ_YELLOW 1047
#define FREQ_RED 1175
#define FREQ_GREEN 1319
#define FREQ_BLUE 1497

// Note duration in ms
#define NOTE_DURATION 500

#define MAX_SEQUENCE_SIZE 50

// ms
#define MAX_PLAYER_WAIT 2000

// ms
#define NOTE_SPACING_TIME 100

// ms
#define PLAYER_SKIP 10

// Memory
#define MEM_ADDR 0xA0 // Pour accéder à la mémoire, on donne la slave address
#define MAX_NEWDATA_SIZE MAX_SEQUENCE_SIZE + 1  // taille maximum du tableau data

// ms
#define MENU_WAIT 500

#endif
