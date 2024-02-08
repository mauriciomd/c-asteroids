#include <math.h>
#include "direction.h"

#define PI 3.14159

#define TO_RADIANS(angle) (angle * PI / 180)

void direction_increase_angle(direction_t* d, double angle) {
   if (d->angle >= 360) d->angle -= 360;
   d->angle += angle;

   d->vector.x = cos(TO_RADIANS(d->angle));
   d->vector.y = sin(TO_RADIANS(d->angle));
}

void direction_decrease_angle(direction_t* d, double angle) {
   if (d->angle <= 0) d->angle += 360;
   d->angle -= angle;

   d->vector.x = cos(TO_RADIANS(d->angle));
   d->vector.y = sin(TO_RADIANS(d->angle));
}

void set_direction_vetor(direction_t* d, double angle) {
   d->angle = angle;
   d->vector.x = cos(TO_RADIANS(d->angle));
   d->vector.y = sin(TO_RADIANS(d->angle));
}