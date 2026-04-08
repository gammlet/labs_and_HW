#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Simulate one particle moving n steps
void one_particle(int *grid, int n)
{
    int x = 0, y = 0, z = 0;
    int size = 2*n + 1;

    for(int i = 0; i < n; i++)
    {
        int r = rand() % 6;

        if(r == 0) x--;          // left (x - 1)
        else if(r == 1) x++;     // right (x + 1)
        else if(r == 2) y++;     // up (y + 1)
        else if(r == 3) y--;     // down (y - 1)
        else if(r == 4) z++;     // up (z + 1)
        else z--;                // down (z - 1)
    }

    int index = (x + n) * size * size + (y + n) * size + (z + n);
    grid[index]++;
}


// Return fraction of particles within distance r*n
// Avoid sqrt by comparing squared distances
double density(int *grid, int n, double r)
{
    int size = 2*n + 1;
    double radius_sq = (r * n) * (r * n);

    long inside = 0;
    long total = 0;

    for(int x = -n; x <= n; x++)
    {
        for(int y = -n; y <= n; y++)
        {
            for(int z = -n; z <= n; z++)
            {
                int index = (x + n) * size * size + (y + n) * size + (z + n);
                int count = grid[index];

                if(count > 0)
                {
                    total += count;

                    int dist_sq = x*x + y*y + z*z;

                    if(dist_sq <= radius_sq)
                        inside += count;
                }
            }
        }
    }

    return (double)inside / total;
}


// use this function to print results
void print_result(int *grid, int n)
{
    printf("radius density\n");
    for(int k = 1; k <= 20; k++)
    {
        printf("%.2lf   %lf\n", 0.05*k, density(grid, n, 0.05*k));
    }
}


// Finish diffusion
void diffusion(int n, int m)
{
    int size = 2*n + 1;
    int total_size = size * size * size;

    // dynamically allocate and initialize to 0
    int *grid = (int*)calloc(total_size, sizeof(int));
    assert(grid != NULL);

    for(int i = 1; i <= m; i++)
        one_particle(grid, n);

    print_result(grid, n);

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

    assert(n >= 1 && n <= 50);
    assert(m >= 1 && m <= 1000000);

    srand(12345);
    diffusion(n, m);

    return 0;
}
