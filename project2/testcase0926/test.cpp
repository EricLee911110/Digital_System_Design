#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void removeElementInVectorByIndex(vector<string>& arr, int idx){
    arr.erase(arr.begin() + idx);
}


vector<string> split(string word, char seperator){
    int start_idx = 0;
    int end_idx = 0;
    vector<string> result;
    for (int i = 0; i < word.size(); i++){
        if (word[i] == seperator){
            end_idx = i;
            result.push_back(word.substr(start_idx, end_idx - start_idx));
            start_idx = i + 1;
        }
        if (i == word.size() -1){
            end_idx = i;
            result.push_back(word.substr(start_idx, end_idx - start_idx + 1));
            start_idx = i + 1;
        }
    }

    return result;
}

vector<string> split_by_index(string word, int idx){
    vector<string> result;
    int start_idx = 0;

    result.push_back(word.substr(start_idx, idx));
    result.push_back(word.substr(idx + 1, word.size() - idx - 1));

    return result;
}


int main(int argc, char* argv[]){
    fstream myfile;
    string line;


    char* fileName = argv[1];
    myfile.open(fileName);

    int num_inputs;
    int num_conditions;
    string condition;
    vector<string> inputs;

    if (myfile.is_open()){
        //cout << "file is open" << endl;

        int whichLine = 0;
        while (std::getline(myfile, line)){
            if (whichLine == 0){
                num_inputs = stoi(line.substr(3, 1));
                //cout << "num_inputs: " << num_inputs << endl;
            }
            if (whichLine == 4){
                num_conditions = stoi(line.substr(3, 1));
                //cout << "num_conditions: " << num_conditions << endl;

                for (int i = 0; i < num_conditions; i++){
                    getline(myfile, line);
                    condition = line.substr(0, num_inputs) + " " + line.substr(num_inputs + 1, 1);
                    inputs.push_back(condition);
                    //cout << inputs[i] << endl;
                }
            }

            whichLine += 1;
        }
    }
    myfile.close();

   
    bool notDone = true;
    int while_count = 0;
    while (notDone == true){
        vector<int> delete_idx;

        
        for (int i = 0; i < inputs.size(); i++){
            string thisCondition = split(inputs[i], ' ')[0];
            string thisResult = split(inputs[i], ' ')[1];

            for (int ii = 0; ii < thisCondition.size(); ii++){
                if (thisCondition[ii] == '-'){
                    delete_idx.push_back(i);
                    //cout << i << endl;
                    /*
                    inputs.push_back(split(thisCondition, '-')[0] + "0" + split(thisCondition, '-')[1]);
                    inputs.push_back(split(thisCondition, '-')[0] + "1" + split(thisCondition, '-')[1]);
                    */
                    
                    // you should seperate by index!!
                    string temp1 = split_by_index(thisCondition, thisCondition.find('-'))[0];
                    string temp2 = split_by_index(thisCondition, thisCondition.find('-'))[1];
                    //cout << temp1 << "0" << temp2 << " " << thisResult << endl;
                    //cout << temp1 << "1" << temp2 << " " << thisResult << endl;

                    inputs.push_back(temp1 + "0" + temp2 + " " + thisResult);
                    inputs.push_back(temp1 + "1" + temp2 + " " + thisResult);
                    break;
                }
            }
        }

        for (int i = delete_idx.size() - 1; i >= 0; i--){
            removeElementInVectorByIndex(inputs, delete_idx[i]);
        }

        notDone = false;
        for (int i = 0; i < inputs.size(); i++){
            string thisCondition = split(inputs[i], ' ')[0];

            for (int ii = 0; ii < thisCondition.size(); ii++){
                if (thisCondition[ii] == '-'){
                    cout << "I did check!!" << endl;
                    notDone = true;
                }
            }
        }

        

        while_count += 1;
        if (while_count > 100){
            notDone = false;
        }        
    }
    
    for (int i = 0; i < inputs.size(); i++){
        cout << inputs[i] << endl;
    }




}