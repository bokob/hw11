#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

#define MAX_VERTEX 10 // 최대 정점 수

int remember_v[MAX_VERTEX];
/* 추가한 정점들을 기억하기 위한 배열.
자신이 추가한 정점과 인접리스트만 출력되게 하기 위해 쓰일 배열이다. */

int visited[MAX_VERTEX]; // dfs, bfs에 쓰일 배열. 방문한 노드인지 확인하기 위한 배열이다.

typedef struct GraphNode // 구조체 GraphNode 선언
{
    int vertex;             // 정점
    struct GraphNode *link; // 구조체 GraphNode에 대한 포인터 link
} GraphNode;                // 선언한 구조체 GraphNode를 GraphNode라 정의

typedef struct GraphType // 구조체 GraphType 선언
{
    int n;                           // 정점의개수
    GraphNode *adj_list[MAX_VERTEX]; // 구조체 GraphNode에 대한 포인터 배열 adj_list
} GraphType;                         // 선언한 구조체 GraphType을 GraphType이라 정의

typedef struct QueueType // 구조체 QueueType 선언
{
    int element[MAX_VERTEX]; // 원형큐
    int front, rear;         // 원형큐에 사용할 front, rear
} QueueType;

void initQueue(QueueType *cq);         // 원형큐 초기화
int is_emmpty(QueueType *cq);          // 원형큐의 공백 상태 검사
int is_full(QueueType *cq);            // 원형큐의 포화 상태 검사
void enqueue(QueueType *cq, int item); // 원형큐에서 enqueue 기능
int dequeue(QueueType *cq);            // 원형큐에서 dequeue 기능

void initialize_graph(GraphType **g);         // 그래프 초기화
void insert_vertex(GraphType *g, int v);      // 그래프에 정점 v 삽입
void insert_edge(GraphType *g, int u, int v); // 그래프의 정점 u와 v의 간선 생성
void dfs(GraphType *g, int v);                // 정점 v에서 깊이 우선 탐색
void bfs(GraphType *g, int v);                // 정점 v에서 너비 우선 탐색
void print_adlist(GraphType *g);              // 그래프의 인접리스트 출력
void free_graph(GraphType *g);                // 그래프 초기화

int main()
{
    char command;
    int vertex;           // insert_vertex 함수의 매개변수로 주기 위한 정점 vertex
    int u, v;             // insert_edge 함수의 매개변수로 주기 위한 정점 u, v
    int initflag = FALSE; // 초기화 여부를 표시하기 위한 변수 initflag
    int search_start;     // dfs, bfs 탐색을 시작할 정점 search_start

    GraphType *g = (GraphType *)malloc(sizeof(GraphType));
    /* 메모리의 Heap 영역에 GraphType 크기만큼의 공간을 만들고, 그곳의 주소를
    메모리의 Stack 영역에 있는 g에 넣는다. */

    printf("[-------------------- [복무창] [2021040021] --------------------]");

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

        int search_flag = FALSE; // search_flag를 FALSE로 초기화

        switch (command)
        {
        case 'z':
        case 'Z':
            initialize_graph(&g); // g 초기화
            initflag = TRUE;      // initflag를 TRUE로 바꾼다.
            break;
        case 'v':
        case 'V':
            if (initflag == FALSE) // initialize_graph 함수 실행하지 않은 경우
            {
                printf("Initialize Graph를 실행해주세요!\n");
                // 그래프를 초기화 하라는 문구 출력
                break;
            }
            printf("어떤 정점을 추가할 것인가요?(0 ~ 9까지의 정점만 가능) ");
            scanf("%d", &vertex);
            insert_vertex(g, vertex); // 그래프에 정점 vertex 추가
            break;
        case 'e':
        case 'E':
            if (initflag == FALSE) // initialize_graph 함수 실행하지 않은 경우
            {
                printf("Initialize Graph를 실행해주세요!\n");
                // 그래프를 초기화 하라는 문구 출력
                break;
            }
            printf("어떤 정점을 연결할 것인가요? ");
            scanf("%d %d", &u, &v);
            insert_edge(g, u, v); // 그래프의 정점 u에서 정점 v로의 간선 생성
            break;
        case 'd':
        case 'D':
            if (initflag == FALSE) // initialize_graph 함수 실행하지 않은 경우
            {
                printf("Initialize Graph를 실행해주세요!\n");
                // 그래프를 초기화 하라는 문구 출력
                break;
            }
            printf("DFS를 시작할 정점을 입력하세요. ");
            scanf("%d", &search_start);          // 탐색을 시작할 정점 입력
            for (int i = 0; i < MAX_VERTEX; i++) // MAX_VERTEX 크기만큼 반복
            {
                if (search_start == remember_v[i])
                // search_start가 remember_v에 존재하는 경우
                {
                    search_flag = TRUE; // search_flag를 TRUE로 바꾼다.
                }
            }
            if (search_flag == FALSE) // search_flag가 FALSE인 경우
            {
                printf("시작할 수 없는 정점입니다!\n");
                // 탐색을 시작할 수 없다는 문구 출력
                break;
            }
            for (int i = 0; i < MAX_VERTEX; i++) // MAX_VERTEX 크기만큼 반복
            {
                visited[i] = FALSE; // visited의 모든 원소를 FALSE로 초기화
            }
            dfs(g, search_start); // 정점 search_start에서 깊이 우선 탐색 시작
            break;
        case 'b':
        case 'B':
            if (initflag == FALSE) // initialize_graph 함수 실행하지 않은 경우
            {
                printf("Initialize Graph를 실행해주세요!\n");
                // 그래프를 초기화 하라는 문구 출력
                break;
            }
            printf("BFS를 시작할 정점을 입력하세요. ");
            scanf("%d", &search_start);          // 탐색을 시작할 정점 입력
            for (int i = 0; i < MAX_VERTEX; i++) // MAX_VERTEX 크기만큼 반복
            {
                if (search_start == remember_v[i])
                // search_start가 remember_v에 존재하는 경우
                {
                    search_flag = TRUE; // search_flag를 TRUE로 바꾼다.
                }
            }
            if (search_flag == FALSE) // search_flag가 FALSE인 경우
            {
                printf("시작할 수 없는 정점입니다!\n");
                // 탐색을 시작할 수 없다는 문구 출력
                break;
            }
            for (int i = 0; i < MAX_VERTEX; i++) // MAX_VERTEX 크기만큼 반복
            {
                visited[i] = FALSE; // visited의 모든 원소를 FALSE로 초기화
            }
            bfs(g, search_start); // 정점 search_start에서 너비 우선 탐색 시작
            break;
        case 'p':
        case 'P':
            if (initflag == FALSE) // initialize_graph 함수 실행하지 않은 경우
            {
                printf("Initialize Graph를 실행해주세요!\n");
                // 그래프를 초기화 하라는 문구 출력
                break;
            }
            print_adlist(g); // 그래프의 인접리스트 출력
            break;
        case 'q':
        case 'Q':
            free_graph(g);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }
    } while (command != 'q' && command != 'Q'); // command가 q,Q가 아닐 때까지 반복

    return 0;
}

void initQueue(QueueType *cq) // 원형큐 초기화
{
    cq->front = cq->rear = 0;
    // cq가 가리키는 곳의 front와 rear 0으로 초기화
}

int is_empty(QueueType *cq) // 원형큐의 공백 상태 검사
{
    return (cq->front == cq->rear);
    // cq가 가리키는 곳의 front와 cq가 가리키는 곳의 rear가 같은 경웨 1반환 아니면 0 반환
}

int is_full(QueueType *cq) // 원형큐의 포화 상태 검사
{
    return ((cq->rear + 1) % MAX_VERTEX == cq->front);
    /* cq가 가리키는 곳의 rear에 1을 더하고 MAX_VERTEX로 나누었을 때의 나머지가
    cq가 가리키는 곳의 front와 같은 경우에 1반환 아니면 0 반환 */
}

void enqueue(QueueType *cq, int item) // 원형큐에서 enqueue 기능
{
    if (is_full(cq)) // cq가 가득찬 경우
    {
        printf("원형큐가 가득 참!\n"); // 원형큐가 가득 찼다는 문구 출력
        return;
    }
    else //  cq가 가득 차지 않은 경우
        cq->rear = (cq->rear + 1) % MAX_VERTEX;
    /* cq가 가리키는 곳의 rear에 cq가 가리키는 곳의 rear에 1을 더한 후 MAX_VERTEX로
    나누었을 때의 나머지를 넣는다.*/

    cq->element[cq->rear] = item;
    // cq가 가리키는 곳의 element의 (cq가 가리키는 곳의 rear)번째 인덱스에 item을 넣는다.
}

int dequeue(QueueType *cq) // 원형큐에서 dequeue 기능
{
    if (is_empty(cq)) // cq가 비어있는 경우
    {
        printf("원형큐가 비었음!\n"); // 원형큐가 비었다는 문구 출력
        exit(1);
    }
    else // cq가 비어있지 않은 경우
        cq->front = (cq->front + 1) % MAX_VERTEX;
    /* cq가 가리키는 곳의 front에 cq가 가리키는 곳의 front에 1을 더한 후 MAX_VERTEX로
    나누었을 때의 나머지를 넣는다.*/

    return cq->element[cq->front];
    // cq가 가리키는 곳의 element의 (cq가 가리키는 곳의 front)번째 인덱스에 들어있는 값 반환
}

void initialize_graph(GraphType **g) // 그래프 초기화
{
    (*g)->n = 0;                         // g가 가리키는 곳이 가리키는 곳의 n에 0을 넣는다.
    for (int v = 0; v < MAX_VERTEX; v++) // MAX_VERTEX 크기만큼 반복
    {
        (*g)->adj_list[v] = NULL;
        // g가 가리키는 곳이 가리키는 곳의 adj_list[v]에 NULL을 넣는다.
        remember_v[v] = -1; // remember_v[v]에 -1을 넣는다.
    }
}

void insert_vertex(GraphType *g, int v) // 그래프에 정점 v 삽입
{
    if (v < 0 || 9 < v) // 정점의 번호가 0~9가 아닐 경우
    {
        printf("0 ~ 9까지의 정점이 아닙니다!\n"); // 0~9까지의 정점이 아니라는 문구 출력
        return;
    }

    if (((g->n) + 1) > MAX_VERTEX) // 그래프의 크기가 최대 정점의 수를 넘는 경우
    {
        printf("그래프 정점의 개수를 초과!\n"); // 그래프 정점으 개수를 초과했다는 문구 출력
        return;
    }
    for (int i = 0; i < MAX_VERTEX; i++) // MAX_VERTEX의 크기만큼 반복
    {
        if (v == remember_v[i]) // v가 remember_v에 있는 경우. 즉, 정점 v가 이미 존재하는 경우
        {
            printf("이미 추가된 정점입니다!\n"); // 이미 추가된 정점이라는 문구 출력
            return;
        }
    }
    remember_v[v] = v; // remember_v의 v번째에 v 저장
    g->n++;            // g가 가리키는 곳의 n을 1만큼 증가
}

void insert_edge(GraphType *g, int u, int v) // 그래프의 정점 u와 v의 간선 생성
{
    GraphNode *node; // GraphNode 포인터 node
    GraphNode *p = g->adj_list[u];
    // GraphNode 포인터 p에 g가 가리키는 곳의 adj_list[u]에 들어있는 주소를 넣는다.
    GraphNode *pre = NULL; // GraphNode 포인터 pre에 NULL을 넣는다.
    int flag = FALSE;
    // 번호가 작은 정점이 인접리스트의 앞쪽으로 삽입되게 하기 위해 필요한 변수 flag

    int temp1 = -1; // remember_v에서의 정점 u의 위치를 저장하기 위한 변수 temp1
    int temp2 = -1; // remember_v에서의 정점 v의 위치를 저장하기 위한 변수 temp2

    for (int i = 0; i < MAX_VERTEX; i++) // MAX_VERTEX 크기만큼 반복
    {
        if (remember_v[i] == u) // 정점 u가 있다면
            temp1 = i;          // 정점 u의 위치를 기억한다.
    }

    for (int i = 0; i < MAX_VERTEX; i++) // MAX_VERTEX 크기만큼 반복
    {
        if (remember_v[i] == v) // 정점 v가 있다면
            temp2 = i;          // 정점 v의 위치를 기억한다.
    }

    if (temp1 == -1 || temp2 == -1) // 정점 u 또는 v가 존재하지 않는다면
    {
        printf("그래프에 존재하지 않는 정점!"); // 그래프에 존재하지 않는다는 문구 출력
        return;
    }

    node = (GraphNode *)malloc(sizeof(GraphNode));
    // 메모리의 Heap 영역에 GraphNode 크기 만큼의 크기를 만들고, 그곳의 주소를 node에 넣는다.
    node->vertex = remember_v[temp2];
    // node가 가리키는 곳의 vertex에 remember_v[temp2]의 값을 넣는다.

    if (g->adj_list[u] == NULL) /* g가 가리키는 곳의 adj_list[u]의 값이 NULL인 경우
    즉, 정점 u에 인접리스트가 존재하지 않는 경우 */
    {
        node->link = g->adj_list[remember_v[temp1]];
        /* node가 가리키는 곳의 link에 g가 가리키는 곳의
        adj[remember_v[temp1]]의 값을 넣는다.
        node가 가리키는 곳의 link에 NULL을 넣는다는 것이다. */
        g->adj_list[remember_v[temp1]] = node;
        /* g가 가리키는 곳의 adj_list[remember_v[temp1]]에 node에 들어있는 주소를 넣는다.
        즉, 정점 u의 인접리스트에 node를 추가하는 것이다. */
    }
    else /* g가 가리키는 곳의 adj_list[u]의 값이 NULL이 아닌 경우
    즉, 정점 u에 인접리스트가 존재하는 경우 */
    {
        while (p != NULL) // p가 NULL이 아닐 때까지 반복
        {
            if (p->vertex > node->vertex)
            // p가 가리키는 곳의 vertex가 node가 가리키는 곳의 vertex보다 큰 경우
            {
                flag = TRUE; // flag를 TRUE로 바꾼다.
                break;
            }
            pre = p;     // prev에 p에 들어있는 주소를 넣는다.
            p = p->link; // p에 p가 가리키는 곳의 link에 들어있는 주소를 넣는다.
        }
        if (flag == TRUE) // flag가 TRUE인 경우. 즉, 중간에 삽입하는 경우
        {
            if (p == g->adj_list[u])
            // p와 g가 가리키는 곳의 adj_list[u]에 들어있는 주소가 같은 경우
            {
                node->link = g->adj_list[remember_v[temp1]];
                /* node가 가리키는 곳의 link에 g가 가리키는 곳의 adj_list[remember_v[temp1]]
                에 들어있는 값을 넣는다. */
                g->adj_list[remember_v[temp1]] = node;
                /* g가 가리키는 곳의 adj_list[remember_v[temp1]]에
                node에 들어있는 주소를 넣는다. */
            }
            else // p와 g가 가리키는 곳의 adj_list[u]에 들어있는 주소가 다른 경우
            {
                node->link = p; // node가 가리키는 곳의 link에 p에 들어있는 주소를 넣는다.
                pre->link = node;
                // pre가 가리키는 곳의 link에 node에 들어있는 주소를 넣는다.
            }
        }
        else // flag가 FALSE인 경우 즉, 마지막에 삽입하는 경우
        {
            node->link = NULL; // node가 가리키는 곳의 link에 NULL을 넣는다.
            pre->link = node;  // pre가 가리키는 곳의 link에 node를 넣는다.
        }
    }
}

void dfs(GraphType *g, int v) // 정점 v에서 깊이 우선 탐색
{
    GraphNode *w;      // GraphNode에 대한 포인터 w
    visited[v] = TRUE; // 시작 정점은 방문한 것으로 표시
    printf("%d ", v);  // 출력
    for (w = g->adj_list[v]; w; w = w->link)
    // w가 g가 가리키는 곳의 v의 인접리스트부터 w가 NULL일 때까지 반복
    {
        if (!visited[w->vertex]) // 만약 w가 가리키는 곳의 vertex가 방문하지 않은 노드인 경우
        {
            dfs(g, w->vertex); // dfs 함수 호출
        }
    }
}

void bfs(GraphType *g, int v) // 정점 v에서 너비 우선 탐색
{
    GraphNode *w; // GraphNode에 대한 포인터 w
    QueueType cq;

    initQueue(&cq); // cQ 초기화

    visited[v] = TRUE; // 너비 우선 탐색을 시작하는 정점 v를 방문했다고 표시

    printf("%d ", v);      // v 출력
    enqueue(&cq, v);       // cq에 v를 enqueue한다.
    while (!is_empty(&cq)) // cq가 비어있지 않을 때까지 반복
    {
        v = dequeue(&cq); // cq에서 dequeue한 것을 v에 할당
        for (w = g->adj_list[v]; w; w = w->link)
            // w가 g가 가리키는 곳의 v의 인접리스트부터 w가 NULL일 때까지 반복
            if (!visited[w->vertex]) // w가 가리키는 곳의 vertex를 방문하지 않았다면
            {
                visited[w->vertex] = TRUE; // w가 가리키는 곳의 vertex를 방문했다고 표시
                printf("%d ", w->vertex);  // w가 가리키는 곳의 vertex 출력
                enqueue(&cq, w->vertex);   // w가 가리키는 곳의 vertex를 cq에 enqueue한다.
            }
    }
}

void print_adlist(GraphType *g) // 그래프의 인접리스트 출력
{
    GraphNode *p;     // GraphNode에 대한 포인터 p
    int flag = FALSE; // 출력할 것이 있는지 없는지 판별하기 위한 flag를 FALSE로 초기화

    for (int i = 0; i < MAX_VERTEX; i++) // remember_v에 저장된 정점이 있는지 탐색
    {
        if (remember_v[i] > -1) // remember_v에 저장된 정점이 있는 경우
        {
            flag = TRUE; // flag를 TRUE로 바꾼다.
        }
    }

    if (flag == FALSE) // flag가 FALSE인 경우
    {
        printf("출력할 것이 없습니다!\n"); // 출력할 것이 없다는 문구 출력
        return;
    }

    for (int i = 0; i < MAX_VERTEX; i++) // MAX_VERTEX 크기만큼 반복
    {
        if (remember_v[i] > -1) // remember_v에 정점이 저장되어있는 경우
        {
            printf("\n\t\t정점 %d의 인접 리스트", remember_v[i]);
            // remember_v에 저장된 정점 출력
            p = g->adj_list[remember_v[i]];
            /* g가 가리키는 곳의 adj_list(remember_v에 저장되어 있는 정점의 인접리스트)
            의 주소를 p에 넣는다.*/

            while (p) // p가 NULL을 가리키지 않을 때까지 반복
            {
                printf(" -> %d", p->vertex); // p가 가리키는 곳의 vertex 출력
                p = p->link;                 // p에 p가 가리키는 곳의 link에 들어있는 주소를 넣는다.
            }
            printf("\n");
        }
    }
}

void free_graph(GraphType *g) // 그래프 초기화
{
    for (int i = 0; i < MAX_VERTEX; i++) // MAX_VERTEX 크기만큼 반복
    {
        GraphNode *p = g->adj_list[i];   
        // GraphNode에 대한 포인터 p에 g가 가리키는 곳의 adj_list[i]에 들어있는 값을 넣는다.
        GraphNode *prev = NULL;         // GraphNode에 대한 포인터 prev에 NULL을 넣는다.  
        if (g->adj_list[i] != NULL)
        /* g가 가리키는 곳의 adj_list[i]가 NULL이 아닌 경우 즉, 인접리스트가 존재하는 경우다. */
        {
            while (p != NULL)   // p가 NULL일 때까지 반복
            {
                prev = p;       // prev에 p에 들어있는 주소를 넣는다.
                p = p->link;    // p에 p가 가리키는 곳의 link에 들어있는 주소를 넣는다.
                free(prev);     // prev를 해제한다.
            }
        }
    }
    free(g); // 그래프 g 해제
}