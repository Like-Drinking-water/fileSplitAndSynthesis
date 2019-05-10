#include<stdio.h>
#include<stdlib.h>

/**
* 打印作者信息 
*/
void author() {
	printf("-------------------------------\n作者：chen\n联系邮箱：879070711@qq.com\n-------------------------------\n");
}

/**
* 用来获取拆分文件的名称 
* @SplitFile 初始拆分文件的名称
* @i 标志以获取的名称 
*/ 
void splitFileName(char splitFile[], int i) {
	int j;
	for (j = 0; j < 5; j++) {
		splitFile[j] = (i % 10) + '0';
		i /= 10;
	}
}

int main(void) {
	FILE *name, *result, *split;
	char tmp;
	int i = 0;
	char resultFile[20], splitFile[10];
	author();
	printf("正在合成请勿关闭......\n");
	//创建最终合成的文件
	name = fopen("name.chl", "rb");
	if (name == NULL) {
		printf("Can not found name.chl!");
		system("pause"); 
	}
	//获取文件名 
	while (!(feof(name)))
	{	
		tmp = fgetc(name);
		if (tmp != EOF) {
			resultFile[i] = tmp;
			i++;	
		}
	}
	resultFile[i] = '\0';
	fclose(name);
	//读取完成后关闭并删除文件
	remove("name.chl");
	result = fopen(resultFile, "wb+");
	//初始化拆分文件名称 
	splitFile[0] = '0';
	splitFile[1] = '0';
	splitFile[2] = '0';
	splitFile[3] = '0';
	splitFile[4] = '0';
	splitFile[5] = '.';
	splitFile[6] = 'c';
	splitFile[7] = 'h';
	splitFile[8] = 'l';
	splitFile[9] = '\0';
	for (i = 0;;) {
		split = fopen(splitFile, "rb");
		//但没有拆分文件可以读取时退出 
		if (split == NULL) {
			break;
		}
		while (!(feof(split)))
		{
			tmp = fgetc(split);
			fputc(tmp, result);	
		}
		//读取完成后关闭并删除文件 
		fclose(split);
		remove(splitFile);
		i++;
		splitFileName(splitFile, i);
	}
	fclose(result);
	return 0;
	
}
