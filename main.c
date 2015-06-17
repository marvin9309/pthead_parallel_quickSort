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
 
   
   // ����ֳt�ƧǪk
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
	
	//��1�M2�Ӱ}�C�i��X��(�}�l) 
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
	
	//��h�⪺��^�� 
	index1= index1-1; 
	index2= index2-1; 
	
	//��̫�S����쪺��쵲�� 
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
	
	//��1�M2�Ӱ}�C�i��X��(����) 
			
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
	
	//��3�M4�Ӱ}�C�i��X��(�}�l) 
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
	
	//��h�⪺��^�� 
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
	
	//��3�M4�Ӱ}�C�i��X��(����) 
	
		
}

int main (int argc, char *argv[])
{
	
	clock_t start, end;
    start = clock();
    long i=0;
	long j;
	
	

   
	//---------------------------------------------------------------------------------------------------//
    //Ū��input file(�}�l) 
    //�n�����D�ɮ׸̦s�F�h�ּƦr (�}�l)
    
    
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
    

    
    //�n�����D�ɮ׸̦s�F�h�ּƦr (����)
    
    //�ʺA�ŧi�@���}�C�ê�l�� 
    long Initial_threshold1 =  (ceil((double)LengthOfInputArray/NUM_THREADS)*NUM_THREADS) ;
    temp =(long *)malloc(  Initial_threshold1 * sizeof(long)  ); 
    for( j= 0 ; j <  Initial_threshold1  ; j++ )
       temp[j]=0;
       
      	
	//�NŪ�i�Ӫ���assign��temp�}�C	           
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
	//Ū��input file(����)

	// NUM_THREADS     4 
	//�ھګݱƧǪ��}�C�j�p�A�ŧi�����ܼƵ���
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
    

	
	//����4��thread�ӥ������쪺4�q�}�C��Quicksort(�}�l) 
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
	//����4��thread�ӥ������쪺4�q�}�C��Quicksort(����) 
	
	
 
	
	
    
    //����2��thread�ӥ���B�z���}�C�X�֡A��1��thread��1 2�}�C�X�֡A��2��thread��3 4�}�C�X�� 
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
    //�k�ٰ}�C�O����  
    free(temp);
   	//---------------------------------------------------------------------------------------------------//
   	
   	
    long threshold1 =(ceil((double)LengthOfInputArray/NUM_THREADS )*2);
    long threshold2 =(ceil((double)LengthOfInputArray/NUM_THREADS )*2);
    long threshold3 =(ceil((double)LengthOfInputArray/NUM_THREADS )*4);
    
    long threshold4 = ((ceil((double)LengthOfInputArray/NUM_THREADS )*2)-1);
    long threshold5 = ((ceil((double)LengthOfInputArray/NUM_THREADS )*2)-1);
   	
   	
   	
	//�̫᪺�X��(�}�l) 
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
	
	//��h�⪺��^�� 
	index5= index5-1; 
	index6= index6-1; 
	
	//��̫�S����쪺��쵲�� 
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
	//�̫᪺�X��(����) 
	//---------------------------------------------------------------------------------------------------//
	//�k�ٰ}�C�O����  
    free(FirstcombineArray);	
    free(SecondcombineArray);
    
    
    //���ͳ̫ᵲ�G���(�}�l)
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
	//���ͳ̫ᵲ�G���(����)
	//---------------------------------------------------------------------------------------------------//

   
    //�k�ٰ}�C�O����  
    free(FinalcombineArray);
    
    
    //�p�����ܵ{������ɶ� 
    end = clock();
    double diff = end - start; // ms
    //printf(" �`�@�n��X%f  ms" , diff);
    printf("�`�@�n��X%f��\n", diff / CLOCKS_PER_SEC );

    

   
  
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

