#ifndef DIRECTION
#define DIRECTION

typedef struct Vector {
    double x;
    double y;
} vector_t;

typedef struct Direction {
    vector_t vector;
    double angle;
} direction_t;

void direction_increase_angle(direction_t* d, double angle);
void direction_decrease_angle(direction_t* d, double angle);
void set_direction_vetor(direction_t* d, double angle);
#endif