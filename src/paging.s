
   .intel_syntax noprefix

   .text

   .global set_paging

set_paging:
   push edi
   push ecx
   push ebx
   
   ## Clear tables
   mov edi, 0x1000
   mov cr3, edi
   xor eax, eax
   mov ecx, 0x100
   rep stosd
   mov edi, cr3
   
   ## Set up table structures
   mov [edi], 0x00002003
   add edi, 0x1000
   mov [edi], 0x00003003
   add edi, 0x1000
   mov [edi], 0x00004003
   add edi, 0x1000
   mov ebx, 0x00000003
   mov ecx, 512

   .SetEntry:
   mov DWORD [edi], ebx
   add ebx, 0x1000
   add edi, 8
   loop .SetEntry

   ## Enable PAE
   mov eax, cr4
   or eax, 1 << 5
   mov cr4, eax
   
   pop edi
   pop ecx
   pop ebx
   ret

   .global enable_paging

enable_paging:
   mov eax, cr0
   or eax, 1 << 31
   mov cr0, eax
   ret
