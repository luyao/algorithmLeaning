/***************************************************************************
 * 
 * Copyright (c) 2014 izptec.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file permutation.cpp
 * @author YAO LU(luyao@izptec.com)
 * @date 2014/03/03 13:59:57
 * @version 1.0 
 * @brief 
 *  
 **/

#include <iostream>
using namespace std;

int P[1024];
int cnt = 0;
int call = 0;
int level = 0;

void inline printPermutation(int n)
{
    for (int j = 1; j<=n; ++j) {
        cout<<P[j]<<" ";
    }
    cout<<endl;
}

void inline swap(int &i, int &j)
{
    int t = j;
    j = i;
    i = t;
}

int generate_v1(int N, int n)
{
    if ( 1== N ) printPermutation(n);
    for (int c=1; c<=N; ++c) {
        //cout<<"Swap P["<<c<<"]="<<P[c]<<" with P["<<N<<"]="<<P[N]<<endl;
        swap(P[c], P[N]);
        generate_v1(N-1, n);
        //cout<<"Swap P["<<c<<"]="<<P[c]<<" with P["<<N<<"]="<<P[N]<<endl;
        swap(P[c], P[N]);
    }
}

int generate_v2(int N, int n)
{
    if ( 1== N ) {
        printPermutation(n);
        return 0;
    }
    for (int c=1; c<=N; ++c) {
        generate_v2(N-1, n);
        swap(P[N%2?1:c], P[N]);
    }
}

int generate_v2_modified(int N, int n)
{
    int c[32];
    int t, M;
    for (int i = 1; i<=n; ++i) {
        P[i] = i; c[i] = 1;
    }
    printPermutation(n);
    for (int i=1; i<=n;) {
        if (c[i] < n) {
            swap( P[(n & 0x1) ? 1 : i], P[n]);
            ++c[i]; i=1;
            printPermutation(n);
        }else {
            c[n++] = 1;
        }
    }
    return 0;
}


int gen_permutation(int i, int n)
{
    ++call;
    static int k = -1;
    k += 1;  //this part will do increase
    P[i] = k;
    for (int j = 0; j<level;++j) {
        cout<<"  ";
    }
    cout<<__FUNCTION__<<" call:"<<call<<" "
        <<"i:"<<i<<" "
        <<"n:"<<n<<" "
        <<"k:"<<k<<endl;

    if (k == n) {
        cout<<++cnt<<":";
        printPermutation(n);
    }

    for (int j=1; j<=n; ++j) {
        if (0 == P[j]) {
            ++level;
            gen_permutation(j, n);
        }
    }
    k -= 1;
    P[i] = 0;
    --level;
    
    return 0;
}


int main(int argc, char **argv)
{
    int n = atoi(argv[1]);
    for (int i = 1; i<=n; ++i) {
        P[i] = i;
    }

    generate_v2_modified(n, n);
    //gen_permutation(n, n);
    //for (int j=1; j<=n; ++j) {
    //    cout<<"P["<<j<<"]"<<P[j]<<" ";
    //}
    //cout<<endl;
}
















/* vim: set ts=256 sw=4 sts=4 tw=80 expandtab noet: */
