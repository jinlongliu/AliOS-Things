/*
 * Copyright (C) 2015-2017 Alibaba Group Holding Limited
 */

#include <aos/aos.h>
#include "soc_init.h"

#define FIRST_LED      GPIO_ALS_LED
#define SG90_PWM_TEST  GPIO_SG90_PWM

static void app_delayed_action(void *arg)
{
    LOG("helloworld %s:%d %s\r\n", __func__, __LINE__, aos_task_name());
    hal_gpio_output_low(&brd_gpio_table[FIRST_LED]);
    hal_gpio_output_high(&brd_gpio_table[SG90_PWM_TEST]);
    aos_msleep(3000);
    hal_gpio_output_high(&brd_gpio_table[FIRST_LED]);
    hal_gpio_output_low(&brd_gpio_table[SG90_PWM_TEST]);
    aos_post_delayed_action(5000, app_delayed_action, NULL);
}

int application_start(int argc, char *argv[])
{
    LOG("application started.");
    aos_post_delayed_action(1000, app_delayed_action, NULL);
    aos_loop_run();

    return 0;
}

