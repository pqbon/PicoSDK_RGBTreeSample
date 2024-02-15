#pragma once

#include "RGBTree.h"
#include <map>
#include <string>

namespace ThePiHut {
std::map<std::string, Colour const> const NamedColour {
    {"aliceblue",             Colour(0xf0f8ff)},
    {"antiquewhite",          Colour(0xfaebd7)},
    {"aqua",                  Colour(0x00ffff)},
    {"aquamarine",            Colour(0x7fffd4)},
    {"azure",                 Colour(0xf0ffff)},
    {"beige",                 Colour(0xf5f5dc)},
    {"bisque",                Colour(0xffe4c4)},
    {"black",                 Colour(0x000000)},
    {"blanchedalmond",        Colour(0xffebcd)},
    {"blue",                  Colour(0x0000ff)},
    {"blueviolet",            Colour(0x8a2be2)},
    {"brown",                 Colour(0xa52a2a)},
    {"burlywood",             Colour(0xdeb887)},
    {"cadetblue",             Colour(0x5f9ea0)},
    {"chartreuse",            Colour(0x7fff00)},
    {"chocolate",             Colour(0xd2691e)},
    {"coral",                 Colour(0xff7f50)},
    {"cornflowerblue",        Colour(0x6495ed)},
    {"cornsilk",              Colour(0xfff8dc)},
    {"crimson",               Colour(0xdc143c)},
    {"cyan",                  Colour(0x00ffff)},
    {"darkblue",              Colour(0x00008b)},
    {"darkcyan",              Colour(0x008b8b)},
    {"darkgoldenrod",         Colour(0xb8860b)},
    {"darkgray",              Colour(0xa9a9a9)},
    {"darkgreen",             Colour(0x006400)},
    {"darkgrey",              Colour(0xa9a9a9)},
    {"darkkhaki",             Colour(0xbdb76b)},
    {"darkmagenta",           Colour(0x8b008b)},
    {"darkolivegreen",        Colour(0x556b2f)},
    {"darkorange",            Colour(0xff8c00)},
    {"darkorchid",            Colour(0x9932cc)},
    {"darkred",               Colour(0x8b0000)},
    {"darksalmon",            Colour(0xe9967a)},
    {"darkseagreen",          Colour(0x8fbc8f)},
    {"darkslateblue",         Colour(0x483d8b)},
    {"darkslategray",         Colour(0x2f4f4f)},
    {"darkslategrey",         Colour(0x2f4f4f)},
    {"darkturquoise",         Colour(0x00ced1)},
    {"darkviolet",            Colour(0x9400d3)},
    {"deeppink",              Colour(0xff1493)},
    {"deepskyblue",           Colour(0x00bfff)},
    {"dimgray",               Colour(0x696969)},
    {"dimgrey",               Colour(0x696969)},
    {"dodgerblue",            Colour(0x1e90ff)},
    {"firebrick",             Colour(0xb22222)},
    {"floralwhite",           Colour(0xfffaf0)},
    {"forestgreen",           Colour(0x228b22)},
    {"fuchsia",               Colour(0xff00ff)},
    {"gainsboro",             Colour(0xdcdcdc)},
    {"ghostwhite",            Colour(0xf8f8ff)},
    {"gold",                  Colour(0xffd700)},
    {"goldenrod",             Colour(0xdaa520)},
    {"gray",                  Colour(0x808080)},
    {"green",                 Colour(0x008000)},
    {"greenyellow",           Colour(0xadff2f)},
    {"grey",                  Colour(0x808080)},
    {"honeydew",              Colour(0xf0fff0)},
    {"hotpink",               Colour(0xff69b4)},
    {"indianred",             Colour(0xcd5c5c)},
    {"indigo",                Colour(0x4b0082)},
    {"ivory",                 Colour(0xfffff0)},
    {"khaki",                 Colour(0xf0e68c)},
    {"lavender",              Colour(0xe6e6fa)},
    {"lavenderblush",         Colour(0xfff0f5)},
    {"lawngreen",             Colour(0x7cfc00)},
    {"lemonchiffon",          Colour(0xfffacd)},
    {"lightblue",             Colour(0xadd8e6)},
    {"lightcoral",            Colour(0xf08080)},
    {"lightcyan",             Colour(0xe0ffff)},
    {"lightgoldenrodyellow",  Colour(0xfafad2)},
    {"lightgray",             Colour(0xd3d3d3)},
    {"lightgreen",            Colour(0x90ee90)},
    {"lightgrey",             Colour(0xd3d3d3)},
    {"lightpink",             Colour(0xffb6c1)},
    {"lightsalmon",           Colour(0xffa07a)},
    {"lightseagreen",         Colour(0x20b2aa)},
    {"lightskyblue",          Colour(0x87cefa)},
    {"lightslategray",        Colour(0x778899)},
    {"lightslategrey",        Colour(0x778899)},
    {"lightsteelblue",        Colour(0xb0c4de)},
    {"lightyellow",           Colour(0xffffe0)},
    {"lime",                  Colour(0x00ff00)},
    {"limegreen",             Colour(0x32cd32)},
    {"linen",                 Colour(0xfaf0e6)},
    {"magenta",               Colour(0xff00ff)},
    {"maroon",                Colour(0x800000)},
    {"mediumaquamarine",      Colour(0x66cdaa)},
    {"mediumblue",            Colour(0x0000cd)},
    {"mediumorchid",          Colour(0xba55d3)},
    {"mediumpurple",          Colour(0x9370db)},
    {"mediumseagreen",        Colour(0x3cb371)},
    {"mediumslateblue",       Colour(0x7b68ee)},
    {"mediumspringgreen",     Colour(0x00fa9a)},
    {"mediumturquoise",       Colour(0x48d1cc)},
    {"mediumvioletred",       Colour(0xc71585)},
    {"midnightblue",          Colour(0x191970)},
    {"mintcream",             Colour(0xf5fffa)},
    {"mistyrose",             Colour(0xffe4e1)},
    {"moccasin",              Colour(0xffe4b5)},
    {"navajowhite",           Colour(0xffdead)},
    {"navy",                  Colour(0x000080)},
    {"oldlace",               Colour(0xfdf5e6)},
    {"olive",                 Colour(0x808000)},
    {"olivedrab",             Colour(0x6b8e23)},
    {"orange",                Colour(0xffa500)},
    {"orangered",             Colour(0xff4500)},
    {"orchid",                Colour(0xda70d6)},
    {"palegoldenrod",         Colour(0xeee8aa)},
    {"palegreen",             Colour(0x98fb98)},
    {"paleturquoise",         Colour(0xafeeee)},
    {"palevioletred",         Colour(0xdb7093)},
    {"papayawhip",            Colour(0xffefd5)},
    {"peachpuff",             Colour(0xffdab9)},
    {"peru",                  Colour(0xcd853f)},
    {"pink",                  Colour(0xffc0cb)},
    {"plum",                  Colour(0xdda0dd)},
    {"powderblue",            Colour(0xb0e0e6)},
    {"purple",                Colour(0x800080)},
    {"red",                   Colour(0xff0000)},
    {"rosybrown",             Colour(0xbc8f8f)},
    {"royalblue",             Colour(0x4169e1)},
    {"saddlebrown",           Colour(0x8b4513)},
    {"salmon",                Colour(0xfa8072)},
    {"sandybrown",            Colour(0xf4a460)},
    {"seagreen",              Colour(0x2e8b57)},
    {"seashell",              Colour(0xfff5ee)},
    {"sienna",                Colour(0xa0522d)},
    {"silver",                Colour(0xc0c0c0)},
    {"skyblue",               Colour(0x87ceeb)},
    {"slateblue",             Colour(0x6a5acd)},
    {"slategray",             Colour(0x708090)},
    {"slategrey",             Colour(0x708090)},
    {"snow",                  Colour(0xfffafa)},
    {"springgreen",           Colour(0x00ff7f)},
    {"steelblue",             Colour(0x4682b4)},
    {"tan",                   Colour(0xd2b48c)},
    {"teal",                  Colour(0x008080)},
    {"thistle",               Colour(0xd8bfd8)},
    {"tomato",                Colour(0xff6347)},
    {"turquoise",             Colour(0x40e0d0)},
    {"violet",                Colour(0xee82ee)},
    {"wheat",                 Colour(0xf5deb3)},
    {"white",                 Colour(0xffffff)},
    {"whitesmoke",            Colour(0xf5f5f5)},
    {"yellow",                Colour(0xffff00)},
    {"yellowgreen",           Colour(0x9acd32)}
};
}
