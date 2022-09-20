#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

void copyArray(int* oldArray, int* NewArray){
    for (int i = 0; i < 32; i++){
        oldArray[i] = NewArray[i];
    }
}

void setZero(int* array, int* filter, int arrayLength){
    cout << "Before: ";
    for (int i = 0; i < arrayLength; i++){
        cout << array[i];
    }
    cout << endl;

    cout << "Filter: ";
    for (int i = 0; i < arrayLength; i++){
        cout << filter[i];
    }
    cout << endl;

    for (int i = 0; i < arrayLength; i++){
        if (filter[i] == 0){
            array[i] = 0;
        }
    }


    cout << "After: ";
    for (int i = 0; i < arrayLength; i++){
        cout << array[i];
    }
    cout << endl;
}

void setOne(int* array, int* filter, int arrayLength){
    cout << "resultFilter: ";
    for (int i = 0; i < arrayLength; i++){
        if (filter[i] == 1){
            array[i] = 1;
            
        };
        cout << array[i];
    }

    cout << endl;
}

void checkTable(int table[][4], int tableHeight){
    cout << "      Table:     " << endl;
    for (int i = 0; i < tableHeight; i++){
        cout << table[i][0] << " " << (char)table[i][1] << " " << table[i][2] << " " << table[i][3] << endl;
    }
}

void checkArray(int array[], int arrayLength){
    cout << "Check array result: ";
    for (int i = 0; i < arrayLength; i++){
        cout << array[i];
    }
    cout << endl;
}

int main(int argc, char* argv[]){
    string line;
    fstream myfile;
    int count = 0;

    int inputCount;
    string inputChar;

    int conditionCount;
    string conditions;
    
    // getting data from file
    myfile.open(argv[1]);
    if (myfile.is_open()) {
        while (myfile.good()){
            count++;
            getline(myfile, line);
            switch(count){
                case 1:{
                    cout << "case 1: " << endl;
                    inputCount = line[3] - '0';
                    cout << inputCount << endl;
                    break;
                }
                case 2: cout << "case 2" << endl; break;
                case 3:{ 
                    cout << "case 3" << endl;
                    for (int i = 0; i < inputCount; i++){
                        char currentChar = line[5 + 2 * i];
                        inputChar = inputChar + currentChar;
                    }
                    cout << inputChar << endl;
                    break;
                }
                case 4: {
                    cout << "case 4" << endl; 
                    break;
                }
                case 5: {
                    cout << "case 5" << endl;
                    conditionCount = line[3] - '0';
                    cout << "conditionCount: " << conditionCount << endl;
                    for (int i = 0; i < conditionCount; i++){
                        getline(myfile, line);
                        conditions = conditions + line + "a";
                        cout << conditions << endl;
                    }

                    break;
                }
            }
            
        }
    }
    else{
        cout << "Unable to open file" << endl;
    }
    myfile.close();


    int totalRows = pow(2, inputCount);

    int table[totalRows][4];
    for (int i = 0; i < totalRows; i++){
        table[i][0] = i;
        table[i][1] = 0;
        table[i][2] = 0;
        table[i][3] = 0;
        table[i][4] = 0;
    }
    int elseThen = 2;

    cout << "elseThen: " << elseThen << endl;

    // basic setup without caring the conditions
    for (int i = 0; i < pow(2, (inputCount - 1)); i++){
        if (i < 2 && i != 0){
            table[i][1] = inputChar[0];
            table[i][2] = elseThen++;
            table[i][3] = elseThen++;
            cout << table[i][0] << (char)table[i][1] << table[i][2] << table[i][3] << endl;
            
        } else if (i < 4 && i != 0){
            table[i][1] = inputChar[1];
            table[i][2] = elseThen++;
            table[i][3] = elseThen++;
            cout << table[i][0] << (char)table[i][1] << table[i][2] << table[i][3] << endl;
        } else if (i < 8 && i != 0){
            table[i][1] = inputChar[2];
            table[i][2] = elseThen++;
            table[i][3] = elseThen++;
            cout << table[i][0] << (char)table[i][1] << table[i][2] << table[i][3] << endl;
        } else if (i < 16 && i != 0){
            table[i][1] = inputChar[3];
            table[i][2] = elseThen++;
            table[i][3] = elseThen++;
            cout << table[i][0] << (char)table[i][1] << table[i][2] << table[i][3] << endl;
        }
    }
    
    int resultFilter[32];
    int currentFilterTemplate[32] = {1};
    int filter[32];  // filter of that one number inside the layer
    int currentFilter[32];  // filter of the entire layer

    std::fill_n(resultFilter, 32, 0);

    
    


    // Building up the correct filter
    cout << conditions << endl;

    string token;
    
    

    for (int i_condition = 0; i_condition < conditionCount; i_condition++){
        token = conditions.substr(i_condition*(inputCount+3), conditions.find('a'));
        cout << "          token: " << token << endl;
        std::fill_n(currentFilter, 32, 1);

        // Building up the correct filter for each condition
        for (int i_token = 0; i_token < 5; i_token++){
            if (token[i_token] == ' '){
                cout << "I counter a space in position: " << i_token << endl;
                break;
            }
            switch(i_token){
                case 0:{
                    if (token[i_token] == '1'){
                        cout << "I counter 1 in position: " << i_token << endl;
                        std::fill_n(filter, 32, 1);
                        for (int i = 0; i < (totalRows / 2); i++){
                            filter[i] = 0;
                        }
                        setZero(currentFilter, filter, totalRows);
                    }else if (token[i_token] == '0'){
                        cout << "I counter 0 in position: " << i_token << endl;
                        std::fill_n(filter, 32, 1);
                        for (int i = totalRows-1; i >= (totalRows / 2); i--){
                            filter[i] = 0;
                        }
                        setZero(currentFilter, filter, totalRows);
                    }
                        
                    break;
                }
                case 1:{
                    if (token[i_token] == '1'){
                        cout << "I counter 1 in position: " << i_token << endl;
                        std::fill_n(filter, 32, 1);
                        for (int j = 0; j < 2; j++){
                            for (int i = 0; i < (totalRows / 4); i++){
                                filter[j * (totalRows/2) + i] = 0;
                            }
                        }
                        setZero(currentFilter, filter, totalRows);
                    }else if (token[i_token] == '0'){
                        cout << "I counter 0 in position: " << i_token << endl;
                        std::fill_n(filter, 32, 1);
                        for (int j = 0; j < 2; j++){
                            for (int i = 0; i < (totalRows / 4); i++){
                                filter[(totalRows/4) + j * (totalRows/2) + i] = 0;
                            }
                        }
                        setZero(currentFilter, filter, totalRows);
                    }
                    break;
                }
                case 2:{
                    if (token[i_token] == '1'){
                        cout << "I counter 1 in position: " << i_token << endl;
                        std::fill_n(filter, 32, 1);
                        for (int j = 0; j < 4; j++){
                            for (int i = 0; i < (totalRows / 8); i++){
                                filter[j * (totalRows/4) + i] = 0;
                            }
                        }
                        setZero(currentFilter, filter, totalRows);
                    }else if (token[i_token] == '0'){
                        cout << "I counter 0 in position: " << i_token << endl;
                        std::fill_n(filter, 32, 1);
                        for (int j = 0; j < 4; j++){
                            for (int i = 0; i < (totalRows / 8); i++){
                                filter[(totalRows/8) + j * (totalRows/4) + i] = 0;
                            }
                        }
                        setZero(currentFilter, filter, totalRows);
                    }
                    break;
                }
                case 3: {
                    if (token[i_token] == '1'){
                        cout << "I counter 1 in position: " << i_token << endl;
                        std::fill_n(filter, 32, 1);
                        for (int j = 0; j < 8; j++){
                            for (int i = 0; i < (totalRows / 16); i++){
                                filter[j * (totalRows/8) + i] = 0;
                            }
                        }
                        setZero(currentFilter, filter, totalRows);
                    }else if (token[i_token] == '0'){
                        cout << "I counter 0 in position: " << i_token << endl;
                        std::fill_n(filter, 32, 1);
                        for (int j = 0; j < 8; j++){
                            for (int i = 0; i < (totalRows / 16); i++){
                                filter[(totalRows/16) + j * (totalRows/8) + i] = 0;
                            }
                        }
                        setZero(currentFilter, filter, totalRows);
                    }
                    break;
                }
                case 4:{
                    if (token[i_token] == '1'){
                        cout << "I counter 1 in position: " << i_token << endl;
                        std::fill_n(filter, 32, 1);
                        for (int j = 0; j < 16; j++){
                            for (int i = 0; i < (totalRows / 32); i++){
                                filter[j * (totalRows/16) + i] = 0;
                            }
                        }
                        setZero(currentFilter, filter, totalRows);
                    }else if (token[i_token] == '0'){
                        cout << "I counter 0 in position: " << i_token << endl;
                        std::fill_n(filter, 32, 1);
                        for (int j = 0; j < 16; j++){
                            for (int i = 0; i < (totalRows / 32); i++){
                                filter[(totalRows/32) + j * (totalRows/16) + i] = 0;
                            }
                        }
                        setZero(currentFilter, filter, totalRows);
                    }
                    break;
                }
            };
        }

        // put the correct filter into the result filter
        setOne(resultFilter, currentFilter, totalRows);
    }

    // use the resultFilter to complete the table
    
    int resultFilterIndex = 0;
    for (int i = (totalRows/2); i < totalRows; i++){
        table[i][1] = inputChar[inputCount-1];
        for (int j = 2; j < 4; j++){
            if (resultFilter[resultFilterIndex] == 1){
                table[i][j] = totalRows;
            }
            resultFilterIndex++;
        }

    }
    checkTable(table, totalRows);

    bool notReduced = true;
    int duplicateRow = 0;
    int duplicateThenElse = 1;
    int j = 1;
    while (notReduced){

        // Check row duplicate
        duplicateRow = 0;
        for (int i = 1; i < totalRows; i++){
            j = 1;
            while ((i + j) < totalRows){
                if (table[i][1] == table[i+j][1] && table[i][2] == table[i+j][2] && table[i][3] == table[i+j][3] && table[i+j][2] != -1){
                    // delete the value of the later one
                    table[i+j][2] = -1;
                    table[i+j][3] = -1;
 
                    if ((i+j+1) / 2 == (i+j) / 2){    // goes to else-edge
                        table[(i+j)/2][2] = i;
                    }else{                      // goes to then-edge
                        table[(i+j)/2][3] = i;
                    }
                    cout << "Row Duplicate move: " << i << " & " << i+j << endl;
                    checkTable(table, totalRows);
                    duplicateRow = 1;
                }
                j++;
            }
        }
        // Check Then-else duplicate

       
        for (int i = 0; i < totalRows; i++){
            if (table[i][2] == table[i][3] && table[i][2] != -1){
                // go through every node in the previous table

                for (int j = 0; j <= i; j++){
                    if (table[j][2] == i){
                        table[j][2] = table[i][2];
                        cout << " ElseThen Move: " << i << "&" << j;
                    }
                    if (table[j][3] == i){
                        table[j][3] = table[i][2];
                        cout << " ElseThen Move: " << i << "&" << j;
                    }
                }

                table[i][2] = -1;
                table[i][3] = -1;
                
                checkTable(table, totalRows);
            }
        }


        if (duplicateRow == 0 && duplicateThenElse == 1){
            notReduced = false;
        }

    }

    checkTable(table, totalRows);

    
    std::ofstream outfile (argv[2]);

    // output part 1 
    outfile << "digraph ROBDD{" << endl;
 
    string thisLevel = ""; 
    for (int i = 0; i < totalRows; i++){
        if (table[i][2] != -1){
            string s = to_string(table[i][0]);
            thisLevel = thisLevel + " " + s;
            
        }
        if (i == 1 || i == 3 || i == 7 || i == 15 || i == 31){
            if (thisLevel != ""){
                outfile << "{rank=same" << thisLevel << "}" << endl;
                thisLevel = "";
            }
        }
    }

    outfile << endl;

    // output part 2
    outfile << "0 [label=0, shape=box]" << endl;;
    for (int i = 0; i < totalRows; i++){
        if (table[i][2] != -1){
            outfile << i << " [label=\"" << (char)table[i][1] << "\"]" << endl;
        }
    }
    outfile << totalRows << " [label=1, shape=box]" << endl;

    outfile << endl;

    // output part 3
    for (int i = 0; i < totalRows; i++){
        if (table[i][2] != -1){
            outfile << i << " -> " << table[i][2] << " [label=\"0\", style=dotted]" << endl;
            outfile << i << " -> " << table[i][3] << " [label=\"1\", style=solid]" << endl;
        }
    }

    outfile << "}" << endl;

    outfile.close();
    return 0;
}