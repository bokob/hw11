#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0 

#define MAX_VERTEX 10

int remember_v[MAX_VERTEX]; // �߰��� �������� ����ϱ� ���� �迭. �ڽ��� �߰��� ������ ��������Ʈ�� ��µǰ� �ϱ� ���� ���� �迭�̴�.

int visited[MAX_VERTEX];
 
typedef struct GraphNode{
	int vertex;
	struct GraphNode *link;
}GraphNode;

typedef struct GraphType{
	int n; // �����ǰ���    
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

int insertList(GraphType *g, int x);

int main()
{
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
                    printf("Initialize Graph�� �������ּ���!\n");
                    break;
                }
                printf("� ������ �߰��� ���ΰ���?(0 ~ 9������ ������ ����) ");
                scanf("%d", &vertex);
                insert_vertex(g,vertex);
                break;
            case 'e': case 'E':
                if(initflag == 0)
                {
                    printf("Initialize Graph�� �������ּ���!\n");
                    break;
                }
                printf("� ������ ������ ���ΰ���? ");
                scanf("%d %d", &u, &v);
                insert_edge(g,u,v);
                break;
            case 'd': case 'D':
                if(initflag == 0)
                {
                    printf("Initialize Graph�� �������ּ���!\n");
                    break;
                }
                printf("DFS�� ������ ������ �Է��ϼ���. ");
                scanf("%d", &search_start);
                for(int i=0;i<MAX_VERTEX;i++)
                {
                    if(search_start == remember_v[i])
                    {
                        search_flag=1;
                    }
                }
                if(search_flag == 0)
                {
                    printf("������ �� ���� �����Դϴ�!\n");
                    break;
                }
                dfs(g,search_start);
                for(int i=0; i<MAX_VERTEX; i++)
                {
                    visited[i]=FALSE;
                }
                break;
            case 'b': case'B':
                if(initflag == 0)
                {
                    printf("Initialize Graph�� �������ּ���!\n");
                    break;
                }
                printf("BFS�� ������ ������ �Է��ϼ���. ");
                scanf("%d", &search_start);
                for(int i=0;i<MAX_VERTEX;i++)
                {
                    if(search_start == remember_v[i])
                    {
                        search_flag=1;
                    }
                }
                if(search_flag == 0)
                {   
                    printf("������ �� ���� �����Դϴ�!\n");
                    break;
                }
                bfs(g,search_start);
                for(int i=0; i<MAX_VERTEX; i++)
                {
                    visited[i]=FALSE;
                }
                break;
            case 'p': case 'P':
                if(initflag == 0)
                {
                    printf("Initialize Graph�� �������ּ���!\n");
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
    {
		(*g)->adj_list[v] = NULL;
        remember_v[v]=-1;
    }
}

void insert_vertex(GraphType *g, int v){

    if(v<0 || 9<v)
    {       
        printf("0 ~ 9������ ������ �ƴմϴ�!\n");
        return;
    }

    if(((g->n)+1)>MAX_VERTEX)
    {
        printf("�׷��� ������ ������ �ʰ�!\n");
        return;
    }
    for(int i=0; i<MAX_VERTEX;i++)
    {
        if(v == remember_v[i])
        {
            printf("�̹� �߰��� �����Դϴ�!\n");
            return;
        }
    }
    remember_v[g->n] = v;
	g->n++;
} 

void insert_edge(GraphType *g, int u, int v){
	GraphNode *node;

    int temp1=-1;       // ���� u�� �ִ��� �Ǻ��ϱ� ���� ����
    int temp2=-1;       // ���� v�� �ִ��� �Ǻ��ϱ� ���� ����

    for(int i=0; i < MAX_VERTEX; i++)   // �߰��� �������� �ִ� �迭���� ���� u�� �ִ��� Ž��
    {
        if(remember_v[i] == u)  // ���� u�� �ִٸ� 
            temp1=i;            // ���� u�� ��ġ�� ����Ѵ�.
    }

    for(int i=0; i< MAX_VERTEX; i++)    // �߰��� �������� �ִ� �迭���� ���� v�� �ִ��� Ž��
    {
        if(remember_v[i] == v)          // ���� v�� �ִٸ�
            temp2=i;                    // ���� v�� ��ġ�� ����Ѵ�.
    }

    if(temp1 == -1 || temp2 == -1)      // ���� u �Ǵ� v�� �������� �ʴ´ٸ�
    {
        printf("�׷����� �������� �ʴ� ����!\n"); // �׷����� �������� �ʴ´ٴ� ���� ���
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
	
    if(remember_v[0] == -1)
    {
        printf("����� ���� �����ϴ�!\n");
        return;
    }

    

   for(int i=0; i< g->n; i++)
    {
        printf("\n\t\t���� %d�� ���� ����Ʈ", remember_v[i]);
        p=g->adj_list[remember_v[i]];

        while(p)
        {
            printf(" -> %d", p->vertex);
            p = p->link;
        }
        printf("\n");
    }
}

/*
int insertList(GraphType *g, int x)
{
    GraphNode *node = (GraphNode*)malloc(sizeof(GraphNode));

    node->vertex=key;
    node->link=NULL;

    if(g->adj_list)
}
*/