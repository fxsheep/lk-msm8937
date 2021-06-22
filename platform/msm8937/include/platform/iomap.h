
#pragma once

#define SDRAM_BASE                         (0x80000000U)
#define MSM_IOMAP_BASE_PHYS                (0x0U)
#define MSM_IOMAP_BASE_SIZE                (0x80000000U)
#define MSM_IOMAP_BASE_VIRT                (0xFFFFFFFF00000000ULL)

#define GIC_BASE                           (MSM_IOMAP_BASE_VIRT + 0x0B000000)


#define PERIPH_SS_BASE                     (MSM_IOMAP_BASE_VIRT + 0x07800000)

#define MSM_SDC1_BASE                      (PERIPH_SS_BASE + 0x00024000)
#define MSM_SDC2_BASE                      (PERIPH_SS_BASE + 0x00064000)

/* UART */
#define BLSP1_UART0_BASE                   (PERIPH_SS_BASE + 0x000AF000)
#define BLSP1_UART1_BASE                   (PERIPH_SS_BASE + 0x000B0000)
#define MSM_USB_BASE                       (PERIPH_SS_BASE + 0x000DB000)