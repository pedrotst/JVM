#include <iostream>
#include <map>
#include <string>

using namespace std;

int main(){
    map<string, string> m;

    m["asdf"] = "inseri";
    m["asdf1"] = "inseri2";

    //cout << m["asdf"] << endl;

    if((m.find("asdf") != m.end())){
        cout << m["asdf"] << endl;
    }
    return 0;
}
