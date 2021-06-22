LOCAL_DIR := $(GET_LOCAL_DIR)

MODULE := $(LOCAL_DIR)

MODULE_DEPS += \
    lib/cbuf \
    lib/fdt \
    dev/interrupt/arm_gic \
    dev/timer/arm_generic \

MODULE_SRCS += \
	$(LOCAL_DIR)/platform.c \
	$(LOCAL_DIR)/uart_dm.c \

ARCH := arm64
ARM_CPU := cortex-a53
MEMBASE := 0x80000000
MEMSIZE := 0x40000000	# 1GB
KERNEL_LOAD_OFFSET := 0x88000
LINKER_SCRIPT += \
	$(BUILDDIR)/system-onesegment.ld

MODULE := $(LOCAL_DIR)

MODULE_DEPS += \
		app/shell \

include make/module.mk 
