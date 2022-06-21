/* Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.

 * Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
 * the the People's Republic of China and other countries.
 * All Allwinner Technology Co.,Ltd. trademarks are used with permission.

 * DISCLAIMER
 * THIRD PARTY LICENCES MAY BE REQUIRED TO IMPLEMENT THE SOLUTION/PRODUCT.
 * IF YOU NEED TO INTEGRATE THIRD PARTY’S TECHNOLOGY (SONY, DTS, DOLBY, AVS OR MPEGLA, ETC.)
 * IN ALLWINNERS’SDK OR PRODUCTS, YOU SHALL BE SOLELY RESPONSIBLE TO OBTAIN
 * ALL APPROPRIATELY REQUIRED THIRD PARTY LICENCES.
 * ALLWINNER SHALL HAVE NO WARRANTY, INDEMNITY OR OTHER OBLIGATIONS WITH RESPECT TO MATTERS
 * COVERED UNDER ANY REQUIRED THIRD PARTY LICENSE.
 * YOU ARE SOLELY RESPONSIBLE FOR YOUR USAGE OF THIRD PARTY’S TECHNOLOGY.


 * THIS SOFTWARE IS PROVIDED BY ALLWINNER"AS IS" AND TO THE MAXIMUM EXTENT
 * PERMITTED BY LAW, ALLWINNER EXPRESSLY DISCLAIMS ALL WARRANTIES OF ANY KIND,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING WITHOUT LIMITATION REGARDING
 * THE TITLE, NON-INFRINGEMENT, ACCURACY, CONDITION, COMPLETENESS, PERFORMANCE
 * OR MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 * IN NO EVENT SHALL ALLWINNER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS, OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __HAL_MBUS_H
#define __HAL_MBUS_H

#include <stdio.h>

#define mbus_err(fmt, args...)  printf("%s()%d - "fmt, __func__, __LINE__, ##args)

/* MBUS PMU ids */
enum mbus_pmu {
	MBUS_PMU_CPU    = 0,    /* CPU bandwidth */
	MBUS_PMU_GPU,           /* GPU bandwidth */
	MBUS_PMU_VE,            /* VE */
	MBUS_PMU_DISP,          /* DISPLAY */
	MBUS_PMU_OTH,           /* other masters */
	MBUS_PMU_TOTAL,         /* total masters */
	MBUS_PMU_RV_SYS,        /* RV_SYS */
	MBUS_PMU_DE,            /* DE */
	MBUS_PMU_G2D,           /* G2D */
	MBUS_PMU_TVD,           /* TVD */
	MBUS_PMU_CSI,           /* CSI */
	MBUS_PMU_DSP_SYS,       /* DSP_SYS */
	MBUS_PMU_DI,            /* DI */
	MBUS_PMU_IOMMU,         /* IOMMU */
};

typedef enum{
	HAL_MBUS_STATUS_ERROR_PARAMETER = -3,
	HAL_MBUS_STATUS_ERROR_CHANNEL = -2,
	HAL_MBUS_STATUS_ERROR = -1,
	HAL_MBUS_STATUS_OK = 0
}hal_mbus_status_t;

hal_mbus_status_t hal_mbus_pmu_get_value(enum mbus_pmu type, unsigned int *value);
hal_mbus_status_t hal_mbus_pmu_enable(void);


#endif
