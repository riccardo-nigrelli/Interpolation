#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifndef M_PI
    #define M_PI (3.14159265358979323846264338327950288)
#endif

int i, j;

/**
 * @brief   Funzione per il calcolo dei coefficienti    
 * @param   Puntatore alla funzione per il calcolo dell'ordinata della funzione in un punto 
 * @param   Estremo inferiore dell'intervallo
 * @param   Estremo superiore dell'intervallo
 * @param   Il grado del polinomio
 * @return  Array contenente i coefficienti
 */ 
double* chebyshev_coefficients(double function(double), double lower_bound, double upper_bound, int grade){

    double x, y, *coefficients = malloc(grade * sizeof(double));
    if (coefficients == NULL){
        perror("Errore nell'allocazione della memoria\n");
        abort();
    }

    for(i = 0; i < grade; i++){
        coefficients[i] = 0.0;
        for(j = 0; j < grade; j++){
            y = cos((2 * j + 1) * M_PI / (2 * grade));
            x = (y * (upper_bound - lower_bound) + (lower_bound + upper_bound))/2;
            coefficients[i] += function(x) * cos(i * ((2 * j + 1) * M_PI / (2 * grade)));    
        }
        coefficients[i] *= 2.0 / grade;
    }

    return coefficients;
}

/**
 * @brief   Funzione per il calcolo dei valori d'interpolazione    
 * @param   Array contenente i nodi d'interpolazione
 * @param   Array contenente i coefficienti di Chebyshev
 * @param   Estremo inferiore dell'intervallo
 * @param   Estremo superiore dell'intervallo
 * @param   Il grado del polinomio
 * @param   Il numero in cui suddividere l'intervallo 
 * @return  Array contenente i valori di valutazione del polinomio 
 */ 
double* chebyshev_polyval(double *x_value, double *coefficients, double lower_bound, double upper_bound, int grade, int steps){

    double *y = (double *) malloc(steps * sizeof(double)), *result = (double *) malloc(steps * sizeof(double));
    if(y == NULL || result == NULL){
        perror("Errore nell'allocazione della memoria\n");
        abort();
    }
    
    for (i = 0; i < steps; i++)
        y[i] = (2 * x_value[i] - (upper_bound + lower_bound))/(upper_bound - lower_bound);
    
    for (i = 0; i < steps; i++){ 
        for (j = 0; j < grade; j++)
            result[i] += coefficients[j] * cos(j * acos(y[i]));
    }

    for(i = 0; i < steps; i++) result[i] = result[i] - 0.5 * coefficients[0];

    free(y);

    return result;
}

/**
 * @brief   Funzione per plottare graficamente la funzione reale e interpolata
 * @param   Array contenete le ascisse della funzione
 * @param   Array contenete le ordinate della funzione
 * @param   Array contenente i valori di interpolazione
 * @param   Array contenente i valori d'errore di interpolazione
 * @param   Il grado del polinomio
 * @param   Il numero di comandi per utilizzare gnuplot
 */ 
void plot_graph_chebyshev(double *x_node, double *y_node, double *poly, double *err, int grade, int commands){

    #if defined(unix) || defined(__unix__) || defined(__unix) || defined(__APPLE__) || defined(__MACH__)
        char *gnuplot_commands[] = {"set title \"INTERPOLAZIONE DI ln(x+1) + cos(x-1) TRAMITE POLINOMIO DI CHEBYSHEV\"", "plot 'resources/function.txt' title 'Reale' with lines, 'resources/chebyshev.txt' title 'Interpolata' with lines, 'resources/error_chebyshev.txt' title 'Errore' with lines"};

        FILE *file  = fopen("resources/function.txt", "w");
        FILE *file1 = fopen("resources/chebyshev.txt", "w");
        FILE *file2 = fopen("resources/error_chebyshev.txt", "w");
    #endif
    
    #if defined(_WIN32) || defined(_WIN36)
        char *gnuplot_commands[] = {"set title \"INTERPOLAZIONE DI ln(x+1) + cos(x-1) TRAMITE POLINOMIO DI CHEBYSHEV\"", "plot 'resources\\function.txt' title 'Reale' with lines, 'resources\\chebyshev.txt' title 'Interpolata' with lines, 'resources\\error_chebyshev.txt' title 'Errore' with lines"};

        FILE *file  = fopen("resources\\function.txt", "w");
        FILE *file1 = fopen("resources\\chebyshev.txt", "w");
        FILE *file2 = fopen("resources\\error_chebyshev.txt", "w");
    #endif

    FILE *pipe  = popen("gnuplot -p", "w");

    if(file == NULL || file1 == NULL || file2 == NULL){
        perror("Errore nell'apertura del file!\n");
        abort();
    }

    if(pipe == NULL){
        perror("Errore nella creazione della pipe!\n");
        abort();
    }

    for(i = 0; i < grade; i++)  fprintf(file, "%.4f %.4f\n", x_node[i], y_node[i]);
    for(i = 0; i < grade; i++)   fprintf(file1, "%.4f %.4f\n", x_node[i], poly[i]);
    for(i = 0; i < grade; i++)   fprintf(file2, "%.4f %.4f\n", x_node[i], err[i]);

    fclose(file);
    fclose(file1);
    fclose(file2);

    for (i = 0; i < commands; i++) fprintf(pipe, "%s \n", gnuplot_commands[i]);

    pclose(pipe);

}
