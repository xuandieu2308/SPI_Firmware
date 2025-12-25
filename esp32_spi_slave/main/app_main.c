#include "spi_service.h"
#include "spi_slave_driver.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#define SPI_BUF_SIZE 64

void spi_slave_receive_task(void *pv) {
    static uint32_t tx_count = 0;
    uint8_t tx_buf[SPI_BUF_SIZE];
    uint8_t rx_buf[SPI_BUF_SIZE];
    ESP_LOGI("SLAVE_RECV", "[START] spi_slave_receive_task running");
    while (1) {
        // Chuẩn bị dữ liệu trả lời ngay khi master truyền
       memset(tx_buf, 0, SPI_BUF_SIZE);  // clear toàn bộ buffer
       memcpy(tx_buf, &tx_count, sizeof(tx_count));
       snprintf((char*)(tx_buf + sizeof(tx_count)), 60, "Hello Master!"); 
        memset(rx_buf, 0, SPI_BUF_SIZE);
        esp_err_t ret = spi_service_slave_prepare_transaction(tx_buf, rx_buf, SPI_BUF_SIZE);
        if (ret == ESP_OK) {
            uint32_t rx_count = 0;
            memcpy(&rx_count, rx_buf, sizeof(rx_count));
            char msg[61];
           strncpy(msg, (char*)(rx_buf + sizeof(rx_count)), 60);
           msg[60] = '\0';
            int valid = 0;
            for (int i = 0; i < 60; ++i) if (msg[i] != 0) valid = 1;
            if (valid) {
                ESP_LOGI("SLAVE_RECV", "Received from master: count=%lu, msg=%s", rx_count, msg);
                ESP_LOGI("SLAVE_SEND", "Sent to master: count=%lu, msg=Hello Master!", tx_count);
                tx_count++;
            }
        } else {
            ESP_LOGE("SLAVE_RECV", "SPI transfer failed: %d", ret);
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void app_main(void) {
    spi_slave_init();
    xTaskCreate(spi_slave_receive_task, "spi_slave_recv", 4096, NULL, 6, NULL);
}
