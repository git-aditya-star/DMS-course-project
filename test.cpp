#include<bits/stdc++.h>
#include <sys/stat.h>
using namespace std;


void createTable(vector<string> query_create){ 
    // for(auto i: query_create){
    //     cout<<i<<endl;
    // }
    ofstream fout, fout_table;

    fout.open("schema.txt",std::ios_base::app);
    
    cout<<endl;
    string table_name = query_create[2]+".txt";
    fout_table.open(table_name, std::ios_base::app);
    
    for(int j = 3; j<query_create.size();j++){
        if(query_create[j] == "int"){
            fout<<query_create[2]<<"#"<<query_create[j-1]<<"#"<<query_create[j]<<endl;
            fout_table<<query_create[j-1]<<"#";
        }
        else if(query_create[j] == "decimal"){
            fout<<query_create[2]<<"#"<<query_create[j-1]<<"#"<<query_create[j]<<endl;
            fout_table<<query_create[j-1]<<"#";
        }
        else if(query_create[j].substr(0,4) == "char"){
            fout<<query_create[2]<<"#"<<query_create[j-1]<<"#"<<query_create[j]<<endl;
            fout_table<<query_create[j-1]<<"#";
        }
    }
    fout.close();
    fout_table.close();
    cout<<"Table created successfully"<<endl;
    

    
    cout<<endl;


}


void describeTable(vector<string> query_describe){
    
    string schema_path = "schema.txt";
    ifstream table(schema_path);
    string table_name = query_describe[1];
    cout<<endl;
    if(table.good()){
        bool exists = false;
        while(table){
        string line;
        getline(table, line);
        cout.flush();
        //cout<<"Checking for table"<<endl;
        if(line.substr(0, table_name.length()) == table_name){
            exists = true;
            for(int i = table_name.length()+1; i<line.length();i++){
                if(line[i] == '#'){
                    cout<<"--";
                    i++;

                }
                cout<<line[i];

            }
            cout<<endl;
        }
        
        }
        if(exists == false){
            cout<<"Table does not exists"<<endl;
        }
        table.close();
    }
    cout<<endl;
   
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
        else if(query[0] == "describe"){
            describeTable(query);
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