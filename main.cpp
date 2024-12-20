#include "./elements/employee.h"
#include "./elements/login.h"

int main(){
    Employee emp;
    Login log;
    bool isContinue, isAdminLogin, isEmpLogin;
    log.frontPage();
    do {
        isContinue = isAdminLogin = isEmpLogin  = false ;
        log.loginPage(&isContinue, &isAdminLogin, &isEmpLogin);
        if (isAdminLogin){
            emp.addAdminId(999);
            log.adminLogin(emp);
        } else if (isEmpLogin){
            log.employeeLogin(emp);
        }
    }while(isContinue != false);
    return 0;
}