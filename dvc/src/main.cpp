#include "lib.h"
#include "../../cpp/activacion.h"
#include "../../cpp/calculo_error.h"
#include "../../cpp/perceptron_binario.h"
#include "../../cpp/perceptron_continuo.h"

#define BUTTON1_PIN 22
#define BUTTON2_PIN 23
#define LED_BINARIO_PIN 5
#define LED_CONTINUO_PIN 18

PerceptronBinario perceptronBinario;
PerceptronContinuo perceptronContinuo;
Library lib;

void setup()
{

    lib.Serial_begin();

    pinMode(LED_BINARIO_PIN, OUTPUT);
    pinMode(LED_CONTINUO_PIN, OUTPUT);
    pinMode(BUTTON1_PIN, INPUT_PULLUP);
    pinMode(BUTTON2_PIN, INPUT_PULLUP);

    perceptronBinario.entrenar();
    perceptronContinuo.entrenar();
    lib.println("Iniciando predicciones...");
}

void loop()
{
    lib.println("===================================");
    int button1State = !digitalRead(BUTTON1_PIN);
    int button2State = !digitalRead(BUTTON2_PIN);

    // Usa los perceptrones para predecir
    int predictionBinario = perceptronBinario.predecir(button1State, button2State);
    float predictionContinuo = perceptronContinuo.predecir(button1State, button2State);

    // Controla el LED binario basado en la predicción binaria
    if (predictionBinario == 1)
    {
        digitalWrite(LED_BINARIO_PIN, HIGH);
        lib.println("LED Binario encendido");
    }
    else
    {
        digitalWrite(LED_BINARIO_PIN, LOW);
        lib.println("LED Binario apagado");
    }

    // Controla el LED continuo basado en la predicción continua
    if (predictionContinuo > 0.5)
    {
        digitalWrite(LED_CONTINUO_PIN, HIGH);
        lib.println("LED Continuo encendido");
    }
    else
    {
        digitalWrite(LED_CONTINUO_PIN, LOW);
        lib.println("LED Continuo apagado");
    }

    delay(1000);
}