#pragma once
#include "esp_err.h"

esp_err_t spi_service_slave_prepare_transaction(uint8_t *tx_data, uint8_t *rx_data, size_t len);