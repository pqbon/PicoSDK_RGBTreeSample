#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/clocks.h"
#include "pio_spi.h"

#include "RGBTree.h"
#include "NamedColours.h"

int main()
{
    ThePiHut::XMasTree xmas_tree;
 
    stdio_init_all();

    xmas_tree.init();
    xmas_tree.on();

    sleep_ms(1000);
    xmas_tree.off();

    xmas_tree.one_by();

    xmas_tree.set_light(0x3, 16, ThePiHut::NamedColour.at("blue"));
    xmas_tree.update();

    xmas_tree.validate();

    xmas_tree.off();
    return 0;
}
