#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double *linear_func(int a, int b, const double *values, int size) {
    double *output = (double *)malloc(size * sizeof(double));
    for (int i = 0; i < size; i++) {
        output[i] = a * values[i] + b;
    }
    return output;
}

double *quadratic_func(int a, int b, const double *values, int size) {
    double *output = (double *)malloc(size * sizeof(double));
    for (int i = 0; i < size; i++) {
        output[i] = values[i] * values[i] + a * values[i] + b;
    }
    return output;
}

double *exp_func(int a, int b, const double *values, int size) {
    double *output = (double *)malloc(size * sizeof(double));
    for (int i = 0; i < size; i++) {
        output[i] = exp(a * values[i]);
    }
    return output;
}

double *sin_func(int a, int b, const double *values, int size) {
    double *output = (double *)malloc(size * sizeof(double));
    for (int i = 0; i < size; i++) {
        output[i] = a * sin(b * values[i]);
    }
    return output;
}

double *func_derivative(const char *func, double *val_plus, double *val, double *val_minus, int a, int b, int order, double h, int size) {
    double *output = (double *)malloc(size * sizeof(double));

    double *(*selected)(int, int, const double *, int) = NULL;
    //string comparison to choose function
    if (func[0] == 'l' && func[1] == 'i' && func[2] == 'n' && func[3] == '\0') {
        selected = linear_func;
    } else if (func[0] == 'q' && func[1] == 'u' && func[2] == 'a' && func[3] == 'd' && func[4] == '\0') {
        selected = quadratic_func;
    } else if (func[0] == 'e' && func[1] == 'x' && func[2] == 'p' && func[3] == '\0') {
        selected = exp_func;
    } else if (func[0] == 's' && func[1] == 'i' && func[2] == 'n' && func[3] == '\0') {
        selected = sin_func;
    } else {
        free(output); //if we get here, you put in a bad string.
    }

    double *x_plus_h = selected(a, b, val_plus, size);
    double *at_x = selected(a, b, val, size);
    double *x_minus_h = NULL;

    if (order == 2) {
        x_minus_h = selected(a, b, val_minus, size);
    }

    switch (order) {
        case 0:
            for (int i = 0; i < size; i++)
                output[i] = at_x[i];
            break;
        case 1:
            for (int i = 0; i < size; i++)
                output[i] = (x_plus_h[i] - at_x[i]) / h;
            break;
        case 2:
            for (int i = 0; i < size; i++)
                output[i] = (x_plus_h[i] - 2 * at_x[i] + x_minus_h[i]) / (h * h);
            break;
        default:
            for (int i = 0; i < size; i++)
                output[i] = 3.14159; //base case
    }

    free(x_plus_h);
    free(at_x);
    if (x_minus_h != NULL) free(x_minus_h); //free it if it exists

    return output;
}

int main(int argc, char *argv[]) {
    
    int size = argc - 2; //size of the array of floats
    double h = atof(argv[argc - 1]); 
    //reserving memory
    double *values = (double *)malloc(size * sizeof(double));
    double *values_plus = (double *)malloc(size * sizeof(double));
    double *values_minus = (double *)malloc(size * sizeof(double));
    
    for (int i = 0; i < size; i++) {
        values[i] = atof(argv[i + 1]);
        values_plus[i] = values[i] + h;
        values_minus[i] = values[i] - h;
    }
    
    //Insert thy test code.
    
    //freeing memory
    free(values);
    free(values_plus);
    free(values_minus);
    
    return 0;
}