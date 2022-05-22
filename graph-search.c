#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0 

#define MAX_VERTEX 10

int remember_v[MAX_VERTEX]; // 추가한 정점들을 기억하기 위한 배열

int visited[MAX_VERTEX];
 
typedef struct GraphNode{
	int vertex;
	struct GraphNode *link;
}GraphNode;

typedef struct GraphType{
	int n; // 정점의개수    
	GraphNode *adj_list[MAX_VERTEX];
}GraphType;

typedef struct QueueType{
	int element[MAX_VERTEX];
	int front, rear;
	int size;
}QueueType;

void initQueue(QueueType *q);
void enqueue(QueueType *q, int item);
int dequeue(QueueType *q);

void initialize_graph(GraphType **g);
void dfs(GraphType *g, int v);

void insert_vertex(GraphType *g, int v);
void insert_edge(GraphType *g, int u, int v);
void bfs(GraphType *g, int v);
void print_adlist(GraphType *g);

int main(){

    /*
	
	int i;
	GraphType g;
	graph_init(&g);
	for(i = 0; i<6;i++){
		insert_vertex(&g, i);
	}
	
	insert_edge(&g,0,1);
	insert_edge(&g,1,0);
	insert_edge(&g,0,5);
	insert_edge(&g,5,0);
	insert_edge(&g,1,2);
	insert_edge(&g,2,1);
	insert_edge(&g,2,3);
	insert_edge(&g,3,2);
	insert_edge(&g,3,4);
	insert_edge(&g,4,3);
	insert_edge(&g,2,5);
	insert_edge(&g,5,2);
	
    DFS(&g,1);
    for(int i=0; i<MAX_VERTICSES; i++)
    {
        visited[i]=0;
    }
    printf("\n");
    BFS(&g,2);
	
	
	for(int i = 0 ; i<7;i++){
	print_adlist(&g,i);	
	}
    */

   char command;
   int vertex;
   int u,v;
   int initflag=0;
   int search_start;

   GraphType *g=(GraphType*)malloc(sizeof(GraphType));

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

        int search_flag=0;

        switch(command){
            case 'z': case 'Z':
                initialize_graph(&g);
                initflag=1;
                break;
            case 'v': case 'V':
                if(initflag == 0)
                {
                    printf("Initialize Graph를 실행해주세요!\n");
                    break;
                }
                printf("어떤 정점을 추가할 것인가요?(0 ~ 9까지의 정점만 가능) ");
                scanf("%d", &vertex);
                insert_vertex(g,vertex);
                break;
            case 'e': case 'E':
                if(initflag == 0)
                {
                    printf("Initialize Graph를 실행해주세요!\n");
                    break;
                }
                printf("어떤 정점을 연결할 것인가요? ");
                scanf("%d %d", &u, &v);
                insert_edge(g,u,v);
                break;
            case 'd': case 'D':
                if(initflag == 0)
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
                        search_flag=1;
                    }
                }
                if(search_flag == 0)
                    break;
                dfs(g,1);
                break;
            case 'b': case'B':
                if(initflag == 0)
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
                        search_flag=1;
                    }
                }
                if(search_flag == 0)
                    break;
                bfs(g,1);
                break;
            case 'p': case 'P':
                if(initflag == 0)
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

void initQueue(QueueType *q){
	q->size = 0 ;
	q->front = -1;
	q->rear = -1;
	for(int i =0; i<MAX_VERTEX; i++)
		q->element[i] = 0 ;
}

void enqueue(QueueType *q, int item){
	q->element[ ++(q->rear) ] = item;
	q->size++ ;
}

int dequeue(QueueType *q){
	int item;
	item = q->element[++(q->front)];
	q->size--;
	return item;
}

void initialize_graph(GraphType** g)
{	
	(*g)->n = 0;
	for(int v=0; v<MAX_VERTEX; v++)
		(*g)->adj_list[v] = NULL;	
}

void insert_vertex(GraphType *g, int v){

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

void insert_edge(GraphType *g, int u, int v){
	GraphNode *node;

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
	node->link = g->adj_list[remember_v[temp1]];
	g->adj_list[remember_v[temp1]] = node; 
}

void dfs(GraphType *g, int v){
	GraphNode *w;
	visited[v] = 1;
	printf("%d ", v);
	for(w = g->adj_list[v]; w; w = w->link){
		if(!visited[w->vertex]){
			dfs(g,w->vertex);	
		}
	}
}

void bfs(GraphType *g, int v){
	GraphNode *w;
	QueueType q;
	initQueue(&q);
	visited[v] = TRUE;
	printf("%d ",v);
	enqueue(&q, v);
	while(q.size != 0){
		v = dequeue(&q);
		for(w =g->adj_list[v]; w; w= w->link)
			if(!visited[w->vertex]){
				visited[w->vertex] = TRUE;
				printf("%d ",w->vertex);
				enqueue(&q, w->vertex);
			}
	}
}

void print_adlist(GraphType *g){
	GraphNode *p;
	
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