whichtest = 3

# first testcase
if whichtest == 1:
    inputs = ["00-0 1",
            "0-11 1",
            "1-01 1",
            "0101 1",
            "1111 -",
            "100- 1",
            "-01- 1"
    ]

# second testcase
if whichtest == 2:
    num_var = 5
    inputs = ["00000 -",
            "00011 -",
            "00101 -",
            "00110 1",
            "00111 -",
            "01001 1",
            "01010 -",
            "01011 -",
            "01110 1",
            "01111 1",
            "10100 -",
            "10101 1",
            "10111 1",
            "11000 -",
            "11001 -",
            "11010 1",
            "11101 1",
            "11110 1"
    ]

# third testcase
if whichtest == 3:
    num_var = 6
    inputs = ["001000 1",
            "0-1011 1",
            "1-0101 1",
            "11-100 1",
            "111101 -",
            "1-0111 1",
            "-0111- 1"
    ]
    

import sys

if __name__ == "__main__":

    input_fileName = sys.argv[1]
    output_fileName = sys.argv[2]
    #print(input_fileName)
    #print(output_fileName)

    myfile = open(input_fileName, "r")
    lines = myfile.readlines()
    myfile.close()
    
    num_var = int(lines[0].split(' ')[1])
    #print(num_var)
    num_conditions = int(lines[4].split(' ')[1])
    #print(num_conditions)
    inputs = []
    #print(inputs)
    for i in range(num_conditions):
        inputs.append(lines[5+i].replace("\n", ""))

    #print(inputs)
    
    pre_level = []
    
    dontCare = []

    def twoToPower(num):
        result = 1
        for i in range(num):
            result *= 2
        return result

    def findName(binaryNum):
        result = 0
        for i in range(len(binaryNum)):
            weight = twoToPower(num_var - 1 - i)
            if binaryNum[i] == "1":
                result += weight

        return result

    def whichGroup(num):
        count = 0
        for i in range(len(num)):
            if num[i] == "1":
                count += 1

        return count

    # return "000- m0m1" if ture else false
    def oneBitBinaryComparision(num1, num2):
        diff_count = 0
        idx_dash = -1
        for i in range(len(num1)):
            if num1[i] != num2[i]:
                idx_dash = i
                diff_count += 1

        if diff_count > 1 or num1 == num2:
            return -1
        
        valueAndName = num1[:idx_dash] + "-" + num1[idx_dash + 1:]

        return valueAndName



    # remove dashs inside value
    notDone = True
    while(notDone):
        deleteIndex = []
        for i in range (len(inputs)):
            thisCondition = inputs[i].split(" ")[0]
            thisResult = inputs[i].split(" ")[1]
            for ii in range(num_var):
                if thisCondition[ii] == "-":
                    inputs.append(thisCondition[:ii] + "0" + thisCondition[ii + 1:] + " " + thisResult)
                    inputs.append(thisCondition[:ii] + "1" + thisCondition[ii + 1:] + " " + thisResult)
                    deleteIndex.append(i)
                    break
                    
            else:
                continue # leave the conditions that don't have dash alone

        #print(deleteIndex)
        deleteIndex.reverse()
        for i in range(len(deleteIndex)):
            del inputs[deleteIndex[i]]
        
        notDone = False
        for i in range(len(inputs)):
            thisCondition = inputs[i].split(" ")[0]
            if "-" in thisCondition:
                notDone = True

    #print("inputs: \n", inputs)
    #print("\n")

            

    # convert every inputs into value-name pair. also it is unique.
    for i in range(len(inputs)):
        value = inputs[i].split(" ")[0]
        name = " m" + str(findName(value))
        valueAndName = value + name
        if valueAndName not in pre_level:
            pre_level.append(valueAndName)

        if inputs[i].split(" ")[1] == "-":
            dontCare.append(f'{valueAndName} {i}')

    #print("dontCare: \n" , dontCare)
    #print("\n")
    #print("pre_level: \n", pre_level)
    #print("\n")
        

    # create empty first_level
    levels = []
    num_levels = num_var - 1 # 3
    num_groups = num_var + 1 # 5
    for i in range(num_levels):
        levels.append([])

        for ii in range(num_groups):
            levels[i].append([])


    # Group up with same number of 1's
    for i in range(len(pre_level)):
        value = pre_level[i].split(" ")[0]
        name = pre_level[i].split(" ")[1]
        if pre_level[i] not in levels[0]:
            levels[0][whichGroup(value)].append(value + " " + name)


    #print("levels: \n", levels)
    #print("\n")


    for level in range(num_levels - 1): # don't need to check last level
        for group in range(num_groups -1): # also don't need to check last group
            for e in range(len(levels[level][group])):
                for ee in range(len(levels[level][group + 1])):
                    num1 = levels[level][group][e].split(' ')[0]
                    num1_name = levels[level][group][e].split(' ')[1]
                    num2 = levels[level][group + 1][ee].split(' ')[0]
                    num2_name = levels[level][group + 1][ee].split(' ')[1]
                    
                    # after comparing. If they only difference one digit add to next group
                    result = oneBitBinaryComparision(num1, num2)
                    if result != -1:
                        newName = f'{num1_name}{num2_name}'
                        result = f'{result} {newName}'
                        levels[level + 1][group].append(result)


    #print("after process the levels: \n")
    #print(levels, "\n")

    # look for Prime inlicant that is not in the last layer
    noNextLayer = []
    for level in range(num_levels - 1): # don't need to check last level
        for group in range(num_groups):
            for e in range(len(levels[level][group])):
                noNextLayer.append(levels[level][group][e])

    #print("noNextLayer: \n", noNextLayer, "\n")

    for level in range(num_levels - 1):
        for group in range(num_groups -1):
            for e in range(len(levels[level][group])):
                for ee in range(len(levels[level][group + 1])):
                    num1 = levels[level][group][e].split(' ')[0]
                    num1_and_name = levels[level][group][e]
                    num2 = levels[level][group + 1][ee].split(' ')[0]
                    num2_and_name = levels[level][group + 1][ee]
                    
                    result = oneBitBinaryComparision(num1, num2)
                    if result != -1:
                        if num1_and_name in noNextLayer:
                            delete_index = noNextLayer.index(num1_and_name)
                            noNextLayer.pop(delete_index)

                        if num2_and_name in noNextLayer:
                            delete_index = noNextLayer.index(num2_and_name)
                            noNextLayer.pop(delete_index)


    #print("noNextLayer: \n", noNextLayer, "\n")

    # combine all the PIs
    finalPI = []
    for group in range(num_groups):
        for e in range(len(levels[num_levels - 1][group])):
            finalPI.append(levels[num_levels - 1][group][e])

    for e in range(len(noNextLayer)):
        finalPI.append(noNextLayer[e])

    print("finalPI: \n", finalPI, "\n")


    # delete duplicate
    finalPI_delete_idx = []
    for i in range(len(finalPI)):
        for ii in range(i + 1, len(finalPI)):
            if finalPI[i].split(" ")[0] == finalPI[ii].split(" ")[0] and ii not in finalPI_delete_idx:
                finalPI_delete_idx.append(ii)

    for i in range(len(finalPI_delete_idx) - 1, -1, -1):
        finalPI.pop(finalPI_delete_idx[i])

    print("finalPI delete duplicate: \n", finalPI, "\n")
    # order final PI to big to small order
    sortNotDone = True
    while sortNotDone:

        sortNotDone = False
        start_pointer = 0
        end_pointer = 0
        for i in range(1, len(finalPI)):
            end_pointer = i
            start_pointer_dash_count = 0
            end_pointer_dash_count = 0
            for ii in range(num_var):
                if finalPI[start_pointer][ii] == "-":
                    start_pointer_dash_count += 1
                if finalPI[end_pointer][ii] == "-":
                    end_pointer_dash_count += 1
            
            if end_pointer_dash_count > start_pointer_dash_count:
                sortNotDone = True
                temp = finalPI[start_pointer]
                finalPI[start_pointer] = finalPI[end_pointer]
                finalPI[end_pointer] = temp
                start_pointer += 1

    print("uni_reversed_finalPI: \n", finalPI, "\n")
        
    levels_need_cover = pre_level
    #print("levels_need_cover: \n", levels_need_cover, "\n")

    # create oneHotTable for PI
    def find_idx_m(word):
        idx_m = []
        for i in range(len(word)):
            if word[i] == "m":
                idx_m.append(i)


        return idx_m  

    oneHotTable = []
    for i in range(len(finalPI)):
        oneHotTable.append([])
        idx_m = find_idx_m(finalPI[i])
        # #print(idx_m)
        
        for ii in range(len(idx_m)):
            if ii == len(idx_m) - 1:
                word = finalPI[i][idx_m[ii]:]
            else:    
                word = finalPI[i][idx_m[ii]:idx_m[ii + 1]]
            # #print(word)

            for iii in range(len(levels_need_cover)):
                if ii == 0:
                    if levels_need_cover[iii].split(' ')[1] == word:
                        oneHotTable[i].append(1)
                    else:
                        oneHotTable[i].append(0)

                else:
                    if levels_need_cover[iii].split(' ')[1] == word:
                        oneHotTable[i][iii] = 1

    #print("oneHotTable: \n", oneHotTable, "\n")

    # check sum in column in order to find essential PI
    sum_in_column = []
    for i in range(len(levels_need_cover)):
        sum_in_column.append(0)

    for row in range(len(oneHotTable)):
        for column in range(len(oneHotTable[row])):
            if oneHotTable[row][column] == 1:
                sum_in_column[column] += 1
                
    #print("sum_in_column:\n", sum_in_column, "\n")

    def find_unique_idx(arr):
        unique_idx = []
        for i in range(len(arr)):
            if arr[i] == 1:
                unique_idx.append(i)
        
        return unique_idx

    # return False if the idx is dont care, True if not
    def isNotDontCare(idx, dontCare):
        #print("inside the dontCare function")
        for i in range(len(dontCare)):
            #print(idx, " ", dontCare[i].split(' ')[2])
            if idx == int(dontCare[i].split(' ')[2]):
                return False

        return True

    # return False if not done, True if done
    def checkUseStat(currentStat, dontCare):
        #print("inside checkUseStat function")
        #print("currentStat: \n", currentStat)

        for i in range(len(currentStat)):
            if isNotDontCare(i, dontCare):
                if currentStat[i] == 0:
                    return False

        return True

    useStat = []
    for i in range(len(levels_need_cover)):
        useStat.append(0)

    #print("useStat: ", useStat, " status: ", checkUseStat(useStat, dontCare), "\n")

    rowUsed = []



    # function call start here
    def find_ePI(sum_in_column, useStat, oneHotTable, dontCare, rowUsed):
        unique_idx = find_unique_idx(sum_in_column)
        #print("unique_idx: ", unique_idx)

        if checkUseStat(useStat, dontCare) == True:
            return rowUsed

        # priority 1: there is unique element and it is not dontCare
        first_ePI_row = -1
        for e in range(len(unique_idx)): 
            if isNotDontCare(unique_idx[e], dontCare):
                if useStat[unique_idx[e]] == 0:
                    for row in range(len(oneHotTable)):
                        if row not in rowUsed:            
                            if oneHotTable[row][unique_idx[e]] == 1:    # if sum_in_column's 1 match oneHotTable_row's 1
                                first_ePI_row = row             # got the first ePI
                                rowUsed.append(first_ePI_row)

                                for eee in range(len(oneHotTable[row])):
                                    if oneHotTable[row][eee] == 1:
                                        sum_in_column[eee] -= 1
                                        useStat[eee] = 1

                                print("Priority 1:")
                                print("row pick: ", row)
                                print("oneHotTable: ", oneHotTable)
                                print("NEW sum_in_column: \n", sum_in_column)
                                print("New useStat: \n", useStat, "\n")
                                print("\n")
                                
                                return find_ePI(sum_in_column, useStat, oneHotTable, dontCare, rowUsed)
                                
                                # just return here so the rest are ignored
                                # return new (sum_in_column, useStat, oneHotTable(static), dontCare(static), rowUsed)
            
            

        # priority 2: There is no unique element, dont want dontCare inside, also want largest(maybe try sort the oneHotTable first)
        for row in range(len(oneHotTable)):
                if row not in rowUsed:
                    for e in range(len(oneHotTable[row])):
                        if isNotDontCare(e, dontCare):
                            if oneHotTable[row][e] == 1:
                                if useStat[e] == 0:
                                    first_ePI_row = row
                                    rowUsed.append(first_ePI_row)

                                    # return here
                                    for eee in range(len(oneHotTable[row])):
                                        if oneHotTable[row][eee] == 1:
                                            sum_in_column[eee] -= 1
                                            useStat[eee] = 1

                                    print("Priority 2:")
                                    print("row pick: ", row)
                                    print("oneHotTable: ", oneHotTable)
                                    print("NEW sum_in_column: \n", sum_in_column)
                                    print("New useStat: \n", useStat, "\n")
                                    
                                    return find_ePI(sum_in_column, useStat, oneHotTable, dontCare, rowUsed)


        # priority 3: Just return something that hasn't been used
        for row in range(len(oneHotTable)):
            if row not in rowUsed:
                first_ePI_row = row
                rowUsed.append(first_ePI_row)
                # return here
                for eee in range(len(oneHotTable[row])):
                    if oneHotTable[row][eee] == 1:
                        sum_in_column[eee] -= 1
                        useStat[eee] = 1

                print("Priority 3:")
                print("row pick: ", row)
                print("oneHotTable: ", oneHotTable)
                print("NEW sum_in_column: \n", sum_in_column)
                print("New useStat: \n", useStat, "\n")
                
                return find_ePI(sum_in_column, useStat, oneHotTable, dontCare, rowUsed)


        if checkUseStat(useStat, dontCare) == False:
            #print("Sorry we are unable to find essential PIs")
        
            return -1





    # print("before entering the function", rowUsed)
    rowUsed = find_ePI(sum_in_column, useStat, oneHotTable, dontCare, rowUsed)
    #print("rowUsed: ", rowUsed, "\n")


    literal_count = 0
    for i in range(len(rowUsed)):
        #print(finalPI[rowUsed[i]])
        bi_num = finalPI[rowUsed[i]].split(' ')[0]
        for e in range(len(bi_num)):
            if bi_num[e] != "-":
                literal_count += 1


    # then you output
    print(f"Total number of terms: {len(rowUsed)}")
    print(f"Total number of literals: {literal_count}")
    print("\n")

    output_file = open(output_fileName, "w")
    output_file.write(lines[0])
    output_file.write(lines[1])
    output_file.write(lines[2])
    output_file.write(lines[3])
    output_file.write(f".p {len(rowUsed)}")
    output_file.write("\n")
    for i in range(len(rowUsed)):
        output_file.write(finalPI[rowUsed[i]].split(' ')[0])
        output_file.write(" 1")
        output_file.write("\n")
    output_file.write(".e\n")

    output_file.close()
    