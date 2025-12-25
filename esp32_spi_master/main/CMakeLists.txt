idf_component_register(
    SRCS "app_main.c" "../hardware/spi_master_driver.c" "../service/spi_service.c"
    INCLUDE_DIRS "../service" "../hardware"
)