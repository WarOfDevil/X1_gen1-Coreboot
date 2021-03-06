/* -*- mode:c -*-
 *
 * Copyright 2018 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/* Declare symbolic names for all the GPIOs that we care about.
 * Note: Those with interrupt handlers must be declared first. */

/* Wake Source interrupts */
GPIO_INT(LID_OPEN,	 PIN(D, 2), GPIO_INT_BOTH |
				    GPIO_HIB_WAKE_HIGH, lid_interrupt)
GPIO_INT(POWER_BUTTON_L, PIN(0, 1), GPIO_INT_BOTH, power_button_interrupt)	/* EC_PWR_BTN_ODL */
GPIO_INT(AC_PRESENT, 	 PIN(0, 0), GPIO_INT_BOTH | GPIO_HIB_WAKE_HIGH, extpower_interrupt)		/* ACOK_OD */

/*
 * Active = Low, Off = High for HGDEDM GMR sensor,
 * (b/79779455) rename TABLET_MODE to TABLET_MODE_L in schematics
 */
GPIO_INT(TABLET_MODE_L,	PIN(8, 6), GPIO_INT_BOTH, tablet_mode_isr)

/* USB-C interrupts */
GPIO_INT(USB_C0_PD_INT_ODL, PIN(6, 1), GPIO_INT_FALLING, tcpc_alert_event)
GPIO_INT(USB_C1_PD_INT_ODL, PIN(F, 5), GPIO_INT_FALLING, tcpc_alert_event)
GPIO_INT(USB_PD_C0_INT_L,   PIN(E, 0), GPIO_INT_FALLING, ppc_interrupt)
GPIO_INT(USB_PD_C1_INT_L,   PIN(F, 1), GPIO_INT_FALLING, ppc_interrupt)

/* Power State interrupts */
#ifdef CONFIG_POWER_S0IX
GPIO_INT(PCH_SLP_S0_L,	 PIN(A, 4), GPIO_INT_BOTH, power_signal_interrupt)	/* SLP_S0_L */
#endif
GPIO_INT(PCH_SLP_S4_L,	 PIN(A, 3), GPIO_INT_BOTH, power_signal_interrupt)	/* SLP_S4_L */
GPIO_INT(PCH_SLP_S3_L,	 PIN(A, 6), GPIO_INT_BOTH, power_signal_interrupt)	/* SLP_S3_L */
GPIO_INT(SUSPWRDNACK,	 PIN(D, 5), GPIO_INT_BOTH, power_signal_interrupt)	/* SUSPWRDNACK */
GPIO_INT(RSMRST_L_PGOOD, PIN(E, 2), GPIO_INT_BOTH, power_signal_interrupt)	/* PMIC_EC_RSMRST_ODL */
GPIO_INT(ALL_SYS_PGOOD,	 PIN(F, 4), GPIO_INT_BOTH, power_signal_interrupt)	/* PMIC_EC_PWROK_OD */

/* Other interrupts */
GPIO_INT(WP_L,		 PIN(A, 1), GPIO_INT_BOTH, switch_interrupt)		/* EC_WP_ODL */

/* TODO(b/74932344): Make it as an interrupt after driver supports this */
GPIO(BASE_SIXAXIS_INT_L,	PIN(5, 6), GPIO_INPUT | GPIO_SEL_1P8V)
GPIO(LID_ACCEL_INT_L,		PIN(5, 0), GPIO_INPUT | GPIO_SEL_1P8V)

/* Define PCH_SLP_S0_L after all interrupts if CONFIG_POWER_S0IX not defined. */
#ifndef CONFIG_POWER_S0IX
GPIO(PCH_SLP_S0_L,	 PIN(A, 4), GPIO_INPUT)		/* SLP_S0_L */
#endif

/*
 * PLT_RST_L isn't used since there is a Virtual Wire on eSPI for it. It is here
 * only for debugging purposes.
 */
GPIO(PLT_RST_L,		 PIN(C, 7), GPIO_INPUT)		/* Platform Reset from SoC */
GPIO(SYS_RESET_L,	 PIN(0, 2), GPIO_ODR_HIGH)	/* SYS_RST_ODL */

GPIO(ENTERING_RW,	 PIN(8, 0), GPIO_OUT_LOW)	/* EC_ENTERING_RW */
GPIO(PCH_WAKE_L,	 PIN(7, 4), GPIO_ODR_HIGH)	/* EC_PCH_WAKE_ODL */
GPIO(PCH_PWRBTN_L,	 PIN(C, 1), GPIO_ODR_HIGH)	/* GPIO_PCH_PWRBTN_L */

GPIO(EN_PP5000,		 PIN(7, 3), GPIO_OUT_LOW)	/* EN_PP5000_A */
GPIO(PP5000_PG,		 PIN(C, 0), GPIO_INPUT)		/* PP5000_PG_OD */
GPIO(EN_PP3300,		 PIN(D, 4), GPIO_OUT_LOW)	/* EN_PP3300_A */
GPIO(PP3300_PG,		 PIN(6, 0), GPIO_INPUT)		/* PP3300_PG_OD */
GPIO(PMIC_EN,		 PIN(7, 2), GPIO_OUT_LOW)	/* Enable A Rails via PMIC */
GPIO(PCH_RSMRST_L,	 PIN(C, 2), GPIO_OUT_LOW)	/* RSMRST# to SOC. All _A rails now up. */
GPIO(PCH_SYS_PWROK,	 PIN(B, 7), GPIO_OUT_LOW)	/* EC_PCH_PWROK. All S0 rails now up. */

/* Peripheral rails */
GPIO(ENABLE_BACKLIGHT,		PIN(D, 3), GPIO_ODR_HIGH |
					   GPIO_SEL_1P8V)	/* EC_BL_EN_OD */
GPIO(EN_P3300_TRACKPAD_ODL,	PIN(3, 3), GPIO_ODR_HIGH)

GPIO(EC_BATT_PRES_L, 	 PIN(E, 5), GPIO_INPUT)

/*
 * PCH_PROCHOT_ODL is primarily for monitoring the PROCHOT# signal which is
 * normally driven by the PMIC. The EC can also drive this signal in the event
 * that the ambient or charger temperature sensors exceeds their thresholds.
 */
GPIO(CPU_PROCHOT,	 PIN(3, 7), GPIO_INPUT | GPIO_SEL_1P8V)	/* PCH_PROCHOT_ODL */

/* I2C pins - Alternate function below configures I2C module on these pins */
GPIO(I2C0_SCL,		 PIN(B, 5), GPIO_INPUT)		/* EC_I2C_BATTERY_3V3_SCL */
GPIO(I2C0_SDA,		 PIN(B, 4), GPIO_INPUT)		/* EC_I2C_BATTERY_3V3_SDA */
GPIO(I2C1_SCL,		 PIN(9, 0), GPIO_INPUT)		/* EC_I2C_USB_C0_PD_SCL */
GPIO(I2C1_SDA,		 PIN(8, 7), GPIO_INPUT)		/* EC_I2C_USB_C0_PD_SDA */
GPIO(I2C2_SCL,		 PIN(9, 2), GPIO_INPUT)		/* EC_I2C_USB_C1_PD_SCL */
GPIO(I2C2_SDA,		 PIN(9, 1), GPIO_INPUT)		/* EC_I2C_USB_C1_PD_SDA */
GPIO(I2C3_SCL,		 PIN(D, 1), GPIO_INPUT)		/* EC_I2C_EEPROM_SCL */
GPIO(I2C3_SDA,		 PIN(D, 0), GPIO_INPUT)		/* EC_I2C_EEPROM_SDA */
GPIO(I2C4_SCL,		 PIN(F, 3), GPIO_INPUT)		/* EC_I2C_CHARGER_3V3_SCL */
GPIO(I2C4_SDA,		 PIN(F, 2), GPIO_INPUT)		/* EC_I2C_CHARGER_3V3_SDA */
GPIO(I2C7_SCL,		 PIN(B, 3), GPIO_INPUT |
				    GPIO_SEL_1P8V)	/* EC_I2C_SENSOR_U_SCL */
GPIO(I2C7_SDA,		 PIN(B, 2), GPIO_INPUT |
				    GPIO_SEL_1P8V)	/* EC_I2C_SENSOR_U_SDA */

/* USB pins */
GPIO(EN_USB_A_5V,	 PIN(6, 7), GPIO_OUT_LOW)	/* Enable A0/A1 5V Charging */
/* OTG pin -  This pin will be changed to PIN(8,3) in Proto 2*/
GPIO(USB2_OTG_ID,	 PIN(A, 0), GPIO_OUT_LOW)	/* OTG ID */
GPIO(USB_A_CHARGE_EN_L,	 PIN(A, 2), GPIO_OUT_HIGH)	/* Enable A0/A1 1.5A Charging */
/* TODO(b/74254366): Break out A1 signals once they are there in HW */
/* USB_C0_PD_RST_L isn't connected to PIN(6,2) since ANX TCPC doesn't have reset */
GPIO(USB_C0_BC12_VBUS_ON,   PIN(6, 3), GPIO_OUT_LOW)	/* C0 BC1.2 Power */
GPIO(USB_C0_BC12_CHG_DET_L, PIN(9, 5), GPIO_INPUT)	/* C0 BC1.2 Detect */
GPIO(USB_C0_HPD_1V8_ODL, PIN(C, 5), GPIO_INPUT |	/* C0 DP Hotplug Detect */
				    GPIO_SEL_1P8V)
GPIO(USB_C1_PD_RST_ODL,	 PIN(7, 0), GPIO_ODR_HIGH)	/* C1 PD Reset */
GPIO(EN_USB_C1_5V_OUT,	 PIN(0, 3), GPIO_OUT_LOW)	/* C1 Source 5V */
GPIO(USB_C1_CHARGE_ON,	 PIN(4, 0), GPIO_OUT_LOW)	/* C1 Accept input voltage*/
GPIO(USB_C1_BC12_VBUS_ON,   PIN(B, 1), GPIO_OUT_LOW)	/* C1 BC1.2 Power */
GPIO(USB_C1_BC12_CHG_DET_L, PIN(E, 4), GPIO_INPUT)	/* C1 BC1.2 Detect */
GPIO(USB_C1_HPD_1V8_ODL, PIN(C, 6), GPIO_INPUT |	/* C1 DP Hotplug Detect */
				    GPIO_SEL_1P8V)

/* LED */
GPIO(BAT_LED_ORANGE_L,		PIN(C, 3), GPIO_OUT_HIGH)	/* LED_1_L */
GPIO(BAT_LED_BLUE_L,		PIN(C, 4), GPIO_OUT_HIGH)	/* LED_2_L */

/* Keyboard pins */
ALTERNATE(PIN_MASK(3, 0x03), 0, MODULE_KEYBOARD_SCAN, GPIO_INPUT)	/* KSI_00-01 */
ALTERNATE(PIN_MASK(2, 0xFC), 0, MODULE_KEYBOARD_SCAN, GPIO_INPUT)	/* KSI_02-07 */
ALTERNATE(PIN_MASK(2, 0x03), 0, MODULE_KEYBOARD_SCAN, GPIO_ODR_HIGH)	/* KSO_00-01 */
ALTERNATE(PIN_MASK(1, 0x7F), 0, MODULE_KEYBOARD_SCAN, GPIO_ODR_HIGH)	/* KSO_03-09 */
ALTERNATE(PIN_MASK(0, 0xE0), 0, MODULE_KEYBOARD_SCAN, GPIO_ODR_HIGH)	/* KSO_10-12 */
GPIO(KBD_KSO2, PIN(1, 7), GPIO_OUT_LOW)	/* KSO_02 inverted */

/* Alternate functions GPIO definitions */
/* Cr50 requires no pull-ups on UART pins. */
ALTERNATE(PIN_MASK(6, 0x30), 0, MODULE_UART, 0)		/* UART from EC to Servo */
ALTERNATE(PIN_MASK(B, 0x30), 0, MODULE_I2C, 0)		/* I2C0 */
ALTERNATE(PIN_MASK(9, 0x07), 0, MODULE_I2C, 0)		/* I2C1 SCL / I2C2 */
ALTERNATE(PIN_MASK(8, 0x80), 0, MODULE_I2C, 0)		/* I2C1 SDA */
ALTERNATE(PIN_MASK(D, 0x03), 0, MODULE_I2C, 0)		/* I2C3 */
ALTERNATE(PIN_MASK(F, 0x0C), 0, MODULE_I2C, 0)		/* I2C4 */
ALTERNATE(PIN_MASK(B, 0x0C), 0, MODULE_I2C, 0)		/* I2C7 */
ALTERNATE(PIN_MASK(4, 0x30), 0, MODULE_ADC, 0)		/* ADC0-1 */
ALTERNATE(PIN_MASK(4, 0x02), 0, MODULE_ADC, 0)		/* ADC4: ADC_USB_C0_VBUS */
ALTERNATE(PIN_MASK(F, 0x01), 0, MODULE_ADC, 0)		/* ADC9: ADC_USB_C1_VBUS */
