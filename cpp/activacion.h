#ifndef ACTIVACION_H
#define ACTIVACION_H

#include <cmath>

class Activacion
{
public:
    // Función de activación lineal
    float lineal(float x)
    {
        return x;
    }

    // Función de activación escalón
    int escalon(float x)
    {
        return (x >= 0) ? 1 : 0;
    }

    // Función de activación sigmoide
    float sigmoide(float x)
    {
        return 1 / (1 + exp(-x));
    }

    // Derivada de la función sigmoide
    float derivadaSigmoide(float x)
    {
        float sig = sigmoide(x);
        return sig * (1 - sig);
    }
};

#endif // ACTIVACION_H