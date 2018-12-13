/*
 * Copyright (C) 2015-2017 Alibaba Group Holding Limited
 */

#include <aos/aos.h>
#include <hal/hal.h>

#define UART_DATA_BYTES 14

uart_dev_t opt_uart;
char readbuf[UART_DATA_BYTES] = {0};

static void init_uart(void) 
{
    opt_uart.port = 2;
    opt_uart.config.baud_rate = 115200;
    opt_uart.config.data_width = DATA_WIDTH_8BIT;
    opt_uart.config.flow_control = FLOW_CONTROL_DISABLED;
    opt_uart.config.mode = MODE_TX_RX;
    opt_uart.config.parity = NO_PARITY;
    opt_uart.config.stop_bits = STOP_BITS_1;

    hal_uart_init(&opt_uart);
}

static void app_delayed_action(void *arg)
{
    uint32_t recBytes = 0;
    int ret = -1;

    LOG("Uart opertion demo %s:%d %s\r\n", __func__, __LINE__, aos_task_name());

    init_uart();
    
    LOG("Uart init finished %s:%d %s\r\n", __func__, __LINE__, aos_task_name());

    /* receive a message and sent out through the uart */
    ret = hal_uart_recv_II(&opt_uart, readbuf, UART_DATA_BYTES, &recBytes, 10);

    LOG("Uart receive finished %s:%d %s\r\n", __func__, __LINE__, aos_task_name());

    if((ret == 0) && (recBytes > 0))
    {
        LOG("Read something %s:%d %s\r\n", __func__, __LINE__, aos_task_name());
        hal_uart_send(&opt_uart, readbuf, recBytes, 10);
    } else {
        LOG("Read none %s:%d %s\r\n", __func__, __LINE__, aos_task_name());
    }

    aos_post_delayed_action(500, app_delayed_action, NULL);
}

int application_start(int argc, char *argv[])
{
    LOG("application started.");
    aos_post_delayed_action(1000, app_delayed_action, NULL);
    aos_loop_run();

    return 0;
}

