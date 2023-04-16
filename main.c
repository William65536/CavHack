#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* This C code is super terrible */

// 1849-01-01,26.704,1.435,Abidjan,Côte D'Ivoire,5.63N,3.23W

int main(void)
{
    FILE *file = fopen("data\\GlobalLandTemperaturesByMajorCity.csv", "rb");
    assert(file != NULL);

    while (fgetc(file) != '\n');

    struct {
        int year;
        int month;
        double temp;
        char city[100];
        double lat;
        double lng;
    } bruh;

    int throwaway1;
    double throwaway2;
    char throwaway3[100];

    fscanf(file, "%d-%d-%d,%lg,%lg,%[A-z' ]s",
        &bruh.year,
        &bruh.month,
        &throwaway1,
        &bruh.temp,
        &throwaway2,
        bruh.city);
    fscanf(file, ",%[A-z' ]s", throwaway3);
    fscanf(file, ",%lgN", &bruh.lat);
    fscanf(file, ",%lgW", &bruh.lng);

    printf("{ year = %d, month = %d, temp = %lg, city = %s, lat = %lg, lng = %lg }",
        bruh.year,
        bruh.month,
        bruh.temp,
        bruh.city,
        bruh.lat,
        bruh.lng);

    fclose(file);

    return 0;
}
