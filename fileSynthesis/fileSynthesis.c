#include<stdio.h>
#include<stdlib.h>

/**
* ��ӡ������Ϣ 
*/
void author() {
	printf("-------------------------------\n���ߣ�chen\n��ϵ���䣺879070711@qq.com\n-------------------------------\n");
}

/**
* ������ȡ����ļ������� 
* @SplitFile ��ʼ����ļ�������
* @i ��־�Ի�ȡ������ 
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
	printf("���ںϳ�����ر�......\n");
	//�������պϳɵ��ļ�
	name = fopen("name.chl", "rb");
	if (name == NULL) {
		printf("Can not found name.chl!");
		system("pause"); 
	}
	//��ȡ�ļ��� 
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
	//��ȡ��ɺ�رղ�ɾ���ļ�
	remove("name.chl");
	result = fopen(resultFile, "wb+");
	//��ʼ������ļ����� 
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
		//��û�в���ļ����Զ�ȡʱ�˳� 
		if (split == NULL) {
			break;
		}
		while (!(feof(split)))
		{
			tmp = fgetc(split);
			fputc(tmp, result);	
		}
		//��ȡ��ɺ�رղ�ɾ���ļ� 
		fclose(split);
		remove(splitFile);
		i++;
		splitFileName(splitFile, i);
	}
	fclose(result);
	return 0;
	
}
