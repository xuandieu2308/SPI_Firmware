#include "spi_master_driver.h"

/* Pin definitions for SPI master */
#define PIN_NUM_MISO   19
#define PIN_NUM_MOSI   23
#define PIN_NUM_CLK    18
#define PIN_NUM_CS     5

/* SPI device handle (global for this driver) */
static spi_device_handle_t spi_handle;

/*
 * Function: spi_master_init
 * -------------------------
 * Initialize the SPI master bus and add the SPI device.
 *
 * returns: ESP_OK on success, or an esp_err_t code on failure.
 */
esp_err_t spi_master_init(void)
{
    spi_bus_config_t bus_config = {
        .miso_io_num     = PIN_NUM_MISO,
        .mosi_io_num     = PIN_NUM_MOSI,
        .sclk_io_num     = PIN_NUM_CLK,
        .quadwp_io_num   = -1,
        .quadhd_io_num   = -1
    };

    spi_bus_initialize(HSPI_HOST, &bus_config, SPI_DMA_CH_AUTO);

    spi_device_interface_config_t dev_config = {
        .clock_speed_hz = 1 * 1000 * 1000,  /* 1 MHz clock */
        .mode           = 0,                /* SPI mode 0 */
        .spics_io_num   = PIN_NUM_CS,
        .queue_size     = 1
    };

    return spi_bus_add_device(HSPI_HOST, &dev_config, &spi_handle);
}
/*
 * Function: spi_master_transfer
 * -----------------------------
 * Perform a full-duplex SPI transfer (simultaneous send/receive).
 *
 * tx_data: pointer to the buffer containing data to transmit.
 * rx_data: pointer to the buffer where received data will be stored.
 * len:     number of bytes to transfer.
 *
 * returns: ESP_OK on success, or an esp_err_t code on failure.
 */
esp_err_t spi_master_transfer(const uint8_t *tx_data,
                              uint8_t *rx_data,
                              size_t len)
{
    spi_transaction_t transaction = {
        .length    = len * 8,
        .tx_buffer = tx_data,
        .rx_buffer = rx_data
    };

    return spi_device_transmit(spi_handle, &transaction);
}