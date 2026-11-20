/* app.c */

/* includes */
#include "app.h"
#include "main.h"
#include "usart.h"
#include <string.h>

/* defines */
#define LED_BLINK_MS    500 /* time between LED toggles, in ms */
#define UART_TIMEOUT_MS 100 /* max time to wait for the UART */

void app_init(void)
{
	const char *msg = "LCR meter starting\r\n";
	HAL_UART_Transmit(&huart2, (const uint8_t *)msg, strlen(msg), UART_TIMEOUT_MS); 
}

void app_run(void)
{
	HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
	HAL_Delay(LED_BLINK_MS);
}
