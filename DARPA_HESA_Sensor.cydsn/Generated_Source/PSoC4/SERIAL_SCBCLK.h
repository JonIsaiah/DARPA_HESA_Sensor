/*******************************************************************************
* File Name: SERIAL_SCBCLK.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_SERIAL_SCBCLK_H)
#define CY_CLOCK_SERIAL_SCBCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void SERIAL_SCBCLK_StartEx(uint32 alignClkDiv);
#define SERIAL_SCBCLK_Start() \
    SERIAL_SCBCLK_StartEx(SERIAL_SCBCLK__PA_DIV_ID)

#else

void SERIAL_SCBCLK_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void SERIAL_SCBCLK_Stop(void);

void SERIAL_SCBCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 SERIAL_SCBCLK_GetDividerRegister(void);
uint8  SERIAL_SCBCLK_GetFractionalDividerRegister(void);

#define SERIAL_SCBCLK_Enable()                         SERIAL_SCBCLK_Start()
#define SERIAL_SCBCLK_Disable()                        SERIAL_SCBCLK_Stop()
#define SERIAL_SCBCLK_SetDividerRegister(clkDivider, reset)  \
    SERIAL_SCBCLK_SetFractionalDividerRegister((clkDivider), 0u)
#define SERIAL_SCBCLK_SetDivider(clkDivider)           SERIAL_SCBCLK_SetDividerRegister((clkDivider), 1u)
#define SERIAL_SCBCLK_SetDividerValue(clkDivider)      SERIAL_SCBCLK_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define SERIAL_SCBCLK_DIV_ID     SERIAL_SCBCLK__DIV_ID

#define SERIAL_SCBCLK_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define SERIAL_SCBCLK_CTRL_REG   (*(reg32 *)SERIAL_SCBCLK__CTRL_REGISTER)
#define SERIAL_SCBCLK_DIV_REG    (*(reg32 *)SERIAL_SCBCLK__DIV_REGISTER)

#define SERIAL_SCBCLK_CMD_DIV_SHIFT          (0u)
#define SERIAL_SCBCLK_CMD_PA_DIV_SHIFT       (8u)
#define SERIAL_SCBCLK_CMD_DISABLE_SHIFT      (30u)
#define SERIAL_SCBCLK_CMD_ENABLE_SHIFT       (31u)

#define SERIAL_SCBCLK_CMD_DISABLE_MASK       ((uint32)((uint32)1u << SERIAL_SCBCLK_CMD_DISABLE_SHIFT))
#define SERIAL_SCBCLK_CMD_ENABLE_MASK        ((uint32)((uint32)1u << SERIAL_SCBCLK_CMD_ENABLE_SHIFT))

#define SERIAL_SCBCLK_DIV_FRAC_MASK  (0x000000F8u)
#define SERIAL_SCBCLK_DIV_FRAC_SHIFT (3u)
#define SERIAL_SCBCLK_DIV_INT_MASK   (0xFFFFFF00u)
#define SERIAL_SCBCLK_DIV_INT_SHIFT  (8u)

#else 

#define SERIAL_SCBCLK_DIV_REG        (*(reg32 *)SERIAL_SCBCLK__REGISTER)
#define SERIAL_SCBCLK_ENABLE_REG     SERIAL_SCBCLK_DIV_REG
#define SERIAL_SCBCLK_DIV_FRAC_MASK  SERIAL_SCBCLK__FRAC_MASK
#define SERIAL_SCBCLK_DIV_FRAC_SHIFT (16u)
#define SERIAL_SCBCLK_DIV_INT_MASK   SERIAL_SCBCLK__DIVIDER_MASK
#define SERIAL_SCBCLK_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_SERIAL_SCBCLK_H) */

/* [] END OF FILE */
