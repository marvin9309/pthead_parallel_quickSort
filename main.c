#include <stdio.h> 
#include <stdlib.h>
#define  NUM 10000000
#define _GNU_SOURCE


void print_infor(int *data);
void quicksort(int *data, int left, int right);
void swap(int *a, int *b);

void FastQuickSort(int *data, int left, int right);

int main(void)
{

	FILE *fp;
       
    int *data = (int *) malloc(NUM*sizeof(int));
	char *s_data = (char *) malloc(NUM*sizeof(char));
	
    int i, n, j=0;
    
    //int data[NUM];
    //char s_data[NUM];
    
    fp=fopen("input.txt","r");
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
    //quicksort(data, 0, j - 1);
    FastQuickSort(data, 0, j - 1);
    
	/*//output print  Start
    printf("\n排序後的結果: ");
    for (i = 0; i < j; i++)
    {
        printf("%d ", data[i]);
    }    
	printf("\n");
	*///output print  Exit

	//output txt  Start
   	FILE *fw;
    int k;
    if((fw=fopen("result.txt","w"))!=NULL)
    {
         for(k=0;i<NUM;i++)
         {
         fprintf(fw,"%d\n", data[i]);
         }   
    }
    fclose(fw);
    //output txt  Exit
    
    system("pause");
}

void FastQuickSort(int *data, int left, int right)
{
	int i, j, s , Temp;
	if(left < right) {
		s = data[(left+right)/2];
		i = left - 1;
		j = right + 1;
		while(1) {
			while(data[++i] < s) ; // 向右找
			while(data[--j] > s) ; // 向左找
			if(i >= j) break;
			Temp = data[i];
			data[i] = data[j];
			data[j] = Temp;
		}
		FastQuickSort(data, left, i-1); // 對左邊進行遞迴
		FastQuickSort(data, j+1, right); // 對右邊進行遞迴
	}
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
