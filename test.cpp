#include<bits/stdc++.h>
using namespace std;


void createTable(vector<string> query_create){ 
    // for(auto i: query_create){
    //     cout<<i<<endl;
    // }
    ofstream fout, fout_table;

    fout.open("schema.txt",std::ios_base::app);
    
    cout<<endl;
    string table_name = query_create[2];
    fout_table.open(table_name, std::ios_base::app);
    
    for(int j = 3; j<query_create.size();j++){
        if(query_create[j] == "int"){
            fout<<table_name<<"#"<<query_create[j-1]<<"#"<<query_create[j]<<endl;
            fout_table<<query_create[j-1]<<"#";
        }
        else if(query_create[j] == "decimal"){
            fout<<table_name<<"#"<<query_create[j-1]<<"#"<<query_create[j]<<endl;
            fout_table<<query_create[j-1]<<"#";
        }
        else if(query_create[j].substr(0,4) == "char"){
            fout<<table_name<<"#"<<query_create[j-1]<<"#"<<query_create[j]<<endl;
            fout_table<<query_create[j-1]<<"#";
        }
    }
    fout.close();
    fout_table.close();
    cout<<"Table created successfully"<<endl;
    

    
    fout.open(table_name, std::ios_base::app);


}


int main(){

    // system("CLS");
    string a;
    getline(cin,a);
    stringstream s1(a);
    string s2;
    vector<string> query;

    while(s1>>s2){
        query.push_back(s2);
        
    }
   
    while(query[0] != "quit"){ 
        

        if(query[0] == "create"){
            createTable(query);
        }


        query.clear();
        string a;
        getline(cin,a);
        stringstream s1(a);
        string s2;
        

        while(s1>>s2){
            query.push_back(s2);
            
        }

    }
    


    return 0;


}