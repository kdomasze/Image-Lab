/* rabbit.c				*/
/*					*/
/* author: Kyle Domaszewicz		*/
/* 					*/
/* modifications:			*/
/* 9/28/13	initial version		*/

#include <stdio.h>

/* main function */

int main(void)
{
	/* Variables */
	int wolf_pop = 0;
	int rabbit_pop = 0;
	float grass_area = 0;
	float wolf_growth_rate = 0;
	float rabbit_growth_rate = 0;
	float grass_growth_rate = 0;

	float prev_wolf_pop;
	float prev_rabbit_pop;
	float prev_grass_area;
	int year;

	int year_max_wolf_pop;
	int year_min_wolf_pop;
	int max_wolf_pop = 0;
	int min_wolf_pop = 32767;
	int year_max_rabbit_pop;
	int year_min_rabbit_pop;
	int max_rabbit_pop = 0;
	int min_rabbit_pop = 32767;	

	/* Get user input for the simulation */

	printf("Enter wolf population (initial): ");
	scanf("%d", &wolf_pop);
	printf("Enter rabbit population (initial): ");
	scanf("%d", &rabbit_pop);
	printf("Enter total grass area, initially fertile (in sq yards): ");
	scanf("%f", &grass_area);
	printf("Enter wolf annual growth rate (in percentage): ");
	scanf("%f", &wolf_growth_rate);
	printf("Enter rabbit annual growth rate (in percentage): ");
	scanf("%f", &rabbit_growth_rate);
	printf("Enter grass area annual growth rate (in percentage): ");
	scanf("%f", &grass_growth_rate);

	/* Header and initial output */
	printf("Year\t\tWolf population\tRabbit population\tAvailable Grass Area\n");
	printf("0\t\t%d\t\t%d\t\t\t%.2f\n", wolf_pop, rabbit_pop, grass_area);
	
	/* Calculations */
	for(year = 1; year <= 20; year++)
	{

		/* Check if max or min population has been reached and records it */
		if(wolf_pop < min_wolf_pop)
		{
			min_wolf_pop = wolf_pop;
			year_min_wolf_pop = year - 1;
		}

		if(wolf_pop > max_wolf_pop)
		{
			max_wolf_pop = wolf_pop;
			year_max_wolf_pop = year - 1;
		}

		if(rabbit_pop < min_rabbit_pop)
		{
			min_rabbit_pop = rabbit_pop;
			year_min_rabbit_pop = year - 1;
		}

		if(rabbit_pop > max_rabbit_pop)
		{
			max_rabbit_pop = rabbit_pop;
			year_max_rabbit_pop = year - 1;
		}

		prev_wolf_pop = wolf_pop;
		prev_rabbit_pop = rabbit_pop;
		prev_grass_area = grass_area;
		
		/* Check if five years has passed since previous disease spread */
		
		if((year-1)%5 == 0 && year != 1)
		{
			wolf_pop = prev_wolf_pop/2;
		}
		else
		{
			wolf_pop = prev_wolf_pop*(1 + wolf_growth_rate/100.00);
		}

		rabbit_pop = prev_rabbit_pop*(1 + rabbit_growth_rate/100.00) - prev_wolf_pop*50;
		grass_area = prev_grass_area*(1 + grass_growth_rate/100.00) - prev_rabbit_pop*1.2;
	
 		printf("%d\t\t%d\t\t%d\t\t\t%.2f\n", year, wolf_pop, rabbit_pop, grass_area);	
	}
		/* Output min/max rabbit/wolf values and years */
		printf("\nWolf population was minimum as %d in year %d", min_wolf_pop, year_min_wolf_pop);
		printf("\nWolf population was maximum as %d in year %d", max_wolf_pop, year_max_wolf_pop);
		printf("\nRabbit population was minimum as %d in year %d", min_rabbit_pop, year_min_rabbit_pop);
		printf("\nRabbit population was maximum as %d in year %d\n", max_rabbit_pop, year_max_rabbit_pop);

	return 0;
}

/* EOF */
