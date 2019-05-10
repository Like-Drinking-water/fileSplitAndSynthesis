#include<stdio.h>
#include<stdlib.h>
#include<process.h>
#include<direct.h>

#define FILE_PATH_LENGTH 200
#define SPLIT_FILE_SIZE 103809024
#define TRUE 1
#define FALSE 0

/**
* ��ӡ������Ϣ 
*/
void author() {
	printf("-------------------------------\n���ߣ�chen\n��ϵ���䣺879070711@qq.com\n-------------------------------\n");
}

/**
* �����ļ�
* @Param source[] Ҫ���������ַ���
* @Param another[] ��ȡ�������ݵ��ַ���
* @Param size Ҫ����������
*/
void copyString(char source[], char another[], int size) {
	int j;
	for (j = 0; j <= size; j++) {
		another[j] = source[j];
	}
	another[j] = '\0';
}

/**
* ��Դ�ļ������ֱ��浽�ض��ļ��� 
* @Param filePath[] ��ֵ��ļ���·��
* @Param fileSplitDir[] ����ļ���ŵ�·��
* @Param pathLastIndex ������־����·��������±� 
* @Param isBase �����ж��ǲ���������·�� 
*/
void sourceFileName(char filePath[], char fileSplitDir[], int pathLastIndex, int *isBase) {
	FILE *theName;
	int i = 0;
	int j = 0;
	int last;
	char splitFilePath[FILE_PATH_LENGTH];
	copyString(fileSplitDir, splitFilePath, pathLastIndex + 4);
	//�����������·�� 
	if (*isBase) {
		i = 0;
		j = -1; 
	} 
	else {
		copyString(fileSplitDir, splitFilePath, pathLastIndex + 4);
		//�ҵ��ַ�����β
		while (filePath[i] != '\0') {
			i++;
		}
		last = i;
		//�ҵ����һ��·���ָ������±�
		while (filePath[i] != '\\' && filePath[i] != '/') {
			i--;
		}
		last -= i;
	}
	//������ļ����Ƶ��ļ����� 
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
	//���ļ����������� 
	while (filePath[i + j + 1] != '\0') {
		fputc(filePath[i + j + 1], theName);
		j++;
	}
	//����������ر��ļ� 
	fclose(theName);
}

/**
* �޸Ĳ���ļ�������
* @Param splitFilePath[] ����Ĳ���ļ�����
* @Param start ��־���ƿ�ʼ���±�
* @Param i ��־�Ѿ�ʹ�õ��ļ��� 
*/
void splitFileName(char splitFilePath[], int start, int i) {
	int j;
	for (j = 1; j <= 5; j++) {
		splitFilePath[start + j] = (i % 10) + '0';
		i /= 10;
	}
}



/**
* ������Ų���ļ����ļ���
* @Param fileBasePath[] �ļ��Ļ���·��
* @Param fileSplitDir[] ����ļ�������ļ���
* @Param size �ļ��Ļ���·���Ĵ�С
* @Param isBase �����ж��ǲ���������·�� 
* @Return 0 ��ʾ�ɹ�
*/
int createSplitDir(char fileBasePath[], char fileSplitDir[], int size, int *isBase) {
	//�ж��Ƿ���������·�� �����򿽱�����·�� 
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
* ��ȡ�ļ��Ļ���·��
* @Param filePath[] �ļ���·���ַ���
* @Param fileBasePath[] �ļ��Ļ���·���ַ���
* @Param isBase �����ж��ǲ���������·�� 
* @Return ���ػ���·���ַ�����β��־���±�
*/
int getBasePath(char filePath[], char fileBasePath[], int *isBase) {
	int i = 0;
	*isBase = TRUE;
	//�ҵ��ַ�����β
	while (filePath[i] != '\0') {
		i++;
		if (filePath[i] == '\\' || filePath[i] == '/') {
			*isBase = FALSE;
		}
	}
	//�������������·�� 
	if (!(*isBase)) {
		//�ҵ����һ��·���ָ������±�
		while (filePath[i] != '\\' && filePath[i] != '/') {
			i--;
		}
		//�����һ��·���ָ���ǰ�����ݸ�ֵ������·��
		copyString(filePath, fileBasePath, i);
	}
	else {
		i = -1;
	}
	
	return (i + 1);
}

int main(void) {
	//������ʱ�������
	char tmp;
	long j; 
	//�ж��Ƿ����������·�� 
	int isBase;
	int status, i, pathLastIndex;
	FILE *fileBase, *fileSplit;
	//���������ļ���·�����ļ��Ļ���·��
	char filePath[FILE_PATH_LENGTH], fileBasePath[FILE_PATH_LENGTH], fileSplitDir[FILE_PATH_LENGTH], splitFilePath[FILE_PATH_LENGTH];
	author(); 
	printf("������Ҫ��ֵ��ļ��ĵ�ַ:");
	scanf("%s",filePath);
	printf("���ڲ������ر�......\n");
	
	//��ȡ�ļ��Ļ���·������¼���ַ���������±�
	pathLastIndex = getBasePath(filePath, fileBasePath, &isBase);
	
	fileBase = fopen(filePath, "rb");  
	//�ж��Ƿ�ɹ����ļ�
	if (fileBase == NULL) {
		printf("Can not open the file!\n");
		system("pause");
		return 0;
	}
	
	//��Ҫ��ֵ��ļ���·���´���һ����Ϊ split ���ļ���
	status = createSplitDir(fileBasePath, fileSplitDir, pathLastIndex - 1, &isBase);
	//�޷������ļ���
	if (status) {
		printf("Can not create dir\n");
		system("pause");
		return 0;
	}
	sourceFileName(filePath, fileSplitDir, pathLastIndex, &isBase);
	//�����ļ��е�·��
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
	//��ȡ�ļ�
	j = 0;
	i = 0;
	while (!(feof(fileBase))) {
		fileSplit = fopen(splitFilePath, "wb+");
		//�ж��Ƿ�ɹ����ļ�
		if (fileSplit == NULL) {
			printf("Can not open the file!\n");
			system("pause");
			return 0;
		}
		//���ļ��ж�ȡ 99M ������ļ� ����ȡ�� 99M ���ļ���ȡ���ֹͣ���� 
		while (j < SPLIT_FILE_SIZE && !(feof(fileBase))) {
			tmp = fgetc(fileBase);
			fputc(tmp, fileSplit);
			j++;
		}
		j = 0;
		//�ر�һ������ļ� 
		fclose(fileSplit);
		i++;
		splitFileName(splitFilePath, pathLastIndex + 5, i);
	}
	fclose(fileBase);
	
	return 0;
}
