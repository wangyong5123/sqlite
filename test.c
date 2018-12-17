#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#define _DEBUG_
int main(int argc, char**argv)
{
     sqlite3 *db=NULL;
     int len;
     int i=0;
     int nrow=0;
     int ncolumn = 0;
     char *zErrMsg =NULL;
     char **azResult=NULL; //二维数组存放结果
     /* 打开数据库 */
     len = sqlite3_open("imagetable.db",&db);
     if( len )
     {
        /*  fprintf函数格式化输出错误信息到指定的stderr文件流中  */
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));//sqlite3_errmsg(db)用以获得数据库打开错误码的英文描述。
        sqlite3_close(db);
        exit(1);
     }
     else printf("You have opened a sqlite3 database named user successfully!\n");
 
      /*插入数据  */
      char*sql1 ="INSERT INTO 'image'VALUES(1,'A00000001',84564564561561,1,1,1,1920,1080,30,20);";
      sqlite3_exec(db,sql1,NULL,NULL,&zErrMsg);

      char*sql2 ="INSERT INTO 'image'VALUES(2,'A00000002',84654156156656,1,0,1,1920,1080,20,90);";
      sqlite3_exec(db,sql2,NULL,NULL,&zErrMsg);
      char*sql3 ="INSERT INTO 'image'VALUES(4,'A00000004',94654511745715,1,1,0,1920,80,20,80);";
      sqlite3_exec(db,sql3,NULL,NULL,&zErrMsg);
#ifdef _DEBUG_
      printf("search error=%s\n",zErrMsg);
      sqlite3_free(zErrMsg);
#endif
      /* 查询数据 */
      char *sql="select * from image WHERE ID = 4";
      sqlite3_get_table(db,sql,&azResult,&nrow,&ncolumn,&zErrMsg);
      printf("nrow=%d ncolumn=%d\n",nrow,ncolumn);
      printf("the result is:\n");
      for(i=10;i<(nrow+1)*ncolumn;i++)
        {
          printf("azResult[%d]=%s\n",i,azResult[i]);
        }
 
      sqlite3_close(db);
      return 0;
}

