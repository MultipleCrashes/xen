/* -*-  Mode:C; c-basic-offset:4; tab-width:4; indent-tabs-mode:nil -*- */
/*
 * vmx.h: prototype for generial vmx related interface
 * Copyright (c) 2004, Intel Corporation.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place - Suite 330, Boston, MA 02111-1307 USA.
 *
 * 	Kun Tian (Kevin Tian) (kevin.tian@intel.com)
 */

#ifndef _ASM_IA64_VT_H
#define _ASM_IA64_VT_H

#define RR7_SWITCH_SHIFT	12	/* 4k enough */
#include <public/hvm/ioreq.h>
#define vmx_user_mode(regs) (((struct ia64_psr *)&(regs)->cr_ipsr)->vm == 1)

#define VCPU_LID(v) (((u64)(v)->vcpu_id)<<24)

extern void identify_vmx_feature(void);
extern unsigned int vmx_enabled;
extern void vmx_init_env(void);
extern void vmx_final_setup_guest(struct vcpu *v);
extern void vmx_save_state(struct vcpu *v);
extern void vmx_load_state(struct vcpu *v);
extern void vmx_setup_platform(struct domain *d, struct vcpu_guest_context *c);
extern void vmx_wait_io(void);
extern void vmx_io_assist(struct vcpu *v);
extern void panic_domain(struct pt_regs *regs, const char *fmt, ...);
extern int ia64_hypercall (struct pt_regs *regs);
extern void vmx_save_state(struct vcpu *v);
extern void vmx_load_state(struct vcpu *v);
extern void show_registers(struct pt_regs *regs);
#define show_execution_state show_registers
extern int vmx_build_physmap_table(struct domain *d);
extern unsigned long __gpfn_to_mfn_foreign(struct domain *d, unsigned long gpfn);
extern void sync_split_caches(void);
extern void vmx_virq_line_assist(struct vcpu *v);
extern void set_privileged_operation_isr (struct vcpu *vcpu,int inst);
extern void privilege_op (struct vcpu *vcpu);
extern void set_ifa_itir_iha (struct vcpu *vcpu, u64 vadr,
          int set_ifa, int set_itir, int set_iha);
extern void inject_guest_interruption(struct vcpu *vcpu, u64 vec);
extern void vmx_intr_assist(struct vcpu *v);
extern void set_illegal_op_isr (struct vcpu *vcpu);
extern void illegal_op (struct vcpu *vcpu);
extern void vmx_relinquish_vcpu_resources(struct vcpu *v);
extern void vmx_die_if_kernel(char *str, struct pt_regs *regs, long err);

static inline vcpu_iodata_t *get_vio(struct domain *d, unsigned long cpu)
{
    return &((shared_iopage_t *)d->arch.vmx_platform.shared_page_va)->vcpu_iodata[cpu];
}

static inline int iopacket_port(struct vcpu *v)
{
    return get_vio(v->domain, v->vcpu_id)->vp_eport;
}

static inline shared_iopage_t *get_sp(struct domain *d)
{
    return (shared_iopage_t *)d->arch.vmx_platform.shared_page_va;
}

typedef unsigned long (*vmx_mmio_read_t)(struct vcpu *v,
                                         unsigned long addr,
                                         unsigned long length);

typedef void (*vmx_mmio_write_t)(struct vcpu *v,
                                 unsigned long addr,
                                 unsigned long length,
                                 unsigned long val);

typedef int (*vmx_mmio_check_t)(struct vcpu *v, unsigned long addr);

struct vmx_mmio_handler {
    vmx_mmio_check_t check_handler;
    vmx_mmio_read_t read_handler;
    vmx_mmio_write_t write_handler;
};

#endif /* _ASM_IA64_VT_H */
