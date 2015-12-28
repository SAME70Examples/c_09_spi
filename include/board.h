#ifndef _BOARD_H
#define _BOARD_H

#define LED_ON 1
#define LED_OFF 0

void led_init(void);

void led_setState(int led_state);

void button_init(void);

int button_isPressed(void);

#endif// _BOARD_H
