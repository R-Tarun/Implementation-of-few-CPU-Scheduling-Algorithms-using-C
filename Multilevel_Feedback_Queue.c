#include <stdio.h>
#include <stdlib.h>
 

struct QNode {
    int pid,bt,at,b;
    struct QNode* next;
};
 
float avwt,avtt;

struct process
{
    int pid,bt,at,b;
};

struct Queue {
    struct QNode *front, *rear;
};
 
struct QNode* newNode(int pid, int at, int bt, int b)
{
    struct QNode* temp = (struct QNode*)malloc(sizeof(struct QNode));
    temp->pid = pid;
    temp->at = at;
    temp->bt = bt;
    temp->b = b;
    temp->next = NULL;
    return temp;
}
 

struct Queue* createQueue()
{
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}
 

void enQueue(struct Queue* q, int pid, int at, int bt, int b)
{
    struct QNode* temp = newNode(pid, at, bt, b);
 
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}
 
void display(struct Queue* q)
{
    struct QNode* temp = (struct QNode*)malloc(sizeof(struct QNode));
    temp = q->front;
    if ((temp == NULL) && (q->rear == NULL))
    {
        printf("Queue is empty");
        return;
    }
    while (temp != q->rear)
    {
        printf("P[%d]\t%d\t%d\n", temp->pid,temp->at,temp->bt);
        temp = temp->next;
    }
    if (temp == q->rear){
        printf("P[%d]\t%d\t%d\n", temp->pid,temp->at,temp->bt);
    }
}

struct QNode* deQueue(struct Queue* q)
{
    if (q->front == NULL) {
        return NULL;
    }
    struct QNode* temp = q->front;
    q->front = q->front->next;
 
    if (q->front == NULL) {
        q->rear = NULL;
    }
    return temp;
}

int empty(struct Queue* q)
{
    if ((q->front == NULL) && (q->rear == NULL)){
        return 0;
    }
    else{
        return 1;
    }
}

int rrs(struct Queue* q, struct Queue* q1, int qt, int t)
{
    int w,tt,s;
    struct QNode *tem;
    //struct QNode *temp = (struct QNode*)malloc(sizeof(struct QNode));
    while(empty(q)){
        tem=deQueue(q);
        //printf("%d %d\n",tem->at,tem->bt);
        if ((tem->bt)<=qt){
            t+=tem->bt;
            w=t-tem->b-tem->at;
            tt=w+tem->b;
            avwt+=w;
            avtt+=tt;
            printf("p[%d]\t%d\t%d\t%d\t%d\t\t%d\n",tem->pid,tem->at,tem->b,w,tt,t);
        }else{
            tem->bt-=qt;
            t+=qt;
            enQueue(q1,tem->pid,tem->at,tem->bt,tem->b);        
        }
    }
    //printf("\nAverage Wait Time: %d",avwt/n);
    //printf("\nAverage TurnAround Time: %d\n",avtt/n);
    return t;
}

void sort(int m, struct process x[])
{                                                          
    int i, j;
    struct process t;
                                                               
    for(i = 1; i <= m-1; i++){                              
        for(j = 1; j <= m-i; j++){                            
            if(x[j-1].at > x[j].at)                                
            {
                t = x[j-1];                                    
                x[j-1] = x[j];                                
                x[j] = t;                                      
            }
           
        }  
       
    }
}


 
int main()
{
    struct Queue* q1 = createQueue();
    struct Queue* q2 = createQueue();
    struct Queue* q3 = createQueue();
    struct process x[10];
    int n,t1,t2;
    printf("Enter no. of processes: ");
    scanf("%d",&n);
    for (int i=0; i<n; i++){
        printf("\nEnter arrival and burst time: ");
        scanf("%d %d",&x[i].at,&x[i].bt);
        x[i].b=x[i].bt;
        x[i].pid=i+1;
    }
    sort(n,x);
    for (int i=0; i<n; i++){
       enQueue(q1,x[i].pid,x[i].at,x[i].bt,x[i].b);
       printf("P[%d]\t%d\t%d\n",x[i].pid,x[i].at,x[i].bt);
    }
    printf("\nProcess\tArrival\tBurst\tWait\tTurnAround\tComplete\n");
    t1=rrs(q1,q2,4,0);
    t2=rrs(q2,q3,8,t1);
    rrs(q3,q3,12,t2);
    printf("\nAverage Wait Time: %.2f",avwt/n);
    printf("\nAverage TurnAround Time: %.2f\n",avtt/n);
    return 0;
} 
