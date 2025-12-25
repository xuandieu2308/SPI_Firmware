    /**
 * @file spi_slave_driver.c
 * @brief SPI slave hardware driver implementation for ESP32.
 *
 * Follows CMU C Coding Standard: clear naming, comments, formatting, no magic numbers, etc.
 */

#include "spi_slave_driver.h"   /* SPI slave driver interface */
#include <string.h>              /* For memcpy, memset */
#include <stddef.h>              /* For size_t */
#include <stdint.h>              /* For uint8_t */

/* SPI pin assignments for ESP32 hardware */
#define PIN_NUM_MISO    19  /* Master In Slave Out */
#define PIN_NUM_MOSI    23  /* Master Out Slave In */
#define PIN_NUM_CLK     18  /* SPI Clock */
#define PIN_NUM_CS      5   /* Chip Select */

/* Receive buffer for SPI transactions (DMA aligned) */
static WORD_ALIGNED_ATTR uint8_t recvbuf[128];

/**
 * @brief Initialize the SPI slave hardware interface.
 *
 * @return ESP_OK on success, error code otherwise.
 */
esp_err_t spi_slave_init(void)
{
    spi_bus_config_t bus_cfg = {
        .mosi_io_num = PIN_NUM_MOSI,
        .miso_io_num = PIN_NUM_MISO,
        .sclk_io_num = PIN_NUM_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1
    };
    spi_slave_interface_config_t slv_cfg = {
        .mode = 0,
        .spics_io_num = PIN_NUM_CS,
        .queue_size = 1,
    };
    return spi_slave_initialize(HSPI_HOST, &bus_cfg, &slv_cfg, SPI_DMA_CH_AUTO);
}

/*
 * @brief Prepare and execute a full-duplex SPI transaction (slave mode).
 *
 * @param[in]  tx_data Pointer to data to send to master.
 * @param[out] rx_data Pointer to buffer to store data received from master.
 * @param[in]  len     Number of bytes to send/receive.
 * @return ESP_OK on success, error code otherwise.
 */
esp_err_t spi_slave_prepare_transaction(uint8_t *tx_data, uint8_t *rx_data, size_t len)
{
    spi_slave_transaction_t t = {
        .length = len * 8,
        .tx_buffer = tx_data,
        .rx_buffer = recvbuf
    };
    esp_err_t ret = spi_slave_transmit(HSPI_HOST, &t, portMAX_DELAY);
    if (ret == ESP_OK) {
        memcpy(rx_data, recvbuf, len);
    }
    return ret;
}