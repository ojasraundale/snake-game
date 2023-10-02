#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
#include<iostream>
#include<time.h>

using namespace std;

struct Body
{
    int IsHead;
    Body* next;
    int velocity;
    int X;
    int Y;
};

struct Snake
{
    Body* Head;
    int SnakeLength;
};
int UpdateMap(int direction);
void DrawMap();
void Initialize();
bool GenerateFood();
void DrawBody(int x, int y, int MapType);
void EndGame();
void MakeWall();
Snake snk;
int MaxX, MaxY, BodyRad, BodyCol, HeadCol, FoodCol, MapMaxX, MapMaxY, IsGameOver;
void *p;
int Map[100][100];


//bool GenerateFood();
int main()
{

    Initialize();
    //while(!IsGameOver)
    if(!GenerateFood())
    DrawMap();
    int haha = 0;
    while(!IsGameOver)
    {

        if(kbhit())
        {
            int dir = getch();
            if(dir == 119 && haha!=3)
            {
                haha = 1;
            }
            else if(dir == 97 && haha!=0)
            {
                haha = 2;
            }
            else if(dir == 115 && haha!=1)
            {
                haha = 3;
            }
            else if(dir == 100 && haha!=2)
            {
                haha = 0;
            }
        }
        if(UpdateMap(haha)==1)
        {
            DrawMap();
            if(!GenerateFood())
            {
                break;
            }
        }
        DrawMap();
        delay(100);
    }
    EndGame();

}

int UpdateMap(int direction)
{
    Body* temp = snk.Head;
    temp->velocity = direction;
    int HPrevX = temp->X; int HPrevY = temp->Y; int HPrevV = temp->velocity;
    if(temp->velocity == 0)
    {temp->X = (temp->X+1)%MaxX;}
    else if(temp->velocity == 1)
    {temp->Y = (temp->Y-1+MaxY)%MaxY;}
    else if(temp->velocity == 2)
    {temp->X = (temp->X-1+MaxX)%MaxX;}
    else if(temp->velocity == 3)
    {temp->Y = (temp->Y+1)%MaxY;}

    if(Map[temp->X][temp->Y] == 1)
    {
        Body* tail = new Body;
        tail->X = HPrevX; tail->Y = HPrevY; tail->velocity = HPrevV;
        tail->next = temp->next;
        temp->next = tail;
        //DrawBody(temp->X,temp->Y,3);
        //DrawBody(HPrevX,HPrevY,4);
        Map[temp->X][temp->Y]=3;
        Map[HPrevX][HPrevY]=4;
        snk.SnakeLength++;
        return 1;
    }
    else
    {
        Body* newtail = temp;
        Body* tail = newtail->next;
        while(tail->next!=NULL)
        {
            newtail = tail;
            tail = tail->next;
        }
        int TPrevX = tail->X; int TPrevY = tail->Y;
        tail->X = HPrevX; tail->Y = HPrevY; tail->velocity = HPrevV;
        newtail->next=NULL;
        tail->next = temp->next;
        temp->next = tail;
        //DrawBody(temp->X,temp->Y,3);
        //DrawBody(HPrevX,HPrevY,4);
        //DrawBody(TPrevX,TPrevY,2);
        Map[HPrevX][HPrevY]=4;
        Map[TPrevX][TPrevY]=2;
        if(Map[temp->X][temp->Y]!=2)
        {
            Map[temp->X][temp->Y]=3;
            IsGameOver = 1;
            return 0;
        }
        Map[temp->X][temp->Y]=3;

    }
    return 2;
}

void DrawMap()
{
    cleardevice();
    setcolor(BodyCol);
    circle(0*2*BodyRad + BodyRad,(MapMaxY-1)*2*BodyRad + BodyRad, BodyRad);
    setfillstyle(SOLID_FILL, BodyCol);
    floodfill(0*2*BodyRad + BodyRad,(MapMaxY-1)*2*BodyRad + BodyRad, BodyCol);
    setcolor(HeadCol);
    circle(1*2*BodyRad + BodyRad,(MapMaxY-1)*2*BodyRad + BodyRad, BodyRad);
    setfillstyle(SOLID_FILL, HeadCol);
    floodfill(1*2*BodyRad + BodyRad,(MapMaxY-1)*2*BodyRad + BodyRad, HeadCol);
    setcolor(FoodCol);
    circle(2*2*BodyRad + BodyRad,(MapMaxY-1)*2*BodyRad + BodyRad, BodyRad);
    setfillstyle(SOLID_FILL, FoodCol);
    floodfill(2*2*BodyRad + BodyRad,(MapMaxY-1)*2*BodyRad + BodyRad, FoodCol);
    setcolor(WHITE);

    setcolor(WHITE);
    rectangle(3*BodyRad*2+1,(MapMaxY-1)*BodyRad*2,(3+1)*BodyRad*2-1,(MapMaxY)*BodyRad*2-1);
    setfillstyle(SOLID_FILL, WHITE);
    floodfill(3*BodyRad*2+BodyRad,(MapMaxY-1)*BodyRad*2+BodyRad,WHITE);
    rectangle(0,0,MaxX*2*BodyRad-1, MaxY*2*BodyRad-1);
    for(int i = 0; i<MaxX; i++)
    {
        for(int j = 0; j < MaxY; j++)
        {
            DrawBody(i,j,Map[i][j]);
            //cout<<Map[i][j];
        }
        //cout<<endl;
    }
}

void DrawBody(int x, int y, int MapType)
{
        /*
        0 -> Wall
        1 -> Food
        2 -> Free
        3 -> Head
        4 -> Body
        */
    //cout<<MapType
    if(MapType == 1)
    {
        getimage(2*2*BodyRad,(MapMaxY-1)*2*BodyRad,2*2*BodyRad + 2*BodyRad,(MapMaxY-1)*2*BodyRad + 2*BodyRad,p);
        putimage(x*2*BodyRad,y*2*BodyRad,p,COPY_PUT);
    }
    else if(MapType == 0)
    {
        getimage(3*2*BodyRad,(MapMaxY-1)*2*BodyRad,3*2*BodyRad + 2*BodyRad,(MapMaxY-1)*2*BodyRad + 2*BodyRad,p);
        putimage(x*2*BodyRad,y*2*BodyRad,p,COPY_PUT);
    }
    else if(MapType == 3)
    {
        getimage(1*2*BodyRad,(MapMaxY-1)*2*BodyRad,1*2*BodyRad + 2*BodyRad,(MapMaxY-1)*2*BodyRad + 2*BodyRad,p);
        putimage(x*2*BodyRad,y*2*BodyRad,p,COPY_PUT);
    }
    else if(MapType == 4)
    {
        getimage(0*2*BodyRad,(MapMaxY-1)*2*BodyRad,0*2*BodyRad + 2*BodyRad,(MapMaxY-1)*2*BodyRad + 2*BodyRad,p);
        putimage(x*2*BodyRad,y*2*BodyRad,p,COPY_PUT);
    }
    else if(MapType == 2)
    {

    }
    return;
}
void Initialize()
{
    IsGameOver = 0;
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    initwindow(600,600);
    BodyRad = 15;
    MapMaxX = (getmaxx()+1)/(2*BodyRad);
    MapMaxY = (getmaxy()+1)/(2*BodyRad);
    MaxX = MapMaxX-1;
    MaxY = MapMaxY-1;
    BodyCol = GREEN; HeadCol = BLUE; FoodCol = RED;
    int area = imagesize(0,0,2*BodyRad,2*BodyRad);
    p = malloc(area);
    cout<<MapMaxX<<" "<<MapMaxY<<endl;

    for(int i = 0; i<MaxX; i++)
    {
        for(int j = 0; j<MaxX; j++)
        {
            Map[i][j] = 2;
        }
    }
    MakeWall();
    snk.Head = new Body;
    snk.Head->IsHead=1;
    snk.Head->velocity=0; snk.Head->X=MaxX/2; snk.Head->Y=MaxY/2;
    Body* temp = new Body;
    snk.Head->next = temp;
    temp->IsHead = 0;
    temp->velocity=0; temp->X = (snk.Head->X)-1; temp->Y = (snk.Head->Y);
    Body* temp1 = new Body;
    temp->next = temp1;
    temp1->IsHead = 0;
    temp1->velocity=0; temp1->X = (temp->X)-1; temp1->Y = (temp->Y);
    Map[MaxX/2][MaxY/2] = 3; Map[MaxX/2 -1][MaxY/2] = 4; Map[MaxX/2 - 2][MaxY/2] = 4;
    snk.SnakeLength=3;

}

void MakeWall()
{
    for(int i = 0; i<MaxX; i++)
    {
        Map[i][0] = 0;
        Map[i][MaxY-1] = 0;
    }
    for(int i = 0; i<MaxY; i++)
    {
        Map[0][i] = 0;
        Map[MaxX-1][i] = 0;
    }
}
bool GenerateFood()
{
    srand(time(NULL)+ 3*snk.SnakeLength + 72*snk.SnakeLength*snk.SnakeLength);
    int randX = rand()%(MaxX);
    int randY = rand()%MaxY;
    int i = randX; int j = randY; int xcounter=0; int ycounter = 0;
    while(Map[i][j]!=2)
    {
        i = (i+1)%MaxX;
        xcounter++;
        if(xcounter==MaxX)
        {
            ycounter++;
            xcounter=0;
            j = (j+1)%MaxY;
        }
        if(ycounter==MaxY)
        {
            return 0;
        }
    }
    //for(i = 0; 1; (i++)%MaxX)
    {
        /*if(counter==randnum){break;}
        for(j = 0; j<MaxY; j++)
        {
            if(Map[i][j]==2)
            {
                counter++;
            }
            if(counter==randnum){break;}
        }
        if(counter==randnum){break;}
        */

    }
    //i = (snk.Head->X+3)%MaxX; j = (snk.Head->Y+3)%MaxY;
    cout<<"Food at ("<<i<<", "<<j<<")"<<endl;
    Map[i][j] = 1;
    return 1;
}


void EndGame()
{
    settextstyle(4, HORIZ_DIR, 4);
    outtextxy(MaxX*BodyRad - 100, MaxY*BodyRad , "Game Over !");
    getch();
    closegraph();
}
