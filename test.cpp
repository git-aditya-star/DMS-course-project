#include<bits/stdc++.h>
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


void select(vector<string> query_select){
    
    bool all =false;
    if(query_select[1] ==  "*"){
        all = true;
    }
    vector<string> cols_name;
    vector<string> table_names;

    int from_index;
    int where_index;
    int end_index;

    for(int i =0;i < query_select.size();i++){
        if(query_select[i] == "from"){
            from_index =i;
        }    
        if(query_select[i] == "where"){
            where_index = i;
        }
        if(query_select[i] == ";"){
            end_index = i;
        }
    }

    for(int i = from_index+1; i<where_index;i++){
        if(query_select[i] != ","){
            table_names.push_back(query_select[i]);
        }
    }

    if(all == true){
        for(int i =0;i<table_names.size();i++){
            string table_name = table_names[i];
            string table_path = table_name+".txt";
            ifstream table(table_path);
            cout<<endl;
            if(table.good()){
                string line;
                getline(table, line);
                cout.flush();
                
                stringstream ss(line);

                while (ss.good()) {
                    string substr;
                    getline(ss, substr, '#');
                    cols_name.push_back(substr);
                }


            table.close();
            }
            else{
                cout<<"Table does not exists"<<endl;
                return ;

            }
        }
    }
    else{
        for(int i = 1; i<from_index;i++){
            if(query_select[i] != ","){
                cols_name.push_back(query_select[i]);
            }
        }
    }

    // for(int i =0;i<table_names.size();i++){
    //     cout<<table_names[i]<<" ";
    // }
    // cout<<endl;
    // for(int i =0;i<cols_name.size();i++){
    //     cout<<cols_name[i]<<" ";
    // }
    // cout<<endl;
    vector<vector<string>> condition;
    vector<string> temp;
    bool andd = false;
    bool orr = false;
    for(int i = where_index+1; i< end_index;i++){
    if(query_select[i] != "and" && query_select[i] != "or"){
        temp.push_back(query_select[i]);
    }
    else{
        if(query_select[i] == "and"){
            andd = true;
        }
        else{
            orr = true;
        }
        condition.push_back(temp);
        temp.clear();
    }
    // if(i - where_index == 3){
    //     condition.push_back(temp);
    //     temp.clear();
    // }
    
        //condition.push_back(query_select[i]);
    }
    condition.push_back(temp);

    // for(int i =0 ;i<condition.size();i++){    //print conditions 
    //     for(int j =0;j<condition[i].size();j++){
    //         cout<<condition[i][j] <<" ";

    //     }
    //     cout<<endl;
    // }
   
    // for(int i=0;i<condition.size();i++){
    //     cout<<condition[i]<<" ";
    // }

    //string attr = condition[0];
    //int attr_index;

    vector<int> attr_indexes;


    // string oper = condition[1];
    // string value = condition[2];

    vector<int> cols_index;


     string table_name = table_names[0];
            string table_path = table_name+".txt";
            ifstream table(table_path);
            cout<<endl;
            
            if(table.good()){
                   
                int count =1;
                int count1 =1;
                vector<pair<string, int>> all_cols;
                while(!table.eof()){
                    string line;
                    getline(table, line);
                    cout.flush();
                    //cout<<line<<endl;           //print table line
                    stringstream ss(line);
                    vector<string> tuple;
                    while (ss.good()) {
                        string substr;
                        getline(ss, substr, '#');
                        tuple.push_back(substr);
                    }

                    

                    
                    if(count == 1){
                        for(int i =0;i<condition.size();i++){

                            for(int i1 =0;i1< tuple.size();i1++){
                                if((tuple[i1]) == condition[i][0]){
                                    attr_indexes.push_back(i1);
                                }
                            }
                        }
                        
                        if(all == false){
                            for(int i = 0;i<cols_name.size();i++){
                                for(int i1 =0;i1<tuple.size();i1++){
                                   if(tuple[i1] == cols_name[i]){
                                       cols_index.push_back(i1);
                                   } 
                                }
                            }
                        }
                        count++;
                    
                    }
                    
                    
                    


                    // if(count == 1){
                    //     for(int i1 =0;i1< tuple.size();i1++){

                    //         if(attr == tuple[i1]){
                    //             attr_index = i1;
                    //         }
                    //         for(int i =0;i<condition.size();i++){
                    //             if(tuple[i1] == condition[i][0]){
                    //                 attr_indexes.push_back(i1);
                    //             }
                    //         }

                    //         if(all == false){
                    //             for(int i2 =0;i2< cols_name.size();i2++){
                    //                 if(tuple[i1] == cols_name[i2]){
                    //                     //cout<<"i1 "<<i1<< endl;
                    //                     cols_index.push_back(i2);
                    //                 }   
                    //             }
                    //         }
                    //         //all_cols.push_back(tuple[i1], i1);
                    //     }
                    //     count++;
                    // }
                    // for(int i=0;i<cols_index.size();i++){
                    //     cout<<cols_index[i]<<" ";
                    // }
                    // cout<<endl;
                   
                    if(all == true){                //printing column names
                        if(count1 == 1){
                        for(int i2 =0;i2 < cols_name.size();i2++){
                                    cout<<cols_name[i2]<<"\t";
                                }
                                cout<<endl;
                                count1++;
                        }
                    }
                    else{
                        if(count1 == 1){
                        for(int i2 =0;i2 < cols_name.size();i2++){
                                    cout<<cols_name[i2]<<"\t";
                                }
                                cout<<endl;
                                count1++;
                        }
                    }
                   
                    //cout<<condition[0].size();
                    int and_count = 0;
                    int or_count =0;

                    for(int j1 = 0;j1 < condition.size();j1++){
                        
                        string oper = condition[j1][1];
                        string attr = condition[j1][0];
                        string value = condition[j1][2];
                        //cout<<attr<<" "<<oper<<" "<<value;
                    if(oper == "=="){
                        if(all == true){
                            //cout<<andd;
                            if(andd == true){
                                
                                if(tuple[attr_indexes[j1]] == value){
                                    
                                    if(and_count == condition.size() -1 ){
                                    for(int i2 = 0; i2< tuple.size();i2++){
                                        cout<<tuple[i2]<<"\t";
                                    }
                                    cout<<endl;
                                }
                                else{
                                    and_count++;
                                }
                                }
                            }  
                            else if(orr == true){
                                    //cout<<"\n"<<tuple[attr_indexes[j1]]<<" "<<value;
                                    if(tuple[attr_indexes[j1]] == value){
                                        
                                                for(int i2 = 0; i2< tuple.size();i2++){
                                                    cout<<tuple[i2]<<"\t";
                                                }
                                                cout<<endl; 
                                                break;
                                           
                                    
                                }
                                
                                //cout<<or_count<<endl;
                            }
                            
                            else{
                                //cout<<tuple[attr_indexes[j1]]<<" "<<value<<endl;
                                if(tuple[attr_indexes[j1]] == value){
                                    for(int i2 = 0; i2< tuple.size();i2++){
                                        cout<<tuple[i2]<<"\t";
                                    }
                                    cout<<endl;
                                }
                            }

                           
                        }
                        else{
                             if(andd == true){
                                 if(tuple[attr_indexes[j1]] == value){
                                    
                                    if(and_count == condition.size() -1 ){
                                    for(int i2 = 0; i2< cols_index.size();i2++){
                                        cout<<tuple[cols_index[i2]]<<"\t";
                                    }
                                    cout<<endl;
                                }
                                else{
                                    and_count++;
                                }
                                }
                            }  
                            else if(orr == true){
                                    if(tuple[attr_indexes[j1]] == value){
                                        
                                               for(int i2 = 0; i2< cols_index.size();i2++){
                                        cout<<tuple[cols_index[i2]]<<"\t";
                                    }
                                    cout<<endl;
                                                break;
                                           
                                    
                                }
                            }
                            else{
                                if(tuple[attr_indexes[j1]] == value){
                                    for(int i2 = 0; i2< cols_index.size();i2++){
                                        cout<<tuple[cols_index[i2]]<<"\t";
                                    }
                                    cout<<endl;
                                }
                            }



                            
                        }

                    }
                    else if(oper == "!="){
                        if(count1 == 2){
                            continue;
                            count1++;
                        }

                        if(all == true){
                            //cout<<andd;
                            if(andd == true){
                                
                                if(tuple[attr_indexes[j1]] != value){
                                    
                                    if(and_count == condition.size() -1 ){
                                    for(int i2 = 0; i2< tuple.size();i2++){
                                        cout<<tuple[i2]<<"\t";
                                    }
                                    cout<<endl;
                                }
                                else{
                                    and_count++;
                                }
                                }
                            }  
                            else if(orr == true){
                                    //cout<<"\n"<<tuple[attr_indexes[j1]]<<" "<<value;
                                    if(tuple[attr_indexes[j1]] != value){
                                        
                                                for(int i2 = 0; i2< tuple.size();i2++){
                                                    cout<<tuple[i2]<<"\t";
                                                }
                                                cout<<endl; 
                                                break;
                                           
                                    
                                }
                                
                                //cout<<or_count<<endl;
                            }
                            
                            else{
                                //cout<<tuple[attr_indexes[j1]]<<" "<<value<<endl;
                                if(tuple[attr_indexes[j1]] != value){
                                    for(int i2 = 0; i2< tuple.size();i2++){
                                        cout<<tuple[i2]<<"\t";
                                    }
                                    cout<<endl;
                                }
                            }

                           
                        }
                        else{
                             if(andd == true){
                                 if(tuple[attr_indexes[j1]] != value){
                                    
                                    if(and_count == condition.size() -1 ){
                                    for(int i2 = 0; i2< cols_index.size();i2++){
                                        cout<<tuple[cols_index[i2]]<<"\t";
                                    }
                                    cout<<endl;
                                }
                                else{
                                    and_count++;
                                }
                                }
                            }  
                            else if(orr == true){
                                    if(tuple[attr_indexes[j1]] != value){
                                        
                                               for(int i2 = 0; i2< cols_index.size();i2++){
                                        cout<<tuple[cols_index[i2]]<<"\t";
                                    }
                                    cout<<endl;
                                                break;
                                           
                                    
                                }
                            }
                            else{
                                if(tuple[attr_indexes[j1]] != value){
                                    for(int i2 = 0; i2< cols_index.size();i2++){
                                        cout<<tuple[cols_index[i2]]<<"\t";
                                    }
                                    cout<<endl;
                                }
                            }



                            
                        }

                    }

                    else if(oper == ">="){
                        stringstream decimal(tuple[attr_indexes[j1]]);
                        stringstream decimal_value(value);
                        double value1 =0 ;
                        double getValue = 0;
                        try{
                        
                        decimal >> getValue;
                        decimal_value >> value1;
                        }
                        catch(exception e){
                            cout<<"error"<<endl;
                        }
                        
                        
                        
                        if(getValue == 0 || value1 == 0){
                            break;
                        }
                            if(all == true){
                            //cout<<andd;
                            if(andd == true){
                                
                                if(getValue >= value1){
                                    
                                    if(and_count == condition.size() -1 ){
                                    for(int i2 = 0; i2< tuple.size();i2++){            // 1 
                                        cout<<tuple[i2]<<"\t";
                                    }
                                    cout<<endl;
                                    }
                                    else{
                                        and_count++;
                                    }
                                }
                            }  
                            else if(orr == true){
                                    //cout<<"\n"<<tuple[attr_indexes[j1]]<<" "<<value;
                                    if(getValue >= value1){
                                        
                                                for(int i2 = 0; i2< tuple.size();i2++){
                                                    cout<<tuple[i2]<<"\t";
                                                }
                                                cout<<endl; 
                                                break;
                                           
                                    
                                }
                                
                                //cout<<or_count<<endl;
                            }
                            
                            else{
                                //cout<<tuple[attr_indexes[j1]]<<" "<<value<<endl;
                                if(getValue >= value1){
                                    for(int i2 = 0; i2< tuple.size();i2++){
                                        cout<<tuple[i2]<<"\t";
                                    }
                                    cout<<endl;
                                }
                            }

                           
                        }
                        else{
                             if(andd == true){
                                 if(getValue >= value1){
                                    
                                    if(and_count == condition.size() -1 ){
                                    for(int i2 = 0; i2< cols_index.size();i2++){
                                        cout<<tuple[cols_index[i2]]<<"\t";
                                    }
                                    cout<<endl;
                                }
                                else{
                                    and_count++;
                                }
                                }
                            }  
                            else if(orr == true){
                                    if(getValue >= value1){
                                        
                                               for(int i2 = 0; i2< cols_index.size();i2++){
                                        cout<<tuple[cols_index[i2]]<<"\t";
                                    }
                                    cout<<endl;
                                                break;
                                           
                                    
                                }
                            }
                            else{
                                if(getValue >= value1){
                                    for(int i2 = 0; i2< cols_index.size();i2++){
                                        cout<<tuple[cols_index[i2]]<<"\t";
                                    }
                                    cout<<endl;
                                }
                            }



                            
                        }
                    }
                    else if(oper == "<="){
                            stringstream decimal(tuple[attr_indexes[j1]]);
                        stringstream decimal_value(value);
                        double value1 =0 ;
                        double getValue = 0;
                        try{
                        
                        decimal >> getValue;
                        decimal_value >> value1;
                        }
                        catch(exception e){
                            cout<<"error"<<endl;
                        }
                        
                        
                        
                        if(getValue == 0 || value1 == 0){
                            break;
                        }
                            if(all == true){
                            //cout<<andd;
                            if(andd == true){
                                
                                if(getValue <= value1){
                                    
                                    if(and_count == condition.size() -1 ){
                                    for(int i2 = 0; i2< tuple.size();i2++){
                                        cout<<tuple[i2]<<"\t";
                                    }
                                    cout<<endl;
                                }
                                else{
                                    and_count++;
                                }
                                }
                            }  
                            else if(orr == true){
                                    //cout<<"\n"<<tuple[attr_indexes[j1]]<<" "<<value;
                                    if(getValue <= value1){
                                        
                                                for(int i2 = 0; i2< tuple.size();i2++){
                                                    cout<<tuple[i2]<<"\t";
                                                }
                                                cout<<endl; 
                                                break;
                                           
                                    
                                }
                                
                                //cout<<or_count<<endl;
                            }
                            
                            else{
                                //cout<<tuple[attr_indexes[j1]]<<" "<<value<<endl;
                                if(getValue <= value1){
                                    for(int i2 = 0; i2< tuple.size();i2++){
                                        cout<<tuple[i2]<<"\t";
                                    }
                                    cout<<endl;
                                }
                            }

                           
                        }
                        else{
                             if(andd == true){
                                 if(getValue <= value1){
                                    
                                    if(and_count == condition.size() -1 ){
                                    for(int i2 = 0; i2< cols_index.size();i2++){
                                        cout<<tuple[cols_index[i2]]<<"\t";
                                    }
                                    cout<<endl;
                                }
                                else{
                                    and_count++;
                                }
                                }
                            }  
                            else if(orr == true){
                                    if(getValue <= value1){
                                        
                                               for(int i2 = 0; i2< cols_index.size();i2++){
                                        cout<<tuple[cols_index[i2]]<<"\t";
                                    }
                                    cout<<endl;
                                                break;
                                           
                                    
                                }
                            }
                            else{
                                if(getValue <= value1){
                                    for(int i2 = 0; i2< cols_index.size();i2++){
                                        cout<<tuple[cols_index[i2]]<<"\t";
                                    }
                                    cout<<endl;
                                }
                            }



                            
                        }

                    }
                    
                    else if(oper == ">"){
                         stringstream decimal(tuple[attr_indexes[j1]]);
                        stringstream decimal_value(value);
                        double value1 =0 ;
                        double getValue = 0;
                        try{
                        
                        decimal >> getValue;
                        decimal_value >> value1;
                        }
                        catch(exception e){
                            cout<<"error"<<endl;
                        }
                        
                        
                        
                        if(getValue == 0 || value1 == 0){
                            break;
                        }
                            if(all == true){
                            //cout<<andd;
                            if(andd == true){
                                
                                if(getValue > value1){
                                    
                                    if(and_count == condition.size() -1 ){
                                    for(int i2 = 0; i2< tuple.size();i2++){
                                        cout<<tuple[i2]<<"\t";
                                    }
                                    cout<<endl;
                                }
                                else{
                                    and_count++;
                                }
                                }
                            }  
                            else if(orr == true){
                                    //cout<<"\n"<<tuple[attr_indexes[j1]]<<" "<<value;
                                    if(getValue > value1){
                                        
                                                for(int i2 = 0; i2< tuple.size();i2++){
                                                    cout<<tuple[i2]<<"\t";
                                                }
                                                cout<<endl; 
                                                break;
                                           
                                    
                                }
                                
                                //cout<<or_count<<endl;
                            }
                            
                            else{
                                //cout<<tuple[attr_indexes[j1]]<<" "<<value<<endl;
                                if(getValue > value1){
                                    for(int i2 = 0; i2< tuple.size();i2++){
                                        cout<<tuple[i2]<<"\t";
                                    }
                                    cout<<endl;
                                }
                            }

                           
                        }
                        else{
                             if(andd == true){
                                 if(getValue > value1){
                                    
                                    if(and_count == condition.size() -1 ){
                                    for(int i2 = 0; i2< cols_index.size();i2++){
                                        cout<<tuple[cols_index[i2]]<<"\t";
                                    }
                                    cout<<endl;
                                }
                                else{
                                    and_count++;
                                }
                                }
                            }  
                            else if(orr == true){
                                    if(getValue > value1){
                                        
                                               for(int i2 = 0; i2< cols_index.size();i2++){
                                        cout<<tuple[cols_index[i2]]<<"\t";
                                    }
                                    cout<<endl;
                                                break;
                                           
                                    
                                }
                            }
                            else{
                                if(getValue > value1){
                                    for(int i2 = 0; i2< cols_index.size();i2++){
                                        cout<<tuple[cols_index[i2]]<<"\t";
                                    }
                                    cout<<endl;
                                }
                            }



                            
                        }

                    }
                    else if(oper == "<"){
                        stringstream decimal(tuple[attr_indexes[j1]]);
                        stringstream decimal_value(value);
                        double value1 =0 ;
                        double getValue = 0;
                        try{
                        
                        decimal >> getValue;
                        decimal_value >> value1;
                        }
                        catch(exception e){
                            cout<<"error"<<endl;
                        }
                        
                        
                        
                        if(getValue == 0 || value1 == 0){
                            break;
                        }
                            if(all == true){
                            //cout<<andd;
                            if(andd == true){
                                
                                if(getValue < value1){
                                    
                                    if(and_count == condition.size() -1 ){
                                    for(int i2 = 0; i2< tuple.size();i2++){
                                        cout<<tuple[i2]<<"\t";
                                    }
                                    cout<<endl;
                                }
                                else{
                                    and_count++;
                                }
                                }
                            }  
                            else if(orr == true){
                                    //cout<<"\n"<<tuple[attr_indexes[j1]]<<" "<<value;
                                    if(getValue < value1){
                                        
                                                for(int i2 = 0; i2< tuple.size();i2++){
                                                    cout<<tuple[i2]<<"\t";
                                                }
                                                cout<<endl; 
                                                break;
                                           
                                    
                                }
                                
                                //cout<<or_count<<endl;
                            }
                            
                            else{
                                //cout<<tuple[attr_indexes[j1]]<<" "<<value<<endl;
                                if(getValue < value1){
                                    for(int i2 = 0; i2< tuple.size();i2++){
                                        cout<<tuple[i2]<<"\t";
                                    }
                                    cout<<endl;
                                }
                            }

                           
                        }
                        else{
                             if(andd == true){
                                 if(getValue < value1){
                                    
                                    if(and_count == condition.size() -1 ){
                                    for(int i2 = 0; i2< cols_index.size();i2++){
                                        cout<<tuple[cols_index[i2]]<<"\t";
                                    }
                                    cout<<endl;
                                }
                                else{
                                    and_count++;
                                }
                                }
                            }  
                            else if(orr == true){
                                    if(getValue < value1){
                                        
                                               for(int i2 = 0; i2< cols_index.size();i2++){
                                        cout<<tuple[cols_index[i2]]<<"\t";
                                    }
                                    cout<<endl;
                                                break;
                                           
                                    
                                }
                            }
                            else{
                                if(getValue < value1){
                                    for(int i2 = 0; i2< cols_index.size();i2++){
                                        cout<<tuple[cols_index[i2]]<<"\t";
                                    }
                                    cout<<endl;
                                }
                            }



                            
                        }


                    }
                    }

                
                
                
                
                }

            }
    
    
    

    
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
        else if(query[0] ==  "select"){
            select(query);
            cout<<endl;
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