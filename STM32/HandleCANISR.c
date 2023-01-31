#include "stm32f4xx_hal.h"

CAN_HandleTypeDef hcan;
CAN_RxHeaderTypeDef rxHeader;

void CAN_RX_IRQHandler(void)
{
  /* Check if a message has been received */
  if (__HAL_CAN_GET_FLAG(&hcan, CAN_FLAG_FMP0))
  {
    /* Clear the interrupt flag */
    __HAL_CAN_CLEAR_FLAG(&hcan, CAN_FLAG_FMP0);

    /* Read the received data from the message object */
    uint8_t data[8];
    HAL_CAN_GetRxMessage(&hcan, CAN_RX_FIFO0, &rxHeader, data);

    /* Process the received data */
    // ...
  }
}

int main(void)
{
  /* Initialize the HAL library */
  HAL_Init();

  /* Configure the CAN peripheral */
  hcan.Instance = CAN1;
  hcan.Init.Prescaler = 16;
  hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.SJW = CAN_SJW_1TQ;
  hcan.Init.BS1 = CAN_BS1_1TQ;
  hcan.Init.BS2 = CAN_BS2_1TQ;
  hcan.Init.TTCM = DISABLE;
  hcan.Init.ABOM = DISABLE;
  hcan.Init.AWUM = DISABLE;
  hcan.Init.NART = DISABLE;
  hcan.Init.RFLM = DISABLE;
  hcan.Init.TXFP = DISABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    /* Initialization error */
    // ...
  }

  /* Enable the CAN receive interrupt */
  HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);

  /* Transmit a message */
  CAN_TxHeaderTypeDef txHeader;
  txHeader.StdId = 0x123;
  txHeader.RTR = CAN_RTR_DATA;
  txHeader.IDE = CAN_ID_STD;
  txHeader.DLC = 8;
  txHeader.TransmitGlobalTime = DISABLE;
  uint8_t txData[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
  if (HAL_CAN_AddTxMessage(&hcan, &txHeader, txData, &TxMailbox) != HAL_OK)
  {
    /* Transmission error */
    // ...
  }

  /* Infinite loop */
  while (1)
  {
    /* Do other tasks */
    // ...
  }
}
