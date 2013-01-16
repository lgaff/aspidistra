## Aspidistra - a feeble attempt at operating a system.

### Introduction
Aspidistra is an attempt to explore the fundamentals of OS and hardware design.
As such, it's not an attempt at producing a practical system - expect a lot of bugs.

That said, I'll try to keep the latter issue as minimal as possible, but given the little time I
have, and the fact that I'm trying to continue in as forward a direction as possible with my explorations
they may persist for a little while.

Aspidistra itself is targeted at the x86 processor architecture, utilising protected, paged memory, and 32-bit
address space. I have no plans (yet) for supporting anything beyond the basic 32-bit instruction and register set, however
Liz is happy to accomodate you should you decide to choose the path of pain. 

### Current features.

- In short, nothing. 
- In longer, next to nothing. Aspidistra currently provides a minimal environment to enter Liz (discussed below): 
  - Protected mode, with a flat 4GB address space.
  - Virtual memory is enabled, paging is enabled, but not configured (Thus, you actually have only 4k of program space).
  - Everything is still in kernel mode.
  - The kernel is in the higher-half.
  - Theoretically, the program dataspace should be in the lower half. practically, kmalloc allocates the program space in kernel
    memory, immediately after the kernel image. (Again, this means your program space is truncated by the kernel image size :)).
  - The PIT is not running, although the means to do so is coded (check dev/timer.c). 
  - No multitasking support is running. 
  - Interrupts are enabled, most are registered to dummy ISR's to avoid triple faulting. These will be filled in on an uncertain schedule.

### Liz, the monitor.

    Liz marks the first point at which Aspidistra becomes anything resembling useful. Once environment loading is complete, the 
    kernel calls liz_main(). Liz is a very simple monitor program akin to those one would find on early DEC minicomputers, or at least, it aims to be. 
    As it currently stands however, Liz is very short on features, and even shorter on tolerance. What Liz does enable (in the broadest possible sense), is for the user to enter arbitrary machine code into memory, and execute it. It is unashamedly primitive, however it does support some very basic mode toggles and commands.

#### Liz commands.
     *g* :: (g)o. Executes the program that was loaded. This command inserts an explicit 'ret' opcode at the end of the loaded program in order to avoid hangs due to user error. 
     *s* :: (s)et start. This sets the current program address as the entry point for the loaded code.
     *e* :: (e)rase. Performs a soft erase on the loaded program. In effect, simply resets the PC to the initial heap address 
            passed to liz_main().
     *d* :: (d)ata mode. Allows loading constant data to memory. This feature is still very broken, so I've disabled it for now.
            You can of course still load constants using raw hex.

#### Liz interface.
     Liz' interface is as primitive as they come. hexadecimal values are entered at the prompt (current instruction index followed by a '>'), punctuated with a newline.
     Primitive scanning and parsing is undertaken before blindly committing to memory, anything Liz can't interpret as hex or a command
     is rejected with an "OP?" response.
     Above the prompt, program status is displayed as the current location in VMEM where the next instruction will be loaded, and the
     byte offset from the beginning of liz' program space.

#### Future direction of Liz.
     Okay, okay, writing raw opcodes is insanely painful, I know. In future I hope to turn Liz into something like a command line assembler that accepts mnemonics rather than raw hex, as well as some of these niceties that hopefully turn it into a useful debugging tool:
     - Longer, less ambiguous command syntax. single characters are where it's at right now because I wanted to avoid writing a lexer/parser to start off. Now that it works, the advantages outweight the detractions.
     - More useful commands for debug:
       - Examine arbitrary memory locations
       - Set/reset breakpoints.
       - register display.
       - The ability to edit loaded programs.
       - More features that rely on Aspidistra becoming more fully featured first.

### Future direction of Aspidistra.
    - The obvious next target is to implement paging and a system call interface. Whether this will take the POSIX road or not I've yet to decide.
    - Re-enabling the PIT and getting stable multitasking is most definitely necessary in the short term so we can look at moving out of kernel space.
    - Some userspace utilities are an obvious requirement if we don't want to live in Liz forever. At this stage, the first target is
    most likely going to take the form of a shell that understands Forth, or perhaps Lisp. 
    - A big big problem right now is console IO. When I started this I was following a tutorial (Highly recommended [www.jamesmolloy.co.uk/tutorial_html/index.html][]), which I took some liberties from as it progressed, resulting in the disaster that is my implementation of standard IO. console IO is being handled several times by several entities, meaning it's tempremental and intolerant to user error. This will probably get the majority of my immediate attention. 

    - Micro vs. Mono kernel: I haven't yet thought this through, though it will need to be decided one way or another very soon.