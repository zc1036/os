
    .intel_syntax noprefix

    .text

    .global is_cpuid_supported

    ## Adapted from https://wiki.osdev.org/CPUID
is_cpuid_supported:
    pushfd                               #Save EFLAGS
    pushfd                               #Store EFLAGS
    xor DWORD PTR [esp], 0x00200000      #Invert the ID bit in stored EFLAGS
    popfd                                #Load stored EFLAGS (with ID bit inverted)
    pushfd                               #Store EFLAGS again (ID bit may or may not be inverted)
    pop eax                              #eax = modified EFLAGS (ID bit may or may not be inverted)
    xor eax,[esp]                        #eax = whichever bits were changed
    popfd                                #Restore original EFLAGS
    and eax,0x00200000                   #eax = zero if ID bit can't be changed, else non-zero
    jz is_cpuid_supported_done
    mov eax, 1
is_cpuid_supported_done:
    ret


    .global cpuid

cpuid:
    push ebx                # Preserve ebx
    push esi                # Preserve esi

    mov esi, [esp+12]      # Put first argument (exx_registers*) in esi
    mov eax, [esi]          # Put eax value from struct in eax register
    mov ebx, [esi+4]        # same for ebx
    mov ecx, [esi+8]        # ecx
    mov edx, [esi+12]       # edx
    cpuid                   # call cpuid instruction using parameters
    mov [esi], eax          # Load up resulting e[abcd]x registers into structure
    mov [esi+4], ebx
    mov [esi+8], ecx
    mov [esi+12], edx

    pop esi                 # Restore registers
    pop ebx
    ret
