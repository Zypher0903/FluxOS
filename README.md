FluxOS is a from-scratch hobby operating system for x86 (32-bit) architecture, designed as a learning project inspired by the OSDev community. It features a custom bootloader, protected-mode kernel, graphical user interface (GUI) with window management, preemptive multitasking, a basic FAT12 filesystem, and an ELF loader for user-mode applications. The goal is to build a minimal, functional OS that boots in QEMU and runs on real hardware (BIOS-based).
This project started as a simple bootloader and evolved into a full prototype with IRQ handling, mouse/keyboard input, and draggable windows – all in under 2,000 lines of code!
Features

Bootloader: Custom 16-bit real-mode to 32-bit protected-mode switch (no GRUB dependency).
Kernel: Global Descriptor Table (GDT), Interrupt Descriptor Table (IDT) with 256 entries and ISR stubs, Programmable Interrupt Controller (PIC) remapping, and Programmable Interval Timer (PIT) for 100Hz ticks.
Input Drivers: PS/2 keyboard (IRQ1) and mouse (IRQ12) with scan code mapping and packet parsing.
GUI (Window Manager): VGA mode 13h (320x200x256 colors), draggable/resizable windows, click detection, close buttons, desktop icons, and a taskbar. Supports double-click to launch apps.
Multitasking: Simple preemptive round-robin scheduler using PIT interrupts.
Memory Management: Basic heap allocator (malloc/free) with 4MB initial heap.
Filesystem: FAT12 support for loading icons, wallpapers, and binaries from a floppy image.
User Mode: ELF loader to execute simple user-space programs (e.g., "Hello World" app).
Emulator Support: Fully boots in QEMU; tested on real x86 hardware (floppy boot).

Project Structure
textFluxOS/
├── boot/              # Bootloader (boot.asm)
├── drivers/           # Keyboard and mouse drivers
│   ├── keyboard.c
│   └── mouse.c
├── gui/               # VGA graphics and window manager
│   ├── vga.c
│   ├── font.c
│   └── wm.c
├── include/           # Headers (common.h, idt.h, etc.)
├── kernel/            # Core kernel files
│   ├── main.c
│   ├── idt.c
│   ├── isr.s          # ISR stubs in assembly
│   ├── pic.c
│   ├── pit.c
│   ├── memory.c
│   ├── scheduler.c
│   └── elf.c
├── apps/              # Sample ELF user apps (e.g., hello.elf)
├── fs/                # FAT12 demo files (e.g., WALLPAPER.BMP)
├── linker.ld          # Linker script
└── Makefile           # Build and run scripts
Building and Running
Prerequisites

Cross-Compiler: i686-elf-gcc (build from OSDev Wiki).
Tools: NASM, QEMU, Make (on Linux/Mac: sudo apt install nasm qemu-system-x86 make).
OS: Tested on Ubuntu 22.04+.

Build Steps

Clone the repo:textgit clone https://github.com/Zypher0903/FluxOS.git
cd FluxOS
Build the kernel and floppy image:textmake
Run in QEMU:textmake run

This generates fluxos.img (1.44MB floppy) and boots into the GUI. You'll see a blue desktop with draggable windows, a mouse cursor, and taskbar. Press keys or move the mouse to interact!
Hardware Boot

Write fluxos.img to a USB floppy (e.g., via dd if=fluxos.img of=/dev/fd0).
Boot from it in BIOS mode (disable Secure Boot).


Boot: boot.asm loads the kernel from disk sectors, sets up GDT, and jumps to protected mode.
Kernel Init: main.c initializes IDT (256 entries with ISR stubs), PIC (IRQ remap), PIT (timer for scheduling), memory heap, drivers, and WM.
Interrupts: PIT (IRQ0) drives multitasking; keyboard (IRQ1) and mouse (IRQ12) handle input via custom handlers.
GUI Events: Window manager processes mouse clicks/drags and key events for window ops and icon launches.
Filesystem & Apps: FAT12 reads files from the boot floppy; ELF loader maps and executes user binaries in ring 3.

For deep dives:

IDT/ISR: Full 256-entry table with assembly stubs for exceptions and IRQs.
WM: Event loop detects left-click (drag titlebar), right-click (close), double-click (launch ELF).

Roadmap

 Custom bootloader & protected mode.
 IDT with ISR/IRQ handlers (keyboard/mouse).
 Window manager with drag/close/clicks.
 PIT-based preemptive multitasking.
 FAT12 filesystem for assets/apps.
 ELF loader + user mode.
 VFS (Virtual File System) layer.
 USB support and AHCI disk driver.
 Simple shell/terminal app.
 Networking (basic Ethernet).
 UEFI boot support.

Contributions welcome! See CONTRIBUTING.md for guidelines.
Resources & Credits

Heavily inspired by OSDev Wiki tutorials (e.g., Bare Bones).
Similar projects: cfenollosa/os-tutorial, littleosbook.
Fonts/Icons: Custom 8x8 bitmap font; BMP assets from public domain.
Thanks to the OSDev Discord for troubleshooting tips!

License
This project is licensed under the MIT License – see LICENSE for details.
