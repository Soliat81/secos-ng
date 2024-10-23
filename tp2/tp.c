/* GPLv2 (c) Airbus */
#include <debug.h>
#include <intr.h>
void bp_handler() {
   // TODO
 	  uint32_t val;
   asm volatile ("mov 4(%%ebp), %0":"=r"(val));
	debug("Val = %x\n",val);
  	debug("bp_handler activated !!!\n");
//	asm volatile ("popa"); //Sauvegarde eax,ebx... dans la pile
//	asm volatile ("leave; iret");
}

void bp_trigger() {
	asm volatile ("int3");
	debug("End bp_trigger\n");
}

void tp() {
	// TODO print idtr
	idt_reg_t idt;
	get_idtr(idt);
	debug("IDTR addr : 0x%x ",(unsigned int) idt.addr);
	debug("limit : %d\n", idt.limit);


	int_desc_t *my_idt = &idt.desc[3];


	my_idt->offset_1 = (uint16_t)((uint32_t)bp_handler);
	my_idt->offset_2 = (uint16_t)(((uint32_t)bp_handler)>>16);

   bp_trigger();
}
