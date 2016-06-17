/*******************************************************************************
* File Name: SERIAL_SPI_UART_INT.c
* Version 3.0
*
* Description:
*  This file provides the source code to the Interrupt Service Routine for
*  the SCB Component in SPI and UART modes.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SERIAL_PVT.h"
#include "SERIAL_SPI_UART_PVT.h"
#include "cyapicallbacks.h"

#if (SERIAL_SCB_IRQ_INTERNAL)
/*******************************************************************************
* Function Name: SERIAL_SPI_UART_ISR
********************************************************************************
*
* Summary:
*  Handles the Interrupt Service Routine for the SCB SPI or UART modes.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
CY_ISR(SERIAL_SPI_UART_ISR)
{
#if (SERIAL_INTERNAL_RX_SW_BUFFER_CONST)
    uint32 locHead;
#endif /* (SERIAL_INTERNAL_RX_SW_BUFFER_CONST) */

#if (SERIAL_INTERNAL_TX_SW_BUFFER_CONST)
    uint32 locTail;
#endif /* (SERIAL_INTERNAL_TX_SW_BUFFER_CONST) */

#ifdef SERIAL_SPI_UART_ISR_ENTRY_CALLBACK
    SERIAL_SPI_UART_ISR_EntryCallback();
#endif /* SERIAL_SPI_UART_ISR_ENTRY_CALLBACK */

    if (NULL != SERIAL_customIntrHandler)
    {
        SERIAL_customIntrHandler();
    }

    #if (SERIAL_CHECK_SPI_WAKE_ENABLE)
    {
        /* Clear SPI wakeup source */
        SERIAL_ClearSpiExtClkInterruptSource(SERIAL_INTR_SPI_EC_WAKE_UP);
    }
    #endif

    #if (SERIAL_CHECK_RX_SW_BUFFER)
    {
        if (SERIAL_CHECK_INTR_RX_MASKED(SERIAL_INTR_RX_NOT_EMPTY))
        {
            do
            {
                /* Move local head index */
                locHead = (SERIAL_rxBufferHead + 1u);

                /* Adjust local head index */
                if (SERIAL_INTERNAL_RX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                if (locHead == SERIAL_rxBufferTail)
                {
                    #if (SERIAL_CHECK_UART_RTS_CONTROL_FLOW)
                    {
                        /* There is no space in the software buffer - disable the
                        * RX Not Empty interrupt source. The data elements are
                        * still being received into the RX FIFO until the RTS signal
                        * stops the transmitter. After the data element is read from the
                        * buffer, the RX Not Empty interrupt source is enabled to
                        * move the next data element in the software buffer.
                        */
                        SERIAL_INTR_RX_MASK_REG &= ~SERIAL_INTR_RX_NOT_EMPTY;
                        break;
                    }
                    #else
                    {
                        /* Overflow: through away received data element */
                        (void) SERIAL_RX_FIFO_RD_REG;
                        SERIAL_rxBufferOverflow = (uint8) SERIAL_INTR_RX_OVERFLOW;
                    }
                    #endif
                }
                else
                {
                    /* Store received data */
                    SERIAL_PutWordInRxBuffer(locHead, SERIAL_RX_FIFO_RD_REG);

                    /* Move head index */
                    SERIAL_rxBufferHead = locHead;
                }
            }
            while(0u != SERIAL_GET_RX_FIFO_ENTRIES);

            SERIAL_ClearRxInterruptSource(SERIAL_INTR_RX_NOT_EMPTY);
        }
    }
    #endif


    #if (SERIAL_CHECK_TX_SW_BUFFER)
    {
        if (SERIAL_CHECK_INTR_TX_MASKED(SERIAL_INTR_TX_NOT_FULL))
        {
            do
            {
                /* Check for room in TX software buffer */
                if (SERIAL_txBufferHead != SERIAL_txBufferTail)
                {
                    /* Move local tail index */
                    locTail = (SERIAL_txBufferTail + 1u);

                    /* Adjust local tail index */
                    if (SERIAL_TX_BUFFER_SIZE == locTail)
                    {
                        locTail = 0u;
                    }

                    /* Put data into TX FIFO */
                    SERIAL_TX_FIFO_WR_REG = SERIAL_GetWordFromTxBuffer(locTail);

                    /* Move tail index */
                    SERIAL_txBufferTail = locTail;
                }
                else
                {
                    /* TX software buffer is empty: complete transfer */
                    SERIAL_DISABLE_INTR_TX(SERIAL_INTR_TX_NOT_FULL);
                    break;
                }
            }
            while (SERIAL_SPI_UART_FIFO_SIZE != SERIAL_GET_TX_FIFO_ENTRIES);

            SERIAL_ClearTxInterruptSource(SERIAL_INTR_TX_NOT_FULL);
        }
    }
    #endif
    
#ifdef SERIAL_SPI_UART_ISR_EXIT_CALLBACK
    SERIAL_SPI_UART_ISR_ExitCallback();
#endif /* SERIAL_SPI_UART_ISR_EXIT_CALLBACK */
    
}

#endif /* (SERIAL_SCB_IRQ_INTERNAL) */


/* [] END OF FILE */
