#include<bits/stdc++.h>
#include<thread>
#include <unistd.h>
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;

map<string,string> redi;
map<string,set<pair<float,string>>> sortedL;
//No of arguments is not checked.

void del(string key,string time) 
{   int tt=stoi(time);
    sleep(tt);
    redi.erase(key);
}

void delss(string key,string time) 
{   int tt=stoi(time);
    usleep(tt);
    redi.erase(key);
}


int main(){
            vector<thread> threads;
    while(true){
        string str,T;
        getline(cin,str);
        stringstream X(str);
        vector<string>  v;
        while (getline(X, T, ' '))
        {
            v.push_back(T);
        }
        transform(v[0].begin(), v[0].end(),v[0].begin(),::toupper);
        if(v[0].compare("GET")==0){
            if(redi[v[1]]!="")
            cout<<redi[v[1]]<<endl;
            else
            cout<<"(nil)"<<endl;
        }
        else if(v[0].compare("SET")==0){
            transform(v[3].begin(), v[3].end(),v[3].begin(),::toupper);
            if(v[3]=="EX"){
                threads.push_back(thread(del,v[1],v[4])); 
                redi[v[1]]=v[2];
                cout<<"OK"<<endl;
            }
            else if(v[3]=="PX"){
                threads.push_back(thread(delss,v[1],v[4]));
                redi[v[1]]=v[2];
                cout<<"OK"<<endl;
            }
            else if(v[3]=="NX"){
                if(redi[v[1]]==""){
                    redi[v[1]]=v[2];
                    cout<<"OK"<<endl;
                }
                else{
                    cout<<"(nil)"<<endl;
                }
            }
            else if(v[3]=="XX"){
                 if(redi[v[1]]!=""){
                    redi[/* code */v[1]]=v[2];
                    cout<<"OK"<<endl;
                }
                else{
                    cout<<"(nil)"<<endl;
                }
            }
            else if(v[3]=="KEEPTTL"){
                    redi[v[1]]=v[2];
                    cout<<"OK"<<endl;
            }
            else{
                redi[v[1]]=v[2];
                cout<<"OK"<<endl;
            }

        }
        else if(v[0]=="EXPIRE")
        {
            if(redi[v[1]]=="")
            {
                cout<<"(integer) 0";
            }
            else
            {
                threads.push_back(thread(del,v[1],v[2]));
                cout<<"(integer) 1";
            }
            
        }
        else if(v[0]=="ZADD")
        {   auto it=sortedL.find(v[1]);
            for(int a=2;a<v.size();a++){
            float f=stof(v[a]);
            if(it==sortedL.end()){
                set<pair<float,string>> p;
                p.insert(make_pair(f,v[++a]));
                sortedL[v[1]]=p;
                cout<<"(integer) 1"<<endl;
            }
            else{
                it->second.insert(make_pair(f,v[++a]));
                cout<<"(integer) 1"<<endl;
            }
            
        }
        }
        else if(v[0]=="ZRANGE")
        {
             auto it=sortedL.find(v[1]);
             if(it==sortedL.end()){
                 cout<<"(empty list or set)";
             }
             else{
                    int l=stoi(v[2]);
                    if(l<0)
                    l+=it->second.size();
                    int r=stoi(v[3]);
                    if(r<0)
                    r+=it->second.size();
                    transform(v[5].begin(), v[5].end(),v[5].begin(),::toupper);
                 if(v[5]=="WITHSCORES"){
                    int v=0;
                    auto sta=it->second.begin();
                    int set =0;
                    for(int i=0;i<it->second.size();i++){
                        if(l<=v<=r){
                        cout<<sta->second<<endl;
                        cout<<sta->first<<endl;
                        set=1;
                        }
                        sta++;
                        v++;
                        //sta++;
                    }
                    if(set==0){
                        cout<<"(empty list or set)";
                    }
                 }
                 else{
                    int v=0;
                    auto sta=it->second.begin();
                    int set =0;
                    for(int i=0;i<it->second.size();i++){
                        if(l<=v<=r){
                        cout<<sta->second<<endl;
                        set=1;
                        }
                        sta++;
                        v++;
                        //sta++;
                    }
                    if(set==0){
                        cout<<"(empty list or set)";
                    }
                 }
             }
        }
        else if(v[0]=="ZRANK"){
            auto it=sortedL.find(v[1]);
            int i=0;
            int fiun=0;
            for(auto iii=it->second.begin();iii!=it->second.end();iii++){
                if(iii->second==v[2]){
                cout<<"(Integer )"<<i<<endl;
                fiun=1;
                }
                i++;
            }
            if(fiun==0){
                cout<<"(nil)"<<endl;
            }

        }   
        
    }
    threads[0].join();
}