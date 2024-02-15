#pragma once
#include "pio_spi.h"

#include <cstdint>
#include <array>
#include <vector>
#include <concepts>
#include <ranges>
//#include <string> //XXX -- not needed unless we support string colours.

namespace ThePiHut {

constexpr uint32_t LedCount {25};

class Colour {
public:
    Colour(uint8_t const red_, uint8_t const green_, uint8_t const blue_);
    Colour(uint32_t const rgb_);
    Colour();
    //Colour(std::string hex_str); //XXX -- do we need this?

    void set_colour(uint8_t const red_, uint8_t const green_, uint8_t const blue_);
    void set_colour(uint32_t const rgb_);

    operator uint32_t() const;

protected:
    uint8_t Red;
    uint8_t Green;
    uint8_t Blue;
};

constexpr uint32_t XMAS_TREE_PIN_MISO {12};
constexpr uint32_t XMAS_TREE_PIN_CS   {11}; // ?? XXX -- what do we do here?
constexpr uint32_t XMAS_TREE_PIN_SCK  {28};
constexpr uint32_t XMAS_TREE_PIN_MOSI {9};

class XMasTree {
public:
    XMasTree();
    XMasTree(uint32_t miso_, uint32_t mosi_, uint32_t sck_, uint32_t cs_);

    void init();

    uint32_t set_light(uint32_t const idx_, uint8_t const brightness_, Colour const &colour_);
    template <typename T> requires std::ranges::range<T>
    void set_lights(T const light_list, uint8_t const brightness_, Colour const &colour_);
    void off_light(uint32_t const idx_);

    void set_tree(uint8_t const brightness_, Colour const &colour_);

    void on();
    void off();

    void one_by();
    void validate();

    void update();

private:
    uint32_t const PIN_MISO;
    uint32_t const PIN_CS;
    uint32_t const PIN_SCK;
    uint32_t const PIN_MOSI;

    union {
        std::array<uint32_t, LedCount> LedValuesU32;
        std::array<uint8_t, LedCount * sizeof(uint32_t)> LedValuesU8;
    };

    pio_spi_inst_t spi;

public:
    std::array<uint32_t, 1> const star  {0x3};
    std::array<uint32_t, 12> const front {0x0, 0x1, 0x2, 0x6, 0x5, 0x4, 0xf, 0xe, 0xe, 0x10, 0x11, 0x12};
    std::array<uint32_t, 12> const back  {0x7, 0x8, 0x9, 0xc, 0xb, 0xa, 0x13, 0x14, 0x15, 0x18, 0x17, 0x16};
    std::array<uint32_t, 12> const right {0x0, 0x1, 0x2, 0x9, 0x8, 0x7, 0x10, 0x11, 0x12, 0x18, 0x17, 0x16};
    std::array<uint32_t, 12> const left  {0x6, 0x5, 0x4, 0xc, 0xb, 0xa, 0xf, 0xe, 0xe, 0x13, 0x14, 0x15};
    std::array<uint32_t, 12> const odd   {0x1, 0x3, 0x5, 0x7, 0x9, 0xb, 0xd, 0xf, 0x11, 0x13, 0x15, 0x17};
    std::array<uint32_t, 12> const even  {0x0, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16};

    std::array<uint32_t, 3> const fr_f   {0x0, 0x1, 0x2};
    std::array<uint32_t, 3> const fr_b   {0x7, 0x8, 0x9};
    std::array<uint32_t, 3> const fl_f   {0x6, 0x5, 0x4};
    std::array<uint32_t, 3> const fl_b   {0xc, 0xb, 0xa};
    std::array<uint32_t, 3> const ff_l   {0xf, 0xe, 0xd};
    std::array<uint32_t, 3> const ff_r   {0x10, 0x11, 0x12};
    std::array<uint32_t, 3> const bb_l   {0x18, 0x17, 0x16};
    std::array<uint32_t, 3> const bb_r   {0x13, 0x14, 0x15};

    std::array<uint32_t, 8> const bot_row {0x0, 0x7, 0x6, 0xc, 0xf, 0x10, 0x18, 0x13};
    std::array<uint32_t, 8> const mid_row {0x1, 0x8, 0x5, 0xb, 0xe, 0x11, 0x17, 0x14};
    std::array<uint32_t, 8> const top_row {0x2, 0x9, 0x4, 0xa, 0xd, 0x12, 0x16, 0x15};
};
}