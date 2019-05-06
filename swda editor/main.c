#include <stdio.h>
#include <string.h>
#include <stdint.h>

void rm_n(char *s)
{
	int l=strlen(s);
	if(s[l-1]=='\n')
		s[l-1]='\0';
}

int get(int a)
{
	char c;
	int b;
	while(1)
	{
		int s=scanf("%d",&b);
		while((c=getchar())!='\n' && c!=EOF);

		if(s==1 && b<=a && b>=0)break;

		printf("請輸入0到%d的整數！\n",a);
	}

	return b;
}

int main()
{
	puts("歡迎使用存檔修改器");
	puts("物品代碼請見：https://ppt.cc/fRQtJx");
	puts("請輸入存檔名稱：");
	char s[129];

	fgets(s,129,stdin);
	rm_n(s);
	
	FILE *f;
	char car[][15]={"輔子徹","機關人","桑紋錦","鑄石子","離開"};
	char opt[][10]={"生命","體力","經驗","仙術","裝備","返回"};
	char opt2[][10]={"現有","全部","返回"};
	char slot[][15]={"護頭/頭","護甲/軀","武器/臂","鞋/腿","戒指/心","護駕","護駕","法寶","法寶","返回"};
	uint32_t tmp;
	int carl[]={330,489,648,807};
	int optl[]={0,8,12,40,-29};

	if((f=fopen(s,"r+"))==NULL)
	{
		puts("檔案無法開啟！");
		return 0;
	}

	while(1)
	{
		puts("\n請輸入想修改的角色：");
		for(int i=0;i<5;i++)
			printf("%d) %s\n",i,car[i]);

		int a=get(4);
		if(a==4)break;

		while(1)
		{
			puts("\n請輸入想修改的項目：");
			for(int i=0;i<6;i++)
				printf("%d) %s\n",i,opt[i]);

			int b=get(5);
			if(b==5)break;

			if(b==4)while(1)
			{
				puts("\n請輸入想修改的欄位：");
				for(int i=0;i<10;i++)
					printf("%d) %s\n",i,slot[i]);
	
				int c=get(9);
				if(c==9)break;
	
				int loc=carl[a]+optl[b]+c*2;
				fseek(f,loc,SEEK_SET);
				fread(&tmp,2,1,f);
				printf("\n目前%s的%s的物品代碼為%d\n",car[a],slot[c],tmp);
				puts("請輸入新的物品代碼（十進位）：");

				int d=get(585);
				fseek(f,loc,SEEK_SET);
				fwrite(&d,2,1,f);

				puts("已成功修改！");
			}
			else while(1)
			{
				puts("\n請輸入想修改的項目：");
				for(int i=0;i<3;i++)
					printf("%d) %s%s\n",i,opt2[i],i<2?opt[b]:"");

				int c=get(2);
				if(c==2)break;

				int loc=carl[a]+optl[b]+c*2;
				fseek(f,loc,SEEK_SET);
				fread(&tmp,2,1,f);
				printf("\n目前%s的%s%s為%d\n",car[a],opt2[c],opt[b],tmp);
				puts("請輸入新的值：");

				int d=get(65535);
				fseek(f,loc,SEEK_SET);
				fwrite(&d,2,1,f);

				puts("已成功修改！");
			}

		}
	}

	puts("\n感謝你的使用！");
	fclose(f);

	return 0;
}
