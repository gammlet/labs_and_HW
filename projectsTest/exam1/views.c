#include <stdio.h>
#include <stdlib.h>

typedef struct building {
    int index;
    struct building *neighbor;
} BuildingSet;

void addToSet(BuildingSet **b, int v) {
    BuildingSet newhouse;
    newhouse->index = v;
    newHouse->neighbor = b;
    return newnode;
}


}

int removeFromSet(BuildingSet **b) {

}

int isSetEmpty(BuildingSet *b) {
    if (b==NULL){
        return 1;
    }else{
        return 0;
    }

}

int topOfTheSet(BuildingSet *b) {}

void printSet(BuildingSet *b) {
    if (isSetEmpty(b)) {
        printf("Empty\n");
        return;
    }
    while (b != NULL) {
        printf("%d ", b->index);
        b = b->neighbor;
    }
    printf("\n");
}

void freeSet(BuildingSet **b) {}

BuildingSet *checkViews(int *input, int count, int position) {
    if(position == 1){
        for(int i = 0 ){
            while(isSetEmpty(b)==0 && b>=topOfTheSet(b)){
                removeFromSet(topOfTheSet(b));
                addToSet();

            }
        }
    }else {

    }

}

int main(int argc, char *argv[]) {
    int position = atoi(argv[1]);
    int count = argc - 2;
    int *input = malloc(count * sizeof(int));

    for (int i = 0; i < count; i++) {
        input[i] = atoi(argv[i + 2]);
    }

    BuildingSet *b = checkViews(input, count, position);
    printSet(b);

    return 0;
}
