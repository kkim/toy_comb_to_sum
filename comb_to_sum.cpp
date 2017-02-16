#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>

using namespace std;


typedef vector<vector<long> > combs;

void print_vv(const combs & vv)
{
  for(int ii = 0; ii<vv.size(); ++ii)
  {
    cout<<"(";
    for(int jj = 0; jj<vv[ii].size(); ++jj)
    {
      cout<<vv[ii][jj];
      if (jj<vv[ii].size()-1) cout<<",";
    }
    cout<<")"<<endl;
  }
}

combs merge(const combs& vv, const combs& vv0)
{
  int vvs = vv.size(), vv0s = vv0.size();
  combs vv1(vvs + vv0s);
  int ii = 0; 
  for(ii = 0; ii<vvs; ++ii)
    vv1[ii] = vv[ii];
  for(; ii<vvs+ vv0s; ++ii)
    vv1[ii] = vv0[ii-vvs];
  return vv1;
}

long sum(const vector<long>& s, int last_ind)
{
  long sum = 0;
  for(int ii = 0; ii<=last_ind; ++ii)
    sum+=s[ii];
  return sum;
}

int count_elements_less_than_or_eq(const vector<long>& s, long v)
{
  int c = 0;
  for(int ii = 0; ii<s.size(); ++ii)
    if(s[ii]<=v) c++;
  return c;
}

long int get_comb_call = 0;

combs get_comb(const vector<long>& s, int last_ind, long v)
{
  combs vv, vv0;
  get_comb_call++;
  
  if(get_comb_call%100000==0) fprintf(stdout,"%d\r",get_comb_call);

  if(s[last_ind]==v)
  {
    vv.resize(1);
    vv[0].resize(1);
    vv[0][0] = v;
  }
  if(last_ind == 0)
  {
    return vv;
  }

  if(sum(s, last_ind)<v) return vv;

  if(s[last_ind]<v)
  {
    vv0=get_comb(s, last_ind-1, v-s[last_ind]);
    for(int ii = 0; ii<vv0.size(); ++ii)
      vv0[ii].push_back(s[last_ind]);
    vv = merge(vv, vv0);
  }


  // s[last_ind]>v-->skip this one
  vv0=get_comb(s, last_ind-1, v);
  vv = merge(vv, vv0);
  
  return vv;
}



int main()
{
  int n, m;
  vector<long> s, v;
  combs vvs;
  cin>>n;
  s.resize(n);
  for(int ii = 0; ii<n; ++ii)
    cin>>s[ii];
  sort(s.begin(), s.end());
  s.erase( unique( s.begin(), s.end() ), s.end() );


  cin>>m;
  v.resize(m);
  for(int ii = 0; ii<m; ++ii)
    cin>>v[ii];

  sort(v.begin(), v.end());

  for(int ii = 0; ii<m; ++ii)
  {
    get_comb_call = 0;
    cout<<"Case of sum = "<<v[ii]<<", n_elements: "<< count_elements_less_than_or_eq(s, v[ii])<<endl;
    vvs = get_comb(s, s.size()-1, v[ii]);
    cout<<vvs.size()<<" combinations, get_comb_calls: "<<get_comb_call<<endl;
    print_vv(vvs);
    cout<<endl;
  }

  return 0;
}
