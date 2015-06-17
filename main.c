#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h> 
#include <string.h>
#define  NUM_THREADS     4

long *temp;
long LengthOfInputArray = 0;

long *FirstcombineArray;
long *SecondcombineArray;
long *FinalcombineArray;
void quicksort(long *data, long left, long right);
//void swap(long *a, long *b);

void * Parallel_QuickSort(void *threadid)
{
   
   long tid;
   long i;
   tid = (long)threadid;
   
   long initial_left = tid*ceil((double)LengthOfInputArray/NUM_THREADS) ;
   long initial_right = ((tid*ceil((double)LengthOfInputArray/NUM_THREADS) +ceil((double)LengthOfInputArray/NUM_THREADS) )-1);
   
   //printf("\nI am the pthread:%ld\n", tid); 
 
   
   // 執行快速排序法
   quicksort(temp , initial_left  , initial_right );
     
   pthread_exit(NULL);
   
}

void *FirstCombine()
{
	
	long index1=(ceil((double)LengthOfInputArray/NUM_THREADS )*0);
    long index2=(ceil((double)LengthOfInputArray/NUM_THREADS )*1);  
    long index_for_FirstcombineArray=0;
    
    long threshold1 = ceil((double)LengthOfInputArray/NUM_THREADS );
    long threshold2 =(ceil((double)LengthOfInputArray/NUM_THREADS )*2);
    long threshold3 =(ceil((double)LengthOfInputArray/NUM_THREADS )*2);
    
    long threshold4 = (ceil((double)LengthOfInputArray/NUM_THREADS )-1);
    long threshold5 = ((ceil((double)LengthOfInputArray/NUM_THREADS )*2)-1);
	
	//第1和2個陣列進行合併(開始) 
	while(  index1<  threshold1  && index2 < threshold2 && index_for_FirstcombineArray <  threshold3 )
	{
		
		if( temp[index1]<temp[index2])
		{

            //printf("index1=%d\n", index1);
		    FirstcombineArray[index_for_FirstcombineArray] = temp[index1];
		    index1= index1+1;
		    index_for_FirstcombineArray = index_for_FirstcombineArray + 1;
		    
		    //printf("\nindex_for_FirstcombineArray=%ld\n",  index_for_FirstcombineArray);
		     
		    
		}
		else
		{

            //printf("index2=%d\n", index2);
		    FirstcombineArray[index_for_FirstcombineArray] = temp[index2];
		    index2= index2+1;
			index_for_FirstcombineArray = index_for_FirstcombineArray + 1;
            
            //printf("\nindex_for_FirstcombineArray=%ld\n",  index_for_FirstcombineArray); 
		    
		}
		
	}
	
	//把多算的減回來 
	index1= index1-1; 
	index2= index2-1; 
	
	//把最後沒比較到的塞到結尾 
	while(index1== threshold4 && index2!= threshold5 )
	{
	    index2= index2+1;	
	    FirstcombineArray[index_for_FirstcombineArray] = temp[index2];
		index_for_FirstcombineArray = index_for_FirstcombineArray + 1; 	
		
	    //printf("\nindex_for_FirstcombineArray=%ld\n",  index_for_FirstcombineArray);
	}
	
	while(index1!= threshold4 && index2== threshold5 )
	{	
	    index1= index1+1;
	    FirstcombineArray[index_for_FirstcombineArray] = temp[index1];
		index_for_FirstcombineArray = index_for_FirstcombineArray + 1; 
		
	    //printf("\nindex_for_FirstcombineArray=%ld\n",  index_for_FirstcombineArray);
	}
	
	//第1和2個陣列進行合併(結束) 
			
}

void *SecondCombine()
{
	
	long index3=(ceil((double)LengthOfInputArray/NUM_THREADS )*2); 
    long index4=(ceil((double)LengthOfInputArray/NUM_THREADS )*3); 
    long index_for_SecondcombineArray=0;
    
    long threshold1 = (ceil((double)LengthOfInputArray/NUM_THREADS )*3 );
    long threshold2 = (ceil((double)LengthOfInputArray/NUM_THREADS)*4);
    long threshold3 = (ceil((double)LengthOfInputArray/NUM_THREADS )*2 );
    
    long threshold4 = ((ceil((double)LengthOfInputArray/NUM_THREADS) *3 )-1);
    long threshold5 = ((ceil((double)LengthOfInputArray/NUM_THREADS)*4)-1);
	
	//第3和4個陣列進行合併(開始) 
	while(  index3<  threshold1   && index4 < threshold2   && index_for_SecondcombineArray < threshold3 )
	{
		
		if( temp[index3]<temp[index4])
		{

		    SecondcombineArray[index_for_SecondcombineArray] = temp[index3];
		    index3= index3+1;
		    index_for_SecondcombineArray = index_for_SecondcombineArray + 1;
		    
	        //printf("\nindex_for_SecondcombineArray =%ld\n",   index_for_SecondcombineArray );
		     
		    
		}
		else
		{

		    SecondcombineArray[index_for_SecondcombineArray] = temp[index4];
		    index4= index4+1;
			index_for_SecondcombineArray = index_for_SecondcombineArray + 1;
			
            //printf("\nindex_for_SecondcombineArray =%ld\n",   index_for_SecondcombineArray );
		    
		}
		
	}
	
	//把多算的減回來 
	index3= index3-1; 
	index4= index4-1; 
	
	while(index3== threshold4 && index4!= threshold5 )
	{
	    index4= index4+1;	
	    SecondcombineArray[	index_for_SecondcombineArray] = temp[index4];
		index_for_SecondcombineArray = index_for_SecondcombineArray + 1;
		
        //printf("\nindex_for_SecondcombineArray =%ld\n",   index_for_SecondcombineArray );
	}
	
	while(index3!= threshold4 && index4== threshold5 )
	{	
	    index3= index3+1;
	    SecondcombineArray[	index_for_SecondcombineArray] = temp[index3];
		index_for_SecondcombineArray = index_for_SecondcombineArray + 1;	
		
        //printf("\nindex_for_SecondcombineArray =%ld\n",   index_for_SecondcombineArray );
	}
	
	//第3和4個陣列進行合併(結束) 
	
		
}

int main (int argc, char *argv[])
{
	
	clock_t start, end;
    start = clock();
    long i=0;
	long j;
	
	

   
	//---------------------------------------------------------------------------------------------------//
    //讀取input file(開始) 
    //要先知道檔案裡存了多少數字 (開始)
    
    
    FILE *fp1;
    if((fp1=fopen("input.txt","r"))==NULL)
	{
          printf("open file error!!\n");
          system("pause");
          exit(0);
    }
    
    char buf1[10];
    buf1[9]='\0';
    while(fgets(buf1,10,fp1) != NULL)
    {
          //printf("\n%s\n", buf1);
          LengthOfInputArray = LengthOfInputArray + 1;      
    }
    
    fclose(fp1); 
    

    
    //要先知道檔案裡存了多少數字 (結束)
    
    //動態宣告一維陣列並初始化 
    long Initial_threshold1 =  (ceil((double)LengthOfInputArray/NUM_THREADS)*NUM_THREADS) ;
    temp =(long *)malloc(  Initial_threshold1 * sizeof(long)  ); 
    for( j= 0 ; j <  Initial_threshold1  ; j++ )
       temp[j]=0;
       
      	
	//將讀進來的數assign到temp陣列	           
    LengthOfInputArray = 0 ;
    FILE *fp2;
    if((fp2=fopen("input.txt","r"))==NULL)
	{
          printf("open file error!!\n");
          system("pause");
          exit(0);
    }
    
    char buf2[10];
    buf2[9]='\0';
    int length;
    long assignNumber=0;
    while(fgets(buf2,10,fp2) != NULL)
    { 
                              
          length = strlen(buf2)-1;
          if( length==1)
             assignNumber = (buf2[0]-'0'); 
          else if(length==2)
             assignNumber = (buf2[0]-'0')*10 + (buf2[1]-'0');  
          else if(length==3)
             assignNumber = (buf2[0]-'0')*100 + (buf2[1]-'0')*10 + (buf2[2]-'0');
          else if(length==4)
             assignNumber = (buf2[0]-'0')*1000 + (buf2[1]-'0')*100 + (buf2[2]-'0')*10 + (buf2[3]-'0') ; 
          else if(length==5)
             assignNumber = (buf2[0]-'0')*10000 + (buf2[1]-'0')*1000 + (buf2[2]-'0')*100 + (buf2[3]-'0')*10 + (buf2[4]-'0') ; 
          else if(length==6)
             assignNumber = (buf2[0]-'0')*100000 + (buf2[1]-'0')*10000 + (buf2[2]-'0')*1000 + (buf2[3]-'0')*100 + (buf2[4]-'0')*10 + (buf2[5]-'0') ;  
          else if(length==7)
             assignNumber = (buf2[0]-'0')*1000000 + (buf2[1]-'0')*100000 + (buf2[2]-'0')*10000 + (buf2[3]-'0')*1000 + (buf2[4]-'0')*100 + (buf2[5]-'0')*10 + (buf2[6]-'0') ;  
          else if(length==8)
             assignNumber = (buf2[0]-'0')*10000000 + (buf2[1]-'0')*1000000 + (buf2[2]-'0')*100000 + (buf2[3]-'0')*10000 + (buf2[4]-'0')*1000 + (buf2[5]-'0')*100 + (buf2[6]-'0')*10 + (buf2[7]-'0') ;      
               
	      temp[LengthOfInputArray] =  assignNumber;
	      

	      //temp[LengthOfInputArray] =  atol(buf2);
	      LengthOfInputArray = LengthOfInputArray + 1;   
    }
    
    fclose(fp2); 
	//讀取input file(結束)

	// NUM_THREADS     4 
	//根據待排序的陣列大小，宣告相關變數等等
    long index5=0;
    long index6=0;
    long index_for_FinalcombineArray=0;
    long Initial_threshold2 =  (ceil((double)LengthOfInputArray/NUM_THREADS )*2) ;
    long Initial_threshold3 =  (ceil((double)LengthOfInputArray/NUM_THREADS )*2) ;
    long Initial_threshold4 =  (ceil((double)LengthOfInputArray/NUM_THREADS )*4) ;
    
    
    FirstcombineArray =(long*)malloc( Initial_threshold2 * sizeof(long));
    SecondcombineArray=(long*)malloc( Initial_threshold3 * sizeof(long)); 
    FinalcombineArray=(long*)malloc ( Initial_threshold4 * sizeof(long)); 
    
    
    for ( j=0; j<Initial_threshold2 ; j++   )
         FirstcombineArray[j]=0;
         
    for ( j=0; j<Initial_threshold3; j++   )
         SecondcombineArray[j]=0;     
         
    for ( j=0; j<Initial_threshold4 ; j++   )
         FinalcombineArray[j]=0; 
    //---------------------------------------------------------------------------------------------------//
    

	
	//產生4個thread來平行對分到的4段陣列做Quicksort(開始) 
    pthread_t threads[NUM_THREADS];
    long rc;
    long t;

   
    for(t=0; t<NUM_THREADS; t++)
    {
	      //printf("In main: creating thread %ld\n", t);
	      rc = pthread_create(&threads[t], NULL,   Parallel_QuickSort  , (void *)t );
	      
	      if (rc)
		  {
	         printf("ERROR; return code from pthread_create() is %ld\n", rc);
	         exit(-1);
	      }
    }
    
    for(t=0; t<NUM_THREADS; t++)
         pthread_join(threads[t], NULL);
	//產生4個thread來平行對分到的4段陣列做Quicksort(結束) 
	
	
 
	
	
    
    //產生2個thread來平行處理兩兩陣列合併，第1個thread做1 2陣列合併，第2個thread做3 4陣列合併 
    pthread_t doFirstCombine ,  doSecondCombine;
	rc = pthread_create( &doFirstCombine  , NULL,   FirstCombine , NULL );
	      
	if (rc)
	{
	         printf("ERROR; return code from pthread_create() is %ld\n", rc);
	         exit(-1);
	}
	
	rc = pthread_create( &doSecondCombine  , NULL,   SecondCombine , NULL );     
	if (rc)
	{
	         printf("ERROR; return code from pthread_create() is %ld\n", rc);
	         exit(-1);
	}

    
    pthread_join(doFirstCombine, NULL);
    pthread_join(doSecondCombine, NULL); 
    //歸還陣列記憶體  
    free(temp);
   	//---------------------------------------------------------------------------------------------------//
   	
   	
    long threshold1 =(ceil((double)LengthOfInputArray/NUM_THREADS )*2);
    long threshold2 =(ceil((double)LengthOfInputArray/NUM_THREADS )*2);
    long threshold3 =(ceil((double)LengthOfInputArray/NUM_THREADS )*4);
    
    long threshold4 = ((ceil((double)LengthOfInputArray/NUM_THREADS )*2)-1);
    long threshold5 = ((ceil((double)LengthOfInputArray/NUM_THREADS )*2)-1);
   	
   	
   	
	//最後的合併(開始) 
	while(  index5<  threshold1 && index6 <  threshold2 && index_for_FinalcombineArray <  threshold3 ) 
	{
		
		if( FirstcombineArray[index5] < SecondcombineArray[index6])
		{

            //printf("index1=%d\n", index1);
		    FinalcombineArray[index_for_FinalcombineArray] = FirstcombineArray[index5];
		    index5= index5+1;
		    index_for_FinalcombineArray = index_for_FinalcombineArray + 1;
		     
		    
		}
		else
		{

            //printf("index2=%d\n", index2);
		    FinalcombineArray[index_for_FinalcombineArray]  = SecondcombineArray[index6];
		    index6= index6+1;
			index_for_FinalcombineArray = index_for_FinalcombineArray + 1;
		    
		}
		
		
		
	}
	
	//把多算的減回來 
	index5= index5-1; 
	index6= index6-1; 
	
	//把最後沒比較到的塞到結尾 
	while(index5==  threshold4 && index6!=  threshold5 )
	{
	    index6= index6+1;	
	    FinalcombineArray[index_for_FinalcombineArray]  = SecondcombineArray[index6];
		index_for_FinalcombineArray = index_for_FinalcombineArray + 1;
	}
	
	while(index5!= threshold4 && index6 == threshold5 )
	{                                                                             
	    index5= index5+1;	
	    FinalcombineArray[index_for_FinalcombineArray]  = FirstcombineArray[index5];
		index_for_FinalcombineArray = index_for_FinalcombineArray + 1;
	}	
	//最後的合併(結束) 
	//---------------------------------------------------------------------------------------------------//
	//歸還陣列記憶體  
    free(FirstcombineArray);	
    free(SecondcombineArray);
    
    
    //產生最後結果文件(開始)
    FILE *writefile;
	writefile=fopen("output.txt", "w");
	long index=0;
	long Writethreshold = (ceil((double)LengthOfInputArray/NUM_THREADS)*4);
	
    
	for( j=0 ; j< Writethreshold ; j=j+4)
	{
        index = j;
		if( FinalcombineArray[index] != 0 && FinalcombineArray[index+1] != 0 && FinalcombineArray[index+2] != 0 && FinalcombineArray[index+3] != 0  )
		   fprintf(writefile, "%ld\n%ld\n%ld\n%ld\n",  FinalcombineArray[index], FinalcombineArray[index+1], FinalcombineArray[index+2], FinalcombineArray[index+3]);
		else if( FinalcombineArray[index]==0 && FinalcombineArray[index+1] != 0 && FinalcombineArray[index+2] != 0 && FinalcombineArray[index+3] != 0  )
           fprintf(writefile, "%ld\n%ld\n%ld\n", FinalcombineArray[index+1], FinalcombineArray[index+2], FinalcombineArray[index+3]);
        else if( FinalcombineArray[index]==0 && FinalcombineArray[index+1] == 0 && FinalcombineArray[index+2] != 0 && FinalcombineArray[index+3] != 0  )
           fprintf(writefile, "%ld\n%ld\n",  FinalcombineArray[index+2], FinalcombineArray[index+3]);
        else if( FinalcombineArray[index]==0 && FinalcombineArray[index+1] == 0 && FinalcombineArray[index+2] == 0 && FinalcombineArray[index+3] != 0  )
           fprintf(writefile, "%ld\n",   FinalcombineArray[index+3]);
        else
           continue;	
	}

	fclose(writefile);	
	//產生最後結果文件(結束)
	//---------------------------------------------------------------------------------------------------//

   
    //歸還陣列記憶體  
    free(FinalcombineArray);
    
    
    //計算並顯示程式執行時間 
    end = clock();
    double diff = end - start; // ms
    //printf(" 總共要花幾%f  ms" , diff);
    printf("總共要花幾%f秒\n", diff / CLOCKS_PER_SEC );

    

   
  
    system("pause");
    return 0;
}



void quicksort(long *data, long left, long right)
{
    long pivot, i, j;
    long temp;

    if (left >= right) { return; }

    pivot = data[left];    

    i = left+1;
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

        //swap(&data[i], &data[j]);
        temp = data[i];
        data[i] = data[j];
        data[j] = temp;
        
    }

    //swap(&data[left], &data[j]);
    temp = data[left];
    data[left] = data[j];
    data[j] = temp;

    quicksort(data, left, j - 1);
    quicksort(data, j + 1, right);
}

/*
void swap(long *a, long *b)
{
    long temp = *a;
    *a = *b;
    *b = temp;
}
*/

