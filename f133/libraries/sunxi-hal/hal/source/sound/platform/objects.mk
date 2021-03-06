#PLATFORM
DRIVERS_SOUND_PLATFORM_OBJECTS-$(CONFIG_SND_PLATFORM_SUNXI_PCM) += $(BUILD_DIR)/drivers/hal/source/sound/platform/sunxi-pcm.o
DRIVERS_SOUND_PLATFORM_OBJECTS-$(CONFIG_SND_PLATFORM_SUNXI_CPUDAI) += $(BUILD_DIR)/drivers/hal/source/sound/platform/sunxi-dummy-cpudai.o
DRIVERS_SOUND_PLATFORM_OBJECTS-$(CONFIG_SND_PLATFORM_SUNXI_DAUDIO) += $(BUILD_DIR)/drivers/hal/source/sound/platform/sunxi-daudio.o
DRIVERS_SOUND_PLATFORM_OBJECTS-$(CONFIG_SND_PLATFORM_SUNXI_DMIC) += $(BUILD_DIR)/drivers/hal/source/sound/platform/sunxi-dmic.o


$(DRIVERS_SOUND_PLATFORM_OBJECTS-y):MODULE_NAME="drivers-sound"

#$(DRIVERS_SOUND_PLATFORM_OBJECTS-y):CFLAGS += -DSNDRV_DEBUG
$(DRIVERS_SOUND_PLATFORM_OBJECTS-y):CFLAGS += -Werror -Wfatal-errors
$(DRIVERS_SOUND_PLATFORM_OBJECTS-y):CFLAGS += -I $(BASE)/drivers/chip-src/sound/core/
$(DRIVERS_SOUND_PLATFORM_OBJECTS-y):CFLAGS += -I $(BASE)/drivers/chip-src/sound/codecs/sunxi/
$(DRIVERS_SOUND_PLATFORM_OBJECTS-y):CFLAGS += -I $(BASE)/include/
$(DRIVERS_SOUND_PLATFORM_OBJECTS-y):CFLAGS += -I $(BASE)/include/drivers/
$(DRIVERS_SOUND_PLATFORM_OBJECTS-y):CFLAGS += -I $(BASE)/include/freertos/
$(DRIVERS_SOUND_PLATFORM_OBJECTS-y):CFLAGS += -I $(BASE)/kernel/FreeRTOS/Source/include/
$(DRIVERS_SOUND_PLATFORM_OBJECTS-y):CFLAGS += -I $(BASE)/kernel/FreeRTOS/Source/port/
$(DRIVERS_SOUND_PLATFORM_OBJECTS-y):CFLAGS += -I $(BASE)/kernel/FreeRTOS/Source/portable/GCC/ARM_CA9

OBJECTS += $(DRIVERS_SOUND_PLATFORM_OBJECTS-y)
