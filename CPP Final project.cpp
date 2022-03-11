
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

using namespace std;

const int MAX = 10;
//void chomp(char str[40]);
//bool is_string(string s1);

class students
{
	//private part of the class
	int std_num; 
	string name;
	string department;
	int num_sub; float marks[MAX];
	char grades[MAX];
	struct adress
	{
		string city;
		string residential_area;
		int zip_code;
	}loc;
public:
	void enter() //enter the data of a student
	{
		ofstream file1("students.txt", ios::app); //a text file is created/opened with the name students

		//Enter the name
		cout << "Enter the student's name : ";
		cin.ignore();
		getline(cin, name);
		while (!is_string(name)) //check if the name contains any thing other than letters
		{
			cout << "Invalid input, Please try again\n"; //if the name is not accpeted prompt the user to enter another name
			cout << "Enter the student's name : ";
			getline(cin, name);

		}
		file1<<"\n"<< name<<"|"; //return to \n

		//Enter the ID
		cout << "Enter the student's ID : ";
		cin>>  std_num;
		while (IDcheck(std_num))//check if the ID is already in use 
		{
			cout << "ID is already in use, please try again\n";
			cout << "Enter the student's ID : "; 
			cin >> std_num;
		}
		file1 << std_num << "|"; //store the ID in the file. "|" is used as sperate between data in the file

		cin.ignore(); //Ignore unwanted entries
		//Enter Department
		cout << "Enter your department : ";
		getline(cin, department);
		file1 << department << "|"; //Store data in the file
		//Enter the number of subjects
		cout << "Enter the student's number of subject : "; 
		cin >> num_sub;
		file1 << num_sub<<" ";
		//Enter the marks
		for (int i = 0; i < num_sub; i++) //according to the number of subject entered by the user
		{
			cout << "Enter the mark of the " << i + 1 << " : ";// the user will be prompted to enter the mark of each subject in an array
			cin >> marks[i];
			if (marks[i] < 0 || marks[i]>100)
			{
				cout << "the mark must be between 0 and 100\n";
				cout << "Enter the mark of the " << i + 1 << " : ";
				cin >> marks[i];
				
			}
			else
			{
				file1 << marks[i] << " ";//the array is stored inside the text in order
			}
		}
		//Enter the city
		cout << "Enter the student's City : ";
		cin.ignore(); //ignore unwanted entries
		getline(cin, loc.city);
		file1 << loc.city << "|";
		//Enter the residential area
		cout << "Enter the student's Residential Area : ";
		getline(cin, loc.residential_area);
		file1 << loc.residential_area << "|";
		//Enter the zip code
		cout << "Enter the student's ZIP Code : ";
		cin >> loc.zip_code;
		file1 << loc.zip_code << "|";
		cout << "\nSucessfully entered\n"; //confirm that the Entry was Sucessfully
		cin.ignore();		
		file1.close();
	}
	void display()
	{
		//new variables are declared to read the file as characters
		char name[30], id[10], dep[25], city[15], resd[15], zip[15];
		int nsubs, nmarks[10];
		ifstream mfile("students.txt"); //read the file using ifstream
		while (!mfile.eof())
		{
			//read the name of each student 
			mfile.getline(name, 30, '|');
			chomp(name); //use chomp to remove \n from each name if 
			mfile.getline(id, 10, '|'); 
			mfile.getline(dep, 25, '|');

			mfile >> nsubs; //read the number of subs to determine how many marks wil be read
			for (int i = 0; i < nsubs; i++)
			{
				mfile >> nmarks[i];
			} 
			mfile.ignore(); //ignore unwanted entries
			mfile.getline(city, 15, '|'); 
			mfile.getline(resd, 15, '|');
			mfile.getline(zip, 15, '|');

			//data will be printed once they are read one by one
			if (name[0] != '\0') //stop when there are no names left
			{
				cout << "\nThe name of the student : "; 
				cout << name << " \nID : " << id << "\nDepartment : " << dep << " \nNumber of subjects : " << nsubs << " ";
				for (int i = 0; i < nsubs; i++)
				{
					cout << "\nThe mark of the subject number " << i + 1 << " is : " << nmarks[i] << " ";
				}
				cout << "\nThe city is : " << city << "\nThe resedential area is : " << " " << resd << "\nThe zip code is : " << " " << zip << endl;
			}
		}
	}
	void modify_student() //modify the text file
	{
		//the same variables that we used earlier to store data
		char rname[30], dep[25], city[15], resd[15], zip[15];
		int nsubs, nmarks[10], id, idq;
		ifstream mfile("students.txt");      //read from students.txt file
		ofstream temp("tmp.txt");            //the data will be stored in the tmp.txt file
		cin.ignore();                        //ignore unwanted entries
		cout << "Enter the ID of the required student : ";  //ask the user for the ID of the student required 
		cin >> idq;                                         //the required ID
		while (!IDcheck(idq))                               //check if the ID exists other wise prompt the user to enter a new one
		{
			cout << "ID not found, Please try again\n";
			cout << "Enter the ID of the required student : ";
			cin >> idq;
		}
		while (!mfile.eof())                                //read until the end of file
		{
			mfile.getline(rname, 30, '|');
			chomp(rname); //remove the unwanted characters "\n"
			mfile >> id;
			mfile.ignore();//ignore unwanted entries
			mfile.getline (dep, 25, '|'); //read a certain number of characters or until "|".
			mfile >> nsubs;
			for (int i = 0; i < nsubs; i++) //read marks according to the number of marks read earlier
			{
				mfile >> marks[i];
			}
			mfile.ignore();
			mfile.getline(city, 15, '|');  //read a certain number of characters or until "|".
			mfile.getline(resd, 15, '|');  //read a certain number of characters or until "|".
			mfile.getline(zip, 15, '|');   //read a certain number of characters or until "|".

			if (id == idq) //if the ID required is read do the following
			{ 
				//Enter the new modified data
				cin.ignore();
				cout << "Enter the new name : ";
				getline(cin, name);
				while (!is_string(name)) //check that the name entered contains letters only
				{
					cout << "Invalid input, Please try again\n";
					cout << "Enter the student's name : ";
					getline(cin, name);

				}
				cout << "Enter the new student's number : ";
				cin >> id;
				while (IDcheck(id)) //check if the ID is already in use. If in use ask the user for another ID
				{
					cout << "ID is already in use, please try again\n";
					cout << "Enter the student's ID : ";
					cin >> id;
				}
				cin.ignore(); //ignore unwanted entries
				cout << "Enter the student's new department : "; 
				cin.getline(dep, 25);
				temp << name << "|" << id << "|" << dep << "|"; //continue
				cout << "Enter the new number of subjects : ";
				cin >> nsubs;
				temp << nsubs << " ";
				for (int i = 0; i < nsubs; i++) //according to the number of subjects, enter a mark for each
				{
					cout << "Enter the new mark for the " << i + 1 << " subject : ";
					cin >> nmarks[i];
					if ((int)nmarks[i] < 0 || (int)nmarks[i]>100)
					{
						cout << "the mark must be between 0 and 100\n";
						cout << "Enter the mark of the " << i + 1 << " : ";
						cin >> nmarks[i];

					}
					else
					{
						temp << nmarks[i] << " ";
					}
				}
				cout << "Enter the new city : ";
				cin.ignore(); //ignore unwanted entries
				cin.getline(city, 15);
				cout << "Enter the new resedential : ";
				cin.getline(resd, 15);
				cout << "Enter the new Zip code : ";
				cin.getline(zip, 15);
				temp << city << "|" << resd << "|" << zip << "|" << "\n";
				//cin.ignore();
			}
			else if(rname[0]!='\0') //don't go through the loop if there are no names left
			{
				temp << rname << "|" << id << "|" << dep << "|";
				temp << nsubs << " ";
				for (int i = 0; i < nsubs; i++)
				{
					temp << marks[i]<<" "; 	
				}
				temp << city << "|" << resd << "|" << zip << "|" << "\n";
			}
		}
		//close both files
		temp.close(); 
		mfile.close();

		remove ("students.txt");              //delete the students file 
		rename("tmp.txt", "students.txt");    //rename the tmp file to students file to take its place
		cout << "Successfully modified\n  ";   //print a confirmation message that the process was successfull
	}
	void get_grades() //display the grades of a student
	{
		//variables to store data in
		char name[30], dep[25], city[15], resd[15], zip[15];
		int nsub, nmarks[10], id,idq;
		float sum = 0;
		double psum;
		ifstream gfile("students.txt"); //read from the text file
		//char rq[30]; 
		cout << "Enter the ID of the required student to get his grades : ";  
		cin.ignore(); //ignore unwanted entries
		cin >> idq;
		while (!IDcheck(idq)) //check if the ID exists. If not prompt the user to enter another ID.
		{
			cout << "ID not found, Please try again\n";
			cout << "Enter the ID of the required student to get his grades : ";
			cin >> idq;
		}
		while (!gfile.eof())       //read until the end of file.
		{
			
			gfile.getline(name, 30, '|');
			chomp(name);          //remove unwanted characters from the name "\n".
			gfile >> id;
			gfile.ignore();
			gfile.getline(dep, 25, '|'); 
			gfile >> nsub;
			for (int i = 0; i < nsub; i++)
			{
				gfile >> nmarks[i];
			}
			gfile.getline(city, 15, '|');
			gfile.getline(resd, 15, '|');
			gfile.getline(zip, 15, '|');
			if (idq == id && name[0] != '\0') //only enter if the ID required is read. Don't enter if there is no name read
			{
				for (int j = 0; j < nsub; j++) //the marks are computed then divided to print out a grade accordingly. 
				{
					sum += nmarks[j];  
				}
				psum = sum / (nsub * 100);
				if (psum < 0.5) cout <<name<< "'s Grade is F " << endl;
				else if ( psum < 0.65) cout <<name<< "'s Grade is D " << endl;
				else if ( psum < 0.75) cout <<name<< "'s Grade is C " << endl;
				else if ( psum < 0.85) cout <<name<< "'s Grade is B " << endl;
				else if ( psum > 0.85) cout << name<<"'s  Grade is A " << endl;
			}
		}
		gfile.close();
	}
	//search for a specific student
	void searchn()
	{
		char name[30], dep[25], city[15], resd[15], zip[15];
		int nsubs, nmarks[10], id, idrq;
		ifstream mfile("students.txt");
		char rq[30], lrq[30];
		char ans[3];
		
		cin.ignore(); 

			/*lrq[0] = '\0';		//reset the array of characters 
			cout << "Enter the name of the required student : ";
		
			cin.getline(rq, 25);
			
			int i; 
			for ( i = 0; rq[i]; i++) //make the search function case free by making both names upper case
			{
				lrq[i] = toupper(rq[i]);
			}
			lrq[i] = '\0';		//end the array of characters to assure there are no unwanted characters
			int len_name = strlen(rq);*/
			
			cout << "Enter the ID of the required student : ";		
			cin >> idrq;
			while (!IDcheck(idrq))		//check that the ID exists
			{
				cout << "ID not found, Please try again\n";
				cout << "Enter the ID of the required student : ";
				cin >> idrq;
			}
		

		
		while (!mfile.eof())
		{
			
			char lname[30] = { 0 };		//reset the array of characters each itteration
			mfile.getline(name, 30, '|');
			chomp(name);	//check for unwanted characters
			int i;
			for (i = 0; name[i]; i++)		//make tha characters upper case
			{
				lname[i] = toupper(name[i]);
			}
			lname[i] = '\0';		//end the array of characters
			mfile >> id;
			mfile.ignore();
			mfile.getline(dep, 25, '|');

			mfile >> nsubs;
			for (int i = 0; i < nsubs; i++)
			{
				mfile >> nmarks[i];
			}
			mfile.getline(city, 15, '|');
			mfile.getline(resd, 15, '|');
			mfile.getline(zip, 15, '|');

			if (id == idrq && name[0] != '\0') //enter only if name and ID are similar.
			{
				cout << "\nThe name you searched for : ";
				cout << name << " \nID : " << id << "\nDepartment : " << dep << " \nNumber of subjects : " << nsubs << " ";
				for (int i = 0; i < nsubs; i++)
				{
					cout <<"\nThe mark of the subject number "<< i+1 <<" is : "  << nmarks[i] << " ";
				}
				cout << "\nThe city is : " << city << "\nThe resedential area is : " << " " << resd << "\nThe zip code is : " << " " << zip << endl;
			}
		}
	}
	bool IDcheck(int idss) //check the existence or the repitition of the ID
	{
		char name[30], dep[25], city[15], resd[15], zip[15];
		int nsubs, nmarks[10], id;
		
		ifstream mfile("students.txt");
		while (!mfile.eof())
		{
			mfile.getline(name, 30, '|');
			mfile >> id;
			mfile.ignore();
			mfile.getline(dep, 25, '|');
			mfile >> nsubs;
			for (int i = 0; i < nsubs; i++)
			{
				mfile >> nmarks[i];
			}
			mfile.getline(city, 15, '|');
			mfile.getline(resd, 15, '|');
			mfile.getline(zip, 15, '|');
			
			
			if (idss ==  id)
			{
				return true;
			}
		
		}
			return false;
	}
	void delete_student() //delete a specific student
	{
		char name[30], dep[25], city[15], resd[15], zip[15];
		int nsubs, nmarks[10],id,idq;
		ifstream mfile("students.txt");		
		ofstream temp("tmp.txt");
		cout << "Enter the ID of the required student : ";		
		cin.ignore();
		cin >> idq;
		while (!IDcheck(idq))
		{
			cout << "ID not found, Please try again\n";
			cout << "Enter the ID of the required student : ";
			cin >> idq;
		}
		while (!mfile.eof())
		{
			mfile.getline(name, 30, '|');
			chomp(name);
			mfile >> id;
			mfile.ignore();
			mfile.getline(dep, 25, '|');
			mfile >> nsubs;
			for (int i = 0; i < nsubs; i++)
			{
				mfile >> marks[i];
			}
			mfile.ignore();
			mfile.getline(city, 15, '|');
			mfile.getline(resd, 15, '|');
			mfile.getline(zip, 15, '|');

			if (idq == id && name[0] != '\0') 
			{
				cout << "succesfully deleted \n";		//confirm that the process was Sucessfully
			}
			else if (name[0] != '\0')		//stop if there are no names left
			{
				temp << name << "|" << id << "|" << dep << "|";		
				temp << nsubs << " ";
				for (int i = 0; i < nsubs; i++)
				{
					temp << marks[i] << " "; //try nmarks IN CASE SOMETHING HAPPENS RETURN TO marks[i]	
				}
				temp << city << "|" << resd << "|" << zip << "|" << "\n";
			}
		}
		temp.close();
		mfile.close();

		remove("students.txt");
		rename("tmp.txt", "students.txt");

	}
	//check if the name contains other characters than letters.
	bool is_string(string s)
	{
		string s1 = s; 

		bool ok;
		while (true)
		{
			ok = 1;
			for (int i = 0; i < s1.length(); i++)
			{
				if (!((s1[i] >= 97 && s1[i] <= 122) || (s1[i] >= 65 && s1[i] <= 90) || s1[i] == 32 || s1[i] == 46))
				{
					ok = 0;
					break;
				}
			}
			if (ok)
			{
				s.erase(s.find_last_not_of(" \n\r\t") + 1);  //pass spaces and new lines and tabs
				return true;
			}

			return false;
		}
	}
	void chomp(char str[40]) //remove unwanted characters "\n"
	{
		int leng;
		leng = strlen(str);

		// Empty string 
		if (leng == 0) {
			return;
		}
		//general case to check for \n
		for (int i = 0; i < leng; i++)
		{
			int j;
			if (str[i] == '\n')
			{
				for (j = i; j < leng; j++)
				{
					swap(str[j], str[j + 1]);

				}
			}
		}
	}
};

int main()
{
	//print a menu for the user
	cout << "-------------------------------Welcome!-------------------------------\n";
	cout << "\n------------------Enter '1' to enter student data-------------------\n";
	cout << "\n------------------Enter '2' to display all students data------------\n";
	cout << "\n------------------Enter '3' to modify student data------------------\n";
	cout << "\n------------------Enter '4' to show student's grade-----------------\n";
	cout << "\n------------------Enter '5' to search for a student-----------------\n";
	cout << "\n------------------Enter '6' to delete a student---------------------\n";
	cout << "\n------------------Enter '7' to exit program-------------------------\n";
	students student;
	int opinion;
	
	//create a loop for multiple entries
	while (true)
	{
		cout << "\nplease enter an option \n";
		cin >> opinion; 
		switch (opinion)
		{
		case 1:
		{
			//enter a new student's data
			student.enter();
			break;
		}
		case 2:
		{
			//display all students' data
			student.display();
			break;
		}
		case 3:
		{
			//modify a certain student's data
			student.modify_student();
			break;
		}
		case 4:
		{
			//display the grades of a certain student
			student.get_grades();
			break;
		}
		case 5:
		{
			//display the data of a certain student
			student.searchn();
			break;
		}
		case 6:
		{
			//delete the data of a student
			student.delete_student();
			break;
		}
		case 7:
		{
			//Exit out of the program
			return 0;
		}
		default:
		{
			//for any invalid input 
			cout << "Invalid input, try again";
			break;
		}
		}
	}	
}

