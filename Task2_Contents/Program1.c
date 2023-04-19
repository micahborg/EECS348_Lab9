/*
 *  Program1.c
 *
 *  Created on: 8 Feb 2023
 *  Author: Micah Borghese
 *  Description: This program reads in a file containing monthly sales data for a year and outputs the data in a variety of ways.
 */

#include <stdio.h>
#include <stdlib.h>


float* read_data_from(char *file_name) {
	const int months = 12;
	float* month_sales_data = (float*)malloc(sizeof(float) * months);

	FILE *fp = fopen(file_name, "r+");

	if (fp == NULL) {
		printf("%s", "Please check your file again!\n");
	}

	for (int i = 0; i < months; i++) {
		fscanf(fp, "%f\n", &month_sales_data[i]);
	}

	return month_sales_data;
}

void output_sales_data(char* months[], float *sales) {
	printf("%s", "Monthly Sales Report for 2022:\n");
	printf("%-10s %s\n", "Month", "Sales");
	for (int i = 0; i < 12; i++) {
		printf("%-10s $%.2f\n", months[i], sales[i]);
	}
}

void min_max_avg(char *months[], float *sales) {
    float min = sales[0];
    char *min_month = months[0];
    float max = sales[0];
    char *max_month = months[0];
    float sum = 0;
    float avg = 0;

    for (int i = 0; i < 12; i++) {
        if (sales[i] < min) {
            min = sales[i];
            min_month = months[i];
        }
        if (sales[i] > max) {
            max = sales[i];
            max_month = months[i];
        }
        sum += sales[i];
    }
    avg = sum / 12;

    printf("%s\n", "Sales Summary:");
    printf("%10s $%.2f    (%s)\n", "Minimum Sales:", min, min_month);
    printf("%10s $%.2f    (%s)\n", "Maximum Sales:", max, max_month);
    printf("%10s $%.2f\n", "Average Sales:", avg);
    
}

void six_month_avg(char *months[], float *sales) {
    float sum = 0;
    float avg = 0;

    printf("%s", "Six-Month Moving Average Report:\n");
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 6; j++) {
            sum += sales[i+j];
        }
        avg = sum/6;
        printf("%-10s -  %-10s $%.2f\n", months[i], months[i+5], avg);
        sum = 0;
        avg = 0;
    }
}

void print_sales_descending(char *months[], float *sales) {
    float temp = 0;
    char *temp_month = months[0];

    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            if (sales[i] > sales[j]) {
                temp = sales[i];
                sales[i] = sales[j];
                sales[j] = temp;

                temp_month = months[i];
                months[i] = months[j];
                months[j] = temp_month;
            }
        }
    }

    printf("%s", "Sales Report in Descending Order:\n");
    printf("%-10s %s\n", "Month", "Sales");
    for (int i = 0; i < 12; i++) {
        printf("%-10s $%.2f\n", months[i], sales[i]);
    }

}

int main() {
	float* month_sales_data = read_data_from("sales_input.txt");
	char* month_arr[] = {
				"January",
				"February",
				"March",
				"April",
				"May",
				"June",
				"July",
				"August",
				"September",
				"October",
				"November",
				"December"
		};

	output_sales_data(month_arr, month_sales_data);
    printf("%s\n", "");

    min_max_avg(month_arr, month_sales_data);
    printf("%s\n", "");

    six_month_avg(month_arr, month_sales_data);
    printf("%s\n", "");

    print_sales_descending(month_arr, month_sales_data);

	return 0;
}