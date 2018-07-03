#ifndef CHEBYSHEV_H

double* chebyshev_coefficients(double function(double), double lower_bound, double upper_bound, int grade);
double* chebyshev_polyval(double *x_value, double *coefficients, double lower_bound, double upper_bound, int grade, int steps);
void plot_graph_chebyshev(double *x_node, double *y_node, double *poly, double *err, int grade, int commands);

#endif /* CHEBYSHEV_H */
