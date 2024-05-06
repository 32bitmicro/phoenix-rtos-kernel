/*
 * Phoenix-RTOS
 *
 * Operating system kernel
 *
 * CPU related routines (RISCV64)
 *
 * Copyright 2018 Phoenix Systems
 * Author: Pawel Pisarczyk
 *
 * This file is part of Phoenix-RTOS.
 *
 * %LICENSE%
 */

#ifndef _HAL_RISCV64_H_
#define _HAL_RISCV64_H_


#include "hal/types.h"


#define csr_set(csr, val) \
	({ \
		unsigned long __v = (unsigned long)(val); \
		__asm__ volatile( \
			"csrs " #csr ", %0" \
			: \
			: "rK"(__v) \
			: "memory"); \
	})


#define csr_write(csr, val) \
	({ \
		unsigned long __v = (unsigned long)(val); \
		__asm__ volatile( \
			"csrw " #csr ", %0" \
			: \
			: "rK"(__v) \
			: "memory"); \
	})


#define csr_read(csr) \
	({ \
		register unsigned long __v; \
		__asm__ volatile( \
			"csrr %0, " #csr \
			: "=r"(__v) \
			: \
			: "memory"); \
		__v; \
	})


#define csr_clear(csr, val) \
	({ \
		unsigned long __v = (unsigned long)(val); \
		__asm__ volatile( \
			"csrc " #csr ", %0" \
			: \
			: "rK"(__v) \
			: "memory"); \
	})


static inline void hal_cpuFlushTLB(const void *vaddr)
{
	/* clang-format off */
	__asm__ volatile (
		"sfence.vma %0, zero"
		:
		: "r"(vaddr)
		: "memory"
	);
	/* clang-format on */
}


static inline void hal_cpuSwitchSpace(addr_t pdir)
{
	/* clang-format off */
	__asm__ volatile(
		"sfence.vma\n\t"
		"csrw satp, %0\n\t"
		"fence\n\t"
		"fence.i\n\t"
		:
		:"r"(pdir)
		: "memory"
	);
	/* clang-format on */
}


/* Barriers */


/* clang-format off */
#define RISCV_FENCE(p, s) \
	({ \
		__asm__ volatile ("fence " #p ", " #s ::: "memory"); \
	})
/* clang-format on */


static inline void hal_cpuInstrBarrier(void)
{
	/* clang-format off */
	__asm__ volatile("fence.i" ::: "memory");
	/* clang-format on */
}


#endif
