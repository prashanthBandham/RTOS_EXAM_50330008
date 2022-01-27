#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

TaskHandle_t t1_handle;
TaskHandle_t t2_handle;
TaskHandle_t t3_handle;
TaskHandle_t t4_handle;
TaskHandle_t t5_handle;
QueueHandle_t msg;

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
    while(1)
    {
        printf("\nIn Task 3");
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}
void task4(void *data)
{
    int count=0;
    while(1)
    {
        printf("\ncounter incremented in Task4");
        count++;
        xQueueSend(msg,&count,0);
        printf("\nmessage sent to Task 5");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
void task5(void *data)
{
    int buff;
    while(1)
    {
        printf("\nIn Task 5");
        xQueueReceive(msg,&buff,0);
        printf("\ndata received from Task4: %d",buff);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    msg=xQueueCreate(5,sizeof(int));

    xTaskCreate(task1, "task_t1", 2048, NULL, 5, &t1_handle);
    xTaskCreate(task2, "task_t1", 2048, NULL, 6, &t2_handle);
    xTaskCreate(task3, "task_t1", 2048, NULL, 7, &t3_handle);
    xTaskCreate(task4, "task_t1", 2048, NULL, 8, &t4_handle);
    xTaskCreate(task5, "task_t1", 2048, NULL, 9, &t5_handle);
}
