//===========================================================//
// Projet Micro - INFO1 - ENSSAT - S2 2018							 //
//===========================================================//
// File                : Programme de départ
// Hardware Environment: Open1768	
// Build Environment   : Keil µVision
//===========================================================//

#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_timer.h"
#include "touch\ili_lcd_general.h"
#include "touch\lcd_api.h"
#include "affichagelcd.h"
#include "touch\touch_panel.h"
#include "tactile.h"
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "assert.h"
#include "memoire.h"
#include "globaldec.h" // fichier contenant toutes les déclarations de variables globales
#include <stdio.h>
#include "timer0.h"
#include "timer1.h"
#include "memoire.h"


//===========================================================//
// Function: pin_Configuration
//===========================================================//
void write_highscore() { // écriture en mémoire du highscore et de la séquence correspondant à cet highscore, mettre à jour highscore avant d'appeler la fonction
		int i;
		Status result = ERROR;
		uint8_t data[MAX_SEQUENCE_SIZE];
		
		data[0]= highScore;
		for(i=1; i<=highScore; i++) {
				data[i] = sequence[i - 1]; // on remplit le tableau avec la séquence correspondant au highscore
		}
		result = i2c_eeprom_write(0x00, data, highScore+1); // on prend comme convention d'écrire et de lire à l'adresse 0x0
		assert(result == SUCCESS); // vérification que l'écriture a fonctionné
}

void read_highscore() { // lecture en mémoire du highscore et de la séquence correspondante
		int i;
		Status result = ERROR;
		uint8_t tmp[MAX_SEQUENCE_SIZE];
	
		result = i2c_eeprom_read(0x00, tmp, MAX_SEQUENCE_SIZE); // lecture en mémoire à l'addresse 0x0 et stockage des données dans le tableau tmp
		assert(result == SUCCESS);
		highScore=tmp[0]; // on récupère le highscore
		for(i=0; i<highScore; i++) {
				sequence[i] = tmp[i + 1]; // on écrase le tableau séquence avec la séquence correspondant à l'highscore
		}
		
		sequenceSize = highScore;
}

void pin_Configuration() {
		PINSEL_CFG_Type maconfig;
	
		// configuration pinsel speaker
		LPC_GPIO1->FIOMASK &= ~(1<<9); 
		maconfig.Portnum = PINSEL_PORT_1;
		maconfig.Pinnum = PINSEL_PIN_9;
		maconfig.Funcnum = PINSEL_FUNC_0;
		maconfig.Pinmode = PINSEL_PINMODE_PULLDOWN;
		maconfig.OpenDrain = PINSEL_PINMODE_NORMAL;
    // application de la configuration
    PINSEL_ConfigPin(&maconfig);
	
		// Memory part
		LPC_GPIO0->FIOMASK &= ~(1<<27); 
		maconfig.Portnum = PINSEL_PORT_0;
		maconfig.Pinnum = PINSEL_PIN_27;
		maconfig.Funcnum = PINSEL_FUNC_1; // SDA0
		maconfig.Pinmode = PINSEL_PINMODE_PULLUP;
		maconfig.OpenDrain = PINSEL_PINMODE_NORMAL;
		PINSEL_ConfigPin(&maconfig);
		
		LPC_GPIO0->FIOMASK &= ~(1<<28);
		maconfig.Portnum = PINSEL_PORT_0;
		maconfig.Pinnum = PINSEL_PIN_28;
		maconfig.Funcnum = PINSEL_FUNC_1; // SCL0
		maconfig.Pinmode = PINSEL_PINMODE_PULLDOWN;
		maconfig.OpenDrain = PINSEL_PINMODE_NORMAL;
		PINSEL_ConfigPin(&maconfig);
		
		// LED
		LPC_GPIO0->FIOMASK &= ~(1<<3); 
		maconfig.Portnum = PINSEL_PORT_0;
		maconfig.Pinnum = PINSEL_PIN_3;
		maconfig.Funcnum = PINSEL_FUNC_0;
		maconfig.Pinmode = PINSEL_PINMODE_PULLDOWN;
		maconfig.OpenDrain = PINSEL_PINMODE_NORMAL;
		PINSEL_ConfigPin(&maconfig);
	
		GPIO_SetDir(1,(1<<9),1); // Speaker ouput on P1.9
		GPIO_SetDir(0,(1<<3),1); // LED output on P0.3
}

void Init() {
		pin_Configuration();
		init_i2c_eeprom(LPC_I2C0);
		T0_Init();
		T1_Init();
}

void clearInterface() {
		dessiner_rect(0,0,250,330,2,1,Blue,Blue);
}

void touchTask() {		
		touch_read();
		couleur_touchee();
		if(currentKey == aucun) {
				return;
		}
	
		playNote();
	
		if(currentKey == sequence[sequencePosition]) {
				sequencePosition ++;
				playerWaitTimer = 0;
			
				if(sequencePosition >= sequenceSize) {
						appState = addNote;
				}
		}
		else {
				appState = endGame;
		}
}

void addTouche() {
		if(sequenceSize == MAX_SEQUENCE_SIZE) {
				flagSequenceOverflow = true;
				appState = endGame;
				return;
		}
		
		switch(rand()%4) {
				case 0:
						sequence[sequenceSize] = rouge;
						break;
				case 1:
						sequence[sequenceSize] = jaune;
						break;
			  case 2:
						sequence[sequenceSize] = vert;
						break;
				case 3:
						sequence[sequenceSize] = bleu;
						break;
		}
		sequenceSize ++;
}

void clearHighlight(int seqPos) {
		switch(sequence[seqPos]){
				case jaune:
						dessiner_rect(10,60,110,110,2,1,Black,Yellow);
						break;
				case vert:
						dessiner_rect(120,60,110,110,2,1,Black,Green);
						break;
				case bleu:
						dessiner_rect(10,170,110,110,2,1,Black,Cyan);
						break;
				case rouge:
						dessiner_rect(120,170,110,110,2,1,Black,Red);
						break;
				default:
						break;
		}
}

void highlightCurrent() {		
		switch(sequence[sequencePosition]){
				case jaune:
						dessiner_rect(10,60,110,110,2,1,White,Yellow);
						break;
				case vert:
						dessiner_rect(120,60,110,110,2,1,White,Green);
						break;
				case bleu:
						dessiner_rect(10,170,110,110,2,1,White,Cyan);
						break;
				case rouge:
						dessiner_rect(120,170,110,110,2,1,White,Red);
						break;
				default:
						break;
		}
}

void addNoteTask() {
		addTouche();
		
		sequencePosition = 0;		
}

void readSequence() {
		if(sequencePosition >= sequenceSize) {
				// end of sequence
				clearHighlight(sequencePosition - 1);
				if(appState == playSequence) {
						appState = playerTurn;
						playerWaitTimer = 0;
				}
				else {
						appState = menuState;
				}
				sequencePosition = 0;
				flagTouch = false;
				return;
		}
		
		currentKey = sequence[sequencePosition];
		
		if(sequencePosition > 0) {
				clearHighlight(sequencePosition - 1);
		}
		
		highlightCurrent();
		playNote();
		
		sequencePosition ++;
}


void drawSquares() {
		dessiner_rect(10,60,110,110,2,1,Black,Yellow);
		dessiner_rect(120,60,110,110,2,1,Black,Green);
		dessiner_rect(10,170,110,110,2,1,Black,Cyan);
		dessiner_rect(120,170,110,110,2,1,Black,Red);
}

void interfaceSimon() {
		int n;
	
		clearInterface();
		// affichage de l'écran maitre
		n=sprintf(chaine,"Rejouez la sequence");
		LCD_write_english_string (20,10,chaine,White,Blue);
		
		drawSquares();
}

//interface affichée lorsque l'on veut avoir accès au highScore
void interfaceHighScore(){
	int n;
	int m;
	
	read_highscore();
	
	clearInterface();
	n=sprintf(chaine,"Voici le highscore");
	LCD_write_english_string (20,10,chaine,White,Blue);
	m=sprintf(chaine, "%d", highScore);
	LCD_write_english_string (20,30,chaine,White,Blue);
	
	drawSquares();
	
	sequencePosition = 0;
	noteSpacingTimer = 0;
}


//fonction début de partie
void startGame() {
		sequenceSize = 0;
		interfaceSimon();
		addTouche();
}

//première interface lancée quand on allume l'application
void interfaceMenu(){
	int n;
	int m;
	
	clearInterface();
	//boutton pour commencer une nouvelle partie
	dessiner_rect(10,60,220,110,2,1,Black,Yellow);
	n=sprintf(chaine,"Commencer une partie");
	LCD_write_english_string(25,80,chaine,Black,Yellow);
	//boutton pour entrevoir le high score
	dessiner_rect(10,170,220,110,2,1,Black,Green);
	m=sprintf(chaine,"Voir le highscore");
	LCD_write_english_string(25,190,chaine,Black,Green);
}

void processMenu() {
	touch_read();
	if(touch_x> 600 && touch_x < 3600 && touch_y > 2000 && touch_y< 3000){
		srand(touch_x + touch_y);
		appState = newGame;
	}
	else if(touch_x> 600 && touch_x <3600 && touch_y > 700 && touch_y< 1800){
		appState = highScoreState;
	}
}

//fonction fin de partie, en fonction de la correction de la séquence jouée, soit on retourne en début de partie, soit on retourne à la partie génération de note
void finDePartie() {
		int n;
		if(currentKey != sequence[sequencePosition]) {
				n = sprintf(chaine,"Tu t'es trompe de touche !");
				LCD_write_english_string(20,10,chaine,White,Blue);
				if(sequenceSize - 1 > highScore){
						highScore = sequenceSize - 1;
						write_highscore();
				}
		}
		else {
				n = sprintf(chaine,"Tu es trop fort !");
				LCD_write_english_string(20,10,chaine,White,Blue);
				highScore = MAX_SEQUENCE_SIZE;
				write_highscore();
		}
}

//===========================================================//
// Function: Main
//===========================================================//
int main(void)
{
	  uint16_t touch_x_tmp = 0;
		uint16_t touch_y_tmp = 0;
	  char coordonnees[20]; //tableau receuillant les coordonnées x et y du point touché sur l'écran tactile
		int k;
	
	  Init(); // init variable globales et pinsel son et IR
	  lcd_Initializtion(); // init pinsel ecran et init LCD
		
	  touch_init(); // init pinsel tactile et init tactile 
	
		read_highscore();
	
    while(1) {
				switch(appState) {
					case menuState:
						interfaceMenu();
						appState = menuWaitState;
						break;
					
					case menuWaitState:
						if(flagTouch) {
							processMenu();
							noteSpacingTimer = 0;
							flagTouch = false;
						}
						break;
					
					case highScoreState:
						interfaceHighScore();
						appState = highScoreSequenceState;
						break;
					
					case newGame:
						startGame();
						appState = playSequence;
						break;
					
					case highScoreSequenceState:
					case playSequence:
						if(noteDuration == -1 && noteSpacingTimer >= MILI_2_TICKS(NOTE_SPACING_TIME, 50)) {
							readSequence(); // Switch state when done
						}
						break;
						
					case playerTurn:
						if(flagTouch && noteDuration == -1) {
							if(noteSpacingTimer > MILI_2_TICKS(PLAYER_SKIP, 50)) {
									touchTask(); // Switch state depending of player action
							}
							flagTouch = false; 
						}
						
						// Player timeout
						if(playerWaitTimer >= MILI_2_TICKS(MAX_PLAYER_WAIT, 50)) {
							appState = endGame;
						}
						break;
						
					case addNote:
						addNoteTask();
						appState = playSequence;
						break;
						
					case endGame:
						finDePartie();
						appState = waitEndGame;
						noteSpacingTimer = 0;
						break;
					
					case waitEndGame:
						if(noteSpacingTimer > MILI_2_TICKS(MENU_WAIT*2, 50)) {
							appState = menuState;
							noteSpacingTimer = 0;
						}
						break;
				}
		}
}

//---------------------------------------------------------------------------------------------	
#ifdef  DEBUG
void check_failed(uint8_t *file, uint32_t line) {while(1);}
#endif
