/* lcd.c */

/* HD44780 16x2 LCD driver, 4-bit mode, write-only.
   start-up sequence and command values follow D. Pearce's
   DAJP_G431KB_Drivers.c (MIT licence), rewritten for HAL. */

/* includes */
#include "lcd.h"
#include "main.h"

/* defines */
#define LCD_PULSE_MS 1 /* E high/low time; 1 ms is safe */
#define LCD_POWER_MS 50 /* wait after power-on before talking to the LCD */
#define LCD_WAKE_MS 5 /* wait between the wake-up nibbles */
#define LCD_CLEAR_MS 2 /* clear takes ~1.5 ms to finish */

#define LCD_CMD_CLEAR 0x01 /* clear display, cursor to top left */
#define LCD_CMD_ENTRY_MODE 0x06 /* cursor moves right after each character */
#define LCD_CMD_DISPLAY_ON 0x0C /* display on, cursor off, no blink */
#define LCD_CMD_FUNC_SET 0x28 /* 4-bit mode, 2 lines, 5x8 font */
#define LCD_CMD_SET_ADDR 0x80 /* set cursor position */

#define LCD_ROW1_ADDR 0x40 /* address of the first character on row 1 */

/* puts the low 4 bits of nibble onto D4-D7 */
static void lcd_write_nibble(uint8_t nibble)
{
	HAL_GPIO_WritePin(LCD_D4_GPIO_Port, LCD_D4_Pin, (nibble & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_D5_GPIO_Port, LCD_D5_Pin, (nibble & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_D6_GPIO_Port, LCD_D6_Pin, (nibble & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_D7_GPIO_Port, LCD_D7_Pin, (nibble & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

/* pulses E high then low, so the LCD reads what's on D4 to D7 */
static void lcd_pulse_enable(void)
{
	HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, GPIO_PIN_SET); /* E high */
	HAL_Delay(LCD_PULSE_MS); /* wait */
	HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, GPIO_PIN_RESET); /* E low: LCD reads the data */
	HAL_Delay(LCD_PULSE_MS); /* wait before the next pulse */
}

/* sends one byte as two nibbles, high half first. is_data = 1 for a character, 0 for a command */
static void lcd_write_byte(uint8_t byte, uint8_t is_data)
{
	HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, is_data ? GPIO_PIN_SET : GPIO_PIN_RESET); /* set RS from is_data */
	lcd_write_nibble(byte >> 4); /* high nibble on D4-D7; LCD reads it */
	lcd_pulse_enable();
	lcd_write_nibble(byte & 0x0F); /* low nibble on D4-D7; LCD reads it */
	lcd_pulse_enable();
}

/* initialise the lcd display */
void lcd_init(void)
{
	HAL_Delay(LCD_POWER_MS); /* let the LCD power up */
	HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_RESET); /* RS low: command */

	/* send 0x03, 3 times, waiting LCD_WAKE_MS after each pulse, forces 8-bit mode from any starting point */
	for (uint8_t i = 0; i < 3; i++) {
		lcd_write_nibble(0x03);
		lcd_pulse_enable();
		HAL_Delay(LCD_WAKE_MS);
	}

	/* send 0x02 once: switch to 4-bit mode */
	lcd_write_nibble(0x02);
	lcd_pulse_enable();
	HAL_Delay(LCD_WAKE_MS);

	lcd_write_byte(LCD_CMD_FUNC_SET, 0); /* 4-bit, 2 lines, 5x8 */
	lcd_write_byte(LCD_CMD_DISPLAY_ON, 0); /* display on, cursor off */
	lcd_write_byte(LCD_CMD_CLEAR, 0); /* clear the screen */
	HAL_Delay(LCD_CLEAR_MS); /* clear is slow so wait for it */
	lcd_write_byte(LCD_CMD_ENTRY_MODE, 0); /* cursor moves right after each character */
}

/* clears the screen and moves the cursor to the top left */
void lcd_clear(void)
{
	lcd_write_byte(LCD_CMD_CLEAR, 0); /* command */
	HAL_Delay(LCD_CLEAR_MS); /* clear is slow */
}

/* writes one character at the cursor */
void lcd_write_char(char c)
{
	lcd_write_byte((uint8_t)c, 1); /* 1 = data, RS = high */
}

/* writes a string at the cursor */
void lcd_write_string(const char *s)
{
	while(*s) { /* *s is the current character: \0 ends the loop */
		lcd_write_char(*s);
		s++; /* moves to the next character */
	}
}

/* moves the cursor: column 0 to 15, row 0 to 1 */
void lcd_goto(uint8_t col, uint8_t row)
{
	uint8_t addr = (row == 0) ? col : (LCD_ROW1_ADDR + col);
	lcd_write_byte(LCD_CMD_SET_ADDR | addr, 0);
}
