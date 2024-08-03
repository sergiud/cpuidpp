/**
 * @file
 * @brief Prints CPU features.
 *
 * @copyright © 2024 Sergiu Deitsch. Distributed under the Boost Software
 * License, Version 1.0. (See accompanying file LICENSE or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include <iomanip>
#include <iostream>

#include <cpuidpp/cpuidpp.hpp>

#define CPUIDPP_FEATURE(name) #name
#define CPUIDPP_SUPPORTED_FEATURE(out, name)                                        \
    out << std::setw(20) << std::left << CPUIDPP_FEATURE(name) << ' '               \
        << std::setw(4)  << std::right << (cpuidpp::name() ? "yes" : "no")          \
        << '\n'                                                                     \
        ;


int main()
{
    std::clog << "vendor: " << cpuidpp::vendor() << std::endl;
    std::clog << "model: " << cpuidpp::model() << std::endl;

    CPUIDPP_SUPPORTED_FEATURE(std::clog, abm);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, acpi);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, adx);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, aes);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, amd_3dnow);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, amd_3dnowext);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, amd_3dnowprefetch);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, apic);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, avx);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, avx2);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, avx512_4fmaps);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, avx512_4vnniw);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, avx512bw);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, avx512cd);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, avx512dq);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, avx512er);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, avx512f);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, avx512ifma);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, avx512pf);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, avx512vbmi);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, avx512vl);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, avx512vpopcntdq);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, bmi1);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, bmi2);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, clflushopt);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, clfsh);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, clwb);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, cmov);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, cmp_legacy);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, cnxt_id);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, cr8_legacy);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, cx16);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, cx8);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, dbx);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, dca);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, de);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, ds);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, ds_cpl);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, dtes64);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, erms);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, eist);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, extapic);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, f16c);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, fma);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, fma4);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, fpu);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, fsgsbase);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, fxsr);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, fxsr_opt);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, hle);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, htt);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, hypervisor);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, ia64);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, ibs);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, intel_pt);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, invpcid);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, lahf_lm);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, lm);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, lwp);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, mca);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, mce);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, misalignsse);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, mmx);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, mmxext);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, monitor);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, movbe);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, mp);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, mpx);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, msr);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, mtrr);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, nodeid_msr);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, nx);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, ospke);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, osvw);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, oxsave);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, pae);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, pat);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, pbe);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, pcid);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, pclmulqdq);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, pcommit);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, pcx_l2i);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, pdcm);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, pdpe1gb);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, perfctr_core);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, perfctr_nb);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, perftsc);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, pge);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, pku);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, popcnt);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, pqe);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, pqm);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, prefetchwt1);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, pse);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, pse36);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, psn);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, rdpid);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, rdrnd);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, rdseed);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, rdtscp);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, rtm);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, sdbg);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, sep);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, sgx);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, sgx_lc);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, sha);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, skinit);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, smap);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, smep);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, smx);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, ss);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, sse);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, sse2);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, sse3);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, sse4_1);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, sse4_2);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, sse4a);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, ssse3);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, svm);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, syscall);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, tbm);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, tce);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, tm);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, tm2);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, topoext);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, tsc);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, tsc_deadline);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, umip);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, vme);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, vmx);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, wdt);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, x2apic);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, xop);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, xsave);
    CPUIDPP_SUPPORTED_FEATURE(std::clog, xtpr);
}
