
# Setup

Run this to install prereqs

    # apt install build-essential grub-common grub-pc-bin qemu-system-x86 mtools xorriso emacs

All that junk is mostly for being able to create the ISO correctly. If you don't have the proper packages, the ISO creation will succeed but QEMU will fail with a helpful error like `Boot failed: Could not read from CDROM (code 0009)`.

# Building

Build from the `./src` directory. Run `make` to build the ISO, and run `make run` to launch QEMU.