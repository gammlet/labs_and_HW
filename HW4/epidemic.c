#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

enum TYPE {S, I, R};

// map (x,y) to a unique integer
int idx(int x, int y, int k)
{
    // shift range from [-k,k] to [0,2k]
    return (x + k) * (2 * k + 1) + (y + k);
}

typedef struct Host
{
    int id;
    int x, y;
    int t;              // time since infected
    enum TYPE type;
} THost;

typedef struct node_tag {
   THost host;
   struct node_tag * next;
} node;

node * create_node(THost host)
{
    node *newnode = (node *)malloc(sizeof(node));
    assert(newnode != NULL);
    newnode->host = host;
    newnode->next = NULL;
    return newnode;
}

void add_first(node **head, node *newnode)
{
    newnode->next = *head;
    *head = newnode;
}

node * remove_first(node **head)
{
    if(*head == NULL) return NULL;
    node *temp = *head;
    *head = (*head)->next;
    temp->next = NULL;
    return temp;
}

void remove_all(node **head)
{
    node *curr = *head;
    while(curr != NULL)
    {
        node *temp = curr;
        curr = curr->next;
        free(temp);
    }
    *head = NULL;
}

int location_match(node *head, THost host)
{
    node *curr = head;
    while(curr != NULL)
    {
        if(curr->host.x == host.x && curr->host.y == host.y)
            return 1;
        curr = curr->next;
    }
    return 0;
}

unsigned hash(unsigned a)
{
    a = (a ^ 61) ^ (a >> 16);
    a = a + (a << 3);
    a = a ^ (a >> 4);
    a = a * 0x27d4eb2d;
    a = a ^ (a >> 15);
    return a;
}

int summary(THost hosts[], int m)
{
    int S_n = 0, I_n = 0, R_n = 0;

    for(int i = 0; i < m; i++)
    {
        S_n += (hosts[i].type == S);
        I_n += (hosts[i].type == I);
        R_n += (hosts[i].type == R);
    }

    if(I_n == 0)
    {
        printf("    S        I        R\n");
        printf("%lf %lf %lf\n",
            (double)S_n/m,
            (double)I_n/m,
            (double)R_n/m);
    }

    return I_n > 0;
}

int one_round(THost *hosts, int m, node *p_arr[], int n_arr, int k, int T)
{
    // Infection and recovery
    for(int i = 0; i < m; i++)
    {
        if(hosts[i].type == S)
        {
            int index = hash(idx(hosts[i].x, hosts[i].y, k)) % n_arr;
            if(location_match(p_arr[index], hosts[i]))
            {
                hosts[i].type = I;
                hosts[i].t = 0;
            }
        }
        else if(hosts[i].type == I)
        {
            hosts[i].t++;
            if(hosts[i].t >= T)
            {
                hosts[i].type = R;
            }
        }
    }

    // clear hash table
    for(int i = 0; i < n_arr; i++)
    {
        remove_all(&p_arr[i]);
    }

    // movement + rebuild hash table
    for(int i = 0; i < m; i++)
    {
        int r = rand() % 4;

        switch(r)
        {
            case 0: // up
                hosts[i].y = (hosts[i].y == k) ? -k : hosts[i].y + 1;
                break;
            case 1: // right
                hosts[i].x = (hosts[i].x == k) ? -k : hosts[i].x + 1;
                break;
            case 2: // down
                hosts[i].y = (hosts[i].y == -k) ? k : hosts[i].y - 1;
                break;
            case 3: // left
                hosts[i].x = (hosts[i].x == -k) ? k : hosts[i].x - 1;
                break;
        }

        if(hosts[i].type == I)
        {
            node *rnode = create_node(hosts[i]);
            int index = hash(idx(hosts[i].x, hosts[i].y, k)) % n_arr;
            add_first(&(p_arr[index]), rnode);
        }
    }

    return summary(hosts, m);
}

int main(int argc, char *argv[])
{
    if(argc != 5)
    {
        printf("Usage: %s k m T N\n", argv[0]);
        return 0;
    }

    int k = atoi(argv[1]);
    int m = atoi(argv[2]);
    int T = atoi(argv[3]);
    int N = atoi(argv[4]);

    assert(k >= 0 && k <= 1000);
    assert(m >= 1 && m <= 100000);
    assert(T >= 1);
    assert(N > 0 && N <= 100000);

    srand(12345);

    THost hosts[m];

    hosts[0].id = 0;
    hosts[0].x = 0;
    hosts[0].y = 0;
    hosts[0].t = 0;
    hosts[0].type = I;

    for(int i = 1; i < m; i++)
    {
        hosts[i].id = i;
        hosts[i].x = rand() % (2*k + 1) - k;
        hosts[i].y = rand() % (2*k + 1) - k;
        hosts[i].t = 0;
        hosts[i].type = S;
    }

    node *p_arr[N];
    for(int i = 0; i < N; i++)
        p_arr[i] = NULL;

    node *r = create_node(hosts[0]);
    int index = hash(idx(hosts[0].x, hosts[0].y, k)) % N;
    add_first(&(p_arr[index]), r);

    while(one_round(hosts, m, p_arr, N, k, T));

    return 0;
}