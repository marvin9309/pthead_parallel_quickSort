#include <stdio.h> 
#include <stdlib.h>
#define  NUM 22
#define _GNU_SOURCE
void quicksort(int *data, int left, int right);
void swap(int *a, int *b);
void print_infor(int *data);

int main(void)
{

	FILE *fp;
    char *line = NULL;
    long lines = 0;
    size_t len = 0;
	ssize_t read;
        
    int i, n, data[NUM],j=0;
    char s_data[NUM];
    
    fp=fopen("data2.txt","r");
if(fp==NULL){
	printf("Open file error\n");
	return 0;
    }

while (fscanf(fp, "%s",&s_data[j])!=EOF){
	data[j]=atoi(&s_data[j]);
	j++;
   }

fclose(fp);
    // 執行快速排序法
    quicksort(data, 0, j - 1);

    printf("\n排序後的結果: ");
    for (i = 0; i < j; i++)
    {
        printf("%d ", data[i]);
    }

    printf("\n");
    
    print_infor(&data);
    
    system("pause");
}

void quicksort(int *data, int left, int right) {
    int pivot, i, j;
    if (left >= right) { return; }
    pivot = data[left];
    i = left + 1;
    j = right;
    while (1)
    {
        while (i <= right)
        {
            if (data[i] > pivot)
            {
                break;
            }
            i = i + 1;
        }
        while (j > left)
        {
            if (data[j] < pivot)
            {
                break;
            }
            j = j - 1;
        }
        if (i > j) { break; }
        swap(&data[i], &data[j]);
    }
    swap(&data[left], &data[j]);
    quicksort(data, left, j - 1);
    quicksort(data, j + 1, right);
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void print_infor(int *data){
     FILE *fw;
     int i;
    if((fw=fopen("result.txt","w"))!=NULL)
    {
         for(i=0;i<NUM;i++)
         {
         fprintf(fw,"%d\n",data[i]);
         }   
    }
    fclose(fw);
}

