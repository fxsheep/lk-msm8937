
#pragma once

#define SDRAM_BASE               (0x80000000U)
#define MSM_IOMAP_BASE_PHYS      (0x0U)
#define MSM_IOMAP_BASE_SIZE      (0x80000000U)
#define MSM_IOMAP_BASE_VIRT      (0xFFFFFFFF00000000ULL)

#define GIC_BASE                 (MSM_IOMAP_BASE_VIRT + 0xB000000)
