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

//! %cpuidpp namespace.
namespace cpuidpp {

struct CPUIDImpl;

/**
 * @brief Represents a class allowing to query CPU features.
 *
 * @note The class @e cannot be instantiated.
 */
class CPUIDPP_EXPORT CPUID final
{
public:
    static bool abm();
    //! Indicates whether Onboard thermal control MSRs for ACPI is available.
    static bool acpi();
    static bool adx();
    //! Indicates whether the AES instruction set is available.
    static bool aes();
    //! Indicates whether 3DNow! is available.
    static bool amd_3dnow();
    //! Indicates whether Extended 3DNow! is available.
    static bool amd_3dnowext();
    //! Indicates whether the @c PREFETCH and @c PREFETCHW instructions are available.
    static bool amd_3dnowprefetch();
    //! Indicates whether Onboard Advanced Programmable Interrupt Controller is available.
    static bool apic();
    //! Indicates whether Advanced Vector Extensions are available.
    static bool avx();
    //! Indicates whether Advanced Vector Extensions 2 are available.
    static bool avx2();
    static bool avx512_4fmaps();
    static bool avx512_4vnniw();
    static bool avx512bw();
    static bool avx512cd();
    //! Indicates whether AVX-512 Doubleword and Quadword Instructions are available.
    static bool avx512dq();
    //! Indicates whether AVX-512 Exponential and Reciprocal Instructions are available.
    static bool avx512er();
    //! Indicates whether AVX-512 Foundation is available.
    static bool avx512f();
    static bool avx512ifma();
    //! Indicates whether AVX-512 Prefetch Instructions are available.
    static bool avx512pf();
    //! Indicates whether AVX-512 Vector Bit Manipulation Instructions are available.
    static bool avx512vbmi();
    static bool avx512vl();
    static bool avx512vpopcntdq();
    //! Indicates whether the Bit Manipulation Instruction Set 1 is available.
    static bool bmi1();
    //! Indicates whether the Bit Manipulation Instruction Set 2 is available.
    static bool bmi2();
    static bool clflushopt();
    //! Indicates whether the @c CLFLUSH instruction is available.
    static bool clfsh();
    static bool clwb();
    //! Indicates whether the Conditional move and @c FCMOV instructions are available.
    static bool cmov();
    static bool cmp_legacy();
    //! Indicates whether L1 Context ID is available.
    static bool cnxt_id();
    static bool cr8_legacy();
    //! Indicates whether the @c CMPXCHG16B instruction is available.
    static bool cx16();
    //! Indicates whether the CMPXCHG8 (compare-and-swap) instruction is available.
    static bool cx8();
    static bool dbx();
    //! Indicates whether Direct cache access for DMA writes is available.
    static bool dca();
    //! Indicates whether debugging extensions (CR4 bit 3) are available.
    static bool de();
    //! Indicates whether Debug store: save trace of executed jumps are available.
    static bool ds();
    //! Indicates whether CPL qualified debug store is available.
    static bool ds_cpl();
    //! Indicates whether 64-bit debug store (edx bit 21) is available.
    static bool dtes64();
    //! Indicates whether Enhanced REP MOVSB/STOSB is available.
    static bool erms();
    //! Indicates whether Enhanced SpeedStep is available.
    static bool est();
    static bool extapic();
    //! Indicates whether F16C (half-precision) FP support is available.
    static bool f16c();
    //! Indicates whether Fused multiply-add (FMA3) is available.
    static bool fma();
    static bool fma4();
    //! Indicates whether onboard x87 FPU is available.
    static bool fpu();
    //! Indicates whether access to base of @c %fs and @c %gs is available.
    static bool fsgsbase();
    //! Indicates whether @c FXSAVE, @c FXRESTOR instructions, CR4 bit 9 are available.
    static bool fxsr();
    static bool fxsr_opt();
    static bool hle();
    //! Indicates whether Hyper-threading is available.
    static bool htt();
    //! Indicates whether we are running on a hypervisor (always 0 on a real CPU, but also with some hypervisors).
    static bool hypervisor();
    //! Indicates whether this is a IA64 processor emulating x86.
    static bool ia64();
    static bool ibs();
    //! Indicates whether Intel Processor Trace is available.
    static bool intel_pt();
    //! Indicates whether the @c INVPCID instruction is available.
    static bool invpcid();
    static bool lahf_lm();
    static bool lm();
    static bool lwp();
    //! Indicates whether the Machine Check Architecture is available.
    static bool mca();
    //! Indicates whether Machine Check Exception is available.
    static bool mce();
    //! Indicates whether the Misaligned SSE mode is available.
    static bool misalignsse();
    //! Indicates whether MMX instructions are available.
    static bool mmx();
    //! Indicates whether Extended MMX is available.
    static bool mmxext();
    //! Indicates whether @c MONITOR and @c MWAIT instructions are available.
    static bool monitor();
    //! Indicates whether the @c MOVBE instruction (big-endian) is available.
    static bool movbe();
    static bool mp();
    static bool mpx();
    //! Indicates whether Model-specific registers are available.
    static bool msr();
    //! Indicates whether Memory Type Range Registers are available.
    static bool mtrr();
    static bool nodeid_msr();
    static bool nx();
    static bool ospke();
    static bool osvw();
    //! Indicates whether @c XSAVE is enabled by OS.
    static bool oxsave();
    static bool pae();
    //! Indicates whether the Page Attribute Table is available.
    static bool pat();
    //! Indicates whether Pending Break Enable (PBE# pin) wakeup support is available.
    static bool pbe();
    //! Indicates whether Process context identifiers (CR4 bit 17) are available.
    static bool pcid();
    //! Indicates whether @c PCLMULQDQ support is available.
    static bool pclmulqdq();
    static bool pcommit();
    static bool pcx_l2i();
    //! Indicates whether Perfmon and debug capability is available.
    static bool pdcm();
    static bool pdpe1gb();
    static bool perfctr_core();
    static bool perfctr_nb();
    static bool perftsc();
    //! Indicates whether the Page Global Enable bit in CR4 is available.
    static bool pge();
    //! Indicates whether Memory Protection Keys for User-mode pages is available.
    static bool pku();
    //! Indicates whether the @c POPCNT instruction is available.
    static bool popcnt();
    static bool pqe();
    static bool pqm();
    //! Indicates whether the @c PREFETCHWT1 instruction is available.
    static bool prefetchwt1();
    //! Indicates whether the Page Size Extension is available.
    static bool pse();
    //! Indicates whether the 36-bit page size extension is available.
    static bool pse36();
    //! Indicates whether the Processor Serial Number is available.
    static bool psn();
    static bool rdpid();
    //! Indicates whether RDRAND (on-chip random number generator) support is available.
    static bool rdrnd();
    static bool rdseed();
    static bool rdtscp();
    static bool rtm();
    //! Indicates whether Silicon Debug interface is available.
    static bool sdbg();
    //! Indicates whether the @c SYSENTER and @c SYSEXIT instructions are available.
    static bool sep();
    //! Indicates whether Software Guard Extensions are available.
    static bool sgx();
    static bool sgx_lc();
    static bool sha();
    static bool skinit();
    static bool smap();
    static bool smep();
    //! Indicates whether Safer Mode Extensions are available.
    static bool smx();
    //! Indicates whether CPU cache supports self-snoop is available.
    static bool ss();
    //! Indicates whether SSE instructions are available.
    static bool sse();
    //! Indicates whether SSE2 instructions are available.
    static bool sse2();
    //! Indicates whether SSE3 instructions are available.
    static bool sse3();
    //! Indicates whether SSE4.1 instructions are available.
    static bool sse4_1();
    //! Indicates whether SSE4.2 instructions are available.
    static bool sse4_2();
    //! Indicates whether SSE4a instructions are available.
    static bool sse4a();
    //! Indicates whether SSSE3 instructions are available.
    static bool ssse3();
    static bool svm();
    static bool syscall();
    static bool tbm();
    static bool tce();
    //! Indicates whether Thermal monitor automatically limits temperature is available.
    static bool tm();
    //! Indicates whether Thermal Monitor 2 is available.
    static bool tm2();
    static bool topoext();
    //! Indicates whether the Time Stamp Counter is available.
    static bool tsc();
    //! Indicates whether APIC supports one-shot operation using a TSC deadline value.
    static bool tsc_deadline();
    //! Indicates whether User-mode Instruction Prevention is available.
    static bool umip();
    //! Indicates whether virtual 8086 mode extensions (such as VIF, VIP, PIV) are available.
    static bool vme();
    //! Indicates whether Virtual Machine eXtensions are available.
    static bool vmx();
    static bool wdt();
    //! Indicates whether x2APIC support is available.
    static bool x2apic();
    static bool xop();
    //! Indicates whether @c XSAVE, @c XRESTOR, @c XSETBV, @c XGETBV are available.
    static bool xsave();
    //! Indicates whether sending task priority messages can be disabled.
    static bool xtpr();
    //! Returns the model of the CPU.
    static const std::string& model();

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
    static const std::string& vendor();

private:
    CPUID() = delete;
};

} // namespace cpuidpp

#endif // !defined(CPUIDPP_CPUIDPP_HPP)
