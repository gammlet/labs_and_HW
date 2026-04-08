#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <_strings.h>

//TODO
//Implement the below function
//Simulate one particle moving n steps in random directions
//Use a random number generator to decide which way to go at every step
//When the particle stops at a final location, use the memory pointed to by grid to 
//record the number of particles that stop at this final location
//Feel free to declare, implement and use other functions when needed

void one_particle(int *grid, int n)
{
	int x = 0, y = 0, z = 0;
	for(int i = 0; i < n; i++){
		int direction = rand() % 6;
		if (direction == 0) {
			x++;
		} else if (direction == 1) {
			x--;
		} else if (direction == 2) {
			y++;
		} else if (direction == 3) {
			y--;
		} else if (direction == 4) {
			z++;
		} else {
			z--;
		}
	}
	int size =2 * n + 1;
	int xi = x + n;
	int yi = y + n;
	int zi = z + n;
	int index = xi * size * size + yi * size + zi;
	grid[index]++;
}

//TODO
//Implement the following function
//This function returns the fraction of particles that lie within the distance
//r*n from the origin (including particles exactly r*n away)
//The distance used here is Euclidean distance
//Note: you will not have access to math.h when submitting on Mimir
double density(int *grid, int n, double r)
{
	int total_particles = 0;
	int size = 2*n + 1;
	int inside = 0;
	int index = 0;

	int R = r*n;
	double R2 = R*R;
	for (int xi = 0; xi<size; xi++) {
		for (int yi = 0; yi<size; yi++) {
			for (int zi = 0; zi<size; zi++) {

				int x = xi - n;
				int y = yi - n;
				int z = zi - n;

				int dist2 = x*x + y*y + z*z;

				index = xi*size*size + yi*size + zi;
				total_particles +=grid[index];

				if (dist2 <= R2) {
					inside += grid[index];
				}
			}
		}
	}
	return (double)inside/total_particles;


    
}

//use this function to print results
void print_result(int *grid, int n)
{
    printf("radius density\n");
    for(int k = 1; k <= 20; k++)
    {
        printf("%.2lf   %lf\n", 0.05*k, density(grid, n, 0.05*k));
    }
}

//TODO
//Finish the following function
//See the assignment decription on Piazza for more details
void diffusion(int n, int m)
{	

	//fill in a few line of code below
	int size = 2*n+1;    // length of one axis in the grid
	int total = size*size*size; //total amount of points on a grid
	int *grid = (int *)malloc(sizeof(int)*total); //memory for 3d grid
	for(int i = 0; i < total; i++) {
		grid[i] = 0;
	}
	// stop woking on grid

	for(int i = 1; i<=m; i++) {
		one_particle(grid, n);  //random walk for new particle and record the final location in grid as counder on index

	}

	print_result(grid, n);
	//fill in some code below
	free(grid);

}

int main(int argc, char *argv[])
{
	
	if(argc != 3)
	{
		printf("Usage: %s n m\n", argv[0]);
		return 0; 
	}
	int n = atoi(argv[1]);
	int m = atoi(argv[2]);

	assert(n >= 1 && n <=50);
	assert(m >= 1 && m <= 1000000);
	srand(12345);
	diffusion(n, m);
	return 0;
}
