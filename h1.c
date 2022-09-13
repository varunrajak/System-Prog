#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define LINESIZE 100


struct studentdata
{	
	float gpa;
   	int cHours;
   	char *firstname, *lastname,*adv, *major, *Degree, *TA;

};

 struct studentdata getrecords(char* line)
 {
   struct studentdata sdata;
   sdata.firstname = strdup(strtok(line,","));
   sdata.lastname = strdup(strtok(NULL,","));
   sdata.major = strdup(strtok(NULL,","));
   sdata.Degree = strdup(strtok(NULL,","));
   sdata.gpa = atof(strtok(NULL,","));
   sdata.cHours = atoi(strtok(NULL,","));
   sdata.TA = strdup(strtok(NULL,","));
   sdata.adv = strdup(strtok(NULL,","));
   
 return sdata;
 }
 


 float q3(struct studentdata list[],int count)
 {
   float sum=0;
   float avg=0;
   for (int i = 0; i<=count; i++) {
	     sum = sum + list[i].cHours;   
   }
   
   avg = sum/count;
   return avg;
 }

//Reference taken for the concept  from https://stackoverflow.com/questions/40405289/count-the-unique-elements-in-the-array-of-struct-in-c

void q2(struct studentdata list[],int count)
{
	float s1,s2,s3;
	
	if(count == 0)
		printf("Error");
	else{

	for(int i = 0; i<count; i++)
		{
			if(list[i].gpa > s1){
				s3 = s2,s2 = s1,s1 = list[i].gpa;
			}
			else if (list[i].gpa > s2){
				s3 = s2;
				s2 = list[i].gpa;
			}
			else if (list[i].gpa > s3){
				s3 = list[i].gpa;
			}
	}
		printf("\n\n first student %.2f GPA\n", s1);
		
		for(int i =0; i<count-1; i++)
		{
			if(list[i].gpa == s1)
			{
				printf("%s %s\n", list[i].firstname, list[i].lastname);
			}
		}
		printf("second studnt %.2f GPA\n", s2);
		for(int i =0; i<count-1; i++)
		{
			if(list[i].gpa == s2)
			{
				printf("%s %s\n", list[i].firstname, list[i].lastname);
			}
		}
		printf("third student  %.2f gpa\n", s3);
		for(int i =0; i<count-1; i++)
		{
			if(list[i].gpa == s3)
			{
				printf("%s %s\n", list[i].firstname, list[i].lastname);
			}
		}
}
}
 
void q1(struct studentdata list[], int count)
{
	int temp,i,j;
	int inc = 0;

	char *noDeg[100];
	

	if(count > 0)
	{
		noDeg[inc++] = strdup ( list[0].Degree);
		
		
		for(i = 1; i < count; i++)	{
			temp = 0;
			for(j =1; j<i; j++)
			{
				if (strcmp(list[i].Degree, list[j].Degree)==0)
					temp = 1;
			}
			if(temp == 0)
				noDeg[inc++] = strdup(list[i].Degree);
		}
		printf("Unique Degrees :  %d\n", inc-1);


		printf("Different Degress present  \n");
		for(i = 1; i < inc; i++)
		{
			printf("%s \n", noDeg[i]);
		}
	}
} 



 
 float q4(struct studentdata list[],int count)
 {
	int i,temp = 0;
    float sum = 0; 
	float avg=0;
	
	char arr[]="Computer Science";

for(i=0;i<count;i++)
{
    if(strcmp(list[i].major,arr) == 0) 
    {
		sum = sum + list[i].gpa;
		temp= temp+1;
    }
 }avg= sum/temp;
 return avg;
}
 
void main ()
{
  	struct studentdata list[100];
	char Line [100];
  	int i;
	int count = 0;
  	float avg;
	float ag;


  	FILE *file =fopen("students_dataset.csv","r");
   if (file == NULL)
	  printf("Error\n");

 //to read file 
  while(fgets(Line, LINESIZE,file)!= NULL)
   {
     list[count++]= getrecords(Line);
   }  
 fclose(file);

q1(list, count);
q2(list, count);

avg = q3(list,count-1);
printf("\nAvg Credit hour:%.2f\n\n",avg);

ag = q4(list,count);
printf("Avg gpa for the computer science department is \n %.2f",ag);

 }




// void q5(struct student students[], int no_student){
// 	int index, current_loc,adv_count;
// 	struct student temp{

// 	}
// 	}
// 	{
// 		/* data */
// 	};
	
// }