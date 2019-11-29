    #include <limits.h>
    #include <stdio.h>
    #include <stdlib.h>
    int array[2000010];
    int main()
    {
        int n;
        scanf("%d", &n);
        int front = 1000005;
        int back = front + 1;
        char task[10];
        int flag = 1;
        int x;
        while (n--)
        {
            scanf("%s", task);
            //printf("%s\n", task);
            if (task[0] == 't')
            {
                scanf("%d", &x);
                if (flag == 1)
                    array[++front] = x;
                else
                    array[--back] = x;
            }
            if (task[0] == 'p')
            {
                scanf("%d", &x);
                if (flag == -1)
                    array[++front] = x;
                else
                    array[--back] = x;
            }
            if (task[0] == 'f')
            {
                if (back > front)
                    printf("No job for Ada?\n");
                else
                {
                    if (flag == 1)
                        printf("%d\n", array[front--]);
                    else
                        printf("%d\n", array[back++]);
                }
            }
            if (task[0] == 'b')
            {
                if (back > front)
                    printf("No job for Ada?\n");
                else
                {
                    if (flag == -1)
                        printf("%d\n", array[front--]);
                    else
                        printf("%d\n", array[back++]);
                }
            }
            if (task[0] == 'r')
            {
     
                flag *= -1;
            }
        }
        return 0;
    }