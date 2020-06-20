
#ifndef FLAGS_HPP
#define FLAGS_HPP

extern "C" bool is_cpuid_supported();

struct eabcdx_registers {
    unsigned long eax, ebx, ecx, edx;
};

enum cpuid_values : unsigned long {
    // A cpuid query number is called a "leaf". This leaf will determine the
    // highest EAX value CPUID recongizes.
    cpuid_query_max_leaf = 0x80000000ul,

    // Query whether long mode is available.
    cpuid_query_extended_processor_info_and_feature_bits = 0x80000001ul,
};

// These bit flags are set in the EDX and ECX registers after CPUID runs
enum cpuid_proc_info_flags {
    cpuid_proc_info_long_mode = 1ul << 29
};

/*
  Calls the cpuid instruction with the given e[abcd]x register values, and then
  updates the structure argument in-place with the registers' values post-cpuid.
 */
extern "C" void cpuid(eabcdx_registers* registers);

#endif
