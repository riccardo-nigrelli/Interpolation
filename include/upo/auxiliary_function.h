#ifndef AUXILIARY_FUNCTION_H

double* divide_interval(double lower, double higher, double step);
double calculate_value_function(double x_node);
double* interpolation_error(double *x_val, double *result, int grade);
void print_comparison_graph(double *x_node, double *y_node, double *poly_lagrange, double *poly_chebyshev, int grade, int commands);

#endif /* AUXILIARY_FUNCTION_H */
