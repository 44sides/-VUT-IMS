#include<stdio.h>
#include<stdlib.h> /* srand, rand*/
#include<math.h>
#include<iostream>
#include<ctype.h>
#include<string>
#include <string.h> 
#include<time.h>
using namespace std;

//passenger cars only (in France)
/*
T = 95 g/km for 2021. 80,75 g/km for 2025. 42,75 g/km for 2030, 0 g/km for 2035 ( MILESTONES )
a = 0.0333 for 2020-2024. 0.0214 for 2025-2030(95% forecast).
M = rand(1300, 1400)
M0 is 1 379,88 in 2020-2021 and 1 398,50 in 2022, 2023 and 2024-2030
*/

/*
Average CO2 emissions from new cars in France = 98.47 g/km (2020) = avgE
Travelled distance for a year = 12223-13802 km (2000-2019) = distance
*/

float parkreduction = 0.93; // 7% of end-of-life cars every year

//Emissions Target = T + a × (M - M0)
float EmTarg(int year){
    float ET; // Specific Emissions
    float T; // CO2 emission target
    float a; // coefficient
    float M; // average mass of the cars in France
    float M0; // average vehicle mass

    switch(year) {
  case 2020:
  case 2021:
    T = 95;
    a = 0.0333;
    M = rand()%100 + 1300; // France
    M0 = 1379.88;
    break;
  case 2024:
    T = 95;
    a = 0.0333;
    M = rand()%100 + 1300;
    M0 = 1398.5;
    break;
  case 2025:
    T = 80.75;
    a = 0.0214;
    M = rand()%100 + 1300;
    M0 = 1398.5;
    break;
  case 2030:
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

void print(int year, float avgE, float start_ET, float distance){
    float ET = EmTarg(year);

    printf("ET - ET reduction (new cars)\n");
    printf("%d: %f - %f%\n", year, ET, (1-(ET/start_ET))*100);
            
    printf("Min. reduction % - Max. CO2 emissions kg (from new cars)\n");
    printf("%d: %f - %fkg\n\n", year, (1-(ET/avgE))*100, ET*distance/1000);
        
    //printf("g/km - gasoline cost saving %/100km\n");
    //float lper100km = ET/ginl;
    //printf("2035: %fg/km - %f%\n\n", ET, (1-((lper100km*gasprice)/start_gasprice))*100);
}

int main(int argc, char **argv)
{
    float ET;
    int year;
    float start_ET;
    srand(time(NULL));

if(!strcmp(argv[1],"-n")) // -n 'avgE', 'min', 'max'
{
    float avgE = stof(argv[2]);
    printf("%f\n\n",avgE);

    float distance = rand()%(stoi(argv[4])-stoi(argv[3])) + stoi(argv[3]);
    printf("%f\n\n",distance);

    start_ET = EmTarg(2020);

    /* PART ONE */
    // Data relative to 2020 (from new cars)
    for(int i=0;i<4;i++)
    {
        if(i==0)
        {
            print(2021, avgE, start_ET, distance); 
        }
        if(i==1)
        {
            print(2025, avgE, start_ET, distance);
        }
        if(i==2)
        {
            print(2030, avgE, start_ET, distance);
        }
        if(i==3)
        {
            print(2035, avgE, start_ET, distance);
        }
    }
}

if(!strcmp(argv[1],"-g")) // -g 'growth', 'gascars', 'regcars'
{
    /* PART TWO */
    start_ET = EmTarg(2020);

    float ec_growth = stof(argv[2]);
    double total_gascars = stoi(argv[3]);
    float registered_cars = stoi(argv[4]);

    double total_old_gascars = total_gascars;
    double total_registered_gascars = 0;
    float ec_share;
    for(int i=1;i<=30;i++) // till 2050
    {
        year = 2020 + i;

        if(year >= 2021 && year < 2025)
            ET = EmTarg(2021);
        if(year >= 2025 && year < 2030)
            ET = EmTarg(2025);
        if(year >= 2030 && year < 2035)
            ET = EmTarg(2030);
        if(year >= 2035)
            ET = EmTarg(2035);

        ec_share = ec_growth*i;
        if(ec_share > 1)
            ec_share = 1;    

        total_old_gascars = total_old_gascars*parkreduction;
        total_registered_gascars += (1-ec_share)*registered_cars;
        printf("%d: %f\n",i+2020, ((total_old_gascars*start_ET) + (total_registered_gascars*ET))/(total_gascars*start_ET)); // emissions in particular year / start year
    }
}

return 0;
}
