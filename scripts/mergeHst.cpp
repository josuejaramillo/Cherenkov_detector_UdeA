#include <iostream>
#include <string>
#include <fstream>
using namespace std;
int main(){
	ofstream outFile("histogram.hst");
	outFile << "p_in_bin(GeV) N_phot N_e+ N_e- N_mu+ N_mu- N_pi0 N_pi+ N_pi- N_n N_p N_pbar N_others Total_per_bin" << endl;
	for(int i = 1; i<61; i++){
		string file = "Salida_"+to_string(i)+".hst";
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
