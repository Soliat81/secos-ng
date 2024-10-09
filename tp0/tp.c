/* GPLv2 (c) Airbus */
#include <debug.h>
#include <info.h>

extern info_t   *info;
extern uint32_t __kernel_start__;
extern uint32_t __kernel_end__;

char * inttypetochar(int e) {
	switch(e) {
		case 1:
			return "MULTIBOOT_MEMORY_AVAILABLE";
			break;
		case 2: 
			return "MULTIBOOT_MEMORY_RESERVED";
			break;
		case 3:
			return "MULTIBOOT_MEMORY_ACPI_RECLAIMABLE";
			break;
		case 4:
			return "MULTIBOOT_MEMORY_NVS";
			break;
		default:
			return "Unknown type";
	}

}

void tp() {
   debug("kernel mem [0x%p - 0x%p]\n", &__kernel_start__, &__kernel_end__);
   debug("MBI flags 0x%x\n", info->mbi->flags);

   multiboot_memory_map_t* entry = (multiboot_memory_map_t*)info->mbi->mmap_addr;
   while((uint32_t)entry < (info->mbi->mmap_addr + info->mbi->mmap_length)) {
      // TODO print "[start - end] type" for each entry
      debug("[0x%x - ", (unsigned int)entry->addr);
      debug("0x%x]", (unsigned int) (entry->len + entry->addr - 1));
      debug(" %s\n", inttypetochar(entry->type));
      entry++;
   }

}
