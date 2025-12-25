#include "spi_service.h"
#include "spi_master_driver.h"

esp_err_t spi_service_master_transfer(uint8_t *tx_data, uint8_t *rx_data, size_t len) {
    return spi_master_transfer(tx_data, rx_data, len);
}