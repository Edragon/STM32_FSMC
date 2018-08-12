#ifndef _SYSTIC_H
#define _SYSTIC_H 1

/* Private functions ---------------------------------------------------------*/
void SysTick_IntConfig(void);
void Delay_ms(__IO uint32_t nTime);
void TimingDelay_Decrement(void);

#endif
