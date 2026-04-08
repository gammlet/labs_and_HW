#include <stdio.h>
#include <stdlib.h>

double two_d_random(int n) {
	//code here
	struct Point {int x ; int y; };
	struct Bounds{ struct  Point A; struct  Point B; };
	struct Point walker = {0,0};

	struct Point* locVisited = (struct Point *)malloc(n*sizeof(int));
	struct Point* inverseLocVisited = (struct Point *)malloc(n*sizeof(int));

	int r = rand() % 4;
}

int main(void) {
	int r = rand() % 4;
	printf("%d\n", r);

}