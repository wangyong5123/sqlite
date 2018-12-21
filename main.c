#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#define _DEBUG_
#include "sqlite3_db.h"
#include<string.h>
int main(int argc, char**argv)
{
	PIC_SAVE_PARAM pic_save_param[10];
	
	strcpy(pic_save_param[0].timestamp,"20181212188");
	pic_save_param[0].jpeg = 1;
	pic_save_param[0].yuv = 1;
	pic_save_param[0].audio =1;
	pic_save_param[0].width = 1920;
	pic_save_param[0].height = 1080;
	pic_save_param[0].zoom_level = 2;
	pic_save_param[0].transcolor_mode = 1;
	pic_save_param[0].falsecolor_type = 0;	

	sqlite3_create();	

	sqlite3_insert(pic_save_param);

	PIC_SEARCH_PARAM pic_search_param;
	pic_search_param.offset = 0;

	int total_row,column,current_row;

	char **buf = sqlite3_search(&pic_search_param,&total_row,&current_row,&column);
	
	printf("total_row=%d,column=%d\n",total_row,column);
	int i,j;


	printf("###buf content####%s,%s,%s,%s,%s,%s,%s,%s,%s\n",buf[0],buf[1],buf[2],buf[3],buf[4],buf[5],buf[6],buf[7],buf[8]);

	
	for (i = 0;i< total_row;i++)
	{
	for(j = 9;j<total_row*9;j+=9)
	{
        strcpy(pic_save_param[i].timestamp,buf[j]);
        pic_save_param[i].jpeg = atoi(buf[j+1]);
        pic_save_param[i].yuv = atoi(buf[j+2]);
        pic_save_param[i].audio =atoi(buf[j+3]);
        pic_save_param[i].width = atoi(buf[j+4]);
        pic_save_param[i].height = atoi(buf[j+5]);
        pic_save_param[i].zoom_level = atoi(buf[j+6]);
        pic_save_param[i].transcolor_mode = atoi(buf[j+7]);
        pic_save_param[i].falsecolor_type = atoi(buf[j+8]);
		}
	}

	
	for(i = 0;i<total_row;i++)
	{
	printf("################count=%d##########\n",i);
	printf("timestamp=%s\n:",pic_save_param[i].timestamp);
	printf("jpeg=%d:\n",pic_save_param[i].jpeg);
	printf("yuv=%d:\n",pic_save_param[i].yuv);
	printf("audio=%d\n:",pic_save_param[i].audio);
	printf("width=%d:\n",pic_save_param[i].width);
	printf("height=%d:\n",pic_save_param[i].height);
	printf("zoom_level=%d\n",pic_save_param[i].zoom_level);
	printf("transolor=%d\n",pic_save_param[i].transcolor_mode);
	printf("falsecolor=%d\n",pic_save_param[i].falsecolor_type);
	}
		printf("\n");

	//sqlite3_delete();

	return 0;
}

