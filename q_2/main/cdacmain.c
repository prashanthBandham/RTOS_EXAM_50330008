#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/timers.h"

TaskHandle_t t1_handle;
TaskHandle_t t2_handle;
TaskHandle_t t3_handle;
TimerHandle_t timer_handle;

void *const timer_id;
void call_back(TimerHandle_t xTimer);
void task1(void *data)
{
    while(1)
    {
        printf("\nIn Task 1");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
void task2(void *data)
{
    while(1)
    {
        printf("\nIn Task 2");
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}
void task3(void *data)
{
    timer_handle = xTimerCreate("timer",(10000 / portTICK_PERIOD_MS),pdFALSE,timer_id,call_back);
    xTimerStart(timer_handle, 1);
    while (1)
    {
        printf("\nIn Task 3");
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}
void call_back(TimerHandle_t xTimer)
{
    printf("\nIn Callback Function");
}

void app_main(void)
{
    xTaskCreate(task1, "task_t1", 2048, NULL, 7, &t1_handle);
    xTaskCreate(task2, "task_t1", 2048, NULL, 6, &t2_handle);
    xTaskCreate(task3, "task_t1", 2048, NULL, 5, &t3_handle);
}
