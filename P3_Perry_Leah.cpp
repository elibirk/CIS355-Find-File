#include <string.h>
#include <vector>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>
#include <stdint.h>
#include <locale.h>
#include <langinfo.h>
#include <fcntl.h>

using namespace std;

void getTimestamp(string name);
void FindFile(string currDir, string name);



int main(int argc, char * argv[]){
  string currDir = ".";
  
  FindFile(currDir, argv[1]);
  return 0;
}//end main
  


void FindFile(string currDir, string name){
    DIR * dir;//directory stream
    struct dirent * dptr; //directory pointer with information
    string currFile;
    string tempDir;
    char * dateString;

    if((dir=opendir(currDir.c_str())) != NULL){
      while((dptr = readdir(dir)) != NULL){
	currFile = dptr->d_name + '\0';
	//      cout << "Checking " << currFile << "\n";
  
      if(dptr->d_type == DT_DIR && currFile.compare(".") != 0 && currFile.compare("..") != 0){ 
	//recurse into function, skipping current and parent directories
	//	cout << "recusing into " << currFile << "\n";
	tempDir = currDir + "/" + dptr->d_name;
	FindFile(tempDir,name);
      }//end if

      else if(currFile.compare(name) == 0){//if we find the file...
        cout << "Found " << name << " in " << currDir << "\n";
	getTimestamp(name);
        return;
      }//end else if
     }//end while
    closedir(dir);
    }//end if
}//end findfile

void getTimestamp(string name){
  struct stat statStruct;
  stat(name.c_str(), &statStruct);

  struct tm * timeinfo = localtime(&statStruct.st_ctime);
  cout << "File last edited on: " << asctime(timeinfo);
}//end getTimestamp
