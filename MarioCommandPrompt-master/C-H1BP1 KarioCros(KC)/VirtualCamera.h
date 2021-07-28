#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<string>
using namespace std;
class VirtualCamera
{
public:
	char preRenderer[100][1000];
	int x;
	int y;
	int width;
	int height;
	int idx;
	char renderer[10000];
	VirtualCamera(int x,int y,int width, int height){
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
		setScreenResolution(width, height);
	}
	void setScreenResolution(int width,int height){
		char buf[100];
		string cmd = "mode con: cols=" + (string)(itoa(width+5,buf,10));
		cmd += " lines=" + (string)(itoa(height+1,buf,10));
		system(cmd.c_str());
	}
	void resetRenderer(){
		for (int i = 0; i < 100; i++){
			for (int j = 0; j < 1000; j++){
				preRenderer[i][j] = ' ' ;
			}
		}
	}
	void preRenderObject(int x,int y,int width,int height,char picture[][1000]){
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width;j++)
			{
				if(x+j>=this->x && x+j<this->x+this->width)
					preRenderer[y+i][x+j] = picture[i][j];
			}
		}
	}
	void render(){
		/*
		for (int i = y; i < y+height; i++){
			for (int j = x; j <= x+width; j++){
				if(preRenderer[i][j]>=0 && preRenderer[i][j]<=255 && j>=0 && preRenderer[i][j]!='\n')//-51
				{
					printf("%c",preRenderer[i][j]);
				}
				else{
//					printf("-***");
					//printf("%c",preRenderer[i][j]);
				}
			}
			printf("\n");
		}
		*/
		
		idx = 0;
		for (int i = y; i < y+height; i++){
			for (int j = x; j <= x+width; j++){
				if(preRenderer[i][j]>=0 && preRenderer[i][j]<=255 && j>=0 && preRenderer[i][j]!='\n')//-51
				{
					renderer[idx] = preRenderer[i][j];
					idx++;
				}
				else{
				}
			}
			//idx--;
			//renderer[idx-1] = '*';
			renderer[idx] = '\n';
			idx++;
		}
		renderer[idx] = '\0';
		idx++;
		printf(renderer);
		//puts(renderer);
		
	}
};