//header file
#include<iostream>
#include <cstdlib>
#include<cmath>
#include<windows.h>
#include<string>
#include<fstream>

using namespace std;

//function used
void file_to_arr(string arr_file[], int index_file);
void intro();
int menu();
void add_record();
void search_record_menu();
void search_record(int);
void search_record(int opt, string arr_get[], int &record_found);
void modify_record();
void generate_result();
void generate_att();
void logout();
//void str_to_arr(int arr_att[], int &sum, string line);

//file stream
fstream myfile,myfile1,myfile2;

//main function
int main ()
{	
	intro ();
	string user,user1,password, password1;
	//save data into string
	cout<<"Welcome to user registration ! \n";
	cout<<"Please enter an username : ";
	getline(cin,user);
	cout<<endl;
	cout<<"Please enter your password : ";
	getline(cin,password);
	cout<<endl;
	
	cout<<"You've done registration ! We'll repeat your username and password \n\n";
	cout<<"Your username is "<<user<<"\n\nYour password is "<<password<<endl;
	
	Sleep(3000);
	system("cls");
	

	// Prompting user to input username
	cout << "Enter Username : ";
	getline(cin,user1);

	//promprting user for password
	cout << "Enter Password : ";
	getline(cin,password1);
	
	//Checking if user's entered credentials are equal to actual USERNAME and PASSWORD 
	if(user1 == user && password1 == password)
	{
            cout << "LOGIN SUCCESS !!!" << endl;
            Sleep(3000);
            
            //open menu function
            int opt = 0;
            char con = 'y';

            while(con == 'y')
            {
                system("cls");
                opt = menu();

                switch(opt)
                {
                    case 1:	add_record();break;

                    case 2: search_record_menu();break;                

                    case 3:	modify_record(); break;

                    case 4:	generate_result(); break;

                    case 5:	generate_att(); break;

                    case 6: logout(); break ;
                }

                cout << "Would you like to continue? (y/n) : ";
                cin >> con;
            }
	}
	
        else
	{
		//login unsuccessful
            cout << "INVALID LOGIN DETAILS " << endl;
	}
	
        return 0;
}

//copy file to array
void file_to_arr(string arr_file[], int index_file)
{
    string line;
    index_file = 0;
    
    myfile.open("student.txt");
    
    while(getline(myfile,line))
    {
        arr_file[index_file] = line;
        index_file++;   
    }
    
    myfile.close();
}

//introduction of project
void intro()
{	
	cout<<"\t\t=======================================";
	cout<<"\n\n\n\t\t\t UNIVERSITI PUTRA MALAYSIA ";
	cout<<"\n\n\n\t\t\t  STUDENT RECORD SYSTEM";
	cout<<"\n\n\t\t\t  SEM 1 ECA ASSIGNMENT";
	cout<<"\n\n\n\t\t\t\t QUESTION 3 ";
	cout<<"\n\t\t=======================================";
	Sleep(3000);
	system("cls");
}

//menu function
int menu ()
{
    int opt;
    
    cout << "**********************************************" << endl;
    cout << "             1. Add Student Record            " << endl;
    cout << "             2. Search Student Record         " << endl;
    cout << "             3. Modify Student Record         " << endl;
    cout << "             4. Generate Results              " << endl;
    cout << "             5. Analyse Attendance            " << endl;
    cout << "             6. Logout			    		 " << endl;
    cout << "**********************************************" << endl;
    cout << "Select your option: ";
    cin >> opt;
    return opt;
}

//add record function
void add_record()
{
    string name, matric, ic, fac, course, session, attendance, test1, test2, assignment, final;
    int result;
    
    cin.ignore();
    cout << "---------New Student Record---------" << endl;
    cout << "Please fill in all field." << endl;
    cout << "Student Name   : ";   getline(cin,name);
    cout << "Matric Number  : ";   getline(cin,matric);
    cout << "IC Number      : ";   getline(cin,ic);
    cout << "Faculty        : ";   getline(cin,fac);
    cout << "Course         : ";   getline(cin,course);
    cout << "Session        : ";   getline(cin,session);
    cout << "Attendance	    : ";   getline(cin,attendance);
    cout << "Test 1         : ";   getline(cin,test1);
    cout << "Test 2         : ";   getline(cin,test2);
    cout << "Assignment     : ";   getline(cin,assignment);
    cout << "Final          : ";   getline(cin,final);
    
    //save input to file
    myfile.open("student.txt", std::fstream::out | std::fstream::app);
    myfile << name      << '\n';
    myfile << matric    << '\n';
    myfile << ic        << '\n';
    myfile << fac       << '\n';
    myfile << course    << '\n';
    myfile << session   << '\n';
    myfile << attendance << '\n';
    myfile << test1     << '\n';
    myfile << test2     << '\n';
    myfile << assignment << '\n';
    myfile << final     << '\n';
    myfile << "END"     << '\n';
    myfile.close();
    
    myfile1.open("attendance.txt", std::fstream::out | std::fstream::app);
    myfile1 << name     << '\n';
    myfile1 << attendance << '\n';
    myfile1 << "END"    << '\n';
    myfile1.close();
    
    myfile2.open("result.txt", std::fstream::out | std::fstream::app);
    myfile2 << name     << '\n';
    myfile2 << test1    << '\n';
    myfile2 << test2    << '\n';
    myfile2 << assignment << '\n';
    myfile2 << final    << '\n';
    myfile2 << "END"    << '\n';
    myfile2.close();
    
    cout << "(New Student Record Added Successful)" << endl;
}

//search record function
void search_record_menu()
{
    string search;
    int opt;
    
    system("cls");
    cout << "---------------Search Student Record--------------" << endl;
    cout << "//**********************************************//" << endl;
    cout << "//  Search the record based on:                 //" << endl;
    cout << "//             1. Name                          //" << endl;
    cout << "//             2. Matric Number                 //" << endl;
    cout << "//             3. IC Number                     //" << endl;
    cout << "//**********************************************//" << endl;
    cout << "Select your option: ";
    cin >> opt;
    
    search_record(opt);
    
}

//search record based on option 
void search_record(int opt)
{
    string search, tmp;
    int found = 0, arr_index = 0, index_file = 0, index_count = 0, search_found = 0, correct = 0;
    string arr_file[1000];
    string arr_name[100], arr_matric[100], arr_ic[100], arr_fac[100], arr_course[100], arr_session[100],
            arr_attendance[100], arr_test1[100], arr_test2[100], arr_assignment[100], arr_final[100];
    
    switch(opt)
    {
        case 1: cout << "Search Name: "; break;
        case 2: cout << "Search Matric Number: "; break;
        case 3: cout << "Search IC Number: "; break;
    }
    cin.ignore();
    getline(cin,search);
    
    file_to_arr(arr_file, index_file);

    for(int i=0 ; i<1000 ; i++)
    {
        
        index_count++;
        tmp = arr_file[i];
        found = tmp.find(search);
        if(found > -1)
        {
            search_found = 1;
            break;
        }
    }
    
    if(search_found == 1)
    {
        arr_index = 0;
        switch(opt)
        {
            case 1:
            {
                if(index_count%12 != 1) {correct = 0; break;}
                index_count--;
                arr_name[arr_index]     = arr_file[index_count++];
                arr_matric[arr_index]   = arr_file[index_count++];
                arr_ic[arr_index]       = arr_file[index_count++];
                arr_fac[arr_index]      = arr_file[index_count++];
                arr_course[arr_index]   = arr_file[index_count++];
                arr_session[arr_index]  = arr_file[index_count++];
                arr_attendance[arr_index] = arr_file[index_count++];
                arr_test1[arr_index]    = arr_file[index_count++];
                arr_test2[arr_index]    = arr_file[index_count++];
                arr_assignment[arr_index] = arr_file[index_count++];
                arr_final[arr_index]    = arr_file[index_count];
                correct = 1;
                break;
            }

            case 2:
            {
                if(index_count%12 != 2) {correct = 0; break;}
                index_count -= 2;
                arr_name[arr_index]     = arr_file[index_count++];
                arr_matric[arr_index]   = arr_file[index_count++];
                arr_ic[arr_index]       = arr_file[index_count++];
                arr_fac[arr_index]      = arr_file[index_count++];
                arr_course[arr_index]   = arr_file[index_count++];
                arr_session[arr_index]  = arr_file[index_count++];
                arr_attendance[arr_index] = arr_file[index_count++];
                arr_test1[arr_index]    = arr_file[index_count++];
                arr_test2[arr_index]    = arr_file[index_count++];
                arr_assignment[arr_index] = arr_file[index_count++];
                arr_final[arr_index]    = arr_file[index_count];
                correct = 1;
                break;
            }

            case 3:
            {
                if(index_count%12 != 3) {correct = 0; break;}
                index_count -= 3;
                arr_name[arr_index]     = arr_file[index_count++];
                arr_matric[arr_index]   = arr_file[index_count++];
                arr_ic[arr_index]       = arr_file[index_count++];
                arr_fac[arr_index]      = arr_file[index_count++];
                arr_course[arr_index]   = arr_file[index_count++];
                arr_session[arr_index]  = arr_file[index_count++];
                arr_attendance[arr_index] = arr_file[index_count++];
                arr_test1[arr_index]    = arr_file[index_count++];
                arr_test2[arr_index]    = arr_file[index_count++];
                arr_assignment[arr_index] = arr_file[index_count++];
                arr_final[arr_index]    = arr_file[index_count];
                correct = 1;
                break;
            }
        }

		//display search record
        if(correct == 1)
        {
            cout << "-------------------------------------------------" << endl;
            cout << "Record Found" << endl;
            
            for(int i=0 ; i<arr_index+1 ; i++)
            {
                cout << "Record "           << i+1 << endl;
                cout << "Student Name: "    << arr_name[i] << endl;
                cout << "Matric Number.: "  << arr_matric[i] << endl;
                cout << "IC Number: "       << arr_ic[i] << endl;
                cout << "Faculty: "         << arr_fac[i] << endl;
                cout << "Course: "          << arr_course[i] << endl;
                cout << "Session: "         << arr_session[i] << endl;
                cout << "Attendance: "      << arr_attendance[i] << endl;
                cout << "Test 1: "          << arr_test1[i] << endl;
                cout << "Test 2	: "         << arr_test2[i] << endl;
                cout << "Assignment: "      << arr_assignment[i] << endl;
                cout << "Final: "           << arr_final[i] << endl;
            }
            cout << "-------------------------------------------------" << endl;
        }
        
        else
        {
            cout << "Record Not Found!" << endl;
        }
    }
    
    else
        cout << "Record Not Found!" << endl;
}

//open file location 
void search_record(int opt, string arr_get[], int &record_found)
{
    string search;
    int found = 0, arr_index = 0, index_file = 0, index_count = 0, search_found = 0, correct = 0;
    string arr_file[1000];
    
    switch(opt)
    {
        case 1: cout << "Search Name: "; break;
        case 2: cout << "Search Matric Number: "; break;
        case 3: cout << "Search IC Number: "; break;
    }
    cin.ignore();
    getline(cin,search);
    
    file_to_arr(arr_file, index_file);

    for(int i=0 ; i<1000 ; i++)
    {
        string tmp;
        
        index_count++;
        tmp = arr_file[i];
        found = tmp.find(search);
        if(found > -1)
        {
            search_found = 1;
            break;
        }
    }
    
    if(search_found == 1)
    {
        switch(opt)
        {
            case 1:
            {
                if(index_count%12 != 1) {correct = 0; record_found = 0; break;}
                index_count--;
                arr_get[arr_index++] = arr_file[index_count++];
                arr_get[arr_index++] = arr_file[index_count++];
                arr_get[arr_index++] = arr_file[index_count++];
                arr_get[arr_index++] = arr_file[index_count++];
                arr_get[arr_index++] = arr_file[index_count++];
                arr_get[arr_index++] = arr_file[index_count++];
                arr_get[arr_index++] = arr_file[index_count++];
                arr_get[arr_index++] = arr_file[index_count++];
                arr_get[arr_index++] = arr_file[index_count++];
                arr_get[arr_index++] = arr_file[index_count++];
                arr_get[arr_index]   = arr_file[index_count];
                correct = 1;
                record_found = 1;
                break;
            }

            case 2:
            {
                if(index_count%12 != 2) {correct = 0; record_found = 0; break;}
                index_count -= 2;
                arr_get[arr_index++] = arr_file[index_count++];
                arr_get[arr_index++] = arr_file[index_count++];
                arr_get[arr_index++] = arr_file[index_count++];
                arr_get[arr_index++] = arr_file[index_count++];
                arr_get[arr_index++] = arr_file[index_count++];
                arr_get[arr_index++] = arr_file[index_count++];
                arr_get[arr_index++] = arr_file[index_count++];
                arr_get[arr_index++] = arr_file[index_count++];
                arr_get[arr_index++] = arr_file[index_count++];
                arr_get[arr_index++] = arr_file[index_count++];
                arr_get[arr_index]   = arr_file[index_count];
                correct = 1;
                record_found = 1;
                break;
            }

            case 3:
            {
                if(index_count%12 != 3) {correct = 0; record_found = 0; break;}
                index_count -= 3;
                arr_get[arr_index++] = arr_file[index_count++];
                arr_get[arr_index++] = arr_file[index_count++];
                arr_get[arr_index++] = arr_file[index_count++];
                arr_get[arr_index++] = arr_file[index_count++];
                arr_get[arr_index++] = arr_file[index_count++];
                arr_get[arr_index++] = arr_file[index_count++];
                arr_get[arr_index++] = arr_file[index_count++];
                arr_get[arr_index++] = arr_file[index_count++];
                arr_get[arr_index++] = arr_file[index_count++];
                arr_get[arr_index++] = arr_file[index_count++];
                arr_get[arr_index]   = arr_file[index_count];
                correct = 1;
                record_found = 1;
                break;
            }
        }

        if(correct == 1)
        {
            cout << "-------------------------------------------------" << endl;
            cout << "Record Found" << endl;

            for(int i=0 ; i<arr_index+1 ; i++)
            {
                cout << "Record " << i+1 << endl;
                cout << "Student Name: "    << arr_get[i++] << endl;
                cout << "Matric Number.: "  << arr_get[i++] << endl;
                cout << "IC Number: "       << arr_get[i++] << endl;
                cout << "Faculty: "         << arr_get[i++] << endl;
                cout << "Course: "          << arr_get[i++] << endl;
                cout << "Session: "         << arr_get[i++] << endl;
                cout << "Attendance: "      << arr_get[i++] << endl;;
                cout << "Test 1: "          << arr_get[i++] << endl;
                cout << "Test 2	: "         << arr_get[i++] << endl;
                cout << "Assignment: "      << arr_get[i++] << endl;
                cout << "Final: "           << arr_get[i] << endl;
            }

            cout << "-------------------------------------------------" << endl;
        }
        else
        {
            cout << "Record Not Found!" << endl;
        }
    }
    
    else
        cout << "Record Not Found!" << endl;
}

//modify particular data
void modify_record()
{
    string arr_get[11], search, line, modify_word;
    int opt;
    int found = 0, owner_found = 0, owner_conf = 0, record_found;
    
    system("cls");
    cout << "---------------Search Student Record--------------" << endl;
    cout << "//**********************************************//" << endl;
    cout << "//  Search the record based on:                 //" << endl;
    cout << "//             1. Name                          //" << endl;
    cout << "//             2. Matric Number                 //" << endl;
    cout << "//             3. IC Number                     //" << endl;
    cout << "//**********************************************//" << endl;
    cout << "Select your option: ";
    cin >> opt;
    
    search_record(opt, arr_get, record_found);
    
    if(record_found == 1)
    {
        cout << "**********************************************" << endl;
        cout << "  Select the field to edit:                   " << endl;
        cout << "             1. Name                          " << endl;
        cout << "             2. Matric Number                 " << endl;
        cout << "             3. IC Number                     " << endl;
        cout << "             4. Faculty                       " << endl;
        cout << "             5. Course                        " << endl;
        cout << "             6. Session                       " << endl;
        cout << "             7. Attendance                    " << endl;
        cout << "             8. Test 1 		                " << endl;
        cout << "             9. Test 2	                     " << endl;
        cout << "             10. Assignment                   " << endl;
        cout << "             11. Final                        " << endl;
        cout << "**********************************************" << endl;
        cout << "Select your option: ";
        cin >> opt;
        search = arr_get[opt-1];
    
        ifstream myfilein("student.txt");
        ofstream myfileout("studenttmp.txt");
        
        int count = 0;
        while(getline(myfilein,line))
        {
            count++;
            owner_found = line.find(arr_get[0]);
            found = line.find(search);
            
            if(owner_found > -1 && found == -1)
            {
                owner_conf = 1;
            }
            
            else if(owner_found > -1 && found > -1)
            {
                if(count%12 == 1)
                {
                    cout << "Replace with: ";
                    cin.ignore();
                    getline(cin, modify_word);

                    line = modify_word;
                    owner_conf = 0;
                }
                
                else
                {}
            }
            
            else if(found > -1 && owner_conf == 1)
            {
                if(count%12 == opt)
                {
                    cout << "Replace with: ";
                    cin.ignore();
                    getline(cin, modify_word);

                    line = modify_word;
                    owner_conf = 0;
                }
                
                else
                {}
            }
            
            else
            {}
            
            line += '\n';
            myfileout << line;
        }
        
        myfilein.close();
        myfileout.close();
        remove("student.txt");
        rename("studenttmp.txt","student.txt");
    
        ifstream myfilein1("result.txt");
        ofstream myfileout1("resulttmp.txt");
        
        count = 0; owner_conf = 0;
        while(getline(myfilein1,line))
        {
            count++;
            owner_found = line.find(arr_get[0]);
            found = line.find(search);
            
            if(owner_found > -1 && found == -1)
            {
                owner_conf = 1;
            }
            
            else if(owner_found > -1 && found > -1)
            {
                line = modify_word;
                owner_conf = 1;
            }

            else if(found > -1 && owner_conf == 1)
            {
                if(count%6 == (opt-6))
                {
                    line = modify_word;
                    owner_conf = 0;
                }
                
                else
                {}
            }
            
            else
            {}
            
            line += '\n';
            myfileout1 << line;
        }
        myfilein1.close();
        myfileout1.close();
        remove("result.txt");
        rename("resulttmp.txt","result.txt");
       
        ifstream myfilein2("attendance.txt");
        ofstream myfileout2("attendancetmp.txt");
        
        count = 0; owner_conf = 0;
        while(getline(myfilein2,line))
        {
            count++;
            owner_found = line.find(arr_get[0]);
            found = line.find(search);
            
            if(owner_found > -1 && found == -1)
            {
                owner_conf = 1;
            }
            
            else if(owner_found > -1 && found > -1)
            {
                line = modify_word;
                owner_conf = 1;
            }

            else if(found > -1 && owner_conf == 1)
            {
                if(count%3 == (opt-5))
                {
                    line = modify_word;
                    owner_conf = 0;
                }
                
                else
                {}
            }
            
            else
            {}
            
            line += '\n';
            myfileout2 << line;
        }
        myfilein2.close();
        myfileout2.close();
        remove("attendance.txt");
        rename("attendancetmp.txt","attendance.txt");
        owner_found = 0;
    }
    
    else
    {}
}

//calculate the final result 
void generate_result()
{
    int opt, found = 0, arr_index = 0 , record_found = 0;
    double arr_Result[4], sum = 0;
    string arr_get[11], search, line;
    
    system("cls");
    cout << "---------------Search Student Record--------------" << endl;
    cout << "//**********************************************//" << endl;
    cout << "//  Search the record based on:                 //" << endl;
    cout << "//             1. Name                          //" << endl;
    cout << "//             2. Matric Number                 //" << endl;
    cout << "//             3. IC Number                     //" << endl;
    cout << "//**********************************************//" << endl;
    cout << "Select your option: ";
    cin >> opt;
    
    search_record(opt, arr_get, record_found);
    
    if(record_found == 1)
    {
        search = arr_get[0];
        
        myfile2.open("result.txt");
        
        while(getline(myfile2,line))
        {
            found = line.find(search);

            if(found > -1)
            {
                getline(myfile2,line);   arr_Result[arr_index++] = atof(line.c_str());
                getline(myfile2,line);   arr_Result[arr_index++] = atof(line.c_str());
                getline(myfile2,line);   arr_Result[arr_index++] = atof(line.c_str());
                getline(myfile2,line);   arr_Result[arr_index] = atof(line.c_str());
                
                cout << "Result Found" << endl;
                
                for(int i=0 ; i<arr_index+1 ; i++)
                {
                    sum += arr_Result[i];
                }
                
                cout << "Final result is  " << sum << endl;
            }
            
            else
            {}
        }
        
        myfile2.close();
    }
    
    else
    {
        cout << "Record Not Found!" << endl;
    }
}

//decide whether the attendance let the student to attend final 
void generate_att()
{
    int opt, found, att = 0, record_found = 0, owner_conf = 0;
    string arr_get[11];
    string search, line, line1, line2;
    
    system("cls");
    cout << "---------------Search Student Record--------------" << endl;
    cout << "//**********************************************//" << endl;
    cout << "//  Search the record based on:                 //" << endl;
    cout << "//             1. Name                          //" << endl;
    cout << "//             2. Matric Number                 //" << endl;
    cout << "//             3. IC Number                     //" << endl;
    cout << "//**********************************************//" << endl;
    cout << "Select your option: ";
    cin >> opt;
    
    search_record(opt, arr_get, record_found);
    
    if(record_found == 1)
    {
        search = arr_get[0];
        
        myfile1.open("attendance.txt");
        
        while(getline(myfile1,line))
        {
            found = line.find(search);
            
            if(found > -1)
            {
                getline(myfile1,line);cout << "Here!" << endl;
                att = atof(line.c_str());
                
                cout << "Attendance Record Found" << endl;
                cout << "Attendance of Semester: " << att << "%" << endl;
                
                if(att >= 80)
                {
                    cout<<"This student able to attend Final" << endl;
                }
                
                else
                {
                    cout<<"This student not able to attend Final" << endl;
                    
                    ifstream myfilein("student.txt");
                    ofstream myfileout("studenttmp.txt");
                    
                    int count = 0;
                    while(getline(myfilein,line1))
                    {
                        count++;
                        found = line1.find(search);
                        
                        if(found > -1)
                        {
                            owner_conf = 1;
                        }
                        
                        else if(count%12 == 11 && owner_conf == 1)
                        {
                            line1 = "0";
                            owner_conf = 0;
                        }
                        
                        else
                        {}
                        
                        line1 += '\n';
                        myfileout << line1;
                    }
                    myfilein.close();
                    myfileout.close();
                    remove("student.txt");
                    rename("studenttmp.txt","student.txt");
                    
                    ifstream myfilein1("result.txt");
                    ofstream myfileout1("resulttmp.txt");
                    
                    count = 0;
                    while(getline(myfilein1,line2))
                    {
                        count++;
                        found = line2.find(search);
                        
                        if(found > -1)
                        {
                            owner_conf = 1;
                        }
                        
                        else if(count%6 == 5 && owner_conf == 1)
                        {
                            line2 = "0";
                            owner_conf = 0;
                        }
                        
                        else
                        {}
                        
                        line2 += '\n';
                        myfileout1 << line2;
                    }
                    myfilein1.close();
                    myfileout1.close();
                    remove("result.txt");
                    rename("resulttmp.txt","result.txt");
                }
            }
            
            else
            {}
        }
        
        myfile1.close();
    }
    
    else
    {
        cout << "Record Not Found!" << endl;
    }
}

//logout system and exit
void logout()
{
	system ("cls");
	cout<<"\n\n\n\t\t\t     UNIVERSITI PUTRA MALAYSIA"<<endl;
	cout<<"\t\t\t      FACULTY OF ENGINEERING"<<endl;
	cout<<"\t\t\t**********************************"<<endl;
	cout<<"\n\n\n\t\t\t\tLOGOUT SUCCESSFUL  !"<<endl;
	cout<<"\n\n\n\t\t\t**********************************"<<endl;
	cin.ignore();
	exit(0);
}

/*void str_to_arr(int arr_att[], int &sum, string line)
{
    for(int i=0 ; i<31 ; i++)
    {
        arr_att[i] = line.at(i)-48;
        sum += arr_att[i];
    }
}*/
