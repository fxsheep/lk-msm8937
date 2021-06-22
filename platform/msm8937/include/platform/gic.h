#pragma once

#include <platform/iomap.h>
#include <platform/irqs.h>

#define GICBASE(n) (GIC_BASE)
#define GICD_OFFSET (0x0)
#define GICC_OFFSET (0x2000)

#define MAX_INT NR_IRQS
