#pragma once
#include "driver/spi_master.h"
#include "esp_err.h"

esp_err_t spi_master_init(void);
esp_err_t spi_master_transfer(const uint8_t *tx_data, uint8_t *rx_data, size_t len);