#ifndef VIZ_H
#define VIZ_H

// function that turns a 2d vector passed as two separate floats into a rgb color vector, where r, g and b are passed as ints by reference. 
// the angle is encoded in the hue and the magnitude in the value
void vect_to_rgb(float u, float v, int &r, int &g, int &b, float scale);

#endif // !VIZ_H