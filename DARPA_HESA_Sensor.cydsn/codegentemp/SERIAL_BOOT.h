/*******************************************************************************
* File Name: SERIAL_BOOT.h
* Version 3.0
*
* Description:
*  This file provides constants and parameter values of the bootloader
*  communication APIs for the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2014-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_BOOT_SERIAL_H)
#define CY_SCB_BOOT_SERIAL_H

#include "SERIAL_PVT.h"

#if (SERIAL_SCB_MODE_I2C_INC)
    #include "SERIAL_I2C.h"
#endif /* (SERIAL_SCB_MODE_I2C_INC) */

#if (SERIAL_SCB_MODE_EZI2C_INC)
    #include "SERIAL_EZI2C.h"
#endif /* (SERIAL_SCB_MODE_EZI2C_INC) */

#if (SERIAL_SCB_MODE_SPI_INC || SERIAL_SCB_MODE_UART_INC)
    #include "SERIAL_SPI_UART.h"
#endif /* (SERIAL_SCB_MODE_SPI_INC || SERIAL_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define SERIAL_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_SERIAL) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (SERIAL_SCB_MODE_I2C_INC)
    #define SERIAL_I2C_BTLDR_COMM_ENABLED     (SERIAL_BTLDR_COMM_ENABLED && \
                                                            (SERIAL_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             SERIAL_I2C_SLAVE_CONST))
#else
     #define SERIAL_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (SERIAL_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (SERIAL_SCB_MODE_EZI2C_INC)
    #define SERIAL_EZI2C_BTLDR_COMM_ENABLED   (SERIAL_BTLDR_COMM_ENABLED && \
                                                         SERIAL_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define SERIAL_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (SERIAL_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (SERIAL_SCB_MODE_SPI_INC)
    #define SERIAL_SPI_BTLDR_COMM_ENABLED     (SERIAL_BTLDR_COMM_ENABLED && \
                                                            (SERIAL_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             SERIAL_SPI_SLAVE_CONST))
#else
        #define SERIAL_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (SERIAL_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (SERIAL_SCB_MODE_UART_INC)
       #define SERIAL_UART_BTLDR_COMM_ENABLED    (SERIAL_BTLDR_COMM_ENABLED && \
                                                            (SERIAL_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (SERIAL_UART_RX_DIRECTION && \
                                                              SERIAL_UART_TX_DIRECTION)))
#else
     #define SERIAL_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (SERIAL_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define SERIAL_BTLDR_COMM_MODE_ENABLED    (SERIAL_I2C_BTLDR_COMM_ENABLED   || \
                                                     SERIAL_SPI_BTLDR_COMM_ENABLED   || \
                                                     SERIAL_EZI2C_BTLDR_COMM_ENABLED || \
                                                     SERIAL_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (SERIAL_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void SERIAL_I2CCyBtldrCommStart(void);
    void SERIAL_I2CCyBtldrCommStop (void);
    void SERIAL_I2CCyBtldrCommReset(void);
    cystatus SERIAL_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus SERIAL_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (SERIAL_SCB_MODE_I2C_CONST_CFG)
        #define SERIAL_CyBtldrCommStart   SERIAL_I2CCyBtldrCommStart
        #define SERIAL_CyBtldrCommStop    SERIAL_I2CCyBtldrCommStop
        #define SERIAL_CyBtldrCommReset   SERIAL_I2CCyBtldrCommReset
        #define SERIAL_CyBtldrCommRead    SERIAL_I2CCyBtldrCommRead
        #define SERIAL_CyBtldrCommWrite   SERIAL_I2CCyBtldrCommWrite
    #endif /* (SERIAL_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (SERIAL_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (SERIAL_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void SERIAL_EzI2CCyBtldrCommStart(void);
    void SERIAL_EzI2CCyBtldrCommStop (void);
    void SERIAL_EzI2CCyBtldrCommReset(void);
    cystatus SERIAL_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus SERIAL_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (SERIAL_SCB_MODE_EZI2C_CONST_CFG)
        #define SERIAL_CyBtldrCommStart   SERIAL_EzI2CCyBtldrCommStart
        #define SERIAL_CyBtldrCommStop    SERIAL_EzI2CCyBtldrCommStop
        #define SERIAL_CyBtldrCommReset   SERIAL_EzI2CCyBtldrCommReset
        #define SERIAL_CyBtldrCommRead    SERIAL_EzI2CCyBtldrCommRead
        #define SERIAL_CyBtldrCommWrite   SERIAL_EzI2CCyBtldrCommWrite
    #endif /* (SERIAL_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (SERIAL_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (SERIAL_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void SERIAL_SpiCyBtldrCommStart(void);
    void SERIAL_SpiCyBtldrCommStop (void);
    void SERIAL_SpiCyBtldrCommReset(void);
    cystatus SERIAL_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus SERIAL_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (SERIAL_SCB_MODE_SPI_CONST_CFG)
        #define SERIAL_CyBtldrCommStart   SERIAL_SpiCyBtldrCommStart
        #define SERIAL_CyBtldrCommStop    SERIAL_SpiCyBtldrCommStop
        #define SERIAL_CyBtldrCommReset   SERIAL_SpiCyBtldrCommReset
        #define SERIAL_CyBtldrCommRead    SERIAL_SpiCyBtldrCommRead
        #define SERIAL_CyBtldrCommWrite   SERIAL_SpiCyBtldrCommWrite
    #endif /* (SERIAL_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (SERIAL_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (SERIAL_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void SERIAL_UartCyBtldrCommStart(void);
    void SERIAL_UartCyBtldrCommStop (void);
    void SERIAL_UartCyBtldrCommReset(void);
    cystatus SERIAL_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus SERIAL_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (SERIAL_SCB_MODE_UART_CONST_CFG)
        #define SERIAL_CyBtldrCommStart   SERIAL_UartCyBtldrCommStart
        #define SERIAL_CyBtldrCommStop    SERIAL_UartCyBtldrCommStop
        #define SERIAL_CyBtldrCommReset   SERIAL_UartCyBtldrCommReset
        #define SERIAL_CyBtldrCommRead    SERIAL_UartCyBtldrCommRead
        #define SERIAL_CyBtldrCommWrite   SERIAL_UartCyBtldrCommWrite
    #endif /* (SERIAL_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (SERIAL_UART_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (SERIAL_BTLDR_COMM_ENABLED)
    #if (SERIAL_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void SERIAL_CyBtldrCommStart(void);
        void SERIAL_CyBtldrCommStop (void);
        void SERIAL_CyBtldrCommReset(void);
        cystatus SERIAL_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus SERIAL_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (SERIAL_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_SERIAL)
        #define CyBtldrCommStart    SERIAL_CyBtldrCommStart
        #define CyBtldrCommStop     SERIAL_CyBtldrCommStop
        #define CyBtldrCommReset    SERIAL_CyBtldrCommReset
        #define CyBtldrCommWrite    SERIAL_CyBtldrCommWrite
        #define CyBtldrCommRead     SERIAL_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_SERIAL) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (SERIAL_BTLDR_COMM_ENABLED) */


/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define SERIAL_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define SERIAL_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define SERIAL_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define SERIAL_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef SERIAL_SPI_BYTE_TO_BYTE
    #define SERIAL_SPI_BYTE_TO_BYTE   (160u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef SERIAL_UART_BYTE_TO_BYTE
    #define SERIAL_UART_BYTE_TO_BYTE  (2086u)
#endif /* SERIAL_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_SERIAL_H) */


/* [] END OF FILE */
