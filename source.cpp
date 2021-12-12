#include<stdio.h>
#include<stdlib.h> /* srand, rand*/
#include<math.h>
#include<iostream>
#include<ctype.h>
#include<string>
#include <string.h> 
#include<time.h>
using namespace std;

float parkreduction = 0.93; // 7% of end-of-life cars every year

//Emissions Target = T + a × (M - M0)
float EmTarg(int year, int minM, int maxM, short scenario){ // scenario: 1-paris agr, 2-green deal 
    float ET; // Specific Emissions
    float T; // CO2 emission target
    float a; // coefficient
    float M; // average mass of the cars
    float M0; // average vehicle mass
    srand(time(NULL));

    switch(year) {
  case 2020:
  case 2021:
    T = 95;
    a = 0.0333;
    M = rand()%(maxM-minM) + minM;
    M0 = 1379.88;
    break;
  case 2024:
    T = 95;
    a = 0.0333;
    M = rand()%(maxM-minM) + minM;
    M0 = 1398.5;
    break;
  case 2025:
    T = 80.75;
    a = 0.0214;
    M = rand()%(maxM-minM) + minM;
    M0 = 1398.5;
    break;
  case 2030:
    if(scenario == 2)
        T = 42.75;
    else
        T = 59.4;
    a = 0.0214;
    M = rand()%(maxM-minM) + minM;
    M0 = 1398.5;
    break; 
  default:
    ET = 0;
    return ET;
}
    ET = T + a * (M - M0);
    return ET;
}

void print(int year, float avgE, float start_ET, float distance,int minM, int maxM){
    float ET = EmTarg(year,minM,maxM, 2);

    printf("ET - ET reduction (new cars)\n");
    printf("%d: %f - %f%\n", year, ET, (1-(ET/start_ET))*100);
            
    printf("Min. reduction % - Max. CO2 emissions kg (from new cars)\n");
    printf("%d: %f - %fkg\n", year, (1-(ET/avgE))*100, ET*distance/1000);

    if(year == 2030)
    {
        printf("---------Paris agreement scenario---------\n");
        ET = EmTarg(year,minM,maxM, 1);

        printf("ET - ET reduction (new cars)\n");
        printf("%d: %f - %f%\n", year, ET, (1-(ET/start_ET))*100);
                
        printf("Min. reduction % - Max. CO2 emissions kg (from new cars)\n");
        printf("%d: %f - %fkg\n", year, (1-(ET/avgE))*100, ET*distance/1000);
    }

    printf("\n");
}

int main(int argc, char **argv)
{
    float ET;
    int year;
    float start_ET;

if(!strcmp(argv[1],"-n")) // -n 'avgE', 'minD', 'maxD', 'minM', 'maxM'
{
    srand(time(NULL));
    float avgE = stof(argv[2]);

    float distance = rand()%(stoi(argv[4])-stoi(argv[3])) + stoi(argv[3]);

    start_ET = EmTarg(2020,stoi(argv[5]),stoi(argv[6]), 2);

    /* PART ONE */
    // Data relative to 2020 (from new cars)
    for(int i=0;i<4;i++)
    {
        if(i==0)
        {
            print(2021, avgE, start_ET, distance,stoi(argv[5]),stoi(argv[6])); 
        }
        if(i==1)
        {
            print(2025, avgE, start_ET, distance,stoi(argv[5]),stoi(argv[6]));
        }
        if(i==2)
        {
            print(2030, avgE, start_ET, distance,stoi(argv[5]),stoi(argv[6]));
        }
        if(i==3)
        {
            print(2035, avgE, start_ET, distance,stoi(argv[5]),stoi(argv[6]));
        }
    }
}

if(!strcmp(argv[1],"-g")) // -g 'growth', 'gascars', 'regcars', 'parkreduct', 'minM', 'maxM'
{
    /* PART TWO */
    start_ET = EmTarg(2020,stoi(argv[5]),stoi(argv[6]), 2);

    float ec_growth = stof(argv[2]);
    double total_gascars = stoi(argv[3]);
    float registered_cars = stoi(argv[4]);
    float parkreduct = stof(argv[5]);

    double total_old_gascars = total_gascars;
    double total_registered_gascars = 0;
    float ec_share;
    for(int i=1;i<=30;i++) // till 2050
    {
        year = 2020 + i;

        if(year >= 2021 && year < 2025)
            ET = EmTarg(2021,stoi(argv[5]),stoi(argv[6]), 2);
        if(year >= 2025 && year < 2030)
            ET = EmTarg(2025,stoi(argv[5]),stoi(argv[6]), 2);
        if(year >= 2030 && year < 2035)
            ET = EmTarg(2030,stoi(argv[5]),stoi(argv[6]), 2);
        if(year >= 2035)
            ET = EmTarg(2035,stoi(argv[5]),stoi(argv[6]), 2);

        ec_share = ec_growth*i;
        if(ec_share > 1)
            ec_share = 1;    

        total_old_gascars = total_old_gascars*parkreduct;
        total_registered_gascars += (1-ec_share)*registered_cars;
        printf("%d: %f\n%f\n",i+2020, 1-(((total_old_gascars*start_ET) + (total_registered_gascars*ET))/(total_gascars*start_ET)),ec_share); // emissions in particular year / start year
    }
}

return 0;
}
