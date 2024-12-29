module;

#include "pio_spi.h"
#include "pico/stdlib.h"

#include <cstdint>
#include <array>
#include <vector>
#include <concepts>
#include <ranges>
#include <cstring>
#include <bit>

export module RGBTree;
import Colours;
import NamedColours;

export namespace ThePiHut {

constexpr uint32_t LedCount {25};

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

XMasTree::XMasTree() :  PIN_MISO {XMAS_TREE_PIN_MISO},
                        PIN_CS   {XMAS_TREE_PIN_CS},
                        PIN_SCK  {XMAS_TREE_PIN_SCK},
                        PIN_MOSI {XMAS_TREE_PIN_MOSI} {
}

XMasTree::XMasTree(uint32_t miso_, uint32_t mosi_, uint32_t sck_, uint32_t cs_) :
                        PIN_MISO {miso_},
                        PIN_CS {cs_},
                        PIN_SCK {sck_},
                        PIN_MOSI {mosi_} {

}

void XMasTree::init(){
    spi = {
            .pio = pio0,
            .sm = 0
    };
    float clkdiv = 31.25f;  // 1 MHz @ 125 clk_sys
    uint cpha0_prog_offs = pio_add_program(spi.pio, &spi_cpha0_program);

    pio_spi_init(spi.pio, spi.sm,
                cpha0_prog_offs,
                8,       // 8 bits per SPI frame
                clkdiv,
                false,
                false,
                PIN_SCK,
                PIN_MOSI,
                PIN_MISO
    );
}

uint32_t XMasTree::set_light(uint32_t const idx_, uint8_t const brightness_, Colour const &colour_){
    assert(brightness_ < 0b11100000);
    uint32_t const colour_int {colour_};
    uint32_t const light {static_cast<uint32_t>(0b11100000 | brightness_) | (colour_int << 8)};

    LedValuesU32.at(idx_) = light;

    return light;
}

template <typename T> requires std::ranges::range<T>
void XMasTree::set_lights(T const light_list, uint8_t const brightness_, Colour const &colour_){
    for(auto &light : light_list){
        set_light(light, brightness_, colour_);
    }
}

void XMasTree::off_light(uint32_t const idx_){
    set_light(idx_, 0x0, NamedColour.at("white"));
    update();
}

void XMasTree::on(){
    set_tree(31, NamedColour.at("white"));
}

void XMasTree::off(){
    set_tree(0, NamedColour.at("black"));
}

void XMasTree::set_tree(uint8_t const brightness_, Colour const &colour_){
    for(uint32_t idx {0}; idx < LedCount; ++idx){
        set_light(idx, brightness_, colour_);
    }
    update();
}

void XMasTree::one_by(){
    for(uint32_t idx {0}; idx < LedCount; ++idx){
        if(idx > 0){
            set_light(idx - 1, 0, NamedColour.at("black"));
        }
        set_light(idx, 31, NamedColour.at("white"));
        update();
        sleep_ms(333);
    }
    off_light(LedCount - 1);
}

void XMasTree::validate(){
    set_lights(star, 0x15, NamedColour.at("white"));
    set_lights(bot_row, 0x15, NamedColour.at("red"));
    set_lights(mid_row, 0x15, NamedColour.at("green"));
    set_lights(top_row, 0x15, NamedColour.at("blue"));
    update();
    sleep_ms(1000);
    set_lights(front, 0x15, NamedColour.at("red"));
    set_lights(back, 0x15, NamedColour.at("blue"));
    update();
    sleep_ms(1000);
    set_lights(left, 0x15, NamedColour.at("red"));
    set_lights(right, 0x15, NamedColour.at("green"));
    update();
    sleep_ms(1000);
    set_lights(fl_f, 0x15, NamedColour.at("red"));
    set_lights(fl_b, 0x15, NamedColour.at("green"));
    set_lights(fr_f, 0x15, NamedColour.at("blue"));
    set_lights(fr_b, 0x15, NamedColour.at("orange"));
    set_lights(ff_l, 0x15, NamedColour.at("red"));
    set_lights(ff_r, 0x15, NamedColour.at("green"));
    set_lights(bb_l, 0x8, NamedColour.at("green"));
    set_lights(bb_r, 0x8, NamedColour.at("red"));
    update();
}

void XMasTree::update(){
    constexpr uint32_t start_frame_sz {4};
    constexpr uint32_t end_frame_sz {5};
    constexpr uint32_t frame_sz {LedCount * sizeof(uint32_t)};
    constexpr uint32_t size {start_frame_sz + frame_sz + end_frame_sz};

    std::array<uint8_t, size> new_frame {};

    std::memset(new_frame.data(), 0x0, start_frame_sz);    
    std::memcpy(new_frame.data() + start_frame_sz, LedValuesU8.data(), frame_sz);    
    std::memset(new_frame.data() + start_frame_sz + frame_sz, 0x0, end_frame_sz);    
    
    pio_spi_write8_blocking(&spi, new_frame.data(), size);
}

}