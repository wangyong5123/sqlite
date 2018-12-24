#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/un.h>  //socket
#include <sys/types.h>    
#include <sys/stat.h> 

#include "sqlite3.h"
#include "sqlite3_db.h"

#define MODULE_NAME "sqlite3_db"

#define DATABASE_NAME "imagetable.db"

#define YUV_PATH_PREFIX  "/DCIM1/Preview/"
#define JPEG_PATH_PREFIX "/DCIM/Camera/"
#define JPEG_SUFFIX ".jpg"
#define YUV_SUFFIX  ".yuv"

int IsFile(const char *fileName)
{
	if (fileName == NULL || fileName[0] == '\0')
	return FALSE;

	struct stat s;
	short retVal;

	s.st_mode = 0x0000;

	retVal = stat(fileName, &s);

	if ( S_ISREG(s.st_mode)  )
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}



char ** sqlite_update(PIC_SAVE_PARAM *pic_save_param)
{
	sqlite3 *db=NULL;
	int len;

	int nrow=0;
	int ncolumn = 0;
	char *zErrMsg =NULL;
	char **azResult=NULL;

	char sql[80];

	len = sqlite3_open("imagetable.db",&db);
	if( len )
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(1);
	}
	else 
	{
		printf("You have opened a sqlite3 database named user successfully!\n");
	}

	printf("sstimestamp=%s\n",pic_save_param->timestamp);
	sprintf(sql,"UPDATE image SET audio = 1 WHERE timestamp = %s",pic_save_param->timestamp);

	sqlite3_exec(db,sql,NULL,NULL,&zErrMsg);
	printf("%s",zErrMsg);//no such column: name; null

	sqlite3_close(db);
	return azResult;
}


int sqlite3_delete(PIC_DELETE_PARAM *pic_delete_param)
{
	printf("sqlite3 delete...\n");
	sqlite3 *db=NULL;
	int len;
	int i=0;
	int nrow=0;
	int ncolumn = 0;
	char *zErrMsg =NULL;
	char **azResult=NULL; 
	char sql[80];

	len = sqlite3_open("imagetable.db",&db);
	if(len)
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(1);
	}
	else 
	{
		printf("You have opened a sqlite3 database named user successfully!\n");
	}
	
	printf("pic_delete_param=%s\n",pic_delete_param->timestamp);	

	sprintf(sql,"select * from image where timestamp = %s",pic_delete_param->timestamp);
	sqlite3_get_table(db,sql,&azResult,&nrow,&ncolumn,&zErrMsg);
	printf("nrow=%d ncolumn=%d\n",nrow,ncolumn);
	printf("the result is:\n");

	for(i=9;i<(nrow+1)*ncolumn;i++)
	{
		printf("azResult[%d]=%s\n",i,azResult[i]);
	}


	//delete from disk memory	
	if(nrow != 0)
	{
		char buf[80],del_buf[81];

		//delete jpg
		sprintf(buf,"JPEG_PATH_PREFIX/%s.jpg",azResult[10]);
		printf("buf=%s\n",buf);

		sprintf(del_buf,"rm -rf %s",buf);
		printf("del cmd  buf1=%s\n",del_buf);
		system(del_buf);	

		//delete audio

		//delete yuv
	}
	else
	{
		printf("nrow is null\n");
	}

	//delete from image table
	sprintf(sql,"delete from image where timestamp = %s",pic_delete_param->timestamp);
	sqlite3_exec(db,sql,NULL,NULL,&zErrMsg);

	sqlite3_close(db);
	return 0;

}


char ** sqlite3_search(PIC_SEARCH_PARAM *pic_search_param,int *total_row,int *current_row,int *column)
{
	printf("sqlite3_search...\n");
	sqlite3 *db=NULL;
	int len;
	int i=0;
	int nrow=0;
	int ncolumn = 0;
	char *zErrMsg =NULL;
	char **azResult=NULL;

	char sql[80],sql_total[40];

	len = sqlite3_open("imagetable.db",&db);
	if( len )
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(1);
	}
	else 
		printf("You have opened a sqlite3 database named user successfully!\n");


	sprintf(sql_total,"select * from image");
	sqlite3_get_table(db,sql_total,&azResult,&nrow,&ncolumn,&zErrMsg);
	printf("sqlite3_search total count successful nrow=%d ncolumn=%d\n",nrow,ncolumn);//total count
	*total_row = nrow;

	sprintf(sql,"select * from image order by timestamp desc limit 4 offset %d",pic_search_param->offset);
	sqlite3_get_table(db,sql,&azResult,&nrow,&ncolumn,&zErrMsg);
	printf("seatch limit count nrow=%d ncolumn=%d\n",nrow,ncolumn);
	for(i=9;i<(nrow+1)*ncolumn;i++)
	{
	printf("azResult[%d]=%s\n",i,azResult[i]);
	}
	*current_row = nrow;
	*column = ncolumn;

	sqlite3_close(db);

	return azResult;
}



int sqlite3_insert(PIC_SAVE_PARAM *pic_save_param)
{
	sqlite3 *db=NULL;
	int len;
	char *zErrMsg =NULL;
	char sql1[180];

	len = sqlite3_open("imagetable.db",&db);
	if(len)
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(1);
	}
	else 
	{
		printf("You have opened a sqlite3 database named user successfully!\n");
	}

 	// char *sql1 ="INSERT INTO 'image'VALUES(1,'A00000001',84564564561561,1,1,1,1920,1080,30,20);";

	sprintf(sql1,"INSERT INTO 'image'VALUES(%s,%d,%d,%d,%d,%d,%d,%d,%d);",\
	pic_save_param->timestamp,pic_save_param->jpeg,pic_save_param->yuv,pic_save_param->audio,\
	pic_save_param->height,pic_save_param->width,pic_save_param->zoom_level,pic_save_param->transcolor_mode,pic_save_param->falsecolor_type);

	sqlite3_exec(db,sql1,NULL,NULL,&zErrMsg);
	printf("insert zErrMsg=%s\n",zErrMsg);

	sqlite3_close(db);
	 
	 return 0;
}


int sqlite3_create()
{
	sqlite3 *db=NULL;
	int len,ret;
	char *zErrMsg =NULL;

	ret = IsFile("imagetable.db");
	if(ret == TRUE)
	{
		printf("imagetable.db is exist\n");
		return -1;
	}
	
	len = sqlite3_open("imagetable.db",&db);
	if(len)
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(1);
	}
	else 
		printf("You have opened a sqlite3 database named user successfully!\n");
	
	const char *sql = " CREATE TABLE image(timestamp VARCHAR(16),jpeg INTEGER,yuv INTEGER,audio INTEGER,width INTEGER,height INTEGER,zoom_level INTEGER,transcolor_mode INTEGER,falsecolor_type INTEGER);" ;

	printf("sqlite3 create successful\n");
	
	sqlite3_exec(db,sql,NULL,NULL,&zErrMsg);
	sqlite3_close(db);
	return 0;
}

