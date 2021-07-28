#pragma once
#include<stdio.h>
#include "Level.h"
class Kario
{
public:
	char sprite[2][4][1000];
	int isFacingRight;
	float x, y;
	int width, height;
	int speed;
	int jump;
	bool isJumping;
	bool onGround;
	bool onCeil;
	bool onRight;
	bool onLeft;
	double tpf;
private:
	void loadSpriteFromFile(){
		FILE *f;
		f = fopen("Assets/mario.txt", "r");
		for (int i = 0; i < 2; i++){
			for (int j = 0; j < 4; j++){
				fgets(sprite[i][j],1000,f);
//				fscanf(f, "%[^\n]\n", &sprite[i][j]);
			}
		}
	}
public:
	Kario(int x,int y,int speed){
		onGround = false;
		onCeil = false;
		onRight = false;
		onLeft = false;
		isJumping = false;
		isFacingRight = 1;
		loadSpriteFromFile();
		this->x = x; this->y = y; this->width = 4; this->height = 4;
		this->speed = speed;
	}
	void update(double tpf){
		//do fly on jump
		if(isJumping && jump>0){
			jump--;
			y-=tpf*10;
		}
		//disable fly on jump if no more speed
		if(jump<=0 && isJumping){
			isJumping = false;
		}
		//fall if no isjumping and no on ground
		if(!isJumping && !onGround){
			y+=tpf*10;
		}
	}
	void moveLeft(double tpf){
		this->tpf = tpf;
		isFacingRight = 0;
		x-=tpf*speed;
	}
	void moveRight(double tpf){
		isFacingRight = 1;
		x+=tpf*speed;
	}
	void jumping(int power){
		isJumping = true;
		jump = power;
	}
	int getX(){return x;}
	int getY(){return y;}
	void checkOnGround(Level *level){
		for(int j=x;j<x+width-1;j++){
			if(level->originStage[getY()+width][j]=='s'){
				onGround = true;
				return;
			}
			onGround = false;
		}
	}
	void checkOnCeil(Level *level){
		for(int j=x;j<x+width-1;j++){
			if(level->originStage[getY()-1][j]=='s'){
				onCeil = true;
				jump = 0;
				return;
			}
			onCeil = false;
		}
	}
	void checkOnLeft(Level *level){
		for(int i=y;i<y+height-1;i++){
			if(level->originStage[i][getX()-1]=='s'){
				onLeft = true;
				return;
			}
			onLeft = false;
		}
	}
	void checkOnRight(Level *level){
		//check onRight
		for(int i=y;i<y+height-1;i++){
			if(level->originStage[i][getX()+width]=='s'){
				onRight = true;
				return;
			}
			onRight = false;
		}
	}
	bool checkOnGoal(Level *level){
		for(int j=x;j<x+width-1;j++){
			if(level->originStage[getY()+width][j]=='G' || level->originStage[getY()-1][j]=='G'){
				return true;
			}
		}
		for(int i=y;i<y+height-1;i++){
			if(level->originStage[i][getX()-1]=='G' || level->originStage[i][getX()+width]=='G'){
				return true;
			}
		}
		return false;
	}
};

