/**
 * @brief %cpuidpp declarations.
 * @file
 *
 * @copyright © 2017 Sergiu Deitsch. Distributed under the Boost Software
 * License, Version 1.0. (See accompanying file LICENSE or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef CPUIDPP_CPUIDPP_HPP
#define CPUIDPP_CPUIDPP_HPP

#if defined(_MSVC_LANG) && (_MSVC_LANG < 201402L)
#error cpuidpp requires a C++11 compiler
#endif // defined(_MSVC_LANG) && _MSVC_LANG <= 201103L

#include <string>

#include <cpuidpp/export.hpp>

namespace cpuidpp {

//! Indicates whether Onboard thermal control MSRs for ACPI is supported.
CPUIDPP_EXPORT bool acpi();
//! Indicates whether Intel ADX (Multi-Precision Add-Carry Instruction Extensions) is supported.
CPUIDPP_EXPORT bool adx();
//! Indicates whether the AES instruction set is supported.
CPUIDPP_EXPORT bool aes();
//! Indicates whether Onboard Advanced Programmable Interrupt Controller is supported.
CPUIDPP_EXPORT bool apic();
//! Indicates whether Advanced Vector Extensions are supported.
CPUIDPP_EXPORT bool avx();
//! Indicates whether Advanced Vector Extensions 2 are supported.
CPUIDPP_EXPORT bool avx2();
//! Indicates whether AVX-512 Multiply Accumulation Single precision is supported.
CPUIDPP_EXPORT bool avx512_4fmaps();
//! Indicates whether AVX-512 Neural Network instructions are supported.
CPUIDPP_EXPORT bool avx512_4vnniw();
//! Indicates whether AVX-512 Byte and Word instructions are supported.
CPUIDPP_EXPORT bool avx512bw();
//! Indicates whether AVX-512 Conflict Detection Instructions are supported.
CPUIDPP_EXPORT bool avx512cd();
//! Indicates whether AVX-512 Doubleword and Quadword Instructions are supported.
CPUIDPP_EXPORT bool avx512dq();
//! Indicates whether AVX-512 Exponential and Reciprocal Instructions are supported.
CPUIDPP_EXPORT bool avx512er();
//! Indicates whether AVX-512 Foundation is supported.
CPUIDPP_EXPORT bool avx512f();
//! Indicates whether AVX-512 Integer Fused Multiply-Add Instructions are supported.
CPUIDPP_EXPORT bool avx512ifma();
//! Indicates whether AVX-512 Prefetch Instructions are supported.
CPUIDPP_EXPORT bool avx512pf();
//! Indicates whether AVX-512 Vector Bit Manipulation Instructions are supported.
CPUIDPP_EXPORT bool avx512vbmi();
//! Indicates whether AVX-512 Vector Length Extensions are supported.
CPUIDPP_EXPORT bool avx512vl();
//! Indicates whether AVX-512 Vector Population Count D/Q are supported.
CPUIDPP_EXPORT bool avx512vpopcntdq();
//! Indicates whether the Bit Manipulation Instruction Set 1 is supported.
CPUIDPP_EXPORT bool bmi1();
//! Indicates whether the Bit Manipulation Instruction Set 2 is supported.
CPUIDPP_EXPORT bool bmi2();
//! Indicates whether the @c CLFLUSHOPT instruction is supported.
CPUIDPP_EXPORT bool clflushopt();
//! Indicates whether the @c CLFLUSH instruction is supported.
CPUIDPP_EXPORT bool clfsh();
//! Indicates whether the @c CLWB instruction is supported.
CPUIDPP_EXPORT bool clwb();
//! Indicates whether the Conditional move and @c FCMOV instructions are supported.
CPUIDPP_EXPORT bool cmov();
//! Indicates whether L1 Context ID is supported.
CPUIDPP_EXPORT bool cnxt_id();
//! Indicates whether the @c CMPXCHG16B instruction is supported.
CPUIDPP_EXPORT bool cx16();
//! Indicates whether the CMPXCHG8 (compare-and-swap) instruction is supported.
CPUIDPP_EXPORT bool cx8();
//! Indicates whether Data breakpoint extensions are supported.
CPUIDPP_EXPORT bool dbx();
//! Indicates whether Direct cache access for DMA writes is supported.
CPUIDPP_EXPORT bool dca();
//! Indicates whether debugging extensions (CR4 bit 3) are supported.
CPUIDPP_EXPORT bool de();
//! Indicates whether Debug store: save trace of executed jumps are supported.
CPUIDPP_EXPORT bool ds();
//! Indicates whether CPL qualified debug store is supported.
CPUIDPP_EXPORT bool ds_cpl();
//! Indicates whether 64-bit debug store (edx bit 21) is supported.
CPUIDPP_EXPORT bool dtes64();
//! Indicates whether Enhanced REP MOVSB/STOSB is supported.
CPUIDPP_EXPORT bool erms();
//! Indicates whether Enhanced SpeedStep is supported.
CPUIDPP_EXPORT bool eist();
//! Indicates whether Extended APIC space is supported.
CPUIDPP_EXPORT bool extapic();
//! Indicates whether F16C (half-precision) FP is supported.
CPUIDPP_EXPORT bool f16c();
//! Indicates whether Fused multiply-add (FMA3) is supported.
CPUIDPP_EXPORT bool fma();
//! Indicates whether onboard x87 FPU is supported.
CPUIDPP_EXPORT bool fpu();
//! Indicates whether access to base of @c %fs and @c %gs is supported.
CPUIDPP_EXPORT bool fsgsbase();
//! Indicates whether @c FXSAVE, @c FXRESTOR instructions, CR4 bit 9 are supported.
CPUIDPP_EXPORT bool fxsr();
//! Indicates whether FXSAVE/FXRSTOR optimizations are supported.
CPUIDPP_EXPORT bool fxsr_opt();
//! Indicates whether Transactional Synchronization Extensions are supported.
CPUIDPP_EXPORT bool hle();
//! Indicates whether Hyper-threading is supported.
CPUIDPP_EXPORT bool htt();
//! Indicates whether we are running on a hypervisor (always 0 on a real CPU, but also with some hypervisors).
CPUIDPP_EXPORT bool hypervisor();
//! Indicates whether this is a IA64 processor emulating x86.
CPUIDPP_EXPORT bool ia64();
//! Indicates whether Intel Processor Trace is supported.
CPUIDPP_EXPORT bool intel_pt();
//! Indicates whether the @c INVPCID instruction is supported.
CPUIDPP_EXPORT bool invpcid();
//! Indicates whether Long mode is active.
CPUIDPP_EXPORT bool lm();
//! Indicates whether the Machine Check Architecture is supported.
CPUIDPP_EXPORT bool mca();
//! Indicates whether Machine Check Exception is supported.
CPUIDPP_EXPORT bool mce();
//! Indicates whether MMX instructions are supported.
CPUIDPP_EXPORT bool mmx();
//! Indicates whether Extended MMX is supported.
CPUIDPP_EXPORT bool mmxext();
//! Indicates whether @c MONITOR and @c MWAIT instructions are supported.
CPUIDPP_EXPORT bool monitor();
//! Indicates whether the @c MOVBE instruction (big-endian) is supported.
CPUIDPP_EXPORT bool movbe();
//! Indicates whether the system is multiprocessor capable.
CPUIDPP_EXPORT bool mp();
//! Indicates whether Intel MPX (Memory Protection Extensions) is supported.
CPUIDPP_EXPORT bool mpx();
//! Indicates whether Model-specific registers are supported.
CPUIDPP_EXPORT bool msr();
//! Indicates whether Memory Type Range Registers are supported.
CPUIDPP_EXPORT bool mtrr();
//! Indicates whether NX bit is supported.
CPUIDPP_EXPORT bool nx();
//! Indicates whether PKU is enabled by OS.
CPUIDPP_EXPORT bool ospke();
//! Indicates whether @c XSAVE is enabled by OS.
CPUIDPP_EXPORT bool oxsave();
//! Indicates whether Physical Address Extension is supported.
CPUIDPP_EXPORT bool pae();
//! Indicates whether the Page Attribute Table is supported.
CPUIDPP_EXPORT bool pat();
//! Indicates whether Pending Break Enable (PBE# pin) wakeup is supported.
CPUIDPP_EXPORT bool pbe();
//! Indicates whether Process context identifiers (CR4 bit 17) are supported.
CPUIDPP_EXPORT bool pcid();
//! Indicates whether the @c PCLMULQDQ instruction is supported.
CPUIDPP_EXPORT bool pclmulqdq();
//! Indicates whether @c PCOMMIT instruction is supported.
CPUIDPP_EXPORT bool pcommit();
//! Indicates whether L2I perf counter extensions are supported.
CPUIDPP_EXPORT bool pcx_l2i();
//! Indicates whether Perfmon and debug capability is supported.
CPUIDPP_EXPORT bool pdcm();
//! Indicates whether Gibibyte pages are supported.
CPUIDPP_EXPORT bool pdpe1gb();
//! Indicates whether Core performance counter extensions are supported.
CPUIDPP_EXPORT bool perfctr_core();
//! Indicates whether NB performance counter extensions are supported.
CPUIDPP_EXPORT bool perfctr_nb();
//! Indicates whether Performance TSC is supported.
CPUIDPP_EXPORT bool perftsc();
//! Indicates whether the Page Global Enable bit in CR4 is supported.
CPUIDPP_EXPORT bool pge();
//! Indicates whether Memory Protection Keys for User-mode pages is supported.
CPUIDPP_EXPORT bool pku();
//! Indicates whether the @c POPCNT instruction is supported.
CPUIDPP_EXPORT bool popcnt();
//! Indicates whether Platform Quality of Service Enforcement is supported.
CPUIDPP_EXPORT bool pqe();
//! Indicates whether Platform Quality of Service Monitoring is supported.
CPUIDPP_EXPORT bool pqm();
//! Indicates whether the @c PREFETCHWT1 instruction is supported.
CPUIDPP_EXPORT bool prefetchwt1();
//! Indicates whether the Page Size Extension is supported.
CPUIDPP_EXPORT bool pse();
//! Indicates whether the 36-bit page size extension is supported.
CPUIDPP_EXPORT bool pse36();
//! Indicates whether the Processor Serial Number is supported.
CPUIDPP_EXPORT bool psn();
//! Indicates whether Read Processor ID is supported.
CPUIDPP_EXPORT bool rdpid();
//! Indicates whether the @c RDRAND (on-chip random number generator) instruction is supported.
CPUIDPP_EXPORT bool rdrnd();
//! Indicates whether the @c RDSEED instruction is supported.
CPUIDPP_EXPORT bool rdseed();
//! Indicates whether the @c RDTSCP instruction is supported.
CPUIDPP_EXPORT bool rdtscp();
//! Indicates whether Transactional Synchronization Extensions are supported.
CPUIDPP_EXPORT bool rtm();
//! Indicates whether Silicon Debug interface is supported.
CPUIDPP_EXPORT bool sdbg();
//! Indicates whether the @c SYSENTER and @c SYSEXIT instructions are supported.
CPUIDPP_EXPORT bool sep();
//! Indicates whether Software Guard Extensions are supported.
CPUIDPP_EXPORT bool sgx();
//! Indicates whether SGX Launch Configuration is supported.
CPUIDPP_EXPORT bool sgx_lc();
//! Indicates whether Intel SHA extensions are supported.
CPUIDPP_EXPORT bool sha();
//! Indicates whether Supervisor Mode Access Prevention is supported.
CPUIDPP_EXPORT bool smap();
//! Indicates whether Supervisor-Mode Execution Prevention is supported.
CPUIDPP_EXPORT bool smep();
//! Indicates whether Safer Mode Extensions are supported.
CPUIDPP_EXPORT bool smx();
//! Indicates whether CPU cache supports self-snoop is supported.
CPUIDPP_EXPORT bool ss();
//! Indicates whether SSE instructions are supported.
CPUIDPP_EXPORT bool sse();
//! Indicates whether SSE2 instructions are supported.
CPUIDPP_EXPORT bool sse2();
//! Indicates whether SSE3 instructions are supported.
CPUIDPP_EXPORT bool sse3();
//! Indicates whether SSE4.1 instructions are supported.
CPUIDPP_EXPORT bool sse4_1();
//! Indicates whether SSE4.2 instructions are supported.
CPUIDPP_EXPORT bool sse4_2();
//! Indicates whether SSSE3 instructions are supported.
CPUIDPP_EXPORT bool ssse3();
//! Indicates whether Thermal monitor automatically limits temperature is supported.
CPUIDPP_EXPORT bool tm();
//! Indicates whether Thermal Monitor 2 is supported.
CPUIDPP_EXPORT bool tm2();
//! Indicates whether the Time Stamp Counter is supported.
CPUIDPP_EXPORT bool tsc();
//! Indicates whether APIC supports one-shot operation using a TSC deadline value.
CPUIDPP_EXPORT bool tsc_deadline();
//! Indicates whether User-mode Instruction Prevention is supported.
CPUIDPP_EXPORT bool umip();
//! Indicates whether virtual 8086 mode extensions (such as VIF, VIP, PIV) are supported.
CPUIDPP_EXPORT bool vme();
//! Indicates whether Virtual Machine eXtensions are supported.
CPUIDPP_EXPORT bool vmx();
//! Indicates whether x2APIC is supported.
CPUIDPP_EXPORT bool x2apic();
//! Indicates whether @c XSAVE, @c XRESTOR, @c XSETBV, @c XGETBV are supported.
CPUIDPP_EXPORT bool xsave();
//! Indicates whether sending task priority messages can be disabled.
CPUIDPP_EXPORT bool xtpr();
//! Returns the model of the CPU.
CPUIDPP_EXPORT const std::string& model();

/**
    * @brief Returns the vendor ID.
    *
    * The following are known manufacturer ID string:
    * * @c "AMDisbetter!" – early engineering samples of AMD K5 processor
    * * @c "AuthenticAMD" – AMD
    * * @c "CentaurHauls" – Centaur (Including some VIA CPU)
    * * @c "CyrixInstead" – Cyrix
    * * @c "GenuineIntel" – Intel
    * * @c "TransmetaCPU" – Transmeta
    * * @c "GenuineTMx86" – Transmeta
    * * @c "Geode by NSC" – National Semiconductor
    * * @c "NexGenDriven" – NexGen
    * * @c "RiseRiseRise" – Rise
    * * @c "SiS SiS SiS " – SiS
    * * @c "UMC UMC UMC " – UMC
    * * @c "VIA VIA VIA " – VIA
    * * @c "Vortex86 SoC" – Vortex
    *
    * The following are known ID strings from virtual machines:
    * * @c "KVMKVMKVM" – KVM
    * * @c "Microsoft Hv" – Microsoft Hyper-V or Windows Virtual PC
    * * @c " lrpepyh vr" – Parallels (it possibly should be @c "prl hyperv ",
    * but it is encoded as @c " lrpepyh vr")
    * * @c "VMwareVMware" – VMware
    * * @c "XenVMMXenVMM" – Xen HVM
    *
    */
CPUIDPP_EXPORT const std::string& vendor();

/**
 * @{
 * @name AMD feature flags
 * @brief CPU features specific to AMD processors.
 */

//! Indicates whether Advanced bit manipulation (@c LZCNT and @c POPCNT) is supported.
CPUIDPP_EXPORT bool abm();
//! Indicates whether 3DNow! is supported.
CPUIDPP_EXPORT bool amd_3dnow();
//! Indicates whether Extended 3DNow! is supported.
CPUIDPP_EXPORT bool amd_3dnowext();
//! Indicates whether the @c PREFETCH and @c PREFETCHW instructions are supported.
CPUIDPP_EXPORT bool amd_3dnowprefetch();
//! Indicates whether Hyperthreading is not valid.
CPUIDPP_EXPORT bool cmp_legacy();
//! Indicates whether CR8 in 32-bit mode is supported.
CPUIDPP_EXPORT bool cr8_legacy();
//! Indicates whether Instruction Based Sampling is supported.
CPUIDPP_EXPORT bool ibs();
//! Indicates whether LAHF/SAHF in long mode is supported.
CPUIDPP_EXPORT bool lahf_lm();
//! Indicates whether OS Visible Workaround is active.
CPUIDPP_EXPORT bool osvw();
//! Indicates whether the Misaligned SSE mode is supported.
CPUIDPP_EXPORT bool misalignsse();
//! Indicates whether @c SKINIT/STGI instructions are supported.
CPUIDPP_EXPORT bool skinit();
//! Indicates whether @c SYSCALL and @c SYSRET instructions are supported.
CPUIDPP_EXPORT bool syscall();
//! Secure Virtual Machine.
CPUIDPP_EXPORT bool svm();
//! Indicates whether SSE4a instructions are supported.
CPUIDPP_EXPORT bool sse4a();
//! Indicates whether the Watchdog timer is supported.
CPUIDPP_EXPORT bool wdt();
//! Indicates whether XOP instruction set is supported.
CPUIDPP_EXPORT bool xop();
//! Indicates whether Light Weight Profiling is supported.
CPUIDPP_EXPORT bool lwp();
//! Indicates whether 4 operands fused multiply-add is supported.
CPUIDPP_EXPORT bool fma4();
//! Indicates whether Translation Cache Extension is supported.
CPUIDPP_EXPORT bool tce();
//! Indicates whether NodeID MSR is supported.
CPUIDPP_EXPORT bool nodeid_msr();
//! Indicates whether Trailing Bit Manipulation is supported.
CPUIDPP_EXPORT bool tbm();
//! Indicates whether Topology Extensions are supported.
CPUIDPP_EXPORT bool topoext();

//! @}

} // namespace cpuidpp

#endif // !defined(CPUIDPP_CPUIDPP_HPP)
