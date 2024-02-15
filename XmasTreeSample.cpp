#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/clocks.h"
#include "pio_spi.h"

#include "RGBTree.h"
#include "NamedColours.h"

constexpr uint32_t LED_GPIO_PIN {21};

int64_t alarm_callback(alarm_id_t id, void *user_data) {
    // Put your timeout handler code in here
    return 0;
}

int main()
{
    ThePiHut::XMasTree xmas_tree;
 
    stdio_init_all();

    // // I2C Initialisation. Using it at 400Khz.
    // i2c_init(I2C_PORT, 400*1000);
    
    // gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    // gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    // gpio_pull_up(I2C_SDA);
    // gpio_pull_up(I2C_SCL);

    // // Timer example code - This example fires off the callback after 2000ms
    // add_alarm_in_ms(2000, alarm_callback, NULL, false);
    // puts("Hello, world!");

    xmas_tree.init();
    xmas_tree.on();

    // sleep_ms(1000);

    // xmas_tree.set_tree(16, ThePiHut::NamedColour.at("red"));

    // sleep_ms(1000);

    // xmas_tree.set_tree(16, ThePiHut::NamedColour.at("blue"));

    // sleep_ms(1000);

    // xmas_tree.set_tree(16, ThePiHut::NamedColour.at("green"));

    // sleep_ms(1000);

    // for(auto &colour : ThePiHut::NamedColour){
    //     xmas_tree.set_tree(8, colour.second);

    //     sleep_ms(1000);
    // }

    sleep_ms(1000);
    xmas_tree.off();

    xmas_tree.one_by();

    xmas_tree.set_light(0x3, 16, ThePiHut::NamedColour.at("blue"));
    xmas_tree.update();

    xmas_tree.validate();

    return 0;
}
