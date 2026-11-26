/* app.h */
#ifndef APP_H
#define APP_H

/* runs once at startup, after CubeMX has set up peripherals */
void app_init(void);

/* runs repeatedly from main loop */
void app_run(void);

#endif
