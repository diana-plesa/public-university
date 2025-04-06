#include <stdio.h>
#include <stdlib.h>

int *queue = NULL;
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

int peek()
{
    if (front == -1 || front > rear)
    {
        printf("No elements in queue");
        return 0;
    }

    return queue[front];
}

int main()
{
    int n = 0;

    printf("Type n: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
            queue = realloc(queue, (i + 1) * sizeof(int));

            if (queue == NULL)
            {
                perror("queue realloc error");
                exit(-1);
            }

            int x = 0;
            printf("Type x: ");
            scanf("%d", &x);
            enqueue(x);
    }
    display_queue_content();
    dequeue(peek());
    display_queue_content();
    free(queue);
    return 0;
}