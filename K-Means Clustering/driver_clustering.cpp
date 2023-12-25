//#include <opencv2/opencv.hpp>
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//int main()
//{
//    int image_width = 500;
//    int image_height = 500;
//
//    Mat plot_image(image_height, image_width, CV_8UC3, Scalar(255, 255, 255));
//    int x1 = 100, y1 = 400, x2 = 400, y2 = 100;
//
//    line(plot_image, Point(x1, y1), Point(x2, y2), Scalar(0, 0, 255), 2, 8);
//
//    namedWindow("Graph", WINDOW_NORMAL);
//    imshow("Graph", plot_image);
//    waitKey(0);
//    return 0;
//}




#include <iostream>
#include <string>
#include<cmath>
#include <fstream>
#include <sstream>
using namespace std;


float eq_dist(float px, float py, float cx, float cy)
{
	return sqrt(((px - cx) * (px - cx)) + ((py - cy) * (py - cy)));
}

bool update_centroid(float px, float py, float& cx, float& cy, float** arr, int count, int K)
{
	float sumx = 0;
	float sumy = 0;
	int i = 0, j = 0;
	for (i = 0, j = 0; j < count; i++)
	{
		if (arr[i][2] == K)
		{
			sumx += arr[i][0];
			sumy += arr[i][1];
			j++;
		}
	}
	cx = sumx / j;
	cy = sumy / j;
	return 1;
}

int main()
{
	int r = 4000;
	int c = 3;
	float** arr = new float* [r];

	for (int i = 0; i < r; i++)
	{
		arr[i] = new float[c];
	}

	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			arr[i][j] = 0.0;
		}
	}

	fstream file;
	file.open("driver_data.csv");

	string line = "";
	string Id = "";
	string temp_dist = "";
	string temp_speed = "";
	float dist = 0.0;
	float speed = 0.0;
	int m = 0;
	string tempString = "";



	//while (getline(file, line))
	while (getline(file, line))
	{
		//stringstream inputString(line);

		file >> line;


		int i = 0;
		temp_dist = "";
		temp_speed = "";
		for (int j = 0; line[j] != '\0'; j++)
		{
			if (line[j] == ',')
			{
				i++;
				continue;
			}
			else if (!(line[j] > 47 && line[j] < 58) && line[j] != ',' && line[j] != '.')
			{
				break;
			}
			else if (i == 0)
			{
				Id += line[j];
			}
			else if (i == 1)
			{
				temp_dist += line[j];
				//	t_d++;
			}
			else
			{
				temp_speed += line[j];
				///t_s++;
			}
		}
		cout << temp_dist << "\t" << temp_speed << endl;
		//Id = line.substr(',');
		//getline(inputString, Id);

		//getline(inputString, tempString, ',');
		////getline(inputString, tempString);

		if (i != 0)
		{
			dist = stof(temp_dist.c_str());

			//getline(inputString, tempString);
			speed = stof(temp_speed.c_str());
			arr[m][0] = dist;
			arr[m][1] = speed;
			cout << arr[m][0] << "\t" << arr[m][1] << endl;
			m++;
		}

		//		line = "";
				//if (!file.eof())
				//{
				//	break;
				//}
	}


	cout << "*************************************** -:FILE DATA READ:- ***************************************" << endl;

	float c1x = arr[0][0];
	float c1y = arr[0][1];
	arr[0][2] = 1;
	float c2x = arr[1500][0];
	float c2y = arr[1500][1];
	arr[1500][2] = 2;
	float c3x = arr[3500][0];
	float c3y = arr[3500][1];
	arr[3500][2] = 3;
	int count1 = 0;
	int count2 = 0;
	int count3 = 0;


	float mini = 0;
	float A_D[3] = { 0 };
	int p = 0;

	bool flag = false;
	for (int i = 0; i < r; i++)
	{
		A_D[0] = eq_dist(arr[i][0], arr[i][1], c1x, c1y);
		A_D[1] = eq_dist(arr[i][0], arr[i][1], c2x, c2y);
		A_D[2] = eq_dist(arr[i][0], arr[i][1], c3x, c3y);

		mini = A_D[0];

		for (int j = 0; j < 3; j++)
		{
			if (A_D[j] < mini)
			{
				mini = A_D[j];
			}
		}

		if (mini == A_D[0]){
			arr[i][2] = 1;
			count1++;
			update_centroid(arr[i][0], arr[i][1], c1x, c1y, arr, count1, 1);
		}
		else if (mini == A_D[1]){
			arr[i][2] = 2;
			count2++;
			update_centroid(arr[i][0], arr[i][1], c2x, c2y, arr, count2, 2);
		}else
		{
			arr[i][2] = 3;
			count3++;
			update_centroid(arr[i][0], arr[i][1], c3x, c3y, arr, count3, 3);
		}

		if (i == 3999 && p < 10)
		{
			i = 0;
			count1 = 0;
			count2 = 0;
			count3 = 0;
			p++;
			flag = true;
			for (int k = 3; k < r; k++)
			{
				arr[k][2] = 0;
			}
			cout << "*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*" << endl;
		}

		//if (flag)
		//{
		//	cout <<"I : " << i << endl;
		//}
	}


	ofstream opt;
	opt.open("output_clust.csv");
	opt << "Mean_Distance,";
	opt << "Speed,";
	opt << "Clustering Value" << endl;

	for (int i = 0; i < r; i++)
	{
		cout << arr[i][0] << "\t" << arr[i][1] << "\t" << arr[i][2];
		opt << arr[i][0] << "," << arr[i][1] << "," << arr[i][2];
		opt << endl;
		cout << endl;
	}

	return 0;
}





//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
////void displayStudents(vector<StudentRecord>& students) {
////
////    for (auto student : students) {
////        student.display();
////    }
////}
////
////int main()
////{
////    ifstream inputFile;
////    inputFile.open("student_records.csv");
////    string line = "";
////
////    vector<StudentRecord> students;
////    while (getline(inputFile, line)) {
////
////        stringstream inputString(line);
////
////        //StudentId, Last Name, FirstName, Age, Phone Number, GPA
////        string studentId;
////        string lastName;
////        string firstName;
////        int age;
////        string phone;
////        double gpa;
////        string tempString;
////
////        getline(inputString, studentId, ',');
////        getline(inputString, lastName, ',');
////        getline(inputString, firstName, ',');
////        getline(inputString, tempString, ',');
////        age = atoi(tempString.c_str());
////        getline(inputString, phone, ',');
////        getline(inputString, tempString);
////        gpa = atof(tempString.c_str());
////
////        StudentRecord student(studentId, lastName,
////            firstName, age, phone, gpa);
////        students.push_back(student);
////        line = "";
////    }
////
////    displayStudents(students);
////}
//
//
//
////
//// struct StudentRecord {
////public:
////    StudentRecord(
////        string id,
////        string firstName,
////        string lastName,
////        int age,
////        string phoneNumber,
////        double gpa
////    ) {
////        Id = id;
////        FirstName = firstName;
////        LastName = lastName;
////        PhoneNumber = phoneNumber;
////        Age = age;
////        Gpa = gpa;
////    }
////
////    void display() {
////        cout << "   Student ID: " << Id << endl;
////        cout << "   First Name: " << FirstName << endl;
////        cout << "    Last Name: " << LastName << endl;
////        cout << " Phone Number: " << PhoneNumber << endl;
////        cout << "          Age: " << Age << endl;
////        cout << "          GPA: " << Gpa << endl;
////        cout << endl;
////    }
////
////    string Id;
////    string FirstName;
////    string LastName;
////    string PhoneNumber;
////    int Age;
////    double Gpa;
////
////};
////