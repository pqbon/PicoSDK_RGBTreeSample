module;

#include <cstdint>

export module Colours;
export namespace ThePiHut {

class Colour {
public:
    Colour(std::uint8_t const red_, std::uint8_t const green_, std::uint8_t const blue_);
    Colour(std::uint32_t const rgb_);
    Colour();
    //Colour(std::string hex_str); //XXX -- do we need this?

    void set_colour(std::uint8_t const red_, std::uint8_t const green_, std::uint8_t const blue_);
    void set_colour(std::uint32_t const rgb_);

    operator std::uint32_t() const;

protected:
    std::uint8_t Red;
    std::uint8_t Green;
    std::uint8_t Blue;
};

//module : private;

Colour::Colour(std::uint8_t const red_, std::uint8_t const green_, std::uint8_t const blue_) : Red {red_}, Green {green_}, Blue {blue_}{
}

Colour::Colour(std::uint32_t const rgb_) : Red {static_cast<std::uint8_t>((rgb_ >> 16) & 0xff)}, Green {static_cast<std::uint8_t>((rgb_ >> 8) & 0xff)}, Blue {static_cast<std::uint8_t>(rgb_ & 0xff)}{
}

Colour::Colour(){
}

void Colour::set_colour(std::uint8_t const red_, std::uint8_t const green_, std::uint8_t const blue_){
    Red = red_;
    Green = green_;
    Blue = blue_;
}

void Colour::set_colour(std::uint32_t const rgb_){
    Red = static_cast<std::uint8_t>((rgb_ >> 16) & 0xff);
    Green = static_cast<std::uint8_t>((rgb_ >> 8) & 0xff);
    Blue = static_cast<std::uint8_t>((rgb_) & 0xff);
}

Colour::operator std::uint32_t() const {
    std::uint32_t const RGB_val {(static_cast<std::uint32_t>(Red) << 16) | (static_cast<std::uint32_t>(Green) << 8) | (static_cast<std::uint32_t>(Blue))};

    return RGB_val;
}

};