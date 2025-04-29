#include "datamemory.h"

Memory::Memory() {
    // Reserve room for pointers only. Capacity becomes 65,536, size stays 0.
    pages.reserve(NumPages);                            
}

uint8_t Memory::loadByte(uint32_t addr) const {
    uint32_t page_num = addr >> PageBits;               // Get the page number
    if (page_num < pages.size() && pages[page_num])     // Check if page exists
        return (*pages[page_num])[addr & PageMask];     // Return the byte
    return 0;                                           // Unmapped regions return 0
    } // Added missing closing brace for loadByte

void Memory::storeByte(uint32_t addr, uint8_t val) {
    uint32_t page_num = addr >> PageBits;               // Get the page number
    if (page_num >= pages.size())                       // Check if directory is too small
        pages.resize(page_num + 1);                     // Expand directory

    auto &p = pages[page_num];                          // Reference to unique_ptr<Page>
    if (!p) p = std::make_unique<Page>();               // Allocate page on first access
    (*p)[addr & PageMask] = val;                        // Write the byte
}
