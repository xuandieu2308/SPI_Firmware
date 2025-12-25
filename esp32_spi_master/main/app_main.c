#include "spi_service.h"
#include "spi_master_driver.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"

#define SPI_BUF_SIZE 64

void spi_master_task(void *pv) {
    uint32_t tx_count = 0;
    char msg[] = "Hello Slave!";
    uint8_t tx_buf[SPI_BUF_SIZE];
    uint8_t rx_buf[SPI_BUF_SIZE];

    while (1) {
        memset(tx_buf, 0, SPI_BUF_SIZE);// xoá toàn bộ buffer gửi
        memcpy(tx_buf, &tx_count, sizeof(tx_count));
        strncpy((char*)(tx_buf + sizeof(tx_count)), msg, 60);

        ESP_LOGI("MASTER_SEND", "Send: count=%lu, msg=%s", tx_count, msg);

        memset(rx_buf, 0, SPI_BUF_SIZE);// xoá toàn bộ buffer nhận
        esp_err_t ret = spi_service_master_transfer(tx_buf, rx_buf, SPI_BUF_SIZE);

        if (ret == ESP_OK) {
            static uint32_t rx_count = 0;
            memcpy(&rx_count, rx_buf, sizeof(rx_count));// lấy số đếm từ buffer nhận

            char slave_msg[61];
            strncpy(slave_msg, (char*)(rx_buf + sizeof(rx_count)), 60);
            slave_msg[60] = '\0';

            if (slave_msg[0] != '\0') {
                ESP_LOGI("MASTER_RECEIVE", "Received from slave: count=%lu, msg=%s", rx_count, slave_msg);
            }
        } else {
            ESP_LOGE("MASTER_RECEIVE", "SPI transfer failed: %d", ret);
        }

        tx_count++;
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}


void app_main(void) {
    spi_master_init();
    xTaskCreate(spi_master_task, "spi_master", 4096, NULL, 5, NULL);
}