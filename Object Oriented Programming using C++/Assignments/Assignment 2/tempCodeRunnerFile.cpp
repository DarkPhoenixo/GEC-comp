#include <iostream> 
using namespace std ;

int votes (int voter[],int i ){
    int choice ;
    
cout<<"The candidates of election are \n";
cout <<"1.Candidate 1\n" ;
cout <<"2.Candidate 2\n" ;
cout <<"3.Candidate 3\n" ;
cout <<"4.Candidate 4\n" ;
cout <<"5.Candidate 5\n" ;
cout <<"Enter your vote\n";
for (int j=0;j<i;j++){ 

cin>>choice ;
voter[j] = choice ;
}
return choice ;
}
void election (int voter[],int i) {
      int count[5]={0,0,0,0,0} ;
    int spoilt_vote=0 ;
    for (int j=0;j<i;j++){ 
  int vote = voter[j] ;
switch (vote){
case 1 : count[0] ++ ;
           break ;
case 2 : count[1] ++ ;
           break ;
case 3 : count[2] ++ ;
           break ;
case 4 : count[3] ++ ;
           break ;
case 5 : count[4] ++ ;
           break ;

default : spoilt_vote ++ ;
          break ;
} }

for(int i=0;i<5;i++) {
    cout <<"The votes for Candidate "<<i+1<<" are "<<count[i]<<" votes"<<endl ;
}
    cout <<"The number of spoilt votes are "<<spoilt_vote<<" votes"<<endl ;

return ;
}


int main (){
    int i ;
    cout<<"Enter the number of voters in the city \n" ;
    cin>>i ;
int voter[100];

votes(voter,i);
election(voter,i) ;

    return 0 ;
}