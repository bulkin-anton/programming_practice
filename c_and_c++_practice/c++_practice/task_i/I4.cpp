#include <vector>
#include <algorithm>
#include <string>
class Department
{
};

class Student
{
public:
    enum { MAX_GRADE = 100, NOT_SET = -1000};
    Student(std::string);
    std::string const & name() const;
    int grade() const;
    Department &department() const;
    void set_grade(int);
    void set_department(Department *);
private:
    std::string _name;
    int _grade;
    Department *dpt;
    bool dpt_ex;
};

Student::Student(std::string name_): _name(name_), _grade(NOT_SET), dpt(0), dpt_ex(false) {}

std::string const&
Student::name() const{
    return _name;
}

int
Student::grade() const{
    if (_grade == NOT_SET){
        throw std::exception();
    }
    return _grade;
}
Department&
Student::department() const{
    if (dpt_ex == false){
        throw std::exception();
    }
    return *dpt;
}

void
Student::set_grade(int x){
    _grade = x;
}

void
Student::set_department(Department *x){
    dpt = x;
    dpt_ex = true;
}

struct Application
{
    Student *student;
    std::vector<Department *> order;
};

namespace no_algorithm
{
void
assign_with_max_grade(std::vector<Application *> & applications)
{
    std::vector<size_t> pos_del;
    for (size_t i  = 0; i < applications.size(); ++i){
        if ((applications[i] -> student -> grade() == Student::MAX_GRADE) &&
        (!(applications[i] -> order.empty()))){
            applications[i] -> student -> set_department((applications[i] -> order)[0]);
            pos_del.push_back(i);
        }
    }
    size_t del_size = pos_del.size();
    for (size_t i = 0; i < del_size; ++i){
        applications.erase(applications.begin() + pos_del[del_size - i - 1]);
    }
}
}

namespace with_algorithm
{

bool
criteria(Application *x){
    if ((x -> student -> grade() == Student::MAX_GRADE) &&
    (!(x -> order.empty()))){
        return false;
    }
    return true;
}

void
department_set(Application *x){
    if (criteria(x) == false){
        x -> student -> set_department((x -> order)[0]);
    }
}

void
assign_with_max_grade(std::vector<Application *> & applications)
{
    for_each(applications.begin(), applications.end(), department_set);
    applications.erase(stable_partition(applications.begin(), applications.end(),
    criteria), applications.end());
}
}
