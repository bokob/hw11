#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0 

#define MAX_VERTEX 10

int remember_v[MAX_VERTEX]; // 추가한 정점들을 기억하기 위한 배열. 자신이 추가한 정점과 인접리스트만 출력되게 하기 위해 쓰일 배열이다.

int visited[MAX_VERTEX];
 
typedef struct GraphNode
{
	int vertex;
	struct GraphNode *link;
}GraphNode;

typedef struct GraphType
{
	int n; // 정점의개수    
	GraphNode *adj_list[MAX_VERTEX];
}GraphType;

typedef struct QueueType
{
	int element[MAX_VERTEX];
	int front, rear;
}QueueType;

void initQueue(QueueType *q);
int is_emmpty(QueueType* q);
int is_full(QueueType *q);
void enqueue(QueueType *q, int item);
int dequeue(QueueType *q);

void initialize_graph(GraphType **g);
void dfs(GraphType *g, int v);
void insert_vertex(GraphType *g, int v);
void insert_edge(GraphType *g, int u, int v);
void bfs(GraphType *g, int v);
void print_adlist(GraphType *g);

int insertList(GraphType *g, int x);

int main()
{
   char command;
   int vertex;
   int u,v;
   int initflag=FALSE;
   int search_start;

   GraphType *g=(GraphType*)malloc(sizeof(GraphType));

   printf("[-------------------- [복무창] [2021040021] --------------------]");
   
   do{
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

        int search_flag=FALSE;

        switch(command){
            case 'z': case 'Z':
                initialize_graph(&g);
                initflag=1;
                break;
            case 'v': case 'V':
                if(initflag == FALSE)
                {
                    printf("Initialize Graph를 실행해주세요!\n");
                    break;
                }
                printf("어떤 정점을 추가할 것인가요?(0 ~ 9까지의 정점만 가능) ");
                scanf("%d", &vertex);
                insert_vertex(g,vertex);
                break;
            case 'e': case 'E':
                if(initflag == FALSE)
                {
                    printf("Initialize Graph를 실행해주세요!\n");
                    break;
                }
                printf("어떤 정점을 연결할 것인가요? ");
                scanf("%d %d", &u, &v);
                insert_edge(g,u,v);
                break;
            case 'd': case 'D':
                if(initflag == FALSE)
                {
                    printf("Initialize Graph를 실행해주세요!\n");
                    break;
                }
                printf("DFS를 시작할 정점을 입력하세요. ");
                scanf("%d", &search_start);
                for(int i=0;i<MAX_VERTEX;i++)
                {
                    if(search_start == remember_v[i])
                    {
                        search_flag=TRUE;
                    }
                }
                if(search_flag == FALSE)
                {
                    printf("시작할 수 없는 정점입니다!\n");
                    break;
                }
                dfs(g,search_start);
                for(int i=0; i<MAX_VERTEX; i++)
                {
                    visited[i]=FALSE;
                }
                break;
            case 'b': case'B':
                if(initflag == FALSE)
                {
                    printf("Initialize Graph를 실행해주세요!\n");
                    break;
                }
                printf("BFS를 시작할 정점을 입력하세요. ");
                scanf("%d", &search_start);
                for(int i=0;i<MAX_VERTEX;i++)
                {
                    if(search_start == remember_v[i])
                    {
                        search_flag=TRUE;
                    }
                }
                if(search_flag == FALSE)
                {   
                    printf("시작할 수 없는 정점입니다!\n");
                    break;
                }
                bfs(g,search_start);
                for(int i=0; i<MAX_VERTEX; i++)
                {
                    visited[i]=FALSE;
                }
                break;
            case 'p': case 'P':
                if(initflag == FALSE)
                {
                    printf("Initialize Graph를 실행해주세요!\n");
                    break;
                }
                print_adlist(g);
                break;
            case 'q': case 'Q':
                free(g);
                break;
            default:
                printf("\n       >>>>>   Concentration!!   <<<<<     \n");
                break;
        }
    }while(command != 'q' && command != 'Q');

    return 0; 
}

void initQueue(QueueType *q)
{
	q->front = q->rear = 0;
}

int is_empty(QueueType* q)  //공백 상태 검출 함수 
{
	return (q->front == q->rear);
}

int is_full(QueueType* q)   //포화 상태 검출 함수 
{
	return ((q->rear + 1) % MAX_VERTEX == q->front);
}


void enqueue(QueueType *q, int item)
{
	if (is_full(q)) {
		fprintf(stderr,"큐가 가득참!\n");
        return;
	}
	else
		q->rear = (q->rear + 1) % MAX_VERTEX;
	
    q->element[q->rear] = item;
}

int dequeue(QueueType *q)
{
	if (is_empty(q)) 
    {
		fprintf(stderr,"큐가 비었음!\n");
	}
	else
		q->front = (q->front + 1) % MAX_VERTEX;
	
    return q->element[q->front];
}

void initialize_graph(GraphType** g)
{	
	(*g)->n = 0;
	for(int v=0; v<MAX_VERTEX; v++)
    {
		(*g)->adj_list[v] = NULL;
        remember_v[v] = -1;
    }
}

void insert_vertex(GraphType *g, int v)
{

    if(v<0 || 9<v)
    {       
        printf("0 ~ 9까지의 정점이 아닙니다!\n");
        return;
    }

    if(((g->n)+1)>MAX_VERTEX)
    {
        printf("그래프 정점의 개수를 초과!\n");
        return;
    }
    for(int i=0; i<MAX_VERTEX;i++)
    {
        if(v == remember_v[i])
        {
            printf("이미 추가된 정점입니다!\n");
            return;
        }
    }
    remember_v[g->n] = v;
	g->n++;
} 

void insert_edge(GraphType *g, int u, int v)
{ 
	GraphNode* node; 
	GraphNode* p = g->adj_list[u];
	GraphNode* pre = NULL;
	int flag = 0;

    int temp1=-1;       // 정점 u가 있는지 판별하기 위한 변수
    int temp2=-1;       // 정점 v가 있는지 판별하기 위한 변수

    for(int i=0; i < MAX_VERTEX; i++)   // 추가한 정점들이 있는 배열에서 정점 u가 있는지 탐색
    {
        if(remember_v[i] == u)  // 정점 u가 있다면 
            temp1=i;            // 정점 u의 위치를 기억한다.
    }

    for(int i=0; i< MAX_VERTEX; i++)    // 추가한 정점들이 있는 배열에서 정점 v가 있는지 탐색
    {
        if(remember_v[i] == v)          // 정점 v가 있다면
            temp2=i;                    // 정점 v의 위치를 기억한다.
    }

    if(temp1 == -1 || temp2 == -1)      // 정점 u 또는 v가 존재하지 않는다면
    {
        printf("그래프에 존재하지 않는 정점!"); // 그래프에 존재하지 않는다는 문구 출력
        return;
    }
	
	node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = remember_v[temp2];

	if (g->adj_list[u] == NULL) //처음 insert 
    {
		node->link = g->adj_list[remember_v[temp1]];
	    g->adj_list[remember_v[temp1]] = node; 
	}
	else
    {
		while (p != NULL) 
        {
			if (p->vertex > node->vertex) 
            {
				flag = 1;				
				break;
			}
			pre = p;
			p = p->link;
			
		}
		if (flag == 1)  //중간에 삽입해야함 
        {
			
			if (p == g->adj_list[u]) {
				node->link = g->adj_list[remember_v[temp1]];
	            g->adj_list[remember_v[temp1]] = node; 
			}
			else 
            {
				node->link = p;
				pre->link = node;
			}
		}
		else 
        {
			node->link = NULL;
			pre->link = node;
		}
	}
}

void dfs(GraphType *g, int v)
{
	GraphNode *w;
	visited[v] = TRUE;
	printf("%d ", v);
	for(w = g->adj_list[v]; w; w = w->link){
		if(!visited[w->vertex]){
			dfs(g,w->vertex);	
		}
	}
}

void bfs(GraphType *g, int v)
{
	GraphNode *w;
	QueueType q;

	initQueue(&q);

	visited[v] = TRUE;

	printf("%d ",v);
	enqueue(&q, v);
	while(!is_empty(&q))
    {
		v = dequeue(&q);
		for(w =g->adj_list[v]; w; w= w->link)
			if(!visited[w->vertex])
            {
				visited[w->vertex] = TRUE;
				printf("%d ",w->vertex);
				enqueue(&q, w->vertex);
			}
	}
}

void print_adlist(GraphType *g)
{
	GraphNode *p;
	
    if(remember_v[0] == -1)
    {
        printf("출력할 것이 없습니다!\n");
        return;
    }

   for(int i=0; i< g->n; i++)
    {
        printf("\n\t\t정점 %d의 인접 리스트", remember_v[i]);
        p=g->adj_list[remember_v[i]];

        while(p)
        {
            printf(" -> %d", p->vertex);
            p = p->link;
        }
        printf("\n");
    }
}