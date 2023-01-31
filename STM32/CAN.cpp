#include "stm32f10x.h"
#include "stm32f10x_can.h"

#define CANx CAN1

CanRxMsg RxMessage;

void CAN_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  CAN_InitTypeDef CAN_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  CAN_DeInit(CANx);
  CAN_StructInit(&CAN_InitStructure);
  CAN_InitStructure.CAN_TTCM = DISABLE;
  CAN_InitStructure.CAN_ABOM = DISABLE;
  CAN_InitStructure.CAN_AWUM = DISABLE;
  CAN_InitStructure.CAN_NART = DISABLE;
  CAN_InitStructure.CAN_RFLM = DISABLE;
  CAN_InitStructure.CAN_TXFP = DISABLE;
  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
  CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;
  CAN_InitStructure.CAN_BS2 = CAN_BS2_5tq;
  CAN_InitStructure.CAN_Prescaler = 6;
  CAN_Init(CANx, &CAN_InitStructure);
  CAN_ITConfig(CANx, CAN_IT_FMP0, ENABLE);
}

int main(void)
{
  CAN_Config();
  while (1)
  {
    if (CAN_MessagePending(CANx, CAN_FIFO0) > 0)
    {
      CAN_Receive(CANx, CAN_FIFO0, &RxMessage);
      CAN_Transmit(CANx, &RxMessage);
      while (CAN_TransmitStatus(CANx, 0) == CAN_TxStatus_Failed);
    }
  }
  return 0;
}
