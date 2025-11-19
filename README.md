# 🌐 FluxOS  
**FluxOS is a from-scratch 32-bit x86 hobby operating system**, built as a learning project inspired by OSDev.  
It features a custom bootloader, protected-mode kernel, fully custom GUI with window management, preemptive multitasking, FAT12 filesystem support, and an ELF loader for user-mode apps — all written in C and Assembly.

FluxOS boots on real hardware (BIOS) and in QEMU, fitting entirely in a 1.44MB floppy image.

---

## 🚀 Features

### 🧵 **Bootloader**
- Custom 16-bit real-mode bootloader (no GRUB)
- Loads kernel from floppy sectors
- Sets up GDT and transitions to 32-bit protected mode

### 🖥️ **Kernel**
- Global Descriptor Table (GDT)
- Interrupt Descriptor Table (IDT) with 256 entries
- Assembly ISR stubs for exceptions & IRQs
- PIC remapping (0x20 / 0x28)
- Programmable Interval Timer (PIT) @ 100Hz

### ⌨️🖱️ **Input Drivers**
- PS/2 keyboard driver (IRQ1)
- PS/2 mouse driver (IRQ12) with packet parsing  
  → supports cursor movement, clicks, drag, double-click

### 🖼️ **Graphics & Window Manager**
- VGA Mode 13h (320×200×256 colors)
- Mouse cursor rendering
- Draggable windows with:
  - titlebars  
  - close buttons  
  - focus management  
- Desktop icons & double-click app launching
- Simple taskbar

### 🔁 **Multitasking**
- Preemptive round-robin scheduler
- Driven by PIT interrupts (IRQ0)
- Kernel task switching

### 🧠 **Memory Management**
- Basic heap (malloc/free)
- 4MB initial heap
- Physical memory identity-mapped

### 💾 **Filesystem**
- FAT12 reader for:
  - icons
  - wallpapers
  - ELF binaries

### 🧩 **User Mode**
- Basic ELF loader
- Loads and executes simple user-mode applications  
  (e.g., `hello.elf`)

### 🖥️ **Emulator & Hardware Support**
- Fully boots in **QEMU**
- Boots on real x86 hardware via floppy/USB  
  (BIOS mode only)

---

## 📁 Project Structure

FluxOS/
├── boot/ # Real-mode bootloader (boot.asm)
├── drivers/ # Keyboard & mouse drivers
│ ├── keyboard.c
│ └── mouse.c
├── gui/ # VGA graphics & window manager
│ ├── vga.c
│ ├── font.c
│ └── wm.c
├── include/ # Header files
├── kernel/ # Core kernel code
│ ├── main.c
│ ├── idt.c
│ ├── isr.s
│ ├── pic.c
│ ├── pit.c
│ ├── memory.c
│ ├── scheduler.c
│ └── elf.c
├── apps/ # User-mode ELF applications
├── fs/ # FAT12 demo assets (icons, wallpaper)
├── LICENSE
├── CONTRIBUTING.md
├── .gitignore
├── linker.ld
└── Makefile

markdown
Copy code

---

## 🛠️ Building FluxOS

### **Prerequisites**
- `i686-elf-gcc` cross-compiler  
  → install via OSDev Wiki guide  
- `NASM`
- `QEMU`
- `Make`

### **Clone and build**
```bash
git clone https://github.com/Zypher0903/FluxOS.git
cd FluxOS
make
Run in QEMU
bash
Copy code
make run
This generates:

fluxos.img → bootable 1.44MB floppy image

kernel binary

FluxOS boots directly into the GUI desktop environment.

💿 Booting on Real Hardware
Write fluxos.img to a floppy or USB floppy emulator:

bash
Copy code
dd if=fluxos.img of=/dev/fd0
Boot from BIOS (disable Secure Boot)

Enjoy FluxOS running on real metal!

🔍 Technical Highlights
🧩 Interrupt System
Complete IDT with 256 entries

Separate exception/IRQ stubs

Hardware IRQ handling (keyboard, mouse, timer)

Uses iret-based return

🪟 Window Manager
Mouse-driven

Multi-window support

Titlebar dragging

Close button actions

Double-click open

Icon-based desktop

📁 FAT12 Loader
Reads sectors from floppy

Loads BMP icons/wallpapers

Loads ELF user apps from disk

📦 ELF Loader
Parses headers

Maps program segments

Transfers control to user mode

🧭 Roadmap
 Virtual File System (VFS)

 AHCI/SATA disk driver

 USB driver (keyboard/mouse)

 Simple command-line shell

 Networking (Ethernet)

 VESA 640×480 / 800×600 graphics

 UEFI boot support

 More user-mode apps

 Paging + virtual memory

🤝 Contributing
See CONTRIBUTING.md for details.
All contributions are welcome!

📄 License
FluxOS is released under the MIT License.
See the LICENSE file for full text.

⭐ Acknowledgements
FluxOS was built using knowledge and inspiration from:

OSDev Wiki & OSDev Forums

The Little Book About OS Development

cfenollosa/os-tutorial

KolibriOS & MenuetOS communities

Public domain 8×8 bitmap fonts

🧑‍💻 Author
David / Zypher0903
Builder of FluxOS — a from-scratch OS dev adventure.
