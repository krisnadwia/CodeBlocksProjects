#pragma once
#include<stdio.h>
#include "Kario.h"
#include "VirtualCamera.h"
class Level
{
public:
	char originStage[100][1000];
	int height;
	int width;
	bool loadLevelFromFile(char *stagePath){
		height = 0;
		width = 0;
		FILE *f;
		f = fopen(stagePath, "r");
		if(f == NULL)return false;
		while (!feof(f)){
			fgets(originStage[height],1000,f);
			//fscanf(f, "%[^\n]\n", originStage[height]);
			if (width < strlen(originStage[height]))width = strlen(originStage[height]);
			height++;
		}
		return true;
	}
public:
	Level(char *stagePath){
		loadLevelFromFile(stagePath);
	}
};

