#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>
using namespace std; 

class aqpd_key{
    public:
        aqpd_key();
        int AdID;
        int QueryID;
        int Position;
        int Depth;
        
        void getdata(int ,int ,int ,int );
        
        friend std::ostream& operator<<(std::ostream&, const aqpd_key&);
};

aqpd_key::aqpd_key(){
    AdID = 0;
    QueryID = 0;
    Position = 0;
    Depth = 0;
}

void aqpd_key::getdata(int a,int q,int p,int d){
    AdID = a;
    QueryID = q;
    Position = p;
    Depth = d;
}

std::ostream& operator<<(std::ostream& out, const aqpd_key& a){
    out<<a.AdID<<";"<<a.QueryID<<";"<<a.Position<<";"<<a.Depth;
    return out;
}

class rest_data{
    public:
        rest_data(){};
        string DisplayURL;
        int AdvertiserID;
        int KeywordID;
        int TitleID;
        int DescriptionID;
        
        int Click;
        int Impression;
        
        void getdata(string ,int ,int ,int ,int ,int ,int );
        
        friend std::ostream& operator<<(std::ostream&, const rest_data&);        
};

void rest_data::getdata(string s,int a,int k,int t,int d,int c,int i){
    DisplayURL = s;
    AdvertiserID = a;
    KeywordID = k;
    TitleID = t;
    DescriptionID = d;
    Click = c;
    Impression = i;    
}

std::ostream& operator<<(std::ostream& out, const rest_data& a){
    out<<a.DisplayURL<<";"<<a.AdvertiserID<<";"<<a.KeywordID<<";"<<a.TitleID<<";"<<a.DescriptionID<<";"<<a.Click<<";"<<a.Impression;
    return out;
}

class for_impressed{
    public:
        for_impressed(){};
        int AdID;
        string DisplayURL;
        int AdvertiserID;
        int KeywordID;
        int TitleID;
        int DescriptionID;
        void getdata(int ,string ,int ,int ,int ,int );        
};

void for_impressed::getdata(int a,string url,int ad,int k,int t,int d){
    AdID = a;
    DisplayURL = url;
    AdvertiserID = ad;
    KeywordID = k;
    TitleID = t;
    DescriptionID = d;    
}

class for_profit{
    public:
        for_profit(){total_Click=0;total_Impression=0;};
        int total_Click;
        int total_Impression;
        for_profit operator+=(for_profit );
        void getdata(int ,int );
};

for_profit for_profit::operator+=(for_profit a){
    total_Click = total_Click + a.total_Click;
    total_Impression = total_Impression + a.total_Impression;
}

void for_profit::getdata(int c,int i){
    total_Click = c;
    total_Impression = i;    
}

struct strCompare{
	bool operator()(aqpd_key a, aqpd_key b){
		if(a.AdID!=b.AdID){
            return(a.AdID<b.AdID);
        }
        else{
            if(a.QueryID!=b.QueryID){
                return(a.QueryID<b.QueryID);
            }
            else{
                if(a.Position!=b.Position){
                    return(a.Position<b.Position);
                }
                else{
                    return(a.Depth<b.Depth); 
                }    
            }
        }
	}
};

struct strCompare2{
	bool operator()(for_impressed a, for_impressed b){
		if(a.AdID!=b.AdID){
            return(a.AdID<b.AdID);
        }
        else{
            if(a.AdvertiserID!=b.AdvertiserID){
                return(a.AdvertiserID<b.AdvertiserID);
            }
            else{
                if(a.KeywordID!=b.KeywordID){
                    return(a.KeywordID<b.KeywordID);
                }
                else{
                    if(a.TitleID!=b.TitleID){
                        return(a.TitleID<b.TitleID);
                    }
                    else{
                        return(a.DescriptionID<b.DescriptionID);
                    }
                } 
            }    
        }
	}
};

typedef vector<map<aqpd_key , vector<rest_data>, strCompare > > datastruct;
typedef map<int,map<int,for_profit> > type_profit;

void get(const int UserID,const int a,const int q,const int p,const int d,datastruct& user){
    int c=0,imp=0;
    aqpd_key aqpd_get;
    aqpd_get.getdata(a,q,p,d);
    for(int j=0;j<(user[UserID][aqpd_get]).size();j++){
        c=c+(user[UserID][aqpd_get])[j].Click;
        imp=imp+(user[UserID][aqpd_get])[j].Impression;
    }
    
    cout<<"********************"<<endl;
    cout<<c<<" "<<imp<<endl;
    cout<<"********************"<<endl;
}

void clicked(int u, datastruct& user){
    cout<<"********************"<<endl;
    for(map<aqpd_key , vector<rest_data>, strCompare >::iterator i=(user[u]).begin();i!=(user[u]).end();++i){
        for(int j=0;j<(i->second).size();j++){
            if((i->second)[j].Click!=0){
                cout<<(i->first).AdID<<" "<<(i->first).QueryID<<endl;
                break;
            }
        }
    }
    cout<<"********************"<<endl;
}

void impressed(int u1,int u2,datastruct& user){
    cout<<"********************"<<endl;
    int aaa=0;
    for_impressed tmp;
    map<for_impressed,int,strCompare2> data;
    for(map<aqpd_key , vector<rest_data>, strCompare >::iterator i=(user[u1]).begin();i!=(user[u1]).end();++i){
        for(map<aqpd_key , vector<rest_data>, strCompare >::iterator j=(user[u2]).begin();j!=(user[u2]).end();++j){
            if((i->first).AdID == (j->first).AdID){
                for(int k=0;k<(i->second).size();k++){
                    tmp.getdata((i->first).AdID,(i->second)[k].DisplayURL,(i->second)[k].AdvertiserID,(i->second)[k].KeywordID,(i->second)[k].TitleID,(i->second)[k].DescriptionID);
                    data[tmp]=1;
                }
                for(int k=0;k<(j->second).size();k++){
                    tmp.getdata((j->first).AdID,(j->second)[k].DisplayURL,(j->second)[k].AdvertiserID,(j->second)[k].KeywordID,(j->second)[k].TitleID,(j->second)[k].DescriptionID);
                    data[tmp]=1;
                }                
            }
            
        }
    }
    for(map<for_impressed,int,strCompare2>::iterator i=data.begin();i!=data.end();++i){
        if(aaa!=(i->first).AdID){
            cout<<(i->first).AdID<<endl;
            cout<<"\t"<<(i->first).DisplayURL<<" "<<(i->first).AdvertiserID<<" "<<(i->first).KeywordID<<" "<<(i->first).TitleID<<" "<<(i->first).DescriptionID<<endl;
            aaa=(i->first).AdID;
        }
        else{
            cout<<"\t"<<(i->first).DisplayURL<<" "<<(i->first).AdvertiserID<<" "<<(i->first).KeywordID<<" "<<(i->first).TitleID<<" "<<(i->first).DescriptionID<<endl;
        }
    }
    cout<<"********************"<<endl;
}

void profit(int a, float theta, type_profit& map_profit){
    cout<<"********************"<<endl;
    for(map<int,for_profit>::iterator i=(map_profit[a]).begin();i!=(map_profit[a]).end();++i){
        float f=0;
        if((i->second).total_Impression!=0){
            f=float((i->second).total_Click)/float((i->second).total_Impression);
        }
        if(f>=theta){cout<< i->first <<endl;}
    }
    cout<<"********************"<<endl;
}

int main(int argc,char** argv ){
    if(argc!=2){
        cout<<"Error argc!=2";
        return (-1);
    }
    char *filename;
    string line;
    filename = argv[1];
    int Click,Impression,AdID,AdvertiserID,Depth,Position,QueryID,KeywordID,TitleID,DescriptionID,UserID;
    aqpd_key aqpd;
    rest_data rest;
    for_profit uci;
    type_profit map_profit;
    char DisplayURL[30];
    datastruct user(24000000);
    FILE *file;
    file = fopen(filename,"r");
    fscanf(file,"%d%d%s%d%d%d%d%d%d%d%d%d",&Click,&Impression,&DisplayURL,&AdID,&AdvertiserID,
           &Depth,&Position,&QueryID,&KeywordID,&TitleID,&DescriptionID,&UserID);
    while (!feof(file)){
        aqpd.getdata(AdID,QueryID,Position,Depth);
        rest.getdata(DisplayURL,AdvertiserID,KeywordID,TitleID,DescriptionID,Click,Impression);
        (user[UserID][aqpd]).push_back(rest);
        uci.getdata(Click,Impression);
        map_profit[AdID][UserID]+=uci;
        fscanf(file,"%d%d%s%d%d%d%d%d%d%d%d%d",&Click,&Impression,&DisplayURL,&AdID,&AdvertiserID,
               &Depth,&Position,&QueryID,&KeywordID,&TitleID,&DescriptionID,&UserID);          
    }          
//    cout<<"command : "<<endl;
    
    while(1){
        string command;
        cin>>command;
        if(command!="quit"){
            if(command=="get"){
                int u_get,a_get,q_get,p_get,d_get;
                cin>>u_get>>a_get>>q_get>>p_get>>d_get;
                get(u_get,a_get,q_get,p_get,d_get,user);
            }
            else if(command=="clicked"){
                int u_clicked;
                cin>>u_clicked;
                clicked(u_clicked,user);
            }
            else if(command=="impressed"){
                int u1,u2;
                cin>>u1>>u2;
                impressed(u1,u2,user);
            }
            else if(command=="profit"){
                int a;
                float theta;
                cin>>a>>theta;
                profit(a,theta,map_profit);
            }
//            else{
//                cout<<"error command"<<endl;
//            }
        }
        else break;
    }

    //system("pause");

}
