#pragma once
#include "esp_err.h"

esp_err_t spi_service_master_send(uint8_t *data, size_t len);
esp_err_t spi_service_master_transfer(uint8_t *tx_data, uint8_t *rx_data, size_t len);