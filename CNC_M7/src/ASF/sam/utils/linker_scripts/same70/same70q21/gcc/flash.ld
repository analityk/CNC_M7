/**

* \file

*

* Copyright (c) 2015 Atmel Corporation. All rights reserved.

*

* \asf_license_start

*

* \page License

*

* Redistribution and use in source and binary forms, with or without

* modification, are permitted provided that the following conditions are met:

*

* 1. Redistributions of source code must retain the above copyright notice,

* this list of conditions and the following disclaimer.

*
*

* 2. Redistributions in binary form must reproduce the above copyright notice,

* this list of conditions and the following disclaimer in the documentation

* and/or other materials provided with the distribution.

*

* 3. The name of Atmel may not be used to endorse or promote products derived

* from this software without specific prior written permission.

*

* 4. This software may only be redistributed and used in connection with an

* Atmel microcontroller product.

*

* THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED

* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF

* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE

* EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR

* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL

* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS

* OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)

* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,

* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN

* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE

* POSSIBILITY OF SUCH DAMAGE.

*

* \asf_license_stop

*

*/

/*------------------------------------------------------------------------------

* Linker script for running in internal FLASH on the ATSAME70Q21

*----------------------------------------------------------------------------*/

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")

OUTPUT_ARCH(arm)

SEARCH_DIR(.)

/* Memory Spaces Definitions */

MEMORY

{

itcm_vectors (rx) : ORIGIN = 0x00000000, LENGTH = 0x00000400 /* Vector table at beginning of ITCM */

itcm (rx) : ORIGIN = 0x00000400, LENGTH = 0x0001FC00 /* Fast code in ITCM */

rom (rx) : ORIGIN = 0x00400000, LENGTH = 0x00200000 /* Remaining Code in Flash Memory */

dtcm (rw) : ORIGIN = 0x20000000, LENGTH = 0x00020000 /* Fast data/bss in DTCM */

ram (rwx) : ORIGIN = 0x20400000, LENGTH = 0x00020000 /* Remaining data/bss in System RAM */

}

/* The stack size used by the application. NOTE: you need to adjust according to your application. */

STACK_SIZE = DEFINED(STACK_SIZE) ? STACK_SIZE : 0x2000;

DTCM_STACK_SIZE = DEFINED(DTCM_STACK_SIZE) ? DTCM_STACK_SIZE : 0x200;

__ram_end__ = ORIGIN(ram) + LENGTH(ram) - 4;

/* The heapsize used by the application. NOTE: you need to adjust according to your application. */

HEAP_SIZE = DEFINED(HEAP_SIZE) ? HEAP_SIZE : 0x1000;

/* Section Definitions */

SECTIONS

{

.fast_vectors (NOLOAD) :

{

. = ALIGN(4);

_srelocate_vectors = .;

} > itcm_vectors

 

.fast_code : AT (_etext)

{

. = ALIGN(4);

_s_fast_code = .;

_s_fast_code_from = LOADADDR(.fast_code);

*(.itcm_functions);

_e_fast_code = .;

_e_fast_code_from = LOADADDR(.fast_code) + SIZEOF(.fast_code);

} > itcm

 

.text :

{

. = ALIGN(4);

_sfixed = .;

KEEP(*(.vectors .vectors.*))

*(.text .text.* .gnu.linkonce.t.*)

*(.glue_7t) *(.glue_7)

*(.rodata .rodata* .gnu.linkonce.r.*)

*(.ARM.extab* .gnu.linkonce.armextab.*)

/* Support C constructors, and C destructors in both user code

and the C library. This also provides support for C++ code. */

. = ALIGN(4);

KEEP(*(.init))

. = ALIGN(4);

__preinit_array_start = .;

KEEP (*(.preinit_array))

__preinit_array_end = .;

. = ALIGN(4);

__init_array_start = .;

KEEP (*(SORT(.init_array.*)))

KEEP (*(.init_array))

__init_array_end = .;

. = ALIGN(0x4);

KEEP (*crtbegin.o(.ctors))

KEEP (*(EXCLUDE_FILE (*crtend.o) .ctors))

KEEP (*(SORT(.ctors.*)))

KEEP (*crtend.o(.ctors))

. = ALIGN(4);

KEEP(*(.fini))

. = ALIGN(4);

__fini_array_start = .;

KEEP (*(.fini_array))

KEEP (*(SORT(.fini_array.*)))

__fini_array_end = .;

KEEP (*crtbegin.o(.dtors))

KEEP (*(EXCLUDE_FILE (*crtend.o) .dtors))

KEEP (*(SORT(.dtors.*)))

KEEP (*crtend.o(.dtors))

. = ALIGN(4);

_efixed = .; /* End of text section */

} > rom

 

/* .ARM.exidx is sorted, so has to go in its own output section. */

PROVIDE_HIDDEN (__exidx_start = .);

.ARM.exidx :

{

*(.ARM.exidx* .gnu.linkonce.armexidx.*)

} > rom

PROVIDE_HIDDEN (__exidx_end = .);

. = ALIGN(4);

_etext = .;

 

/* Slow data segment listed first */

/* Only a few modules are listed here */

/* Uses system memory */

.data : AT (_etext + SIZEOF(.fast_code))

{

. = ALIGN(4);

_s_data = .;

_s_data_from = LOADADDR(.data);

. = ALIGN(4);

_e_data = .;

_e_data_from = LOADADDR(.data) + SIZEOF(.data);

} > ram

 

/* Slow BSS segment listed first */

/* Only a few modules are listed here */

/* Uses system memory */

.bss (NOLOAD) :

{

. = ALIGN(4);

_s_bss = . ;

_s_zero = .;

. = ALIGN(4);

_e_bss = . ;

_e_zero = .;

} > dtcm

 

/* Fast data segment takes all remaining */

/* modules, uses the TCM */

.fast_data : AT (_etext + SIZEOF(.fast_code) + SIZEOF(.data))

{

. = ALIGN(4);

_s_fast_data = .;

_s_fast_data_from = LOADADDR(.fast_data);

*(.data .data.*);

. = ALIGN(4);

_e_fast_data = .;

_e_fast_data_from = LOADADDR(.fast_data) + SIZEOF(.fast_data);

} > dtcm

 

/* Fast BSS segment takes all remaining */

/* modules, uses the TCM */

.fast_bss (NOLOAD) :

{

. = ALIGN(4);

_s_fast_bss = . ;

_s_fast_zero = .;

*(.bss .bss.*)

*(COMMON)

. = ALIGN(4);

_e_fast_bss = . ;

_e_fast_zero = .;

} > dtcm

 

/* heap section - needs to be listed before stack since heap grows up in address space*/

.heap (NOLOAD):

{

. = ALIGN(8);

_s_heap = .;

. = . + HEAP_SIZE;

. = ALIGN(8);

_e_heap = .;

} > dtcm

/* startup stack section. Stack needed just for reset_handler, just to get us through operation where we check TCM bits in GPNVM */

.stack (NOLOAD):

{

. = ALIGN(8);

_s_stack = .;

. = . + STACK_SIZE;

. = ALIGN(8);

_e_stack = .;

} > ram

 

.runtime_stack (NOLOAD):

{

. = ALIGN(8);

_s_runtime_stack = .;

. = . + DTCM_STACK_SIZE;

. = ALIGN(8);

_e_runtime_stack = .;

} > dtcm

. = ALIGN(4);

_end = . ;

_ram_end_ = ORIGIN(ram) + LENGTH(ram) -1 ;
}