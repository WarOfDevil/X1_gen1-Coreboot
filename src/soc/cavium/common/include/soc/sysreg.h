/*
 * This file is part of the coreboot project.
 *
 * Copyright 2018-present  Facebook, Inc.
 * Copyright (c) 2003-2017  Cavium Inc. (support@cavium.com). All rights
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; version 2 of
 * the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#ifndef __SOC_CAVIUM_COMMON_INCLUDE_SOC_SYSREG_H
#define __SOC_CAVIUM_COMMON_INCLUDE_SOC_SYSREG_H

/* TODO: add CVMCTL_EL1 */

#define AP_CVMMEMCTL0_EL1_NODE_SHIFT		61
#define AP_CVMMEMCTL0_EL1_NODE_MASK		0x3
#define AP_CVMMEMCTL0_EL1_STEXFAILCNT_SHIFT	58
#define AP_CVMMEMCTL0_EL1_STEXFAILCNT_MASK	0x7
#define AP_CVMMEMCTL0_EL1_WFELDEX1DIS		(1 << 57)
#define AP_CVMMEMCTL0_EL1_STLSTALLFORCE		(1 << 56)
#define AP_CVMMEMCTL0_EL1_DMBSTALLFORCE		(1 << 55)
#define AP_CVMMEMCTL0_EL1_TLBINOPDIS		(1 << 54)
#define AP_CVMMEMCTL0_EL1_TLBIICFLUSH		(1 << 53)
#define AP_CVMMEMCTL0_EL1_GSYNCTO_SHIFT		48
#define AP_CVMMEMCTL0_EL1_GSYNCTO_MASK		0x1f
#define AP_CVMMEMCTL0_EL1_UTLBFILLBYPDIS	(1 << 47)
#define AP_CVMMEMCTL0_EL1_TLBIALL		(1 << 46)
#define AP_CVMMEMCTL0_EL1_WBFDSBFLUSHALL	(1 << 45)
#define AP_CVMMEMCTL0_EL1_WBFDMBFLUSHNEXT	(1 << 44)
#define AP_CVMMEMCTL0_EL1_STEXL2CFORCE		(1 << 43)
#define AP_CVMMEMCTL0_EL1_WCUMISSFORCE		(1 << 41)
#define AP_CVMMEMCTL0_EL1_REPLAYPREFDIS		(1 << 40)
#define AP_CVMMEMCTL0_EL1_ZVAL2CDIS		(1 << 39)
#define AP_CVMMEMCTL0_EL1_LDIL2CDIS		(1 << 38)
#define AP_CVMMEMCTL0_EL1_DVCA47		(1 << 37)
#define AP_CVMMEMCTL0_EL1_STPREFDIS		(1 << 36)
#define AP_CVMMEMCTL0_EL1_LDPREFDIS		(1 << 35)
#define AP_CVMMEMCTL0_EL1_WFILDEXDIS		(1 << 34)
#define AP_CVMMEMCTL0_EL1_WFITO_SHIFT		31
#define AP_CVMMEMCTL0_EL1_WFITO_MASK		0x7
#define AP_CVMMEMCTL0_EL1_RBFSHORTTO_SHIFT	26
#define AP_CVMMEMCTL0_EL1_RBFSHORTTO_MASK	0x1f
#define AP_CVMMEMCTL0_EL1_RBFTO_SHIFT		21
#define AP_CVMMEMCTL0_EL1_RBFTO_MASK		0x1f
#define AP_CVMMEMCTL0_EL1_WBFALLBARRIER		(1 << 20)
#define AP_CVMMEMCTL0_EL1_WBFNOMERGE		(1 << 19)
#define AP_CVMMEMCTL0_EL1_WBFTONSHENA		(1 << 18)
#define AP_CVMMEMCTL0_EL1_WBFTOMRGCLRENA	(1 << 17)
#define AP_CVMMEMCTL0_EL1_WBFTO_SHIFT		12
#define AP_CVMMEMCTL0_EL1_WBFTO_MASK		0x1f
#define AP_CVMMEMCTL0_EL1_WBFTHRESH_SHIFT	7
#define AP_CVMMEMCTL0_EL1_WBFTHRESH_MASK	0x1f
#define AP_CVMMEMCTL0_EL1_UTLBENTRIESM1_SHIFT	2
#define AP_CVMMEMCTL0_EL1_UTLBENTRIESM1_MASK	0x1f
#define AP_CVMMEMCTL0_EL1_CCLKFORCE		(1 << 1)
#define AP_CVMMEMCTL0_EL1_MCLKFORCE		(1 << 0)

#endif	/* __SOC_CAVIUM_COMMON_INCLUDE_SOC_SYSREG_H */
