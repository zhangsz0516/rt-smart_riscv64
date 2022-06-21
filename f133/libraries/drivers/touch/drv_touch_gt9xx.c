/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-02-08     Zhangyihong  the first version
 * 2018-04-03     XY           gt9xx for 1024 * 600
 * 2018-04-14     liu2guang    optimize int and rst to pin framework
 * 2017-08-08     XY           imxrt1052
 * 2018-10-29     XY
 */

#include "drv_touch.h"
// #include "tcon.h"
#include "drv_lcd.h"
#include "string.h"
#include "drv_pin.h"
// #include "drv_gpio.h"

#define DBG_TAG  "TOUCH.gt9xx"
#define DBG_LVL  DBG_LOG
#include <rtdbg.h>

// extern tcon_panel_t _panel;

#define TP_INT_PIN GET_PIN(GPIO_PORT_E, GPIO_PIN_10)       /* GPIO_PORT_E GPIO_PIN_10 */
#define TP_RST_PIN GET_PIN(GPIO_PORT_E, GPIO_PIN_11)       /* GPIO_PORT_E GPIO_PIN_11 */

#ifndef TP_INT_PIN
#error "Please config touch panel INT pin."
#endif
#ifndef TP_RST_PIN
#error "Please config touch panel RST pin."
#endif

#ifndef IIC_RETRY_NUM
#define IIC_RETRY_NUM 2
#endif

/* Either 0x5D or 0x14 could be used as the address */
#define GT9xx_TS_ADDR1              (0x14)
#define GT9xx_TS_ADDR2              (0x5D)
static uint8_t GT9xx_TS_ADDR = GT9xx_TS_ADDR1;

#define gt9xx_READ_XY_REG           (0x814E)    /* 坐标寄存器       */
#define gt9xx_CLEARBUF_REG          (0x814E)    /* 清除坐标寄存器   */
#define gt9xx_CONFIG_REG            (0x8047)    /* 配置参数寄存器   */
#define gt9xx_COMMAND_REG           (0x8040)    /* 实时命令         */
#define gt9xx_PRODUCT_ID_REG        (0x8140)    /* 产品ID           */
#define gt9xx_VENDOR_ID_REG         (0x814A)    /* 当前模组选项信息 */
#define gt9xx_CONFIG_VERSION_REG    (0x8047)    /* 配置文件版本号   */
#define gt9xx_CONFIG_CHECKSUM_REG   (0x80FF)    /* 配置文件校验码   */
#define gt9xx_FIRMWARE_VERSION_REG  (0x8144)    /* 固件版本号       */

static struct touch_driver gt9xx_driver;

void gt9xx_hw_reset(rt_uint8_t address)
{
    rt_tick_t delay = rt_tick_from_millisecond(30);

    rt_pin_mode(TP_RST_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(TP_INT_PIN, PIN_MODE_OUTPUT);

    // // powerup timing
    // rt_pin_write(TP_RST_PIN, PIN_LOW);
    // rt_pin_write(TP_INT_PIN, PIN_LOW);
    // rt_thread_mdelay(15);
    // rt_pin_write(TP_RST_PIN, PIN_HIGH);
    // rt_thread_mdelay(10);

    if (address == 0x5D)
    {
        rt_pin_write(TP_RST_PIN, PIN_LOW);
        rt_pin_write(TP_INT_PIN, PIN_LOW);
        rt_thread_delay(delay);
        rt_pin_write(TP_RST_PIN, PIN_HIGH);
        rt_pin_write(TP_INT_PIN, PIN_LOW);
        rt_thread_delay(delay);
        rt_pin_write(TP_INT_PIN, PIN_LOW);
        rt_thread_delay(delay);
        rt_pin_write(TP_INT_PIN, PIN_HIGH);
    }
    else
    {
        rt_pin_write(TP_RST_PIN, PIN_LOW);
        rt_pin_write(TP_INT_PIN, PIN_HIGH);
        rt_thread_delay(delay);
        rt_pin_write(TP_RST_PIN, PIN_HIGH);
        rt_pin_write(TP_INT_PIN, PIN_HIGH);
        rt_thread_delay(delay);
        rt_pin_write(TP_INT_PIN, PIN_LOW);
        rt_thread_delay(delay);
        rt_pin_write(TP_INT_PIN, PIN_HIGH);
    }

    rt_thread_mdelay(5);    /* more than 5ms */
}

static rt_bool_t gt9xx_probe(struct rt_i2c_bus_device *i2c_bus)
{
    rt_uint8_t cmd[2];
    rt_uint8_t buffer[5] = {0};

    rt_kprintf("gt9xx_probe\n");

    GT9xx_TS_ADDR = GT9xx_TS_ADDR1;
    gt9xx_hw_reset(GT9xx_TS_ADDR);
    rt_thread_delay(RT_TICK_PER_SECOND / 5);

    cmd[0] = (rt_uint8_t)((gt9xx_PRODUCT_ID_REG >> 8) & 0xFF);
    cmd[1] = (rt_uint8_t)(gt9xx_PRODUCT_ID_REG & 0xFF);
    if (rt_touch_read(GT9xx_TS_ADDR1, &cmd, 2, buffer, 4) != 0)
    {
        if (rt_touch_read(GT9xx_TS_ADDR2, &cmd, 2, buffer, 4) != 0)
        {
            LOG_E("Failed to fetch GT9XX ID at the address 0x%x/0x%x", GT9xx_TS_ADDR1, GT9xx_TS_ADDR2);
            return RT_FALSE;
        }
        GT9xx_TS_ADDR = GT9xx_TS_ADDR2;
    }

    buffer[4] = '\0';

    LOG_D("%#X %#X %#X %#X %#X", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);

    if(!rt_strcmp((const char*)buffer, "911"))
    {
        LOG_I("Found chip gt911");
        return RT_TRUE;
    }
    else if(!rt_strcmp((const char*)buffer, "928"))
    {
        LOG_I("Found chip gt928");
        return RT_TRUE;
    }
    else if(!rt_strcmp((const char*)buffer, "9147"))
    {
        LOG_I("Found chip gt9147");
        return RT_TRUE;
    }
    else if(!rt_strcmp((const char*)buffer, "9157"))
    {
        LOG_I("Found chip gt9157");
        return RT_TRUE;
    }
    else
    {
        LOG_E("Uknow chip gt9xx device: [%s]", buffer);
    }

    return RT_FALSE;
}

static void gt9xx_init(struct rt_i2c_bus_device *i2c_bus)
{
    rt_uint8_t buf = 0;
    rt_uint8_t cmd[2];

    gt9xx_driver.isr_sem = rt_sem_create("gt9xx", 0, RT_IPC_FLAG_FIFO);
    RT_ASSERT(gt9xx_driver.isr_sem);

    cmd[0] = (rt_uint8_t)((gt9xx_CONFIG_VERSION_REG >> 8) & 0xFF);
    cmd[1] = (rt_uint8_t)(gt9xx_CONFIG_VERSION_REG & 0xFF);
    rt_touch_read(GT9xx_TS_ADDR, &cmd, 2, &buf, 1);
    LOG_I("GT9xx Config version: 0x%02X", buf);

    cmd[0] = (rt_uint8_t)((gt9xx_VENDOR_ID_REG >> 8) & 0xFF);
    cmd[1] = (rt_uint8_t)(gt9xx_VENDOR_ID_REG & 0xFF);
    rt_touch_read(GT9xx_TS_ADDR, &cmd, 2, &buf, 1);
    LOG_I("GT9xx Sensor id: 0x%02X", buf);

    rt_sem_release(gt9xx_driver.isr_sem);
}

static void gt9xx_deinit(void)
{
    rt_sem_delete(gt9xx_driver.isr_sem);
}

static rt_err_t gt9xx_read_point(touch_message_t msg)
{
    rt_uint8_t cmd[2];
    rt_uint8_t buf[8] = {0};
    static rt_uint8_t s_tp_down = 0;

    static rt_uint8_t last_buf[8] = {0};

    cmd[0] = (rt_uint8_t)((gt9xx_READ_XY_REG >> 8) & 0xFF);
    cmd[1] = (rt_uint8_t)(gt9xx_READ_XY_REG & 0xFF);
    rt_touch_read(GT9xx_TS_ADDR, &cmd, 2, buf, 8);

    /* software debounce */
    if (last_buf[0] != buf[0])
    {
        msg->event = TOUCH_EVENT_NONE;
    }
    else if ((buf[0] & 0x01) == 0)
    {
        if (s_tp_down)
        {
            s_tp_down = 0;
            msg->event = TOUCH_EVENT_UP;
        }
        else
        {
            msg->event = TOUCH_EVENT_NONE;
        }
    }
    else
    {
#if 1
        msg->x = ((rt_uint16_t)buf[3] << 8) | buf[2];
        msg->y = ((rt_uint16_t)buf[5] << 8) | buf[4];
#else
        switch (_panel->ctp_flag)
        {
        case REVERSE_X:
            msg->x = ((rt_uint16_t)buf[3] << 8) | buf[2];
            msg->x = _panel->width - msg->x;
            msg->y = ((rt_uint16_t)buf[5] << 8) | buf[4];
            break;
        case REVERSE_Y:
            msg->x = ((rt_uint16_t)buf[3] << 8) | buf[2];
            msg->x = _panel->width - msg->x;
            msg->y = ((rt_uint16_t)buf[5] << 8) | buf[4];
            msg->y = _panel->height - msg->y;
            break;
        case (REVERSE_X | REVERSE_Y):
            msg->x = ((rt_uint16_t)buf[3] << 8) | buf[2];
            msg->y = ((rt_uint16_t)buf[5] << 8) | buf[4];
            msg->y = _panel->height - msg->y;
            break;
        case REVERSE_MODE:
            msg->y = ((rt_uint16_t)buf[3] << 8) | buf[2];
            msg->x = ((rt_uint16_t)buf[5] << 8) | buf[4];
            msg->x = _panel->height - msg->x;
            break;
        case (REVERSE_MODE | REVERSE_X):
            msg->y = ((rt_uint16_t)buf[3] << 8) | buf[2];
            msg->x = ((rt_uint16_t)buf[5] << 8) | buf[4];
            msg->x = msg->x;
            break;
        case (REVERSE_MODE | REVERSE_Y):
            msg->y = ((rt_uint16_t)buf[3] << 8) | buf[2];
            msg->y = _panel->width - msg->y;
            msg->x = ((rt_uint16_t)buf[5] << 8) | buf[4];
            msg->x = _panel->height - msg->x;
            break;
        case (REVERSE_MODE | REVERSE_X | REVERSE_Y):
            msg->y = ((rt_uint16_t)buf[3] << 8) | buf[2];
            msg->x = ((rt_uint16_t)buf[5] << 8) | buf[4];
            msg->y = _panel->width - msg->y;
            break;
        default:
            msg->x = ((rt_uint16_t)buf[3] << 8) | buf[2];
            msg->y = ((rt_uint16_t)buf[5] << 8) | buf[4];
            break;
        }
#endif
        if (s_tp_down)
        {
            msg->event = TOUCH_EVENT_MOVE;
        }
        else
        {
            msg->event = TOUCH_EVENT_DOWN;
            s_tp_down = 1;
        }
    }
    /* update the last record */
    rt_memcpy(last_buf, buf, 8);

    buf[0] = ((gt9xx_CLEARBUF_REG >> 8) & 0xFF);
    buf[1] = (gt9xx_CLEARBUF_REG & 0xFF);
    buf[2] = 0x00;
    rt_touch_write(GT9xx_TS_ADDR, buf, 3);

    rt_sem_release(gt9xx_driver.isr_sem);

    return RT_EOK;
}

struct touch_ops gt9xx_ops =
{
    .init       = gt9xx_init,
    .deinit     = gt9xx_deinit,
    .read_point = gt9xx_read_point,
};

static int gt9xx_driver_register(void)
{
    gt9xx_driver.probe     = gt9xx_probe;
    gt9xx_driver.ops       = &gt9xx_ops;
    gt9xx_driver.user_data = RT_NULL;

    rt_touch_drivers_register(&gt9xx_driver);

    return RT_EOK;
}
INIT_ENV_EXPORT(gt9xx_driver_register);
