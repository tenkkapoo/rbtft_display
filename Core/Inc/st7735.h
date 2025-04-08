#ifndef st7735
#define st7735

void reset_display(void);
void send_command(SPI_HandleTypeDef *hspi, uint8_t cmd);
void send_data(SPI_HandleTypeDef *hspi, uint8_t data);
void init_display(SPI_HandleTypeDef *hspi);

#endif