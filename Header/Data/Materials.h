//
// Created by chenhonxinh on 2021/12/7.
//

#ifndef BIGPROJECT_MATERIALS_H
#define BIGPROJECT_MATERIALS_H

#include <string>

using namespace std;
class Materials {
public:
    Materials(string,int);

    Materials( string &name,  string &kind, int count, bool isRegulate);

    string getName() const;

    void setName(const string &name);

    const string &getKind() const;

    void setKind(const string &kind);

    int getCount() const;

    void setCount(int count);

    bool isRegulate() const;

    void setIsRegulate(bool isRegulate);

protected:
private:
    string name;
    string kind;
    int count;
    bool is_regulate= false;
};


#endif //BIGPROJECT_MATERIALS_H
