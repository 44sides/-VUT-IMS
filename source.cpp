#include<stdio.h>
#include<stdlib.h> /* srand, rand*/
#include<math.h>
#include<iostream>
#include<ctype.h>
#include<string.h>
#include <time.h>

//passenger cars only (in France)
/*
T = 95 g/km for 2020-2024. 80,75 g/km for 2025-2029. 42,75 g/km for 2030
a = 0.0333 for 2020-2030
M = rand(1291, 1342)
M0 is 1 379,88 in 2020-2021 and 1 398,50 in 2022, 2023 and 2024-2030
*/

/*
Average CO2 emissions from cars in France = 98.5
*/

//Emissions Target = T + a × (M - M0)
float EmTarg(int year){
    float ET; // Specific Emissions
    float T; // CO2 emission target
    float a; // coefficient
    float M; // average mass of the cars in France
    float M0; // average vehicle mass
    srand(time(NULL));

    switch(year) {
  case 2020:
  case 2021:
    T = 95;
    a = 0.0333;
    M = rand()%51 + 1291;
    M0 = 1379.88;
    break;
  case 2022:
  case 2023:
  case 2024:
    T = 95;
    a = 0.0333;
    M = rand()%51 + 1291;
    M0 = 1398.5;
    break;
  case 2025:
  case 2026:
  case 2027:
  case 2028:
  case 2029:
    T = 80.75;
    a = 0.0333;
    M = rand()%51 + 1291;
    M0 = 1398.5;
    break;
  case 2030:
    T = 42.75;
    a = 0.0333;
    M = rand()%51 + 1291;
    M0 = 1398.5;
    break; 
  default:
    ET = 0;
}
    ET = T + a * (M - M0);
    return ET;
}

int main(int argc, char *argv[])
{
    float ET = EmTarg(2030);

    printf("%f",ET);
}