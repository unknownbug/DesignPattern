/*
组合模式：
将对象组合成树形结构以表示‘部分-整体’的层次结构。组合模式使得用户对单个对象和组合对象的使用具有一致性。

使用场景：
发现需求中是体现部分与整体层次的结构时，以及你希望用户可以忽略组合对象与单个对象的不同，统一的使用组合结构中的所有对象时，就应该考虑使用组合模式。

部分-整体
*/
#include <iostream>
#include <list>
#include <string>
#include <memory>
#include <algorithm>

/*公司组织 demo*/


class Company {
public:
    using shared_company = std::shared_ptr<Company>;
    Company(const std::string & name) 
    : _name(name)
    {}
    virtual ~Company() = default;

    virtual void add(shared_company company) = 0;
    virtual void remove(shared_company company) = 0;
    virtual void display(int depth) = 0;
    virtual void lineOfDuty() = 0;

protected:
    std::string _name;
};

class ConcreteCompany : public Company {
public:
    ConcreteCompany(const std::string & name) : Company(name) {}
    ~ConcreteCompany() = default;

    void add(shared_company company) override {
        _children.emplace_back(company);
    }
    void remove(shared_company company) override {
        _children.erase(std::find(_children.begin(), _children.end(), company));
    }
    void display(int depth) override {
        std::string line(depth, '-');
        std::cout << line << _name << std::endl;
        for (auto com : _children) {
            com->display(depth + 2);
        }
    }
    void lineOfDuty() override {
        std::cout << _name << "负责管理区域各部门" << std::endl;
        for (auto com : _children) {
            com->lineOfDuty();
        }
    }

private:
    std::list<shared_company> _children;
};

//财务部
class FinanceDept : public Company {
public:
    FinanceDept(const std::string & name) : Company(name) {}
    ~FinanceDept() = default;

    void add(shared_company) override {
        std::cout << "叶子" << std::endl;
    }

    void remove(shared_company) override {
        std::cout << "叶子" << std::endl;
    }

    void display(int depth) override {
        std::string line(depth, '-');
        std::cout << line << _name << std::endl;
    }

    void lineOfDuty() override {
        std::cout << _name << "负责发工资" << std::endl;
    }

};

//行政部
class AdministrationDept : public Company {
public:
    AdministrationDept(const std::string & name) : Company(name) {}
    ~AdministrationDept() = default;

    void add(shared_company) override {
        std::cout << "叶子" << std::endl;
    }

    void remove(shared_company) override {
        std::cout << "叶子" << std::endl;
    }

    void display(int depth) override {
        std::string line(depth, '-');
        std::cout << line << _name << std::endl;
    }

    void lineOfDuty() override {
        std::cout << _name << "负责各种福利" << std::endl;
    }

};

//研发部
class DevelopmentDept : public Company {
public:
    DevelopmentDept(const std::string & name) : Company(name) {}
    ~DevelopmentDept() = default;

    void add(shared_company) override {
        std::cout << "叶子" << std::endl;
    }

    void remove(shared_company) override {
        std::cout << "叶子" << std::endl;
    }

    void display(int depth) override {
        std::string line(depth, '-');
        std::cout << line << _name << std::endl;
    }

    void lineOfDuty() override {
        std::cout << _name << "负责写代码" << std::endl;
    }

};

int main() 
{

    Company::shared_company finance(new FinanceDept("财务部"));
    Company::shared_company admin(new AdministrationDept("行政部"));
    Company::shared_company dvl(new DevelopmentDept("研发部"));

    Company::shared_company company(new ConcreteCompany("总公司"));
    Company::shared_company nanjing(new ConcreteCompany("南京公司"));
    Company::shared_company hangzhou(new ConcreteCompany("杭州公司"));

    company->add(finance);
    company->add(admin);
    company->add(dvl);

    company->add(nanjing);
    company->add(hangzhou);

    nanjing->add(finance);
    nanjing->add(admin);
    nanjing->add(dvl);

    hangzhou->add(finance);
    hangzhou->add(admin);
    hangzhou->add(dvl);

    company->display(1);
    company->lineOfDuty();
    return 0;
}