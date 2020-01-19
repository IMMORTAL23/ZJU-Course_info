#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#define stringlen 1000
char* getRandomString(int length) ;
int main (){
	int i;
	long long int num_of_random;
	FILE *fp;
	char filename[10];
	double stature;
	printf("���ɵ���������");
	scanf("%d",&num_of_random); 
	getchar();
	printf("\n�����ļ���:");
	gets(filename);
	srand((unsigned) time(NULL)); 
	if ((fp=fopen(filename,"w"))==NULL){
       	printf("\n--------------------------------------------------------------\n");
   		printf("�ļ�����ʧ��!�밴�س�����!\n");
   		getchar();
   	    return;
    }
	for(i=0;i<num_of_random;i++){
		stature = getRandomStature();
		fprintf(fp,"%s %f %f\n",getRandomString(stringlen),stature,getRandomWeight(stature));
	}
	if (fclose(fp)){
       	printf("\n--------------------------------------------------------------\n");
   		printf("�ļ�����ʧ��!�밴�س�����!\n");
   		getchar();
   	    return;
    }
    printf("\n--------------------------------------------------------------\n"); 
	printf("�ɹ������ļ���%s��",filename);
	getchar(); 
} 


char* getRandomString(int length)  
{  
    int flag, i;  
    char* string;  
    if ((string = (char*) malloc(length)) == NULL )  
    {  
        printf("Malloc failed!\n");  
        return NULL ;  
    }  
  
    for (i = 0; i < length - 1; i++)  
    {  
        flag = rand() % 3;  //�õ������0��1��2ֵ 
        switch (flag)  
        {  
            case 0:  
                string[i] = 'A' + rand() % 26;  //������д��ĸ 
                break;  
            case 1:  
                string[i] = 'a' + rand() % 26;  //����Сд��ĸ 
                break;  
            case 2:  
                string[i] = '0' + rand() % 10;  //�������� 
                break;  
            default:  
                string[i] = 'x';  
                break;  
        }  
    }  
    string[length - 1] = '\0';  
    return string;  
}

double getRandomStature(void){
	double num;
    num = (double)rand() / RAND_MAX * (max_stature - min_stature) + min_stature; 
    //��������ߺ�����߼������� 
    return num;

}
double getRandomWeight(double stature){//��������������֯���������ع�ϵ�������һ������ֵ 
	double num;
    num = 1 - (double)rand() / RAND_MAX * 0.6 ; //����0.4-1��С�� 
    num = num * (stature -80); 
    return num;

} 
