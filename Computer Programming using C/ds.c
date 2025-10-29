#include<stdio.h>
#include<string.h>
struct sub{
float mk;
int gd;
};

struct sm{
struct sub a[4];
int sn;
float sgpa;
};

struct stud{
 char stud_name[30];
 struct sm b[2];
 int roll_num; 

}s1;

float SGPAfinder(struct sm *sem) {
    float countnumber = 0;

    for (int i = 0; i < 4; i++) {
        float mk = sem->a[i].mk;
        int grades = sem->a[i].gd ;
        if (85 <= mk && mk <= 100) {
            grades = 10;
        } else if (75 <= mk && mk < 85) 
        { grades = 9;
        } 
        else if (65 <= mk && mk < 75)
        {  grades = 8;
        } 
        else if (55 <= mk && mk < 65) {
            grades = 7;
        } 
        else if (45 <= mk && mk < 55) {
            grades = 6;
        }
         else if (40 <= mk && mk < 45) 
         {
            grades = 5;
        } 
        else {
            grades = 0;
        }

        countnumber += grades;
    }

    return countnumber / 4.0;
}

float firstsemcalc(struct stud * s1){

    printf("ENTER semester : \n");
    scanf("%d",&(s1->b[0].sn));

    printf("ENTER marks IN MATHEMATICS-I  : ");
    scanf("%f",&(s1->b[0].a[0].mk));

    printf("ENTER marks IN BASICS OF ELECTRICAL ENGINEERING : ");
    scanf("%f",&(s1->b[0].a[1].mk));

    printf("ENTER marks IN BASICS OF MECHANICAL ENGINEERING : ");
    scanf("%f",&(s1->b[0].a[2].mk));

    printf("ENTER marks IN CHEMISTRY : ");
    scanf("%f",&(s1->b[0].a[3].mk));

return s1->b[0].sgpa=SGPAfinder(&(s1->b[0]));

}

float secondsemcalc(struct stud * s1){

    printf("ENTER student's sem : ");
    scanf("%d",&(s1->b[1].sn));

    printf("ENTER marks IN MATHEMATICS II : ");
    scanf("%f",&(s1->b[1].a[0].mk));

    printf("ENTER marks IN PHYSICS : ");
    scanf("%f",&(s1->b[1].a[1].mk));

    printf("ENTER marks IN CIVIL ENGINEERING : ");
    scanf("%f",&(s1->b[1].a[2].mk));

    printf("ENTER marks IN COMPUTER PROGRAMMING : ");
    scanf("%f",&(s1->b[1].a[3].mk));

return s1->b[1].sgpa=SGPAfinder(&(s1->b[1]));

}




int main(){
    printf("ENTER student'S name : ");
    gets(s1.stud_name);

    printf("ENTER students roll number : ");
    scanf("%d",&s1.roll_num);

   int s= firstsemcalc(&s1);
   int k=secondsemcalc(&s1);
   float cgpa=(float)(s1.b[0].sgpa+s1.b[1].sgpa)/2;

   printf("RESULTS\n");
   printf("\n");
   printf("stud_name : %s ",s1.stud_name);
   printf("roll_num NO : %d \n",s1.roll_num);
   printf("sm : %d",s1.b[0].sn);
   printf("       GRADEPOINT\n");
   
   printf(" \n");

   printf("MATHEMATICS 1 :.1 %f %d\n",s1.b[0].a[0].mk,s1.b[0].a[0].gd);
   printf("BASICS OF ELECTRICAL ENGINEERING : %.1f  %d\n",s1.b[0].a[1].mk,s1.b[0].a[1].gd);
   printf("BASICS OF MECHANICAL ENGINEERING : %.1f  %d\n",s1.b[0].a[2].mk,s1.b[0].a[2].gd);
   printf("CHEMISTRY : %.1f  %d\n",s1.b[0].a[3].mk,s1.b[0].a[3].gd);
   printf("SGPA : %.1f\n",s1.b[0].sgpa);
   
     printf("\n\n");

   printf("sem marks : %d",s1.b[1].sn);
    printf("grade\n");
   printf("\n\n");
 
   printf("MATHEMATICS II : %.2f %d\n",s1.b[1].a[0].mk,s1.b[1].a[0].gd);
   printf("PHYSICS : %.2f%d\n",s1.b[1].a[1].mk,s1.b[1].a[1].gd);
   printf("CIVIL ENGINEERING : %.2f %d\n",s1.b[1].a[2].mk,s1.b[1].a[2].gd);
   printf("COMPUTER PROGRAMMING: %.2f %d\n",s1.b[1].a[3].mk,s1.b[1].a[3].gd);
   printf("SGPA : %.2f\n",s1.b[1].sgpa);
   printf("===========================================\n");
   printf("===========================================\n");
   printf("CGPA : %.3f",cgpa);

return 0;
}
