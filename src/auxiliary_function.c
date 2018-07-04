#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int i;

/**
 * @brief   Funzione con la quale si divide l'intervallo in parti uguali
 * @param   Estremo inferiore dell'intervallo
 * @param   Estremo superiore dell'intervallo
 * @param   Numero in cui dividere l'intervallo
 * @return  Array contenente i valori dell'intervallo suddiviso
 */
double* divide_interval(double lower, double higher, double step){
    
    double *x_plot = (double *) malloc(step * sizeof(double));
    double j, n;

    if (x_plot == NULL){
        perror("Errore nell'allocazione della memoria\n");
        abort();
    }

    n = (higher - lower) / (step - 1);
    for (i = 0, j = 0; i < step; i++, j += n) x_plot[i] = j;
    x_plot[(int)step - 1] = higher;

    return x_plot;
}

/**
 * @brief   Funzione per calcolare il valore che assume la funzione in un punto 
 * @param   Ascissa del punto di cui si vuole conosce l'ordinata 
 * @return  Il valore della funzione nel punto
 */
double calculate_value_function(double x_node){
    return log(x_node + 1) + cos(x_node - 1);
}

/**
 * @brief   Funzione per il calcolo dell'errore di interpolazione
 * @param   Array contenente i nodi di interpolazione
 * @param   Array contenente i valori dell'interpolazione
 * @param   Grado del polinomio
 * @return  Array contenente gli errori di interpolazione nei vari nodi
 */ 
double* interpolation_error(double *x_val, double *result, int grade){

	double *error = malloc(grade * sizeof(double));

	for (i = 0; i < grade; i++)
		error[i] = fabs(((log(x_val[i] + 1)) + cos(x_val[i] - 1)) - result[i]);

	return error;
}

void print_comparison_graph(double *x_node, double *y_node, double *poly_lagrange, double *poly_chebyshev, int grade, int commands){
    
    char *gnuplot_commands[] = {"set title \"INTERPOLAZIONE DI ln(x+1) + cos(x-1) TRAMITE POLINOMIO DI CHEBYSHEV\"", "plot 'resources/function.txt' title 'Reale' with lines, 'resources/chebyshev.txt' title 'Chebyshev' with lines, 'resources/lagrange.txt' title 'Lagrange' with lines"};

    FILE *file  = fopen("resources/function.txt", "w");
    FILE *file1 = fopen("resources/chebyshev.txt", "w");
    FILE *file2 = fopen("resources/lagrange.txt", "w");
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
    for(i = 0; i < grade; i++)   fprintf(file1, "%.4f %.4f\n", x_node[i], poly_lagrange[i]);
    for(i = 0; i < grade; i++)   fprintf(file2, "%.4f %.4f\n", x_node[i], poly_chebyshev[i]);

    fclose(file);
    fclose(file1);
    fclose(file2);

    for (i = 0; i < commands; i++) fprintf(pipe, "%s \n", gnuplot_commands[i]);

    pclose(pipe);

}
