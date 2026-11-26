/* lcd.h */
#ifndef LCD_H
#define LCD_H

#include <stdint.h>

/* sets up the LCD: 4-bit mode, 2 lines, display on, cursor off, cleared. call once at start-up */
void lcd_init(void);

/* clears the LCD display */
void lcd_clear(void);

/* moves the cursor: col is 0–15, row is 0–1 */
void lcd_goto(uint8_t col, uint8_t row);

/* writes one character at the cursor */
void lcd_write_char(char c);

/* writes a string at the cursor */
void lcd_write_string(const char *s);

#endif
