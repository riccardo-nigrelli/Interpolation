#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int i, j;

/**
 * @brief   Funzione per calcolare il valore che assume la funzione in un punto 
 * @param   Ascissa del punto di cui si vuole conosce l'ordinata 
 * @return  Il valore della funzione nel punto
 */
double calculate_value_function(double x_node){
    return log(x_node + 1) + cos(x_node - 1);
}

/**
 * @brief   Funzione con la quale si divide l'intervallo in parti uguali
 * @param   Estremo inferiore dell'intervallo
 * @param   Estremo superiore dell'intervallo
 * @param   Numero in cui dividere l'intervallo
 * @return  Array contenente i valori dell'intervallo suddiviso
 */
double* divide_interval(double lower, double higher, double step){
    
    double *x_plot = (double *) malloc((step + 1) * sizeof(double));
    double j, n = (higher - lower) / step;

    if (x_plot == NULL){
        perror("Errore nell'allocazione della memoria\n");
        abort();
    }

    for (i = 0, j = 0; i <= step; i++, j += n) x_plot[i] = j;

    return x_plot;
}

double* polyfit(double function(double), double* x_node, const int grade){

    double product, *sum = (double *) malloc((grade + 1) * sizeof(double));

    if(sum == NULL){
        perror("Errore nell'allocazione della memoria\n");
        abort();
    }

    /*
    for (i = 0; i <= grade; i++) {
        sum[i] = 0.0;
        for (j = 0 ; j <= grade; j++) {
            product = 1.0;
            if (i != j) 
                product *= (function(i) - x_node[j])/(x_node[j] - x_node[i]);
        }
        sum[i] += product * x_node[i];
        
        === PROF ===
        float sum=0., frac=0.;

    } */


    for (i = 0; i <= grade; i++) {
        product = 1.0, sum[i] = 0;

        for (j = 0; j <= grade; j++) {
            if (i != j) 
                product *= (function(i) - x_node[i])/(x_node[j] - x_node[i]);
        }
        sum[i] += product * function(i);
    }

    return sum;
} 