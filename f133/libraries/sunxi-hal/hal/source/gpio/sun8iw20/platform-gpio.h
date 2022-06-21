/*
* Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.
*
* Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
* the the People's Republic of China and other countries.
* All Allwinner Technology Co.,Ltd. trademarks are used with permission.
*
* DISCLAIMER
* THIRD PARTY LICENCES MAY BE REQUIRED TO IMPLEMENT THE SOLUTION/PRODUCT.
* IF YOU NEED TO INTEGRATE THIRD PARTY’S TECHNOLOGY (SONY, DTS, DOLBY, AVS OR MPEGLA, ETC.)
* IN ALLWINNERS’SDK OR PRODUCTS, YOU SHALL BE SOLELY RESPONSIBLE TO OBTAIN
* ALL APPROPRIATELY REQUIRED THIRD PARTY LICENCES.
* ALLWINNER SHALL HAVE NO WARRANTY, INDEMNITY OR OTHER OBLIGATIONS WITH RESPECT TO MATTERS
* COVERED UNDER ANY REQUIRED THIRD PARTY LICENSE.
* YOU ARE SOLELY RESPONSIBLE FOR YOUR USAGE OF THIRD PARTY’S TECHNOLOGY.
*
*
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

#ifndef __PLATFORM_GPIO_H__
#define __PLATFORM_GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

#define CONFIG_SOC_SUN20IW1 1

#define GPIO_MAX_BANK PG_BASE
#define BANK_BOUNDARY PL_BASE
#define SUNXI_GPIO_PBASE 0x02000000
#define SUNXI_GPIO_RES_SIZE 0x07FF

/* sunxi gpio irq*/
#if defined(CONFIG_CORE_DSP0) /* DSP */
#include <interrupt.h>
#define SUNXI_IRQ_GPIOB (RINTC_IRQ_MASK | 40)
#define SUNXI_IRQ_GPIOC (RINTC_IRQ_MASK | 42)
#define SUNXI_IRQ_GPIOD (RINTC_IRQ_MASK | 44)
#define SUNXI_IRQ_GPIOE (RINTC_IRQ_MASK | 46)
#define SUNXI_IRQ_GPIOF (RINTC_IRQ_MASK | 48)
#define SUNXI_IRQ_GPIOG (RINTC_IRQ_MASK | 50)
#elif defined(CONFIG_ARCH_SUN8IW20) /* ARM */
#define SUNXI_GIC_START 32
#define SUNXI_IRQ_GPIOB (SUNXI_GIC_START + 69)
#define SUNXI_IRQ_GPIOC (SUNXI_GIC_START + 71)
#define SUNXI_IRQ_GPIOD (SUNXI_GIC_START + 73)
#define SUNXI_IRQ_GPIOE (SUNXI_GIC_START + 75)
#define SUNXI_IRQ_GPIOF (SUNXI_GIC_START + 77)
#define SUNXI_IRQ_GPIOG (SUNXI_GIC_START + 79)
#elif defined(CONFIG_SOC_SUN20IW1) /* RISC-V */
#define SUNXI_IRQ_GPIOB (85)
#define SUNXI_IRQ_GPIOC (87)
#define SUNXI_IRQ_GPIOD (89)
#define SUNXI_IRQ_GPIOE (91)
#define SUNXI_IRQ_GPIOF (93)
#define SUNXI_IRQ_GPIOG (95)
#endif /* CONFIG_CORE_DSP0 */

typedef enum
{
    GPIO_PB0 = GPIOB(0),
    GPIO_PB1 = GPIOB(1),
    GPIO_PB2 = GPIOB(2),
    GPIO_PB3 = GPIOB(3),
    GPIO_PB4 = GPIOB(4),
    GPIO_PB5 = GPIOB(5),
    GPIO_PB6 = GPIOB(6),
    GPIO_PB7 = GPIOB(7),

    GPIO_PC0 = GPIOC(0),
    GPIO_PC1 = GPIOC(1),
    GPIO_PC2 = GPIOC(2),
    GPIO_PC3 = GPIOC(3),
    GPIO_PC4 = GPIOC(4),
    GPIO_PC5 = GPIOC(5),
    GPIO_PC6 = GPIOC(6),
    GPIO_PC7 = GPIOC(7),

    GPIO_PD0 = GPIOD(0),
    GPIO_PD1 = GPIOD(1),
    GPIO_PD2 = GPIOD(2),
    GPIO_PD3 = GPIOD(3),
    GPIO_PD4 = GPIOD(4),
    GPIO_PD5 = GPIOD(5),
    GPIO_PD6 = GPIOD(6),
    GPIO_PD7 = GPIOD(7),
    GPIO_PD8 = GPIOD(8),
    GPIO_PD9 = GPIOD(9),
    GPIO_PD10 = GPIOD(10),
    GPIO_PD11 = GPIOD(11),
    GPIO_PD12 = GPIOD(12),
    GPIO_PD13 = GPIOD(13),
    GPIO_PD14 = GPIOD(14),
    GPIO_PD15 = GPIOD(15),
    GPIO_PD16 = GPIOD(16),
    GPIO_PD17 = GPIOD(17),
    GPIO_PD18 = GPIOD(18),
    GPIO_PD19 = GPIOD(19),
    GPIO_PD20 = GPIOD(20),
    GPIO_PD21 = GPIOD(21),
    GPIO_PD22 = GPIOD(22),

    GPIO_PE0 = GPIOE(0),
    GPIO_PE1 = GPIOE(1),
    GPIO_PE2 = GPIOE(2),
    GPIO_PE3 = GPIOE(3),
    GPIO_PE4 = GPIOE(4),
    GPIO_PE5 = GPIOE(5),
    GPIO_PE6 = GPIOE(6),
    GPIO_PE7 = GPIOE(7),
    GPIO_PE8 = GPIOE(8),
    GPIO_PE9 = GPIOE(9),
    GPIO_PE10 = GPIOE(10),
    GPIO_PE11 = GPIOE(11),
    GPIO_PE12 = GPIOE(12),
    GPIO_PE13 = GPIOE(13),
    GPIO_PE14 = GPIOE(14),
    GPIO_PE15 = GPIOE(15),
    GPIO_PE16 = GPIOE(16),
    GPIO_PE17 = GPIOE(17),

    GPIO_PF0 = GPIOF(0),
    GPIO_PF1 = GPIOF(1),
    GPIO_PF2 = GPIOF(2),
    GPIO_PF3 = GPIOF(3),
    GPIO_PF4 = GPIOF(4),
    GPIO_PF5 = GPIOF(5),
    GPIO_PF6 = GPIOF(6),

    GPIO_PG0 = GPIOG(0),
    GPIO_PG1 = GPIOG(1),
    GPIO_PG2 = GPIOG(2),
    GPIO_PG3 = GPIOG(3),
    GPIO_PG4 = GPIOG(4),
    GPIO_PG5 = GPIOG(5),
    GPIO_PG6 = GPIOG(6),
    GPIO_PG7 = GPIOG(7),
    GPIO_PG8 = GPIOG(8),
    GPIO_PG9 = GPIOG(9),
    GPIO_PG10 = GPIOG(10),
    GPIO_PG11 = GPIOG(11),
    GPIO_PG12 = GPIOG(12),
    GPIO_PG13 = GPIOG(13),
    GPIO_PG14 = GPIOG(14),
    GPIO_PG15 = GPIOG(15),

    /* To aviod compile warnings. */
    GPIO_MAX = GPIOO(31),

} gpio_pin_t;

#ifdef __cplusplus
}
#endif
#endif /* __PLATFORM_GPIO_H__ */
