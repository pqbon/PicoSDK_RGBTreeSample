#include "RGBTree.h"
#include "pio_spi.h"
#include "NamedColours.h"

#include "pico/stdlib.h"

#include <stdio.h>
#include <cstring>
#include <bit>

namespace ThePiHut {

Colour::Colour(uint8_t const red_, uint8_t const green_, uint8_t const blue_) : Red {red_}, Green {green_}, Blue {blue_}{
}

Colour::Colour(uint32_t const rgb_) : Red {static_cast<uint8_t>((rgb_ >> 16) & 0xff)}, Green {static_cast<uint8_t>((rgb_ >> 8) & 0xff)}, Blue {static_cast<uint8_t>(rgb_ & 0xff)}{
}

Colour::Colour(){

}
void Colour::set_colour(uint8_t const red_, uint8_t const green_, uint8_t const blue_){
    Red = red_;
    Green = green_;
    Blue = blue_;
}

void Colour::set_colour(uint32_t const rgb_){
    Red = static_cast<uint8_t>((rgb_ >> 16) & 0xff);
    Green = static_cast<uint8_t>((rgb_ >> 8) & 0xff);
    Blue = static_cast<uint8_t>((rgb_) & 0xff);
}

Colour::operator uint32_t() const {
    uint32_t const RGB_val {(static_cast<uint32_t>(Red) << 16) | (static_cast<uint32_t>(Green) << 8) | (static_cast<uint32_t>(Blue))};

    return RGB_val;
}

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