#include "timer1.h"

void T1_Init(void)
{
	TIM_TIMERCFG_Type		Timer_Config_Structure;
	TIM_MATCHCFG_Type		Timer_MatchConfig_Structure;

	// valeur du PC est donnée en micro secondes
	Timer_Config_Structure.PrescaleOption = TIM_PRESCALE_USVAL;					
	// valeur du PC en micro seconds
	Timer_Config_Structure.PrescaleValue	= 1;							

	// applique la configuration
	TIM_Init(LPC_TIM1, TIM_TIMER_MODE,&Timer_Config_Structure);


	// match channel configuré
	Timer_MatchConfig_Structure.MatchChannel = 0;		
		// génère interruption	
	Timer_MatchConfig_Structure.IntOnMatch   = TRUE;
	// reset on match
	Timer_MatchConfig_Structure.ResetOnMatch = TRUE;
	// n'arrête pas le timer on match
	Timer_MatchConfig_Structure.StopOnMatch  = FALSE;
	Timer_MatchConfig_Structure.ExtMatchOutputType = TIM_EXTMATCH_NOTHING;

	// On match toutes les 20 us
	Timer_MatchConfig_Structure.MatchValue = 20;	
	// applique la configuration
	TIM_ConfigMatch(LPC_TIM1,&Timer_MatchConfig_Structure);

	// active les interupts pour TIMER1
	NVIC_EnableIRQ(TIMER1_IRQn);

	// lance TIMER1
	TIM_Cmd(LPC_TIM1,ENABLE);
}

void TIMER1_IRQHandler() { // faux? (previousPressend permet au joueur d'appuyer plus longtemps sur la touche, sans qu'on considère qu'il a appuyé dessus plusieurs fois.

	if(((LPC_GPIO0->FIOPIN)&(1<<19))==0) {
			flagTouch = true; // réveil de la tache clavier 
			GPIO_IntCmd(0,(1<<19),0); 
	}
	else {
			GPIO_IntCmd(0,(1<<19),1);
  }
	
	TIM_ClearIntPending(LPC_TIM1, TIM_MR0_INT);
}
