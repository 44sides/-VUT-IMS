#include<stdio.h>
#include<stdlib.h> /* srand, rand*/
#include<math.h>
#include<iostream>
#include<ctype.h>
#include<string.h>
#include<time.h>
using namespace std;

//passenger cars only (in France)
/*
T = 95 g/km for 2021. 80,75 g/km for 2025. 42,75 g/km for 2030, 0 g/km for 2035
a = 0.0333 for 2020-2024. 0.0214 for 2025-2030(95% forecast).
M = rand(1300, 1400)
M0 is 1 379,88 in 2020-2021 and 1 398,50 in 2022, 2023 and 2024-2030
*/

/*
Average CO2 emissions from new cars in France = 113.74 g/km (2019) = avgE
Travelled distance for a year = 12223-13802 km (2000-2019) = distance
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
    M = rand()%100 + 1300;
    M0 = 1379.88;
    break;
  case 2022:
  case 2023:
  case 2024:
    T = 95;
    a = 0.0333;
    M = rand()%100 + 1300;
    M0 = 1398.5;
    break;
  case 2025:
  case 2026:
  case 2027:
  case 2028:
  case 2029:
    T = 80.75;
    a = 0.0214;
    M = rand()%100 + 1300;
    M0 = 1398.5;
    break;
  case 2030:
  case 2031:
  case 2032:
  case 2033:
  case 2034:
    T = 42.75;
    a = 0.0214;
    M = rand()%100 + 1300;
    M0 = 1398.5;
    break; 
  default:
    ET = 0;
    return ET;
}
    ET = T + a * (M - M0);
    return ET;
}

//possible parameters: year,...
int main(int argc, char *argv[])
{
    int year = 2030;

    float avgE = 113.74;
    float distance = rand()%1579 + 12223;

    float ET;
    float reduce;
    //(avgE-EmTarg(year))/(year-2020);

    // year: ET - min. reduction % - max. CO2 emissions kg. Relative to 2019 (from new cars).
    for(int i=0;i<4;i++)
    {
        if(i==0)
        {
            ET = EmTarg(2021);
            reduce = avgE - ET;
            printf("2021: %f - %f - %f\n",ET,(1-(ET/avgE))*100,ET*distance/1000);
        }
        if(i==1)
        {
            ET = EmTarg(2025);
            reduce = avgE - ET;
            printf("2025: %f - %f - %f\n",ET,(1-(ET/avgE))*100,ET*distance/1000);
        }
        if(i==2)
        {
            ET = EmTarg(2030);
            reduce = avgE - ET;
            printf("2030: %f - %f - %f\n",ET,(1-(ET/avgE))*100,ET*distance/1000);
        }
        if(i==3)
        {
            ET = EmTarg(2035);
            reduce = avgE - ET;
            printf("2035: %f - %f - %f\n",ET,(1-(ET/avgE))*100,ET*distance/1000);
        }
    }
}
