
# if you dont specify the particular function that you are going to get from the libary then you need to add before each call
# of the function (name of the libary).name of the function
try:
    x = input("x: ")
except:
    print("That is not an int!")
    exit()
try:
    y = cs50.get_int("y: ")
except:
    print("That is not an int!")
    exit()
print(x+y)
