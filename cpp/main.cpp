#include <stdlib.h> // Asegúrate de incluir cmath en lugar de stdlib.h o math.h

#include "lib.h"
#include "activacion.h"
#include "calculo_error.h"
#include "perceptron_binario.h"
#include "perceptron_continuo.h"

int main(int argc, char const *argv[])
{
    Library lib;
    lib.Serial_begin();
    PerceptronBinario perceptronBinario;
    PerceptronContinuo perceptronContinuo;

    perceptronBinario.entrenar();
    perceptronContinuo.entrenar();

    int entradas[4][2] = {
        {0, 0},
        {0, 1},
        {1, 0},
        {1, 1}};

    lib.println("Iniciando predicciones...");
    for (int i = 0; i < 4; i++)
    {
        int button1State = entradas[i][0];
        int button2State = entradas[i][1];

        lib.println("===================================");
        // Usa los perceptrones para predecir
        int predictionBinario = perceptronBinario.predecir(button1State, button2State);
        float predictionContinuo = perceptronContinuo.predecir(button1State, button2State);
        lib.println("");
        // Controla el LED binario basado en la predicción binaria
        if (predictionBinario == 1)
        {
            lib.println("LED Binario encendido");
        }
        else
        {
            lib.println("LED Binario apagado");
        }

        // Controla el LED continuo basado en la predicción continua
        if (predictionContinuo > 0.5)
        {
            lib.println("LED Continuo encendido");
        }
        else
        {
            lib.println("LED Continuo apagado");
        }
    }

    return 0;
}
