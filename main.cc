#include<stdio.h>
#include<stdlib.h>
#include"sqlite3.h"

#define _DEBUG_

int main(int argc,char ** argv)
{
	sqlite3 *db = NULL;
	int len;
	int i = 0;
	int nrow=0;
	int ncolumn = 0;
	
	char *zErrMsg = NULL;
//	char **azResult = NULL;

	char **azResult = (char **)malloc(100);
	
	//char **azResult = ;
	len = sqlite3_open("usr",&db);
	if(len)
	{
		fprintf(stderr,"Can't open database:%s\n",sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(1);
	}
	else
	{
		printf("You have open a sqlite3 database named usr successfuly\n");
	}
	
#if 0
     char *sql = " CREATE TABLE SensorData(\
         ID INTEDER PRIMARY KEY,\
         SensorID INTEGER,\
         siteNum INTEGER,\
         Time VARCHAR(12),\
         SensorParameter REAL\
         );" ;
#endif
     char *sql = " CREATE TABLE SensorData(\
		ID INTEGER PRIMATY KEY,\
		SensorID INTEGRE, \
		siteNum INTEGER,\
		Time VARCHAR(12),\
		SensorParameter REAL,\
		);";

	sqlite3_exec(db,sql,NULL,NULL,&zErrMsg);
	
#ifdef _DEBUG_

	printf("wy1=%s\n",zErrMsg);
	sqlite3_free(zErrMsg);
#endif
	char * sql1 = "INSERT INTO 'SensorData'VALUES(NULL,1,2,2018120401,13.5)";
	sqlite3_exec(db,sql1,NULL,NULL,&zErrMsg);
	
	char * sql2 = "INSERT INTO 'SensorData'VALUES(NULL,2,2,2018120402,13.5)";
	sqlite3_exec(db,sql2,NULL,NULL,&zErrMsg);

	char * sql3 = "INSERT INTO 'SensorData'VALUES(NULL,3,2,2018120403,13.5)";
	sqlite3_exec(db,sql3,NULL,NULL,&zErrMsg);

	//search info
	sql="select * from SensorData";
	sqlite3_get_table(db,sql,&azResult,&nrow,&ncolumn,&zErrMsg);
	printf("nrow=%d,ncolumn=%d\n",nrow,ncolumn);
	printf("the result is :\n");
	for(i = 0;i<(nrow+1);i++)
	{
		printf("azResult[%d]=%s\n",i,azResult[i]);
	}

	//delete info
	sql = "delete from SensorData where SensorID =1;";
	sqlite3_exec(db,sql,NULL,NULL,&zErrMsg);

#ifdef _DEBUG_
	printf("zErrMsg=%s\n",zErrMsg);
	sqlite3_free(zErrMsg);	
#endif
	
	sql="select * from SensorData";
	sqlite3_get_table(db,sql,&azResult,&nrow,&ncolumn,&zErrMsg);
	printf("nrow=%d,ncolumn=%d\n",nrow,ncolumn);
	printf("the delete result is :\n");
	for(i = 0;i<(nrow+1);i++)
	{
		printf("azResult[%d]=%s\n",i,azResult[i]);
	}


	free(azResult);
	sqlite3_free(db);
	return 0;
}
