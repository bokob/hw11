#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 10
#define MAX_QUEUE_SIZE 100
#define MAX_STACL_SIZE 100

int remember_v[MAX_VERTEX]; // �߰��� �������� ����ϱ� ���� �迭

typedef struct graphNode{
    int vertex;
    struct graphNode* link;
}graphNode;

typedef struct graphType{
    int n;                              // �׷����� ������ ����
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
                    printf("Initialize Graph�� �������ּ���!\n");
                    break;
                }
                printf("� ������ �߰��� ���ΰ���?(0 ~ 9������ ������ ����) ");
                scanf("%d", &vertex);
                insertVertex(g,vertex);
                break;
            case 'e': case 'E':
                if(flag == 0)
                {
                    printf("Initialize Graph�� �������ּ���!\n");
                    break;
                }
                printf("� ������ ������ ���ΰ���? ");
                scanf("%d %d", &u, &v);
                insertEdge(g,u,v);
                break;
            case 'd': case 'D':
                if(flag == 0)
                {
                    printf("Initialize Graph�� �������ּ���!\n");
                    break;
                }
                //DFS();
                break;
            case 'b': case'B':
                if(flag == 0)
                {
                    printf("Initialize Graph�� �������ּ���!\n");
                    break;
                }
                //BFS();
                break;
            case 'p': case 'P':
                if(flag == 0)
                {
                    printf("Initialize Graph�� �������ּ���!\n");
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
        printf("0 ~ 9������ ������ �ƴմϴ�!\n");
        return;
    }

    if(((g->n)+1)>MAX_VERTEX)
    {
        printf("�׷��� ������ ������ �ʰ�!\n");
        return;
    }
    remember_v[g->n] = v;
    g->n++;
}

void insertEdge(graphType* g, int u, int v)
{
    graphNode* node;
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
        printf("�׷����� �������� �ʴ� ����!"); // �׷����� �������� �ʴ´ٴ� ���� ���
        return;
    }

    node=(graphNode*)malloc(sizeof(graphNode));
    node->vertex=remember_v[temp2];
    node->link=g->adjList_H[remember_v[temp1]]; // ���� ������ ���� ��带 ù ��° ���� ����
    g->adjList_H[remember_v[temp1]] = node;
}

void print_adjList(graphType *g)
{
    graphNode* p;
    for(int i=0; i< g->n; i++)
    {
        printf("\n\t\t���� %d�� ���� ����Ʈ", remember_v[i]);
        p=g->adjList_H[remember_v[i]];

        while(p)
        {
            printf(" -> %d", p->vertex);
            p = p->link;
        }
        printf("\n");
    }
}
