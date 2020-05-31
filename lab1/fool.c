/*
    *
    * test block comment
    *
    * 
*/
int a,b;//test line comment
// test line comment ;
struct {
    int a,b;
}t1;
struct test{
    int a,b,c[10];
    float m,n;
}t2[100][10];
int main(){
    int i=0,a[10],b[10];
    for(i=1;i<10;i++){
        a[i]=i;
        b[i] += t2[i][i].a;
        t2[i][i].b*=t2[i][i].c[2]+t2[i][i].m*t2[i][i].n;
        if(i<0)
            break;
    }
    return 1;
}