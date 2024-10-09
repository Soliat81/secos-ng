/* GPLv2 (c) Airbus */
#include <debug.h>
#include <segmem.h>

void userland() {
   asm volatile ("mov %eax, %cr0");
}

void print_gdt_content(gdt_reg_t gdtr_ptr) {
    seg_desc_t* gdt_ptr;
    gdt_ptr = (seg_desc_t*)(gdtr_ptr.addr);
    int i=0;
    while ((uint32_t)gdt_ptr < ((gdtr_ptr.addr) + gdtr_ptr.limit)) {
        uint32_t start = gdt_ptr->base_3<<24 | gdt_ptr->base_2<<16 | gdt_ptr->base_1;
        uint32_t end;
        if (gdt_ptr->g) {
            end = start + ( (gdt_ptr->limit_2<<16 | gdt_ptr->limit_1) <<12) + 4095;
        } else {
            end = start + (gdt_ptr->limit_2<<16 | gdt_ptr->limit_1);
        }
        debug("%d ", i);
        debug("[0x%x ", start);
        debug("- 0x%x] ", end);
        debug("seg_t: 0x%x ", gdt_ptr->type);
        debug("desc_t: %d ", gdt_ptr->s);
        debug("priv: %d ", gdt_ptr->dpl);
        debug("present: %d ", gdt_ptr->p);
        debug("avl: %d ", gdt_ptr->avl);
        debug("longmode: %d ", gdt_ptr->l);
        debug("default: %d ", gdt_ptr->d);
        debug("gran: %d ", gdt_ptr->g);
        debug("\n");
        gdt_ptr++;
        i++;
    }
}


void tp() {
	// TODO
	
	gdt_reg_t gdtr;

	get_gdtr(gdtr);

	debug("GDT addr: 0x%x ", (unsigned int) gdtr.addr);
	debug("limit: %d\n" , gdtr.limit);

	print_gdt_content(gdtr);

	debug("SS: %d\n", get_ss());
	debug("DS: %d\n", get_ds());
	debug("ES: %d\n", get_es());
	debug("FS: %d\n", get_fs());
	debug("GS: %d\n", get_gs());
	debug("CS: %d\n", get_seg_sel(cs));

	seg_desc_t my_gdt[6];

	my_gdt[0].raw = NULL;

	my_gdt[1].limit_1=0xffff;
	my_gdt[1].base_1=0x0000;
	my_gdt[1].base_2=0x00;
	my_gdt[1].type=0x5;
}
