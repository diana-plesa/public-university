#include <stdio.h>
#include <string.h>
#define MAX 100

int queue[MAX];
int front = -1;
int rear = -1;

void enqueue(int number)
{
    if (front == -1)
    {
        front++;
    }
    rear++;
    queue[rear] = number;
}

int dequeue()
{
    if (rear == -1)
    {
        printf("Can not remove an element. Empty queue\n");
        return 0;
    }

    int element = queue[front];
    front++;

    if(front > rear)
    {
        front = -1;
        rear = -1;
    }
    
    return element;
}

void display_queue_content()
{
    if(front == -1)
    {
        printf("Empty queue\n");
        return;
    }

    for (int i = front; i <= rear; i++)
    {
        printf("%d ", queue[i]);
    }
    printf("\n");
}

int main()
{
    int x = 1, y = 2;

    enqueue(x);
    enqueue(y);
    display_queue_content();
    dequeue(x);
    display_queue_content();

    return 0;
}