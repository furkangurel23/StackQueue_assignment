#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef int bool;
#define true 1
#define false 0

/*Stack*/
typedef struct Stack //a structure to represent stack
{
    int top;
    int size;
    char* array;
};
struct Stack* createStack(int size)
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->size=size;
    stack->top=-1;
    stack->array=(char*)malloc(stack->size * sizeof(char));
    return stack;
};

bool isFull(struct Stack* stack) //Stack is full when the top equals to size.
{
    return ((stack->size)-1==stack->top)? true:false;

}
bool isEmpty(struct Stack* stack) //Stack is empty if top equals to minus one.
{
    return (stack->top==-1) ? true:false;
}
void Push(struct Stack* stack, char x) //Append an element to stack
{
    if(isFull(stack)==true)
    {
        printf("Stack is overflow!\n");
        return;
    }
    else
    {
        stack->array[++stack->top]=x;
    }
}
void Pop(struct Stack* stack) //Delete an element from stack.
{
    if(isEmpty(stack)==true)
    {
        printf("Stack is empty!\n");
        return;
    }
    else
    {
        stack->array[stack->top--];
    }
}
char Top(struct Stack* stack)
{
    if(isEmpty(stack)==true)
    {
        printf("Stack is empty!\n");
        return;
    }
    else
    {
        return stack->array[stack->top];
    }
}
void printStack(struct Stack* stack)
{
    int i;
    printf("Stack: ");
    for(i=0; i<=stack->top; i++)
    {
        printf("%c ",stack->array[i]);
    }
    printf("\n");
}
/*Queue*/
typedef struct Queue //a stack to represent queue
{
    int front;
    int rear;
    int size;
    char* array;
};
struct Queue* createQueue(int size) //function to create a queue given size
{
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->size=size;
    queue->front=queue->rear=-1;
    queue->array=(char*)malloc(queue->size * sizeof(char));
    return queue;
};
bool queueIsFull(struct Queue* queue) //Queue is full when rear equals to front.
{
    if((queue->rear+1)%queue->size==queue->front)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool queueIsEmpty(struct Queue* queue) //Queue is empty if rear and front equals to minus one.
{
    return (queue->rear == -1 && queue->front== -1)? true: false;
}
void Enqueue(struct Queue* queue, char x) //Adding an item to the queue.
{
    if(queueIsFull(queue)== true){printf("Queue is overflow!\n ");return ;}
    else if(queueIsEmpty(queue)== true)
    {
        queue->front =queue->rear = 0;
    }
    else
    {
        queue->rear=(queue->rear+1)%queue->size;
    }
    queue->array[queue->rear]=x;
}
void Dequeue(struct Queue* queue) //Deleting an item from the queue.
{
    if(queueIsEmpty(queue)==true){printf("Queue is empty!\n");return;}
    else if(queue->rear==queue->front)
    {
        queue->rear=queue->front=-1;
    }
    else
    {
        queue->front=(queue->front+1)%queue->size;
    }
}
char Front(struct Queue* queue) // Function to get front of queue
{
    if(queueIsEmpty(queue)==true){printf("Queue is empty!\n");return -1;}
    else
    {
        return queue->array[queue->front];
    }
}
char Rear(struct Queue* queue) // Function to get rear of queue
{
    if(queueIsEmpty(queue)==true){printf("Queue is empty!\n");return 1;}
    else
    {
        return queue->array[queue->rear];
    }
}
void printQueue(struct Queue* queue)
{
    int i;
    int count = (queue->rear+queue->size - queue->front)%queue->size + 1;
    printf("Queue: ");
    for(i=0; i< count; i++)
    {
        int index = (queue->front+i)%queue->size;
        printf("%c ", queue->array[index]);
    }
    printf("\n");
}
struct Server
{
    struct Queue* queue;
    struct Stack* stack;
    char* past;
    int pasTop;
};
struct Client
{
    struct Queue* queue;
    struct Stack* stack;
    char* past;
    int pastTop;

};
void pushClientPast(struct Client* client, char x)
{
    client->past[++client->pastTop]=x;
}
void pushServerPast(struct Server* server, char x)
{
    server->past[++server->pasTop]=x;
}
int main(int argv,char*argc[])
{
    FILE *file1;
    file1 = fopen(argc[1],"r");
    int* singleLine[50];
    if(file1==NULL)
    {
        printf("File not found!\n");
    }
    else
    {
        int line;int count=0;int countLine=0;
        int serverAndClientCount;
        while(fscanf(file1,"%d",&line)==1)
        {
            if(feof(file1))
            {
                puts("EOF");
            }
            count++;
            if(count==1)
            {
                serverAndClientCount=line;
            }
            else
            {
                singleLine[countLine]=line;
                countLine++;
            }
        }
        struct Server server;
        struct Client clients[serverAndClientCount-1];
        int i; int q;
        for(i=0;singleLine[i]<50; ++i);
        int a=0;
        for(q=0; q<i;q=q+2)
        {
            if(q+2>=i)
            {
                server.queue=createQueue(singleLine[q]);
                server.stack=createStack(singleLine[q+1]);
                server.pasTop=-1;
                break;
            }
            else
            {
                struct Client client;
                client.queue=createQueue(singleLine[q]);
                client.stack=createStack(singleLine[q+1]);
                client.pastTop=-1;
                clients[a]=client;
                a++;
            }
        }
        FILE* file2;
        file2 = fopen(argc[2],"r");
        if(file2==NULL)
        {
            printf("File could not found!");
        }
        else
        {
            char teksatir[800];int linecount=0;int m=0; int b=0;
            char ch,ch2,ch3;
            for(m=0;fgets(teksatir,sizeof(teksatir),file2) !=NULL;m++)
            {
                if(linecount==0)
                {
                    int satir = atoi(teksatir);
                    server.past=(char*)malloc(satir*sizeof(char));
                    int d;
                    for(d=0; d<a;d++)
                    {
                        clients[d].past=(char*)malloc(satir*sizeof(char));
                    }
                }
                else
                {
                    if(sscanf(teksatir,"%c %c %c",&ch,&ch2,&ch3)==3)
                    {
                        if(ch=='A')
                        {
                            int c=ch2-'0';
                            if(queueIsFull(clients[c-1].queue)==true){pushClientPast(&clients[c-1],'1'); }
                            else
                            {
                                Enqueue(clients[c-1].queue,ch3);
                            }
                        }
                        else if(ch=='I')
                        {
                            int c=ch2-'0';
                            if(c==serverAndClientCount)
                            {
                                if(isFull(server.stack)==true){pushServerPast(&server,'2');}
                                else
                                {
                                    Push(server.stack,ch3);
                                }
                            }
                            else if(c!=serverAndClientCount)
                            {
                                if(isFull(clients[c-1].stack)==true){pushClientPast(&clients[c-1],'2');}
                                else
                                {
                                    Push(clients[c-1].stack,ch3);
                                }
                            }
                        }
                        else if(ch=='S')//clientten veri al server queue ya gönder. önceligin client stack daha sonrasinda client queue.
                        {
                            int c = ch2-'0';
                            if(queueIsFull(server.queue)==false)
                            {
                                if(isEmpty(clients[c-1].stack)==false)
                                {
                                    Enqueue(server.queue,Top(clients[c-1].stack));
                                    pushClientPast(&clients[c-1],Top(clients[c-1].stack));
                                    Pop(clients[c-1].stack);
                                }
                                else if(isEmpty(clients[c-1].stack)==true && queueIsEmpty(clients[c-1].queue)==false)
                                {
                                    Enqueue(server.queue,Front(clients[c-1].queue));
                                    pushClientPast(&clients[c-1],Front(clients[c-1].queue));
                                    Dequeue(clients[c-1].queue);
                                }
                                else if(isEmpty(clients[c-1].stack)==true && queueIsEmpty(clients[c-1].queue)==true)
                                {
                                    pushClientPast(&clients[c-1],'3');
                                }
                            }
                            else
                            {
                                if(isEmpty(clients[c-1].stack)==false)
                                {
                                    pushClientPast(&clients[c-1],Top(clients[c-1].stack));
                                    Pop(clients[c-1].stack);
                                    pushServerPast(&server,'1');
                                }
                                else if(isEmpty(clients[c-1].stack)==true && queueIsEmpty(clients[c-1].queue)==false)
                                {
                                    pushClientPast(&clients[c-1],Front(clients[c-1].queue));
                                    Dequeue(clients[c-1].queue);
                                    pushServerPast(&server,'1');
                                }
                                else if(isEmpty(clients[c-1].stack)==true && queueIsEmpty(clients[c-1].queue)==true)
                                {
                                    pushClientPast(&clients[c-1],'3');
                                }
                            }
                        }
                        else if(ch=='O')
                        {
                            if(isEmpty(server.stack)==false)
                            {
                                pushServerPast(&server,Top(server.stack));
                                Pop(server.stack);
                            }
                            else if(isEmpty(server.stack)==true && queueIsEmpty(server.queue)==false)
                            {
                                pushServerPast(&server,Front(server.queue));
                                Dequeue(server.queue);
                            }

                            else if(queueIsEmpty(server.queue)==true && isEmpty(server.stack)==true)
                            {
                                pushServerPast(&server,'3');
                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                }
                linecount++;
            }
        }
        int u,e;
        for(u=0; u<a; u++)
        {
            for(e=0; e<=clients[u].pastTop; e++)
            {
                printf("%c ",clients[u].past[e]);
            }
            printf("\n");
        }
        int y;
        for(y=0; y<=server.pasTop;y++)
        {
            printf("%c ",server.past[y]);
        }
        fclose(file2);
    }
    fclose(file1);
    return 0;
}
