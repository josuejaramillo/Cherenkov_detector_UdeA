#include <iostream>
#include <string>
#include <fstream>
using namespace std;
int main(){
	ofstream outFile("showers.shw");
	for(int i = 1; i<61; i++){
		string file = "Salida_"+to_string(i)+".shw";
		ifstream inputFile(file);
		string line;
		while (getline(inputFile, line)) {
			if (line[0] ==  '#')
				continue;
			outFile << line << endl;
		}
		inputFile.close();
	}
	outFile.close();
	cout << "success" +  to_string(1) << endl;
	return 0;
}
