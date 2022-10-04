#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]){
    
    fstream myfile;
    string line;

    cout << argv[1] << endl;
    char* fileName = argv[1];
    myfile.open(fileName);

    int num_inputs;
    int num_conditions;
    string symbols[100];
    string conditions[100];

    if (myfile.is_open()){
        cout << "file is open" << endl;
        
        int whichLine = 0;
        while ( std::getline(myfile, line) ){
            cout << "        " << line << endl;
            
            if (whichLine == 0){
                num_inputs = stoi(line.substr(3, 1));
                cout << num_inputs << endl;
            }

            if (whichLine == 2){
                for (int i = 0; i < num_inputs; i++){
                    symbols[i] = line.substr(5 + 2 * i, 1);
                    cout << symbols[i];
                }
                cout << endl;
            }

            if (whichLine == 4){
                num_conditions = stoi(line.substr(3, 1));
                cout << num_conditions << endl;
                for (int i = 0; i < num_conditions; i++){
                    getline(myfile, line);
                    conditions[i] = line.substr(0, num_inputs);
                    cout << conditions[i] << endl;
                }
            }

            whichLine += 1;
        }
    }

    myfile.close();
    

    



}