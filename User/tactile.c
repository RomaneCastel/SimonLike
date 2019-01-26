#include "tactile.h"

void recuperation_coordonnees(char * coordonnees) {
	int n;
	n=sprintf(coordonnees, "%d; %d", touch_x, touch_y); //on récupère dans un tableau de caractères (chaîne de caractère) les coordonées x et y de l'endroit appuyé sur l'écran.
}

void couleur_touchee(void) {
	if( touch_x> 600 && touch_x < 2000 && touch_y > 2000 && touch_y< 3000){
		currentKey = jaune;
	}
	else if( touch_x> 2100 && touch_x < 3600 && touch_y > 2000 && touch_y< 3000){
		currentKey = vert;
	}
	else if( touch_x> 600 && touch_x < 2000 && touch_y > 700 && touch_y< 1800){
		currentKey = bleu;
	}
	else if( touch_x> 2100 && touch_x < 3600 && touch_y > 700 && touch_y< 1800){
		currentKey = rouge;
	}
	else{
			currentKey = aucun;
	}
}
