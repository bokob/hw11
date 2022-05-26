#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

#define MAX_VERTEX 10 // �ִ� ���� ��

int remember_v[MAX_VERTEX];
/* �߰��� �������� ����ϱ� ���� �迭.
�ڽ��� �߰��� ������ ��������Ʈ�� ��µǰ� �ϱ� ���� ���� �迭�̴�. */

int visited[MAX_VERTEX]; // dfs, bfs�� ���� �迭. �湮�� ������� Ȯ���ϱ� ���� �迭�̴�.

typedef struct GraphNode // ����ü GraphNode ����
{
    int vertex;             // ����
    struct GraphNode *link; // ����ü GraphNode�� ���� ������ link
} GraphNode;                // ������ ����ü GraphNode�� GraphNode�� ����

typedef struct GraphType // ����ü GraphType ����
{
    int n;                           // �����ǰ���
    GraphNode *adj_list[MAX_VERTEX]; // ����ü GraphNode�� ���� ������ �迭 adj_list
} GraphType;                         // ������ ����ü GraphType�� GraphType�̶� ����

typedef struct QueueType // ����ü QueueType ����
{
    int element[MAX_VERTEX]; // ����ť
    int front, rear;         // ����ť�� ����� front, rear
} QueueType;

void initQueue(QueueType *cq);         // ����ť �ʱ�ȭ
int is_emmpty(QueueType *cq);          // ����ť�� ���� ���� �˻�
int is_full(QueueType *cq);            // ����ť�� ��ȭ ���� �˻�
void enqueue(QueueType *cq, int item); // ����ť���� enqueue ���
int dequeue(QueueType *cq);            // ����ť���� dequeue ���

void initialize_graph(GraphType **g);         // �׷��� �ʱ�ȭ
void insert_vertex(GraphType *g, int v);      // �׷����� ���� v ����
void insert_edge(GraphType *g, int u, int v); // �׷����� ���� u�� v�� ���� ����
void dfs(GraphType *g, int v);                // ���� v���� ���� �켱 Ž��
void bfs(GraphType *g, int v);                // ���� v���� �ʺ� �켱 Ž��
void print_adlist(GraphType *g);              // �׷����� ��������Ʈ ���
void free_graph(GraphType *g);                // �׷��� �ʱ�ȭ

int main()
{
    char command;
    int vertex;           // insert_vertex �Լ��� �Ű������� �ֱ� ���� ���� vertex
    int u, v;             // insert_edge �Լ��� �Ű������� �ֱ� ���� ���� u, v
    int initflag = FALSE; // �ʱ�ȭ ���θ� ǥ���ϱ� ���� ���� initflag
    int search_start;     // dfs, bfs Ž���� ������ ���� search_start

    GraphType *g = (GraphType *)malloc(sizeof(GraphType));
    /* �޸��� Heap ������ GraphType ũ�⸸ŭ�� ������ �����, �װ��� �ּҸ�
    �޸��� Stack ������ �ִ� g�� �ִ´�. */

    printf("[-------------------- [����â] [2021040021] --------------------]");

    do
    {
        printf("\n\n");
        printf("----------------------------------------------------------------\n");
        printf("                         Graph Searches                         \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Graph     = z                                       \n");
        printf(" Insert Vertex        = v      Insert Edge                  = e \n");
        printf(" Depth First Search   = d      Breath First Search          = b \n");
        printf(" Print Graph          = p      Quit                         = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        int search_flag = FALSE; // search_flag�� FALSE�� �ʱ�ȭ

        switch (command)
        {
        case 'z':
        case 'Z':
            initialize_graph(&g); // g �ʱ�ȭ
            initflag = TRUE;      // initflag�� TRUE�� �ٲ۴�.
            break;
        case 'v':
        case 'V':
            if (initflag == FALSE) // initialize_graph �Լ� �������� ���� ���
            {
                printf("Initialize Graph�� �������ּ���!\n");
                // �׷����� �ʱ�ȭ �϶�� ���� ���
                break;
            }
            printf("� ������ �߰��� ���ΰ���?(0 ~ 9������ ������ ����) ");
            scanf("%d", &vertex);
            insert_vertex(g, vertex); // �׷����� ���� vertex �߰�
            break;
        case 'e':
        case 'E':
            if (initflag == FALSE) // initialize_graph �Լ� �������� ���� ���
            {
                printf("Initialize Graph�� �������ּ���!\n");
                // �׷����� �ʱ�ȭ �϶�� ���� ���
                break;
            }
            printf("� ������ ������ ���ΰ���? ");
            scanf("%d %d", &u, &v);
            insert_edge(g, u, v); // �׷����� ���� u���� ���� v���� ���� ����
            break;
        case 'd':
        case 'D':
            if (initflag == FALSE) // initialize_graph �Լ� �������� ���� ���
            {
                printf("Initialize Graph�� �������ּ���!\n");
                // �׷����� �ʱ�ȭ �϶�� ���� ���
                break;
            }
            printf("DFS�� ������ ������ �Է��ϼ���. ");
            scanf("%d", &search_start);          // Ž���� ������ ���� �Է�
            for (int i = 0; i < MAX_VERTEX; i++) // MAX_VERTEX ũ�⸸ŭ �ݺ�
            {
                if (search_start == remember_v[i])
                // search_start�� remember_v�� �����ϴ� ���
                {
                    search_flag = TRUE; // search_flag�� TRUE�� �ٲ۴�.
                }
            }
            if (search_flag == FALSE) // search_flag�� FALSE�� ���
            {
                printf("������ �� ���� �����Դϴ�!\n");
                // Ž���� ������ �� ���ٴ� ���� ���
                break;
            }
            for (int i = 0; i < MAX_VERTEX; i++) // MAX_VERTEX ũ�⸸ŭ �ݺ�
            {
                visited[i] = FALSE; // visited�� ��� ���Ҹ� FALSE�� �ʱ�ȭ
            }
            dfs(g, search_start); // ���� search_start���� ���� �켱 Ž�� ����
            break;
        case 'b':
        case 'B':
            if (initflag == FALSE) // initialize_graph �Լ� �������� ���� ���
            {
                printf("Initialize Graph�� �������ּ���!\n");
                // �׷����� �ʱ�ȭ �϶�� ���� ���
                break;
            }
            printf("BFS�� ������ ������ �Է��ϼ���. ");
            scanf("%d", &search_start);          // Ž���� ������ ���� �Է�
            for (int i = 0; i < MAX_VERTEX; i++) // MAX_VERTEX ũ�⸸ŭ �ݺ�
            {
                if (search_start == remember_v[i])
                // search_start�� remember_v�� �����ϴ� ���
                {
                    search_flag = TRUE; // search_flag�� TRUE�� �ٲ۴�.
                }
            }
            if (search_flag == FALSE) // search_flag�� FALSE�� ���
            {
                printf("������ �� ���� �����Դϴ�!\n");
                // Ž���� ������ �� ���ٴ� ���� ���
                break;
            }
            for (int i = 0; i < MAX_VERTEX; i++) // MAX_VERTEX ũ�⸸ŭ �ݺ�
            {
                visited[i] = FALSE; // visited�� ��� ���Ҹ� FALSE�� �ʱ�ȭ
            }
            bfs(g, search_start); // ���� search_start���� �ʺ� �켱 Ž�� ����
            break;
        case 'p':
        case 'P':
            if (initflag == FALSE) // initialize_graph �Լ� �������� ���� ���
            {
                printf("Initialize Graph�� �������ּ���!\n");
                // �׷����� �ʱ�ȭ �϶�� ���� ���
                break;
            }
            print_adlist(g); // �׷����� ��������Ʈ ���
            break;
        case 'q':
        case 'Q':
            free_graph(g);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }
    } while (command != 'q' && command != 'Q'); // command�� q,Q�� �ƴ� ������ �ݺ�

    return 0;
}

void initQueue(QueueType *cq) // ����ť �ʱ�ȭ
{
    cq->front = cq->rear = 0;
    // cq�� ����Ű�� ���� front�� rear 0���� �ʱ�ȭ
}

int is_empty(QueueType *cq) // ����ť�� ���� ���� �˻�
{
    return (cq->front == cq->rear);
    // cq�� ����Ű�� ���� front�� cq�� ����Ű�� ���� rear�� ���� ��� 1��ȯ �ƴϸ� 0 ��ȯ
}

int is_full(QueueType *cq) // ����ť�� ��ȭ ���� �˻�
{
    return ((cq->rear + 1) % MAX_VERTEX == cq->front);
    /* cq�� ����Ű�� ���� rear�� 1�� ���ϰ� MAX_VERTEX�� �������� ���� ��������
    cq�� ����Ű�� ���� front�� ���� ��쿡 1��ȯ �ƴϸ� 0 ��ȯ */
}

void enqueue(QueueType *cq, int item) // ����ť���� enqueue ���
{
    if (is_full(cq)) // cq�� ������ ���
    {
        printf("����ť�� ���� ��!\n"); // ����ť�� ���� á�ٴ� ���� ���
        return;
    }
    else //  cq�� ���� ���� ���� ���
        cq->rear = (cq->rear + 1) % MAX_VERTEX;
    /* cq�� ����Ű�� ���� rear�� cq�� ����Ű�� ���� rear�� 1�� ���� �� MAX_VERTEX��
    �������� ���� �������� �ִ´�.*/

    cq->element[cq->rear] = item;
    // cq�� ����Ű�� ���� element�� (cq�� ����Ű�� ���� rear)��° �ε����� item�� �ִ´�.
}

int dequeue(QueueType *cq) // ����ť���� dequeue ���
{
    if (is_empty(cq)) // cq�� ����ִ� ���
    {
        printf("����ť�� �����!\n"); // ����ť�� ����ٴ� ���� ���
        exit(1);
    }
    else // cq�� ������� ���� ���
        cq->front = (cq->front + 1) % MAX_VERTEX;
    /* cq�� ����Ű�� ���� front�� cq�� ����Ű�� ���� front�� 1�� ���� �� MAX_VERTEX��
    �������� ���� �������� �ִ´�.*/

    return cq->element[cq->front];
    // cq�� ����Ű�� ���� element�� (cq�� ����Ű�� ���� front)��° �ε����� ����ִ� �� ��ȯ
}

void initialize_graph(GraphType **g) // �׷��� �ʱ�ȭ
{
    (*g)->n = 0;                         // g�� ����Ű�� ���� ����Ű�� ���� n�� 0�� �ִ´�.
    for (int v = 0; v < MAX_VERTEX; v++) // MAX_VERTEX ũ�⸸ŭ �ݺ�
    {
        (*g)->adj_list[v] = NULL;
        // g�� ����Ű�� ���� ����Ű�� ���� adj_list[v]�� NULL�� �ִ´�.
        remember_v[v] = -1; // remember_v[v]�� -1�� �ִ´�.
    }
}

void insert_vertex(GraphType *g, int v) // �׷����� ���� v ����
{
    if (v < 0 || 9 < v) // ������ ��ȣ�� 0~9�� �ƴ� ���
    {
        printf("0 ~ 9������ ������ �ƴմϴ�!\n"); // 0~9������ ������ �ƴ϶�� ���� ���
        return;
    }

    if (((g->n) + 1) > MAX_VERTEX) // �׷����� ũ�Ⱑ �ִ� ������ ���� �Ѵ� ���
    {
        printf("�׷��� ������ ������ �ʰ�!\n"); // �׷��� ������ ������ �ʰ��ߴٴ� ���� ���
        return;
    }
    for (int i = 0; i < MAX_VERTEX; i++) // MAX_VERTEX�� ũ�⸸ŭ �ݺ�
    {
        if (v == remember_v[i]) // v�� remember_v�� �ִ� ���. ��, ���� v�� �̹� �����ϴ� ���
        {
            printf("�̹� �߰��� �����Դϴ�!\n"); // �̹� �߰��� �����̶�� ���� ���
            return;
        }
    }
    remember_v[v] = v; // remember_v�� v��°�� v ����
    g->n++;            // g�� ����Ű�� ���� n�� 1��ŭ ����
}

void insert_edge(GraphType *g, int u, int v) // �׷����� ���� u�� v�� ���� ����
{
    GraphNode *node; // GraphNode ������ node
    GraphNode *p = g->adj_list[u];
    // GraphNode ������ p�� g�� ����Ű�� ���� adj_list[u]�� ����ִ� �ּҸ� �ִ´�.
    GraphNode *pre = NULL; // GraphNode ������ pre�� NULL�� �ִ´�.
    int flag = FALSE;
    // ��ȣ�� ���� ������ ��������Ʈ�� �������� ���Եǰ� �ϱ� ���� �ʿ��� ���� flag

    int temp1 = -1; // remember_v������ ���� u�� ��ġ�� �����ϱ� ���� ���� temp1
    int temp2 = -1; // remember_v������ ���� v�� ��ġ�� �����ϱ� ���� ���� temp2

    for (int i = 0; i < MAX_VERTEX; i++) // MAX_VERTEX ũ�⸸ŭ �ݺ�
    {
        if (remember_v[i] == u) // ���� u�� �ִٸ�
            temp1 = i;          // ���� u�� ��ġ�� ����Ѵ�.
    }

    for (int i = 0; i < MAX_VERTEX; i++) // MAX_VERTEX ũ�⸸ŭ �ݺ�
    {
        if (remember_v[i] == v) // ���� v�� �ִٸ�
            temp2 = i;          // ���� v�� ��ġ�� ����Ѵ�.
    }

    if (temp1 == -1 || temp2 == -1) // ���� u �Ǵ� v�� �������� �ʴ´ٸ�
    {
        printf("�׷����� �������� �ʴ� ����!"); // �׷����� �������� �ʴ´ٴ� ���� ���
        return;
    }

    node = (GraphNode *)malloc(sizeof(GraphNode));
    // �޸��� Heap ������ GraphNode ũ�� ��ŭ�� ũ�⸦ �����, �װ��� �ּҸ� node�� �ִ´�.
    node->vertex = remember_v[temp2];
    // node�� ����Ű�� ���� vertex�� remember_v[temp2]�� ���� �ִ´�.

    if (g->adj_list[u] == NULL) /* g�� ����Ű�� ���� adj_list[u]�� ���� NULL�� ���
    ��, ���� u�� ��������Ʈ�� �������� �ʴ� ��� */
    {
        node->link = g->adj_list[remember_v[temp1]];
        /* node�� ����Ű�� ���� link�� g�� ����Ű�� ����
        adj[remember_v[temp1]]�� ���� �ִ´�.
        node�� ����Ű�� ���� link�� NULL�� �ִ´ٴ� ���̴�. */
        g->adj_list[remember_v[temp1]] = node;
        /* g�� ����Ű�� ���� adj_list[remember_v[temp1]]�� node�� ����ִ� �ּҸ� �ִ´�.
        ��, ���� u�� ��������Ʈ�� node�� �߰��ϴ� ���̴�. */
    }
    else /* g�� ����Ű�� ���� adj_list[u]�� ���� NULL�� �ƴ� ���
    ��, ���� u�� ��������Ʈ�� �����ϴ� ��� */
    {
        while (p != NULL) // p�� NULL�� �ƴ� ������ �ݺ�
        {
            if (p->vertex > node->vertex)
            // p�� ����Ű�� ���� vertex�� node�� ����Ű�� ���� vertex���� ū ���
            {
                flag = TRUE; // flag�� TRUE�� �ٲ۴�.
                break;
            }
            pre = p;     // prev�� p�� ����ִ� �ּҸ� �ִ´�.
            p = p->link; // p�� p�� ����Ű�� ���� link�� ����ִ� �ּҸ� �ִ´�.
        }
        if (flag == TRUE) // flag�� TRUE�� ���. ��, �߰��� �����ϴ� ���
        {
            if (p == g->adj_list[u])
            // p�� g�� ����Ű�� ���� adj_list[u]�� ����ִ� �ּҰ� ���� ���
            {
                node->link = g->adj_list[remember_v[temp1]];
                /* node�� ����Ű�� ���� link�� g�� ����Ű�� ���� adj_list[remember_v[temp1]]
                �� ����ִ� ���� �ִ´�. */
                g->adj_list[remember_v[temp1]] = node;
                /* g�� ����Ű�� ���� adj_list[remember_v[temp1]]��
                node�� ����ִ� �ּҸ� �ִ´�. */
            }
            else // p�� g�� ����Ű�� ���� adj_list[u]�� ����ִ� �ּҰ� �ٸ� ���
            {
                node->link = p; // node�� ����Ű�� ���� link�� p�� ����ִ� �ּҸ� �ִ´�.
                pre->link = node;
                // pre�� ����Ű�� ���� link�� node�� ����ִ� �ּҸ� �ִ´�.
            }
        }
        else // flag�� FALSE�� ��� ��, �������� �����ϴ� ���
        {
            node->link = NULL; // node�� ����Ű�� ���� link�� NULL�� �ִ´�.
            pre->link = node;  // pre�� ����Ű�� ���� link�� node�� �ִ´�.
        }
    }
}

void dfs(GraphType *g, int v) // ���� v���� ���� �켱 Ž��
{
    GraphNode *w;      // GraphNode�� ���� ������ w
    visited[v] = TRUE; // ���� ������ �湮�� ������ ǥ��
    printf("%d ", v);  // ���
    for (w = g->adj_list[v]; w; w = w->link)
    // w�� g�� ����Ű�� ���� v�� ��������Ʈ���� w�� NULL�� ������ �ݺ�
    {
        if (!visited[w->vertex]) // ���� w�� ����Ű�� ���� vertex�� �湮���� ���� ����� ���
        {
            dfs(g, w->vertex); // dfs �Լ� ȣ��
        }
    }
}

void bfs(GraphType *g, int v) // ���� v���� �ʺ� �켱 Ž��
{
    GraphNode *w; // GraphNode�� ���� ������ w
    QueueType cq;

    initQueue(&cq); // cQ �ʱ�ȭ

    visited[v] = TRUE; // �ʺ� �켱 Ž���� �����ϴ� ���� v�� �湮�ߴٰ� ǥ��

    printf("%d ", v);      // v ���
    enqueue(&cq, v);       // cq�� v�� enqueue�Ѵ�.
    while (!is_empty(&cq)) // cq�� ������� ���� ������ �ݺ�
    {
        v = dequeue(&cq); // cq���� dequeue�� ���� v�� �Ҵ�
        for (w = g->adj_list[v]; w; w = w->link)
            // w�� g�� ����Ű�� ���� v�� ��������Ʈ���� w�� NULL�� ������ �ݺ�
            if (!visited[w->vertex]) // w�� ����Ű�� ���� vertex�� �湮���� �ʾҴٸ�
            {
                visited[w->vertex] = TRUE; // w�� ����Ű�� ���� vertex�� �湮�ߴٰ� ǥ��
                printf("%d ", w->vertex);  // w�� ����Ű�� ���� vertex ���
                enqueue(&cq, w->vertex);   // w�� ����Ű�� ���� vertex�� cq�� enqueue�Ѵ�.
            }
    }
}

void print_adlist(GraphType *g) // �׷����� ��������Ʈ ���
{
    GraphNode *p;     // GraphNode�� ���� ������ p
    int flag = FALSE; // ����� ���� �ִ��� ������ �Ǻ��ϱ� ���� flag�� FALSE�� �ʱ�ȭ

    for (int i = 0; i < MAX_VERTEX; i++) // remember_v�� ����� ������ �ִ��� Ž��
    {
        if (remember_v[i] > -1) // remember_v�� ����� ������ �ִ� ���
        {
            flag = TRUE; // flag�� TRUE�� �ٲ۴�.
        }
    }

    if (flag == FALSE) // flag�� FALSE�� ���
    {
        printf("����� ���� �����ϴ�!\n"); // ����� ���� ���ٴ� ���� ���
        return;
    }

    for (int i = 0; i < MAX_VERTEX; i++) // MAX_VERTEX ũ�⸸ŭ �ݺ�
    {
        if (remember_v[i] > -1) // remember_v�� ������ ����Ǿ��ִ� ���
        {
            printf("\n\t\t���� %d�� ���� ����Ʈ", remember_v[i]);
            // remember_v�� ����� ���� ���
            p = g->adj_list[remember_v[i]];
            /* g�� ����Ű�� ���� adj_list(remember_v�� ����Ǿ� �ִ� ������ ��������Ʈ)
            �� �ּҸ� p�� �ִ´�.*/

            while (p) // p�� NULL�� ����Ű�� ���� ������ �ݺ�
            {
                printf(" -> %d", p->vertex); // p�� ����Ű�� ���� vertex ���
                p = p->link;                 // p�� p�� ����Ű�� ���� link�� ����ִ� �ּҸ� �ִ´�.
            }
            printf("\n");
        }
    }
}

void free_graph(GraphType *g) // �׷��� �ʱ�ȭ
{
    for (int i = 0; i < MAX_VERTEX; i++) // MAX_VERTEX ũ�⸸ŭ �ݺ�
    {
        GraphNode *p = g->adj_list[i];   
        // GraphNode�� ���� ������ p�� g�� ����Ű�� ���� adj_list[i]�� ����ִ� ���� �ִ´�.
        GraphNode *prev = NULL;         // GraphNode�� ���� ������ prev�� NULL�� �ִ´�.  
        if (g->adj_list[i] != NULL)
        /* g�� ����Ű�� ���� adj_list[i]�� NULL�� �ƴ� ��� ��, ��������Ʈ�� �����ϴ� ����. */
        {
            while (p != NULL)   // p�� NULL�� ������ �ݺ�
            {
                prev = p;       // prev�� p�� ����ִ� �ּҸ� �ִ´�.
                p = p->link;    // p�� p�� ����Ű�� ���� link�� ����ִ� �ּҸ� �ִ´�.
                free(prev);     // prev�� �����Ѵ�.
            }
        }
    }
    free(g); // �׷��� g ����
}