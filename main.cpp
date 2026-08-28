#include<iostream>
#include<fstream>
#include<string>
#include <cstdio>
using namespace std;

struct TheTu{
    string ID;
    string pin;
};
struct TaiKhoan{
    string ID;
    string name;
    long long accBalance;
    string currency;
};

void hienthiTheTu()
{
    string filename = "TheTu.txt";
    ifstream file(filename);
    string line;
    while(getline(file, line)){
        cout<< line << endl;
    }
    file.close();
}
void themtk(){
    string id;
    cin >> id;
    string defaultpin= "123456";
    ofstream fileTheTu("TheTu.txt", ios::app);
    cout << endl;
    fileTheTu <<  id << " " << defaultpin << endl;
    fileTheTu.close();
    
    //add file id tk vua them
    string tenFileTaiKhoan = id + ".txt";
    ofstream fileTaiKhoan(tenFileTaiKhoan);
    fileTaiKhoan << "ID: " << id << endl;
    fileTaiKhoan << "PIN: " << defaultpin << endl;
    
    //add file lichsuid tk vua them
    string tenfileLichSu = "LichSu" + id + ".txt" ;
    ofstream fileLichSu(tenfileLichSu);
    fileLichSu << "ID: " << id << endl;
    fileLichSu << "Lich su giao dich:" << endl;
}
void xoatk(){
    string id;
    cout << "nhap id tk can xoa";
    cin >> id;
    string tenfile = id + ".txt";
    //xoa file id
    if(remove(tenfile.c_str())==0){
        cout <<"Xoa file " << tenfile << endl;
    }
    else {
        cout << "khong tim thay file " << tenfile << endl;
    }
    //update thetu.txt = NewTheTu 
    ifstream oldfile("TheTu.txt");
    if(!oldfile){
        cout << "ko mo dc file TheTu.txt" <<endl;
        return;
    }
    ofstream newfile("NewTheTu.txt");
    string idfile;
    string pin;
    while(oldfile >> idfile >> pin){
        if(idfile != id){
            newfile << idfile << " "<< pin << endl;
        }
    }
    oldfile.close();
    newfile.close();
    //xoa file thetu va rename newTheTu
    remove("TheTu.txt");
    rename("NewTheTu.txt", "TheTu.txt");
    cout <<"da xoa va cap nhap thanh cong"<< endl;
}
int main(){
    //hienthiTheTu();
    //themtk();
    xoatk();
    return 0;
}
