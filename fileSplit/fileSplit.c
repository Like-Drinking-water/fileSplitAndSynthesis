#include<stdio.h>
#include<stdlib.h>
#include<process.h>
#include<direct.h>

#define FILE_PATH_LENGTH 200
#define SPLIT_FILE_SIZE 103809024
#define TRUE 1
#define FALSE 0

/**
* 打印作者信息 
*/
void author() {
	printf("-------------------------------\n作者：chen\n联系邮箱：879070711@qq.com\n-------------------------------\n");
}

/**
* 拷贝文件
* @Param source[] 要被拷贝的字符串
* @Param another[] 获取拷贝内容的字符串
* @Param size 要拷贝的数量
*/
void copyString(char source[], char another[], int size) {
	int j;
	for (j = 0; j <= size; j++) {
		another[j] = source[j];
	}
	another[j] = '\0';
}

/**
* 将源文件的名字保存到特定文件中 
* @Param filePath[] 拆分的文件的路径
* @Param fileSplitDir[] 拆分文件存放的路径
* @Param pathLastIndex 用来标志基础路径的最后下标 
* @Param isBase 用来判断是不是最短相对路径 
*/
void sourceFileName(char filePath[], char fileSplitDir[], int pathLastIndex, int *isBase) {
	FILE *theName;
	int i = 0;
	int j = 0;
	int last;
	char splitFilePath[FILE_PATH_LENGTH];
	copyString(fileSplitDir, splitFilePath, pathLastIndex + 4);
	//如果是最短相对路径 
	if (*isBase) {
		i = 0;
		j = -1; 
	} 
	else {
		copyString(fileSplitDir, splitFilePath, pathLastIndex + 4);
		//找到字符串结尾
		while (filePath[i] != '\0') {
			i++;
		}
		last = i;
		//找到最后一个路径分隔符的下标
		while (filePath[i] != '\\' && filePath[i] != '/') {
			i--;
		}
		last -= i;
	}
	//给存放文件名称的文件命名 
	splitFilePath[pathLastIndex + 5] = '/';
	splitFilePath[pathLastIndex + 6] = 'n';
	splitFilePath[pathLastIndex + 7] = 'a';
	splitFilePath[pathLastIndex + 8] = 'm';
	splitFilePath[pathLastIndex + 9] = 'e';
	splitFilePath[pathLastIndex + 10] = '.';
	splitFilePath[pathLastIndex + 11] = 'c';
	splitFilePath[pathLastIndex + 12] = 'h';
	splitFilePath[pathLastIndex + 13] = 'l';
	splitFilePath[pathLastIndex + 14] = '\0';
	theName = fopen(splitFilePath, "wb+");
	if (theName == NULL) {
		printf("Can not open the file!!!\n");
		system("pause");
		return;
	}
	//将文件名保存起来 
	while (filePath[i + j + 1] != '\0') {
		fputc(filePath[i + j + 1], theName);
		j++;
	}
	//操作结束后关闭文件 
	fclose(theName);
}

/**
* 修改拆分文件的名称
* @Param splitFilePath[] 最初的拆分文件名称
* @Param start 标志名称开始的下标
* @Param i 标志已经使用的文件名 
*/
void splitFileName(char splitFilePath[], int start, int i) {
	int j;
	for (j = 1; j <= 5; j++) {
		splitFilePath[start + j] = (i % 10) + '0';
		i /= 10;
	}
}



/**
* 创建存放拆分文件的文件夹
* @Param fileBasePath[] 文件的基础路径
* @Param fileSplitDir[] 拆分文件保存的文件夹
* @Param size 文件的基础路径的大小
* @Param isBase 用来判断是不是最短相对路径 
* @Return 0 表示成功
*/
int createSplitDir(char fileBasePath[], char fileSplitDir[], int size, int *isBase) {
	//判断是否是最短相对路径 不是则拷贝基础路径 
	if (!(*isBase)) {
		copyString(fileBasePath, fileSplitDir, size);
	} 
	fileSplitDir[size + 1] = 's';
	fileSplitDir[size + 2] = 'p';
	fileSplitDir[size + 3] = 'l';
	fileSplitDir[size + 4] = 'i';
	fileSplitDir[size + 5] = 't';
	fileSplitDir[size + 6] = '\0';
	return _mkdir(fileSplitDir);
}

/**
* 获取文件的基础路径
* @Param filePath[] 文件的路径字符串
* @Param fileBasePath[] 文件的基础路径字符串
* @Param isBase 用来判断是不是最短相对路径 
* @Return 返回基础路径字符串结尾标志的下标
*/
int getBasePath(char filePath[], char fileBasePath[], int *isBase) {
	int i = 0;
	*isBase = TRUE;
	//找到字符串结尾
	while (filePath[i] != '\0') {
		i++;
		if (filePath[i] == '\\' || filePath[i] == '/') {
			*isBase = FALSE;
		}
	}
	//如果不是相对最短路径 
	if (!(*isBase)) {
		//找到最后一个路径分隔符的下标
		while (filePath[i] != '\\' && filePath[i] != '/') {
			i--;
		}
		//将最后一个路径分隔符前的内容赋值给基础路径
		copyString(filePath, fileBasePath, i);
	}
	else {
		i = -1;
	}
	
	return (i + 1);
}

int main(void) {
	//用来临时存放数据
	char tmp;
	long j; 
	//判断是否是输入相对路径 
	int isBase;
	int status, i, pathLastIndex;
	FILE *fileBase, *fileSplit;
	//用来保存文件的路径和文件的基础路径
	char filePath[FILE_PATH_LENGTH], fileBasePath[FILE_PATH_LENGTH], fileSplitDir[FILE_PATH_LENGTH], splitFilePath[FILE_PATH_LENGTH];
	author(); 
	printf("请输入要拆分的文件的地址:");
	scanf("%s",filePath);
	printf("正在拆分请勿关闭......\n");
	
	//获取文件的基础路径并记录下字符串的最后下标
	pathLastIndex = getBasePath(filePath, fileBasePath, &isBase);
	
	fileBase = fopen(filePath, "rb");  
	//判断是否成功打开文件
	if (fileBase == NULL) {
		printf("Can not open the file!\n");
		system("pause");
		return 0;
	}
	
	//在要拆分的文件的路径下创建一个名为 split 的文件夹
	status = createSplitDir(fileBasePath, fileSplitDir, pathLastIndex - 1, &isBase);
	//无法创建文件夹
	if (status) {
		printf("Can not create dir\n");
		system("pause");
		return 0;
	}
	sourceFileName(filePath, fileSplitDir, pathLastIndex, &isBase);
	//拷贝文件夹的路径
	copyString(fileSplitDir, splitFilePath, pathLastIndex + 4);
	splitFilePath[pathLastIndex + 5] = '/';
	splitFilePath[pathLastIndex + 6] = '0';
	splitFilePath[pathLastIndex + 7] = '0';
	splitFilePath[pathLastIndex + 8] = '0';
	splitFilePath[pathLastIndex + 9] = '0';
	splitFilePath[pathLastIndex + 10] = '0';
	splitFilePath[pathLastIndex + 11] = '.';
	splitFilePath[pathLastIndex + 12] = 'c';
	splitFilePath[pathLastIndex + 13] = 'h';
	splitFilePath[pathLastIndex + 14] = 'l';
	splitFilePath[pathLastIndex + 15] = '\0';
	//读取文件
	j = 0;
	i = 0;
	while (!(feof(fileBase))) {
		fileSplit = fopen(splitFilePath, "wb+");
		//判断是否成功打开文件
		if (fileSplit == NULL) {
			printf("Can not open the file!\n");
			system("pause");
			return 0;
		}
		//从文件中读取 99M 到拆分文件 当读取到 99M 或文件读取完成停止操作 
		while (j < SPLIT_FILE_SIZE && !(feof(fileBase))) {
			tmp = fgetc(fileBase);
			fputc(tmp, fileSplit);
			j++;
		}
		j = 0;
		//关闭一个拆分文件 
		fclose(fileSplit);
		i++;
		splitFileName(splitFilePath, pathLastIndex + 5, i);
	}
	fclose(fileBase);
	
	return 0;
}
