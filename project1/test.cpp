#include <iostream>
#include <fstream>

using namespace std;

int powerFunction(int howManyTimes){
    int result = 1;
    for (int i = 0; i < howManyTimes; i++){
        result *= 2;
    }
    
    return result;
}

void checkTable(string** table, int totalRows){
    cout << endl;
    cout << "Table: " << endl;
    for (int i = 1; i < totalRows; i++){
        cout << table[i][0] << " " << table[i][1] << " " << table[i][2] << " " << table[i][3] << endl;
    }
}

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


    // read inputs from file
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
    
    int totalRows = 1;
    for (int i = 0; i < num_inputs; i ++){
        totalRows *= 2;
    }
    cout << totalRows << endl;

    // setup table memory
    string** table = new string*[totalRows];

    for (int i = 0; i < totalRows; i++){
        table[i] = new string[4];
    }


    // build up filter for each layer
    int* resultFilter = new int[totalRows];
    for(int i = 0; i < totalRows; i++){
        resultFilter[i] = 0;
    }

    for (int i = 0; i < num_conditions; i++){
        int* currentFilter = new int[totalRows];
        cout << "before: " << endl;
        for (int j = 0; j < totalRows; j++){
            currentFilter[j] = 1;
            cout << currentFilter[j];
        }
        cout << endl;

        for (int j = 0; j < num_inputs; j++){
            string indicator = conditions[i].substr(j, 1);
            switch(j){
                
                case 0:{
                    cout << "reach case 0: " << endl;
                    if (indicator == "1"){
                        for (int k = 0; k < totalRows / 2; k++){
                            currentFilter[k] = 0;
                        }
                    }
                    else{
                        for (int k = totalRows /2; k < totalRows; k++){
                            currentFilter[k] = 0;
                        }
                    }
                    break;
                }
                
                
                case 1:{
                    cout << "reach case 1: " << endl;
                    if (indicator == "1"){
                        for (int k = 0; k < totalRows; k++){
                            if ((k % (totalRows / 2)) >= (totalRows / 4)){
                                currentFilter[k] = 0;
                            }
                        }
                    }
                    else{
                        for (int k = 0; k < totalRows; k++){
                            if ((k % (totalRows / 2)) < (totalRows / 4)){
                                currentFilter[k] = 0;
                            }
                        }
                    }
                    break;
                }

                case 2:{
                    cout << "reach case 2: " << endl;
                    if (indicator == "1"){
                        for (int k = 0; k < totalRows; k++){
                            if ((k % (totalRows / 4)) >= (totalRows / 8)){
                                currentFilter[k] = 0;
                            }
                        }
                    }
                    else{
                        for (int k = 0; k < totalRows; k++){
                            if ((k % (totalRows / 4)) < (totalRows / 8)){
                                currentFilter[k] = 0;
                            }
                        }
                    }
                    break;
                }

                case 3:{
                    cout << "reach case 3: " << endl;
                    if (indicator == "1"){
                        for (int k = 0; k < totalRows; k++){
                            if ((k % (totalRows / 8)) >= (totalRows / 16)){
                                currentFilter[k] = 0;
                            }
                        }
                    }
                    else{
                        for (int k = 0; k < totalRows; k++){
                            if ((k % (totalRows / 8)) < (totalRows / 16)){
                                currentFilter[k] = 0;
                            }
                        }
                    }
                    break;
                }

                case 4:{
                    cout << "reach case 2: " << endl;
                    if (indicator == "1"){
                        for (int k = 0; k < totalRows; k++){
                            if ((k % (totalRows / 16)) >= (totalRows / 32)){
                                currentFilter[k] = 0;
                            }
                        }
                    }
                    else{
                        for (int k = 0; k < totalRows; k++){
                            if ((k % (totalRows / 16)) < (totalRows / 32)){
                                currentFilter[k] = 0;
                            }
                        }
                    }
                    break;
                }

            }
        }

        cout << "after: " << endl;
        for (int j = 0; j < totalRows; j++){
            cout << currentFilter[j];
            if (currentFilter[j] == 1){
                resultFilter[j] = 1;
            }
        }
        cout << endl;

    }

    cout << "resultFilter: " << endl; 
    for (int i = 0; i < totalRows; i++){
        cout << resultFilter[i];
    }    
    cout << endl;


    // Fill in all the values in table

    int thresh = 1;
    int idx_filter = 0;
    for (int i = 1; i < totalRows; i++){
        table[i][0] = to_string(i);
        if (i == powerFunction(thresh)){
            thresh += 1;
        }
        table[i][1] = symbols[thresh - 1];
        if (i > (totalRows / 2)  -1){
            table[i][2] = to_string(resultFilter[idx_filter] == 1 ? totalRows : 0);
            idx_filter++;
            table[i][3] = to_string(resultFilter[idx_filter] == 1 ? totalRows : 0);
            idx_filter++;
        }
        else{
            table[i][2] = to_string(i * 2);
            table[i][3] = to_string((i * 2) + 1);        
        }
    }
    checkTable(table, totalRows);

    // Reduce the table
    bool notReducedForm = true;
    while (notReducedForm){
        notReducedForm = false;
        cout << "Duplicate detection" << endl;

        // Row identical
        for (int i = 1; i < totalRows; i++){
            for (int j = i + 1; j < totalRows; j++){
                if (table[i][1] == table[j][1] && table[i][2] == table[j][2] && table[i][3] == table[j][3] && table[i][2] != "-1"){
                    table[j][2] = "-1";
                    table[j][3] = "-1";
                    cout << i << " " << j << endl;
                    
                    if (j % 2 == 0){
                        table[j/2][2] = to_string(i);
                    }
                    else{
                        table[j/2][3] = to_string(i);
                    }
                    if(j/2 == 5){
                        cout << "Here is the problem" << endl;
                        checkTable(table, totalRows);
                    }
                    
                    notReducedForm = true;
                }
            }
        }


        
    }
    checkTable(table, totalRows);
    
    notReducedForm = true;
    while (notReducedForm){
        notReducedForm = false;

        // else-then identical
        for (int i = 1; i < totalRows; i++){
            if (table[i][2] == table[i][3] && table[i][2] != "-1"){
                for (int j = 1; j < i; j++){
                    if (table[j][2] == to_string(i)){
                        table[j][2] = table[i][2];
                    }
                    if (table[j][3] == to_string(i)){
                        table[j][3] = table[i][2];
                    }
                }
                
                cout << i << endl;

                table[i][2] = "-1";
                table[i][3] = "-1";
                notReducedForm = true;
            }
        }
    }

    checkTable(table, totalRows);



    // outputFile part 1

    string outputFileName = argv[2];
    ofstream outputFile (outputFileName);
    outputFile << "digraph ROBDD{" << endl;
    string levelGroups[100];
    string currentGroup;
    
    int idx_levelGroups = 0;
    for (int i = 1; i < totalRows + 1; i++){
        if (i == powerFunction(idx_levelGroups)){
                levelGroups[idx_levelGroups] = currentGroup;
                idx_levelGroups += 1;
                currentGroup = "";
                if (i == totalRows){
                    break;
                }
        }
        if (table[i][2] != "-1"){    
            currentGroup = currentGroup + " " + table[i][0];
        }

    }
    for (int i = 1; i < num_inputs + 1; i++){
        cout << i << levelGroups[i] << endl;
        outputFile << "{rank=same" << levelGroups[i] << "}" << endl;;
    }
    outputFile << endl;

    // outputFile part 2
    outputFile << "0 [label=0, shape=box]" << endl;
    for (int i = 1; i < totalRows; i++){
        if (table[i][2] != "-1"){
            outputFile << i << " [label=\"" << table[i][1] << "\"]" << endl;
        }
    }
    outputFile << to_string(totalRows) << " [label=1, shape=box]" << endl;

    outputFile << endl;
    // outputFile part 3
    for (int i = 1; i < totalRows; i++){
        if (table[i][2] != "-1"){
            outputFile << to_string(i) << " -> " << table[i][2] << " [label=\"0\", style=dotted]" << endl;
            outputFile << to_string(i) << " -> " << table[i][3] << " [label=\"1\", style=solid]" << endl;
        }
    }
    outputFile << "}";


    outputFile.close();

}