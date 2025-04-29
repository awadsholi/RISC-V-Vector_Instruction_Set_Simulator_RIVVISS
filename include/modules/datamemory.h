#ifndef MEMORY_H
#define MEMORY_H

#include <systemc.h>
#include <vector>
#include <unordered_map>
#include <memory>
#include <cstdint>
#include <array> // Include array header for std::array

class Memory {
    static constexpr uint32_t PageBits = 16;                
    static constexpr uint32_t PageSize = 1u << PageBits;    // 2^16 = 65,536 bytes per page
    static constexpr uint32_t PageMask = PageSize - 1;      // Mask for the low 16 bits
    static constexpr uint32_t NumPages = 1u << (32 - PageBits); // 4 GB / 64 KB = 65,536 pages

    using Page = std::array<uint8_t, PageSize>;             // One physical page (64 KiB)

    std::vector<std::unique_ptr<Page>> pages;               // Directory: index = page number

public:
    Memory();
    uint8_t loadByte(uint32_t addr) const;
    void storeByte(uint32_t addr, uint8_t val);    

};

extern Memory* datamem;

#endif 