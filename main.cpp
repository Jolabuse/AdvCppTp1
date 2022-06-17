#include <iostream>
#include <list>
#include <vector>
#include <cmath>
#include "parenthesisManager.h"


using namespace std;

vector<std::string> split(vector<std::string> dividedOpe,std::string ope){
    vector<std::string> temp;
    int ind;
    bool cond;
    do{
        cond = false;
        temp.clear();
        for(auto const& s : dividedOpe) {
            if(s != ope) {
                ind = s.find(ope);
                if (ind != string::npos) {
                    temp.push_back(s.substr(0, ind));
                    temp.push_back(s.substr(ind, 1));
                    if (ind != s.length() - 1) {
                        temp.push_back(s.substr(ind + 1, s.length()));
                    }
                    cond = true;
                } else{
                    temp.push_back(s);
                }
            } else{
                temp.push_back(s);
            }
        }
        if(cond){
            dividedOpe = temp;
        }
    } while (cond);
    return dividedOpe;
}
vector<std::string> splitPower(vector<std::string> dividedOpe){
    string ope = "power";
    vector<std::string> temp;
    int ind;
    bool cond;
    do{
        cond = false;
        temp.clear();
        for(auto const& s : dividedOpe) {
            if(s != ope) {
                ind = s.find(ope);
                if (ind != string::npos) {
                    temp.push_back(s.substr(0, ind));
                    temp.push_back(s.substr(ind, 5));
                    if (ind != s.length() - 1) {
                        temp.push_back(s.substr(ind + 5, s.length()));
                    }
                    cond = true;
                } else{
                    temp.push_back(s);
                }
            } else{
                temp.push_back(s);
            }
        }
        if(cond){
            dividedOpe = temp;
        }
    } while (cond);
    return dividedOpe;
}

vector<std::string> splitPar(vector<std::string> dividedOpe){
    vector<std::string> temp;
    string ope = "(";
    int ind;
    bool cond;
    do{
        cond = false;
        temp.clear();
        for(auto const& s : dividedOpe) {
            if(s != ope) {
                ind = s.find(ope);
                if (ind != string::npos) {
                    if(s.substr(0, ind) != ""){
                        temp.push_back(s.substr(0, ind));
                    }
                    temp.push_back(s.substr(ind, 1));
                    if (ind != s.length() - 1) {
                        temp.push_back(s.substr(ind + 1, s.length()));
                    }
                    cond = true;
                } else{
                    temp.push_back(s);
                }
            } else{
                temp.push_back(s);
            }
        }
        if(cond){
            dividedOpe = temp;
        }
    } while (cond);
    return dividedOpe;
}

vector<parenthesisManager> detectParenthesis(vector<string> ope){
    vector<parenthesisManager> pm;
    bool insert;
    for (int i=0;i<ope.size();i++) {
        insert = false;
        if(ope.at(i) == "("){
            for (int j=0;j<pm.size();j++) {
                if(pm.at(j).end == -1){
                    pm.insert(pm.begin()+j,parenthesisManager(i));
                    insert = true;
                    break;
                }
            }
            if(!insert){
                pm.push_back(parenthesisManager(i));
            }
        }
        if (ope.at(i) == ")"){
            for(auto& j : pm){
                if(j.end==-1){
                    j.end = i;
                }
            }
        }

    }
    return pm;
}



vector<std::string> divideOperation(std::string const ope){
    vector<std::string> dividedOpe/*,temp*/;
    /*int ind;
    bool cond;*/
    dividedOpe.push_back(ope);
    dividedOpe = split(dividedOpe,"+");
    dividedOpe = split(dividedOpe,"*");
    dividedOpe = split(dividedOpe,"-");
    dividedOpe = split(dividedOpe,"/");
    dividedOpe = splitPar(dividedOpe);
    dividedOpe = split(dividedOpe,")");
    dividedOpe = split(dividedOpe,"!");
    dividedOpe = splitPower(dividedOpe);
    dividedOpe = split(dividedOpe,"^");
    dividedOpe = split(dividedOpe,"%");
    return dividedOpe;
}

int getPriority(std::string const ope){
    if(ope == "*") {
        return 2;
    }if(ope == "+") {
        return 1;
    }if(ope == "-") {
        return 1;
    }if(ope == "/") {
        return 2;
    }if(ope == "power") {
        return 3;
    }if(ope == "!") {
        return 3;
    }if(ope == "%") {
        return 2;
    }
    if(ope == "^"){
        return 3;
    }
    return -1;
}

vector<int> order(vector<string> ope){
    vector<int> order;
    bool insert;
    for(int i=0;i<ope.size();i++){
        if (getPriority(ope.at(i)) != -1){
            insert= false;
            for(int j=0;j<order.size();j++){
                if(getPriority(ope.at(i)) > getPriority(ope.at(order.at(j)))){
                    order.insert(order.begin()+j,i);
                    insert = true;
                    break;
                }
            }
            if(!insert){
                order.push_back(i);
            }
        }
    }
    return order;
}

int operator % (string a, string b){
    return stoi(a)% stoi(b);
}

double operator ^(string a, string b){
    double res = 1,a1 = stod(a),realPart,intPart;
    realPart = std::modf(stod(b),&intPart);
    if(realPart != 0.5) {
        if(realPart == 0) {
            for (int i = 0; i < stoi(b); i++) {
                res = res * a1;
            }
        }
        else{
            throw std::invalid_argument("error");
        }
    }else
    {
        for (int i = 0; i < intPart; i++) {
            res = res * a1;
        }
        res = res* sqrt(a1);
    }
    return res;
}

int operator !(string a){
    int res = 1;
    for(int i=2;i<=stoi(a);i++){
        res=res*i;
    }
    return res;
}

double resGivenOpe(vector<string> ope){
    if(ope.at(1) == "*"){
        return stod(ope.at(0)) * stod(ope.at(2));
    }
    if(ope.at(1) == "+"){
        return stod(ope.at(0)) + stod(ope.at(2));
    }
    if(ope.at(1) == "-"){
        return stod(ope.at(0)) - stod(ope.at(2));
    }
    if(ope.at(1) == "/"){
        return stod(ope.at(0)) / stod(ope.at(2));
    }
    if(ope.at(1) == "!"){
        return !ope.at(0);
    }
    if(ope.at(1) == "%"){
        return ope.at(0) % ope.at(2);
    }
    if(ope.at(1) == "power"){
        return ope.at(0) ^ ope.at(2);
    }
    if(ope.at(1) == "^"){
        return ope.at(0) ^ ope.at(2);
    }
}

double doOperation(vector<string> ope){
    vector<int> ord;
    double res;
    int ind;
    while (ope.size() > 1){
        ord.clear();
        ord = ::order(ope);
        ind = ord.at(0);
        if(ope.at(ind) != "!"){
            res = resGivenOpe(vector<string>(ope.begin()+ind-1,ope.begin()+ind+2));
            ope.erase(ope.begin()+ind-1,ope.begin()+ind+2);
            ope.insert(ope.begin()+ind-1, to_string(res));
        }
        else{
            res = resGivenOpe(vector<string>(ope.begin()+ind-1,ope.begin()+ind+1));
            ope.erase(ope.begin()+ind-1,ope.begin()+ind+1);
            ope.insert(ope.begin()+ind-1, to_string(res));
        }
    }
    return stod(ope.at(0));
}

double doOperationParenthesis(vector<string> ope){
    vector<parenthesisManager> pm;
    parenthesisManager p;
    double res;
    while (ope.size()>1){
        pm = detectParenthesis(ope);
        for(auto p : pm){
        }
        if(!pm.empty()) {
            p = pm.at(0);
            res = doOperation(vector<string>(ope.begin() + p.start + 1, ope.begin() + p.end));
            ope.erase(ope.begin() + p.start, ope.begin() + p.end + 1);
            ope.insert(ope.begin() + p.start, to_string(res));
        }
        else{
            return doOperation(ope);
        }
    }
    return stod(ope.at(0));
}


int main() {
    string input;
    vector<std::string> divOpe;
    double res;
    while(true) {
        try{
            cout << "enter a correct formula with ^ written as 'power' without spaces\nand write the * before or after the parenthesis: " << endl;
            cin >> input;
            divOpe = divideOperation(input);
            res =doOperationParenthesis(divOpe);
            cout<<"The result is : "<<res<<endl;
            break;
        }catch(const exception & e){
            cout<< "There is a mistake in your input" <<endl;
        }

    }



    return 0;
}
