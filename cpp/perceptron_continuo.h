class PerceptronContinuo
{
private:
    Library lib;
    CalculoError err;
    static const int numEntradas = 2;
    static const int numEjemplos = 4;
    float pesos[numEntradas + 1]; // +1 para el sesgo
    float tasaAprendizaje = 0.1;
    const float umbralErrorTotal = 0.001;
    const float umbralDifErrores = 0.001;
    int entradas[numEjemplos][numEntradas] = {
        {0, 0},
        {0, 1},
        {1, 0},
        {1, 1}};
    float salidaDeseada[numEjemplos] = {0.0, 0.2, 0.7, 1.0}; // Valores continuos

public:
    PerceptronContinuo()
    {
        lib.randomseed();
        // Inicializar pesos con valores aleatorios
        for (int i = 0; i <= numEntradas; i++)
        {
            pesos[i] = lib.random(-100, 100) / 100.0;
        }
    }

    void entrenar()
    {
        bool aprendizajeCompleto = false;
        int epoca = 0;
        float errorTotalAnterior = 0;
        while (!aprendizajeCompleto && epoca < 200)
        {
            aprendizajeCompleto = true;
            float errorTotal = 0;
            for (int i = 0; i < numEjemplos; i++)
            {
                float suma = pesos[numEntradas]; // Inicializar con el sesgo
                for (int j = 0; j < numEntradas; j++)
                {
                    suma += entradas[i][j] * pesos[j];
                }
                float salidaObtenida = suma; // Función de activación lineal
                float error = err.errorDiferencia(salidaDeseada[i], salidaObtenida);
                errorTotal += abs(error);
                if (error != 0)
                {
                    aprendizajeCompleto = false;
                    // Actualizar pesos y sesgo
                    for (int j = 0; j < numEntradas; j++)
                    {
                        pesos[j] += tasaAprendizaje * error * entradas[i][j];
                    }
                    pesos[numEntradas] += tasaAprendizaje * error; // Actualizar el sesgo
                }
            }
            float difErrores = abs(errorTotal - errorTotalAnterior);
            if (aprendizajeCompleto || errorTotal < umbralErrorTotal || difErrores < umbralErrorTotal) // Criterio de parada adicional basado en el error total
            {
                break;
            }
            epoca++;
            errorTotalAnterior = errorTotal;
            lib.println("Epoca: " + std::to_string(epoca) + ", Error total: " + std::to_string(errorTotal));
        }
        // print la ecuacion de la recta obtenida sin reemplaar los valores
        lib.println("Ecuacion de la recta obtenida: ");
        for (int i = 0; i < numEntradas; i++)
        {
            lib.print(std::to_string(pesos[i]) + "x" + std::to_string(i + 1));
            if (i < numEntradas - 1)
            {
                lib.print(" + ");
            }
        }
        lib.println(" + " + std::to_string(pesos[numEntradas])); // Imprimir el sesgo
    }

    float predecir(int entrada1, int entrada2)
    {
        float suma = pesos[numEntradas]; // Inicializar con el sesgo
        suma += entrada1 * pesos[0] + entrada2 * pesos[1];
        float salidaObtenida = suma;
        lib.println("Prediccion Continua para (" + std::to_string(entrada1) + ", " + std::to_string(entrada2) + ") suma = " + std::to_string(salidaObtenida));
        return salidaObtenida;
    }
};