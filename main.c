#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void fastQuickSort(int *data, int left, int right);
void dataPartition(int *data, int *data_a, int *data_b, int left, int right, int middle);
void dataCombination_2in1(int *data, int *data_a, int *data_b, int a, int b);
void dataCombination_4in1(int *data, int *data_a, int *data_b, int *data_c, int *data_d, int a, int b, int c, int d);
int arrayLargeCountCompute(int *data, int left, int right, int middle);
enum {LINE_CNT = 150, BUF_SIZE = 40};

int getNumOfLinesInFile(char* filename);


struct DataPart{
	int *data;
	int *data_a;
	int *data_b;
	int left;
	int right;
	int middle;
}part[4];

struct DataQuickSort{
	int *data;
	int left;
	int right;
}sort[4];

struct DataCombine_2in1{
	int *data;
	int *data_a;
	int *data_b;
	int a;
	int b;
}combine_2in1[4];

struct DataCombine_4in1{
	int *data;
	int *data_a;
	int *data_b;
	int *data_c;
	int *data_d;
	int a;
	int b;
	int c;
	int d;
}combine_4in1[2];

void* threadPartition(struct DataPart* part){	
	dataPartition(part->data, part->data_a, part->data_b, part->left, part->right, part->middle);
	pthread_exit(NULL);
}

void* threadQuickSort(struct DataQuickSort* sort){	
	fastQuickSort(sort->data, sort->left, sort->right);
	pthread_exit(NULL);
}

void* threadCombination_2in1(struct DataCombine_2in1* combine_2in1){	
	dataCombination_2in1(combine_2in1->data, combine_2in1->data_a, combine_2in1->data_b, combine_2in1->a, combine_2in1->b);
	pthread_exit(NULL);
}

void* threadCombination_4in1(struct DataCombine_4in1* combine_4in1){	
	dataCombination_4in1(combine_4in1->data, combine_4in1->data_a, combine_4in1->data_b, combine_4in1->data_c, combine_4in1->data_d, combine_4in1->a, combine_4in1->b, combine_4in1->c, combine_4in1->d);
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	char* buffer= (char *) malloc(20*sizeof(char));
	char* ptr= (char *) malloc(20*sizeof(char));
    int i, j=0, l, m, n, lo=0;
    static int WNUM;
    char name[]= "input.txt";
    
    pthread_t thread[4];
    int ret;
    
	//*****input txt  Start*****//    
	FILE *fa;
	
	char *line = NULL;
    size_t len = 0;
    size_t read;
    
    fa=fopen(argv[1],"r");
    /*
  	while(fgets(buffer, 10, fa)!=NULL) ++WNUM;
  	printf("%d\n", getNumOfLinesInFile(name));
	*/
  	WNUM = getNumOfLinesInFile(argv[1]);
    rewind(fa); 

    int *data = (int *) malloc(WNUM*sizeof(int));
	/*
	while(fgets(buffer, 10, fa)!=NULL) {
    	ptr = buffer; data[j++] = atoi(ptr);
    	while( (ptr = strchr(ptr, ' '))!=NULL && *(ptr+1)!='\n') {
      	 	data[j] = atoi(ptr++);
    	}
	}
	*/
	/*
	while (fscanf(fa, "%s",ptr)!=EOF){ 
	data[lo]=atoi(ptr);
	lo++;
   }
  	*/
  	
  	for (lo=0; lo<WNUM; lo++) {
        read = getline(&line, &len, fa);
        data[lo] = atoi(line);
    } 
	
	fclose(fa);
	free(buffer);
	free(ptr);
	/*
	for(i=0;i<WNUM;i++)
    {
		printf("%d\n", data[i]);	   
   	}*/
	//*****input txt  Exit*****//  


	int *data1[2][4];
	int count[2][4];
	
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
	
	for(i = 0; i < 4; i++){
		switch(i){
			case 0:{
				part[i].data = data;
				part[i].data_a = data1[0][0];
				part[i].data_b = data1[1][0];
				part[i].left = 0;
				part[i].right = WNUM/4;
				part[i].middle = WNUM/2;
				break;
			}
			case 1:{
				part[i].data = data;
				part[i].data_a = data1[0][1];
				part[i].data_b = data1[1][1];
				part[i].left = WNUM/4;
				part[i].right = WNUM/4+WNUM/4;
				part[i].middle = WNUM/2;
				break;
			}
			case 2:{
				part[i].data = data;
				part[i].data_a = data1[0][2];
				part[i].data_b = data1[1][2];
				part[i].left = WNUM/4+WNUM/4;
				part[i].right = WNUM/4+WNUM/4+WNUM/4;
				part[i].middle = WNUM/2;
				break;
			}
			case 3:{
				part[i].data = data;
				part[i].data_a = data1[0][3];
				part[i].data_b = data1[1][3];
				part[i].left =  WNUM/4+WNUM/4+WNUM/4;
				part[i].right = WNUM;
				part[i].middle = WNUM/2;
				break;
			}
		}
		ret = pthread_create(&thread[i],NULL,threadPartition,&part[i]);
		if(ret!=0)
		{
			printf ("Create pthread error!\n");
			exit (1);
		}
	}
	pthread_join(thread[0],NULL);
	pthread_join(thread[1],NULL);
	pthread_join(thread[2],NULL);
	pthread_join(thread[3],NULL);
	
	free(data);
	
	int *data2[2];
	int WNUM1[4];	

	WNUM1[0] = (count[0][0]+count[0][2]);
	WNUM1[1] = (count[0][1]+count[0][3]);
	WNUM1[2] = (count[1][0]+count[1][2]);
	WNUM1[3] = (count[1][1]+count[1][3]);
	
	data2[0] = (int *) malloc((WNUM1[0]+WNUM1[1])*sizeof(int));
	data2[1] = (int *) malloc((WNUM1[2]+WNUM1[3])*sizeof(int));
	
	for(i = 0; i < 2; i++){

		combine_4in1[i].data = data2[i];
		combine_4in1[i].data_a = data1[i][0];
		combine_4in1[i].data_b = data1[i][2];
		combine_4in1[i].data_c = data1[i][1];
		combine_4in1[i].data_d = data1[i][3];
		combine_4in1[i].a = count[i][0];
		combine_4in1[i].b = count[i][2];
		combine_4in1[i].c = count[i][1];
		combine_4in1[i].d = count[i][3];
		
		ret = pthread_create(&thread[i],NULL,threadCombination_4in1,&combine_4in1[i]);
		if(ret!=0)
		{
			printf ("Create pthread error!\n");
			exit (1);
		}
	}
	pthread_join(thread[0],NULL);
	pthread_join(thread[1],NULL);
	pthread_join(thread[2],NULL);
	pthread_join(thread[3],NULL);
	
	free(data1[0][0]);
	free(data1[0][1]);
	free(data1[0][2]);
	free(data1[0][3]);
	free(data1[1][0]);
	free(data1[1][1]);
	free(data1[1][2]);
	free(data1[1][3]);

	int *data3[2][4];
	int count1[2][4];	
	
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

	for(i = 0; i < 4; i++){
		switch(i){
			case 0:{
				part[i].data = data2[0];
				part[i].data_a = data3[0][0];
				part[i].data_b = data3[0][1];
				part[i].left = 0;
				part[i].right = (WNUM1[0]+WNUM1[1])/2;
				part[i].middle = (WNUM1[0]+WNUM1[1])/2;
				break;
			}
			case 1:{
				part[i].data = data2[0];
				part[i].data_a = data3[0][2];
				part[i].data_b = data3[0][3];
				part[i].left = (WNUM1[0]+WNUM1[1])/2;
				part[i].right = (WNUM1[0]+WNUM1[1]);
				part[i].middle = (WNUM1[0]+WNUM1[1])/2;
				break;
			}
			case 2:{
				part[i].data = data2[1];
				part[i].data_a = data3[1][0];
				part[i].data_b = data3[1][1];
				part[i].left = 0;
				part[i].right = (WNUM1[2]+WNUM1[3])/2;
				part[i].middle = (WNUM1[2]+WNUM1[3])/2;
				break;
			}
			case 3:{
				part[i].data = data2[1];
				part[i].data_a = data3[1][2];
				part[i].data_b = data3[1][3];
				part[i].left =  (WNUM1[2]+WNUM1[3])/2;
				part[i].right = (WNUM1[2]+WNUM1[3]);
				part[i].middle = (WNUM1[2]+WNUM1[3])/2;
				break;
			}
		}
		ret = pthread_create(&thread[i],NULL,threadPartition,&part[i]);
		if(ret!=0)
		{
			printf ("Create pthread error!\n");
			exit (1);
		}
	}
	pthread_join(thread[0],NULL);
	pthread_join(thread[1],NULL);
	pthread_join(thread[2],NULL);
	pthread_join(thread[3],NULL);
	
	free(data2[0]);
	free(data2[1]);
	
	int *data4[4];
	int WNUM2[4];	

	WNUM2[0] = (count1[0][0]+count1[0][2]);
	WNUM2[1] = (count1[0][1]+count1[0][3]);
	WNUM2[2] = (count1[1][0]+count1[1][2]);
	WNUM2[3] = (count1[1][1]+count1[1][3]);
	
	data4[0] = (int *) malloc(WNUM2[0]*sizeof(int));
	data4[1] = (int *) malloc(WNUM2[1]*sizeof(int));
	data4[2] = (int *) malloc(WNUM2[2]*sizeof(int));
	data4[3] = (int *) malloc(WNUM2[3]*sizeof(int));	
	
	for(i = 0; i < 4; i++){

		combine_2in1[i].data = data4[i];
		combine_2in1[i].data_a = data3[i/2][i%2];
		combine_2in1[i].data_b = data3[i/2][i%2+2];
		combine_2in1[i].a = count1[i/2][i%2];
		combine_2in1[i].b = count1[i/2][i%2+2];
		
		ret = pthread_create(&thread[i],NULL,threadCombination_2in1,&combine_2in1[i]);
		if(ret!=0)
		{
			printf ("Create pthread error!\n");
			exit (1);
		}
	}
	pthread_join(thread[0],NULL);
	pthread_join(thread[1],NULL);
	pthread_join(thread[2],NULL);
	pthread_join(thread[3],NULL);

	for(i = 0; i < 4; i++){

		sort[i].data = data4[i];
		sort[i].left = 0;
		sort[i].right = WNUM2[i]-1;
			
		ret = pthread_create(&thread[i],NULL,threadQuickSort,&sort[i]);
		if(ret!=0)
		{
			printf ("Create pthread error!\n");
			exit (1);
		}
	}
	pthread_join(thread[0],NULL);
	pthread_join(thread[1],NULL);
	pthread_join(thread[2],NULL);
	pthread_join(thread[3],NULL);

    free(data3[0][0]);
    free(data3[0][1]);
    free(data3[0][2]);
    free(data3[0][3]);
    free(data3[1][0]);
    free(data3[1][1]);
    free(data3[1][2]);
    free(data3[1][3]);	
    
	   FILE *fw;

    if((fw=fopen(argv[2],"w"))!=NULL)
    {
        for(i=0;i<WNUM2[0];i++)
        {
           fprintf(fw,"%d\n", data4[0][i]);
        }   
        for(i=0;i<WNUM2[1];i++)
        {
           fprintf(fw,"%d\n", data4[1][i]);
        }  
        for(i=0;i<WNUM2[2];i++)
        {
           fprintf(fw,"%d\n", data4[2][i]);
        }  
        for(i=0;i<WNUM2[3];i++)
        {
           fprintf(fw,"%d\n", data4[3][i]);
        }  
    }
    fclose(fw);
    //*****output txt  Exit*****//
    
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
	int o;
	int t = 0;
	for( o = 0; o < a; o++){
		data[t++] = data_a[o];
	}
	for( o = 0; o < b; o++){
		data[t++] = data_b[o];
	}
	for( o = 0; o < c; o++){
		data[t++] = data_c[o];
	}
	for( o = 0; o < d; o++){
		data[t++] = data_d[o];
	}
}

int getNumOfLinesInFile(char* filename){
    FILE *fp;
    int numOfLines = 0;
    char ch;
    char buf[BUF_SIZE+1] ;
    char * ptr;
    size_t read_bytes;
    
    fp = fopen(filename, "r");
    if(fp == NULL){
        printf("Error: Can not open %s.\n", filename);
        return 1;
    }
    while((read_bytes = fread(buf, 1, BUF_SIZE, fp))) { // read_bytes==0 時結束
        buf[read_bytes] = '\0';
        ptr = (char*)strchr(buf, '\n');
        while(ptr!=NULL) {
            numOfLines++;
            ptr = (char*)strchr(ptr+1, '\n');
        }
    }
    fclose(fp);
    return numOfLines+1; //使用fread，會少讀最後一行，若檔案無最後一行空白的話。
}
