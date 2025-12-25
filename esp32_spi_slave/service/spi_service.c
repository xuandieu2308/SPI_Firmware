#include "spi_service.h"
#include "spi_slave_driver.h"

esp_err_t spi_service_slave_prepare_transaction(uint8_t *tx_data, uint8_t *rx_data, size_t len) {
    return spi_slave_prepare_transaction(tx_data, rx_data, len);
}