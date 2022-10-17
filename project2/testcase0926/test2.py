# num_var = 4

# def twoToPower(num):
#     result = 1
#     for i in range(num):
#         result *= 2
#     return result

# def findName(binaryNum):
#     result = 0
#     for i in range(len(binaryNum)):
#         weight = twoToPower(num_var - 1 - i)
#         print("weight: ", weight)
#         if binaryNum[i] == "1":
#             result += weight

#     return result
        

# name = findName("0110")
# print(name)

for i in range(5):
    for ii in range(4):
        if i == 3:
            for iii in range(10):
                print(i, ii, iii)
                if iii == 3:
                    continue