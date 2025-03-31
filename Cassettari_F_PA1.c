/*

I Fiore Cassettari here certify that this programming assignment reflects my own work,
without the use of any external individuals (other than course/department staff ), generative-AI,
or any other forbidden resources. I understand/accept the consequences of cheating as outlined
in the course syllabus.

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 100

float mean(float arr[], int size) {
    float sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return roundf((sum / size) * 1000) / 1000;
}

float median(float arr[], int size) {

    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        float temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }

    if (size % 2 == 1) {
        return roundf(arr[size / 2] * 1000) / 1000;
    } else {
        return roundf(((arr[size / 2 - 1] + arr[size / 2]) / 2) * 1000) / 1000;
    }
}

float mode(float arr[], int size) {
    float maxValue = -1;
    int maxCount = 0;

    for (int i = 0; i < size; i++) {
        int count = 1;
        for (int j = i + 1; j < size; j++) {
            if (arr[i] == arr[j]) {
                count++;
            }
        }
        if (count > maxCount) {
            maxCount = count;
            maxValue = arr[i];
        }
    }

    if (maxCount > 1) {
        return maxValue;
    } else {
        return -1;
    }
}

char* ascii(float arr[], int size) {
    static char asciiArr[MAX_SIZE];

    int* roundedArr = rounded_vals(arr, size);

    for (int i = 0; i < size; i++) {
        if (roundedArr[i] >= 32 && roundedArr[i] <= 126) {
            asciiArr[i] = (char)roundedArr[i];
        } else {
            asciiArr[i] = '*';
        }
    }
    asciiArr[size] = '\0';

    return asciiArr;
}

float std_dev(float arr[], int size) {
    float m = mean(arr, size);
    float sumSq = 0.0;

    for (int i = 0; i < size; i++) {
        sumSq += pow(arr[i] - m, 2);
    }

    return roundf(sqrt(sumSq / (size - 1)) * 1000) / 1000;
}

int* rounded_vals(float arr[], int size) {
    static int roundedArr[MAX_SIZE];

    for (int i = 0; i < size; i++) {
        roundedArr[i] = roundf(arr[i]);
    }

    return roundedArr;
}

void print_results(float mean, float median, float mode, float std_dev, int* rounded, char* ascii, int size) {
    printf("Mean: %.3f\n", mean);
    printf("Median: %.3f\n", median);
    printf("Mode: %.3f\n", mode);
    printf("Standard Deviation: %.3f\n", std_dev);

    printf("Rounded: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", rounded[i]);
    }
    printf("\n");

    printf("ASCII: %s\n", ascii);
}

int main(int argc, char* argv[]) {
    int size = argc - 1;


    float arr[MAX_SIZE];

    for (int i = 0; i < size; i++) {
        arr[i] = atof(argv[i + 1]);
    }

    float mean_val = mean(arr, size);
    float median_val = median(arr, size);
    float mode_val = mode(arr, size);
    float std_dev_val = std_dev(arr, size);
    int* rounded = rounded_vals(arr, size);
    char* asciiValues = ascii(arr, size);

    print_results(mean_val, median_val, mode_val, std_dev_val, rounded, asciiValues, size);

    return 0;
}
