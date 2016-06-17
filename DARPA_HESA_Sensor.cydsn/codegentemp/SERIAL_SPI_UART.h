/*******************************************************************************
* File Name: SERIAL_SPI_UART.h
* Version 3.0
*
* Description:
*  This file provides constants and parameter values for the SCB Component in
*  SPI and UART modes.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_SPI_UART_SERIAL_H)
#define CY_SCB_SPI_UART_SERIAL_H

#include "SERIAL.h"


/***************************************
*   SPI Initial Parameter Constants
****************************************/

#define SERIAL_SPI_MODE                   (0u)
#define SERIAL_SPI_SUB_MODE               (0u)
#define SERIAL_SPI_CLOCK_MODE             (0u)
#define SERIAL_SPI_OVS_FACTOR             (16u)
#define SERIAL_SPI_MEDIAN_FILTER_ENABLE   (0u)
#define SERIAL_SPI_LATE_MISO_SAMPLE_ENABLE (0u)
#define SERIAL_SPI_RX_DATA_BITS_NUM       (8u)
#define SERIAL_SPI_TX_DATA_BITS_NUM       (8u)
#define SERIAL_SPI_WAKE_ENABLE            (0u)
#define SERIAL_SPI_BITS_ORDER             (1u)
#define SERIAL_SPI_TRANSFER_SEPARATION    (1u)
#define SERIAL_SPI_NUMBER_OF_SS_LINES     (1u)
#define SERIAL_SPI_RX_BUFFER_SIZE         (8u)
#define SERIAL_SPI_TX_BUFFER_SIZE         (8u)

#define SERIAL_SPI_INTERRUPT_MODE         (0u)

#define SERIAL_SPI_INTR_RX_MASK           (0u)
#define SERIAL_SPI_INTR_TX_MASK           (0u)

#define SERIAL_SPI_RX_TRIGGER_LEVEL       (7u)
#define SERIAL_SPI_TX_TRIGGER_LEVEL       (0u)

#define SERIAL_SPI_BYTE_MODE_ENABLE       (0u)
#define SERIAL_SPI_FREE_RUN_SCLK_ENABLE   (0u)
#define SERIAL_SPI_SS0_POLARITY           (0u)
#define SERIAL_SPI_SS1_POLARITY           (0u)
#define SERIAL_SPI_SS2_POLARITY           (0u)
#define SERIAL_SPI_SS3_POLARITY           (0u)


/***************************************
*   UART Initial Parameter Constants
****************************************/

#define SERIAL_UART_SUB_MODE              (0u)
#define SERIAL_UART_DIRECTION             (3u)
#define SERIAL_UART_DATA_BITS_NUM         (8u)
#define SERIAL_UART_PARITY_TYPE           (2u)
#define SERIAL_UART_STOP_BITS_NUM         (2u)
#define SERIAL_UART_OVS_FACTOR            (12u)
#define SERIAL_UART_IRDA_LOW_POWER        (0u)
#define SERIAL_UART_MEDIAN_FILTER_ENABLE  (0u)
#define SERIAL_UART_RETRY_ON_NACK         (0u)
#define SERIAL_UART_IRDA_POLARITY         (0u)
#define SERIAL_UART_DROP_ON_FRAME_ERR     (0u)
#define SERIAL_UART_DROP_ON_PARITY_ERR    (0u)
#define SERIAL_UART_WAKE_ENABLE           (0u)
#define SERIAL_UART_RX_BUFFER_SIZE        (8u)
#define SERIAL_UART_TX_BUFFER_SIZE        (8u)
#define SERIAL_UART_MP_MODE_ENABLE        (0u)
#define SERIAL_UART_MP_ACCEPT_ADDRESS     (0u)
#define SERIAL_UART_MP_RX_ADDRESS         (2u)
#define SERIAL_UART_MP_RX_ADDRESS_MASK    (255u)

#define SERIAL_UART_INTERRUPT_MODE        (0u)

#define SERIAL_UART_INTR_RX_MASK          (0u)
#define SERIAL_UART_INTR_TX_MASK          (0u)

#define SERIAL_UART_RX_TRIGGER_LEVEL      (7u)
#define SERIAL_UART_TX_TRIGGER_LEVEL      (0u)

#define SERIAL_UART_BYTE_MODE_ENABLE      (0u)
#define SERIAL_UART_CTS_ENABLE            (0u)
#define SERIAL_UART_CTS_POLARITY          (0u)
#define SERIAL_UART_RTS_ENABLE            (0u)
#define SERIAL_UART_RTS_POLARITY          (0u)
#define SERIAL_UART_RTS_FIFO_LEVEL        (4u)

/* SPI mode enum */
#define SERIAL_SPI_SLAVE  (0u)
#define SERIAL_SPI_MASTER (1u)

/* UART direction enum */
#define SERIAL_UART_RX    (1u)
#define SERIAL_UART_TX    (2u)
#define SERIAL_UART_TX_RX (3u)


/***************************************
*   Conditional Compilation Parameters
****************************************/

#if(SERIAL_SCB_MODE_UNCONFIG_CONST_CFG)

    /* Mode */
    #define SERIAL_SPI_SLAVE_CONST        (1u)
    #define SERIAL_SPI_MASTER_CONST       (1u)

    /* Direction */
    #define SERIAL_RX_DIRECTION           (1u)
    #define SERIAL_TX_DIRECTION           (1u)
    #define SERIAL_UART_RX_DIRECTION      (1u)
    #define SERIAL_UART_TX_DIRECTION      (1u)

    /* Only external RX and TX buffer for Uncofigured mode */
    #define SERIAL_INTERNAL_RX_SW_BUFFER   (0u)
    #define SERIAL_INTERNAL_TX_SW_BUFFER   (0u)

    /* Get RX and TX buffer size */
    #define SERIAL_INTERNAL_RX_BUFFER_SIZE    (SERIAL_rxBufferSize + 1u)
    #define SERIAL_RX_BUFFER_SIZE             (SERIAL_rxBufferSize)
    #define SERIAL_TX_BUFFER_SIZE             (SERIAL_txBufferSize)

    /* Return true if buffer is provided */
    #define SERIAL_CHECK_RX_SW_BUFFER (NULL != SERIAL_rxBuffer)
    #define SERIAL_CHECK_TX_SW_BUFFER (NULL != SERIAL_txBuffer)

    /* Always provide global variables to support RX and TX buffers */
    #define SERIAL_INTERNAL_RX_SW_BUFFER_CONST    (1u)
    #define SERIAL_INTERNAL_TX_SW_BUFFER_CONST    (1u)

    /* Get wakeup enable option */
    #define SERIAL_SPI_WAKE_ENABLE_CONST  (1u)
    #define SERIAL_CHECK_SPI_WAKE_ENABLE  (0u != SERIAL_scbEnableWake)
    #define SERIAL_UART_WAKE_ENABLE_CONST (1u)

    /* SPI/UART: TX or RX FIFO size */
    #if (SERIAL_CY_SCBIP_V0 || SERIAL_CY_SCBIP_V1)
        #define SERIAL_SPI_UART_FIFO_SIZE             (SERIAL_FIFO_SIZE)
        #define SERIAL_CHECK_UART_RTS_CONTROL_FLOW    (0u)
    #else
        #define SERIAL_SPI_UART_FIFO_SIZE (SERIAL_GET_FIFO_SIZE(SERIAL_CTRL_REG & \
                                                                                    SERIAL_CTRL_BYTE_MODE))

        #define SERIAL_CHECK_UART_RTS_CONTROL_FLOW \
                    ((SERIAL_SCB_MODE_UART_RUNTM_CFG) && \
                     (0u != SERIAL_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(SERIAL_UART_FLOW_CTRL_REG)))
    #endif /* (SERIAL_CY_SCBIP_V0 || SERIAL_CY_SCBIP_V1) */

#else

    /* Internal RX and TX buffer: for SPI or UART */
    #if (SERIAL_SCB_MODE_SPI_CONST_CFG)

        /* SPI Direction */
        #define SERIAL_SPI_RX_DIRECTION (1u)
        #define SERIAL_SPI_TX_DIRECTION (1u)

        /* Get FIFO size */
        #if (SERIAL_CY_SCBIP_V0 || SERIAL_CY_SCBIP_V1)
            #define SERIAL_SPI_UART_FIFO_SIZE    (SERIAL_FIFO_SIZE)
        #else
            #define SERIAL_SPI_UART_FIFO_SIZE \
                                           SERIAL_GET_FIFO_SIZE(SERIAL_SPI_BYTE_MODE_ENABLE)

        #endif /* (SERIAL_CY_SCBIP_V0 || SERIAL_CY_SCBIP_V1) */

        /* SPI internal RX and TX buffers */
        #define SERIAL_INTERNAL_SPI_RX_SW_BUFFER  (SERIAL_SPI_RX_BUFFER_SIZE > \
                                                                SERIAL_SPI_UART_FIFO_SIZE)
        #define SERIAL_INTERNAL_SPI_TX_SW_BUFFER  (SERIAL_SPI_TX_BUFFER_SIZE > \
                                                                SERIAL_SPI_UART_FIFO_SIZE)

        /* Internal SPI RX and TX buffer */
        #define SERIAL_INTERNAL_RX_SW_BUFFER  (SERIAL_INTERNAL_SPI_RX_SW_BUFFER)
        #define SERIAL_INTERNAL_TX_SW_BUFFER  (SERIAL_INTERNAL_SPI_TX_SW_BUFFER)

        /* Internal SPI RX and TX buffer size */
        #define SERIAL_INTERNAL_RX_BUFFER_SIZE    (SERIAL_SPI_RX_BUFFER_SIZE + 1u)
        #define SERIAL_RX_BUFFER_SIZE             (SERIAL_SPI_RX_BUFFER_SIZE)
        #define SERIAL_TX_BUFFER_SIZE             (SERIAL_SPI_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define SERIAL_SPI_WAKE_ENABLE_CONST  (0u != SERIAL_SPI_WAKE_ENABLE)
        #define SERIAL_UART_WAKE_ENABLE_CONST (0u)

    #else

        /* UART Direction */
        #define SERIAL_UART_RX_DIRECTION (0u != (SERIAL_UART_DIRECTION & SERIAL_UART_RX))
        #define SERIAL_UART_TX_DIRECTION (0u != (SERIAL_UART_DIRECTION & SERIAL_UART_TX))

        /* Get FIFO size */
        #if (SERIAL_CY_SCBIP_V0 || SERIAL_CY_SCBIP_V1)
            #define SERIAL_SPI_UART_FIFO_SIZE    (SERIAL_FIFO_SIZE)
        #else
            #define SERIAL_SPI_UART_FIFO_SIZE \
                                           SERIAL_GET_FIFO_SIZE(SERIAL_UART_BYTE_MODE_ENABLE)
        #endif /* (SERIAL_CY_SCBIP_V0 || SERIAL_CY_SCBIP_V1) */

        /* UART internal RX and TX buffers */
        #define SERIAL_INTERNAL_UART_RX_SW_BUFFER  (SERIAL_UART_RX_BUFFER_SIZE > \
                                                                SERIAL_SPI_UART_FIFO_SIZE)
        #define SERIAL_INTERNAL_UART_TX_SW_BUFFER  (SERIAL_UART_TX_BUFFER_SIZE > \
                                                                    SERIAL_SPI_UART_FIFO_SIZE)

        /* Internal UART RX and TX buffer */
        #define SERIAL_INTERNAL_RX_SW_BUFFER  (SERIAL_INTERNAL_UART_RX_SW_BUFFER)
        #define SERIAL_INTERNAL_TX_SW_BUFFER  (SERIAL_INTERNAL_UART_TX_SW_BUFFER)

        /* Internal UART RX and TX buffer size */
        #define SERIAL_INTERNAL_RX_BUFFER_SIZE    (SERIAL_UART_RX_BUFFER_SIZE + 1u)
        #define SERIAL_RX_BUFFER_SIZE             (SERIAL_UART_RX_BUFFER_SIZE)
        #define SERIAL_TX_BUFFER_SIZE             (SERIAL_UART_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define SERIAL_SPI_WAKE_ENABLE_CONST  (0u)
        #define SERIAL_UART_WAKE_ENABLE_CONST (0u != SERIAL_UART_WAKE_ENABLE)

    #endif /* (SERIAL_SCB_MODE_SPI_CONST_CFG) */

    /* Mode */
    #define SERIAL_SPI_SLAVE_CONST    (SERIAL_SPI_MODE == SERIAL_SPI_SLAVE)
    #define SERIAL_SPI_MASTER_CONST   (SERIAL_SPI_MODE == SERIAL_SPI_MASTER)

    /* Direction */
    #define SERIAL_RX_DIRECTION ((SERIAL_SCB_MODE_SPI_CONST_CFG) ? \
                                            (SERIAL_SPI_RX_DIRECTION) : (SERIAL_UART_RX_DIRECTION))

    #define SERIAL_TX_DIRECTION ((SERIAL_SCB_MODE_SPI_CONST_CFG) ? \
                                            (SERIAL_SPI_TX_DIRECTION) : (SERIAL_UART_TX_DIRECTION))

    /* Internal RX and TX buffer: for SPI or UART. Used in conditional compilation check */
    #define SERIAL_CHECK_RX_SW_BUFFER (SERIAL_INTERNAL_RX_SW_BUFFER)
    #define SERIAL_CHECK_TX_SW_BUFFER (SERIAL_INTERNAL_TX_SW_BUFFER)

    /* Provide global variables to support RX and TX buffers */
    #define SERIAL_INTERNAL_RX_SW_BUFFER_CONST    (SERIAL_INTERNAL_RX_SW_BUFFER)
    #define SERIAL_INTERNAL_TX_SW_BUFFER_CONST    (SERIAL_INTERNAL_TX_SW_BUFFER)

    /* SPI wakeup */
    #define SERIAL_CHECK_SPI_WAKE_ENABLE  (SERIAL_SPI_WAKE_ENABLE_CONST)

    /* UART flow control: not applicable for CY_SCBIP_V0 || CY_SCBIP_V1 */
    #define SERIAL_CHECK_UART_RTS_CONTROL_FLOW    (SERIAL_SCB_MODE_UART_CONST_CFG && \
                                                             SERIAL_UART_RTS_ENABLE)

#endif /* End (SERIAL_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*       Type Definitions
***************************************/

/* SERIAL_SPI_INIT_STRUCT */
typedef struct
{
    uint32 mode;
    uint32 submode;
    uint32 sclkMode;
    uint32 oversample;
    uint32 enableMedianFilter;
    uint32 enableLateSampling;
    uint32 enableWake;
    uint32 rxDataBits;
    uint32 txDataBits;
    uint32 bitOrder;
    uint32 transferSeperation;
    uint32 rxBufferSize;
    uint8* rxBuffer;
    uint32 txBufferSize;
    uint8* txBuffer;
    uint32 enableInterrupt;
    uint32 rxInterruptMask;
    uint32 rxTriggerLevel;
    uint32 txInterruptMask;
    uint32 txTriggerLevel;
    uint8 enableByteMode;
    uint8 enableFreeRunSclk;
    uint8 polaritySs;
} SERIAL_SPI_INIT_STRUCT;

/* SERIAL_UART_INIT_STRUCT */
typedef struct
{
    uint32 mode;
    uint32 direction;
    uint32 dataBits;
    uint32 parity;
    uint32 stopBits;
    uint32 oversample;
    uint32 enableIrdaLowPower;
    uint32 enableMedianFilter;
    uint32 enableRetryNack;
    uint32 enableInvertedRx;
    uint32 dropOnParityErr;
    uint32 dropOnFrameErr;
    uint32 enableWake;
    uint32 rxBufferSize;
    uint8* rxBuffer;
    uint32 txBufferSize;
    uint8* txBuffer;
    uint32 enableMultiproc;
    uint32 multiprocAcceptAddr;
    uint32 multiprocAddr;
    uint32 multiprocAddrMask;
    uint32 enableInterrupt;
    uint32 rxInterruptMask;
    uint32 rxTriggerLevel;
    uint32 txInterruptMask;
    uint32 txTriggerLevel;
    uint8 enableByteMode;
    uint8 enableCts;
    uint8 ctsPolarity;
    uint8 rtsRxFifoLevel;
    uint8 rtsPolarity;
} SERIAL_UART_INIT_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

/* SPI specific functions */
#if(SERIAL_SCB_MODE_UNCONFIG_CONST_CFG)
    void SERIAL_SpiInit(const SERIAL_SPI_INIT_STRUCT *config);
#endif /* (SERIAL_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(SERIAL_SCB_MODE_SPI_INC)
    #define SERIAL_SpiIsBusBusy() ((uint32) (0u != (SERIAL_SPI_STATUS_REG & \
                                                              SERIAL_SPI_STATUS_BUS_BUSY)))

    #if (SERIAL_SPI_MASTER_CONST)
        void SERIAL_SpiSetActiveSlaveSelect(uint32 slaveSelect);
    #endif /*(SERIAL_SPI_MASTER_CONST) */

    #if !(SERIAL_CY_SCBIP_V0 || SERIAL_CY_SCBIP_V1)
        void SERIAL_SpiSetSlaveSelectPolarity(uint32 slaveSelect, uint32 polarity);
    #endif /* !(SERIAL_CY_SCBIP_V0 || SERIAL_CY_SCBIP_V1) */
#endif /* (SERIAL_SCB_MODE_SPI_INC) */

/* UART specific functions */
#if(SERIAL_SCB_MODE_UNCONFIG_CONST_CFG)
    void SERIAL_UartInit(const SERIAL_UART_INIT_STRUCT *config);
#endif /* (SERIAL_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(SERIAL_SCB_MODE_UART_INC)
    void SERIAL_UartSetRxAddress(uint32 address);
    void SERIAL_UartSetRxAddressMask(uint32 addressMask);

    /* UART RX direction APIs */
    #if(SERIAL_UART_RX_DIRECTION)
        uint32 SERIAL_UartGetChar(void);
        uint32 SERIAL_UartGetByte(void);

        #if !(SERIAL_CY_SCBIP_V0 || SERIAL_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void SERIAL_UartSetRtsPolarity(uint32 polarity);
            void SERIAL_UartSetRtsFifoLevel(uint32 level);
        #endif /* !(SERIAL_CY_SCBIP_V0 || SERIAL_CY_SCBIP_V1) */
    #endif /* (SERIAL_UART_RX_DIRECTION) */

    /* UART TX direction APIs */
    #if(SERIAL_UART_TX_DIRECTION)
        #define SERIAL_UartPutChar(ch)    SERIAL_SpiUartWriteTxData((uint32)(ch))
        void SERIAL_UartPutString(const char8 string[]);
        void SERIAL_UartPutCRLF(uint32 txDataByte);

        #if !(SERIAL_CY_SCBIP_V0 || SERIAL_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void SERIAL_UartEnableCts(void);
            void SERIAL_UartDisableCts(void);
            void SERIAL_UartSetCtsPolarity(uint32 polarity);
        #endif /* !(SERIAL_CY_SCBIP_V0 || SERIAL_CY_SCBIP_V1) */
    #endif /* (SERIAL_UART_TX_DIRECTION) */
#endif /* (SERIAL_SCB_MODE_UART_INC) */

/* Common APIs RX direction */
#if(SERIAL_RX_DIRECTION)
    uint32 SERIAL_SpiUartReadRxData(void);
    uint32 SERIAL_SpiUartGetRxBufferSize(void);
    void   SERIAL_SpiUartClearRxBuffer(void);
#endif /* (SERIAL_RX_DIRECTION) */

/* Common APIs TX direction */
#if(SERIAL_TX_DIRECTION)
    void   SERIAL_SpiUartWriteTxData(uint32 txData);
    void   SERIAL_SpiUartPutArray(const uint8 wrBuf[], uint32 count);
    uint32 SERIAL_SpiUartGetTxBufferSize(void);
    void   SERIAL_SpiUartClearTxBuffer(void);
#endif /* (SERIAL_TX_DIRECTION) */

CY_ISR_PROTO(SERIAL_SPI_UART_ISR);

#if(SERIAL_UART_RX_WAKEUP_IRQ)
    CY_ISR_PROTO(SERIAL_UART_WAKEUP_ISR);
#endif /* (SERIAL_UART_RX_WAKEUP_IRQ) */


/***************************************
*     Buffer Access Macro Definitions
***************************************/

#if(SERIAL_SCB_MODE_UNCONFIG_CONST_CFG)
    /* RX direction */
    void   SERIAL_PutWordInRxBuffer  (uint32 idx, uint32 rxDataByte);
    uint32 SERIAL_GetWordFromRxBuffer(uint32 idx);

    /* TX direction */
    void   SERIAL_PutWordInTxBuffer  (uint32 idx, uint32 txDataByte);
    uint32 SERIAL_GetWordFromTxBuffer(uint32 idx);

#else
    /* RX direction */
    #if(SERIAL_INTERNAL_RX_SW_BUFFER_CONST)
        #define SERIAL_PutWordInRxBuffer(idx, rxDataByte) \
                do{                                                 \
                    SERIAL_rxBufferInternal[(idx)] = ((uint8) (rxDataByte)); \
                }while(0)

        #define SERIAL_GetWordFromRxBuffer(idx) SERIAL_rxBufferInternal[(idx)]

    #endif /* (SERIAL_INTERNAL_RX_SW_BUFFER_CONST) */

    /* TX direction */
    #if(SERIAL_INTERNAL_TX_SW_BUFFER_CONST)
        #define SERIAL_PutWordInTxBuffer(idx, txDataByte) \
                    do{                                             \
                        SERIAL_txBufferInternal[(idx)] = ((uint8) (txDataByte)); \
                    }while(0)

        #define SERIAL_GetWordFromTxBuffer(idx) SERIAL_txBufferInternal[(idx)]

    #endif /* (SERIAL_INTERNAL_TX_SW_BUFFER_CONST) */

#endif /* (SERIAL_TX_SW_BUFFER_ENABLE) */


/***************************************
*         SPI API Constants
***************************************/

/* SPI sub mode enum */
#define SERIAL_SPI_MODE_MOTOROLA      (0x00u)
#define SERIAL_SPI_MODE_TI_COINCIDES  (0x01u)
#define SERIAL_SPI_MODE_TI_PRECEDES   (0x11u)
#define SERIAL_SPI_MODE_NATIONAL      (0x02u)
#define SERIAL_SPI_MODE_MASK          (0x03u)
#define SERIAL_SPI_MODE_TI_PRECEDES_MASK  (0x10u)
#define SERIAL_SPI_MODE_NS_MICROWIRE  (SERIAL_SPI_MODE_NATIONAL)

/* SPI phase and polarity mode enum */
#define SERIAL_SPI_SCLK_CPHA0_CPOL0   (0x00u)
#define SERIAL_SPI_SCLK_CPHA0_CPOL1   (0x02u)
#define SERIAL_SPI_SCLK_CPHA1_CPOL0   (0x01u)
#define SERIAL_SPI_SCLK_CPHA1_CPOL1   (0x03u)

/* SPI bits order enum */
#define SERIAL_BITS_ORDER_LSB_FIRST   (0u)
#define SERIAL_BITS_ORDER_MSB_FIRST   (1u)

/* SPI transfer separation enum */
#define SERIAL_SPI_TRANSFER_SEPARATED     (0u)
#define SERIAL_SPI_TRANSFER_CONTINUOUS    (1u)

/* SPI slave select constants */
#define SERIAL_SPI_SLAVE_SELECT0    (SERIAL_SCB__SS0_POSISTION)
#define SERIAL_SPI_SLAVE_SELECT1    (SERIAL_SCB__SS1_POSISTION)
#define SERIAL_SPI_SLAVE_SELECT2    (SERIAL_SCB__SS2_POSISTION)
#define SERIAL_SPI_SLAVE_SELECT3    (SERIAL_SCB__SS3_POSISTION)

/* SPI slave select polarity settings */
#define SERIAL_SPI_SS_ACTIVE_LOW  (0u)
#define SERIAL_SPI_SS_ACTIVE_HIGH (1u)


/***************************************
*         UART API Constants
***************************************/

/* UART sub-modes enum */
#define SERIAL_UART_MODE_STD          (0u)
#define SERIAL_UART_MODE_SMARTCARD    (1u)
#define SERIAL_UART_MODE_IRDA         (2u)

/* UART direction enum */
#define SERIAL_UART_RX    (1u)
#define SERIAL_UART_TX    (2u)
#define SERIAL_UART_TX_RX (3u)

/* UART parity enum */
#define SERIAL_UART_PARITY_EVEN   (0u)
#define SERIAL_UART_PARITY_ODD    (1u)
#define SERIAL_UART_PARITY_NONE   (2u)

/* UART stop bits enum */
#define SERIAL_UART_STOP_BITS_1   (2u)
#define SERIAL_UART_STOP_BITS_1_5 (3u)
#define SERIAL_UART_STOP_BITS_2   (4u)

/* UART IrDA low power OVS enum */
#define SERIAL_UART_IRDA_LP_OVS16     (16u)
#define SERIAL_UART_IRDA_LP_OVS32     (32u)
#define SERIAL_UART_IRDA_LP_OVS48     (48u)
#define SERIAL_UART_IRDA_LP_OVS96     (96u)
#define SERIAL_UART_IRDA_LP_OVS192    (192u)
#define SERIAL_UART_IRDA_LP_OVS768    (768u)
#define SERIAL_UART_IRDA_LP_OVS1536   (1536u)

/* Uart MP: mark (address) and space (data) bit definitions */
#define SERIAL_UART_MP_MARK       (0x100u)
#define SERIAL_UART_MP_SPACE      (0x000u)

/* UART CTS/RTS polarity settings */
#define SERIAL_UART_CTS_ACTIVE_LOW    (0u)
#define SERIAL_UART_CTS_ACTIVE_HIGH   (1u)
#define SERIAL_UART_RTS_ACTIVE_LOW    (0u)
#define SERIAL_UART_RTS_ACTIVE_HIGH   (1u)

/* Sources of RX errors */
#define SERIAL_INTR_RX_ERR        (SERIAL_INTR_RX_OVERFLOW    | \
                                             SERIAL_INTR_RX_UNDERFLOW   | \
                                             SERIAL_INTR_RX_FRAME_ERROR | \
                                             SERIAL_INTR_RX_PARITY_ERROR)

/* Shifted INTR_RX_ERR defines ONLY for SERIAL_UartGetByte() */
#define SERIAL_UART_RX_OVERFLOW       (SERIAL_INTR_RX_OVERFLOW << 8u)
#define SERIAL_UART_RX_UNDERFLOW      (SERIAL_INTR_RX_UNDERFLOW << 8u)
#define SERIAL_UART_RX_FRAME_ERROR    (SERIAL_INTR_RX_FRAME_ERROR << 8u)
#define SERIAL_UART_RX_PARITY_ERROR   (SERIAL_INTR_RX_PARITY_ERROR << 8u)
#define SERIAL_UART_RX_ERROR_MASK     (SERIAL_UART_RX_OVERFLOW    | \
                                                 SERIAL_UART_RX_UNDERFLOW   | \
                                                 SERIAL_UART_RX_FRAME_ERROR | \
                                                 SERIAL_UART_RX_PARITY_ERROR)


/***************************************
*     Vars with External Linkage
***************************************/

#if(SERIAL_SCB_MODE_UNCONFIG_CONST_CFG)
    extern const SERIAL_SPI_INIT_STRUCT  SERIAL_configSpi;
    extern const SERIAL_UART_INIT_STRUCT SERIAL_configUart;
#endif /* (SERIAL_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*    Specific SPI Macro Definitions
***************************************/

#define SERIAL_GET_SPI_INTR_SLAVE_MASK(sourceMask)  ((sourceMask) & SERIAL_INTR_SLAVE_SPI_BUS_ERROR)
#define SERIAL_GET_SPI_INTR_MASTER_MASK(sourceMask) ((sourceMask) & SERIAL_INTR_MASTER_SPI_DONE)
#define SERIAL_GET_SPI_INTR_RX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~SERIAL_INTR_SLAVE_SPI_BUS_ERROR)

#define SERIAL_GET_SPI_INTR_TX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~SERIAL_INTR_MASTER_SPI_DONE)


/***************************************
*    Specific UART Macro Definitions
***************************************/

#define SERIAL_UART_GET_CTRL_OVS_IRDA_LP(oversample) \
        ((SERIAL_UART_IRDA_LP_OVS16   == (oversample)) ? SERIAL_CTRL_OVS_IRDA_LP_OVS16 : \
         ((SERIAL_UART_IRDA_LP_OVS32   == (oversample)) ? SERIAL_CTRL_OVS_IRDA_LP_OVS32 : \
          ((SERIAL_UART_IRDA_LP_OVS48   == (oversample)) ? SERIAL_CTRL_OVS_IRDA_LP_OVS48 : \
           ((SERIAL_UART_IRDA_LP_OVS96   == (oversample)) ? SERIAL_CTRL_OVS_IRDA_LP_OVS96 : \
            ((SERIAL_UART_IRDA_LP_OVS192  == (oversample)) ? SERIAL_CTRL_OVS_IRDA_LP_OVS192 : \
             ((SERIAL_UART_IRDA_LP_OVS768  == (oversample)) ? SERIAL_CTRL_OVS_IRDA_LP_OVS768 : \
              ((SERIAL_UART_IRDA_LP_OVS1536 == (oversample)) ? SERIAL_CTRL_OVS_IRDA_LP_OVS1536 : \
                                                                          SERIAL_CTRL_OVS_IRDA_LP_OVS16)))))))

#define SERIAL_GET_UART_RX_CTRL_ENABLED(direction) ((0u != (SERIAL_UART_RX & (direction))) ? \
                                                                     (SERIAL_RX_CTRL_ENABLED) : (0u))

#define SERIAL_GET_UART_TX_CTRL_ENABLED(direction) ((0u != (SERIAL_UART_TX & (direction))) ? \
                                                                     (SERIAL_TX_CTRL_ENABLED) : (0u))


/***************************************
*        SPI Register Settings
***************************************/

#define SERIAL_CTRL_SPI      (SERIAL_CTRL_MODE_SPI)
#define SERIAL_SPI_RX_CTRL   (SERIAL_RX_CTRL_ENABLED)
#define SERIAL_SPI_TX_CTRL   (SERIAL_TX_CTRL_ENABLED)


/***************************************
*       SPI Init Register Settings
***************************************/

#define SERIAL_SPI_SS_POLARITY \
             (((uint32) SERIAL_SPI_SS0_POLARITY << SERIAL_SPI_SLAVE_SELECT0) | \
              ((uint32) SERIAL_SPI_SS1_POLARITY << SERIAL_SPI_SLAVE_SELECT1) | \
              ((uint32) SERIAL_SPI_SS2_POLARITY << SERIAL_SPI_SLAVE_SELECT2) | \
              ((uint32) SERIAL_SPI_SS3_POLARITY << SERIAL_SPI_SLAVE_SELECT3))

#if(SERIAL_SCB_MODE_SPI_CONST_CFG)

    /* SPI Configuration */
    #define SERIAL_SPI_DEFAULT_CTRL \
                    (SERIAL_GET_CTRL_OVS(SERIAL_SPI_OVS_FACTOR) | \
                     SERIAL_GET_CTRL_BYTE_MODE (SERIAL_SPI_BYTE_MODE_ENABLE) | \
                     SERIAL_GET_CTRL_EC_AM_MODE(SERIAL_SPI_WAKE_ENABLE)      | \
                     SERIAL_CTRL_SPI)

    #define SERIAL_SPI_DEFAULT_SPI_CTRL \
                    (SERIAL_GET_SPI_CTRL_CONTINUOUS    (SERIAL_SPI_TRANSFER_SEPARATION)       | \
                     SERIAL_GET_SPI_CTRL_SELECT_PRECEDE(SERIAL_SPI_SUB_MODE &                   \
                                                                  SERIAL_SPI_MODE_TI_PRECEDES_MASK)     | \
                     SERIAL_GET_SPI_CTRL_SCLK_MODE     (SERIAL_SPI_CLOCK_MODE)                | \
                     SERIAL_GET_SPI_CTRL_LATE_MISO_SAMPLE(SERIAL_SPI_LATE_MISO_SAMPLE_ENABLE) | \
                     SERIAL_GET_SPI_CTRL_SCLK_CONTINUOUS(SERIAL_SPI_FREE_RUN_SCLK_ENABLE)     | \
                     SERIAL_GET_SPI_CTRL_SSEL_POLARITY (SERIAL_SPI_SS_POLARITY)               | \
                     SERIAL_GET_SPI_CTRL_SUB_MODE      (SERIAL_SPI_SUB_MODE)                  | \
                     SERIAL_GET_SPI_CTRL_MASTER_MODE   (SERIAL_SPI_MODE))

    /* RX direction */
    #define SERIAL_SPI_DEFAULT_RX_CTRL \
                    (SERIAL_GET_RX_CTRL_DATA_WIDTH(SERIAL_SPI_RX_DATA_BITS_NUM)     | \
                     SERIAL_GET_RX_CTRL_BIT_ORDER (SERIAL_SPI_BITS_ORDER)           | \
                     SERIAL_GET_RX_CTRL_MEDIAN    (SERIAL_SPI_MEDIAN_FILTER_ENABLE) | \
                     SERIAL_SPI_RX_CTRL)

    #define SERIAL_SPI_DEFAULT_RX_FIFO_CTRL \
                    SERIAL_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(SERIAL_SPI_RX_TRIGGER_LEVEL)

    /* TX direction */
    #define SERIAL_SPI_DEFAULT_TX_CTRL \
                    (SERIAL_GET_TX_CTRL_DATA_WIDTH(SERIAL_SPI_TX_DATA_BITS_NUM) | \
                     SERIAL_GET_TX_CTRL_BIT_ORDER (SERIAL_SPI_BITS_ORDER)       | \
                     SERIAL_SPI_TX_CTRL)

    #define SERIAL_SPI_DEFAULT_TX_FIFO_CTRL \
                    SERIAL_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(SERIAL_SPI_TX_TRIGGER_LEVEL)

    /* Interrupt sources */
    #define SERIAL_SPI_DEFAULT_INTR_SPI_EC_MASK   (SERIAL_NO_INTR_SOURCES)

    #define SERIAL_SPI_DEFAULT_INTR_I2C_EC_MASK   (SERIAL_NO_INTR_SOURCES)
    #define SERIAL_SPI_DEFAULT_INTR_SLAVE_MASK \
                    (SERIAL_SPI_INTR_RX_MASK & SERIAL_INTR_SLAVE_SPI_BUS_ERROR)

    #define SERIAL_SPI_DEFAULT_INTR_MASTER_MASK \
                    (SERIAL_SPI_INTR_TX_MASK & SERIAL_INTR_MASTER_SPI_DONE)

    #define SERIAL_SPI_DEFAULT_INTR_RX_MASK \
                    (SERIAL_SPI_INTR_RX_MASK & (uint32) ~SERIAL_INTR_SLAVE_SPI_BUS_ERROR)

    #define SERIAL_SPI_DEFAULT_INTR_TX_MASK \
                    (SERIAL_SPI_INTR_TX_MASK & (uint32) ~SERIAL_INTR_MASTER_SPI_DONE)

#endif /* (SERIAL_SCB_MODE_SPI_CONST_CFG) */


/***************************************
*        UART Register Settings
***************************************/

#define SERIAL_CTRL_UART      (SERIAL_CTRL_MODE_UART)
#define SERIAL_UART_RX_CTRL   (SERIAL_RX_CTRL_LSB_FIRST) /* LSB for UART goes first */
#define SERIAL_UART_TX_CTRL   (SERIAL_TX_CTRL_LSB_FIRST) /* LSB for UART goes first */


/***************************************
*      UART Init Register Settings
***************************************/

#if(SERIAL_SCB_MODE_UART_CONST_CFG)

    /* UART configuration */
    #if(SERIAL_UART_MODE_IRDA == SERIAL_UART_SUB_MODE)

        #define SERIAL_DEFAULT_CTRL_OVS   ((0u != SERIAL_UART_IRDA_LOW_POWER) ?              \
                                (SERIAL_UART_GET_CTRL_OVS_IRDA_LP(SERIAL_UART_OVS_FACTOR)) : \
                                (SERIAL_CTRL_OVS_IRDA_OVS16))

    #else

        #define SERIAL_DEFAULT_CTRL_OVS   SERIAL_GET_CTRL_OVS(SERIAL_UART_OVS_FACTOR)

    #endif /* (SERIAL_UART_MODE_IRDA == SERIAL_UART_SUB_MODE) */

    #define SERIAL_UART_DEFAULT_CTRL \
                                (SERIAL_GET_CTRL_BYTE_MODE  (SERIAL_UART_BYTE_MODE_ENABLE)  | \
                                 SERIAL_GET_CTRL_ADDR_ACCEPT(SERIAL_UART_MP_ACCEPT_ADDRESS) | \
                                 SERIAL_DEFAULT_CTRL_OVS                                              | \
                                 SERIAL_CTRL_UART)

    #define SERIAL_UART_DEFAULT_UART_CTRL \
                                    (SERIAL_GET_UART_CTRL_MODE(SERIAL_UART_SUB_MODE))

    /* RX direction */
    #define SERIAL_UART_DEFAULT_RX_CTRL_PARITY \
                                ((SERIAL_UART_PARITY_NONE != SERIAL_UART_PARITY_TYPE) ?      \
                                  (SERIAL_GET_UART_RX_CTRL_PARITY(SERIAL_UART_PARITY_TYPE) | \
                                   SERIAL_UART_RX_CTRL_PARITY_ENABLED) : (0u))

    #define SERIAL_UART_DEFAULT_UART_RX_CTRL \
                    (SERIAL_GET_UART_RX_CTRL_MODE(SERIAL_UART_STOP_BITS_NUM)                    | \
                     SERIAL_GET_UART_RX_CTRL_POLARITY(SERIAL_UART_IRDA_POLARITY)                | \
                     SERIAL_GET_UART_RX_CTRL_MP_MODE(SERIAL_UART_MP_MODE_ENABLE)                | \
                     SERIAL_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(SERIAL_UART_DROP_ON_PARITY_ERR) | \
                     SERIAL_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(SERIAL_UART_DROP_ON_FRAME_ERR)   | \
                     SERIAL_UART_DEFAULT_RX_CTRL_PARITY)

    #define SERIAL_UART_DEFAULT_RX_CTRL \
                                (SERIAL_GET_RX_CTRL_DATA_WIDTH(SERIAL_UART_DATA_BITS_NUM)        | \
                                 SERIAL_GET_RX_CTRL_MEDIAN    (SERIAL_UART_MEDIAN_FILTER_ENABLE) | \
                                 SERIAL_GET_UART_RX_CTRL_ENABLED(SERIAL_UART_DIRECTION))

    #define SERIAL_UART_DEFAULT_RX_FIFO_CTRL \
                                SERIAL_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(SERIAL_UART_RX_TRIGGER_LEVEL)

    #define SERIAL_UART_DEFAULT_RX_MATCH_REG  ((0u != SERIAL_UART_MP_MODE_ENABLE) ?          \
                                (SERIAL_GET_RX_MATCH_ADDR(SERIAL_UART_MP_RX_ADDRESS) | \
                                 SERIAL_GET_RX_MATCH_MASK(SERIAL_UART_MP_RX_ADDRESS_MASK)) : (0u))

    /* TX direction */
    #define SERIAL_UART_DEFAULT_TX_CTRL_PARITY (SERIAL_UART_DEFAULT_RX_CTRL_PARITY)

    #define SERIAL_UART_DEFAULT_UART_TX_CTRL \
                                (SERIAL_GET_UART_TX_CTRL_MODE(SERIAL_UART_STOP_BITS_NUM)       | \
                                 SERIAL_GET_UART_TX_CTRL_RETRY_NACK(SERIAL_UART_RETRY_ON_NACK) | \
                                 SERIAL_UART_DEFAULT_TX_CTRL_PARITY)

    #define SERIAL_UART_DEFAULT_TX_CTRL \
                                (SERIAL_GET_TX_CTRL_DATA_WIDTH(SERIAL_UART_DATA_BITS_NUM) | \
                                 SERIAL_GET_UART_TX_CTRL_ENABLED(SERIAL_UART_DIRECTION))

    #define SERIAL_UART_DEFAULT_TX_FIFO_CTRL \
                                SERIAL_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(SERIAL_UART_TX_TRIGGER_LEVEL)

    #define SERIAL_UART_DEFAULT_FLOW_CTRL \
                        (SERIAL_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(SERIAL_UART_RTS_FIFO_LEVEL) | \
                         SERIAL_GET_UART_FLOW_CTRL_RTS_POLARITY (SERIAL_UART_RTS_POLARITY)   | \
                         SERIAL_GET_UART_FLOW_CTRL_CTS_POLARITY (SERIAL_UART_CTS_POLARITY)   | \
                         SERIAL_GET_UART_FLOW_CTRL_CTS_ENABLE   (SERIAL_UART_CTS_ENABLE))

    /* Interrupt sources */
    #define SERIAL_UART_DEFAULT_INTR_I2C_EC_MASK  (SERIAL_NO_INTR_SOURCES)
    #define SERIAL_UART_DEFAULT_INTR_SPI_EC_MASK  (SERIAL_NO_INTR_SOURCES)
    #define SERIAL_UART_DEFAULT_INTR_SLAVE_MASK   (SERIAL_NO_INTR_SOURCES)
    #define SERIAL_UART_DEFAULT_INTR_MASTER_MASK  (SERIAL_NO_INTR_SOURCES)
    #define SERIAL_UART_DEFAULT_INTR_RX_MASK      (SERIAL_UART_INTR_RX_MASK)
    #define SERIAL_UART_DEFAULT_INTR_TX_MASK      (SERIAL_UART_INTR_TX_MASK)

#endif /* (SERIAL_SCB_MODE_UART_CONST_CFG) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

#define SERIAL_SPIM_ACTIVE_SS0    (SERIAL_SPI_SLAVE_SELECT0)
#define SERIAL_SPIM_ACTIVE_SS1    (SERIAL_SPI_SLAVE_SELECT1)
#define SERIAL_SPIM_ACTIVE_SS2    (SERIAL_SPI_SLAVE_SELECT2)
#define SERIAL_SPIM_ACTIVE_SS3    (SERIAL_SPI_SLAVE_SELECT3)

#endif /* CY_SCB_SPI_UART_SERIAL_H */


/* [] END OF FILE */
