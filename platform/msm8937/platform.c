#include <arch/arm64.h>
#include <lk/trace.h>
#include <assert.h>
#include <lk/err.h>
#include <lk/bits.h>
#include <kernel/spinlock.h>
#include <kernel/thread.h>
#include <kernel/mp.h>
#include <platform/interrupts.h>
#include <lk/init.h>
#include <kernel/vm.h>
#include <kernel/spinlock.h>
#include <dev/timer/arm_generic.h>
#include <platform.h>
#include <dev/interrupt/arm_gic.h>
#include <dev/timer/arm_generic.h>
#include <platform/iomap.h>
#include <platform/irqs.h>
#include <dev/uart.h>

typedef struct arm64_iframe_long arm_platform_iframe_t;

extern int smc_call(ulong arg0, ulong arg1, ulong arg2, ulong arg3);

/* initial memory mappings. parsed by start.S */
struct mmu_initial_mapping mmu_initial_mappings[] = {
    {
        .phys = SDRAM_BASE,
        .virt = KERNEL_BASE,
        .size = MEMSIZE,
        .flags = 0,
        .name = "memory"
    },

    /* peripherals */
    {
        .phys = MSM_IOMAP_BASE_PHYS,
        .virt = MSM_IOMAP_BASE_VIRT,
        .size = MSM_IOMAP_BASE_SIZE,
        .flags = MMU_INITIAL_MAPPING_FLAG_DEVICE,
        .name = "peripherals"
    },

    /* null entry to terminate the list */
    { 0 }
};

static pmm_arena_t arena = {
    .name = "sdram",
    .base = SDRAM_BASE,
    .size = MEMSIZE,
    .flags = PMM_ARENA_FLAG_KMAP,
};

#define DEBUG_UART 0

void platform_dputc(char c) {
    if (c == '\n')
        uart_putc(DEBUG_UART, '\r');
    uart_putc(DEBUG_UART, c);
}

int platform_dgetc(char *c, bool wait) {
    int ret = uart_getc(DEBUG_UART, wait);
    if (ret == -1)
        return -1;
    *c = ret;
    return 0;
}

void platform_init(void) {
}

void platform_early_init(void) {
    struct list_node list = LIST_INITIAL_VALUE(list);

    //platform_clock_init();

    /* initialize the interrupt controller */
    arm_gic_init();

    arm_generic_timer_init(INT_QTMR_NON_SECURE_PHY_TIMER_EXP, 0);

    pmm_add_arena(&arena);

    /* reserve memory occupied by TrustZone, etc. */

    pmm_alloc_range(0x85b00000, 0xd00000 / PAGE_SIZE, &list);

#if WITH_SMP
    /* boot the secondary cpus using the Power State Coordintion Interface */
    ulong psci_call_num = 0x84000000 + 0x40000000 + 3; /* SMC64 CPU_ON */

    for (int cpuid = 1; cpuid < SMP_MAX_CPUS; cpuid++) {
        /* note: assumes cpuids are numbered like MPIDR 0:0:0:N */
        int ret = smc_call(psci_call_num, cpuid, MEMBASE + KERNEL_LOAD_OFFSET, cpuid);
        if (ret != 0) {
            printf("ERROR: psci CPU_ON returns %d\n", ret);
        }
    }
#endif
}
