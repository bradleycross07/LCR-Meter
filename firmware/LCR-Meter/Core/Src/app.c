/* app.c */

/* includes */
#include "app.h"
#include "main.h"
#include "debug.h"

/* defines */
#define LED_BLINK_MS    500 /* time between LED toggles, in ms */

void app_init(void)
{
	debug_print("LCR meter starting\r\n");
}

void app_run(void)
{
	HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
	HAL_Delay(LED_BLINK_MS);
}
