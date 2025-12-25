#ifndef SPI_SLAVE_DRIVER_H
#define SPI_SLAVE_DRIVER_H

#include <stddef.h>
#include <stdint.h>
#include "esp_err.h"
#include "driver/spi_slave.h"

esp_err_t spi_slave_init(void);
esp_err_t spi_slave_prepare_transaction(uint8_t *tx_data, uint8_t *rx_data, size_t len);

#endif /* SPI_SLAVE_DRIVER_H */