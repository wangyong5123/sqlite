#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include "sqlite3_db.h"
#include<string.h>


int main(int argc, char**argv)
{
	int total_row,column,current_row;
	int i,j;
	
////////////////   create  /////////////////////////////

	sqlite3_create();	

////////////////////////insert///////////////////////////
	PIC_SAVE_PARAM pic_save_param[10];
	strcpy(pic_save_param[0].timestamp,"2018121213");
	pic_save_param[0].jpeg = 1;
	pic_save_param[0].yuv = 1;
	pic_save_param[0].audio =1;
	pic_save_param[0].width = 1920;
	pic_save_param[0].height = 1080;
	pic_save_param[0].zoom_level = 2;
	pic_save_param[0].transcolor_mode = 1;
	pic_save_param[0].falsecolor_type = 0;	

	sqlite3_insert(pic_save_param);

///////////////////////search //////////////////////////////
	PIC_SEARCH_PARAM pic_search_param;
	pic_search_param.offset = 0;

	char **buf = sqlite3_search(&pic_search_param,&total_row,&current_row,&column);
	printf("total_row=%d,current_row=%d,column=%d\n",total_row,current_row,column);
	
//printf("###buf content####\n %s,%s,%s,%s,%s,%s,%s,%s,%s\n",buf[0],buf[1],buf[2],buf[3],buf[4],buf[5],buf[6],buf[7],buf[8]);
	
	for (i = 0,j = column;i< current_row;i++)
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

		j+=column;
	}	

	printf("search result...\n");
	for(i = 0;i<current_row;i++)
	{
		printf("################count=%d##########\n",i);
		printf("timestamp=%s\n",pic_save_param[i].timestamp);
		printf("jpeg=%d\n",pic_save_param[i].jpeg);
		printf("yuv=%d\n",pic_save_param[i].yuv);
		printf("audio=%d\n",pic_save_param[i].audio);
		printf("width=%d\n",pic_save_param[i].width);
		printf("height=%d\n",pic_save_param[i].height);
		printf("zoom_level=%d\n",pic_save_param[i].zoom_level);
		printf("transolor=%d\n",pic_save_param[i].transcolor_mode);
		printf("falsecolor=%d\n",pic_save_param[i].falsecolor_type);
	}
	printf("\n");

///////////////////////////delete //////////////////////////////
	PIC_DELETE_PARAM pic_delete_param;
	strcpy(pic_delete_param.timestamp,"2018121213");
	printf("pic_delete_param1=%s\n",pic_delete_param.timestamp);
//	sqlite3_delete(&pic_delete_param);

///////////////////////////update ////////////////////////////
	strcpy(pic_save_param[0].timestamp,"20181212188");
	printf("pic_delete_param2=%s\n",pic_delete_param.timestamp);
	sqlite_update(pic_save_param);

	return 0;
}


