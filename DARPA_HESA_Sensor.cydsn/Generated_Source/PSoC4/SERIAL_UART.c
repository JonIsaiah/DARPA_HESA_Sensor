/*******************************************************************************
* File Name: SERIAL_UART.c
* Version 3.0
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  UART mode.
*
* Note:
*
*******************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SERIAL_PVT.h"
#include "SERIAL_SPI_UART_PVT.h"
#include "cyapicallbacks.h"

#if(SERIAL_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    const SERIAL_UART_INIT_STRUCT SERIAL_configUart =
    {
        SERIAL_UART_SUB_MODE,
        SERIAL_UART_DIRECTION,
        SERIAL_UART_DATA_BITS_NUM,
        SERIAL_UART_PARITY_TYPE,
        SERIAL_UART_STOP_BITS_NUM,
        SERIAL_UART_OVS_FACTOR,
        SERIAL_UART_IRDA_LOW_POWER,
        SERIAL_UART_MEDIAN_FILTER_ENABLE,
        SERIAL_UART_RETRY_ON_NACK,
        SERIAL_UART_IRDA_POLARITY,
        SERIAL_UART_DROP_ON_PARITY_ERR,
        SERIAL_UART_DROP_ON_FRAME_ERR,
        SERIAL_UART_WAKE_ENABLE,
        0u,
        NULL,
        0u,
        NULL,
        SERIAL_UART_MP_MODE_ENABLE,
        SERIAL_UART_MP_ACCEPT_ADDRESS,
        SERIAL_UART_MP_RX_ADDRESS,
        SERIAL_UART_MP_RX_ADDRESS_MASK,
        (uint32) SERIAL_SCB_IRQ_INTERNAL,
        SERIAL_UART_INTR_RX_MASK,
        SERIAL_UART_RX_TRIGGER_LEVEL,
        SERIAL_UART_INTR_TX_MASK,
        SERIAL_UART_TX_TRIGGER_LEVEL,
        (uint8) SERIAL_UART_BYTE_MODE_ENABLE,
        (uint8) SERIAL_UART_CTS_ENABLE,
        (uint8) SERIAL_UART_CTS_POLARITY,
        (uint8) SERIAL_UART_RTS_POLARITY,
        (uint8) SERIAL_UART_RTS_FIFO_LEVEL
    };


    /*******************************************************************************
    * Function Name: SERIAL_UartInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for the UART operation.
    *
    * Parameters:
    *  config:  Pointer to a structure that contains the following ordered list of
    *           fields. These fields match the selections available in the
    *           customizer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SERIAL_UartInit(const SERIAL_UART_INIT_STRUCT *config)
    {
        uint32 pinsConfig;

        if (NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Get direction to configure UART pins: TX, RX or TX+RX */
            pinsConfig  = config->direction;

        #if !(SERIAL_CY_SCBIP_V0 || SERIAL_CY_SCBIP_V1)
            /* Add RTS and CTS pins to configure */
            pinsConfig |= (0u != config->rtsRxFifoLevel) ? (SERIAL_UART_RTS_PIN_ENABLE) : (0u);
            pinsConfig |= (0u != config->enableCts)      ? (SERIAL_UART_CTS_PIN_ENABLE) : (0u);
        #endif /* !(SERIAL_CY_SCBIP_V0 || SERIAL_CY_SCBIP_V1) */

            /* Configure pins */
            SERIAL_SetPins(SERIAL_SCB_MODE_UART, config->mode, pinsConfig);

            /* Store internal configuration */
            SERIAL_scbMode       = (uint8) SERIAL_SCB_MODE_UART;
            SERIAL_scbEnableWake = (uint8) config->enableWake;
            SERIAL_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            SERIAL_rxBuffer      =         config->rxBuffer;
            SERIAL_rxDataBits    = (uint8) config->dataBits;
            SERIAL_rxBufferSize  = (uint8) config->rxBufferSize;

            /* Set TX direction internal variables */
            SERIAL_txBuffer      =         config->txBuffer;
            SERIAL_txDataBits    = (uint8) config->dataBits;
            SERIAL_txBufferSize  = (uint8) config->txBufferSize;

            /* Configure UART interface */
            if(SERIAL_UART_MODE_IRDA == config->mode)
            {
                /* OVS settings: IrDA */
                SERIAL_CTRL_REG  = ((0u != config->enableIrdaLowPower) ?
                                                (SERIAL_UART_GET_CTRL_OVS_IRDA_LP(config->oversample)) :
                                                (SERIAL_CTRL_OVS_IRDA_OVS16));
            }
            else
            {
                /* OVS settings: UART and SmartCard */
                SERIAL_CTRL_REG  = SERIAL_GET_CTRL_OVS(config->oversample);
            }

            SERIAL_CTRL_REG     |= SERIAL_GET_CTRL_BYTE_MODE  (config->enableByteMode)      |
                                             SERIAL_GET_CTRL_ADDR_ACCEPT(config->multiprocAcceptAddr) |
                                             SERIAL_CTRL_UART;

            /* Configure sub-mode: UART, SmartCard or IrDA */
            SERIAL_UART_CTRL_REG = SERIAL_GET_UART_CTRL_MODE(config->mode);

            /* Configure RX direction */
            SERIAL_UART_RX_CTRL_REG = SERIAL_GET_UART_RX_CTRL_MODE(config->stopBits)              |
                                        SERIAL_GET_UART_RX_CTRL_POLARITY(config->enableInvertedRx)          |
                                        SERIAL_GET_UART_RX_CTRL_MP_MODE(config->enableMultiproc)            |
                                        SERIAL_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(config->dropOnParityErr) |
                                        SERIAL_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(config->dropOnFrameErr);

            if(SERIAL_UART_PARITY_NONE != config->parity)
            {
               SERIAL_UART_RX_CTRL_REG |= SERIAL_GET_UART_RX_CTRL_PARITY(config->parity) |
                                                    SERIAL_UART_RX_CTRL_PARITY_ENABLED;
            }

            SERIAL_RX_CTRL_REG      = SERIAL_GET_RX_CTRL_DATA_WIDTH(config->dataBits)       |
                                                SERIAL_GET_RX_CTRL_MEDIAN(config->enableMedianFilter) |
                                                SERIAL_GET_UART_RX_CTRL_ENABLED(config->direction);

            SERIAL_RX_FIFO_CTRL_REG = SERIAL_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure MP address */
            SERIAL_RX_MATCH_REG     = SERIAL_GET_RX_MATCH_ADDR(config->multiprocAddr) |
                                                SERIAL_GET_RX_MATCH_MASK(config->multiprocAddrMask);

            /* Configure RX direction */
            SERIAL_UART_TX_CTRL_REG = SERIAL_GET_UART_TX_CTRL_MODE(config->stopBits) |
                                                SERIAL_GET_UART_TX_CTRL_RETRY_NACK(config->enableRetryNack);

            if(SERIAL_UART_PARITY_NONE != config->parity)
            {
               SERIAL_UART_TX_CTRL_REG |= SERIAL_GET_UART_TX_CTRL_PARITY(config->parity) |
                                                    SERIAL_UART_TX_CTRL_PARITY_ENABLED;
            }

            SERIAL_TX_CTRL_REG      = SERIAL_GET_TX_CTRL_DATA_WIDTH(config->dataBits)    |
                                                SERIAL_GET_UART_TX_CTRL_ENABLED(config->direction);

            SERIAL_TX_FIFO_CTRL_REG = SERIAL_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);

        #if !(SERIAL_CY_SCBIP_V0 || SERIAL_CY_SCBIP_V1)
            SERIAL_UART_FLOW_CTRL_REG = SERIAL_GET_UART_FLOW_CTRL_CTS_ENABLE(config->enableCts) | \
                                            SERIAL_GET_UART_FLOW_CTRL_CTS_POLARITY (config->ctsPolarity)  | \
                                            SERIAL_GET_UART_FLOW_CTRL_RTS_POLARITY (config->rtsPolarity)  | \
                                            SERIAL_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(config->rtsRxFifoLevel);
        #endif /* !(SERIAL_CY_SCBIP_V0 || SERIAL_CY_SCBIP_V1) */

            /* Configure interrupt with UART handler but do not enable it */
            CyIntDisable    (SERIAL_ISR_NUMBER);
            CyIntSetPriority(SERIAL_ISR_NUMBER, SERIAL_ISR_PRIORITY);
            (void) CyIntSetVector(SERIAL_ISR_NUMBER, &SERIAL_SPI_UART_ISR);

            /* Configure WAKE interrupt */
        #if(SERIAL_UART_RX_WAKEUP_IRQ)
            CyIntDisable    (SERIAL_RX_WAKE_ISR_NUMBER);
            CyIntSetPriority(SERIAL_RX_WAKE_ISR_NUMBER, SERIAL_RX_WAKE_ISR_PRIORITY);
            (void) CyIntSetVector(SERIAL_RX_WAKE_ISR_NUMBER, &SERIAL_UART_WAKEUP_ISR);
        #endif /* (SERIAL_UART_RX_WAKEUP_IRQ) */

            /* Configure interrupt sources */
            SERIAL_INTR_I2C_EC_MASK_REG = SERIAL_NO_INTR_SOURCES;
            SERIAL_INTR_SPI_EC_MASK_REG = SERIAL_NO_INTR_SOURCES;
            SERIAL_INTR_SLAVE_MASK_REG  = SERIAL_NO_INTR_SOURCES;
            SERIAL_INTR_MASTER_MASK_REG = SERIAL_NO_INTR_SOURCES;
            SERIAL_INTR_RX_MASK_REG     = config->rxInterruptMask;
            SERIAL_INTR_TX_MASK_REG     = config->txInterruptMask;

            /* Clear RX buffer indexes */
            SERIAL_rxBufferHead     = 0u;
            SERIAL_rxBufferTail     = 0u;
            SERIAL_rxBufferOverflow = 0u;

            /* Clear TX buffer indexes */
            SERIAL_txBufferHead = 0u;
            SERIAL_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: SERIAL_UartInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for the UART operation.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SERIAL_UartInit(void)
    {
        /* Configure UART interface */
        SERIAL_CTRL_REG = SERIAL_UART_DEFAULT_CTRL;

        /* Configure sub-mode: UART, SmartCard or IrDA */
        SERIAL_UART_CTRL_REG = SERIAL_UART_DEFAULT_UART_CTRL;

        /* Configure RX direction */
        SERIAL_UART_RX_CTRL_REG = SERIAL_UART_DEFAULT_UART_RX_CTRL;
        SERIAL_RX_CTRL_REG      = SERIAL_UART_DEFAULT_RX_CTRL;
        SERIAL_RX_FIFO_CTRL_REG = SERIAL_UART_DEFAULT_RX_FIFO_CTRL;
        SERIAL_RX_MATCH_REG     = SERIAL_UART_DEFAULT_RX_MATCH_REG;

        /* Configure TX direction */
        SERIAL_UART_TX_CTRL_REG = SERIAL_UART_DEFAULT_UART_TX_CTRL;
        SERIAL_TX_CTRL_REG      = SERIAL_UART_DEFAULT_TX_CTRL;
        SERIAL_TX_FIFO_CTRL_REG = SERIAL_UART_DEFAULT_TX_FIFO_CTRL;

    #if !(SERIAL_CY_SCBIP_V0 || SERIAL_CY_SCBIP_V1)
        SERIAL_UART_FLOW_CTRL_REG = SERIAL_UART_DEFAULT_FLOW_CTRL;
    #endif /* !(SERIAL_CY_SCBIP_V0 || SERIAL_CY_SCBIP_V1) */

        /* Configure interrupt with UART handler but do not enable it */
    #if(SERIAL_SCB_IRQ_INTERNAL)
        CyIntDisable    (SERIAL_ISR_NUMBER);
        CyIntSetPriority(SERIAL_ISR_NUMBER, SERIAL_ISR_PRIORITY);
        (void) CyIntSetVector(SERIAL_ISR_NUMBER, &SERIAL_SPI_UART_ISR);
    #endif /* (SERIAL_SCB_IRQ_INTERNAL) */

        /* Configure WAKE interrupt */
    #if(SERIAL_UART_RX_WAKEUP_IRQ)
        CyIntDisable    (SERIAL_RX_WAKE_ISR_NUMBER);
        CyIntSetPriority(SERIAL_RX_WAKE_ISR_NUMBER, SERIAL_RX_WAKE_ISR_PRIORITY);
        (void) CyIntSetVector(SERIAL_RX_WAKE_ISR_NUMBER, &SERIAL_UART_WAKEUP_ISR);
    #endif /* (SERIAL_UART_RX_WAKEUP_IRQ) */

        /* Configure interrupt sources */
        SERIAL_INTR_I2C_EC_MASK_REG = SERIAL_UART_DEFAULT_INTR_I2C_EC_MASK;
        SERIAL_INTR_SPI_EC_MASK_REG = SERIAL_UART_DEFAULT_INTR_SPI_EC_MASK;
        SERIAL_INTR_SLAVE_MASK_REG  = SERIAL_UART_DEFAULT_INTR_SLAVE_MASK;
        SERIAL_INTR_MASTER_MASK_REG = SERIAL_UART_DEFAULT_INTR_MASTER_MASK;
        SERIAL_INTR_RX_MASK_REG     = SERIAL_UART_DEFAULT_INTR_RX_MASK;
        SERIAL_INTR_TX_MASK_REG     = SERIAL_UART_DEFAULT_INTR_TX_MASK;

    #if(SERIAL_INTERNAL_RX_SW_BUFFER_CONST)
        SERIAL_rxBufferHead     = 0u;
        SERIAL_rxBufferTail     = 0u;
        SERIAL_rxBufferOverflow = 0u;
    #endif /* (SERIAL_INTERNAL_RX_SW_BUFFER_CONST) */

    #if(SERIAL_INTERNAL_TX_SW_BUFFER_CONST)
        SERIAL_txBufferHead = 0u;
        SERIAL_txBufferTail = 0u;
    #endif /* (SERIAL_INTERNAL_TX_SW_BUFFER_CONST) */
    }
#endif /* (SERIAL_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: SERIAL_UartPostEnable
********************************************************************************
*
* Summary:
*  Restores HSIOM settings for the UART output pins (TX and/or RTS) to be 
*  controlled by the SCB UART.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SERIAL_UartPostEnable(void)
{
#if (SERIAL_SCB_MODE_UNCONFIG_CONST_CFG)

#if (SERIAL_TX_SCL_MISO_PIN)
    if (SERIAL_CHECK_TX_SCL_MISO_PIN_USED)
    {
        /* Set SCB UART to drive the output pin */
        SERIAL_SET_HSIOM_SEL(SERIAL_TX_SCL_MISO_HSIOM_REG, SERIAL_TX_SCL_MISO_HSIOM_MASK,
                                       SERIAL_TX_SCL_MISO_HSIOM_POS, SERIAL_HSIOM_UART_SEL);
    }
#endif /* (SERIAL_TX_SCL_MISO_PIN_PIN) */

#if (SERIAL_RTS_SS0_PIN)
    if (SERIAL_CHECK_RTS_SS0_PIN_USED)
    {
        /* Set SCB UART to drive the output pin */
        SERIAL_SET_HSIOM_SEL(SERIAL_RTS_SS0_HSIOM_REG, SERIAL_RTS_SS0_HSIOM_MASK,
                                       SERIAL_RTS_SS0_HSIOM_POS, SERIAL_HSIOM_UART_SEL);
    }
#endif /* (SERIAL_RTS_SS0_PIN) */

#else
#if (SERIAL_UART_TX_PIN)
     /* Set SCB UART to drive the output pin */
    SERIAL_SET_HSIOM_SEL(SERIAL_TX_HSIOM_REG, SERIAL_TX_HSIOM_MASK,
                                   SERIAL_TX_HSIOM_POS, SERIAL_HSIOM_UART_SEL);
#endif /* (SERIAL_UART_TX_PIN) */

#if (SERIAL_UART_RTS_PIN)
    /* Set SCB UART to drive the output pin */
    SERIAL_SET_HSIOM_SEL(SERIAL_RTS_HSIOM_REG, SERIAL_RTS_HSIOM_MASK,
                                   SERIAL_RTS_HSIOM_POS, SERIAL_HSIOM_UART_SEL);
#endif /* (SERIAL_UART_RTS_PIN) */

#endif /* (SERIAL_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: SERIAL_UartStop
********************************************************************************
*
* Summary:
*  Changes the HSIOM settings for the UART output pins (TX and/or RTS) to keep
*  them inactive after the block is disabled. The output pins are controlled by
*  the GPIO data register. Also, the function disables the skip start feature to
*  not cause it to trigger after the component is enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SERIAL_UartStop(void)
{
#if(SERIAL_SCB_MODE_UNCONFIG_CONST_CFG)
    #if (SERIAL_TX_SCL_MISO_PIN)
        if (SERIAL_CHECK_TX_SCL_MISO_PIN_USED)
        {
            /* Set GPIO to drive output pin */
            SERIAL_SET_HSIOM_SEL(SERIAL_TX_SCL_MISO_HSIOM_REG, SERIAL_TX_SCL_MISO_HSIOM_MASK,
                                           SERIAL_TX_SCL_MISO_HSIOM_POS, SERIAL_HSIOM_GPIO_SEL);
        }
    #endif /* (SERIAL_TX_SCL_MISO_PIN_PIN) */

    #if (SERIAL_RTS_SS0_PIN)
        if (SERIAL_CHECK_RTS_SS0_PIN_USED)
        {
            /* Set output pin state after block is disabled */
            SERIAL_uart_rts_spi_ss0_Write(SERIAL_GET_UART_RTS_INACTIVE);

            /* Set GPIO to drive output pin */
            SERIAL_SET_HSIOM_SEL(SERIAL_RTS_SS0_HSIOM_REG, SERIAL_RTS_SS0_HSIOM_MASK,
                                           SERIAL_RTS_SS0_HSIOM_POS, SERIAL_HSIOM_GPIO_SEL);
        }
    #endif /* (SERIAL_SS0_PIN) */

#else
    #if (SERIAL_UART_TX_PIN)
        /* Set GPIO to drive output pin */
        SERIAL_SET_HSIOM_SEL(SERIAL_TX_HSIOM_REG, SERIAL_TX_HSIOM_MASK,
                                       SERIAL_TX_HSIOM_POS, SERIAL_HSIOM_GPIO_SEL);
    #endif /* (SERIAL_UART_TX_PIN) */

    #if (SERIAL_UART_RTS_PIN)
        /* Set output pin state after block is disabled */
        SERIAL_rts_Write(SERIAL_GET_UART_RTS_INACTIVE);

        /* Set GPIO to drive output pin */
        SERIAL_SET_HSIOM_SEL(SERIAL_RTS_HSIOM_REG, SERIAL_RTS_HSIOM_MASK,
                                       SERIAL_RTS_HSIOM_POS, SERIAL_HSIOM_GPIO_SEL);
    #endif /* (SERIAL_UART_RTS_PIN) */

#endif /* (SERIAL_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (SERIAL_UART_WAKE_ENABLE_CONST)
    /* Disable skip start feature used for wakeup */
    SERIAL_UART_RX_CTRL_REG &= (uint32) ~SERIAL_UART_RX_CTRL_SKIP_START;
#endif /* (SERIAL_UART_WAKE_ENABLE_CONST) */
}


/*******************************************************************************
* Function Name: SERIAL_UartSetRxAddress
********************************************************************************
*
* Summary:
*  Sets the hardware detectable receiver address for the UART in the
*  Multiprocessor mode.
*
* Parameters:
*  address: Address for hardware address detection.
*
* Return:
*  None
*
*******************************************************************************/
void SERIAL_UartSetRxAddress(uint32 address)
{
     uint32 matchReg;

    matchReg = SERIAL_RX_MATCH_REG;

    matchReg &= ((uint32) ~SERIAL_RX_MATCH_ADDR_MASK); /* Clear address bits */
    matchReg |= ((uint32)  (address & SERIAL_RX_MATCH_ADDR_MASK)); /* Set address  */

    SERIAL_RX_MATCH_REG = matchReg;
}


/*******************************************************************************
* Function Name: SERIAL_UartSetRxAddressMask
********************************************************************************
*
* Summary:
*  Sets the hardware address mask for the UART in the Multiprocessor mode.
*
* Parameters:
*  addressMask: Address mask.
*   0 - address bit does not care while comparison.
*   1 - address bit is significant while comparison.
*
* Return:
*  None
*
*******************************************************************************/
void SERIAL_UartSetRxAddressMask(uint32 addressMask)
{
    uint32 matchReg;

    matchReg = SERIAL_RX_MATCH_REG;

    matchReg &= ((uint32) ~SERIAL_RX_MATCH_MASK_MASK); /* Clear address mask bits */
    matchReg |= ((uint32) (addressMask << SERIAL_RX_MATCH_MASK_POS));

    SERIAL_RX_MATCH_REG = matchReg;
}


#if(SERIAL_UART_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: SERIAL_UartGetChar
    ********************************************************************************
    *
    * Summary:
    *  Retrieves the next data element from the receive buffer.
    *  This function is designed for ASCII characters and returns a char
    *  where 1 to 255 are valid characters and 0 indicates an error occurred or
    *  no data present.
    *  - The RX software buffer is disabled: returns the data element
    *    retrieved from the RX FIFO.
    *    Undefined data will be returned if the RX FIFO is empty.
    *  - The RX software buffer is enabled: returns the data element from
    *    the software receive buffer.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  The next data element from the receive buffer.
    *  ASCII character values from 1 to 255 are valid.
    *  A returned zero signifies an error condition or no data available.
    *
    * Side Effects:
    *  The errors bits may not correspond with reading characters due to RX FIFO
    *  and software buffer usage.
    *  RX software buffer is enabled: The internal software buffer overflow
    *  does not treat as an error condition.
    *  Check SCB_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 SERIAL_UartGetChar(void)
    {
        uint32 rxData = 0u;

        /* Reads data only if there is data to read */
        if (0u != SERIAL_SpiUartGetRxBufferSize())
        {
            rxData = SERIAL_SpiUartReadRxData();
        }

        if (SERIAL_CHECK_INTR_RX(SERIAL_INTR_RX_ERR))
        {
            rxData = 0u; /* Error occurred: returns zero */
            SERIAL_ClearRxInterruptSource(SERIAL_INTR_RX_ERR);
        }

        return (rxData);
    }


    /*******************************************************************************
    * Function Name: SERIAL_UartGetByte
    ********************************************************************************
    *
    * Summary:
    *  Retrieves the next data element from the receive buffer, returns the
    *  received byte and error condition.
    *   - The RX software buffer is disabled: returns the data element retrieved
    *     from the RX FIFO. Undefined data will be returned if the RX FIFO is
    *     empty.
    *   - The RX software buffer is enabled: returns data element from the
    *     software receive buffer.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Bits 7-0 contain the next data element from the receive buffer and
    *  other bits contain the error condition.
    *
    * Side Effects:
    *  The errors bits may not correspond with reading characters due to RX FIFO
    *  and software buffer usage.
    *  RX software buffer is disabled: The internal software buffer overflow
    *  is not returned as status by this function.
    *  Check SCB_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 SERIAL_UartGetByte(void)
    {
        uint32 rxData;
        uint32 tmpStatus;

        #if (SERIAL_CHECK_RX_SW_BUFFER)
        {
            SERIAL_DisableInt();
        }
        #endif

        if (0u != SERIAL_SpiUartGetRxBufferSize())
        {
            /* Enables interrupt to receive more bytes: at least one byte is in
            * buffer.
            */
            #if (SERIAL_CHECK_RX_SW_BUFFER)
            {            
                SERIAL_EnableInt();
            }
            #endif

            /* Get received byte */
            rxData = SERIAL_SpiUartReadRxData();
        }
        else
        {
            /* Reads a byte directly from RX FIFO: underflow is raised in the case
            * of empty. Otherwise the first received byte will be read.
            */
            rxData = SERIAL_RX_FIFO_RD_REG;

            /* Enables interrupt to receive more bytes.
            * The RX_NOT_EMPTY interrupt is cleared by the interrupt routine
            * in case the byte was received and read by code above.
            */
            #if (SERIAL_CHECK_RX_SW_BUFFER)
            {
                SERIAL_EnableInt();
            }
            #endif
        }

        /* Get and clear RX error mask */
        tmpStatus = (SERIAL_GetRxInterruptSource() & SERIAL_INTR_RX_ERR);
        SERIAL_ClearRxInterruptSource(SERIAL_INTR_RX_ERR);

        /* Puts together data and error status:
        * MP mode and accept address: 9th bit is set to notify mark.
        */
        rxData |= ((uint32) (tmpStatus << 8u));

        return (rxData);
    }


    #if !(SERIAL_CY_SCBIP_V0 || SERIAL_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: SERIAL_UartSetRtsPolarity
        ********************************************************************************
        *
        * Summary:
        *  Sets active polarity of RTS output signal.
        *
        * Parameters:
        *  polarity: Active polarity of RTS output signal.
        *   SERIAL_UART_RTS_ACTIVE_LOW  - RTS signal is active low.
        *   SERIAL_UART_RTS_ACTIVE_HIGH - RTS signal is active high.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void SERIAL_UartSetRtsPolarity(uint32 polarity)
        {
            if(0u != polarity)
            {
                SERIAL_UART_FLOW_CTRL_REG |= (uint32)  SERIAL_UART_FLOW_CTRL_RTS_POLARITY;
            }
            else
            {
                SERIAL_UART_FLOW_CTRL_REG &= (uint32) ~SERIAL_UART_FLOW_CTRL_RTS_POLARITY;
            }
        }


        /*******************************************************************************
        * Function Name: SERIAL_UartSetRtsFifoLevel
        ********************************************************************************
        *
        * Summary:
        *  Sets level in the RX FIFO for RTS signal activation.
        *  While the RX FIFO has fewer entries than the RX FIFO level the RTS signal
        *  remains active, otherwise the RTS signal becomes inactive.
        *
        * Parameters:
        *  level: Level in the RX FIFO for RTS signal activation.
        *         The range of valid level values is between 0 and RX FIFO depth - 1.
        *         Setting level value to 0 disables RTS signal activation.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void SERIAL_UartSetRtsFifoLevel(uint32 level)
        {
            uint32 uartFlowCtrl;

            uartFlowCtrl = SERIAL_UART_FLOW_CTRL_REG;

            uartFlowCtrl &= ((uint32) ~SERIAL_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
            uartFlowCtrl |= ((uint32) (SERIAL_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK & level));

            SERIAL_UART_FLOW_CTRL_REG = uartFlowCtrl;
        }
    #endif /* !(SERIAL_CY_SCBIP_V0 || SERIAL_CY_SCBIP_V1) */

#endif /* (SERIAL_UART_RX_DIRECTION) */


#if(SERIAL_UART_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: SERIAL_UartPutString
    ********************************************************************************
    *
    * Summary:
    *  Places a NULL terminated string in the transmit buffer to be sent at the
    *  next available bus time.
    *  This function is blocking and waits until there is space available to put
    *  all the requested data into the  transmit buffer.
    *
    * Parameters:
    *  string: pointer to the null terminated string array to be placed in the
    *          transmit buffer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SERIAL_UartPutString(const char8 string[])
    {
        uint32 bufIndex;

        bufIndex = 0u;

        /* Blocks the control flow until all data has been sent */
        while(string[bufIndex] != ((char8) 0))
        {
            SERIAL_UartPutChar((uint32) string[bufIndex]);
            bufIndex++;
        }
    }


    /*******************************************************************************
    * Function Name: SERIAL_UartPutCRLF
    ********************************************************************************
    *
    * Summary:
    *  Places a byte of data followed by a carriage return (0x0D) and
    *  line feed (0x0A) into the transmit buffer.
    *  This function is blocking and waits until there is space available to put
    *  all the requested data into the  transmit buffer.
    *
    * Parameters:
    *  txDataByte : the data to be transmitted.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SERIAL_UartPutCRLF(uint32 txDataByte)
    {
        SERIAL_UartPutChar(txDataByte);  /* Blocks control flow until all data has been sent */
        SERIAL_UartPutChar(0x0Du);       /* Blocks control flow until all data has been sent */
        SERIAL_UartPutChar(0x0Au);       /* Blocks control flow until all data has been sent */
    }


    #if !(SERIAL_CY_SCBIP_V0 || SERIAL_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: SERIALSCB_UartEnableCts
        ********************************************************************************
        *
        * Summary:
        *  Enables usage of CTS input signal by the UART transmitter.
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void SERIAL_UartEnableCts(void)
        {
            SERIAL_UART_FLOW_CTRL_REG |= (uint32)  SERIAL_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: SERIAL_UartDisableCts
        ********************************************************************************
        *
        * Summary:
        *  Disables usage of CTS input signal by the UART transmitter.
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void SERIAL_UartDisableCts(void)
        {
            SERIAL_UART_FLOW_CTRL_REG &= (uint32) ~SERIAL_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: SERIAL_UartSetCtsPolarity
        ********************************************************************************
        *
        * Summary:
        *  Sets active polarity of CTS input signal.
        *
        * Parameters:
        *  polarity: Active polarity of CTS output signal.
        *   SERIAL_UART_CTS_ACTIVE_LOW  - CTS signal is active low.
        *   SERIAL_UART_CTS_ACTIVE_HIGH - CTS signal is active high.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void SERIAL_UartSetCtsPolarity(uint32 polarity)
        {
            if (0u != polarity)
            {
                SERIAL_UART_FLOW_CTRL_REG |= (uint32)  SERIAL_UART_FLOW_CTRL_CTS_POLARITY;
            }
            else
            {
                SERIAL_UART_FLOW_CTRL_REG &= (uint32) ~SERIAL_UART_FLOW_CTRL_CTS_POLARITY;
            }
        }
    #endif /* !(SERIAL_CY_SCBIP_V0 || SERIAL_CY_SCBIP_V1) */

#endif /* (SERIAL_UART_TX_DIRECTION) */


#if(SERIAL_UART_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: SERIAL_UartSaveConfig
    ********************************************************************************
    *
    * Summary:
    *  Clears and enables interrupt on a falling edge of the Rx input. The GPIO
    *  event wakes up the device and SKIP_START feature allows the UART continue
    *  receiving data bytes properly. The GPIO interrupt does not track in the
    *  active mode therefore requires to be cleared by this API.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SERIAL_UartSaveConfig(void)
    {
        /* Clear interrupt activity:
        *  - set skip start and disable RX. At GPIO wakeup RX will be enabled.
        *  - clear rx_wake interrupt source as it triggers during normal operation.
        *  - clear wake interrupt pending state as it becomes pending in active mode.
        */

        SERIAL_UART_RX_CTRL_REG |= SERIAL_UART_RX_CTRL_SKIP_START;

    #if(SERIAL_SCB_MODE_UNCONFIG_CONST_CFG)
        #if(SERIAL_MOSI_SCL_RX_WAKE_PIN)
            (void) SERIAL_uart_rx_wake_i2c_sda_spi_mosi_ClearInterrupt();
        #endif /* (SERIAL_MOSI_SCL_RX_WAKE_PIN) */
    #else
        #if(SERIAL_UART_RX_WAKE_PIN)
            (void) SERIAL_rx_wake_ClearInterrupt();
        #endif /* (SERIAL_UART_RX_WAKE_PIN) */
    #endif /* (SERIAL_SCB_MODE_UNCONFIG_CONST_CFG) */

    #if(SERIAL_UART_RX_WAKEUP_IRQ)
        SERIAL_RxWakeClearPendingInt();
        SERIAL_RxWakeEnableInt();
    #endif /* (SERIAL_UART_RX_WAKEUP_IRQ) */
    }


    /*******************************************************************************
    * Function Name: SERIAL_UartRestoreConfig
    ********************************************************************************
    *
    * Summary:
    *  Disables the RX GPIO interrupt. Until this function is called the interrupt
    *  remains active and triggers on every falling edge of the UART RX line.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SERIAL_UartRestoreConfig(void)
    {
    /* Disable RX GPIO interrupt: no more triggers in active mode */
    #if(SERIAL_UART_RX_WAKEUP_IRQ)
        SERIAL_RxWakeDisableInt();
    #endif /* (SERIAL_UART_RX_WAKEUP_IRQ) */
    }
#endif /* (SERIAL_UART_WAKE_ENABLE_CONST) */


#if(SERIAL_UART_RX_WAKEUP_IRQ)
    /*******************************************************************************
    * Function Name: SERIAL_UART_WAKEUP_ISR
    ********************************************************************************
    *
    * Summary:
    *  Handles the Interrupt Service Routine for the SCB UART mode GPIO wakeup
    *  event. This event is configured to trigger on a falling edge of the RX line.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    CY_ISR(SERIAL_UART_WAKEUP_ISR)
    {
    #ifdef SERIAL_UART_WAKEUP_ISR_ENTRY_CALLBACK
        SERIAL_UART_WAKEUP_ISR_EntryCallback();
    #endif /* SERIAL_UART_WAKEUP_ISR_ENTRY_CALLBACK */

        /* Clear interrupt source: the event becomes multi triggered and is
        * only disabled by SERIAL_UartRestoreConfig() call.
        */
    #if(SERIAL_SCB_MODE_UNCONFIG_CONST_CFG)
        #if(SERIAL_MOSI_SCL_RX_WAKE_PIN)
            (void) SERIAL_uart_rx_wake_i2c_sda_spi_mosi_ClearInterrupt();
        #endif /* (SERIAL_MOSI_SCL_RX_WAKE_PIN) */
    #else
        #if(SERIAL_UART_RX_WAKE_PIN)
            (void) SERIAL_rx_wake_ClearInterrupt();
        #endif /* (SERIAL_UART_RX_WAKE_PIN) */
    #endif /* (SERIAL_SCB_MODE_UNCONFIG_CONST_CFG) */

    #ifdef SERIAL_UART_WAKEUP_ISR_EXIT_CALLBACK
        SERIAL_UART_WAKEUP_ISR_ExitCallback();
    #endif /* SERIAL_UART_WAKEUP_ISR_EXIT_CALLBACK */
    }
#endif /* (SERIAL_UART_RX_WAKEUP_IRQ) */


/* [] END OF FILE */
