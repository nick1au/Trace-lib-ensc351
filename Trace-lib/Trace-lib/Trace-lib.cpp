// Trace-lib.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "stdlib.h"
#include <fstream>
#include <cassert>
#include <string>
#include <chrono>

// http://www.cplusplus.com/reference/thread/thread/ tid
// https://msdn.microsoft.com/en-us/library/t2y34y40.aspx?f=255&MSPPError=-2147217396 pid

using namespace std;

struct logdata {
	string name;
	string cat;
	string ph;
	int pid;
	int tid;
	int ts;
};

void trace_start(const char* filename); // char vs const char
void trace_event_start(char* name, char* categories, char* arguments);
void trace_event_end(char* arguments);
void trace_end();
void write_to_text();

ofstream filestr;
logdata *myData;
int counter;
int write_state = 0; // 0 never written, 1 written

int main()
{
	trace_start("file.txt");
	cout << counter << endl;
	//char name = "name";
	//char cat = 'cat';
	//char arg = 'arg;'
	trace_event_start((char*) "name", (char*) "cat", (char*) "arg");
	trace_event_end((char*) "arg");
	write_to_text();
	trace_end();
	cin >> counter;
	return 0;
}

void trace_start(const char* filename) {
	filestr.open(filename);
	if (filestr.fail()) {
		cout << "Error opening file." << endl;
		assert(1);
	}

	myData = new logdata[11000]; //allocate stuff
	counter = 0;
}

void trace_event_start(char* name, char* categories, char* arguments) {
	(myData[counter]).name = (string)name;
	(myData[counter]).cat = (string)categories;
	(myData[counter]).ph = "B";
	(myData[counter]).pid = 1;
	(myData[counter]).tid = 1;
	if (counter == 0) {
		//start timer
	}
	// (myData[counter]).ts = ; store timestamp
	

	//cout << "name " << (myData[counter]).name << " cat " << (myData[counter]).cat << " ph "<< (myData[counter]).ph << " pid " << (myData[counter]).pid << " tid " << (myData[counter]).tid << endl;
	//cout << "cat " << (myData[counter]).cat << endl;

	//write_to_text();

	counter++;
	//cout << myData[0].name;
}

void trace_event_end(char* arguments) {
	int test_c = counter;
	while (test_c > 0) {
		test_c--;
		if ((myData[test_c]).ph == "B"){
		(myData[counter]).name = (myData[test_c]).name;
		(myData[counter]).cat = (myData[test_c]).cat;
		(myData[counter]).ph = "E";
		(myData[counter]).pid = (myData[test_c]).pid;
		(myData[counter]).tid = (myData[test_c]).tid;
		

		//cout << "name " << (myData[counter]).name << " cat " << (myData[counter]).cat << " ph " << (myData[counter]).ph << " pid " << (myData[counter]).pid << " tid " << (myData[counter]).tid << endl;
		//write_to_text();
		counter++;
		return;
		}
	}
	cout << "trace_event_end not possible since no start";


}

void trace_end() {
	filestr << "]";
	filestr.close();
}

void write_to_text() {
	if (write_state == 0) {
		filestr << "[ ";
		write_state = 1;
	}

	for (int i = 0; i < counter; i++)
	{
		cout << counter << endl;
		cout << "name " << (myData[i]).name << " cat " << (myData[i]).cat << " ph " << (myData[i]).ph << " pid " << (myData[i]).pid << " tid " << (myData[i]).tid << endl;
		filestr << "{ \"name\" : " << "\"" << myData[i].name << "\","
			<< "\"cat\":" << "\"" << myData[i].cat << "\","
			<< "\"ph\":" << "\"" << myData[i].ph << "\","
			<< "\"pid\":" << "\"" << myData[i].pid << "\","
			<< "\"tid\":" << "\"" << myData[i].tid << "\","
			<< "\"ts\":" << "\"" << myData[i].ts << "\" }" << endl;
	}
}