/******************************************************************************

   Copyright (C), 2017-2018,    SightCare Ltd.(CN-HangZhou).    All rights reserved. 

*******************************************************************************
 * File Name : sqlite3_db.h
 * Version : 1.0
 * Author : wang yong
 * Created : 2018/12/15
 * Last Modified :
 * Description : sqlite3_db.cpp header file
 * Function List :
 * Modification History :
   1.Date : 2018/12/15
     Author : wang yong
     Modification : Created file
 
******************************************************************************/
#ifndef __AI_IPC_SQLITE_H__
#define __AI_IPC_SQLITE_H__


/*fix me  create table */

#define TRUE 1
#define FALSE 0

typedef struct PIC_SEARCH_PARAM
{
	char timestamp[256];
	int offset;
}PIC_SEARCH_PARAM;


typedef struct PIC_DELETE_PARAM
{
	char timestamp[256];
}PIC_DELETE_PARAM;


typedef struct PIC_SAVE_PARAM
{
	char timestamp[32];
	int jpeg;
	int yuv;
	int audio;
	int width;
	int height;
	int zoom_level;
	int transcolor_mode;
	int falsecolor_type;
}PIC_SAVE_PARAM;
/*fix me  create table */

typedef struct SQLITE_PARAMS
{
	int total_count;/*pic search result total count*/
	int current_search_count;/*pic search result current count*/
	PIC_SAVE_PARAM picture_store[4];
}SQLITE_PARAMS;

int sqlite3_delete(PIC_DELETE_PARAM       *pic_save_param);
char ** sqlite3_search(PIC_SEARCH_PARAM *pic_save_param,int *total_row,int *current_row,int *column);
int sqlite3_insert(PIC_SAVE_PARAM *pic_save_param);
int sqlite3_create();
char ** sqlite_update(PIC_SAVE_PARAM *pic_save_param);

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */





#endif /* __AI_IPC_SQLITE_H__ */

