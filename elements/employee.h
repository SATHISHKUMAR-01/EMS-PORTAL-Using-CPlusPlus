#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include "../libraries/headers.h"

struct emp_details {
    int emp_id;
    int age;
    string dob;
    string name;
    string role;
    string fatherName;
    string department;
    string dateOfJoin;
};

class Employee {
    private:
    vector<emp_details> employee;
    
    public:
    // Set Methods
    void setEmpId(struct emp_details *detail, int emp_id);
    void setAge(struct emp_details *detail, int age);
    void setName(struct emp_details *detail, string name);
    void setRole(struct emp_details *detail, string role);
    void setDob(struct emp_details *detail, string dob);
    void setFatherName(struct emp_details *detail, string fatherName);
    void setDepartment(struct emp_details *detail, string department);
    void setDateOfJoin(struct emp_details *detail, string dateOfJoin);

    //Get Methods
    int getEmpId(struct emp_details *detail);
    int getAge(struct emp_details *detail);
    string getName(struct emp_details *detail);
    string getRole(struct emp_details *detail);
    string getDob(struct emp_details *detail);
    string getFatherName(struct emp_details *detail);
    string getDepartment(struct emp_details *detail);
    string getDateOfJoin(struct emp_details *detail);

    void addEmployee(struct emp_details details);
    void displayEmployee();
    void diplaySpecificEmployee(int emp_id);
    void updateEmployeeData(Employee& emp);
    emp_details* getEmployee(int emp_id);
};

#endif