A simple 32-bit monotask operating system for i386 architecture written using C and nasm.
------------------------------
Whats going on under the hood?
1. i386 processor starts in **real** 16-bit mode for backwards compatibility. We need to build or way up to 32-bit or **protected** mode.
2. BIOS recongnizes boot file by magic number **0xAA55** at the end of a first sector of a disk and successfully loads it into memory at address **0x7c00**.
3. Using BIOS **interrupt 0x10** we can print characters to show useful information like if the transition to 32-bit mode is successful.
4. Moving all needed options to registers and calling BIOS **interrupt 0x13** we have successfully loaded our main C kernel into memory.
5. We have defined and loaded GDT with 3 basic segments. Flat memory model is used here; afterwards I disabled all BIOS interrupts and successfully entered 32-bit protected mode, and right afterwards we jump into kernel entry.
6. VGA driver was implemented to print characters on a screen;
7. IDT, ISRs and IRQs were successfully defined and loaded.
8. Simple memory allocator and Paging were implemented.
9. Using Programmable interval timer regular interrupts are now called.
10. Now, by reading port **0x60**, we can see keyboard scancodes which were left there by PIC; A keyboard driver was implemented!
11. Finally, a very privitive shell was now implemented.



How to build and run on Debian/Ubuntu system:
---------------------
1. You need toolchain for i386 arch and Qemu. You can install following packages:
```
sudo apt install qemu-system-i386 i686-linux-gnu-gcc gdb-multiarch
```
2. Clone the repository:
```
git clone https://github.com/oleksandryusiuk/Xinu.git
cd Xinu
```
3. Build using Make:
```
make run
```
or debug/research it using gdb-multiarch by running:
```
make debug
```
to do in future:
Scheduling,
Filesystem

--------------------

references:
https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf
