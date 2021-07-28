#include<iostream>
#include<vector>
#include<Windows.h>
#include<time.h>
#pragma comment(lib, "winmm.lib")
using namespace std;
//declare
struct Tile{
	bool active;
	bool available;
	int cost;
	char value;
	POINT point;
	Tile *parent;
	Tile *sideTile[4];
};
//input handler
int cursorX = 0,cursorY = 0;
int couple = 0;
HANDLE hStdin;
DWORD fdwSaveOldMode;
POINT active[2];
int activeIndex=0;
char item[10][10] = {0};
Tile papan[20][20];
bool quit = false;
const static int TILE_LEFT = 0;
const static int TILE_RIGHT = 1;
const static int TILE_TOP = 2;
const static int TILE_BOTTOM =3;
int gameBoardWidth = 8,gameBoardHeight = 8;
void gotoxy(short x, short y) {
	COORD pos = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void printScreen(int gameBoardHeight,int gameBoardWidth,Tile papan[][20]){
	gotoxy(0,0);
	printf("position X : %3d position Y : %3d\n",cursorX,cursorY);
	printf("couple left : %4d",couple);
	for(int i=0;i<gameBoardHeight+2;i++){
		for(int j=0;j<gameBoardWidth+2;j++){
			//if(papan[i][j]!=' ')
			{
				/*
				gotoxy(20+3*j,7+3*i);
				printf("%c%c%c",218,(papan[i][j].sideTile[TILE_TOP]==NULL)?196:179,191);
				gotoxy(20+3*j,7+3*i+1);
				printf("%c%c%c",(papan[i][j].sideTile[TILE_LEFT]==NULL)?179:196,papan[i][j].value,(papan[i][j].sideTile[TILE_RIGHT]==NULL)?179:196);
				gotoxy(20+3*j,7+3*i+2);
				printf("%c%c%c",192,(papan[i][j].sideTile[TILE_BOTTOM]==NULL)?196:179,217);
				*/
				if(!papan[i][j].active){
					gotoxy(20+3*j,7+3*i);
					printf("%c%c%c",218,196,191);
					gotoxy(20+3*j,7+3*i+1);
					printf("%c%c%c",179,papan[i][j].value,179);
					gotoxy(20+3*j,7+3*i+2);
					printf("%c%c%c",192,196,217);
				}
				else{
					gotoxy(20+3*j,7+3*i);
					printf("%c%c%c",201,205,187);
					gotoxy(20+3*j,7+3*i+1);
					printf("%c%c%c",186,papan[i][j].value,186);
					gotoxy(20+3*j,7+3*i+2);
					printf("%c%c%c",200,205,188);
				}
			}
		}
	}
	int i=1,j=12;
	gotoxy(20+3*j,7+3*i);
	printf("%c%c%c%c%c%c",218,196,196,196,196,191);
	gotoxy(20+3*j,7+3*i+1);
	printf("%c%s%c",179," OK ",179);
	gotoxy(20+3*j,7+3*i+2);
	printf("%c%c%c%c%c%c",192,196,196,196,196,217);
}
void insertSortedIntoVector(Tile *t,vector<Tile*>&openList){
	bool val = false;
	for(int i=0;i<openList.size();i++){
		if(openList[i]->cost > t->cost){
			val = true;
			openList.insert(openList.begin()+i,t);
			break;
		}
	}
	if(!val){
		openList.push_back(t);
	}
}
void Debug(){
	printf("Av");getchar();
}
void setupPapan(Tile papan[][20],char item[][10]){
	//SETUP
	for(int i=0;i<gameBoardHeight+2;i++)for(int j=0;j<gameBoardWidth+2;j++)
	{
		papan[i][j].available = true;
		papan[i][j].value=' ';
		papan[i][j].point.x = j;
		papan[i][j].point.y = i;
		if(i!=0)
			papan[i][j].sideTile[TILE_TOP] = &papan[i-1][j];
		else
			papan[i][j].sideTile[TILE_TOP] = NULL;
		if(i!=gameBoardHeight+1)
			papan[i][j].sideTile[TILE_BOTTOM] = &papan[i+1][j];
		else
			papan[i][j].sideTile[TILE_BOTTOM] = NULL;
		if(j!=0)
			papan[i][j].sideTile[TILE_LEFT] = &papan[i][j-1];
		else
			papan[i][j].sideTile[TILE_LEFT] = NULL;
		if(j!=gameBoardWidth+1)
			papan[i][j].sideTile[TILE_RIGHT] = &papan[i][j+1];
		else
			papan[i][j].sideTile[TILE_RIGHT] = NULL;
		papan[i][j].parent = NULL;
		papan[i][j].cost = 999;
	}
	for(int i=1;i<=gameBoardHeight;i++)for(int j=1;j<=gameBoardWidth;j++)
	{
		if(item[i-1][j-1]!=' '){
			papan[i][j].available = false;
			papan[i][j].value=item[i-1][j-1];
		}
	}
}
bool generatePath(POINT from,POINT to,Tile papan[][20],char item[][10]){
	setupPapan(papan,item);
	//GENERATE PATH
	vector<Tile*>openList;
	int xFrom = from.x,yFrom = from.y,xTo = to.x,yTo = to.y;
	papan[yFrom][xFrom].cost = 0;
	papan[yTo][xTo].available = true;
	bool found = false;
	openList.push_back(&papan[yFrom][xFrom]);
	while(openList.size()!=0 && found==false){
		//cari untuk kiri kanan atas bawah
		for(int i=0;i<4;i++)
		{
			if(openList[0]->sideTile[i]!=NULL && (openList[0]->sideTile[i]->value == ' ' || (openList[0]->sideTile[i]->point.x==xFrom && openList[0]->sideTile[i]->point.y==yFrom)|| (openList[0]->sideTile[i]->point.x==xTo && openList[0]->sideTile[i]->point.y==yTo))){// && openList[0]->sideTile[i]->available){
				//klo garisnya lurus
				if(openList[0]->parent==NULL || (openList[0]->sideTile[i]->point.y == openList[0]->parent->point.y) || (openList[0]->sideTile[i]->point.x == openList[0]->parent->point.x)){
					if(openList[0]->cost<3)
						if(openList[0]->sideTile[i]->cost > openList[0]->cost){
							openList[0]->sideTile[i]->cost = openList[0]->cost;
							openList[0]->sideTile[i]->parent = openList[0];
							insertSortedIntoVector(openList[0]->sideTile[i],openList);
						}
				}else{
					if(openList[0]->cost<2)
					{
						if(openList[0]->sideTile[i]->cost > openList[0]->cost+1){
							openList[0]->sideTile[i]->cost = openList[0]->cost+1;
							openList[0]->sideTile[i]->parent = openList[0];
							insertSortedIntoVector(openList[0]->sideTile[i],openList);
						}
					}
				}
			}
		}
		if(openList[0]->value == papan[yTo][xTo].value && openList[0]->point.x == papan[yTo][xTo].point.x && openList[0]->point.y == papan[yTo][xTo].point.y)
		{
			found = true;
			break;
		}
		//openList[0]->value = '0';
		openList[0]->available = false;
		openList.erase(openList.begin());
		//gotoxy(0,0);printf("size of list : %d\n",openList.size());
		//printScreen(gameBoardHeight,gameBoardWidth,papan);
		//getchar();
		//system("cls");
	}
	if(found)return true;
	else return false;
}
void coupleCount(){
	couple = 0;
	for(int i=1;i<=gameBoardHeight;i++){
		for(int j=1;j<=gameBoardWidth;j++){
			for(int a=1;a<=gameBoardHeight;a++){
				for(int b=1;b<=gameBoardWidth;b++){
					if(!(a==i && b==j)){
						if((item[i-1][j-1] == item[a-1][b-1]) && item[i-1][j-1]!=' ' && item[a-1][b-1]!=' '){
							Tile t[20][20];
							POINT a1;a1.x = j;a1.y = i;
							POINT a2;a2.x = b;a2.y = a;
							setupPapan(t,item);
							bool f = generatePath(a1,a2,t,item);
							if(f)couple++;
						}
					}
				}
			}
		}
	}

}
VOID ErrorExit (LPSTR lpszMessage)
{
    fprintf(stderr, "%s\n", lpszMessage);

    // Restore input mode on exit.

    SetConsoleMode(hStdin, fdwSaveOldMode);

    ExitProcess(0);
}
VOID KeyEventProc(KEY_EVENT_RECORD ker)
{

    //printf("Key event: ");
	if(ker.bKeyDown)
	{
        //printf("key pressed\n");
	}
    else
	{
		//printf("key released\n");
	}
}
VOID MouseEventProc(MOUSE_EVENT_RECORD mer)
{
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif
    //printf("Mouse event: ");
    switch(mer.dwEventFlags)
    {
        case 0:
            if(mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
            {
                //printf("left button press \n");
				if(activeIndex == 0 || activeIndex == 1){
					int x = (mer.dwMousePosition.X-20)/3;
					int y = (mer.dwMousePosition.Y-7)/3;
					if(papan[y][x].value != ' ' && !(papan[y][x].point.x==active[0].x && papan[y][x].point.y==active[0].y))
					{
						//if(activeIndex==0 || activeIndex==1)// && !(x==active[0].x && y==active[0].y)))
						{
							if(x>=0 && x<=9 && y>=0 && y<=9){
								active[activeIndex].x = (mer.dwMousePosition.X-20)/3;
								active[activeIndex].y = (mer.dwMousePosition.Y-7)/3;
								papan[active[activeIndex].y][active[activeIndex].x].active = true;
								activeIndex++;
							}
						}
					}
				}
				else if(activeIndex == 2){
					int x = (mer.dwMousePosition.X-20)/3;
					int y = (mer.dwMousePosition.Y-7)/3;
					if(x >=12 && x<=13 && y == 1){
						if(papan[active[1].y][active[1].x].value == papan[active[0].y][active[0].x].value)
						{
							bool found = generatePath(active[0],active[1],papan,item);
							if(found){
								Tile *curr = &papan[active[1].y][active[1].x];
								item[active[0].y-1][active[0].x-1] = ' ';
								item[active[1].y-1][active[1].x-1] = ' ';
								while(curr!=NULL){
									curr->value = 'A';
									curr = curr->parent;
								}
								activeIndex++;

								coupleCount();
								if(couple == 0){
									quit = true;
								}
							}else{
								setupPapan(papan,item);
								papan[active[0].y][active[0].x].active = false;
								papan[active[1].y][active[1].x].active = false;
								activeIndex = 0;
							}
						}
						else{
							setupPapan(papan,item);
							papan[active[0].y][active[0].x].active = false;
							papan[active[1].y][active[1].x].active = false;
							activeIndex = 0;
						}
					}
				}
				else{
					setupPapan(papan,item);
					papan[active[0].y][active[0].x].active = false;
					papan[active[1].y][active[1].x].active = false;
					activeIndex = 0;
				}
            }
            else if(mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
            {
                //printf("right button press \n");
				setupPapan(papan,item);
				papan[active[0].y][active[0].x].active = false;
				papan[active[1].y][active[1].x].active = false;
				activeIndex = 0;
            }
            else
            {
                //printf("button press\n");
            }
            break;
        case DOUBLE_CLICK:
            //printf("double click\n");
            break;
        case MOUSE_HWHEELED:
            //printf("horizontal mouse wheel\n");
            break;
        case MOUSE_MOVED:
			cursorX = (mer.dwMousePosition.X-20)/3;
			cursorY = (mer.dwMousePosition.Y-7)/3;
            //printf("mouse moved\n");
            break;
        case MOUSE_WHEELED:
            //printf("vertical mouse wheel\n");
            break;
        default:
            //printf("unknown\n");
            break;
    }
}
VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD wbsr)
{
    //printf("Resize event\n");
    //printf("Console screen buffer is %d columns by %d rows.\n", wbsr.dwSize.X, wbsr.dwSize.Y);
}
int main(){
	system("mode con:cols=83 lines=10");
	puts(" _        _______  _______ _________ _______  _______  _______  _        _       ");
	puts("| \\    /\\(  ___  )(  ____ )\\__   __/(  ___  )(  ____ \\(  ____ \\( \\      ( \\      ");
	puts("|  \\  / /| (   ) || (    )|   ) (   | (   ) || (    \\/| (    \\/| (      | (      ");
	puts("|  (_/ / | (___) || (____)|   | |   | |   | || |      | (__    | |      | |      ");
	puts("|   _ (  |  ___  ||     __)   | |   | |   | || |      |  __)   | |      | |      ");
	puts("|  ( \\ \\ | (   ) || (\\ (      | |   | |   | || |      | (      | |      | |      ");
	puts("|  /  \\ \\| )   ( || ) \\ \\_____) (___| (___) || (____/\\| (____/\\| (____/\\| (____/\\");
	puts("|_/    \\/|/     \||/   \\__/\\_______/(_______)(_______/(_______/(_______/(_______/");
	getchar();
	system("cls");
	system("mode con: cols=120 lines=40");
	//template input
    DWORD cNumRead, fdwMode, i;
    INPUT_RECORD irInBuf[128];
    int counter=0;
    // Get the standard input handle.
    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    if (hStdin == INVALID_HANDLE_VALUE)
        ErrorExit("GetStdHandle");
    // Save the current input mode, to be restored on exit.
    if (! GetConsoleMode(hStdin, &fdwSaveOldMode) )
        ErrorExit("GetConsoleMode");
    // Enable the window and mouse input events.
    fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    if (! SetConsoleMode(hStdin, fdwMode) )
        ErrorExit("SetConsoleMode");
	srand(time(NULL));
	//RANDOM POSITION
	for(int i=14;i<=29;i++){
		int x,y;
		for(int j=0;j<4;j++)
		{
			do{
				x = rand()%gameBoardWidth;
				y = rand()%gameBoardHeight;
			}while(item[y][x]!=0);
			item[y][x] = i;
		}
	}
	setupPapan(papan,item);
	coupleCount();
	//game loop
	while(true){
		printScreen(gameBoardHeight,gameBoardWidth,papan);
		//input listener
        // Wait for the events.
        if (! ReadConsoleInput(
                hStdin,      // input buffer handle
                irInBuf,     // buffer to read into
                128,         // size of read buffer
                &cNumRead) ) // number of records read
            ErrorExit("ReadConsoleInput");
        // Dispatch the events to the appropriate handler.
        for (i = 0; i < cNumRead; i++)
        {
            switch(irInBuf[i].EventType)
            {
                case KEY_EVENT: // keyboard input
                    KeyEventProc(irInBuf[i].Event.KeyEvent);
                    break;

                case MOUSE_EVENT: // mouse input
                    MouseEventProc(irInBuf[i].Event.MouseEvent);
                    break;

                case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing
                    ResizeEventProc( irInBuf[i].Event.WindowBufferSizeEvent );
                    break;

                case FOCUS_EVENT:  // disregard focus events

                case MENU_EVENT:   // disregard menu events
                    break;

                default:
                    ErrorExit("Unknown event type");
                    break;
            }
        }
		if(quit == true){
			break;
		}
	}
	int c = 0;
	for(int i=0;i<gameBoardHeight;i++){
		for(int j=0;j<gameBoardWidth;j++){
			if(item[i][j]!=' '){
				c++;
			}
		}
	}
	for(int i=0;i<50;i++){
		printf("\n");
	}
	if(c==0)
		printf("YOU ALREADY COMPLETE THE GAME PERFECTLY\n");
	else
		printf("YOU COMPLETE THE GAME, BUT IT'S %d PIECE LEFT\n",c);
	getchar();
	// Restore input mode on exit.
    SetConsoleMode(hStdin, fdwSaveOldMode);
	return 0;
}
