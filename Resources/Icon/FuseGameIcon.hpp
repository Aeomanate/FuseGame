//
// Created by Lyosha12 on 24.02.2019.
//

#ifndef FUSEGAME_ICON_H
#define FUSEGAME_ICON_H

typedef struct {
    unsigned const width, height, bytes_per_pixel;
    unsigned char const pixel_data[32*32*4 + 1];
} FuseGameIcon;

extern const FuseGameIcon FUSEGAME_ICON;

#endif //FUSEGAME_ICON_H
