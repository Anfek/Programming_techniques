#include <fstream>
#include <iostream>

using namespace std;

void print_to_cmd(std::string str){
    const char *command = str.c_str();
    system(command);
}

int main(){
    print_to_cmd("dir /a /b /-p /o:gen >files.txt");

    string str = "g++ ", buf = "";
    ifstream fin("files.txt");
    if(!fin.is_open()){
        cout << "Can not open file" << endl;
        return 0;
    }


    while (getline(fin, buf)){
        if (buf.size() > 4 && buf!="compile_and_run_me.cpp"){
            string check = buf.substr(buf.size()-4);
            if(check == ".cpp")
                str+= buf + ' ';
        }
        
    }
    fin.close();
    str+="-o lab_5b";
    
    print_to_cmd(str);
    print_to_cmd("lab_5b.exe");
    print_to_cmd("del lab_5b.exe");
    return 0;
}