# Diff `big` module with linux-4.10-1 kvm

## Source structure of `big`

```bash

$ tree ../big
../big
├── include
│   ├── asm
│   │   ├── kvm_host.h
│   │   └── osnet.h
│   ├── linux
│   │   ├── kvm_host.h
│   │   └── kvm_para.h
│   └── uapi
│       └── osnet_additional_hc.h
├── Makefile
├── osnet
│   ├── asm_kvm_host.h -> ../include/asm/kvm_host.h
│   ├── kvm_main.c -> ../virt-kvm/kvm_main.c
│   ├── lapic.c -> ../x86-kvm/lapic.c
│   ├── lapic.h -> ../x86-kvm/lapic.h
│   ├── linux_kvm_host.h -> ../include/linux/kvm_host.h
│   ├── mmu.c -> ../x86-kvm/mmu.c
│   ├── osnet_additional_hc.h -> ../include/uapi/osnet_additional_hc.h
│   ├── osnet.h -> ../include/asm/osnet.h
│   ├── vmx.c -> ../x86-kvm/vmx.c
│   └── x86.c -> ../x86-kvm/x86.c
├── README.txt
├── virt-kvm
│   ├── async_pf.c
│   ├── async_pf.h
│   ├── coalesced_mmio.c
│   ├── coalesced_mmio.h
│   ├── eventfd.c
│   ├── irqchip.c
│   ├── kvm_main.c
│   ├── lib
│   │   ├── irqbypass.c
│   │   └── Makefile.old
│   ├── vfio.c
│   └── vfio.h
└── x86-kvm
    ├── assigned-dev.c
    ├── assigned-dev.h
    ├── cpuid.c
    ├── cpuid.h
    ├── debugfs.c
    ├── emulate.c
    ├── hyperv.c
    ├── hyperv.h
    ├── i8254.c
    ├── i8254.h
    ├── i8259.c
    ├── ioapic.c
    ├── ioapic.h
    ├── iommu.c
    ├── irq.c
    ├── irq_comm.c
    ├── irq.h
    ├── Kconfig.old
    ├── kvm_cache_regs.h
    ├── lapic.c
    ├── lapic.h
    ├── Makefile.old
    ├── mmu_audit.c
    ├── mmu.c
    ├── mmu.h
    ├── mmutrace.h
    ├── mtrr.c
    ├── page_track.c
    ├── paging_tmpl.h
    ├── pmu_amd.c
    ├── pmu.c
    ├── pmu.h
    ├── pmu_intel.c
    ├── svm.c
    ├── trace.h
    ├── tss.h
    ├── vmx.c
    ├── x86.c
    └── x86.h

8 directories, 67 files

```

## Diff results

`big/include/asm/kvm_host.h` vs `linux-4.10.1/arch/x86/include/asm/kvm_host.h`:

```
37a38,46
> /* OSNET */
> #include "../asm/osnet.h"
> /* OSNET-END*/
> 
> #if OSNET_MVM
> unsigned long osnet_find_spte(struct kvm_vcpu *vcpu, gfn_t gfn);
> bool osnet_spt_walk(struct kvm_vcpu *vcpu, gfn_t gfn);
> #endif
> 
1032a1042,1063
> #if OSNET_MVM
>         u32 (*get_pin_based_exec_ctrl)(struct kvm_vcpu *vcpu);
>         u32 (*get_cpu_exec_ctrl)(struct kvm_vcpu *vcpu);
>         u32 (*get_secondary_exec_ctrl)(struct kvm_vcpu *vcpu);
>         u32 (*vmcs_read32)(unsigned long field);
>         u64 (*vmcs_read64)(unsigned long field);
>         void (*vmcs_write32)(unsigned long field, u32 value);
>         void (*vmcs_write64)(unsigned long field, u64 value);
>         void (*dump_vmcs)(void);
>         void (*update_pid)(struct kvm_vcpu *vcpu, unsigned long pid);
>         void (*disable_intercept_msr_x2apic)(u32 msr, int type,
>                                              bool apicv_active);
>         void (*enable_intercept_msr_x2apic)(u32 msr, int type,
>                                             bool apicv_active);
>         void (*disable_intercept_vcpu_msr_x2apic)(struct kvm_vcpu *vcpu, u32 msr,
>                                                   int type, bool apicv_active);
>         void (*enable_intercept_vcpu_msr_x2apic)(struct kvm_vcpu *vcpu, u32 msr,
>                                                  int type, bool apicv_active);
>         void (*print_mvm)(struct kvm_vcpu *vcpu);
>         void (*set_msr_bitmap)(struct kvm_vcpu *vcpu);
>         void (*restore_msr_bitmap)(struct kvm_vcpu *vcpu);
> #endif
```

`big/include/asm/osnet.h`: new file.

`big/include/linux/kvm_host.h` vs `linux-4.10.1/include/linux/kvm_host.h`:

```
36,40c36
< /* OSNET */
< //#include <asm/kvm_host.h>
< #include "../asm/kvm_host.h"
< #include "../asm/osnet.h"
< /* OSNET-END */
---
> #include <asm/kvm_host.h>
437,440d432
< #if OSNET_MVM
<         struct osnet_pi_desc osnet_pid;
<         struct osnet_cpumap osnet_cpumap;
< #endif

```

`big/include/linux/kvm_para.h` vs `linux-4.10.1/include/linux/kvm_para.h`: no difference.

`big/include/linux/uapi/osnet_additional_hc.h`: new file. (additional hypercalls)

`big/osnet/*`: just some symbolic links to files in `big/include`, `big/virt-kvm` or `big/x86-kvm`.

`big/virt-kvm` vs `linux-4.10.1/virt/kvm`:

```
zhifeiy@rs3labsrv2:~/directvisor$ diff -r big/virt-kvm linux-4.10.1/virt/kvm/


Only in linux-4.10.1/virt/kvm/: arm

diff -r big/virt-kvm/async_pf.c linux-4.10.1/virt/kvm/async_pf.c
23,24c23
< //#include <linux/kvm_host.h>
< #include "../include/linux/kvm_host.h"
---
> #include <linux/kvm_host.h>

diff -r big/virt-kvm/coalesced_mmio.c linux-4.10.1/virt/kvm/coalesced_mmio.c
13,14c13
< //#include <linux/kvm_host.h>
< #include "../include/linux/kvm_host.h"
---
> #include <linux/kvm_host.h>

diff -r big/virt-kvm/eventfd.c linux-4.10.1/virt/kvm/eventfd.c
24,25c24
< //#include <linux/kvm_host.h>
< #include "../include/linux/kvm_host.h"
---
> #include <linux/kvm_host.h>

diff -r big/virt-kvm/irqchip.c linux-4.10.1/virt/kvm/irqchip.c
27,28c27
< //#include <linux/kvm_host.h>
< #include "../include/linux/kvm_host.h"
---
> #include <linux/kvm_host.h>
33,34c32
< //#include "irq.h"
< #include "../x86-kvm/irq.h"
---
> #include "irq.h"


Only in linux-4.10.1/virt/kvm/: Kconfig

diff -r big/virt-kvm/kvm_main.c linux-4.10.1/virt/kvm/kvm_main.c
21,22c21
< //#include <linux/kvm_host.h>
< #include "../include/linux/kvm_host.h"
---
> #include <linux/kvm_host.h>
41,44c40
< /* OSNET */
< //#include <linux/kvm_para.h>
< #include "../include/linux/kvm_para.h"
< /* OSNET-END */
---
> #include <linux/kvm_para.h>
70,73d65
< /* OSNET */
< #include "../include/asm/osnet.h"
< /* OSNET-END */
< 
748,754d739
< #if OSNET_MVM
<         for (i = 0; i < kvm->osnet_pid.size; i++) {
<                 struct osnet_pid_pte *entry;
<                 entry = &kvm->osnet_pid.pid_pte[i];
<                 free_page(entry->pid);
<         }
< #endif
2962,2975d2946
< #if OSNET_MVM
< static int osnet_kvm_ioctl_set_cpumap(struct kvm *kvm, const void __user *argp)
< {
<         int ret;
< 
<         ret = copy_from_user(&(kvm->osnet_cpumap), argp,
<                              sizeof(kvm->osnet_cpumap));
<         if (ret)
<                 pr_err("bytes could not be copied: %d\n", ret);
< 
<         return ret;
< }
< #endif
< 
3135,3140c3106
< #if OSNET_MVM
<       case OSNET_KVM_SET_CPUMAP:
<                 r = osnet_kvm_ioctl_set_cpumap(kvm, argp);
<               break;
< #endif
<         default:
---
>       default:


Only in big/virt-kvm: .kvm_main.o.d


Only in big/virt-kvm: lib

diff -r big/virt-kvm/vfio.c linux-4.10.1/virt/kvm/vfio.c
14,15c14
< //#include <linux/kvm_host.h>
< #include "../include/linux/kvm_host.h"
---
> #include <linux/kvm_host.h>

```

`big/x86-kvm` vs `linux-4.10.1/arch/x86/kvm`:

```

diff -r big/x86-kvm/assigned-dev.c linux-4.10.1/arch/x86/kvm/assigned-dev.c
11,12c11
< //#include <linux/kvm_host.h>
< #include "../include/linux/kvm_host.h"
---
> #include <linux/kvm_host.h>

diff -r big/x86-kvm/assigned-dev.h linux-4.10.1/arch/x86/kvm/assigned-dev.h
4,5c4
< //#include <linux/kvm_host.h>
< #include "../include/linux/kvm_host.h"
---
> #include <linux/kvm_host.h>

diff -r big/x86-kvm/cpuid.c linux-4.10.1/arch/x86/kvm/cpuid.c
15,16c15
< //#include <linux/kvm_host.h>
< #include "../include/linux/kvm_host.h"
---
> #include <linux/kvm_host.h>

diff -r big/x86-kvm/debugfs.c linux-4.10.1/arch/x86/kvm/debugfs.c
10,11c10
< //#include <linux/kvm_host.h>
< #include "../include/linux/kvm_host.h"
---
> #include <linux/kvm_host.h>

diff -r big/x86-kvm/emulate.c linux-4.10.1/arch/x86/kvm/emulate.c
23,24c23
< //#include <linux/kvm_host.h>
< #include "../include/linux/kvm_host.h"
---
> #include <linux/kvm_host.h>

diff -r big/x86-kvm/hyperv.c linux-4.10.1/arch/x86/kvm/hyperv.c
29,30c29
< //#include <linux/kvm_host.h>
< #include "../include/linux/kvm_host.h"
---
> #include <linux/kvm_host.h>

diff -r big/x86-kvm/i8254.c linux-4.10.1/arch/x86/kvm/i8254.c
35,36c35
< //#include <linux/kvm_host.h>
< #include "../include/linux/kvm_host.h"
---
> #include <linux/kvm_host.h>

diff -r big/x86-kvm/i8259.c linux-4.10.1/arch/x86/kvm/i8259.c
34,35c34
< //#include <linux/kvm_host.h>
< #include "../include/linux/kvm_host.h"
---
> #include <linux/kvm_host.h>

diff -r big/x86-kvm/ioapic.c linux-4.10.1/arch/x86/kvm/ioapic.c
30,31c30
< //#include <linux/kvm_host.h>
< #include "../include/linux/kvm_host.h"
---
> #include <linux/kvm_host.h>

diff -r big/x86-kvm/ioapic.h linux-4.10.1/arch/x86/kvm/ioapic.h
4,5c4
< //#include <linux/kvm_host.h>
< #include "../include/linux/kvm_host.h"
---
> #include <linux/kvm_host.h>

diff -r big/x86-kvm/iommu.c linux-4.10.1/arch/x86/kvm/iommu.c
27,28c27
< //#include <linux/kvm_host.h>
< #include "../include/linux/kvm_host.h"
---
> #include <linux/kvm_host.h>

diff -r big/x86-kvm/irq.c linux-4.10.1/arch/x86/kvm/irq.c
24,25c24
< //#include <linux/kvm_host.h>
< #include "../include/linux/kvm_host.h"
---
> #include <linux/kvm_host.h>

diff -r big/x86-kvm/irq_comm.c linux-4.10.1/arch/x86/kvm/irq_comm.c
23,24c23
< //#include <linux/kvm_host.h>
< #include "../include/linux/kvm_host.h"
---
> #include <linux/kvm_host.h>

diff -r big/x86-kvm/irq.h linux-4.10.1/arch/x86/kvm/irq.h
27,28c27
< //#include <linux/kvm_host.h>
< #include "../include/linux/kvm_host.h"
---
> #include <linux/kvm_host.h>

Only in linux-4.10.1/arch/x86/kvm: Kconfig

Only in big/x86-kvm: Kconfig.old

diff -r big/x86-kvm/lapic.c linux-4.10.1/arch/x86/kvm/lapic.c
0a1
> 
20,21c21
< //#include <linux/kvm_host.h>
< #include "../include/linux/kvm_host.h"
---
> #include <linux/kvm_host.h>
46,50d45
< /* OSNET */
< //#include <asm/osnet.h>
< #include "../include/asm/osnet.h"
< /* OSNET-END */
< 
263,269d257
< #if OSNET_MVM
< void osnet_kvm_apic_set_x2apic_id(struct kvm_lapic *apic, u32 id)
< {
<         kvm_apic_set_x2apic_id(apic, id);
< }
< #endif
< 
1845c1833
<                         kvm_apic_set_x2apic_id(apic, vcpu->vcpu_id);
---
> 			kvm_apic_set_x2apic_id(apic, vcpu->vcpu_id);

diff -r big/x86-kvm/lapic.h linux-4.10.1/arch/x86/kvm/lapic.h
6,15c6
< //#include <linux/kvm_host.h>
< #include "../include/linux/kvm_host.h"
< 
< /* OSNET */
< //#include <asm/osnet.h>
< #include "../include/asm/osnet.h"
< #if OSNET_MVM
< void osnet_kvm_apic_set_x2apic_id(struct kvm_lapic *apic, u32 id);
< #endif
< /* OSNET-END */
---
> #include <linux/kvm_host.h>

Only in linux-4.10.1/arch/x86/kvm: Makefile

Only in big/x86-kvm: Makefile.old

diff -r big/x86-kvm/mmu.c linux-4.10.1/arch/x86/kvm/mmu.c
27,28c27
< //#include <linux/kvm_host.h>
< #include "../include/linux/kvm_host.h"
---
> #include <linux/kvm_host.h>
48,51d46
< /* OSNET */
< #include "../include/asm/osnet.h"
< /* OSNET-END */
< 
2597,2640d2591
< 
< #if OSNET_MVM
< unsigned long osnet_find_spte(struct kvm_vcpu *vcpu, gfn_t gfn)
< {
<         struct kvm_shadow_walk_iterator iterator;
< 
<         for_each_shadow_entry(vcpu, (u64)gfn << PAGE_SHIFT, iterator) {
<                 u64 *sptep = iterator.sptep;
<                 if (is_shadow_present_pte(*sptep)) {
<                         kvm_pfn_t pfn = gfn_to_pfn(vcpu->kvm, gfn);
<                         if (pfn == spte_to_pfn(*sptep))
<                                 return (unsigned long) sptep;
<                 }
<         }
< 
<         return 0;
< }
< EXPORT_SYMBOL_GPL(osnet_find_spte);
< 
< bool osnet_spt_walk(struct kvm_vcpu *vcpu, gfn_t gfn)
< {
<         kvm_pfn_t pfn = gfn_to_pfn(vcpu->kvm, gfn);
<         struct kvm_shadow_walk_iterator iterator;
< 
<         /*
<          * pfn is retrieved based on the kvm_memslot and HVA.
<          * HVA is updated with the new pfn.
<          */
<         pr_info("gpa\tpfn\t*spte\tspte_to_pfn(*spte)\n");
<         for_each_shadow_entry(vcpu, (u64)gfn << PAGE_SHIFT, iterator) {
<                 u64 *sptep = iterator.sptep;
<                 u64 gaddr = iterator.addr;
<                 if (is_shadow_present_pte(*sptep)) {
<                         pr_info("0x%llx\t0x%llx\t0x%llx\t0x%llx\n",
<                                         gaddr, pfn, *sptep, spte_to_pfn(*sptep));
<                         if (pfn == spte_to_pfn(*sptep))
<                                 return true;
<                 }
<         }
< 
<         return false;
< }
< EXPORT_SYMBOL_GPL(osnet_spt_walk);
< #endif

diff -r big/x86-kvm/mmu.h linux-4.10.1/arch/x86/kvm/mmu.h
4,5c4
< //#include <linux/kvm_host.h>
< #include "../include/linux/kvm_host.h"
---
> #include <linux/kvm_host.h>

diff -r big/x86-kvm/mmutrace.h linux-4.10.1/arch/x86/kvm/mmutrace.h
3d2
< #define TRACE_INCLUDE_PATH /home/zhifeiy/directvisor/big/x86-kvm 
329,330c328
< //#define TRACE_INCLUDE_PATH .
< #define TRACE_INCLUDE_PATH /home/zhifeiy/directvisor/big/x86-kvm
---
> #define TRACE_INCLUDE_PATH .

diff -r big/x86-kvm/mtrr.c linux-4.10.1/arch/x86/kvm/mtrr.c
19,20c19
< //#include <linux/kvm_host.h>
< #include "../include/linux/kvm_host.h"
---
> #include <linux/kvm_host.h>

diff -r big/x86-kvm/page_track.c linux-4.10.1/arch/x86/kvm/page_track.c
16,19c16,17
< //#include <linux/kvm_host.h>
< #include "../include/linux/kvm_host.h"
< //#include <asm/kvm_host.h>
< #include "../include/asm/kvm_host.h"
---
> #include <linux/kvm_host.h>
> #include <asm/kvm_host.h>

diff -r big/x86-kvm/pmu_amd.c linux-4.10.1/arch/x86/kvm/pmu_amd.c
15,16c15
< //#include <linux/kvm_host.h>
< #include "../include/linux/kvm_host.h"
---
> #include <linux/kvm_host.h>

diff -r big/x86-kvm/pmu.c linux-4.10.1/arch/x86/kvm/pmu.c
17,18c17
< //#include <linux/kvm_host.h>
< #include "../include/linux/kvm_host.h"
---
> #include <linux/kvm_host.h>

diff -r big/x86-kvm/svm.c linux-4.10.1/arch/x86/kvm/svm.c
20,21c20
< //#include <linux/kvm_host.h>
< #include "../include/linux/kvm_host.h"
---
> #include <linux/kvm_host.h>

diff -r big/x86-kvm/trace.h linux-4.10.1/arch/x86/kvm/trace.h
3d2
< #define TRACE_INCLUDE_PATH /home/zhifeiy/directvisor/big/x86-kvm
1370,1371c1369
< //#define TRACE_INCLUDE_PATH arch/x86/kvm
< #define TRACE_INCLUDE_PATH /home/tcheng8/big/x86-kvm
---
> #define TRACE_INCLUDE_PATH arch/x86/kvm

diff -r big/x86-kvm/vmx.c linux-4.10.1/arch/x86/kvm/vmx.c
24,27c24
< /* OSNET */
< //#include <linux/kvm_host.h>
< #include "../include/linux/kvm_host.h"
< /* OSNET-END */
---
> #include <linux/kvm_host.h>
58,62d54
< /* OSNET */
< //#include <asm/osnet.h>
< #include "../include/asm/osnet.h"
< /* OSNET-END */
< 
633,638c625
< #if OSNET_MVM
<         struct pi_desc *pi_desc;
<         unsigned long *msr_bitmap;
< #else
<         struct pi_desc pi_desc;
< #endif
---
> 	struct pi_desc pi_desc;
685,689c672
< #if OSNET_MVM
<         return to_vmx(vcpu)->pi_desc;
< #else
<         return &(to_vmx(vcpu)->pi_desc);
< #endif
---
> 	return &(to_vmx(vcpu)->pi_desc);
2589c2572
<                         else
---
> 			else
2595c2578
<                 else
---
> 		else
4968,4998d4950
< #if 1
< static void osnet_vmx_disable_intercept_vcpu_msr_x2apic(struct kvm_vcpu *vcpu, u32 msr,
< 							int type, bool apicv_active)
< {
< 	struct vcpu_vmx *vmx;
< 
< 	vmx = to_vmx(vcpu);
< 	__vmx_disable_intercept_for_msr(vmx->msr_bitmap, msr, type);
< }
< #else
< static void osnet_vmx_disable_intercept_vcpu_msr_x2apic(struct kvm_vcpu *vcpu, u32 msr,
<                                                         int type, bool apicv_active)
< {
<         struct vcpu_vmx *vmx;
< 
<         vmx = to_vmx(vcpu);
< 
< 	if (apicv_active) {
< 		__vmx_disable_intercept_for_msr(vmx->osnet_msr_bitmap_legacy_x2apic_apicv,
< 				                msr, type);
< 		__vmx_disable_intercept_for_msr(vmx->osnet_msr_bitmap_longmode_x2apic_apicv,
< 				                msr, type);
< 	} else {
< 		__vmx_disable_intercept_for_msr(vmx->osnet_msr_bitmap_legacy_x2apic,
< 				                msr, type);
< 		__vmx_disable_intercept_for_msr(vmx->osnet_msr_bitmap_longmode_x2apic,
< 				                msr, type);
< 	}
< }
< #endif
< 
5059,5063c5011,5012
< #if OSNET_MVM
<                 WARN_ON_ONCE(pi_test_sn(vmx->pi_desc));
< #else
<                 WARN_ON_ONCE(pi_test_sn(&vmx->pi_desc));
< #endif
---
> 		WARN_ON_ONCE(pi_test_sn(&vmx->pi_desc));
> 
5106,5108d5054
< #if OSNET_MVM
<         if (pi_test_and_set_pir(vector, vmx->pi_desc))
<                 return;
5110,5113c5056,5057
<         r = pi_test_and_set_on(vmx->pi_desc);
< #else
<         if (pi_test_and_set_pir(vector, &vmx->pi_desc))
<                 return;
---
> 	if (pi_test_and_set_pir(vector, &vmx->pi_desc))
> 		return;
5115,5116c5059
<         r = pi_test_and_set_on(&vmx->pi_desc);
< #endif
---
> 	r = pi_test_and_set_on(&vmx->pi_desc);
5125,5136c5068
< #if OSNET_MVM
<         if (!pi_test_on(vmx->pi_desc))
<                 return;
< 
<         pi_clear_on(vmx->pi_desc);
<         /*
<          * IOMMU can write to PIR.ON, so the barrier matters even on UP.
<          * But on x86 this is just a compiler barrier anyway.
<          */
<         smp_mb__after_atomic();
<         kvm_apic_update_irr(vcpu, vmx->pi_desc->pir);
< #else
---
> 
5147d5078
< #endif
5333d5263
< 
5359,5363c5289
< #if OSNET_MVM
<                 vmcs_write64(POSTED_INTR_DESC_ADDR, __pa((vmx->pi_desc)));
< #else
<                 vmcs_write64(POSTED_INTR_DESC_ADDR, __pa((&vmx->pi_desc)));
< #endif
---
> 		vmcs_write64(POSTED_INTR_DESC_ADDR, __pa((&vmx->pi_desc)));
5511,5517c5437,5440
< #if OSNET_MVM
<         if (kvm_vcpu_apicv_active(vcpu))
<                 memset(vmx->pi_desc, 0, sizeof(struct pi_desc));
< #else
<         if (kvm_vcpu_apicv_active(vcpu))
<                 memset(&vmx->pi_desc, 0, sizeof(struct pi_desc));
< #endif
---
> 
> 	if (kvm_vcpu_apicv_active(vcpu))
> 		memset(&vmx->pi_desc, 0, sizeof(struct pi_desc));
> 
9242,9245d9164
< #if OSNET_DEBUG_TRACE
<         trace_printk("%d\n", vmx->exit_reason);
< #endif
< 
9307,9316d9225
< #if OSNET_MVM
< static void osnet_vmx_free_msr_bitmap(struct kvm_vcpu *vcpu)
< {
<         struct vcpu_vmx *vmx;
< 
<         vmx = to_vmx(vcpu);
<         free_page((unsigned long)vmx->msr_bitmap);
< }
< #endif
< 
9321,9324d9229
< #if OSNET_MVM
<         osnet_vmx_free_msr_bitmap(vcpu);
< #endif
< 
9336,9354d9240
< #if OSNET_MVM
< static void osnet_vmx_init_pid(struct kvm *kvm, struct vcpu_vmx *vmx,
<                                unsigned int id)
< {
<         unsigned long pid = get_zeroed_page(GFP_KERNEL);
<         struct osnet_pid_pte *entry = &kvm->osnet_pid.pid_pte[id];
< 
<         vmx->pi_desc = (struct pi_desc*) pid;
<         entry->pid = pid;
<         kvm->osnet_pid.size++;
< }
< 
< static void osnet_vmx_init_msr_bitmap(struct vcpu_vmx *vmx)
< {
<         vmx->msr_bitmap = (unsigned long *)__get_free_page(GFP_KERNEL);
<         memset(vmx->msr_bitmap, 0xff, PAGE_SIZE);
< }
< #endif
< 
9363,9366c9249
< #if OSNET_MVM
<         osnet_vmx_init_pid(kvm, vmx, id);
<         osnet_vmx_init_msr_bitmap(vmx);
< #endif
---
> 
10387c10270
< 	vm_entry_controls_init(vmx,
---
> 	vm_entry_controls_init(vmx, 
11617,11766d11499
< #if OSNET_MVM
< static u32 osnet_get_vmx_pin_based_exec_ctrl(struct kvm_vcpu *vcpu)
< {
<         struct vcpu_vmx *vmx = to_vmx(vcpu);
<         return vmx_pin_based_exec_ctrl(vmx);
< }
< 
< static u32 osnet_get_vmx_cpu_exec_ctrl(struct kvm_vcpu *vcpu)
< {
<         struct vcpu_vmx *vmx = to_vmx(vcpu);
<         return vmx_exec_control(vmx);
< }
< 
< static u32 osnet_get_vmx_secondary_exec_ctrl(struct kvm_vcpu *vcpu)
< {
<         struct vcpu_vmx *vmx = to_vmx(vcpu);
<         return vmx_secondary_exec_control(vmx);
< }
< 
< static void osnet_update_pid(struct kvm_vcpu *vcpu, unsigned long pid)
< {
<         struct vcpu_vmx *vmx = to_vmx(vcpu);
<         vmx->pi_desc = (struct pi_desc*) pid;
< }
< 
< static void __osnet_vmx_enable_intercept_for_msr(unsigned long *msr_bitmap,
<                                                  u32 msr, int type)
< {
<         int f = sizeof(unsigned long);
< 
<         if (!cpu_has_vmx_msr_bitmap())
<                 return;
< 
<         if (msr <= 0x1fff) {
<                 if (type & MSR_TYPE_R)
<                         /* read-low */
<                         __set_bit(msr, msr_bitmap + 0x000 / f);
< 
<                 if (type & MSR_TYPE_W)
<                         /* write-low */
<                         __set_bit(msr, msr_bitmap + 0x800 / f);
< 
<         } else if ((msr >= 0xc0000000) && (msr <= 0xc0001fff)) {
<                 msr &= 0x1fff;
<                 if (type & MSR_TYPE_R)
<                         /* read-high */
<                         __set_bit(msr, msr_bitmap + 0x400 / f);
< 
<                 if (type & MSR_TYPE_W)
<                         /* write-high */
<                         __set_bit(msr, msr_bitmap + 0xc00 / f);
<         }
< }
< 
< static void osnet_vmx_enable_intercept_msr_x2apic(u32 msr, int type,
<                                                   bool apicv_active)
< {
<         if (apicv_active) {
<                 __osnet_vmx_enable_intercept_for_msr(
<                                 vmx_msr_bitmap_legacy_x2apic_apicv, msr, type);
<                 __osnet_vmx_enable_intercept_for_msr(
<                                 vmx_msr_bitmap_longmode_x2apic_apicv, msr, type);
<         }
<         else {
<                 __osnet_vmx_enable_intercept_for_msr(
<                                 vmx_msr_bitmap_legacy_x2apic, msr, type);
<                 __osnet_vmx_enable_intercept_for_msr(
<                                 vmx_msr_bitmap_longmode_x2apic, msr, type);
<         }
< }
< 
< static void osnet_vmx_enable_intercept_vcpu_msr_x2apic(struct kvm_vcpu *vcpu, u32 msr,
< 						       int type, bool apicv_active)
< {
< 	struct vcpu_vmx *vmx = to_vmx(vcpu);
< 
< 	vmx = to_vmx(vcpu);
< 	__osnet_vmx_enable_intercept_for_msr(vmx->msr_bitmap, msr, type);
< }
< 
< static void osnet_print_mvm(struct kvm_vcpu *vcpu)
< {
<         pid_t pid;
<         struct vcpu_vmx *vmx;
<         struct kvm_lapic *apic;
<         int vcpuid;
<         int pcpu;
<         u32 vapicid;
<         u32 vapicldr;
<         u64 bitmap_paddr;
<         u64 vmcs_bitmap_paddr;
< 
<         pid = current->pid;
<         vmx = to_vmx(vcpu);
<         apic = vcpu->arch.apic;
<         vcpuid = vcpu->vcpu_id;
<         pcpu = vcpu->cpu;
<         vapicid = *((u32 *)(apic->regs + APIC_ID));
<         vapicldr = *((u32 *)(apic->regs + APIC_LDR));
<         bitmap_paddr = __pa(vmx->msr_bitmap);
<         vmcs_bitmap_paddr = vmcs_read64(MSR_BITMAP);
< 
<         pr_info("TID: %d\n", pid);
<         pr_info("VCPUID: %d\n", vcpuid);
<         pr_info("PCPU: %d\n", pcpu);
<         pr_info("MSR_BITMAP: 0x%llx\n", bitmap_paddr);
<         pr_info("VMCS_MSR_BITMAP: 0x%llx\n", vmcs_bitmap_paddr);
<         pr_info("VAPICID: 0x%x\n", vapicid);
<         pr_info("VAPICLDR: 0x%x\n", vapicldr);
< }
< 
< static void osnet_vmx_set_msr_bitmap(struct kvm_vcpu *vcpu)
< {
< 	struct vcpu_vmx *vmx;
< 	unsigned long *msr_bitmap;
< 
< 	if (is_guest_mode(vcpu))
< 		msr_bitmap = to_vmx(vcpu)->nested.msr_bitmap;
< 	else if (cpu_has_secondary_exec_ctrls() &&
< 		 (vmcs_read32(SECONDARY_VM_EXEC_CONTROL) &
< 		  SECONDARY_EXEC_VIRTUALIZE_X2APIC_MODE)) {
< 		if (enable_apicv && kvm_vcpu_apicv_active(vcpu)) {
< 			if (is_long_mode(vcpu))
< 				msr_bitmap = vmx_msr_bitmap_longmode_x2apic_apicv;
< 			else
< 				msr_bitmap = vmx_msr_bitmap_legacy_x2apic_apicv;
< 		} else {
< 			if (is_long_mode(vcpu))
< 				msr_bitmap = vmx_msr_bitmap_longmode_x2apic;
< 			else
< 				msr_bitmap = vmx_msr_bitmap_legacy_x2apic;
< 		}
< 	} else {
< 		if (is_long_mode(vcpu))
< 			msr_bitmap = vmx_msr_bitmap_longmode;
< 		else
< 			msr_bitmap = vmx_msr_bitmap_legacy;
< 	}
< 
< 	vmx = to_vmx(vcpu);
< 	memcpy(vmx->msr_bitmap, msr_bitmap, PAGE_SIZE);
< 	vmcs_write64(MSR_BITMAP, __pa(vmx->msr_bitmap));
< }
< 
< static void osnet_vmx_restore_msr_bitmap(struct kvm_vcpu *vcpu)
< {
< 	vmx_set_msr_bitmap(vcpu);
< }
< #endif
< 
11895,11912d11627
< #if OSNET_MVM
<         .get_pin_based_exec_ctrl = osnet_get_vmx_pin_based_exec_ctrl,
<         .get_cpu_exec_ctrl = osnet_get_vmx_cpu_exec_ctrl,
<         .get_secondary_exec_ctrl = osnet_get_vmx_secondary_exec_ctrl,
<         .vmcs_read32 = vmcs_read32,
<         .vmcs_read64 = vmcs_read64,
<         .vmcs_write32 = vmcs_write32,
<         .vmcs_write64 = vmcs_write64,
<         .dump_vmcs = dump_vmcs,
<         .update_pid = osnet_update_pid,
<         .disable_intercept_msr_x2apic = vmx_disable_intercept_msr_x2apic,
<         .enable_intercept_msr_x2apic = osnet_vmx_enable_intercept_msr_x2apic,
<         .disable_intercept_vcpu_msr_x2apic = osnet_vmx_disable_intercept_vcpu_msr_x2apic,
<         .enable_intercept_vcpu_msr_x2apic = osnet_vmx_enable_intercept_vcpu_msr_x2apic,
<         .print_mvm = osnet_print_mvm,
<         .set_msr_bitmap = osnet_vmx_set_msr_bitmap,
<         .restore_msr_bitmap = osnet_vmx_restore_msr_bitmap,
< #endif

diff -r big/x86-kvm/x86.c linux-4.10.1/arch/x86/kvm/x86.c
22,25c22
< /* OSNET */
< //#include <linux/kvm_host.h>
< #include "../include/linux/kvm_host.h"
< /* OSNET-END */
---
> #include <linux/kvm_host.h>
6117,6601d6113
< /* OSNET */
< //#include <asm/osnet.h>
< #include "../include/asm/osnet.h"
< /* OSNET-END */
< 
< #if OSNET_MVM
< #include <asm/pgtable.h>
< #include <asm/pgalloc.h>
< #include <linux/mm.h>
< #include <linux/page-flags.h>
< #include <linux/kallsyms.h>
< #include "../include/uapi/osnet_additional_hc.h"
< 
< static struct osnet_pid_pte *osnet_get_pid_pte(struct kvm_vcpu *vcpu)
< {
<         int id;
<         struct kvm *kvm;
<         struct osnet_pid_pte *entry;
< 
<         id = vcpu->vcpu_id;
<         kvm = vcpu->kvm;
<         entry = &kvm->osnet_pid.pid_pte[id];
< 
<         return entry;
< }
< 
< static unsigned long osnet_get_pid(struct kvm_vcpu *vcpu)
< {
<         return osnet_get_pid_pte(vcpu)->pid;
< }
< 
< static unsigned long osnet_get_gpid(struct kvm_vcpu *vcpu)
< {
<         return osnet_get_pid_pte(vcpu)->gpid;
< }
< 
< static void osnet_set_gpid(struct kvm_vcpu *vcpu, unsigned long gpid)
< {
<         struct osnet_pid_pte *entry;
<         entry = osnet_get_pid_pte(vcpu);
<         entry->gpid = gpid;
< }
< 
< static struct vm_area_struct *osnet_find_vma(struct mm_struct *mm,
<                                              unsigned long addr)
< {
<         struct vm_area_struct *vma;
< 
<         down_read(&mm->mmap_sem);
<         vma = find_vma(mm, addr);
<         up_read(&mm->mmap_sem);
< 
<         return vma;
< }
< 
< static unsigned long osnet_page_walk(struct mm_struct *mm, unsigned long addr)
< {
<         pgd_t *pgd;
<         pud_t *pud;
<         pmd_t *pmd;
<         pte_t *pte;
< 
<         pgd = pgd_offset(mm, addr);
<         if (pgd_none(*pgd)) {
<                 pr_info("PGD does not exist\n");
<                 goto out;
<         }
<         pr_info("PGD: 0x%p\t0x%lx\n", pgd, pgd_val(*pgd));
< 
<         pud = pud_offset(pgd, addr);
<         if (pud_none(*pud)) {
<                 pr_info("PUD does not exist\n");
<                 goto out;
<         }
<         pr_info("PUD: 0x%p\t0x%lx\n", pud, pud_val(*pud));
< 
<         pmd = pmd_offset(pud, addr);
<         if (pmd_none(*pmd)) {
<                 pr_info("PMD does not exist\n");
<                 goto out;
<         }
<         pr_info("PMD: 0x%p\t0x%lx\n", pmd, pmd_val(*pmd));
< 
<         pte = pte_offset_map(pmd, addr);
<         if (pte_none(*pte)) {
<                 pr_info("PTE does not exist\n");
<                 goto out;
<         }
<         pr_info("PTE: 0x%p\t0x%lx\n", pte, pte_val(*pte));
< 
<         return (unsigned long)pte;
< 
< out:
<         return 0;
< }
< 
< static int osnet_map_pid(struct kvm_vcpu *vcpu, unsigned long gpa)
< {
<         gfn_t gfn;
<         kvm_pfn_t gpfn;
<         hva_t hva;
<         struct vm_area_struct *vma;
<         struct mm_struct *mm;
<         void *pid;
<         struct page *gpage;
<         void *gpid;
<         u64 pid_paddr;
<         //typedef void (*func_t)(void);
<         //func_t my_flush_tlb_current_task;
<         struct kvm *kvm;
< 
<         gfn = gpa_to_gfn(gpa);
<         gpfn = gfn_to_pfn(vcpu->kvm, gfn);
<         hva = gfn_to_hva(vcpu->kvm, gfn);
<         vma = osnet_find_vma(current->mm, hva);
<         if (!vma) {
<                 pr_alert("VMA is not found\n");
<                 return -EAGAIN;
<         } else {
<                 mm = vma->vm_mm;
<         }
< 
<         gpage = pfn_to_page(gpfn);
<         gpid = kmap(gpage);
<         osnet_set_gpid(vcpu, (unsigned long)gpid);
< 
<         pid = (void *)osnet_get_pid(vcpu);
<         memcpy(gpid, pid, PAGE_SIZE);
< 
<         pr_info("***** update vmcs *****\n");
<         pid_paddr = kvm_x86_ops->vmcs_read64(POSTED_INTR_DESC_ADDR);
<         kvm_x86_ops->vmcs_write64(POSTED_INTR_DESC_ADDR, virt_to_phys(gpid));
<         pr_info("OLD PID PADDR: 0x%llx\n", pid_paddr);
<         pr_info("NEW PID PADDR: 0x%llx\n", virt_to_phys(gpid));
< 
<         pr_info("***** update vmx->pi_desc *****\n");
<         kvm_x86_ops->update_pid(vcpu, (unsigned long)gpid);
<         pr_info("OLD VMX->PI_DESC: 0x%lx\n", (unsigned long)pid);
<         pr_info("NEW VMX->PI_DESC: 0x%lx\n", (unsigned long)gpid);
< 
<         pr_info("***** update irte  *****\n");
<         kvm = vcpu->kvm;
<         mutex_lock(&kvm->irq_lock);
<         kvm_irq_routing_update(kvm);
<         mutex_unlock(&kvm->irq_lock);
<         synchronize_srcu_expedited(&kvm->irq_srcu);
< 
<         //pr_info("***** flush tlb *****\n");
<         //my_flush_tlb_current_task =
<         //        (func_t)kallsyms_lookup_name("flush_tlb_current_task");
<         //my_flush_tlb_current_task();
< 
<         return 0;
< }
< 
< static int osnet_unmap_pid(struct kvm_vcpu *vcpu, unsigned long gpa)
< {
<         gfn_t gfn;
<         kvm_pfn_t pfn;
<         hva_t hva;
<         struct vm_area_struct *vma;
<         struct mm_struct *mm;
<         void *pid;
<         struct page *page;
<         void *gpid;
<         //typedef void (*func_t)(void);
<         //func_t my_flush_tlb_current_task;
<         struct kvm *kvm;
< 
<         gfn = gpa_to_gfn(gpa);
<         pfn = gfn_to_pfn(vcpu->kvm, gfn);
<         hva = gfn_to_hva(vcpu->kvm, gfn);
<         vma = osnet_find_vma(current->mm, hva);
<         if (!vma) {
<                 pr_alert("VMA is not found\n");
<                 return -EAGAIN;
<         } else {
<                 mm = vma->vm_mm;
<         }
< 
<         pr_info("***** restore vmcs *****\n");
<         pid = (void*)osnet_get_pid(vcpu);
<         gpid = (void *)osnet_get_gpid(vcpu);
<         memcpy(pid, gpid, PAGE_SIZE);
<         kvm_x86_ops->vmcs_write64(POSTED_INTR_DESC_ADDR, virt_to_phys(pid));
< 
<         pr_info("***** restore vmx->pi_desc *****\n");
<         kvm_x86_ops->update_pid(vcpu, (unsigned long)pid);
< 
<         pr_info("***** restore irte *****\n");
<         kvm = vcpu->kvm;
<         mutex_lock(&kvm->irq_lock);
<         kvm_irq_routing_update(kvm);
<         mutex_unlock(&kvm->irq_lock);
<         synchronize_srcu_expedited(&kvm->irq_srcu);
< 
<         //pr_info("***** flush tlb *****\n");
<         //my_flush_tlb_current_task =
<         //        (func_t)kallsyms_lookup_name("flush_tlb_current_task");
<         //my_flush_tlb_current_task();
< 
<         pr_info("***** unmap host-to-guest page *****\n");
<         page = virt_to_page(gpid);
<         kunmap(page);
<         osnet_set_gpid(vcpu, 0);
< 
<         return 0;
< }
< 
< static bool hypercall_page_walk(struct kvm_vcpu *vcpu, unsigned long gpa)
< {
<         gfn_t gfn;
<         hva_t hva;
<         kvm_pfn_t pfn;
<         struct vm_area_struct *vma;
<         struct mm_struct *mm;
<         unsigned long pid;
< 
<         gfn = gpa_to_gfn(gpa);
<         hva = gfn_to_hva(vcpu->kvm, gfn);
<         pfn = gfn_to_pfn(vcpu->kvm, gfn);
<         vma = osnet_find_vma(current->mm, hva);
<         if (!vma) {
<                 pr_alert("VMA is not found\n");
<                 return false;
<         } else {
<                 mm = vma->vm_mm;
<         }
< 
<         pr_info("***** Walk GPA *****\n");
<         pr_info("GPA: 0x%lx\n", gpa);
<         pr_info("HVA: 0x%lx\t0x%llx\n", hva, pfn << PAGE_SHIFT);
<         osnet_page_walk(mm, hva);
< 
<         pr_info("***** Walk SPT *****\n");
<         if(!osnet_spt_walk(vcpu, gfn))
<                 pr_info("pfn 0x%llx is not found in spte\n", pfn);
< 
<         pr_info("***** Walk PID *****\n");
<         pid = osnet_get_pid(vcpu);
<         pr_info("PID: 0x%lx\t0x%llx\n", pid, virt_to_phys((void *)pid));
<         osnet_page_walk(mm, pid);
< 
<         return true;
< }
< 
< static int osnet_get_x2apic_id(void)
< {
<         return per_cpu(x86_cpu_to_apicid, smp_processor_id());
< }
< 
< static void osnet_setup_x2apic_id(struct kvm_vcpu *vcpu)
< {
<         int cpu;
<         int apicid;
<         int vcpuid;
<         struct kvm_lapic *apic;
<         struct osnet_cpumap *cpumap;
< 
<         cpumap = &(vcpu->kvm->osnet_cpumap);
<         vcpuid = vcpu->vcpu_id;
<         cpu = cpumap->pcpus[vcpuid];
<         apicid = per_cpu(x86_cpu_to_apicid, cpu);
<         apic = vcpu->arch.apic;
<         osnet_kvm_apic_set_x2apic_id(apic, apicid);
< 
<         pr_info("vcpu(%d) x2apic id: 0x%x\n", vcpu->vcpu_id, apicid);
< }
< 
< static void osnet_restore_x2apic_id(struct kvm_vcpu *vcpu)
< {
<         int apicid;
< 
<         apicid = vcpu->vcpu_id;
<         osnet_kvm_apic_set_x2apic_id(vcpu->arch.apic, apicid);
< 
<         pr_info("vcpu(%d) x2apic id: 0x%x\n", vcpu->vcpu_id, apicid);
< }
< 
< #include <asm/vmx.h>
< #include <linux/clockchips.h>
< 
< #define OSNET_MSR_TYPE_R 1
< #define OSNET_MSR_TYPE_W 2
< 
< static void osnet_set_cpu_exec_ctrl(struct kvm_vcpu *vcpu, bool enable)
< {
<         u32 cpu_exec_ctrl = kvm_x86_ops->get_cpu_exec_ctrl(vcpu);
< 
<         if (enable) {
<                 cpu_exec_ctrl |= CPU_BASED_HLT_EXITING;
<         } else {
<                 cpu_exec_ctrl &= ~CPU_BASED_HLT_EXITING;
<         }
< 
<         kvm_x86_ops->vmcs_write32(CPU_BASED_VM_EXEC_CONTROL, cpu_exec_ctrl);
< }
< 
< static void osnet_dump_vmcs(void)
< {
<         u64 io_bitmap_a;
<         u64 io_bitmap_a_high;
<         u64 io_bitmap_b;
<         u64 io_bitmap_b_high;
< 
<         io_bitmap_a = kvm_x86_ops->vmcs_read64(IO_BITMAP_A);
<         io_bitmap_a_high = kvm_x86_ops->vmcs_read64(IO_BITMAP_A_HIGH);
<         io_bitmap_b = kvm_x86_ops->vmcs_read64(IO_BITMAP_B);
<         io_bitmap_b_high = kvm_x86_ops->vmcs_read64(IO_BITMAP_B_HIGH);
< 
<         kvm_x86_ops->dump_vmcs();
<         pr_err("io bitmap a: 0x%016llx\n", io_bitmap_a);
<         pr_err("io bitmap a high: 0x%016llx\n", io_bitmap_a_high);
<         pr_err("io bitmap b: 0x%016llx\n", io_bitmap_b);
<         pr_err("io bitmap b high: 0x%016llx\n", io_bitmap_b_high);
< }
< 
< static void osnet_set_timer_vcpu_msr_bitmap(struct kvm_vcpu *vcpu, bool enable)
< {
<         u32 msr;
<         bool apicv_active = vcpu->arch.apic && vcpu->arch.apicv_active;
< 
<         if (enable) {
<                 msr = APIC_BASE_MSR + (APIC_TMICT >> 4);
<                 kvm_x86_ops->enable_intercept_vcpu_msr_x2apic(vcpu, msr, OSNET_MSR_TYPE_W,
<                                                               apicv_active);
< 
<                 msr = APIC_BASE_MSR + (APIC_TMCCT >> 4);
<                 kvm_x86_ops->enable_intercept_vcpu_msr_x2apic(vcpu, msr, OSNET_MSR_TYPE_R,
<                                                               apicv_active);
<                 msr = APIC_BASE_MSR + (APIC_TDCR >> 4);
<                 kvm_x86_ops->enable_intercept_vcpu_msr_x2apic(vcpu, msr, OSNET_MSR_TYPE_W,
<                                                               apicv_active);
<         } else {
<                 msr = APIC_BASE_MSR + (APIC_TMICT >> 4);
<                 kvm_x86_ops->disable_intercept_vcpu_msr_x2apic(vcpu, msr, OSNET_MSR_TYPE_W,
<                                                                apicv_active);
< 
<                 msr = APIC_BASE_MSR + (APIC_TMCCT >> 4);
<                 kvm_x86_ops->disable_intercept_vcpu_msr_x2apic(vcpu, msr, OSNET_MSR_TYPE_R,
<                                                                apicv_active);
<                 msr = APIC_BASE_MSR + (APIC_TDCR >> 4);
<                 kvm_x86_ops->disable_intercept_vcpu_msr_x2apic(vcpu, msr, OSNET_MSR_TYPE_W,
<                                                                apicv_active);
<         }
< }
< 
< static void osnet_set_icr_vcpu_msr_bitmap(struct kvm_vcpu *vcpu, bool enable)
< {
<         u32 msr;
<         bool apicv_active = vcpu->arch.apic && vcpu->arch.apicv_active;
< 
<         if (enable) {
<                 msr = APIC_BASE_MSR + (APIC_ICR >> 4);
<                 kvm_x86_ops->enable_intercept_vcpu_msr_x2apic(vcpu, msr, OSNET_MSR_TYPE_W,
<                                                               apicv_active);
< 
<                 //msr = APIC_BASE_MSR + (APIC_ICR2 >> 4);
<                 //kvm_x86_ops->enable_intercept_msr_x2apic(msr, OSNET_MSR_TYPE_W,
<                 //                                         apicv_active);
<         } else {
<                 msr = APIC_BASE_MSR + (APIC_ICR >> 4);
<                 kvm_x86_ops->disable_intercept_vcpu_msr_x2apic(vcpu, msr, OSNET_MSR_TYPE_W,
<                                                                apicv_active);
< 
<                 //msr = APIC_BASE_MSR + (APIC_ICR2 >> 4);
<                 //kvm_x86_ops->disable_intercept_msr_x2apic(msr, OSNET_MSR_TYPE_W,
<                 //                                         apicv_active);
<         }
< }
< 
< static void osnet_set_lapic(bool oneshot, bool timer_vector, u32 val)
< {
<         if (oneshot) {
<                 if (timer_vector)
<                         apic_write(APIC_LVTT, LOCAL_TIMER_VECTOR);
<                 else
<                         apic_write(APIC_LVTT, POSTED_INTR_VECTOR);
<         } else {
<                 if (timer_vector)
<                         apic_write(APIC_LVTT, 0x20000 | LOCAL_TIMER_VECTOR);
<                 else
<                         apic_write(APIC_LVTT, 0x20000 | POSTED_INTR_VECTOR);
<         }
< 
<         apic_write(APIC_TMICT, val);
< }
< 
< static void osnet_set_msr_bitmap(struct kvm_vcpu *vcpu, bool enable_private)
< {
<         if (enable_private)
<                 kvm_x86_ops->set_msr_bitmap(vcpu);
<         else
<                 kvm_x86_ops->restore_msr_bitmap(vcpu);
< }
< 
< static unsigned long osnet_setup_dtid(struct kvm_vcpu *vcpu,
<                                       unsigned long gpa)
< {
<         unsigned long ret;
< 
<         ret = osnet_map_pid(vcpu, gpa);
<         pr_info("vcpu(%d) maps pid(%d)\n", vcpu->vcpu_id, current->pid);
< 
<         osnet_set_cpu_exec_ctrl(vcpu, false);
<         osnet_set_msr_bitmap(vcpu, true);
<         osnet_set_timer_vcpu_msr_bitmap(vcpu, false);
<         osnet_set_lapic(false, false, 0x616d);
< 
<         return ret;
< }
< 
< static unsigned long osnet_restore_dtid(struct kvm_vcpu *vcpu,
<                                         unsigned long gpa)
< {
<         unsigned long ret;
< 
<         ret = osnet_unmap_pid(vcpu, gpa);
<         pr_info("vcpu(%d) unmaps pid(%d)\n", vcpu->vcpu_id, current->pid);
< 
<         osnet_set_cpu_exec_ctrl(vcpu, true);
<         osnet_set_timer_vcpu_msr_bitmap(vcpu, true);
<         osnet_set_lapic(true, true, 0x616d);
<         osnet_set_msr_bitmap(vcpu, false);
< 
<         return ret;
< }
< 
< static unsigned long osnet_get_clockevent_factor(const char *query)
< {
<         unsigned long ret;
<         unsigned long clock_events;
<         struct clock_event_device *lapic_events;
<         struct clock_event_device *evt;
< 
<         clock_events = kallsyms_lookup_name("lapic_events");
<         lapic_events = (struct clock_event_device *)clock_events;
<         evt = this_cpu_ptr(lapic_events);
< 
<         if (strcmp(query, "mult") == 0)
<                 ret = evt->mult;
<         else if (strcmp(query, "shift") == 0)
<                 ret = evt->shift;
<         else
<                 ret = 0;
< 
<         return ret;
< }
< 
< static void osnet_test(struct kvm_vcpu *vcpu, unsigned long arg)
< {
<         gfn_t gfn;
<         kvm_pfn_t pfn;
<         struct page *page;
<         char *data;
< 
<         gfn = gpa_to_gfn(arg);
<         pfn = gfn_to_pfn(vcpu->kvm, gfn);
<         page = pfn_to_page(pfn);
<         data = (char *)kmap(page);
<         data[0] = 'k';
<         kunmap(page);
< 
<         pr_info("gpa: 0x%lx\n", arg);
<         pr_info("pfn: 0x%llx\n", pfn);
<         pr_info("paddr: 0x%llx\n", virt_to_phys((void *)data));
< }
< 
< static void osnet_print_mvm(struct kvm_vcpu *vcpu)
< {
<         kvm_x86_ops->print_mvm(vcpu);
< }
< 
< static void osnet_print_cpumap(struct kvm_vcpu *vcpu)
< {
<         struct osnet_cpumap *cpumap;
< 
<         cpumap = &(vcpu->kvm->osnet_cpumap);
<         pr_info("path:  %s\n", cpumap->path);
<         pr_info("valid: %d\n", cpumap->is_valid);
<         for (unsigned int i = 0; i < cpumap->nvcpus; i++)
<                 pr_info("vcpu-pcpu: %d\t%d\n", i, cpumap->pcpus[i]);
< }
< #endif
< 
6641,6707c6153
<                 break;
< #if OSNET_MVM
< 	case KVM_HC_GET_CLOCKEVENT_MULT:
< 		ret = osnet_get_clockevent_factor("mult");
<                 break;
< 	case KVM_HC_GET_CLOCKEVENT_SHIFT:
< 		ret = osnet_get_clockevent_factor("shift");
<                 break;
<         /* TODO: remove */
<         case KVM_HC_GET_X2APIC_ID:
<                 ret = osnet_get_x2apic_id();
<                 break;
<         case KVM_HC_SET_X2APIC_ID:
<                 osnet_setup_x2apic_id(vcpu);
<                 ret = 0;
<                 break;
<         case KVM_HC_RESTORE_X2APIC_ID:
<                 osnet_restore_x2apic_id(vcpu);
<                 ret = 0;
<                 break;
<         case KVM_HC_SET_CPU_EXEC_VMCS:
<                 osnet_set_cpu_exec_ctrl(vcpu, false);
<                 ret = 0;
<                 break;
<         case KVM_HC_RESTORE_CPU_EXEC_VMCS:
<                 osnet_set_cpu_exec_ctrl(vcpu, true);
<                 ret = 0;
<                 break;
<         case KVM_HC_DUMP_VMCS:
<                 osnet_dump_vmcs();
<                 ret = 0;
<                 break;
<         case KVM_HC_DISABLE_INTERCEPT_WRMSR_ICR:
<                 osnet_set_icr_vcpu_msr_bitmap(vcpu, false);
<                 pr_info("disable intercept wrmsr icr\n");
<                 ret = 0;
<                 break;
<         case KVM_HC_ENABLE_INTERCEPT_WRMSR_ICR:
<                 osnet_set_icr_vcpu_msr_bitmap(vcpu, true);
<                 pr_info("enable intercept wrmsr icr\n");
<                 ret = 0;
<                 break;
<         case KVM_HC_SETUP_DTID:
<                 ret = osnet_setup_dtid(vcpu, a0);
<                 break;
<         case KVM_HC_RESTORE_DTID:
<                 ret = osnet_restore_dtid(vcpu, a0);
<                 break;
<         case KVM_HC_TEST:
<                 osnet_test(vcpu, a0);
<                 osnet_print_mvm(vcpu);
<                 osnet_print_cpumap(vcpu);
<                 ret = 0;
<                 break;
<         case KVM_HC_PAGE_WALK:
<                 ret = hypercall_page_walk(vcpu, a0);
<                 break;
<         case KVM_HC_MAP_PID:
<                 ret = osnet_map_pid(vcpu, a0);
<                 pr_info("vcpu(%d) maps pid(%d)\n", vcpu->vcpu_id, current->pid);
<                 break;
<         case KVM_HC_UNMAP_PID:
<                 ret = osnet_unmap_pid(vcpu, a0);
<                 pr_info("vcpu(%d) unmaps pid(%d)\n", vcpu->vcpu_id,
<                                                      current->pid);
<                 break;
< #endif
---
> 		break;

diff -r big/x86-kvm/x86.h linux-4.10.1/arch/x86/kvm/x86.h
4,5c4
< //#include <linux/kvm_host.h>
< #include "../include/linux/kvm_host.h"
---
> #include <linux/kvm_host.h>

```

## Known issues

### asm/kvm_host.h

- hyperv related stuff is abandoned (don't we have it in x86-kvm??)
    - struct hv_message
    - HV_SYNIC_SINT_COUNT
    - HV_SYNIC_STIMER_COUNT
    - HV_X64_MSR_CRASH_PARAMS
    - HV_REFERENCE_TSC_PAGE
- function __default_cpu_present_to_apicid

### virt/kvm/kvm_main.c

- struct mmu_notifier_ops has changed in linux/mmu_notifier.h, implementation of ops in kvm also needs changing
- Missing functions:
    - In kvm_create_vm(): mmdrop?
    - macro access_ok?
    - single_task_running
    - prepare_to_swait
    - swake_up
    - ACCESS_ONCE
    - sigset_from_compat
- struct vm_fault
- struct task_struct
