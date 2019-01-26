#include "timer0.h"


void T0_Init(void)
{
	TIM_TIMERCFG_Type		Timer_Config_Structure;
	TIM_MATCHCFG_Type		Timer_MatchConfig_Structure;

	// valeur du PC est donnée en micro secondes
	Timer_Config_Structure.PrescaleOption = TIM_PRESCALE_USVAL;					
	// valeur du PC en micro seconds
	Timer_Config_Structure.PrescaleValue	= 1;							

	// applique la configuration
	TIM_Init(LPC_TIM0, TIM_TIMER_MODE,&Timer_Config_Structure);


	// match channel configuré
	Timer_MatchConfig_Structure.MatchChannel = 0;		
		// génère interruption	
	Timer_MatchConfig_Structure.IntOnMatch   = TRUE;
	// reset on match
	Timer_MatchConfig_Structure.ResetOnMatch = TRUE;
	// n'arrête pas le timer on match
	Timer_MatchConfig_Structure.StopOnMatch  = FALSE;											
	// pas besoin de toggle MAT0.0
	Timer_MatchConfig_Structure.ExtMatchOutputType = TIM_EXTMATCH_NOTHING;

	// On match toutes les 50 us
	Timer_MatchConfig_Structure.MatchValue = 50;	
	// applique la configuration
	TIM_ConfigMatch(LPC_TIM0,&Timer_MatchConfig_Structure);

	// active les interupts pour TIMER0
	NVIC_EnableIRQ(TIMER0_IRQn);

	// lance TIMER0
	TIM_Cmd(LPC_TIM0,ENABLE);
}

void playNote() {
		if(noteDuration == -1) {
				noteDuration = 0;
		}
}

void toggleAudio() {
	if((LPC_GPIO1->FIOPIN & (1<<9)) == (1<<9)) {
		LPC_GPIO1->FIOCLR=(1<<9);
	}
	else {
		LPC_GPIO1->FIOSET=(1<<9);
	}
}

void TIMER0_IRQHandler() {
	// Other timers
	playerWaitTimer ++;
	noteSpacingTimer ++;
	
	if(noteDuration != -1) {
		// Note did not end
		noteDuration ++;
		
		if(noteDuration >= MILI_2_TICKS(NOTE_DURATION, 50)) {
			noteDuration = -1;
			noteSpacingTimer = 0;
			currentKey = aucun;
			return;
		}
		else {
			int freq;
			
			switch(currentKey) {
				case vert:
					freq = FREQ_GREEN;
					break;
				case bleu:
					freq = FREQ_BLUE;
					break;
				case rouge:
					freq = FREQ_RED;
					break;
				case jaune:
					freq = FREQ_YELLOW;
					break;
				default:
					noteDuration = -1;
					noteSpacingTimer = 0;
					TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);
					return;
					break;
			}
			
			soundTimer ++;
			
			if(soundTimer >= MICRO_2_TICKS(freq, 50)/2) {
					soundTimer = 0;
					
					toggleAudio();
			}
		}
	}
	
	// clear interrupt sur Timer0 mr0
	TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);
}
