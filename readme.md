# Perceptron Implementation on ESP32

This project implements both Binary and Continuous Perceptrons on an ESP32 microcontroller. The perceptrons are trained and used to make predictions based on button inputs, with LED outputs indicating the results.

## Table of Contents

1. [Introduction](#introduction)
2. [Components](#components)
3. [Setup](#setup)
4. [Implementation](#implementation)
5. [Usage](#usage)
6. [Results](#results)

## Introduction

This project demonstrates the implementation of two types of perceptrons:
1. Binary Perceptron: For classification tasks with binary outputs.
2. Continuous Perceptron: For regression tasks with continuous outputs.

Both perceptrons are trained and executed on an ESP32 board, with buttons for input and LEDs for output visualization.

## Components

- ESP32 development board
- 2 push buttons
- 2 LEDs (one for Binary Perceptron, one for Continuous Perceptron)
- Resistors for LEDs
- Breadboard and jumper wires

## Setup

1. Connect the components to the ESP32 as follows:
   - Button 1 to GPIO 22
   - Button 2 to GPIO 23
   - Binary Perceptron LED to GPIO 5
   - Continuous Perceptron LED to GPIO 18

2. Install the necessary libraries and header files:
   - lib.h
   - activacion.h
   - calculo_error.h
   - perceptron_binario.h
   - perceptron_continuo.h

## Implementation

The main code for the ESP32 is as follows:

```cpp
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
    lib.println("Starting predictions...");
}

void loop()
{
    lib.println("===================================");
    int button1State = !digitalRead(BUTTON1_PIN);
    int button2State = !digitalRead(BUTTON2_PIN);
    
    int predictionBinario = perceptronBinario.predecir(button1State, button2State);
    float predictionContinuo = perceptronContinuo.predecir(button1State, button2State);
    
    digitalWrite(LED_BINARIO_PIN, predictionBinario == 1 ? HIGH : LOW);
    digitalWrite(LED_CONTINUO_PIN, predictionContinuo > 0.5 ? HIGH : LOW);
    
    lib.println(predictionBinario == 1 ? "Binary LED on" : "Binary LED off");
    lib.println(predictionContinuo > 0.5 ? "Continuous LED on" : "Continuous LED off");
    
    delay(1000);
}

```
## Implementation

The main code for the ESP32 is as follows:

## Usage

Upload the code to your ESP32 board.
Open the Serial Monitor to view the training process and predictions.
Press the buttons in different combinations to see how the perceptrons respond:

(0, 0): Neither button pressed
(0, 1): Only Button 2 pressed
(1, 0): Only Button 1 pressed
(1, 1): Both buttons pressed

## Results
The perceptrons will make predictions based on the button inputs:

## Binary Perceptron:

LED on for positive classification (1)
LED off for negative classification (0)


## Continuous Perceptron:

LED on for predictions > 0.5
LED off for predictions <= 0.5

Observe how the LEDs respond to different button combinations to see the perceptrons in action!
