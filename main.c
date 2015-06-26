#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#define _GNU_SOURCE

void swap(int *a, int *b);
void fastQuickSort(int *data, int left, int right);
void dataPartition(int *data, int *data_a, int *data_b, int left, int right, int middle);
void dataCombination_2in1(int *data, int *data_a, int *data_b, int a, int b);
void dataCombination_4in1(int *data, int *data_a, int *data_b, int *data_c, int *data_d, int a, int b, int c, int d);
int arrayLargeCountCompute(int *data, int left, int right, int middle);
int main(void)
{
	char* buffer= (char *) malloc(20*sizeof(char));
	char* ptr= (char *) malloc(20*sizeof(char));
    int i, j=0, l, m, n;
    static long WNUM, NUM;
    
	//*****input txt  Start*****//    
	FILE *fp;
    fp=fopen("input.txt","r");
    
  	while(fgets(buffer, 10, fp)!=NULL) ++WNUM;
  	
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
	long count[2][4];
	
	count[0][0] = (WNUM/4-arrayLargeCountCompute(data, 0, WNUM/4, WNUM/2));
	count[1][0] = (arrayLargeCountCompute(data, 0, WNUM/4, WNUM/2));
	count[0][1] = (WNUM/4-arrayLargeCountCompute(data, WNUM/4, WNUM/4*2, WNUM/2));
	count[1][1] = (arrayLargeCountCompute(data, WNUM/4, WNUM/4*2, WNUM/2));
	count[0][2] = (WNUM/4-arrayLargeCountCompute(data, WNUM/4*2, WNUM/4*3, WNUM/2));
	count[1][2] = (arrayLargeCountCompute(data, WNUM/4*2, WNUM/4*3, WNUM/2));
	count[0][3] = ((WNUM/4+WNUM-WNUM/4*4)-arrayLargeCountCompute(data, WNUM/4*3, WNUM, WNUM/2));
	count[1][3] = (arrayLargeCountCompute(data, WNUM/4*3, WNUM, WNUM/2));
	
	data1[0][0] = (int *) malloc(count[0][0]*sizeof(int));
	data1[1][0] = (int *) malloc(count[1][0]*sizeof(int));
	data1[0][1] = (int *) malloc(count[0][1]*sizeof(int));
	data1[1][1] = (int *) malloc(count[1][1]*sizeof(int));
	data1[0][2] = (int *) malloc(count[0][2]*sizeof(int));
	data1[1][2] = (int *) malloc(count[1][2]*sizeof(int));
	data1[0][3] = (int *) malloc(count[0][3]*sizeof(int));
	data1[1][3] = (int *) malloc(count[1][3]*sizeof(int));

	dataPartition(data, data1[0][0], data1[1][0], 0, WNUM/4, WNUM/2);
	dataPartition(data, data1[0][1], data1[1][1], WNUM/4, WNUM/4+WNUM/4, WNUM/2);
	dataPartition(data, data1[0][2], data1[1][2], WNUM/4+WNUM/4, WNUM/4+WNUM/4+WNUM/4, WNUM/2);
	dataPartition(data, data1[0][3], data1[1][3], WNUM/4+WNUM/4+WNUM/4, WNUM, WNUM/2);
	
	free(data);
	
	int *data2[2];
	long WNUM1[4];	

	WNUM1[0] = (count[0][0]+count[0][2]);
	WNUM1[1] = (count[0][1]+count[0][3]);
	WNUM1[2] = (count[1][0]+count[1][2]);
	WNUM1[3] = (count[1][1]+count[1][3]);
	
	data2[0] = (int *) malloc((WNUM1[0]+WNUM1[1])*sizeof(int));
	data2[1] = (int *) malloc((WNUM1[2]+WNUM1[3])*sizeof(int));
	
	dataCombination_4in1(data2[0], data1[0][0], data1[0][2], data1[0][1], data1[0][3], count[0][0], count[0][2], count[0][1], count[0][3]);
	dataCombination_4in1(data2[1], data1[1][0], data1[1][2], data1[1][1], data1[1][3], count[1][0], count[1][2], count[1][1], count[1][3]);
	
	free(data1[0][0]);
	free(data1[0][1]);
	free(data1[0][2]);
	free(data1[0][3]);
	free(data1[1][0]);
	free(data1[1][1]);
	free(data1[1][2]);
	free(data1[1][3]);

	int *data3[2][4];
	long count1[2][4];	
	
	count1[0][0] = ((WNUM1[0]+WNUM1[1])/2-arrayLargeCountCompute(data2[0], 0, (WNUM1[0]+WNUM1[1])/2, (WNUM1[0]+WNUM1[1])/2));
	count1[0][1] = (arrayLargeCountCompute(data2[0], 0, (WNUM1[0]+WNUM1[1])/2, (WNUM1[0]+WNUM1[1])/2));
	count1[0][2] = (((WNUM1[0]+WNUM1[1])/2+(WNUM1[0]+WNUM1[1])-(WNUM1[0]+WNUM1[1])/2*2)-arrayLargeCountCompute(data2[0], (WNUM1[0]+WNUM1[1])/2, (WNUM1[0]+WNUM1[1]), (WNUM1[0]+WNUM1[1])/2));
	count1[0][3] = (arrayLargeCountCompute(data2[0], (WNUM1[0]+WNUM1[1])/2, (WNUM1[0]+WNUM1[1]), (WNUM1[0]+WNUM1[1])/2));
	count1[1][0] = ((WNUM1[2]+WNUM1[3])/2-arrayLargeCountCompute(data2[1], 0, (WNUM1[2]+WNUM1[3])/2, (WNUM1[2]+WNUM1[3])/2));
	count1[1][1] = (arrayLargeCountCompute(data2[1], 0, (WNUM1[2]+WNUM1[3])/2, (WNUM1[2]+WNUM1[3])/2));
	count1[1][2] = (((WNUM1[2]+WNUM1[3])/2+(WNUM1[2]+WNUM1[3])-(WNUM1[2]+WNUM1[3])/2*2)-arrayLargeCountCompute(data2[1], (WNUM1[2]+WNUM1[3])/2, (WNUM1[2]+WNUM1[3]), (WNUM1[2]+WNUM1[3])/2));
	count1[1][3] = (arrayLargeCountCompute(data2[1], (WNUM1[2]+WNUM1[3])/2, (WNUM1[2]+WNUM1[3]), (WNUM1[2]+WNUM1[3])/2));
	
	data3[0][0] = (int *) malloc(count1[0][0]*sizeof(int));
	data3[0][1] = (int *) malloc(count1[0][1]*sizeof(int));
	data3[0][2] = (int *) malloc(count1[0][2]*sizeof(int));
	data3[0][3] = (int *) malloc(count1[0][3]*sizeof(int));
	data3[1][0] = (int *) malloc(count1[1][0]*sizeof(int));
	data3[1][1] = (int *) malloc(count1[1][1]*sizeof(int));
	data3[1][2] = (int *) malloc(count1[1][2]*sizeof(int));
	data3[1][3] = (int *) malloc(count1[1][3]*sizeof(int));

	int o = 0, p = 0;
	int q;
	

	dataPartition(data2[0], data3[0][0], data3[0][1], 0, (WNUM1[0]+WNUM1[1])/2, (WNUM1[0]+WNUM1[1])/2);
	dataPartition(data2[0], data3[0][2], data3[0][3], (WNUM1[0]+WNUM1[1])/2, (WNUM1[0]+WNUM1[1]), (WNUM1[0]+WNUM1[1])/2);
	dataPartition(data2[1], data3[1][0], data3[1][1], 0, (WNUM1[2]+WNUM1[3])/2, (WNUM1[2]+WNUM1[3])/2);
	dataPartition(data2[1], data3[1][2], data3[1][3], (WNUM1[2]+WNUM1[3])/2, (WNUM1[2]+WNUM1[3]), (WNUM1[2]+WNUM1[3])/2);
	
	free(data2[0]);
	free(data2[1]);
	
	int *data4[4];
	long WNUM2[4];	

	WNUM2[0] = (count1[0][0]+count1[0][2]);
	WNUM2[1] = (count1[0][1]+count1[0][3]);
	WNUM2[2] = (count1[1][0]+count1[1][2]);
	WNUM2[3] = (count1[1][1]+count1[1][3]);
	
	data4[0] = (int *) malloc(WNUM2[0]*sizeof(int));
	data4[1] = (int *) malloc(WNUM2[1]*sizeof(int));
	data4[2] = (int *) malloc(WNUM2[2]*sizeof(int));
	data4[3] = (int *) malloc(WNUM2[3]*sizeof(int));	
	
	dataCombination_2in1(data4[0], data3[0][0], data3[0][2], count1[0][0], count1[0][2]);
	dataCombination_2in1(data4[1], data3[0][1], data3[0][3], count1[0][1], count1[0][3]);	
	dataCombination_2in1(data4[2], data3[1][0], data3[1][2], count1[1][0], count1[1][2]);
	dataCombination_2in1(data4[3], data3[1][1], data3[1][3], count1[1][1], count1[1][3]);

	fastQuickSort(data4[0], 0, WNUM2[0]-1);
	fastQuickSort(data4[1], 0, WNUM2[1]-1);
	fastQuickSort(data4[2], 0, WNUM2[2]-1);
	fastQuickSort(data4[3], 0, WNUM2[3]-1);

    free(data3[0][0]);
    free(data3[0][1]);
    free(data3[0][2]);
    free(data3[0][3]);
    free(data3[1][0]);
    free(data3[1][1]);
    free(data3[1][2]);
    free(data3[1][3]);	
		   
   	FILE *fw;
    int u;
    if((fw=fopen("result.txt","w"))!=NULL)
    {
        for(u=0;u<WNUM2[0];u++)
        {
           fprintf(fw,"%d\n", data4[0][u]);
        }   
        for(u=0;u<WNUM2[1];u++)
        {
           fprintf(fw,"%d\n", data4[1][u]);
        }  
        for(u=0;u<WNUM2[2];u++)
        {
           fprintf(fw,"%d\n", data4[2][u]);
        }  
        for(u=0;u<WNUM2[3];u++)
        {
           fprintf(fw,"%d\n", data4[3][u]);
        }  
    }
    fclose(fw);
    //*****output txt  Exit*****//
    
    //system("pause");
}

void fastQuickSort(int *data, int left, int right)
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
		fastQuickSort(data, left, i-1); // 對左邊進行遞迴
		fastQuickSort(data, j+1, right); // 對右邊進行遞迴
	}
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int arrayLargeCountCompute(int *data, int left, int right, int middle){
	int count = 0;
	int l;
	for(l = left; l < right; l++){
		if(data[l] > data[middle]){
			++count;
		}
	}
	return count;
}

void dataPartition(int *data, int *data_a, int *data_b, int left, int right, int middle){
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

void dataCombination_2in1(int *data, int *data_a, int *data_b, int a, int b){
	int o ,p ;
	int t = 0;
	for( o = 0; o < a; o++){
		data[t++] = data_a[o];
	}
	for( p = 0; p < b; p++){
		data[t++] = data_b[p];
	}
}

void dataCombination_4in1(int *data, int *data_a, int *data_b, int *data_c, int *data_d, int a, int b, int c, int d){
	int o ,p ,r ,s;
	int t = 0;
	for( o = 0; o < a; o++){
		data[t++] = data_a[o];
	}
	for( p = 0; p < b; p++){
		data[t++] = data_b[p];
	}
	for( p = 0; p < c; p++){
		data[t++] = data_c[p];
	}
	for( p = 0; p < d; p++){
		data[t++] = data_d[p];
	}
}
