#include "py/nlr.h"
#include "py/obj.h"
#include "py/runtime.h"
#include "py/binary.h"
#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"

#define ECHO_TEST_TXD  (23)
#define ECHO_TEST_RXD  (19)
#define ECHO_TEST_RTS  (5)
#define ECHO_TEST_CTS  (18)

#define BUF_SIZE (128)

static void echo_task()
{
    printf("starting echo in\n");
        /* Configure parameters of an UART driver,
     * communication pins and install the driver */
    uart_config_t uart_config = {
        .baud_rate = 4000000,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_CTS_RTS
    };
    uart_param_config(UART_NUM_1, &uart_config);
    uart_set_pin(UART_NUM_1, ECHO_TEST_TXD, ECHO_TEST_RXD, ECHO_TEST_RTS, ECHO_TEST_CTS);
    uart_driver_install(UART_NUM_1, BUF_SIZE * 2, 0, 0, NULL, 0);

    // Configure a temporary buffer for the incoming data
    uint8_t *data = (uint8_t *) malloc(BUF_SIZE*2);
    //vTaskDelay(30000 / portTICK_RATE_MS);
    while (1) {
        //printf("in dealy\n");
        
        //printf("done dealy\n");
        // Read data from the UART
        int len = uart_read_bytes(UART_NUM_1, data, 20, 2 / portTICK_RATE_MS);
        //printf("%d", len);// Write data back to the UART
        if(len > 0)
        {
            int x = uart_write_bytes(UART_NUM_1, (const char *) data, len);
           // printf("%d,\n", x);
        }


    }
}

STATIC mp_obj_t loop()
{
            /* Configure parameters of an UART driver,
     * communication pins and install the driver */
    xTaskCreate(echo_task, "uart_echo_task", 2048, NULL, 10, NULL);
    //printf("hello\n");
    //vTaskDelay(20 / portTICK_RATE_MS);
    //printf("works\n");
    //int a = 2;
    //int b = 3;
    //while(true);
    return mp_obj_new_int(6);
    return MP_OBJ_NULL;    
}

STATIC MP_DEFINE_CONST_FUN_OBJ_0(loop_obj, loop);

STATIC const mp_rom_map_elem_t loop_globals_table[] = {
    {MP_ROM_QSTR(MP_QSTR___name__), MP_OBJ_NEW_QSTR(MP_QSTR_loopback)},
    {MP_OBJ_NEW_QSTR(MP_QSTR_echo2), MP_ROM_PTR(&loop_obj)}
};
STATIC MP_DEFINE_CONST_DICT(loop_globals, loop_globals_table);

const mp_obj_module_t mp_module_loopback_uart = {
    .base = {&mp_type_module},
    .globals = (mp_obj_dict_t *)&loop_globals,
};