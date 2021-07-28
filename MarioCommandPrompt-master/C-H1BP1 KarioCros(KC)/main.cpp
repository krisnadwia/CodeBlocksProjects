#include "Kario.h"
#include "Level.h"
#include "VirtualCamera.h"
#include<stdio.h>
#include<conio.h>
#include<Windows.h>
#include<time.h>
#include<string.h>
#pragma comment(lib, "winmm.lib")
enum GameState
{
	MainMenu,InfoScreen,InGame
};
int main(){
	SYSTEMTIME time;
	int lastTime;
	int currTime;
	double deltaTime;
	char input;
	GameState currGameState = GameState::MainMenu;
//In Menu Variable
	int activeStage = 0;
	int totalStage = 0;
	char splashScreen[100][100];
	int splashHeight = 0;
	FILE *f;
	f = fopen("Assets/splashScreen.txt", "r");
	while (!feof(f)){
		fgets(splashScreen[splashHeight],1000,f);
		splashHeight++;
	}
//In Info Variable
	char information;
	bool isWin;
//In Game Variable
	Kario *kc = new Kario(10,19,20);
	Level *level[100];
	while(true){
		char levelNumber[3];
		sprintf(levelNumber,"%d",totalStage);
		char myFile[100]="Assets/level";
		strcat(myFile,levelNumber);
		strcat(myFile,".lvl");
		if(fopen(myFile,"r")==NULL)break;
		level[totalStage] = new Level(myFile);
		totalStage++;
	}
	VirtualCamera *cam = new VirtualCamera(kc->x-10,0,100, level[0]->height);
//In Game Setup
	kc->x=10;
//set Time
	GetSystemTime(&time);
	lastTime = (time.wSecond * 1000) + time.wMilliseconds;
	currTime = (time.wSecond * 1000) + time.wMilliseconds;
	while (true){
		deltaTime = ((lastTime - currTime)/1000.0);
		deltaTime = (deltaTime < 0.4)?deltaTime:0.4;
		GetSystemTime(&time);
		currTime = (time.wSecond * 1000) + time.wMilliseconds;
		//Game State
		if (currGameState == GameState::InGame){
			//game logic
			kc->jump--;
			kc->checkOnGround(level[activeStage]);
			kc->checkOnCeil(level[activeStage]);
			kc->checkOnLeft(level[activeStage]);
			kc->checkOnRight(level[activeStage]);
			if(kc->checkOnGoal(level[activeStage])){
				currGameState = GameState::InfoScreen;
				isWin = true;
			}
			kc->update(deltaTime);
			//camera following player
			cam->x = kc->x-10;
			cam->y = 0;
			//check fall to the dead
			if(kc->getY()>= 10+level[activeStage]->height){
				isWin = false;
				currGameState = GameState::InfoScreen;
			}
			//input in game
			if (kbhit())
			{
				input = getch();
				if (input == 'a' || input=='A')
				{
					if(!kc->onLeft && kc->x>10)
						kc->moveLeft(deltaTime);
				}
				else if(input == 'd' || input == 'D')
				{
					if(!kc->onRight)
						kc->moveRight(deltaTime);
				}
				else if(input == ' ')
				{
					if(!kc->isJumping && kc->onGround)
						kc->jumping(30);
				}
				if(input == 27){
					currGameState = GameState::MainMenu;
				}
			}
			//render
			cam->resetRenderer();
			cam->preRenderObject(0, 0, level[activeStage]->width, level[activeStage]->height, level[activeStage]->originStage);
			cam->preRenderObject(kc->x,kc->y,kc->width,kc->height,kc->sprite[kc->isFacingRight]);
			cam->render();
		}
		else if (currGameState == GameState::InfoScreen){
			for(int i=0;i<12;i++)printf("\n");
			for(int i=0;i<25;i++)printf(" ");
			if(!isWin)
				printf("Your LOSE!! last X Position in Level %d is %d\n",activeStage+1,kc->getX());
			else
				printf("Congratulation, YOU COMPLETE LEVEL %d, TRY OTHER\n",activeStage+1);
			if(kbhit()){
				input = getch();
				if(input == 13){
					currGameState = GameState::MainMenu;
				}
			}
		}
		else if(currGameState == GameState::MainMenu){
			for(int i=0;i<splashHeight;i++){
				printf("%s",splashScreen[i]);
			}
			printf("\nSelect a Level To Play: Level %d\n",(activeStage!=totalStage)?activeStage+1:0);
			for(int i=0;i<totalStage;i++){
				if(activeStage==i)
					printf("%d. >Play with Stage %d\n",i+1,i+1);
				else
					printf("%d. Play with Stage %d\n",i+1,i+1);
			}
			if(activeStage==totalStage){printf("%d. >Exit\n",totalStage+1);}
			else printf("%d. Exit\n",totalStage+1);
			if(kbhit()){
				input = getch();
				//printf("%d\n",input);
				//getchar();
				//enter
				if(input == 13){
					if(activeStage==totalStage){
						exit(1);
					}
					else{
						currGameState = GameState::InGame;
						kc->x = 10;
						kc->y = 19;
					}
				}
				else if(input =='w' || input=='W'){
					if(activeStage>0)
						activeStage--;
				}
				else if(input =='s' || input=='S'){
					if(activeStage<totalStage)
						activeStage++;
				}
			}
		}
		Sleep(40);
		GetSystemTime(&time);
		lastTime = (time.wSecond * 1000) + time.wMilliseconds;
		system("cls");
	}
	getchar();
}
