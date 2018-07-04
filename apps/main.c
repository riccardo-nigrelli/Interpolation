#include <stdio.h>
#include <stdlib.h>
#include <upo/lagrange.h>
#include <upo/chebyshev.h>
#include <upo/auxiliary_function.h>

#define GRADE 6

#define LOWER_BOUND 0
#define UPPER_BOUND 6
#define STEPS_PLOT 1000
#define COMMANDS 2

#define RESET   "\033[0m"
#define RED     "\033[31m" 
#define BOLD    "\033[1m"

const char *separator = "";

int i, j;
double x_node[GRADE + 1], x_val[GRADE], y_node[GRADE + 1], y_plot[STEPS_PLOT], y_node_chebyshev[GRADE + 1];
double *x_plot, *polynomial, *err, *polynomial_to_plot, *err_to_plot;
double *coefficients_chebyshev, *polynomial_chebyshev, *result_chebyshev, *polynomial_to_plot_chebyshev, *err_to_plot_chebyshev;

void main_menu();
void lagrange_polynomial();
void chebyshev_polynomial();
void comparation_methods();

int main(void){

    unsigned int choice;
    int exit;

    do{

        main_menu();
        scanf("%u", &choice);
        getchar();

        while(choice < 1 || choice > 4){
            printf(BOLD RED "\nERRORE! " RESET);
            printf("Premere invio per riprovare...");
            getchar();
            fflush(stdin); 
            main_menu();
            scanf("%u", &choice);
            getchar();
        }

        switch(choice){
            case 1:
                lagrange_polynomial();
                plot_graph(x_plot, y_plot, polynomial_to_plot, err_to_plot, STEPS_PLOT, COMMANDS); 
                scanf("%u", &choice);
                getchar();

                while(choice < 1 || choice > 2){
                    printf(BOLD RED "\nERRORE! " RESET);
                    printf("Premere invio per riprovare...");
                    getchar();
                    fflush(stdin);
                    lagrange_polynomial();
                    scanf("%u", &choice);
                    getchar();

                    free(x_plot);
                    free(polynomial);
                    free(err);
                    free(polynomial_to_plot);
                    free(err_to_plot);
                }
                
                switch(choice){
                    case 1:
                        exit = 2;
                        free(x_plot);
                        free(polynomial);
                        free(err);
                        free(polynomial_to_plot);
                        free(err_to_plot);
                        break;
                    case 2:
                        exit = 1;
                        free(x_plot);
                        free(polynomial);
                        free(err);
                        free(polynomial_to_plot);
                        free(err_to_plot);
                        break;
                }

                break;
                
            case 2:
                chebyshev_polynomial();
                /*plot_graph_chebyshev(x_plot, y_plot, polynomial_to_plot, err_to_plot, STEPS_PLOT, COMMANDS); */
                scanf("%u", &choice);
                getchar();

                while(choice < 1 || choice > 2){
                    printf(BOLD RED "\nERRORE! " RESET);
                    printf("Premere invio per riprovare...");
                    getchar();
                    fflush(stdin);
                    chebyshev_polynomial();
                    scanf("%u", &choice);
                    getchar();

                    free(x_plot);
                    free(polynomial_to_plot_chebyshev);
                    free(err_to_plot_chebyshev);
                    free(coefficients_chebyshev);
                    free(polynomial_chebyshev);
                    free(result_chebyshev);
                }
                
                switch(choice){
                    case 1:
                        exit = 2;

                        free(x_plot);
                        free(polynomial_to_plot_chebyshev);
                        free(err_to_plot_chebyshev);
                        free(coefficients_chebyshev);
                        free(polynomial_chebyshev);
                        free(result_chebyshev);
                        break;
                    case 2:
                        exit = 1;

                        free(x_plot);
                        free(polynomial_to_plot_chebyshev);
                        free(err_to_plot_chebyshev);
                        free(coefficients_chebyshev);
                        free(polynomial_chebyshev);
                        free(result_chebyshev);
                        break;
                }

                break;

            case 3:
                comparation_methods();
                scanf("%u", &choice);
                getchar();

                while(choice < 1 || choice > 2){
                    printf(BOLD RED "\nERRORE! " RESET);
                    printf("Premere invio per riprovare...");
                    getchar();
                    fflush(stdin);
                    comparation_methods();
                    scanf("%u", &choice);
                    getchar();

                    free(x_plot);
                    free(polynomial);
                    free(err);
                    free(polynomial_to_plot);
                    free(err_to_plot);
                    free(coefficients_chebyshev);
                    free(polynomial_chebyshev);
                    free(result_chebyshev);
                }

                switch(choice){
                    case 1:
                        exit = 2;

                        free(x_plot);
                        free(polynomial);
                        free(err);
                        free(polynomial_to_plot);
                        free(err_to_plot);
                        free(coefficients_chebyshev);
                        free(polynomial_chebyshev);
                        free(result_chebyshev);
                        break;
                    case 2:
                        exit = 1;

                        free(x_plot);
                        free(polynomial);
                        free(err);
                        free(polynomial_to_plot);
                        free(err_to_plot);
                        free(coefficients_chebyshev);
                        free(polynomial_chebyshev);
                        free(result_chebyshev);
                        break;
                }

                break;

            case 4:
                exit = 1;
                break;
        }

    }while(exit != 1);

    return 0;
}

/**
 * @brief Funzione che utilizzo per la stampa del menù
 */
void main_menu(){

    #if defined(unix) || defined(__unix__) || defined(__unix) || defined(__APPLE__) || defined(__MACH__)
        system("clear");
    #endif
    
    #if defined(_WIN32) || defined(_WIN36)
        system("cls");
    #endif
    
    printf("PROGRAMMA PER L'INTERPOLAZIONE DELLA FUNZIONE ln(x + 1) + cos(x - 1)\n\n");

    printf("1) Interpolazione tramite polinomio di Lagrange\n");
    printf("2) Interpolazione tramite polinomio di Chebyshev\n");
    printf("3) Confronto tra i due metodi di interpolazione\n");
    printf("4) Esci\n\n");

    printf("La mia scelta e' la numero: ");
}

/**
 * @brief Funzione con la quale vado a stampare i risultati ottenuti con il metodo di Lagrange 
 */
void lagrange_polynomial(){


    #if defined(unix) || defined(__unix__) || defined(__unix) || defined(__APPLE__) || defined(__MACH__)
        system("clear");
    #endif
    
    #if defined(_WIN32) || defined(_WIN36)
        system("cls");
    #endif
    
    printf("\nINTERPOLAZIONE CON IL POLINOMIO DI LAGRANGE\n\n");

    printf("X_NODE     [");
    for(i = 0; i <= GRADE; i++){
        x_node[i] = i;
        printf("%s%.4f", separator, x_node[i]);
        separator = ", ";
    }
    printf("]\n");


    for(i = 0; i <= GRADE; i++) y_node[i] = calculate_value_function(i);
    
    separator = "";
    printf("X_VALUE    [");
	for(i = 0; i < GRADE; i++){
		x_val[i] = (x_node[i] + x_node[i + 1]) / 2;
		printf("%s%.4f", separator, x_val[i]);
        separator = ", ";
	}
	printf("]\n");


    separator = "";
    printf("Y_VALUE    [");
	for(i = 0; i < GRADE; i++){
		printf("%s%.4f", separator, calculate_value_function(x_val[i]));
        separator = ", ";
	}
	printf("]\n");

    polynomial = polyval(x_val, x_node, y_node, GRADE, GRADE);

    separator = "";
    printf("POLYNOMIAL [");
	for(i = 0; i < GRADE; i++){
		printf("%s%.4f", separator, polynomial[i]);
        separator = ", ";
    }
	printf("]\n");

    err = interpolation_error(x_val, polynomial, GRADE);

    separator = "";
    printf("ERROR      [");
	for(i = 0; i < GRADE; i++){
		printf("%s%.4f", separator, err[i]);
        separator = ", ";
    }
	printf("]\n");

    /* Per plottare espando l'intervallo [0, 6] in 1000 parti uguali */
    x_plot = divide_interval(LOWER_BOUND, UPPER_BOUND, STEPS_PLOT);

    for(i = 0; i < STEPS_PLOT; i++) y_plot[i] = calculate_value_function(x_plot[i]);
    
    polynomial_to_plot = polyval(x_plot, x_node, y_node, GRADE, STEPS_PLOT); 
    err_to_plot = interpolation_error(x_plot, polynomial_to_plot, STEPS_PLOT);

    printf("\n1) Torna al menu' precedente\n");
    printf("2) Esci\n\n");

    printf("La mia scelta e' la numero: ");
} 

void chebyshev_polynomial(){

    #if defined(unix) || defined(__unix__) || defined(__unix) || defined(__APPLE__) || defined(__MACH__)
        system("clear");
    #endif
    
    #if defined(_WIN32) || defined(_WIN36)
        system("cls");
    #endif
    
    printf("\nINTERPOLAZIONE CON IL POLINOMIO DI CHEBYSHEV\n\n");

    separator = "";
    printf("X_NODE       [");
    for(i = 0; i <= GRADE; i++){
        x_node[i] = i;
        printf("%s%.4f", separator, x_node[i]);
        separator = ", ";
    }
    printf("]\n");    
    
    separator = "";
    printf("X_VALUE      [");
	for(i = 0; i < GRADE; i++){
		x_val[i] = (x_node[i] + x_node[i + 1]) / 2;
		printf("%s%.4f", separator, x_val[i]);
        separator = ", ";
	}
	printf("]\n");

    separator = "";
    printf("Y_VALUE      [");
	for(i = 0; i < GRADE; i++){
		printf("%s%.4f", separator, calculate_value_function(x_val[i]));
        separator = ", ";
	}
	printf("]\n");

    
    coefficients_chebyshev = chebyshev_coefficients(calculate_value_function, LOWER_BOUND, UPPER_BOUND, GRADE);

    separator = "";
    printf("COEFFICIENTS [");
    for(i = 0; i < GRADE; i++){
        printf("%s%.4f", separator, coefficients_chebyshev[i]);
        separator = ", ";
    }
    printf("]\n");
    
    result_chebyshev = chebyshev_polyval(x_val, coefficients_chebyshev, LOWER_BOUND, UPPER_BOUND, GRADE, GRADE);
    
    separator = "";
    printf("POLYNOMIAL   [");
    for(i = 0; i < GRADE; i++){
        printf(" %f", result_chebyshev[i]);
        separator = ", ";
    }
	printf("]\n"); 

    
    err = interpolation_error(x_val, result_chebyshev, GRADE);

    separator = "";
    printf("ERROR        [");
	for(i = 0; i < GRADE; i++){
		printf("%s%.4f", separator, err[i]);
        separator = ", ";
    }
	printf("]\n");

    /* Per plottare espando l'intervallo [0, 6] in 1000 parti uguali */
    x_plot = divide_interval(LOWER_BOUND, UPPER_BOUND, STEPS_PLOT);

    for(i = 0; i < STEPS_PLOT; i++) y_plot[i] = calculate_value_function(x_plot[i]);
    
    polynomial_to_plot_chebyshev = chebyshev_polyval(x_plot, coefficients_chebyshev, LOWER_BOUND, UPPER_BOUND, GRADE, STEPS_PLOT); 
    err_to_plot_chebyshev = interpolation_error(x_plot, polynomial_to_plot, STEPS_PLOT);

    
    printf("\n1) Torna al menu' precedente\n");
    printf("2) Esci\n\n");

    printf("La mia scelta e' la numero: ");
} 

void comparation_methods(){

    #if defined(unix) || defined(__unix__) || defined(__unix) || defined(__APPLE__) || defined(__MACH__)
        system("clear");
    #endif
    
    #if defined(_WIN32) || defined(_WIN36)
        system("cls");
    #endif
    
    printf("\nCONFRONTE DEI DUE METODI DI INTERPOLAZIONE\n\n");    

    printf("- Polinomio di Lagrange: \n\n");

    for(i = 0; i <= GRADE; i++){
        x_node[i] = i;
        y_node[i] = calculate_value_function(i);    
    }

	for(i = 0; i < GRADE; i++) x_val[i] = (x_node[i] + x_node[i + 1]) / 2;
    
    polynomial = polyval(x_val, x_node, y_node, GRADE, GRADE);
    err = interpolation_error(x_val, polynomial, GRADE);

    separator = "";
    printf("  Y_VALUE    [");
	for(i = 0; i < GRADE; i++){
		printf("%s%.4f", separator, calculate_value_function(x_val[i]));
        separator = ", ";
	}
	printf("]\n");

    separator = "";
    printf("  POLYNOMIAL [");
	for(i = 0; i < GRADE; i++){
		printf("%s%.4f", separator, polynomial[i]);
        separator = ", ";
    }
	printf("]\n");

    separator = "";
    printf("  ERROR      [");
	for(i = 0; i < GRADE; i++){
		printf("%s%.4f", separator, err[i]);
        separator = ", ";
    }
	printf("]\n\n\n");

    printf("- Polinomio di Chebyshev: \n\n");

    coefficients_chebyshev = chebyshev_coefficients(calculate_value_function, LOWER_BOUND, UPPER_BOUND, GRADE);
    result_chebyshev = chebyshev_polyval(x_val, coefficients_chebyshev, LOWER_BOUND, UPPER_BOUND, GRADE, GRADE);
    err = interpolation_error(x_val, result_chebyshev, GRADE);

    separator = "";
    printf("  Y_VALUE    [");
	for(i = 0; i < GRADE; i++){
		printf("%s%.4f", separator, calculate_value_function(x_val[i]));
        separator = ", ";
	}
	printf("]\n");

    separator = "";
    printf("  POLYNOMIAL [");
    for(i = 0; i < GRADE; i++){
        printf("%s%.4f", separator, result_chebyshev[i]);
        separator = ", ";
    }
	printf("]\n");

    separator = "";
    printf("  ERROR      [");
	for(i = 0; i < GRADE; i++){
		printf("%s%.4f", separator, err[i]);
        separator = ", ";
    }
	printf("]\n");


    /* Ora vado ad espandare l'intervallo e plotto i due metodi di interpolazione */
    x_plot = divide_interval(LOWER_BOUND, UPPER_BOUND, STEPS_PLOT);

    for(i = 0; i < STEPS_PLOT; i++) y_plot[i] = calculate_value_function(x_plot[i]);


    polynomial_to_plot = polyval(x_plot, x_node, y_node, GRADE, STEPS_PLOT); 
    polynomial_to_plot_chebyshev = chebyshev_polyval(x_plot, coefficients_chebyshev, LOWER_BOUND, UPPER_BOUND, GRADE, STEPS_PLOT); 

    print_comparison_graph(x_plot, y_plot, polynomial_to_plot, polynomial_to_plot_chebyshev, STEPS_PLOT, COMMANDS);

    printf("\n1) Torna al menu' precedente\n");
    printf("2) Esci\n\n");

    printf("La mia scelta e' la numero: ");
}
