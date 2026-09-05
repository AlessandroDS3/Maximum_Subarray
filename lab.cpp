#include <iostream>
#include <chrono>
#include <cstdlib>
#include <iomanip>
using namespace std;

int cubica(int a[], int n) {
    int mejor = a[0];

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int suma = 0;

            for (int k = i; k <= j; k++) {
                suma = suma + a[k];
            }

            if (suma > mejor) {
                mejor = suma;
            }
        }
    }

    return mejor;
}

int cuadratica(int a[], int n) {
    int mejor = a[0];

    for (int i = 0; i < n; i++) {
        int suma = 0;

        for (int j = i; j < n; j++) {
            suma = suma + a[j];

            if (suma > mejor) {
                mejor = suma;
            }
        }
    }

    return mejor;
}

int kanade(int a[], int n) {
    int aqui = a[0];
    int global = a[0];

    for (int i = 1; i < n; i++) {

        if (a[i] > aqui + a[i])
            aqui = a[i];
        else
            aqui = aqui + a[i];

        if (aqui > global)
            global = aqui;
    }

    return global;
}

void llenarArreglo(int a[], int n) {
    for (int i = 0; i < n; i++) {
        a[i] = (rand() % 201) - 100; // numero entre -100 y 100
    }
}

int main() {
    srand(12345);
    cout << fixed << setprecision(6);

    // Prueba de las tres versiones con 100 arreglos pequenos.
    cout << "Prueba\tn\tCubica\tCuadratica\tKadane" << endl;
    for (int prueba = 1; prueba <= 100; prueba++) {
        int a[20];
        int n = 2 + rand() % 19;
        llenarArreglo(a, n);
        // Aseguramos que cada arreglo tenga ambos signos.
        a[0] = 1 + rand() % 100;
        a[1] = -(1 + rand() % 100);

        int suma1 = cubica(a, n);
        int suma2 = cuadratica(a, n);
        int suma3 = kanade(a, n);
        cout << prueba << "\t" << n << "\t" << suma1 << "\t"
             << suma2 << "\t" << suma3 << endl;
    }

    double ultimoCubica = 0;
    double ultimoCuadratica = 0;
    double ultimoKadane = 0;
    double anterior = 0;

    cout << "\nCubica" << endl;
    cout << "n\tTiempo(ms)\tRazon\tSuma" << endl;
    anterior = 0;
    for (int n = 1000; n <= 8000; n = n * 2) {
        int* a = new int[n];
        srand(12345);
        llenarArreglo(a, n);

        auto inicio = chrono::steady_clock::now();
        int suma = cubica(a, n);
        auto fin = chrono::steady_clock::now();

        double ms = chrono::duration<double, milli>(fin - inicio).count();
        cout << n << "\t" << ms << "\t";
        if (anterior > 0) {
            cout << ms / anterior;
        } else {
            cout << "-";
        }
        cout << "\t" << suma << endl;
        anterior = ms;
        ultimoCubica = ms;
        delete[] a;
    }

    cout << "\nCuadratica" << endl;
    cout << "n\tTiempo(ms)\tRazon\tSuma" << endl;
    anterior = 0;
    for (int n = 1000; n <= 128000; n = n * 2) {
        int* a = new int[n];
        srand(12345);
        llenarArreglo(a, n);

        auto inicio = chrono::steady_clock::now();
        int suma = cuadratica(a, n);
        auto fin = chrono::steady_clock::now();

        double ms = chrono::duration<double, milli>(fin - inicio).count();
        cout << n << "\t" << ms << "\t";
        if (anterior > 0) {
            cout << ms / anterior;
        } else {
            cout << "-";
        }
        cout << "\t" << suma << endl;
        anterior = ms;
        ultimoCuadratica = ms;
        delete[] a;
    }

    cout << "\nKadane" << endl;
    cout << "n\tTiempo(ms)\tRazon\tSuma" << endl;
    anterior = 0;
    for (int n = 1000; n <= 32768000; n = n * 2) {
        int* a = new int[n];
        srand(12345);
        llenarArreglo(a, n);

        auto inicio = chrono::steady_clock::now();
        int suma = kanade(a, n);
        auto fin = chrono::steady_clock::now();

        double ms = chrono::duration<double, milli>(fin - inicio).count();
        cout << n << "\t" << ms << "\t";
        if (anterior > 0) {
            cout << ms / anterior;
        } else {
            cout << "-";
        }
        cout << "\t" << suma << endl;
        anterior = ms;
        ultimoKadane = ms;
        delete[] a;
    }

    // Estimaciones en milisegundos para cien millones de elementos.
    double factorCubica = 100000000.0 / 8000;
    double factorCuadratica = 100000000.0 / 128000;
    double factorKadane = 100000000.0 / 32768000;
    double predCubica = ultimoCubica * factorCubica * factorCubica * factorCubica;
    double predCuadratica = ultimoCuadratica * factorCuadratica * factorCuadratica;
    double predKadane = ultimoKadane * factorKadane;

    cout << "\nPredicciones para n = 100000000 (ms)" << endl;
    cout << "Cubica: " << predCubica << endl;
    cout << "Cuadratica: " << predCuadratica << endl;
    cout << "Kadane: " << predKadane << endl;

    // Probamos Kadane solo si la prediccion es menor de un minuto.
    if (predKadane < 60000) {
        int n = 100000000;
        int* a = new int[n];
        srand(12345);
        llenarArreglo(a, n);

        auto inicio = chrono::steady_clock::now();
        int suma = kanade(a, n);
        auto fin = chrono::steady_clock::now();

        double ms = chrono::duration<double, milli>(fin - inicio).count();
        cout << "Kadane medido (ms): " << ms << endl;
        cout << "Suma: " << suma << endl;
        delete[] a;
    }

    return 0;
}
