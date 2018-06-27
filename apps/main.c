#include <stdio.h>
#include <stdlib.h>
#include <upo/lagrange.h>

#define GRADE 6

#define LOWER_BOUND 0
#define UPPER_BOUND 6
#define STEPS       1000

#define RESET   "\033[0m"
#define RED     "\033[31m" 
#define BOLD    "\033[1m"

char *separator = "";
/*double x_node_lagrange[GRADE + 1], x_val_lagrange[GRADE], y_node_lagrange[GRADE + 1];
double *poly_lagrange, *err_lagrange; */

int i, j;
double *x_plot, *polynomial;
double x_node[] = {0, 1, 2, 3, 4, 5, 6};

static void main_menu();
static void lagrange_polynomial();
/*static void chebyshev_polynomial(); */

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
            fflush(NULL); 
            main_menu();
            scanf("%u", &choice);
            getchar();
        }

        switch(choice){
            case 1:
                lagrange_polynomial();
                /*write_data_on_file_lagrange(x_node_lagrange, y_node_lagrange, x_val_lagrange, poly_lagrange, err_lagrange); */
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

                    /*free(poly_lagrange);
                    free(err_lagrange);*/
                }
                
                switch(choice){
                    case 1:
                        exit = 2;
                        /*free(poly_lagrange);
                        free(err_lagrange);*/
                        break;
                    case 2:
                        exit = 1;
                        /*free(poly_lagrange);
                        free(err_lagrange);*/
                        break;
                }

                break;
                
            case 2:
                /*chebyshev_polynomial();*/
                scanf("%u", &choice);
                getchar();

                while(choice < 1 || choice > 2){
                    printf(BOLD RED "\nERRORE! " RESET);
                    printf("Premere invio per riprovare...");
                    getchar();
                    fflush(stdin);
                    /*chebyshev_polynomial();*/
                    scanf("%u", &choice);
                    getchar();

                    /*fare la free degli array*/
                }
                
                switch(choice){
                    case 1:
                        exit = 2;
                        /*fare la free degli array*/
                        break;
                    case 2:
                        exit = 1;
                        /*fare la free degli array*/
                        break;
                }

                break;

            case 3:
                system("clear");
                printf("Menu' 3");
                break;

            case 4:
                exit = 1;
                break;
        }

    }while(exit != 1);

    return 0;
}

/**
 * 
 * @brief Funzione che utilizzo per la stampa del menù
 * 
 */
void main_menu(){

    system("clear");
    
    printf("PROGRAMMA PER L'INTERPOLAZIONE DELLA FUNZIONE ln(x + 1) + cos(x - 1)\n\n");

    printf("1) Interpolazione tramite polinomio di Lagrange\n");
    printf("2) Interpolazione tramite polinomio di Chebyshev\n");
    printf("3) Confronto tra i due metodi di interpolazione\n");
    printf("4) Esci\n\n");

    printf("La mia scelta e' la numero: ");
}

/**
 * 
 * @brief Funzione con la quale vado a stampare i risultati ottenuti con il metodo di Lagrange 
 * 
 */
void lagrange_polynomial(){

    system("clear");
    
    printf("\nINTERPOLAZIONE CON IL POLINOMIO DI LAGRANGE\n\n");


    x_plot = divide_interval(LOWER_BOUND, UPPER_BOUND, STEPS);  /*Divido l'intervallo [0-6] in 1000 parti per 
                                                                  avere una buona precisione */
    
    polynomial = polyfit(calculate_value_function, x_node, GRADE);
    for(i = 0; i <= GRADE; i++){
        printf("product[%d] = %.4f\n", i, polynomial[i]);
    }


    /*
    int i;
    
    node_lagrange(x_node_lagrange, y_node_lagrange);
    poly_lagrange = polynomial_lagrange(x_val_lagrange, x_node_lagrange);

    separator = "";
    printf("POLYNOMIAL {");
    for(i = 0; i < GRADE + 1; i++){
        printf("%s%.4f", separator, poly_lagrange[i]);
        separator = ", ";
    }
    printf("}\n");


    

    err_lagrange = error_lagrange(x_val_lagrange, poly_lagrange);

    separator = "";
	printf("ERROR      {");
	for(i = 0; i < GRADE; i++){
        printf("%s%.4f", separator, err_lagrange[i]);
        separator = ", ";
    }
	printf("}\n"); */

    printf("\n1) Torna al menu' precedente\n");
    printf("2) Esci\n\n");

    printf("La mia scelta e' la numero: ");
} 

void chebyshev_polynomial(){

    system("clear");
    
    printf("\nINTERPOLAZIONE CON IL POLINOMIO DI CHEBYSHEV\n\n");

    /*node_succession_lagrange(x_node_lagrange, y_node_lagrange, x_val_lagrange); */
/*
    printf("\n1) Torna al menu' precedente\n");
    printf("2) Esci\n\n");

    printf("La mia scelta e' la numero: ");*/
} 
