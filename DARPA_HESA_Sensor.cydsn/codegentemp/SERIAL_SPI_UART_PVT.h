/*******************************************************************************
* File Name: SERIAL_SPI_UART_PVT.h
* Version 3.0
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component in SPI and UART modes.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_SPI_UART_PVT_SERIAL_H)
#define CY_SCB_SPI_UART_PVT_SERIAL_H

#include "SERIAL_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (SERIAL_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  SERIAL_rxBufferHead;
    extern volatile uint32  SERIAL_rxBufferTail;
    extern volatile uint8   SERIAL_rxBufferOverflow;
#endif /* (SERIAL_INTERNAL_RX_SW_BUFFER_CONST) */

#if (SERIAL_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  SERIAL_txBufferHead;
    extern volatile uint32  SERIAL_txBufferTail;
#endif /* (SERIAL_INTERNAL_TX_SW_BUFFER_CONST) */

#if (SERIAL_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 SERIAL_rxBufferInternal[SERIAL_INTERNAL_RX_BUFFER_SIZE];
#endif /* (SERIAL_INTERNAL_RX_SW_BUFFER) */

#if (SERIAL_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 SERIAL_txBufferInternal[SERIAL_TX_BUFFER_SIZE];
#endif /* (SERIAL_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void SERIAL_SpiPostEnable(void);
void SERIAL_SpiStop(void);

#if (SERIAL_SCB_MODE_SPI_CONST_CFG)
    void SERIAL_SpiInit(void);
#endif /* (SERIAL_SCB_MODE_SPI_CONST_CFG) */

#if (SERIAL_SPI_WAKE_ENABLE_CONST)
    void SERIAL_SpiSaveConfig(void);
    void SERIAL_SpiRestoreConfig(void);
#endif /* (SERIAL_SPI_WAKE_ENABLE_CONST) */

void SERIAL_UartPostEnable(void);
void SERIAL_UartStop(void);

#if (SERIAL_SCB_MODE_UART_CONST_CFG)
    void SERIAL_UartInit(void);
#endif /* (SERIAL_SCB_MODE_UART_CONST_CFG) */

#if (SERIAL_UART_WAKE_ENABLE_CONST)
    void SERIAL_UartSaveConfig(void);
    void SERIAL_UartRestoreConfig(void);
#endif /* (SERIAL_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in SERIAL_SetPins() */
#define SERIAL_UART_RX_PIN_ENABLE    (SERIAL_UART_RX)
#define SERIAL_UART_TX_PIN_ENABLE    (SERIAL_UART_TX)

/* UART RTS and CTS position to be used in  SERIAL_SetPins() */
#define SERIAL_UART_RTS_PIN_ENABLE    (0x10u)
#define SERIAL_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define SERIAL_SpiUartEnableIntRx(intSourceMask)  SERIAL_SetRxInterruptMode(intSourceMask)
#define SERIAL_SpiUartEnableIntTx(intSourceMask)  SERIAL_SetTxInterruptMode(intSourceMask)
uint32  SERIAL_SpiUartDisableIntRx(void);
uint32  SERIAL_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_SERIAL_H) */


/* [] END OF FILE */
