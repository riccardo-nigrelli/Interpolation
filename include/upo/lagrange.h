#ifndef LAGRANGE_H
/*#define LAGRANGE_H*/

static double calculate_value_function(double x_node);
static double* divide_interval(double lower, double higher, double step);
static double* polyfit(double function(double), double* x_node, const int grade);

#endif /* LAGRANGE_H */
