/*
* Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.
*
* Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
* the the People's Republic of China and other countries.
* All Allwinner Technology Co.,Ltd. trademarks are used with permission.
*
* DISCLAIMER
* THIRD PARTY LICENCES MAY BE REQUIRED TO IMPLEMENT THE SOLUTION/PRODUCT.
* IF YOU NEED TO INTEGRATE THIRD PARTY'S TECHNOLOGY (SONY, DTS, DOLBY, AVS OR MPEGLA, ETC.)
* IN ALLWINNERS'SDK OR PRODUCTS, YOU SHALL BE SOLELY RESPONSIBLE TO OBTAIN
* ALL APPROPRIATELY REQUIRED THIRD PARTY LICENCES.
* ALLWINNER SHALL HAVE NO WARRANTY, INDEMNITY OR OTHER OBLIGATIONS WITH RESPECT TO MATTERS
* COVERED UNDER ANY REQUIRED THIRD PARTY LICENSE.
* YOU ARE SOLELY RESPONSIBLE FOR YOUR USAGE OF THIRD PARTY'S TECHNOLOGY.
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

#ifndef __UART_SUN8IW20_H__
#define __UART_SUN8IW20_H__

#include <rtthread.h>

/* config for DSP */
#if defined(CONFIG_CORE_DSP0)
#include <interrupt.h>

#define SUNXI_CLK_UART0 CLK_BUS_UART0
#define SUNXI_RST_UART0 RST_BUS_UART0

#define SUNXI_CLK_UART1 CLK_BUS_UART1
#define SUNXI_RST_UART1 RST_BUS_UART1

#define SUNXI_CLK_UART2 CLK_BUS_UART2
#define SUNXI_RST_UART2 RST_BUS_UART2

#define SUNXI_CLK_UART3 CLK_BUS_UART3
#define SUNXI_RST_UART3 RST_BUS_UART3

#define SUNXI_IRQ_UART0		(RINTC_IRQ_MASK | 1)
#define SUNXI_IRQ_UART1		(RINTC_IRQ_MASK | 2)
#define SUNXI_IRQ_UART2		(RINTC_IRQ_MASK | 3)
#define SUNXI_IRQ_UART3		(RINTC_IRQ_MASK | 4)

#define SUNXI_UART0_BASE	(0x02500000)
#define SUNXI_UART1_BASE	(0x02500400)
#define SUNXI_UART2_BASE	(0x02500800)
#define SUNXI_UART3_BASE	(0x02500C00)

#define UART_FIFO_SIZE		(64)

#define UART0_GPIO_FUNCTION	(3)
#define UART1_GPIO_FUNCTION	(7)
#define UART2_GPIO_FUNCTION	(2)
#define UART3_GPIO_FUNCTION	(5)

#define UART0_TX		GPIOF(2)
#define UART0_RX		GPIOF(4)
#define UART1_TX		GPIOB(8)
#define UART1_RX		GPIOB(9)
#define UART2_TX		GPIOC(8)
#define UART2_RX		GPIOC(9)
#define UART3_TX		GPIOD(10)
#define UART3_RX		GPIOD(11)

#else

#define SUNXI_CLK_UART0 CLK_BUS_UART0;
#define SUNXI_RST_UART0 RST_BUS_UART0;

#define SUNXI_CLK_UART1 CLK_BUS_UART1;
#define SUNXI_RST_UART1 RST_BUS_UART1;

#define SUNXI_CLK_UART2 CLK_BUS_UART2;
#define SUNXI_RST_UART2 RST_BUS_UART2;

#define SUNXI_CLK_UART3 CLK_BUS_UART3;
#define SUNXI_RST_UART3 RST_BUS_UART3;

#define SUNXI_IRQ_UART0		(18)
#define SUNXI_IRQ_UART1		(19)
#define SUNXI_IRQ_UART2		(20)
#define SUNXI_IRQ_UART3		(21)
#define SUNXI_IRQ_UART4		(22)
#define SUNXI_IRQ_UART5		(23)


#define SUNXI_UART0_BASE	(0x02500000)
#define SUNXI_UART1_BASE	(0x02500400)
#define SUNXI_UART2_BASE	(0x02500800)
#define SUNXI_UART3_BASE	(0x02500c00)
#define SUNXI_UART4_BASE	(0x02501000)
#define SUNXI_UART5_BASE	(0x02501400)

//TODO:UART1~5 FIFO:256
#define UART_FIFO_SIZE		(64)

#define UART0_GPIO_FUNCTION	(6)
#define UART1_GPIO_FUNCTION	(6)
#define UART2_GPIO_FUNCTION	(6)
#define UART3_GPIO_FUNCTION	(6)

#ifdef BOARD_allwinnerd1
#define UART0_TX		GPIOB(8)
#define UART0_RX		GPIOB(9)
#elif defined(BOARD_allwinnerf133)
#define UART0_TX		GPIOE(2)
#define UART0_RX		GPIOE(3)
#endif
#define UART1_TX		GPIOB(10)
#define UART1_RX		GPIOB(11)
#define UART2_TX		GPIOL(8)
#define UART2_RX		GPIOL(9)
#define UART3_TX		GPIOL(8)
#define UART3_RX		GPIOL(9)

#endif /* CONFIG_CORE_DSP0 */

#endif /*__UART_SUN8IW20_H__  */