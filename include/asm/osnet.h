/*
 * control flags.
 */
#ifndef _ASM_X86_OSNET_H
#define _ASM_X86_OSNET_H

/* configure VMCS */
#define OSNET_CONFIGURE_VMCS 1
#define OSNET_CONFIGURE_MSR_BITMAP 1

/* map per-vcpu posted-intr descriptor (PID) */
#define OSNET_DTID_HYPERCALL_MAP_PID 1
#define OSNET_DTID_PI_DESC 1

#if OSNET_DTID_PI_DESC
#include <linux/kvm_types.h>
#define OSNET_KVM_MAX_VCPU_ID 1023
#define OSNET_OLD_PID_PROTECTION 0x063
#define OSNET_NEW_PID_PROTECTION 0x167

struct osnet_pid_pte {
        /* vaddr of host's pid */
        unsigned long pid;

        /* vaddr of the shared/guest PID */
        unsigned long gpid;
};

struct osnet_pi_desc {
        struct osnet_pid_pte pid_pte[OSNET_KVM_MAX_VCPU_ID];
        unsigned int hash[OSNET_KVM_MAX_VCPU_ID];
        unsigned int size;
};
#endif

/* set the X2APIC ID */
#define OSNET_SET_X2APIC_ID 1

/* clockevent device */
#define OSNET_GET_CLOCKEVENT_FACTOR 1

/* setup DID */
#define OSNET_SETUP_DID OSNET_CONFIGURE_VMCS && \
                        OSNET_CONFIGURE_MSR_BITMAP && \
                        OSNET_DTID_HYPERCALL_MAP_PID && \
                        OSNET_GET_CLOCKEVENT_FACTOR && \
                        OSNET_DTID_PI_DESC

/* MVM: multiple-vm hypervisor*/
#define OSNET_MVM 1
#if OSNET_MVM

#define OSNET_STRING_LENGTH 100
#define OSNET_MAX_VCPU_ID 1024
#define OSNET_NULL_CHAR '\0'
#define OSNET_FALSE_VALUE -1

#define OSNET_KVMIO 0xBE
#define OSNET_KVM_SET_CPUMAP   _IOW(OSNET_KVMIO, 0x00, struct osnet_cpumap)

struct osnet_cpumap {
        int pcpus[OSNET_MAX_VCPU_ID];
        unsigned int nvcpus;
        bool is_valid;
        char path[OSNET_STRING_LENGTH];
};

struct osnet_tid_cpumap {
        int tids[OSNET_MAX_VCPU_ID];
        struct osnet_cpumap cpumap;
};

#endif

#endif  /* _ASM_X86_OSNET_H */
