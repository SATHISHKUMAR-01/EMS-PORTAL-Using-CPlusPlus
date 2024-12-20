#include "login.h"
#include "admin.h"
#include "../libraries/messages.h"

#define ATTENDANCE_DIR "/Users/sathiska/Documents/c++/EMS-PORTAL-Using-CPlusPlus/attendance_record/"

void Login::frontPage(){
    cout << "\n" << WELCOME_MESSAGE << " " << APP_NAME << endl;
    
    int boxCount = 5;
    int middleArea = (boxCount/2);
    cout << BORDER_LINES <<  endl;
    for(int index = 0; index < boxCount; index++){
        if (index==middleArea){
            cout << "|---          For More Information,        ---|" << endl;
            cout << "|---           Login to Portal             ---|" << endl;
        }else {
            cout << BODY_LINES << endl;
        }
    }
    cout << BORDER_LINES << "\n" << endl;
}

void Login::loginPage(bool *isContinue, bool *isAdminLogin, bool *isEmpLogin){
    string resp;
    cout << "Do you want to continue (Y/N) - ";
    cin >> resp;
    while ((resp != "Y" && resp != "y") && (resp != "N" && resp != "n")){
        cout << "\nWrong input given !!! Enter either y or n - ";
        cin >> resp;
    }
    if (resp == "Y" || resp == "y"){
        *isContinue = true;
        cout << "\nEnter 1 for Employee Login\nEnter 2 for Admin Login\nEnter 3 for Exit\n\nEnter your choice - ";
        cin >> resp;
        while ((resp != "1" && resp != "2" && resp != "3")){
            cout << "\nWrong input given !!! Enter 1 or 2 or 3 - ";
            cin >> resp;
        }
    }else{
        cout << "Exiting..." << endl;
        return;
    }
    cout << "\n" << BORDER_LINES <<  endl;
    if (resp == "1") {
        cout << "       You have selected Employee Login     " << endl;
        *isEmpLogin = true;
    }else if (resp == "2"){
        cout << "       You have selected Admin Login      " << endl;
        *isAdminLogin = true;
    }
    cout << BORDER_LINES <<  endl;
}

void Login::employeeLogin(Employee& emp){
    int emp_id;
    string password;
    int resp;
    cout << "\n" << BORDER_LINES <<  endl;
    cout << "          Welcome to Employee Login" << endl;
    cout << BORDER_LINES <<  endl;
    
    cout << "\nEnter your employee ID : ";
    cin  >> emp_id;
    cout << "\nEnter your password : ";
    cin  >> password;

    if (!emp.validateCredentials(emp_id, password)){
        cout << "\n Username/Password mismatch !!!!!\n" << endl;
        return;
    }

    cout << "\nLoading" << endl;
    sleep(2);
    for (int index = 0 ; index < 3 ; index++){
        sleep(1);
        cout << "." << endl;
    }
    emp_details* details = emp.getEmployee(emp_id);
    
    if (details == nullptr) {
        cout << BORDER_LINES <<  endl;
        cout << "           Employee not found " << endl;
        cout << BORDER_LINES <<  endl;
        return;
    }

    cout << "\n --- Login successfull --- " << endl;

    cout << "\nWelcome, " << emp.getName(details) << "\n" << endl;

    string options[] = {
        "Enter 01 to view holiday planners",
        "Enter 02 to view leave balances",
        "Enter 03 to apply/cancel/view leave",
        "Enter 04 to view salary",
        "Enter 05 to view the people in the company",
        "Enter 06 to view project and manager info",
        "Enter 07 to approve leave requests",
        "Enter 08 to submit/cancel/view self-review",
        "Enter 09 to approve the self-review of the employee",
        "Enter 10 to view attendance info",
        "Enter 11 to see notifications",
        "Enter 12 to request for a additional leave",
        "Enter 13 to see announcements",
        "Enter 0 to exit",
    };

    int numOptions = sizeof(options) / sizeof(options[0]);

    do{
        cout << "\n" << BORDER_LINES <<  endl;
        cout << "           Employee Operations   " << endl;
        cout << BORDER_LINES << "\n" << endl;

        for (int index = 0 ; index < numOptions; index++){
            cout << options[index] << endl;
        }

        cout << "\n\nEnter your choice - ";
        cin >> resp;

        while ( (resp < 0 || resp > numOptions-1)){
            cout << "\nWrong input given !!! Enter value from 1 to "<< numOptions << " - ";
            cin >> resp;
        }

        cout << "\n" << BORDER_LINES <<  endl;
        if(resp == VIEW_HOLIDAY){
            showHolidays();
            cout << BORDER_LINES <<  endl;
        }else if(resp == VIEW_LEAVE_BALANCE){
            leaveData *leaveBalance = emp.viewLeaveBalance(emp_id);
            cout << "           Leave Balances" << endl;
            cout << BORDER_LINES <<  endl;
            if (leaveBalance != nullptr) {
                cout << "   Work From Home    :  " << leaveBalance->workFromHome << endl;
                cout << "   Annual Leave      :  " << leaveBalance->annualLeave << endl;
                cout << "   Vacation Leave    :  " << leaveBalance->vacationLeave << endl;
                cout << "   Team Time Off     :  " << leaveBalance->teamOff << endl;
                cout << "   Maternity Leave   :  " << leaveBalance->maternityLeave << endl;
                cout << "   Paternity Leave   :  " << leaveBalance->paternityLeave << endl;
                cout << "   Marriage Leave    :  " << leaveBalance->marriageLeave << endl;
            }else{
                cout << "           Record not found !!!  " << endl;
            }
            cout << BORDER_LINES <<  endl;
        }else if(resp == LEAVE_OPERATIONS){
            cout << "    Apply for a Leave " << endl;
            cout << BORDER_LINES <<  endl;
            int leave_operation;
            leaveData *leaveBalance;
            
            leaveBalance = emp.viewLeaveBalance(emp_id);

            cout << "\nDo you want to apply for a leave/cancel a leave ? \n" << endl; 
            cout << "Enter 01 to apply for a leave" << endl;
            cout << "Enter 02 to cancel a leave " << endl;
            cout << "Enter 03 to view applied leave " << endl;
            cout << "\nEnter your choice : ";
            cin  >> leave_operation;
            cout << "\n" << BORDER_LINES <<  endl;
            if(leave_operation == 1){
                leave_details details;
                int leave_type, numDays;
                string reason, startDate, endDate;
                bool leave_status;
                cout << "           Select the leave type" << endl;
                cout << BORDER_LINES << "\n" <<endl;
                cout << "Enter 01 to choose work from home " << endl;
                cout << "Enter 02 to choose vacation leave " << endl;
                cout << "Enter 03 to choose annual leave " << endl;
                cout << "Enter 04 to choose team time off " << endl;
                cout << "Enter 05 to choose paternity leave " << endl;
                cout << "Enter 06 to choose maternity leave " << endl;
                cout << "Enter 07 to choose marriage leave " << endl;
                cout << "\nEnter your choice : ";
                cin  >> leave_type;

                cout << "\nEnter the number of days you want to apply : ";
                cin  >> numDays;

                if (leave_type == 1){
                    if (leaveBalance->workFromHome < numDays){
                        cout << "\nYour work from home count is less, Cant Apply !!!! \n" << endl;
                        continue;
                    }
                }else if (leave_type == 2){
                    if (leaveBalance->vacationLeave < numDays){
                        cout << "\nYour vacation leave count is less, Cant Apply !!!! \n" << endl;
                        continue;
                    }
                }else if (leave_type == 3){
                    if (leaveBalance->annualLeave < numDays){
                        cout << "\nYour annual leave count is less, Cant Apply !!!! \n" << endl;
                        continue;
                    }
                }else if (leave_type == 4){
                    if (leaveBalance->teamOff < numDays){
                        cout << "\nYour team time off count is less, Cant Apply !!!! \n" << endl;
                        continue;
                    }
                }else if (leave_type == 5){
                    if (leaveBalance->paternityLeave < numDays){
                        cout << "\nYour paternity leave count is less, Cant Apply !!!! \n" << endl;
                        continue;
                    }
                }else if (leave_type == 6){
                    if (leaveBalance->maternityLeave < numDays){
                        cout << "\nYour maternity leave count is less, Cant Apply !!!! \n" << endl;
                        continue;
                    }
                }else if (leave_type == 7){
                    if (leaveBalance->marriageLeave < numDays){
                        cout << "\nYour marriage leave count is less, Cant Apply !!!! \n" << endl;
                        continue;
                    }
                }

                cout << "\nEnter the start date : ";
                cin  >> startDate;

                cout << "\nEnter the end date   : ";
                cin  >> endDate;

                cout << "\nEnter the leave reason : ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, reason);

                details.leave_type = getLeaveType(leave_type);
                details.end_date = endDate;
                details.start_date = startDate;
                details.number_of_days = numDays;
                details.reason = reason;
                details.leave_status = PENDING;
                
                emp.applyLeave(emp_id, details);

                cout << "\n" << BORDER_LINES << endl;
                cout << "   Leave Applied Successfully   " << endl;
                cout << BORDER_LINES << "\n" << endl;

            }else if(leave_operation == 2){
                cout << "\n" << BORDER_LINES << endl;
                cout << " Your current pending leave requests" << endl;
                cout << BORDER_LINES << "\n" << endl;

                map<int, vector<leave_details>>& pending_leave = emp.getLeaveRequest();
               
                if (pending_leave.count(emp_id)) {
                    for (auto it = pending_leave[emp_id].begin(); it != pending_leave[emp_id].end(); ) {
                        if (!it->leave_status){
                            cout << "Leave Type     : " << it->leave_type << endl;
                            cout << "Start Date     : " << it->start_date << endl;
                            cout << "End Date       : " << it->end_date << endl;
                            cout << "Number of Days : " << it->number_of_days << endl;
                            cout << "Reason         : " << it->reason << endl;

                            char choice;
                            cout << "\nDo you want to delete this leave request? (y/n): ";
                            cin >> choice;

                            if (choice == 'y' || choice == 'Y') {
                                it = pending_leave[emp_id].erase(it);
                                cout << "\n<----- Leave Request Cancelled Successfully ----->\n" << endl;
                            } else {
                                ++it;
                            }
                        }else{
                            ++it;
                        }
                    }
                }else{
                    cout << "There is no pending leave request found !!!";
                }
            }else if(leave_operation == 3){
                map<int, vector<leave_details>>& pending_leave = emp.getLeaveRequest();
                if (pending_leave.count(emp_id)) {
                    for (auto it = pending_leave[emp_id].begin(); it != pending_leave[emp_id].end(); ++it ) {
                        cout << "Leave Type     : " << it->leave_type << endl;
                        cout << "Start Date     : " << it->start_date << endl;
                        cout << "End Date       : " << it->end_date << endl;
                        cout << "Number of Days : " << it->number_of_days << endl;
                        cout << "Reason         : " << it->reason << endl;
                        string status;
                        if (it->leave_status == PENDING){
                            status = "Pending";
                        }else if (it->leave_status == APPROVED){
                            status = "Approved";
                        }else if (it->leave_status == REJECTED){
                            status = "Rejected";
                        }
                        cout << "Status         : " << status << endl;
                        cout << "\n" << BORDER_LINES << "\n" << endl;
                    }
                }else{
                    cout << "There is no leave request found !!!" << endl;
                }
            }
        }else if(resp == VIEW_SALARY){
            cout << "\n      <----- Salary Slip ----->\n" << endl;
            cout << "        Total Salary : Rs." << emp.getSalary(details) << endl;
        }else if(resp == VIEW_PEOPLE){
            cout << "           People in the Company " << endl;
            cout << BORDER_LINES <<  endl;
            emp.showPeopleData();
        }else if(resp == EXIT){
            cout << "           Exiting Employee Login    " << endl;
            cout << BORDER_LINES <<  endl;
        }else if(resp == VIEW_PROJECT_AND_MANAGER_INFO){
            cout << "   View Employee's manager and project data " << endl;
            cout << BORDER_LINES <<  endl;
            int emp_id;
            cout << "\nEnter the employee id  :  ";
            cin  >> emp_id;
            emp.viewManagerAndProjectDetails(emp_id);
        }else if(resp == APPROVE_LEAVE_REQ){
            manager_details* mngr_details = emp.getSpecificManagerData(emp_id);
            message_details message_info;
            leaveData *leaveBalance;
            string subject;

            if (mngr_details == nullptr) {
                cout << BORDER_LINES <<  endl;
                cout << "     Operation not permitted  " << endl;
                cout << BORDER_LINES <<  endl;
                return;
            }

            map<int, vector<leave_details>>& pending_leave = emp.getLeaveRequest();

            for (int id : mngr_details->team_members_id){
                if (pending_leave.count(id)) {
                    emp_details* emp_info =  emp.getEmployee(id);
                    for (auto it = pending_leave[id].begin(); it != pending_leave[id].end(); ++it) {

                        if (!it->leave_status){
                            cout << "Employee Name  : " << emp_info->name << endl;
                            cout << "Leave Type     : " << it->leave_type << endl;
                            cout << "Start Date     : " << it->start_date << endl;
                            cout << "End Date       : " << it->end_date << endl;
                            cout << "Number of Days : " << it->number_of_days << endl;
                            cout << "Reason         : " << it->reason << endl;

                            char choice;
                            cout << "Do you want to approve this leave request? (y/n): ";
                            cin >> choice;

                            if (choice == 'y' || choice == 'Y') {
                                it->leave_status = APPROVED;
                                leaveBalance = emp.viewLeaveBalance(id);
                                if (it->leave_type == "WORK_FROM_HOME"){
                                    leaveBalance->workFromHome-=it->number_of_days;
                                }else if (it->leave_type == "VACATION_LEAVE"){
                                    leaveBalance->vacationLeave-=it->number_of_days;
                                }else if (it->leave_type == "ANNUAL_LEAVE"){
                                    leaveBalance->annualLeave-=it->number_of_days;
                                }else if (it->leave_type == "TEAM_TIME_OFF"){
                                    leaveBalance->teamOff-=it->number_of_days;
                                }else if (it->leave_type == "PATERNITY_LEAVE"){
                                    leaveBalance->paternityLeave-=it->number_of_days;
                                }else if (it->leave_type == "MATERNITY_LEAVE"){
                                    leaveBalance->maternityLeave-=it->number_of_days;
                                }else if (it->leave_type == "MARRIAGE_LEAVE"){
                                    leaveBalance->marriageLeave-=it->number_of_days;
                                }
                                cout << "\n<----- Leave Request Approved Successfully ----->\n" << endl;
                                subject = "Your Leave Application has been Accepted.\n"
                                        "Leave type: " + it->leave_type + "\n" +
                                        "Start Date: " + it->start_date + "\n" +
                                        "End Date: " + it->end_date + "\n" +
                                        "Reason: " + it->reason + "\n";
                                message_info.info = subject;
                                emp.addMessage(id, message_info);
                            }else if (choice == 'n' || choice == 'N'){
                                it->leave_status = REJECTED;
                                cout << "\n<----- Leave Request Rejected ----->\n" << endl;
                                subject = "Your Leave Application has been Rejected.\n"
                                        "Leave type: " + it->leave_type + "\n" +
                                        "Start Date: " + it->start_date + "\n" +
                                        "End Date: " + it->end_date + "\n" +
                                        "Reason: " + it->reason + "\n";
                                message_info.info = subject;
                                emp.addMessage(id, message_info);
                            }
                        }
                    }
                }
            }
        }else if(resp == REVIEW_OPERATIONS){
            cout << "     Review Operations   " << endl;
            cout << BORDER_LINES <<  endl;
            int review_operation;
            cout << "\nDo you want to submit comment for a review/cancel comments for a review ? \n" << endl; 
            cout << "Enter 01 to submit comments for a review" << endl;
            cout << "Enter 02 to cancel comments for a review " << endl;
            cout << "Enter 03 to view added review comments " << endl;
            cout << "\nEnter your choice : ";
            cin  >> review_operation;
            cout << "\n" << BORDER_LINES <<  endl;
            if(review_operation == 1){
                review_details details;

                cout << "\nEnter your self sufficiency comments         : ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, details.emp_self_sufficiency_comments);

                cout << "\nAdd Rating for the category self sufficiency (out of 5) : ";
                cin  >> details.emp_self_sufficieny_rating;

                cout << "\nEnter your proficiency comments         : ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, details.emp_proficiency_comments);

                cout << "\nAdd Rating for the category proficiency (out of 5) : ";
                cin  >> details.emp_proficiency_rating;

                details.status = false;

                emp.addReview(emp_id, details);

                cout << "\n" << BORDER_LINES << endl;
                cout << "   Review Added Successfully   " << endl;
                cout << BORDER_LINES << "\n" << endl;

            }else if(review_operation == 2){
                cout << "\n" << BORDER_LINES << endl;
                cout << " Your current pending review" << endl;
                cout << BORDER_LINES << "\n" << endl;

                map<int, vector<review_details>>& pending_review = emp.getReviewData();
               
                if (pending_review.count(emp_id)) {
                    for (auto it = pending_review[emp_id].begin(); it != pending_review[emp_id].end(); ) {

                        if(!it->status){
                            cout << "Self Sufficieny Comments     : " << it->emp_self_sufficiency_comments << endl;
                            cout << "Self Sufficieny Rating       : " << it->emp_self_sufficieny_rating << endl;
                            cout << "Proficiency Comments         : " << it->emp_proficiency_comments << endl;
                            cout << "Proficiency Rating           : " << it->emp_proficiency_rating << endl;

                            char choice;
                            cout << "Do you want to delete this review ? (y/n): ";
                            cin >> choice;

                            if (choice == 'y' || choice == 'Y') {
                                it = pending_review[emp_id].erase(it);
                                cout << "\n<----- Review Comments Deleted Successfully ----->\n" << endl;
                            } else {
                                ++it;
                            }
                        }else{
                            ++it;
                        }
                    }
                }else{
                    cout << "There is no pending review found !!!";
                }
            }else if (review_operation == 3){
                map<int, vector<review_details>>& pending_review = emp.getReviewData();
                if (pending_review.count(emp_id)) {
                    for (auto it = pending_review[emp_id].begin(); it != pending_review[emp_id].end(); ++it ) {
                        cout << "Your Self Sufficiency Comments  :  " << it->emp_self_sufficiency_comments << endl;
                        cout << "Your Self Sufficiency Rating    :  " << it->emp_self_sufficieny_rating << endl;
                        cout << "Your Proficiency Comments       :  " << it->emp_proficiency_comments << endl;
                        cout << "Your Proficiency Rating         :  " << it->emp_proficiency_rating << endl;

                        if (it->mngr_self_sufficiency_comments != ""){
                            cout << "\nManager Self Sufficiency Comments  :  " << it->mngr_self_sufficiency_comments << endl;
                            cout << "Manager Self Sufficiency Rating    :  " << it->mngr_self_sufficieny_rating << endl;
                            cout << "Manager Proficiency Comments       :  " << it->mngr_proficiency_comments << endl;
                            cout << "Manager Proficiency Rating         :  " << it->mngr_proficiency_rating << endl;
                            cout << "\n" << BORDER_LINES << endl;
                            cout << "     Final Rating  :   " << it->final_rating << endl;
                            cout << BORDER_LINES << endl;
                        }else {
                            cout << "\n<------ Manager Review is Pending ------>" << endl;
                        }
                        string status = it->status ? "Approved" : "Pending";
                        cout << "Status         : " << status << endl;
                    }
                }else{
                    cout << "There is no review comments found !!!" << endl;
                }
            }
        }else if(resp == APPROVE_REVIEW){
            manager_details* mngr_details = emp.getSpecificManagerData(emp_id);
            message_details message_info;
            string subject;

            if (mngr_details == nullptr) {
                cout << BORDER_LINES <<  endl;
                cout << "     Operation not permitted  " << endl;
                cout << BORDER_LINES <<  endl;
                return;
            }

            map<int, vector<review_details>>& review_info = emp.getReviewData();

            for (int id : mngr_details->team_members_id){
                if (review_info.count(id)) {
                    emp_details* emp_info =  emp.getEmployee(id);
                    for (auto it = review_info[id].begin(); it != review_info[id].end(); ++it) {

                        if (!it->status){
                            cout << "\nEmployee Name  : " << emp_info->name << endl;
                            cout << "\nSelf Sufficieny Comments     : " << it->emp_self_sufficiency_comments << endl;
                            cout << "Self Sufficieny Rating       : " << it->emp_self_sufficieny_rating << endl;
                            cout << "Proficiency Comments         : " << it->emp_proficiency_comments << endl;
                            cout << "Proficiency Rating           : " << it->emp_proficiency_rating << endl;

                            char choice;
                            cout << "Do you want to add your comments to this review ? (y/n): ";
                            cin >> choice;

                            if (choice == 'y' || choice == 'Y') {
                                cout << "\nAdd your comments and rating !!!" << endl;

                                cout << "\nEnter your self sufficiency comments         : ";
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                getline(cin, it->mngr_self_sufficiency_comments);
                                
                                cout << "\nAdd Rating for the category self sufficiency : ";
                                cin  >> it->mngr_self_sufficieny_rating;

                                cout << "\nEnter your proficiency comments         : ";
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                getline(cin, it->mngr_proficiency_comments);

                                cout << "\nAdd Rating for the category proficiency : ";
                                cin  >> it->mngr_proficiency_rating;

                                it->status = true;
                                it->final_rating = (it->mngr_self_sufficieny_rating + it->mngr_proficiency_rating) / 2;

                                subject = "Your Review has been Accepted.\n"
                                        "Final Rating : " + to_string(it->final_rating) + "\n";
                                message_info.info = subject;
                                emp.addMessage(id, message_info);
                            }
                        }
                    }
                }
            }
        }else if(resp == VIEW_ATTENDANCE){
            cout << "       Attendance Info   " << endl;
            cout << BORDER_LINES <<  endl;
            vector<EmployeeLog> attendance_details = emp.getAttendanceInfo(emp_id);
            cout << "\n" << BORDER_LINES << endl;
            for (const auto& attendance : attendance_details) {
                attendance.display();
            }
            cout << BORDER_LINES << "\n" << endl;
        }else if(resp == VIEW_NOTIFICATIONS){
            vector<message_details> message_info = emp.getMessage(emp_id);
            cout << "\n<------- Received Notifications ------->\n" << endl;
            for (auto it = message_info.begin(); it!=message_info.end(); ++it ){
                cout << BORDER_LINES << endl;
                cout << it->info;
                cout << BORDER_LINES << endl;
            }
            cout << "\n<-------------------------------------->\n" << endl;
        }else if(resp == REQ_FOR_LEAVE){
            cout << "    Requestion for a Leave " << endl;
            cout << BORDER_LINES <<  endl;
            int leave_req_operation;
            
            cout << "Enter 01 to apply for a leave request" << endl;
            cout << "Enter 02 to cancel a leave request" << endl;
            cout << "Enter 03 to view applied leave request" << endl;
            cout << "\nEnter your choice : ";
            cin  >> leave_req_operation;
            cout << "\n" << BORDER_LINES <<  endl;

            if(leave_req_operation == 1){
                leave_req details;
                int leave_type, numDays;
                string reason;
                bool leave_status;
                cout << "           Select the leave type" << endl;
                cout << BORDER_LINES << "\n" <<endl;
                cout << "Enter 01 to choose work from home " << endl;
                cout << "Enter 02 to choose vacation leave " << endl;
                cout << "Enter 03 to choose annual leave " << endl;
                cout << "Enter 04 to choose team time off " << endl;
                cout << "Enter 05 to choose paternity leave " << endl;
                cout << "Enter 06 to choose maternity leave " << endl;
                cout << "Enter 07 to choose marriage leave " << endl;
                cout << "\nEnter your choice : ";
                cin  >> leave_type;

                cout << "\nEnter the number of days you want to apply : ";
                cin  >> numDays;

                cout << "\nEnter the leave reason : ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, reason);

                details.leave_type = getLeaveType(leave_type);
                details.number_of_days = numDays;
                details.comments = reason;
                details.status = PENDING;
                
                emp.applyLeaveReq(emp_id, details);

                cout << "\n" << BORDER_LINES << endl;
                cout << "  Leave Request has been Applied Successfully   " << endl;
                cout << BORDER_LINES << "\n" << endl;

            }else if(leave_req_operation == 2){
                cout << "\n" << BORDER_LINES << endl;
                cout << " Your current pending leave requests" << endl;
                cout << BORDER_LINES << "\n" << endl;

                map<int, vector<leave_req>>& pending_leave_req = emp.getPendingLeaveRequest();
               
                if (pending_leave_req.count(emp_id)) {
                    for (auto it = pending_leave_req[emp_id].begin(); it != pending_leave_req[emp_id].end(); ) {
                        if (!it->status){
                            cout << "Leave Type     : " << it->leave_type << endl;
                            cout << "Number of Days : " << it->number_of_days << endl;
                            cout << "Reason         : " << it->comments << endl;

                            char choice;
                            cout << "\nDo you want to delete this leave request? (y/n): ";
                            cin >> choice;

                            if (choice == 'y' || choice == 'Y') {
                                it = pending_leave_req[emp_id].erase(it);
                                cout << "\n<----- Leave Request Cancelled Successfully ----->\n" << endl;
                            } else {
                                ++it;
                            }
                        }else{
                            ++it;
                        }
                    }
                }else{
                    cout << "There is no pending leave request found !!!";
                }
            }else if(leave_req_operation == 3){
                map<int, vector<leave_req>>& pending_leave_req = emp.getPendingLeaveRequest();
                if (pending_leave_req.count(emp_id)) {
                    for (auto it = pending_leave_req[emp_id].begin(); it != pending_leave_req[emp_id].end(); ++it ) {
                        cout << "Leave Type     : " << it->leave_type << endl;
                        cout << "Number of Days : " << it->number_of_days << endl;
                        cout << "Reason         : " << it->comments << endl;
                        string status;
                        if (it->status == PENDING){
                            status = "Pending";
                        }else if (it->status == APPROVED){
                            status = "Approved";
                        }else if (it->status == REJECTED){
                            status = "Rejected";
                        }
                        cout << "Status         : " << status << endl;
                        cout << "\n" << BORDER_LINES << "\n" << endl;
                    }
                }else{
                    cout << "There is no leave request found !!!" << endl;
                }
            }
        }else if (resp == VIEW_ANNOUNCEMENTS){
            vector<string> message = emp.getAnnouncements();
            for (auto it = message.begin(); it!=message.end(); it++){
                cout << "\n" BORDER_LINES << endl;
                cout << *it << "\n" << endl;
                cout << BORDER_LINES << "\n" << endl;
            }
        }
    }while(resp != EXIT);
}

void Login::displayEmployeeData(int emp_id, int age, string name, string dob, string role, string fatherName, string department, string dateOfJoin, string sex, int salary){
    cout << "\n" << BORDER_LINES <<  endl;
    cout << "      Summary of New Employee Details" << endl;
    cout << BORDER_LINES <<  endl;
    cout << "   Employee Id   : " << emp_id << endl;
    cout << "   Name          : " << name << endl;
    cout << "   Sex           : " << sex << endl;
    cout << "   Father's Name : " << fatherName << endl;
    cout << "   Date of Birth : " << dob << endl;
    cout << "   Age           : " << age << endl;
    cout << "   Role          : " << role << endl;
    cout << "   Department    : " << department << endl;
    cout << "   Date of Join  : " << dateOfJoin << endl;
    cout << "   Salary        : " << salary << endl;
    cout << BORDER_LINES <<  endl;
}

void Login::addEmployeeData(Employee& emp){
    int emp_id, age, count, salary;
    string dob, name, role, fatherName, department, dateOfJoin, sex;
    string password;

    cout << "\nEnter the count of employee data you want to add : ";
    cin >> count;

    emp_details details[count];
    for(int index=0 ; index<count ; index++) {
        string resp;
        cout << "\nEnter the employee ID : ";
        cin >> emp_id;

        cout << "\nEnter the name of the employee : ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, name);
       
        cout << "\nEnter the father's name : ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, fatherName);
        
        cout << "\nEnter the age : ";
        cin >> age;

        cout << "\nEnter the sex (Male/Female/Others) : ";
        cin >> sex;

        cout << "\nEnter the Date of Birth (DD/MM/YYYY) : ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, dob);

        cout << "\nEnter the employee role (Intern/Senior/Manager) : ";
        cin >> role;

        cout << "\nEnter the department belongs to (Admin/HR/IT/Engineering) : ";
        cin >> department;

        cout << "\nEnter the Date of Join (DD/MM/YYYY) : ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, dateOfJoin);

        cout << "\nEnter the salary : ";
        cin  >> salary;

        displayEmployeeData(emp_id,age,name,dob,role,fatherName,department,dateOfJoin,sex,salary);

        cout << "\nEnter 1 to save the data\nEnter 2 to edit any value\n\nEnter your choice - ";
        cin >> resp;

        while ((resp != "1" && resp != "2")){
            cout << "\nWrong input given !!! Enter 1 or 2 - ";
            cin >> resp;
        }
            
        if (resp == "2"){
            do {
                int editKey;
                cout << "\n" << BORDER_LINES <<  endl;
                cout << "   Which field you want to change ?\n\n";
                cout << "     Enter 01 to edit employee ID" << endl;
                cout << "     Enter 02 to edit name" << endl;
                cout << "     Enter 03 to edit father's name" << endl;
                cout << "     Enter 04 to edit date of birth" << endl;
                cout << "     Enter 05 to edit Age" << endl;
                cout << "     Enter 06 to edit Role" << endl;
                cout << "     Enter 07 to edit Department" << endl;
                cout << "     Enter 08 to edit Date of Join" << endl;
                cout << "     Enter 09 to edit sex" << endl;
                cout << "     Enter 10 to edit salary" << endl;
                cout << BORDER_LINES <<  endl;
                cout << "Enter your choice - ";
                cin >> editKey;

                switch (editKey){
                    case EDIT_EMP_ID:
                        cout << "\nOld employee ID : " << emp_id << endl;
                        cout << "Enter the new value : ";
                        cin  >> emp_id;
                        break;
                    case EDIT_NAME:
                        cout << "\nOld Name : " << name << endl;
                        cout << "Enter the new value : ";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        getline(cin, name);
                        break;
                    case EDIT_FATHER_NAME:
                        cout << "\nOld Father's name : " << fatherName << endl;
                        cout << "Enter the new value : ";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        getline(cin, fatherName);
                        break;
                    case EDIT_DOB:
                        cout << "\nOld Date of Birth : " << dob << endl;
                        cout << "Enter the new value : ";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        getline(cin, dob);
                        break;
                    case EDIT_AGE:
                        cout << "\nOld Age : " << age << endl;
                        cout << "Enter the new value : ";
                        cin  >> age;
                        break;
                    case EDIT_ROLE:
                        cout << "\nOld Role : " << role << endl;
                        cout << "Enter the new value (Intern/Senior/Manager) : ";
                        cin  >> role;
                        break;
                    case EDIT_DEPARTMENT:
                        cout << "\nOld Department : " << department << endl;
                        cout << "Enter the new value (Admin/HR/IT/Engineering) : ";
                        cin  >> department;
                        break;
                    case EDIT_DATE_OF_JOIN:
                        cout << "\nOld Date Of Join : " << dateOfJoin << endl;
                        cout << "Enter the new value : ";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        getline(cin, dateOfJoin);
                        break;
                    case EDIT_SEX:
                        cout << "\nOld Sex : " << sex << endl;
                        cout << "Enter the new value (Male/Female/Others) : ";
                        cin  >> sex;
                        break;
                    case EDIT_SALARY:
                        cout << "\nOld Salary : " << salary << endl;
                        cout << "Enter the new value : ";
                        cin  >> salary;
                        break;
                    default:
                        cout << "Wrong Value Entered" << endl;
                        break;
                }
                displayEmployeeData(emp_id,age,name,dob,role,fatherName,department,dateOfJoin,sex,salary);
                cout << "\nEnter 1 to save the data\nEnter 2 to edit any value\n\nEnter your choice - ";
                cin >> resp;

                while ((resp != "1" && resp != "2")){
                    cout << "\nWrong input given !!! Enter 1 or 2 - ";
                    cin >> resp;
                }
            }while(resp == "2");
        }

        details[index].emp_id = emp_id;
        details[index].name = name;
        details[index].age = age;
        details[index].fatherName = fatherName;
        details[index].dob = dob;
        details[index].role = role;
        details[index].department = department;
        details[index].dateOfJoin = dateOfJoin;
        details[index].sex = sex;
        details[index].salary = salary;

        emp.addEmployee(details[index]);
        password = name.substr(0, 2) + role;
        emp.addCredentials(emp_id, password);

        cout << "\n" << BORDER_LINES <<  endl;
        cout << "       Data Saved Successfully !!! " << endl;
        cout << BORDER_LINES <<  endl;
    }
}

void Login::adminLogin(Employee& emp){
    int resp;
    bool addEntry, updateEntry;
    Admin admin;

    int emp_id;
    cout << "\n" << BORDER_LINES <<  endl;
    cout << "          Welcome to Admin Login" << endl;
    cout << BORDER_LINES <<  endl;
    
    cout << "\nEnter your employee ID : ";
    cin  >> emp_id;
    bool isAdmin = emp.isAdmin(emp_id);

    if(!isAdmin){
        cout << "\n" << BORDER_LINES <<  endl;
        cout << "              Admin not found " << endl;
        cout << BORDER_LINES <<  endl;
        return;
    }

    string options[] = {
        "Enter 01 to add new employee data",
        "Enter 02 to update existing employee data",
        "Enter 03 to view all employee details",
        "Enter 04 to view specific employee details",
        "Enter 05 to grant leave to employee",
        "Enter 06 to view the leave counts for all leave types",
        "Enter 07 to add new manager",
        "Enter 08 to remove manager details",
        "Enter 09 to view list of managers in the company",
        "Enter 10 to update manager details",
        "Enter 11 to add new project",
        "Enter 12 to remove project details",
        "Enter 13 to view list of  projects in the company",
        "Enter 14 to update project details",
        "Enter 15 to map employee to the manager",
        "Enter 16 to map employee to the project",
        "Enter 17 to view project and manager details of an employee",
        "Enter 18 to add attendance entry",
        "Enter 19 to view additional leave req from employee",
        "Enter 20 to add announcements",
        "Enter 0 to exit",
    };

    int numOptions = sizeof(options) / sizeof(options[0]);

    do {
        cout << "\n" << BORDER_LINES <<  endl;
        cout << "            Admin Operations   " << endl;
        cout << BORDER_LINES << "\n" << endl;

        for (int index = 0 ; index < numOptions; index++){
            cout << options[index] << endl;
        }

        cout <<"\n\nEnter your choice - ";
        cin >> resp;
        while ( (resp < 0 || resp > numOptions-1)){
            cout << "\nWrong input given !!! Enter value from 1 to "<< numOptions << " - ";
            cin >> resp;
        }
        cout << "\n" << BORDER_LINES <<  endl;
        if (resp == ADD_NEW_EMPLOYEE) {
            cout << "           Adding new Employee Data     " << endl;
            cout << BORDER_LINES <<  endl;
            addEmployeeData(emp);
        }else if (resp == UPDATE_EMPLOYEE_DATA){
            cout << "           Updating Employee Data    " << endl;
            cout << BORDER_LINES <<  endl;
            emp.updateEmployeeData(emp);
        }else if (resp == VIEW_ALL_EMPLOYEE_DATA){
            cout << "         Displaying all Employee Data    " << endl;
            cout << BORDER_LINES <<  endl;
            emp.displayEmployee();
        }else if (resp == VIEW_SPECIFIC_EMPLOYEE_DATA){
            int emp_id;
            cout << "       Displaying specific Employee Data    " << endl;
            cout << BORDER_LINES <<  endl;
            cout << "\nEnter the employee id : ";
            cin  >> emp_id;
            emp.diplaySpecificEmployee(emp_id);
        }else if (resp == EXIT){
            cout << "           Exiting Admin Login    " << endl;
            cout << BORDER_LINES <<  endl;
        }else if (resp == GRANT_LEAVE){
            cout << "           Granting Leave to employees    " << endl;
            cout << BORDER_LINES <<  endl;
            emp.grantLeaveToEmployee();
        }else if (resp == VIEW_LEAVE_COUNTS){
            cout << "           Default Leave counts   " << endl;
            cout << BORDER_LINES <<  endl;
            cout << "   Intern Work from Home    -  " << emp.getInternWorkFromHome() << endl;
            cout << "   Senior Work from Home    -  " << emp.getSeniorWorkFromHome() << endl;
            cout << "   Manager Work from Home   -  " << emp.getManagerWorkFromHome() << endl;
            cout << "   Annual Leave             -  " << emp.getAnnualLeave() << endl;
            cout << "   Vacation Leave           -  " << emp.getAnnualLeave() << endl;
            cout << "   Team Time Off            -  " << emp.getTeamOff() << endl;
            cout << "   Maternity Leave          -  " << emp.getMaternityLeave() << endl;
            cout << "   Paternity Leave          -  " << emp.getPaternityLeave() << endl;
            cout << "   Marriage Leave           -  " << emp.getMarriageLeave() << endl;
        }else if (resp == ADD_MANAGER_DATA){
            cout << "         Adding new manager data   " << endl;
            cout << BORDER_LINES <<  endl;
            admin.addManagerData(emp);
        }else if (resp == REMOVE_MANAGER_DATA){
            cout << "         Remove Manager data   " << endl;
            cout << BORDER_LINES <<  endl;
            admin.removeManagerData(emp);
        }else if (resp == VIEW_MANAGER_DATA){
            cout << "         Viewing Manager details   " << endl;
            cout << BORDER_LINES <<  endl;
            admin.viewManagerDetails(emp);
        }else if (resp == UPDATE_MANAGER_DATA){
            cout << "         Updating Manager details   " << endl;
            cout << BORDER_LINES <<  endl;
            admin.updateManagerData(emp);
        }else if (resp == ADD_PROJECT_DATA){
            cout << "         Adding new project data   " << endl;
            cout << BORDER_LINES <<  endl;
            admin.addProjectData(emp);
        }else if (resp == REMOVE_PROJECT_DATA){
            cout << "         Removing Project details   " << endl;
            cout << BORDER_LINES <<  endl;
            admin.removeProjectData(emp);
        }else if (resp == VIEW_PROJECT_DATA){
            cout << "         Viewing Project details   " << endl;
            cout << BORDER_LINES <<  endl;
            admin.viewProjectDetails(emp);
        }else if (resp == UPDATE_PROJECT_DATA){
            cout << "         Updating Project data   " << endl;
            cout << BORDER_LINES <<  endl;
            admin.updateProjectData(emp);
        }else if (resp == MAP_EMPLOYEE_TO_MANAGER){
            cout << "         Mapping employee to manager  " << endl;
            cout << BORDER_LINES <<  endl;
            int emp_id,manager_id;
            cout << "Enter the engineer - employee id  :  ";
            cin  >> emp_id;
            cout << "\nEnter the manager - employee id   :  ";
            cin  >> manager_id;
            emp.mapEmployeeToManager(emp_id, manager_id);
        }else if (resp == MAP_EMPLOYEE_TO_PROJECT){
            cout << "         Mapping employee to project  " << endl;
            cout << BORDER_LINES <<  endl;
            int emp_id,project_id;
            cout << "Enter the employee id  :  ";
            cin  >> emp_id;
            cout << "\nEnter the project id   :  ";
            cin  >> project_id;
            emp.mapEmployeeToProject(emp_id, project_id);
        }else if (resp == VIEW_EMP_PROJECT_AND_MANAGER_INFO){
            cout << " View Employee's manager and project data " << endl;
            cout << BORDER_LINES <<  endl;
            int emp_id;
            cout << "Enter the employee id  :  ";
            cin  >> emp_id;
            emp.viewManagerAndProjectDetails(emp_id);
        }else if (resp == ADD_ATTENDANCE_ENTRY){
            cout << "     Adding the attendance entry of the day " << endl;
            cout << BORDER_LINES <<  endl;
            string filename;
            cout << "\nEnter the csv file name : ";
            cin >> filename;
            filename = ATTENDANCE_DIR+filename;
            admin.readCSVAndStore(filename, emp);
        }else if(resp == VIEW_ADDITIONAL_LEAVE_REQ){
            map<int, vector<leave_req>>& pending_leave_req = emp.getPendingLeaveRequest();
            message_details message_info;
            string subject;

            for (auto& [key, leave_vector] : pending_leave_req) {
                cout << "Processing leave requests for Employee ID: " << key << endl;

                for (auto it = leave_vector.begin(); it != leave_vector.end(); ++it) {
                    if (!it->status) {
                        cout << "Leave Type     : " << it->leave_type << endl;
                        cout << "Number of Days : " << it->number_of_days << endl;
                        cout << "Reason         : " << it->comments << endl;

                        char choice;
                        cout << "\nDo you want to approve this leave request? (y/n): ";
                        cin >> choice;
                        if (choice == 'y' || choice == 'Y') {
                            it->status = APPROVED;
                            cout << "Leave request approved.\n";

                            subject = "Your Leave Request  has been Approved.\n"
                                        "Leave type: " + it->leave_type + "\n" +
                                        "Number of Days: " + to_string(it->number_of_days) + "\n" +
                                        "Reason: " + it->comments + "\n";
                            message_info.info = subject;

                            emp.addMessage(key, message_info);
                        } else if (choice == 'n' || choice == 'N'){
                            it->status = REJECTED;
                            cout << "Leave request not approved.\n";

                            subject = "Your Leave Request  has been Rejected.\n"
                                        "Leave type: " + it->leave_type + "\n" +
                                        "Number of Days: " + to_string(it->number_of_days) + "\n" +
                                        "Reason: " + it->comments + "\n";
                            message_info.info = subject;

                            emp.addMessage(key, message_info);
                        }
                    }
                }
            }
        }else if (resp == ADD_ANNOUNCEMENTS){
            string message;
            cout << "Enter the message info : ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, message);

            message = "Date : " + getCurrentDate() + "\n\n" + "Message : " + message;

            emp.addAnnouncements(message);
        }

    }while(resp != EXIT);
}

void Login::addHoliday(string name, string date){
    holidayCalendar[name] = date;
}

void Login::showHolidays(){
    cout << "          HOLIDAY CALENDAR  -  2024   " <<  endl;
    cout << BORDER_LINES <<  endl;
    for (auto it = holidayCalendar.begin(); it != holidayCalendar.end(); ++it) {
        cout << left << setw(20) << it->first << setw(5) <<  ":"  << setw(5) << it->second << '\n';
    }
}

string Login::getLeaveType(int type){
    string leave_type;

    if(type == WORK_FROM_HOME){
        leave_type = "WORK_FROM_HOME";
    }else if(type == VACATION_LEAVE){
        leave_type = "VACATION_LEAVE";
    }else if(type == ANNUAL_LEAVE){
        leave_type = "ANNUAL_LEAVE";
    }else if(type == TEAM_TIME_OFF){
        leave_type = "TEAM_TIME_OFF";
    }else if(type == PATERNITY_LEAVE){
        leave_type = "PATERNITY_LEAVE";
    }else if(type == MATERNITY_LEAVE){
        leave_type = "MATERNITY_LEAVE";
    }else if(type == MARRIAGE_LEAVE){
        leave_type = "MARRIAGE_LEAVE";
    }
    return leave_type;
}

string Login::getCurrentDate() {    
    auto now = chrono::system_clock::now();
    auto in_time_t = chrono::system_clock::to_time_t(now);

    stringstream ss;
    ss << put_time(localtime(&in_time_t), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}