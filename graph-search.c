#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 10
#define MAX_QUEUE_SIZE 100
#define MAX_STACL_SIZE 100

int remember_v[MAX_VERTEX]; // 추가한 정점들을 기억하기 위한 배열

typedef struct graphNode{
    int vertex;
    struct graphNode* link;
}graphNode;

typedef struct graphType{
    int n;                              // 그래프의 정점의 개수
    int vertex[MAX_VERTEX];
    graphNode* adjList_H[MAX_VERTEX];
}graphType;

typedef struct{
    int queue[MAX_QUEUE_SIZE];
    int front,rear;
}QueueType;

typedef struct{
    int stack[MAX_STACL_SIZE];
    int top;
}StackType;


void initializeGraph(graphType** g);
void insertVertex(graphType* g, int v);
void insertEdge(graphType* g, int u, int v);
void print_adjList(graphType *g);

int main()
{   
   char command;
   int vertex;
   int u,v;
   int flag=0;

   graphType *g=(graphType*)malloc(sizeof(graphType));

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

        switch(command){
            case 'z': case 'Z':
                initializeGraph(&g);
                flag=1;
                break;
            case 'v': case 'V':
                if(flag == 0)
                {
                    printf("Initialize Graph를 실행해주세요!\n");
                    break;
                }
                printf("어떤 정점을 추가할 것인가요?(0 ~ 9까지의 정점만 가능) ");
                scanf("%d", &vertex);
                insertVertex(g,vertex);
                break;
            case 'e': case 'E':
                if(flag == 0)
                {
                    printf("Initialize Graph를 실행해주세요!\n");
                    break;
                }
                printf("어떤 정점을 연결할 것인가요? ");
                scanf("%d %d", &u, &v);
                insertEdge(g,u,v);
                break;
            case 'd': case 'D':
                if(flag == 0)
                {
                    printf("Initialize Graph를 실행해주세요!\n");
                    break;
                }
                //DFS();
                break;
            case 'b': case'B':
                if(flag == 0)
                {
                    printf("Initialize Graph를 실행해주세요!\n");
                    break;
                }
                //BFS();
                break;
            case 'p': case 'P':
                if(flag == 0)
                {
                    printf("Initialize Graph를 실행해주세요!\n");
                    break;
                }
                print_adjList(g);
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

void initializeGraph(graphType** g)
{
    (*g)->n=0;
    for(int v=0; v<MAX_VERTEX;v++)
        (*g)->adjList_H[v]=NULL;
}

void insertVertex(graphType* g, int v)
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
    remember_v[g->n] = v;
    g->n++;
}

void insertEdge(graphType* g, int u, int v)
{
    graphNode* node;
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

    node=(graphNode*)malloc(sizeof(graphNode));
    node->vertex=remember_v[temp2];
    node->link=g->adjList_H[remember_v[temp1]]; // 삽입 간선에 대한 노드를 첫 번째 노드로 연결
    g->adjList_H[remember_v[temp1]] = node;
}

void print_adjList(graphType *g)
{
    graphNode* p;
    for(int i=0; i< g->n; i++)
    {
        printf("\n\t\t정점 %d의 인접 리스트", remember_v[i]);
        p=g->adjList_H[remember_v[i]];

        while(p)
        {
            printf(" -> %d", p->vertex);
            p = p->link;
        }
        printf("\n");
    }
}
