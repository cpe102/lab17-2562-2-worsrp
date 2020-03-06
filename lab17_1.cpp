#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cctype>
using namespace std;

string calgrade(int score){
    if(score>79) return "A";
    else if (score>69) return "B";
    else if (score>59) return "C";
    else if (score>49) return "D";
    else return "F";
}

void upper(string &cmdline){
    string cmdup;
    for(int i=0;i<cmdline.size();i++){
        cmdup+=toupper(cmdline[i]);
    }
    cmdline = cmdup;

}
void namelinker(vector<string> name,string &namelink){
    string spc=" ";
    for(int i=1;i<name.size();i++){
        if(i==name.size()-1) namelink+=name[i];
        else namelink=namelink+name[i]+spc;

    }
}

void checkcmd(vector<string> cmd,vector<string> name,vector<string> grade,string cmdlink,int &status){
    int flag=0;
    string namelink;
    if(cmd[0]=="NAME"){
        cout << "------------------------------" << "\n";
        for(int i=0;i<name.size();i++){
            namelink = name[i];
            upper(namelink);
            if(cmdlink==namelink) {
                cout << name[i] << "'s grade = " << grade[i] << "\n";
                flag = 1;
            }
        }
        if(flag==0) cout << "Cannot found" << "\n";
        cout << "------------------------------" << "\n";
    }else if(cmd[0]=="GRADE"){
        cout << "------------------------------" << "\n";
        for(int i=0;i<name.size();i++){
            if(grade[i]==cmdlink){
                cout << name[i] << "\n";
            }
        }
        cout << "------------------------------" << "\n";
    }else if(cmd[0]=="EXIT"){
        status=1;
    }else cout << "Invalid command" << "\n";
}

int main(){
    ifstream source;
    source.open("name_score.txt");
    string data;
    char name_data[100];
    vector<string> name,grade;
    vector<int> score;
    char format[] = "%[^:]: %d %d %d";
    int scr1,scr2,scr3,i=0,status=0;
    while(getline(source,data)){
        sscanf(data.c_str(),format,name_data,&scr1,&scr2,&scr3);
        name.push_back(name_data);
        score.push_back(scr1+scr2+scr3);
        grade.push_back(calgrade(score[i]));
        i++;
    }
    do{
        string cmdline,cmdlink;
        vector<string> cmd;
        int start=0;
        cout << "Please input your command : ";
        getline(cin,cmdline);
        upper(cmdline);
        int end = cmdline.find_first_of(" ");
        while (end!=-1){
            cmd.push_back(cmdline.substr(start,end-start));
            start = end+1;
            end=cmdline.find_first_of(" ",start);
        }
        cmd.push_back(cmdline.substr(start,cmdline.size()-start));
        namelinker(cmd,cmdlink);
        checkcmd(cmd,name,grade,cmdlink,status);
    }while(status!=1);
}