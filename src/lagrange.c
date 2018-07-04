#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int i, j, k;

/**
 * @brief   Funzione per valutare il polinomio nei punti  
 * @param   Array contenente i nodi in cui verrà esecuita l'interpolazione
 * @param   Array contenente i nodi dell'intervallo
 * @param   Array contenente i valori che la funzione assume nei punti dell'intervallo
 * @param   Il grado del polinomio
 * @param   Il numero in cui viene suddiviso 
 * @return  Array contenente i valori di valutazione del polinomio nei vari punti
 */
double* polyval(double *x_val, double *x_node, double *y_node, int grade, int step){ 

    double product, *result = malloc(step * sizeof(double));
    if (result == NULL){
        perror("Errore nell'allocazione della memoria\n");
        abort();
    }

    for (j = 0; j < step; j++){
		result[j] = 0.0;
		for (k = 0; k <= grade; k++){
			product = 1.0;
			for (i = 0; i <= grade; i++){
				if (k != i)
					product *= ((x_val[j] - x_node[i])/(x_node[k] - x_node[i]));
			}
			result[j] += y_node[k] * product;
		}
	}

    return result;
}

/**
 * @brief   Funzione con la quale vado a creare e plottare a runtime i grafici della funzione
 * @param   Array contenente i valori delle ascisse
 * @param   Array contenente i valori delle ordinate
 * @param   Array contenente i valori delle dell'interpolazione
 * @param   Array contenente i valori dell'errore di interpolazione
 * @param   Il grado del polinomio
 * @param   Il numero di comandi che esegue la pipe per gnuplot
 */ 
void plot_graph(double *x_node, double *y_node, double *poly, double *err, int grade, int commands){
    
    char *gnuplot_commands[] = {"set title \"INTERPOLAZIONE DI ln(x+1) + cos(x-1) TRAMITE POLINOMIO DI LAGRANGE\"", "plot 'resources/function.txt' title 'Reale' with lines, 'resources/lagrange.txt' title 'Interpolata' with lines, 'resources/error_lagrange.txt' title 'Errore' with lines"};

    FILE *file  = fopen("resources/function.txt", "w");
    FILE *file1 = fopen("resources/lagrange.txt", "w");
    FILE *file2 = fopen("resources/error_lagrange.txt", "w");
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
