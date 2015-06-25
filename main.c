#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#define _GNU_SOURCE

void swap(int *a, int *b);
void FastQuickSort(int *data, int left, int right);

void dataPatition (int *data, int *data_a, int *data_b, int left, int right, int middle){
	int o = 0, p = 0;
	int q;
	
	for(q = left; q < right; q++){
		if(data[q] > data[middle]){
			data_b[o++] = data[q];
		}
		else{
			data_a[p++] = data[q];
		}
	}
}

int main(void)
{
	char* buffer= (char *) malloc(20*sizeof(char));
	char* ptr= (char *) malloc(20*sizeof(char));
    int i, j=0, l, m, n;
    long WNUM, NUM;
    

	
	//*****input txt  Start*****//    
	FILE *fp;
    fp=fopen("data2.txt","r");
    
  	while(fgets(buffer, 10, fp)!=NULL) ++WNUM;
	printf("%d",WNUM);
	NUM = WNUM;
    rewind(fp);

    int *data = (int *) malloc(WNUM*sizeof(int));
    int *buff = (int *) malloc(WNUM/4*sizeof(int));

	while(fgets(buffer, 10, fp)!=NULL) {
    	ptr = buffer; data[j++] = atoi(ptr);
    	while( (ptr = strchr(ptr, ' '))!=NULL && *(ptr+1)!='\n') {
      	 	data[j++] = atoi(ptr++);
    	}
	}
	fclose(fp);
	free(buffer);
	free(ptr);
	//*****input txt  Exit*****//  
	int *data1[2][4];
	int count[2][4];
	count[0][0] = (WNUM/4-ArrayLargeCountCompute(data, 0, WNUM/4, WNUM/2));
	count[1][0] = (ArrayLargeCountCompute(data, 0, WNUM/4, WNUM/2));
	count[0][1] = (WNUM/4-ArrayLargeCountCompute(data, WNUM/4, WNUM/4*2, WNUM/2));
	count[1][1] = (ArrayLargeCountCompute(data, WNUM/4, WNUM/4*2, WNUM/2));
	count[0][2] = (WNUM/4-ArrayLargeCountCompute(data, WNUM/4*2, WNUM/4*3, WNUM/2));
	count[1][2] = (ArrayLargeCountCompute(data, WNUM/4*2, WNUM/4*3, WNUM/2));
	count[0][3] = ((WNUM/4+WNUM-WNUM/4*4)-ArrayLargeCountCompute(data, WNUM/4*3, WNUM, WNUM/2));
	count[1][3] = (ArrayLargeCountCompute(data, WNUM/4*3, WNUM, WNUM/2));
	
	data1[0][0] = (int *) malloc(count[0][0]*sizeof(int));
	data1[1][0] = (int *) malloc(count[1][0]*sizeof(int));
	data1[0][1] = (int *) malloc(count[0][1]*sizeof(int));
	data1[1][1] = (int *) malloc(count[1][1]*sizeof(int));
	data1[0][2] = (int *) malloc(count[0][2]*sizeof(int));
	data1[1][2] = (int *) malloc(count[1][2]*sizeof(int));
	data1[0][3] = (int *) malloc(count[0][3]*sizeof(int));
	data1[1][3] = (int *) malloc(count[1][3]*sizeof(int));

	dataPatition (data, data1[1][0], data1[0][0], 0, WNUM/4, WNUM/2);
	dataPatition (data, data1[0][1], data1[1][1], WNUM/4, WNUM/4+WNUM/4, WNUM/2);
	dataPatition (data, data1[0][2], data1[1][2], WNUM/4*2, WNUM/4*2+WNUM/4, WNUM/2);
	dataPatition (data, data1[0][3], data1[1][3], WNUM/4*3, WNUM, WNUM/2);

    printf(" %d \n排序後的結果: ",data[WNUM/2]);
    for (i = 0; i <count[0][0]; i++)
    {
        printf("%d ", data1[0][0][i]);
    }
         printf("\n排序後的結果: ");
    for (i = 0; i <count[1][0]; i++)
    {
        printf("%d ", data1[1][0][i]);
    }
         printf("\n排序後的結果: ");
    for (i = 0; i <count[0][1]; i++)
    {
        printf("%d ", data1[0][1][i]);
    }
         printf("\n排序後的結果: ");
    for (i = 0; i <count[1][1]; i++)
    {
        printf("%d ", data1[1][1][i]);
    }
     printf("\n排序後的結果: ");
    for (i = 0; i <count[0][2]; i++)
    {
        printf("%d ", data1[0][2][i]);
    }
         printf("\n排序後的結果: ");
    for (i = 0; i <count[1][2]; i++)
    {
        printf("%d ", data1[1][2][i]);
    }
         printf("\n排序後的結果: ");
    for (i = 0; i <count[0][3]; i++)
    {
        printf("%d ", data1[0][3][i]);
    }
         printf("\n排序後的結果: ");
    for (i = 0; i <count[1][3]; i++)
    {
        printf("%d ", data1[1][3][i]);
    }


    // 執行快速排序法
    //quicksort(data, 0, j - 1);
    FastQuickSort(data, 0, j - 1);
    
    //*****output print  Start*****//
	/*
    printf("\n排序後的結果: ");
    for (i = 0; i < j; i++)
    {
        printf("%d ", data[i]);
    }    
	printf("\n");
	*/
	//*****output print  Exit*****//
	
	//*****output txt  Start*****//
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
    //*****output txt  Exit*****//
    
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

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int ArrayLargeCountCompute(int *data, int left, int right, int middle){
	int count = 0;
	int l;
	for(l = left; l < right; l++){
		if(data[l] > data[middle]){
			++count;
		}
	}
	return count;
}
