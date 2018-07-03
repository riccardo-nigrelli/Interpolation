#ifndef LAGRANGE_H

double* polyval(double *x_val, double *x_node, double *y_node, int grade, int step);
void plot_graph(double *x_node, double *y_node, double *poly, double *err, int grade, int commands);

#endif /* LAGRANGE_H */
