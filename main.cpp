#include<iostream>
#include<fstream>
#include<string>
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
    fileTheTu << id << " " << defaultpin << endl;
    fileTheTu.close();

}
int main(){
    //hienthiTheTu();
    themtk();
    return 0;
}
