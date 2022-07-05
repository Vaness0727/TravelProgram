#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXSIZE 10
#define FINITY 100000

void printDistance();
float calcDistance(float, float, float, float);

int x[MAXSIZE] = {0,1,2,3,4,5,6,7,8,9};
int num;
float location[MAXSIZE][2], distance[MAXSIZE][MAXSIZE];
float bestc = FINITY;
float cc = 0;
int bestx[MAXSIZE];


void getLocation()
{
    printf("Please enter the numbers of location : ");
    scanf("%d", &num);

    printf("\nPlease enter the longitude and latitude for each location : \n");

    for(int i = 0; i < num; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            scanf("%f", &location[i][j]);
        }
        printf("\n");
    }

    printDistance();
}

void printDistance()
{
    for(int i = 1; i <= num; i++)
    {
       for(int j = 1; j <= num; j++)
       {
           if(i == j) distance[i][j] = 0;
           else if(i > j) distance[i][j] = distance[j][i];
           else
           {
                distance[i][j] = calcDistance(location[i-1][0], location[i-1][1], location[j-1][0], location[j-1][1]);
           }
       }
    }

    printf("\nDistance between each two location is : \n\n");

    for(int i = 1; i <= num; i++)
    {
       for(int j = 1; j <= num; j++)
       {
           printf("%lf\t", distance[i][j]);
       }
       printf("\n");
    }

    for(int i = 1; i <= num; i++)
    {
       for(int j = 1; j <= num; j++)
       {
           if(i == j) distance[i][j] = FINITY;
       }
    }
}

float calcDistance(float lat1, float lon1, float lat2, float lon2)
{
    float dLat, dLon, a, c, distance;
    dLat = (lat2 - lat1) / 57.295779513082325;
    dLon = (lon2 - lon1) / 57.295779513082325;
    a = sin(dLat/2) * sin(dLat/2) + cos(lat1 / 57.295779513082325) * cos(lat2 / 57.295779513082325) * sin(dLon/2) * sin(dLon/2);
    c = 2 * atan2(sqrt(a),sqrt(1-a));
    distance = 6371 * c;
    return distance;
}

void swap(int t, int i)
{
    int temp;
    temp = x[t];
    x[t] = x[i];
    x[i] = temp;
}

void backtrack(int i)
{
    int j, k;
    if(i == num)
    {
        if(distance[x[num-1]][x[num]] != FINITY && distance[x[num]][x[1]] != FINITY && (cc + distance[x[num-1]][x[num]] + distance[x[num]][x[1]] <= bestc || bestc == FINITY))
        {
            for(j = 1; j <= num; j++)
            {
                bestx[j] = x[j];
            }

            bestc = cc + distance[x[num-1]][x[num]] + distance[x[num]][x[1]];

        }
    }
    else
    {
        for( j = i; j <= num; j++)
        {
            if(distance[x[i-1]][x[j]] != FINITY && (cc + distance[x[i-1]][x[j]] < bestc || bestc == FINITY))
            {
                swap(i, j);
                cc += distance[x[i-1]][x[i]];
                backtrack(i+1);
                cc -= distance[x[i-1]][x[i]];
                swap(i, j);
            }
        }
    }
}

int main()
{
    getLocation();

    backtrack(2);

    printf("\nBest path is : ");
    for(int i = 1; i <= num; i++)
    {
        printf("%d-->", bestx[i]);
    }
    printf("%-5d", bestx[1]);
    printf("\n\nTotal distance : %f\n", bestc);

    system("pause");
    return 0;
}