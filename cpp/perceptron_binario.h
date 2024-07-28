class PerceptronBinario
{
private:
    Library lib;
    Activacion act;
    CalculoError err;
    static const int numEntradas = 2;
    static const int numEjemplos = 4;
    float pesos[numEntradas + 1]; // +1 para el sesgo
    float tasaAprendizaje = 0.1;
    const float umbralErrorTotal = 0.01;
    int entradas[numEjemplos][numEntradas] = {
        {0, 0},
        {0, 1},
        {1, 0},
        {1, 1}};
    int salidaDeseada[numEjemplos] = {0, 1, 0, 0};

public:
    PerceptronBinario()
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
        while (!aprendizajeCompleto && epoca < 200)
        { // Límite de 10000 épocas para evitar bucles infinitos
            aprendizajeCompleto = true;
            int clasificacionesCorrectas = 0;
            float errorTotal = 0;
            for (int i = 0; i < numEjemplos; i++)
            {
                float suma = pesos[numEntradas]; // Inicializar con el sesgo
                // Calcular la suma ponderada de las entradas
                for (int j = 0; j < numEntradas; j++)
                {
                    suma += entradas[i][j] * pesos[j];
                }
                // Aplicar la función de activación (función escalón)
                int salidaObtenida = act.escalon(suma);
                // Calcular error
                float error = err.errorDiferencia(salidaDeseada[i], salidaObtenida);
                errorTotal += error;
                // Actualizar pesos si la salida es incorrecta
                if (salidaObtenida != salidaDeseada[i])
                {
                    aprendizajeCompleto = false;

                    for (int j = 0; j < numEntradas; j++)
                    {
                        pesos[j] += tasaAprendizaje * error * entradas[i][j];
                    }
                    pesos[numEntradas] += tasaAprendizaje * error; // Actualizar el sesgo
                }
                else
                {
                    clasificacionesCorrectas++;
                }
            }
            epoca++;
            lib.println("Epoca: " + std::to_string(epoca) + ", Error total: " + std::to_string(errorTotal) + ", Clasificaciones correctas: " + std::to_string(clasificacionesCorrectas));
        }
        // Mostrar pesos
        for (int i = 0; i <= numEntradas; i++)
        {
            lib.println("Peso " + std::to_string(i) + ": " + std::to_string(pesos[i]));
        }
        // Mostrar la ecuación
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

    int predecir(int entrada1, int entrada2)
    {
        float suma = pesos[numEntradas]; // Inicializar con el sesgo
        // Calcular la suma ponderada de las entradas
        suma += entrada1 * pesos[0] + entrada2 * pesos[1];
        // Aplicar la función de activación (función escalón)
        int salida = act.escalon(suma);
        lib.println("Prediccion Binaria para (" + std::to_string(entrada1) + ", " + std::to_string(entrada2) + ") suma = " + std::to_string(suma) + ": " + std::to_string(salida));
        return salida;
    }
};
