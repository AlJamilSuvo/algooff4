#include <iostream>
#include <cstdio>
#include <cmath>
#define INF 1000000
using namespace std;
int N;
int set_length[100];
int mat[100][100];
int m;
int using_set[100];
int sol[100][100];
int min_set_num=INF;
int esi[100];
int c[100];
int first_set_no;
int cover_number(){
    int cnt=0;
    for(int i=0;i<N;i++) if(c[i]) cnt++;
    return cnt;
}
int get_pruning_number(int used_set){
    int ir=N-cover_number();
    int max_length=-1;
    for(int i=0;i<m;i++){
        if (!using_set[i]){
        	int sl;
        	for(int j=0;j<N;j++){
        		if(mat[i][j] && !c[i]) sl++;
			}
			if(sl>max_length) max_length=sl;
		}
    }

    int pn=used_set+ceil((double)ir/(double)max_length);
    return pn;
}
void set_element_index(int set){
    for(int i=0;i<N;i++){
        if (c[i]==0 && mat[set][i]==1){
            esi[i]=set;
            c[i]=1;
        }
    }
}
void reset_element_index(int set){
    for(int i=0;i<N;i++){
        if (esi[i]==set){
            esi[i]=-1;
            c[i]=0;
        }
    }
}
bool set_cover(int s,int us,int si){
    int pn=get_pruning_number(us);
    if (pn>min_set_num){
        cout<<pn<<" "<<min_set_num<<" pruning"<<endl;
        return false;
    }
    else{
        set_element_index(s);
        int cnt=cover_number();
        if(cnt==N){
            us=us+1;
            sol[si][s]=-1;
            reset_element_index(s);
            if (us<min_set_num){
                min_set_num=us;
                return true;
            }
            else return false;
        }
        using_set[s]=1;
        bool f=false;
        for(int i=s+1;i<m;i++){
            if(using_set[i]==0) if(set_cover(i,us+1,si)){
                sol[si][s]=i;
                f=true;
            }
        }
        reset_element_index(s);
        using_set[s]=0;
        if (f) return true;
        else return false;
    }
}
void solve_set_cover(){
    for(int i=0;i<N;i++){
        esi[i]=-1;
        c[i]=0;
    }
    for(int i=0;i<m;i++) using_set[i]=0;
    for(int i=0;i<N;i++) for(int j=0;j<m;j++) sol[i][j]=0;
    bool f=false;
    for(int i=0;i<m;i++){
        if (set_cover(i,0,i)){
            first_set_no=i;
            f=true;
        }
    }
    if (f){

        cout<<min_set_num<<endl;
        int k=first_set_no;
        while(k!=-1){
            cout<<k<<" ";
            k=sol[first_set_no][k];
        }
        cout<<endl;
    }
    else{
        cout<<"No Possible Solution"<<endl;
    }
}

int main(){
    cin>>N;
    cin>>m;
    for(int i=0;i<m;i++){
        int l=0;
        for(int j=0;j<N;j++){
            cin>>mat[i][j];
            if(mat[i][j]) l++;
        }
        set_length[i]=l;
    }
    solve_set_cover();
}
