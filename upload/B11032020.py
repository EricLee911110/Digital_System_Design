import sys

input_kiss_name = sys.argv[1]
output_kiss_name = sys.argv[2]
output_dot_name = sys.argv[3]

f = open(f'{input_kiss_name}', 'r')

# dealing with inputs
f.readline()
num_input = int(f.readline().split(' ')[1])
num_output = int(f.readline().split(' ')[1])
num_term = int(f.readline().split(' ')[1])
num_state = int(f.readline().split(' ')[1])
init_state = f.readline().split(' ')[1].replace("\n", "")


input_terms = []
for i in range(0, num_term):
    input_terms.append(f.readline().replace("  ", " ").replace("\n", ""))

end_kiss = f.readline()
f.close()
#print(end_kiss)

def twoToPower(num):
    result = 1
    for i in range(0, num):
        result *= 2

    return result

def stateToNum(state, states):
    for i in range(0, len(states)):
        if state == states[i]:
            return i
    return None

def binToDecimal(num):
    return int(num, 2)

def allgray(matrix):
    for row in range(len(matrix)):
        for col in range(len(matrix)):
            if matrix[row][col] != [-1] and matrix[row][col] != [0]:
                return False
    return True

def findFirstTwo(implication_table):
        combine1 = -1
        combine2 = -1
        for i in range(num_state):
            for j in range(num_state):
                if i < j:
                    if implication_table[i][j] != [0] and implication_table[i][j] != [-1]:
                        combine1 = i
                        combine2 = j
                        return combine1, combine2

        #print('can not find one')
        return -1, -1



# get number-state table
states = []
for i in range(0, num_term):
    value = input_terms[i].split(' ')[1]
    if value not in states:
        states.append(value)



#print(states)

# state_transition table
state_transition = []
for i in range(0, len(states)):
    state_transition.append([])

for i in range(0, num_term):
    start_input = input_terms[i].split(' ')[0]
    start_state = input_terms[i].split(' ')[1]
    end_state = input_terms[i].split(' ')[2]
    end_output = input_terms[i].split(' ')[3]

    state_transition[stateToNum(start_state, states)].append([end_state, end_output])

#print(state_transition)

# generate output pair
possible_output = []
if num_input == 1:
    possible_output = ['0-0', '0-1', '1-0', '1-1']
if num_input == 2:
    possible_output = ['0-0-0-0', '0-0-0-1', '0-0-1-0', '0-0-1-1', '0-1-0-0', '0-1-0-1', '0-1-1-0', '0-1-1-1', '1-0-0-0', '1-0-0-1', '1-0-1-0', '1-0-1-1', '1-1-0-0', '1-1-0-1', '1-1-1-0', '1-1-1-1']

# for each possible pair of output. If performed any minimize operation, then we will do it all over again.
state_transition_got_changed = True
while(state_transition_got_changed):
    state_transition_got_changed = False
    for output_idx in range(len(possible_output)):
        output = possible_output[output_idx]
        #print('output: ', output)
        # build init implication table
        implication_table = [[[] for _ in range(num_state)] for _ in range(num_state)]

        for i in range(num_state):
            for j in range(num_state):
                if i >= j:
                    implication_table[i][j].append(0)
                else:
                    if state_transition[i][0][0] == -1 or state_transition[j][0][0] == -1:
                        implication_table[i][j].append(0)
                    else:
                        for ii in range(twoToPower(num_input)):
                            implication_table[i][j].append(f'{state_transition[j][ii][0]}-{state_transition[i][ii][0]}')
                
        # find incompatible end_output
        incomp_states = []
        for i in range(len(state_transition)):
            for ii in range(twoToPower(num_input)):
                if (state_transition[i][ii][1] != output.split('-')[ii]):
                    current_state = states[i]
                    if current_state not in incomp_states:
                        incomp_states.append(current_state)
        
        #print("incomp_state: \n", incomp_states)

        # delete incompatible by observing end_output
        #print("before: ")
        #print(implication_table)
        
        for i in range(len(incomp_states)):
            incomp_state_idx = stateToNum(incomp_states[i], states)
            for ii in range(len(implication_table)):
                # delete row
                implication_table[incomp_state_idx][ii] = [-1]
                # delete col
                implication_table[ii][incomp_state_idx] = [-1]
        #print("after: ")
        #print(implication_table)

        while(not allgray(implication_table)):
            # delete incompatible by gray area (in a while loop)
            turn_gray = True
            while turn_gray:
                #print("round turn gray")
                turn_gray = False
                for row in range(len(implication_table)):
                    for col in range(len(implication_table)):
                        if implication_table[row][col][0] != 0 and implication_table[row][col][0] != -1:
                            for i in range(twoToPower(num_input)):

                                state1 = implication_table[row][col][i].split('-')[0]
                                state2 = implication_table[row][col][i].split('-')[1]
                                
                                # let the later state in alphabetical order be the second one, that how we store information in our upper triangle
                                if stateToNum(state1, states) > stateToNum(state2, states):
                                    temp = state1
                                    state1 = state2
                                    state2 = temp
                                #print(state1)
                                #print(state2)
                                # check wether the state is gray. If it gray, then turn it to gray
                                if implication_table[stateToNum(state1, states)][stateToNum(state2, states)][0] == -1 or implication_table[stateToNum(state1, states)][stateToNum(state2, states)][0] == 0:
                                    if state1 != state2:
                                        implication_table[row][col] = [-1]
                                        ##print("turn gray")
                                        turn_gray = True
                                        break


            # find the first two that can combine, it returns index of each state
            combine1, combine2 = findFirstTwo(implication_table)
            #print("combine1: ", combine1)
            #print("combine2: ", combine2)

            if combine1 != -1:
                #print("minimize")
                state_transition_got_changed = True
                
                # update state_transition table
                #print("before: ")
                #print(state_transition)
                for i in range(twoToPower(num_input)):
                    if num_input == 1:
                        state_transition[combine2][i] = [-1, -1]
                    if num_input == 2:
                        state_transition[combine2][i] = [-1, -1, -1, -1]
                # change others contain the state being removed
                for i in range(len(state_transition)):
                    if state_transition[i][0][0] == states[combine2]:
                        state_transition[i][0][0] = states[combine1]
                    if state_transition[i][1][0] == states[combine2]:
                        state_transition[i][1][0] = states[combine1]
                    if num_input == 2:
                        if state_transition[i][2][0] == states[combine2]:
                            state_transition[i][2][0] = states[combine1]
                        if state_transition[i][3][0] == states[combine2]:
                            state_transition[i][3][0] = states[combine1]
                        

                #print("after: ")
                #print(state_transition)

                # update the the implication table
                # paint a cross
                for row in range(len(implication_table)):
                    for col in range(len(implication_table)):
                        if row == combine2 or col == combine2:
                            implication_table[row][col] = [0]
                
                for row in range(len(implication_table)):
                    for col in range(len(implication_table)):
                        if implication_table[row][col] != [0] and implication_table[row][col] != [-1]:
                            for i in range(twoToPower(num_input)):
                                if states[combine2] in implication_table[row][col][i]:
                                    implication_table[row][col][i] = implication_table[row][col][i].replace(states[combine2], states[combine1])

                #print("after replacemen:")
                #print(implication_table)
            #print("round end")
            # return back to deletion by gray area

#print("state_transition: ")
#print(state_transition)
#print(implication_table)

num_output_term = 0
for i in range(len(state_transition)):
    for ii in range(len(state_transition[i])):
        if -1 not in state_transition[i][ii]:
            num_output_term += 1

num_output_state = int(num_output_term / twoToPower(num_input))
if num_input == 1:
    input_cycle = ["0","1"]
if num_input == 2:
    input_cycle = ["00", "01", "10", "11"]

#print(input_kiss_name)
#print(output_kiss_name)
#print(output_dot_name)
# generate output kiss file
f = open(output_kiss_name, 'w')
f.write(".start_kiss\n")
f.write(f'.i {num_input}\n')
f.write(f'.o {num_output}\n')
f.write(f'.p {num_output_term}\n')
f.write(f'.s {num_output_state}\n')
f.write(f'.r {init_state}\n')
for i in range(len(state_transition)):
    for ii in range(len(state_transition[i])):
        if state_transition[i][ii][0] == -1:
            break
        f.write(f'{input_cycle[ii]} {states[i]} {state_transition[i][ii][0]} {state_transition[i][ii][1]}\n')
f.write(".end_kiss")
f.close()

# generate output dot file
f = open(output_dot_name, "w")
f.write("digraph STG{\n")
f.write("   rankdir=LR;\n")
f.write("\n")
f.write("   INIT [shape=point];\n")
for i in range(len(state_transition)):
    if state_transition[i][0][0] != -1:
        f.write(f'   {states[i]} [label="{states[i]}"];\n')
f.write("\n")
f.write(f'   INIT -> {init_state};\n')


for i in range(len(state_transition)):
    each_state = []
    combine_state_idx = []
    left_alone_state = []
    for ii in range(len(state_transition[i])):
        if state_transition[i][ii][0] == -1:
            break
        each_state.append(f'{state_transition[i][ii][0]}')
    #print(each_state)

    for ii in range(len(each_state)):
        if each_state[ii] not in left_alone_state:
            left_alone_state.append(each_state[ii])
    #print("left_alone", left_alone_state)

    for ii in range(len(each_state)):
        current_same_state = ""
        current_same_state = current_same_state + str(ii)
        already_inside = False
        for e in combine_state_idx:
            if str(ii) in e:
                already_inside = True
        if (not already_inside):
            for iii in range(ii+1, len(each_state)):
                if each_state[ii] == each_state[iii]:
                    current_same_state = current_same_state + "-" + str(iii)
            combine_state_idx.append(current_same_state)
    #print("combine: ", combine_state_idx)

    for ii in range(len(combine_state_idx)):
        f.write(f'   {states[i]} -> {state_transition[i][int(combine_state_idx[ii].split("-")[0])][0]} [label="')
        for iii in range(len(combine_state_idx[ii].split('-'))):
            state_index = int(combine_state_idx[ii].split("-")[iii])
            if iii > 0:
                f.write(",")
            f.write(f'{input_cycle[state_index]}/{state_transition[i][state_index][1]}')
            
        f.write("\"];\n")
                        
    
f.write('}')