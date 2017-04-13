/**
 * @brief %cpuidpp implementation.
 * @file
 *
 * @copyright © 2017 Sergiu Deitsch. Distributed under the Boost Software
 * License, Version 1.0. (See accompanying file LICENSE or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include <cpuidpp/cpuidpp.hpp>

#include <algorithm>
#include <array>
#include <bitset>
#include <functional>
#include <locale>

#if defined(HAVE___GET_CPUID)
#include <cpuid.h>
#elif defined(HAVE___CPUID)
#include <intrin.h>
#endif

namespace cpuidpp {

namespace {

#if defined(HAVE___GET_CPUID)
inline void cpuid(unsigned* info, unsigned leaf)
{
    __get_cpuid(leaf, info, info + 1, info + 2, info + 3);
}
#elif defined(HAVE___CPUID)
inline void cpuid(unsigned* info, unsigned leaf)
{
    __cpuid(reinterpret_cast<int*>(info), static_cast<int>(leaf));
}
#else
/**
 * @brief Implements the CPUID instruction on platforms and compilers that don't
 *        provide it.
 *
 * @param info 4-byte array that will contain the content of the registers @c
 *        eax, @c ebx, @c ecx and @c edx.
 * @param leaf Information leaf: @c eax register.
 */
inline void cpuid(unsigned* info, unsigned leaf)
{
#if defined(__i386__) && defined(__PIC__)
    __asm__ (
        "xchgl %%ebx, %1\n\t"
        "cpuid\n\t"
        "xchgl %%ebx, %1\n\t"
        :
        "=a" (info[0]),
        "=r" (info[1]),
        "=c" (info[2]),
        "=d" (info[3])
        :
        "0" (leaf)
    );
#else
    __asm__ (
        "cpuid"
        :
        "=a" (info[0]),
        "=b" (info[1]),
        "=c" (info[2]),
        "=d" (info[3])
        :
        "a" (leaf)
    );
#endif // defined(__i386__) && defined(__PIC__)
}
#endif

#if defined(HAVE___GET_CPUID_COUNT)
inline void cpuidex(unsigned* info, unsigned leaf, unsigned subleaf)
{
    __get_cpuid_count(leaf, subleaf, info, info + 1, info + 2, info + 3);
}
#elif defined(HAVE___CPUIDEX)
inline void cpuidex(unsigned* info, unsigned leaf, unsigned subleaf)
{
    __cpuidex(reinterpret_cast<int*>(info), static_cast<int>(leaf),
            static_cast<int>(subleaf));
}
#else
inline void cpuidex(unsigned* info, unsigned leaf, unsigned subleaf)
{
    __asm__ (
        "cpuid"
        :
        "=a" (info[0]),
        "=b" (info[1]),
        "=c" (info[2]),
        "=d" (info[3])
        :
        "0" (leaf),
        "2" (subleaf)
    );
}
#endif

} // namespace

#define CPUIDPP_IMPL_FLAG(name, bit, member) \
    bool name() const                        \
    {                                        \
        return member.test(bit);             \
    }

struct CPUIDImpl
{
    CPUIDImpl()
    {
        std::array<unsigned, 4> info{};
        // EAX=0
        cpuid(info.data(), 0);

#define CPUIDPP_EXTRACT_CHAR(var, index1, index2) \
            static_cast<char>((var[index1] >> ((index2) * 8)) & 0xff)

        vendor =
        {
              CPUIDPP_EXTRACT_CHAR(info, 1, 0)
            , CPUIDPP_EXTRACT_CHAR(info, 1, 1)
            , CPUIDPP_EXTRACT_CHAR(info, 1, 2)
            , CPUIDPP_EXTRACT_CHAR(info, 1, 3)
            , CPUIDPP_EXTRACT_CHAR(info, 3, 0)
            , CPUIDPP_EXTRACT_CHAR(info, 3, 1)
            , CPUIDPP_EXTRACT_CHAR(info, 3, 2)
            , CPUIDPP_EXTRACT_CHAR(info, 3, 3)
            , CPUIDPP_EXTRACT_CHAR(info, 2, 0)
            , CPUIDPP_EXTRACT_CHAR(info, 2, 1)
            , CPUIDPP_EXTRACT_CHAR(info, 2, 2)
            , CPUIDPP_EXTRACT_CHAR(info, 2, 3)
        };

        info.fill(0);
        // EAX=1
        cpuid(info.data(), 1);

        f1_2 = info[2];
        f1_3 = info[3];

        info.fill(0);
        // EAX=7 ECX=0
        cpuidex(info.data(), 7, 0);

        f7_1 = info[1];
        f7_2 = info[2];
        f7_3 = info[3];

        info.fill(0);
        // EAX=0x80000000
        cpuid(info.data(), 0x80000000);

        const unsigned max_leaf = static_cast<unsigned>(info[0]);

        if (max_leaf >= 0x80000001 && vendor == "AuthenticAMD") {
            info.fill(0);
            // EAX=0x80000001
            cpuid(info.data(), 0x80000001);

            f80000001_2 = info[2];
            f80000001_3 = info[3];

            constexpr unsigned mask_0_9 = ((1U << 9U) - 1U);
            constexpr unsigned mask_0_17 = ((1U << 17U) - 1U);
            constexpr unsigned mask_0_12 = ((1U << 12U) - 1U);
            constexpr unsigned mask_12_17 = mask_0_17 ^ mask_0_12;

            f1_3 &= ~mask_0_9;
            f1_3 |= f80000001_3.to_ulong() & mask_0_9;
            f1_3 &= ~mask_12_17;
            f1_3 |= f80000001_3.to_ulong() & mask_12_17;
            f1_3[24] = f80000001_3[24]; // fxr
        }

        if (max_leaf >= 0x80000004) {
            model.reserve(48);

            info.fill(0);
            // EAX=0x80000002
            cpuid(info.data(), 0x80000002);

            model.append
            ({
                  CPUIDPP_EXTRACT_CHAR(info, 0, 0)
                , CPUIDPP_EXTRACT_CHAR(info, 0, 1)
                , CPUIDPP_EXTRACT_CHAR(info, 0, 2)
                , CPUIDPP_EXTRACT_CHAR(info, 0, 3)
                , CPUIDPP_EXTRACT_CHAR(info, 1, 0)
                , CPUIDPP_EXTRACT_CHAR(info, 1, 1)
                , CPUIDPP_EXTRACT_CHAR(info, 1, 2)
                , CPUIDPP_EXTRACT_CHAR(info, 1, 3)
                , CPUIDPP_EXTRACT_CHAR(info, 2, 0)
                , CPUIDPP_EXTRACT_CHAR(info, 2, 1)
                , CPUIDPP_EXTRACT_CHAR(info, 2, 2)
                , CPUIDPP_EXTRACT_CHAR(info, 2, 3)
                , CPUIDPP_EXTRACT_CHAR(info, 3, 0)
                , CPUIDPP_EXTRACT_CHAR(info, 3, 1)
                , CPUIDPP_EXTRACT_CHAR(info, 3, 2)
                , CPUIDPP_EXTRACT_CHAR(info, 3, 3)
            });

            info.fill(0);
            // EAX=0x80000003
            cpuid(info.data(), 0x80000003);

            model.append
            ({
                  CPUIDPP_EXTRACT_CHAR(info, 0, 0)
                , CPUIDPP_EXTRACT_CHAR(info, 0, 1)
                , CPUIDPP_EXTRACT_CHAR(info, 0, 2)
                , CPUIDPP_EXTRACT_CHAR(info, 0, 3)
                , CPUIDPP_EXTRACT_CHAR(info, 1, 0)
                , CPUIDPP_EXTRACT_CHAR(info, 1, 1)
                , CPUIDPP_EXTRACT_CHAR(info, 1, 2)
                , CPUIDPP_EXTRACT_CHAR(info, 1, 3)
                , CPUIDPP_EXTRACT_CHAR(info, 2, 0)
                , CPUIDPP_EXTRACT_CHAR(info, 2, 1)
                , CPUIDPP_EXTRACT_CHAR(info, 2, 2)
                , CPUIDPP_EXTRACT_CHAR(info, 2, 3)
                , CPUIDPP_EXTRACT_CHAR(info, 3, 0)
                , CPUIDPP_EXTRACT_CHAR(info, 3, 1)
                , CPUIDPP_EXTRACT_CHAR(info, 3, 2)
                , CPUIDPP_EXTRACT_CHAR(info, 3, 3)
            });

            info.fill(0);
            // EAX=0x80000004
            cpuid(info.data(), 0x80000004);

            model.append
            ({
                  CPUIDPP_EXTRACT_CHAR(info, 0, 0)
                , CPUIDPP_EXTRACT_CHAR(info, 0, 1)
                , CPUIDPP_EXTRACT_CHAR(info, 0, 2)
                , CPUIDPP_EXTRACT_CHAR(info, 0, 3)
                , CPUIDPP_EXTRACT_CHAR(info, 1, 0)
                , CPUIDPP_EXTRACT_CHAR(info, 1, 1)
                , CPUIDPP_EXTRACT_CHAR(info, 1, 2)
                , CPUIDPP_EXTRACT_CHAR(info, 1, 3)
                , CPUIDPP_EXTRACT_CHAR(info, 2, 0)
                , CPUIDPP_EXTRACT_CHAR(info, 2, 1)
                , CPUIDPP_EXTRACT_CHAR(info, 2, 2)
                , CPUIDPP_EXTRACT_CHAR(info, 2, 3)
                , CPUIDPP_EXTRACT_CHAR(info, 3, 0)
                , CPUIDPP_EXTRACT_CHAR(info, 3, 1)
                , CPUIDPP_EXTRACT_CHAR(info, 3, 2)
                , CPUIDPP_EXTRACT_CHAR(info, 3, 3)
            });

            // Trim whitespace left and right
            model.erase(model.begin(), std::find_if_not(model.begin(), model.end(),
                std::bind(std::isspace<char>, std::placeholders::_1, std::locale::classic())));
            model.erase(std::find_if_not(model.rbegin(), model.rend(),
                std::bind(std::isspace<char>, std::placeholders::_1, std::locale::classic())).base(), model.end());
        }
    }

    CPUIDPP_IMPL_FLAG(fpu,              0, f1_3)
    CPUIDPP_IMPL_FLAG(vme,              1, f1_3)
    CPUIDPP_IMPL_FLAG(de,               2, f1_3)
    CPUIDPP_IMPL_FLAG(pse,              3, f1_3)
    CPUIDPP_IMPL_FLAG(tsc,              4, f1_3)
    CPUIDPP_IMPL_FLAG(msr,              5, f1_3)
    CPUIDPP_IMPL_FLAG(pae,              6, f1_3)
    CPUIDPP_IMPL_FLAG(mce,              7, f1_3)
    CPUIDPP_IMPL_FLAG(cx8,              8, f1_3)
    CPUIDPP_IMPL_FLAG(apic,             9, f1_3)
    CPUIDPP_IMPL_FLAG(sep,              11, f1_3)
    CPUIDPP_IMPL_FLAG(mtrr,             12, f1_3)
    CPUIDPP_IMPL_FLAG(pge,              13, f1_3)
    CPUIDPP_IMPL_FLAG(mca,              14, f1_3)
    CPUIDPP_IMPL_FLAG(cmov,             15, f1_3)
    CPUIDPP_IMPL_FLAG(pat,              16, f1_3)
    CPUIDPP_IMPL_FLAG(pse36,            17, f1_3)
    CPUIDPP_IMPL_FLAG(psn,              18, f1_3)
    CPUIDPP_IMPL_FLAG(clfsh,            19, f1_3)
    CPUIDPP_IMPL_FLAG(ds,               21, f1_3)
    CPUIDPP_IMPL_FLAG(acpi,             22, f1_3)
    CPUIDPP_IMPL_FLAG(mmx,              23, f1_3)
    CPUIDPP_IMPL_FLAG(fxsr,             24, f1_3)
    CPUIDPP_IMPL_FLAG(sse,              25, f1_3)
    CPUIDPP_IMPL_FLAG(sse2,             26, f1_3)
    CPUIDPP_IMPL_FLAG(ss,               27, f1_3)
    CPUIDPP_IMPL_FLAG(htt,              28, f1_3)
    CPUIDPP_IMPL_FLAG(tm,               29, f1_3)
    CPUIDPP_IMPL_FLAG(ia64,             30, f1_3)
    CPUIDPP_IMPL_FLAG(pbe,              31, f1_3)

    CPUIDPP_IMPL_FLAG(sse3,             0, f1_2)
    CPUIDPP_IMPL_FLAG(pclmulqdq,        1, f1_2)
    CPUIDPP_IMPL_FLAG(dtes64,           2, f1_2)
    CPUIDPP_IMPL_FLAG(monitor,          3, f1_2)
    CPUIDPP_IMPL_FLAG(ds_cpl,           4, f1_2)
    CPUIDPP_IMPL_FLAG(vmx,              5, f1_2)
    CPUIDPP_IMPL_FLAG(smx,              6, f1_2)
    CPUIDPP_IMPL_FLAG(est,              7, f1_2)
    CPUIDPP_IMPL_FLAG(tm2,              8, f1_2)
    CPUIDPP_IMPL_FLAG(ssse3,            9, f1_2)
    CPUIDPP_IMPL_FLAG(cnxt_id,          10, f1_2)
    CPUIDPP_IMPL_FLAG(sdbg,             11, f1_2)
    CPUIDPP_IMPL_FLAG(fma,              12, f1_2)
    CPUIDPP_IMPL_FLAG(cx16,             13, f1_2)
    CPUIDPP_IMPL_FLAG(xtpr,             14, f1_2)
    CPUIDPP_IMPL_FLAG(pdcm,             15, f1_2)

    CPUIDPP_IMPL_FLAG(pcid,             17, f1_2)
    CPUIDPP_IMPL_FLAG(dca,              18, f1_2)
    CPUIDPP_IMPL_FLAG(sse4_1,           19, f1_2)
    CPUIDPP_IMPL_FLAG(sse4_2,           20, f1_2)
    CPUIDPP_IMPL_FLAG(x2apic,           21, f1_2)
    CPUIDPP_IMPL_FLAG(movbe,            22, f1_2)
    CPUIDPP_IMPL_FLAG(popcnt,           23, f1_2)
    CPUIDPP_IMPL_FLAG(tsc_deadline,     24, f1_2)
    CPUIDPP_IMPL_FLAG(aes,              25, f1_2)
    CPUIDPP_IMPL_FLAG(xsave,            26, f1_2)
    CPUIDPP_IMPL_FLAG(oxsave,           27, f1_2)
    CPUIDPP_IMPL_FLAG(avx,              28, f1_2)
    CPUIDPP_IMPL_FLAG(f16c,             29, f1_2)
    CPUIDPP_IMPL_FLAG(rdrnd,            30, f1_2)
    CPUIDPP_IMPL_FLAG(hypervisor,       31, f1_2)

    CPUIDPP_IMPL_FLAG(fsgsbase,         0, f7_1)

    CPUIDPP_IMPL_FLAG(sgx,              2, f7_1)
    CPUIDPP_IMPL_FLAG(bmi1,             3, f7_1)
    CPUIDPP_IMPL_FLAG(hle,              4, f7_1)
    CPUIDPP_IMPL_FLAG(avx2,             5, f7_1)

    CPUIDPP_IMPL_FLAG(smep,             7, f7_1)
    CPUIDPP_IMPL_FLAG(bmi2,             8, f7_1)
    CPUIDPP_IMPL_FLAG(erms,             9, f7_1)
    CPUIDPP_IMPL_FLAG(invpcid,          10, f7_1)
    CPUIDPP_IMPL_FLAG(rtm,              11, f7_1)
    CPUIDPP_IMPL_FLAG(pqm,              12, f7_1)

    CPUIDPP_IMPL_FLAG(mpx,              14, f7_1)
    CPUIDPP_IMPL_FLAG(pqe,              15, f7_1)
    CPUIDPP_IMPL_FLAG(avx512f,          16, f7_1)
    CPUIDPP_IMPL_FLAG(avx512dq,         17, f7_1)
    CPUIDPP_IMPL_FLAG(rdseed,           18, f7_1)
    CPUIDPP_IMPL_FLAG(adx,              19, f7_1)
    CPUIDPP_IMPL_FLAG(smap,             20, f7_1)
    CPUIDPP_IMPL_FLAG(avx512ifma,       21, f7_1)
    CPUIDPP_IMPL_FLAG(pcommit,          22, f7_1)
    CPUIDPP_IMPL_FLAG(clflushopt,       23, f7_1)
    CPUIDPP_IMPL_FLAG(clwb,             24, f7_1)
    CPUIDPP_IMPL_FLAG(intel_pt,         25, f7_1)
    CPUIDPP_IMPL_FLAG(avx512pf,         26, f7_1)
    CPUIDPP_IMPL_FLAG(avx512er,         27, f7_1)
    CPUIDPP_IMPL_FLAG(avx512cd,         28, f7_1)
    CPUIDPP_IMPL_FLAG(sha,              29, f7_1)
    CPUIDPP_IMPL_FLAG(avx512bw,         30, f7_1)
    CPUIDPP_IMPL_FLAG(avx512vl,         31, f7_1)


    CPUIDPP_IMPL_FLAG(prefetchwt1,      0, f7_2)
    CPUIDPP_IMPL_FLAG(avx512vbmi,       1, f7_2)
    CPUIDPP_IMPL_FLAG(umip,             2, f7_2)
    CPUIDPP_IMPL_FLAG(pku,              3, f7_2)
    CPUIDPP_IMPL_FLAG(ospke,            4, f7_2)

    CPUIDPP_IMPL_FLAG(avx512vpopcntdq,  14, f7_2)

    CPUIDPP_IMPL_FLAG(rdpid,            22, f7_2)

    CPUIDPP_IMPL_FLAG(sgx_lc,           30, f7_2)

    CPUIDPP_IMPL_FLAG(avx512_4vnniw,    2, f7_3)
    CPUIDPP_IMPL_FLAG(avx512_4fmaps,    3, f7_3)

    // AMD specific

    CPUIDPP_IMPL_FLAG(syscall,          11, f80000001_3)

    CPUIDPP_IMPL_FLAG(mp,               19, f80000001_3)
    CPUIDPP_IMPL_FLAG(nx,               20, f80000001_3)

    CPUIDPP_IMPL_FLAG(mmxext,           22, f80000001_3)

    CPUIDPP_IMPL_FLAG(fxsr_opt,         25, f80000001_3)
    CPUIDPP_IMPL_FLAG(pdpe1gb,          26, f80000001_3)
    CPUIDPP_IMPL_FLAG(rdtscp,           27, f80000001_3)

    CPUIDPP_IMPL_FLAG(lm,               29, f80000001_3)
    CPUIDPP_IMPL_FLAG(amd_3dnowext,     30, f80000001_3)
    CPUIDPP_IMPL_FLAG(amd_3dnow,        31, f80000001_3)

    CPUIDPP_IMPL_FLAG(lahf_lm,          0, f80000001_2)
    CPUIDPP_IMPL_FLAG(cmp_legacy,       1, f80000001_2)
    CPUIDPP_IMPL_FLAG(svm,              2, f80000001_2)
    CPUIDPP_IMPL_FLAG(extapic,          3, f80000001_2)
    CPUIDPP_IMPL_FLAG(cr8_legacy,       4, f80000001_2)
    CPUIDPP_IMPL_FLAG(abm,              5, f80000001_2)
    CPUIDPP_IMPL_FLAG(sse4a,            6, f80000001_2)
    CPUIDPP_IMPL_FLAG(misalignsse,      7, f80000001_2)
    CPUIDPP_IMPL_FLAG(amd_3dnowprefetch,8, f80000001_2)
    CPUIDPP_IMPL_FLAG(osvw,             9, f80000001_2)
    CPUIDPP_IMPL_FLAG(ibs,              10, f80000001_2)
    CPUIDPP_IMPL_FLAG(xop,              11, f80000001_2)
    CPUIDPP_IMPL_FLAG(skinit,           12, f80000001_2)
    CPUIDPP_IMPL_FLAG(wdt,              13, f80000001_2)

    CPUIDPP_IMPL_FLAG(lwp,              15, f80000001_2)
    CPUIDPP_IMPL_FLAG(fma4,             16, f80000001_2)
    CPUIDPP_IMPL_FLAG(tce,              17, f80000001_2)

    CPUIDPP_IMPL_FLAG(nodeid_msr,       19, f80000001_2)

    CPUIDPP_IMPL_FLAG(tbm,              21, f80000001_2)
    CPUIDPP_IMPL_FLAG(topoext,          22, f80000001_2)
    CPUIDPP_IMPL_FLAG(perfctr_core,     23, f80000001_2)
    CPUIDPP_IMPL_FLAG(perfctr_nb,       24, f80000001_2)

    CPUIDPP_IMPL_FLAG(dbx,              26, f80000001_2)
    CPUIDPP_IMPL_FLAG(perftsc,          27, f80000001_2)
    CPUIDPP_IMPL_FLAG(pcx_l2i,          28, f80000001_2)

    static const CPUIDImpl& get()
    {
        static const CPUIDImpl instance;
        return instance;
    }

    std::bitset<32> f1_2;
    std::bitset<32> f1_3;
    std::bitset<32> f7_1;
    std::bitset<32> f7_2;
    std::bitset<32> f7_3;
    std::bitset<32> f80000001_2;
    std::bitset<32> f80000001_3;
    std::string vendor;
    std::string model;
};

const std::string& CPUID::vendor()
{
    return CPUIDImpl::get().vendor;
}

const std::string& CPUID::model()
{
    return CPUIDImpl::get().model;
}

#define CPUIDPP_CPUID_IMPL_FLAG(name)       \
    bool CPUID::name()                      \
    {                                       \
        return CPUIDImpl::get().name();     \
    }


CPUIDPP_CPUID_IMPL_FLAG(fpu)
CPUIDPP_CPUID_IMPL_FLAG(vme)
CPUIDPP_CPUID_IMPL_FLAG(de)
CPUIDPP_CPUID_IMPL_FLAG(pse)
CPUIDPP_CPUID_IMPL_FLAG(tsc)
CPUIDPP_CPUID_IMPL_FLAG(msr)
CPUIDPP_CPUID_IMPL_FLAG(pae)
CPUIDPP_CPUID_IMPL_FLAG(mce)
CPUIDPP_CPUID_IMPL_FLAG(cx8)
CPUIDPP_CPUID_IMPL_FLAG(apic)
CPUIDPP_CPUID_IMPL_FLAG(sep)
CPUIDPP_CPUID_IMPL_FLAG(mtrr)
CPUIDPP_CPUID_IMPL_FLAG(pge)
CPUIDPP_CPUID_IMPL_FLAG(mca)
CPUIDPP_CPUID_IMPL_FLAG(cmov)
CPUIDPP_CPUID_IMPL_FLAG(pat)
CPUIDPP_CPUID_IMPL_FLAG(pse36)
CPUIDPP_CPUID_IMPL_FLAG(psn)
CPUIDPP_CPUID_IMPL_FLAG(clfsh)
CPUIDPP_CPUID_IMPL_FLAG(ds)
CPUIDPP_CPUID_IMPL_FLAG(acpi)
CPUIDPP_CPUID_IMPL_FLAG(mmx)
CPUIDPP_CPUID_IMPL_FLAG(fxsr)
CPUIDPP_CPUID_IMPL_FLAG(sse)
CPUIDPP_CPUID_IMPL_FLAG(sse2)
CPUIDPP_CPUID_IMPL_FLAG(ss)
CPUIDPP_CPUID_IMPL_FLAG(htt)
CPUIDPP_CPUID_IMPL_FLAG(tm)
CPUIDPP_CPUID_IMPL_FLAG(ia64)
CPUIDPP_CPUID_IMPL_FLAG(pbe)

CPUIDPP_CPUID_IMPL_FLAG(sse3)
CPUIDPP_CPUID_IMPL_FLAG(pclmulqdq)
CPUIDPP_CPUID_IMPL_FLAG(dtes64)
CPUIDPP_CPUID_IMPL_FLAG(monitor)
CPUIDPP_CPUID_IMPL_FLAG(ds_cpl)
CPUIDPP_CPUID_IMPL_FLAG(vmx)
CPUIDPP_CPUID_IMPL_FLAG(smx)
CPUIDPP_CPUID_IMPL_FLAG(est)
CPUIDPP_CPUID_IMPL_FLAG(tm2)
CPUIDPP_CPUID_IMPL_FLAG(ssse3)
CPUIDPP_CPUID_IMPL_FLAG(cnxt_id)
CPUIDPP_CPUID_IMPL_FLAG(sdbg)
CPUIDPP_CPUID_IMPL_FLAG(fma)
CPUIDPP_CPUID_IMPL_FLAG(cx16)
CPUIDPP_CPUID_IMPL_FLAG(xtpr)
CPUIDPP_CPUID_IMPL_FLAG(pdcm)

CPUIDPP_CPUID_IMPL_FLAG(pcid)
CPUIDPP_CPUID_IMPL_FLAG(dca)
CPUIDPP_CPUID_IMPL_FLAG(sse4_1)
CPUIDPP_CPUID_IMPL_FLAG(sse4_2)
CPUIDPP_CPUID_IMPL_FLAG(x2apic)
CPUIDPP_CPUID_IMPL_FLAG(movbe)
CPUIDPP_CPUID_IMPL_FLAG(popcnt)
CPUIDPP_CPUID_IMPL_FLAG(tsc_deadline)
CPUIDPP_CPUID_IMPL_FLAG(aes)
CPUIDPP_CPUID_IMPL_FLAG(xsave)
CPUIDPP_CPUID_IMPL_FLAG(oxsave)
CPUIDPP_CPUID_IMPL_FLAG(avx)
CPUIDPP_CPUID_IMPL_FLAG(f16c)
CPUIDPP_CPUID_IMPL_FLAG(rdrnd)
CPUIDPP_CPUID_IMPL_FLAG(hypervisor)

CPUIDPP_CPUID_IMPL_FLAG(fsgsbase)

CPUIDPP_CPUID_IMPL_FLAG(sgx)
CPUIDPP_CPUID_IMPL_FLAG(bmi1)
CPUIDPP_CPUID_IMPL_FLAG(hle)
CPUIDPP_CPUID_IMPL_FLAG(avx2)

CPUIDPP_CPUID_IMPL_FLAG(smep)
CPUIDPP_CPUID_IMPL_FLAG(bmi2)
CPUIDPP_CPUID_IMPL_FLAG(erms)
CPUIDPP_CPUID_IMPL_FLAG(invpcid)
CPUIDPP_CPUID_IMPL_FLAG(rtm)
CPUIDPP_CPUID_IMPL_FLAG(pqm)

CPUIDPP_CPUID_IMPL_FLAG(mpx)
CPUIDPP_CPUID_IMPL_FLAG(pqe)
CPUIDPP_CPUID_IMPL_FLAG(avx512f)
CPUIDPP_CPUID_IMPL_FLAG(avx512dq)
CPUIDPP_CPUID_IMPL_FLAG(rdseed)
CPUIDPP_CPUID_IMPL_FLAG(adx)
CPUIDPP_CPUID_IMPL_FLAG(smap)
CPUIDPP_CPUID_IMPL_FLAG(avx512ifma)
CPUIDPP_CPUID_IMPL_FLAG(pcommit)
CPUIDPP_CPUID_IMPL_FLAG(clflushopt)
CPUIDPP_CPUID_IMPL_FLAG(clwb)
CPUIDPP_CPUID_IMPL_FLAG(intel_pt)
CPUIDPP_CPUID_IMPL_FLAG(avx512pf)
CPUIDPP_CPUID_IMPL_FLAG(avx512er)
CPUIDPP_CPUID_IMPL_FLAG(avx512cd)
CPUIDPP_CPUID_IMPL_FLAG(sha)
CPUIDPP_CPUID_IMPL_FLAG(avx512bw)
CPUIDPP_CPUID_IMPL_FLAG(avx512vl)


CPUIDPP_CPUID_IMPL_FLAG(prefetchwt1)
CPUIDPP_CPUID_IMPL_FLAG(avx512vbmi)
CPUIDPP_CPUID_IMPL_FLAG(umip)
CPUIDPP_CPUID_IMPL_FLAG(pku)
CPUIDPP_CPUID_IMPL_FLAG(ospke)

CPUIDPP_CPUID_IMPL_FLAG(avx512vpopcntdq)

CPUIDPP_CPUID_IMPL_FLAG(rdpid)

CPUIDPP_CPUID_IMPL_FLAG(sgx_lc)

CPUIDPP_CPUID_IMPL_FLAG(avx512_4vnniw)
CPUIDPP_CPUID_IMPL_FLAG(avx512_4fmaps)

// AMD specific

CPUIDPP_CPUID_IMPL_FLAG(syscall)

CPUIDPP_CPUID_IMPL_FLAG(mp)
CPUIDPP_CPUID_IMPL_FLAG(nx)

CPUIDPP_CPUID_IMPL_FLAG(mmxext)

CPUIDPP_CPUID_IMPL_FLAG(fxsr_opt)
CPUIDPP_CPUID_IMPL_FLAG(pdpe1gb)
CPUIDPP_CPUID_IMPL_FLAG(rdtscp)

CPUIDPP_CPUID_IMPL_FLAG(lm)
CPUIDPP_CPUID_IMPL_FLAG(amd_3dnowext)
CPUIDPP_CPUID_IMPL_FLAG(amd_3dnow)

CPUIDPP_CPUID_IMPL_FLAG(lahf_lm)
CPUIDPP_CPUID_IMPL_FLAG(cmp_legacy)
CPUIDPP_CPUID_IMPL_FLAG(svm)
CPUIDPP_CPUID_IMPL_FLAG(extapic)
CPUIDPP_CPUID_IMPL_FLAG(cr8_legacy)
CPUIDPP_CPUID_IMPL_FLAG(abm)
CPUIDPP_CPUID_IMPL_FLAG(sse4a)
CPUIDPP_CPUID_IMPL_FLAG(misalignsse)
CPUIDPP_CPUID_IMPL_FLAG(amd_3dnowprefetch)
CPUIDPP_CPUID_IMPL_FLAG(osvw)
CPUIDPP_CPUID_IMPL_FLAG(ibs)
CPUIDPP_CPUID_IMPL_FLAG(xop)
CPUIDPP_CPUID_IMPL_FLAG(skinit)
CPUIDPP_CPUID_IMPL_FLAG(wdt)

CPUIDPP_CPUID_IMPL_FLAG(lwp)
CPUIDPP_CPUID_IMPL_FLAG(fma4)
CPUIDPP_CPUID_IMPL_FLAG(tce)

CPUIDPP_CPUID_IMPL_FLAG(nodeid_msr)

CPUIDPP_CPUID_IMPL_FLAG(tbm)
CPUIDPP_CPUID_IMPL_FLAG(topoext)
CPUIDPP_CPUID_IMPL_FLAG(perfctr_core)
CPUIDPP_CPUID_IMPL_FLAG(perfctr_nb)

CPUIDPP_CPUID_IMPL_FLAG(dbx)
CPUIDPP_CPUID_IMPL_FLAG(perftsc)
CPUIDPP_CPUID_IMPL_FLAG(pcx_l2i)

} // namespace cpuidpp
