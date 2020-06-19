#!/bin/bash
function usage()
{
   echo "Usage: $0 input_file"
   exit 1
}

if [ ! "$1" ] || [ ! -r "$1" ]; then
   usage
fi

flags="--is-i386-xen-pae-domu --is-x86_64-xen-domu --is-x86-xen-dom0 --is-x86-multiboot --is-x86-multiboot2 --is-arm-linux --is-arm64-linux --is-ia64-linux --is-mips-linux --is-mipsel-linux --is-sparc64-linux --is-powerpc-linux --is-x86-linux --is-x86-linux32 --is-x86-kfreebsd --is-i386-kfreebsd --is-x86_64-kfreebsd --is-x86-knetbsd --is-i386-knetbsd --is-x86_64-knetbsd --is-i386-efi --is-x86_64-efi --is-ia64-efi --is-arm64-efi --is-arm-efi --is-hibernated-hiberfil --is-x86_64-xnu --is-i386-xnu --is-xnu-hibr --is-x86-bios-bootsector"

for flag in $flags; do
   if grub-file $flag $1; then
      echo "$1 passed $flag"
   fi
done
