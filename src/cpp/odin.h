#ifndef ODIN_H
#define ODIN_H

struct Vec3 {
    float r;
    float g;
    float b;
};

extern "C" {   

void from_odin();
Vec3 get_clear_color();

}

#endif // ODIN_H