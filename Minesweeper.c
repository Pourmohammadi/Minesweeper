#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct cell
{
    int state;
    int flag;
    int value;
    int mine;
}c[32][32];


void zero (int x,int y)
{
    if (c[x][y].value != 0 || c[x][y].state)
    {
        c[x][y].state = 1;
        return ;
    }
    else
    {
        c[x][y].state = 1;
        zero((x-1),(y-1));
        zero((x-1),(y));
        zero((x-1),(y+1));
        zero((x),(y-1));
        zero((x),(y+1));
        zero((x+1),(y-1));
        zero((x+1),(y));
        zero((x+1),(y+1));
    }
}

int main()
{
    char name[20];
    printf("enter your username  ");
    scanf("%s",name);

    restart:
    system("cls");
    for (int i = 0 ; i < 32 ; ++i)
    {
        for (int j = 0 ; j < 32 ; ++j)
        {
            c[i][j].state = 0;
            c[i][j].flag = 0;
            c[i][j].value = 0;
            c[i][j].mine = 0;
        }
    }

    int count = 0;
    srand(time(0));
    while(count<100)
    {
        int x = (rand()%30)+1;
        int y = (rand()%30)+1;
        if (c[x][y].mine == 0)
        {
            c[x][y].mine = 1;
            c[x][y].value = 9;
            count += 1;
        }
    }


    for (int i = 1 ; i <= 30 ; ++i)
    {
        for (int j = 1 ; j <= 30 ; ++j)
        {
            if (c[i][j].mine==0)
            {
                count = 0 ;
                for (int x = i-1 ; x <= i+1 ; ++x)
                    for (int y = j-1 ; y <= j+1 ; ++y)
                        count += c[x][y].mine;
                c[i][j].value = count;
            }

        }

    }

    for (int i = 0 ; i <= 31 ; ++i)
    {
        c[0][i].value = 9;
        c[31][i].value = 9;
        c[i][0].value = 9;
        c[i][31].value = 9;
    }

    int x,y,z,opened;

    while(1)
    {
        opened = 0;
        system("cls");
        for (int i = 1 ; i <= 30 ; ++i)
        {
            for (int j = 1 ; j <= 30 ; ++j)
            {
                if (c[i][j].state==1)
                    {
                        printf("[%d]  ",c[i][j].value);
                        opened += 1;
                    }
                else if (c[i][j].flag==1)
                    printf("[#]  ");
                else
                    printf("[ ]  ");
            }
            printf("\n\n");
        }
        if (opened == 880)
        {
            system("cls");
            break;
        }
        printf("username: %s\t\t\t\t\t\t\t\tscore: %d\n\n",name,opened);

        printf("choose a cell: ");
        scanf("%d%d",&x,&y);

        if (c[x][y].flag==0)
        {
            printf("if you want to open the cell press (1) and if you want to sign the cell press (2): ");
            scanf("%d",&z);

            if (z==1)
            {
                if (c[x][y].mine==1)
                {
                    system("cls");
                    printf("Game Over  :(\n");
                    for (int i = 1 ; i <= 30 ; ++i)
                    {
                        for (int j = 1 ; j <= 30 ; ++j)
                        {
                            if (c[i][j].mine==1)
                                printf("%[*]  ");
                            else
                                printf("[%d]  ",c[i][j].value);
                        }
                        printf("\n\n");
                    }
                    printf("if you want to restart the game press (1) and if you don't want, press (2): ");
                    scanf("%d",&z);
                    if (z==1)
                        goto restart;
                    else
                        return 0;
                }
                else if (c[x][y].value == 0)
                {
                    zero(x,y);
                }
                else
                {
                    c[x][y].state = 1;
                }

            }
            else
            {
                c[x][y].flag = 1;
            }
        }
        else
        {
            printf("are you sure that you want to open the cell? if yes , press (1) otherwise press (2) ");
            scanf("%d",&z);
            if (z==1)
            {
                if (c[x][y].mine==1)
                {
                    system("cls");
                    for (int i = 1 ; i <= 30 ; ++i)
                    {
                        for (int j = 1 ; j <= 30 ; ++j)
                        {
                            if (c[i][j].mine==1)
                                printf("%[*]  ");
                            else
                                printf("[%d]  ",c[i][j].value);
                        }
                        printf("\n\n");
                    }
                    printf("Game Over  :(\n");
                    printf("if you want to restart the game press (1) and if you don't want, press (2): ");
                    scanf("%d",&z);
                    if (z==1)
                        goto restart;
                    else
                        return 0;
                }
                else if (c[x][y].value == 0)
                {
                    zero(x,y);
                }
                else
                {
                    c[x][y].state = 1;
                }
            }
        }

    }
    for (int i = 1 ; i <= 30 ; ++i)
    {
        for (int j = 1 ; j <= 30 ; ++j)
        {
            if (c[i][j].mine==1)
                printf("%[*]  ");
            else
                printf("[%d]  ",c[i][j].value);
        }
        printf("\n\n");
    }
    printf("CONGRATULATION %s, YOU WON THE GAME :)\nif you want to restart the game press (1) and if you don't want, press (2): ",name);
    scanf("%d",&z);
    if (z==1)
        goto restart;

    return 0;
}
