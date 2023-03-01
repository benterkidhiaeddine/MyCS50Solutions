class person():
    #defining the constructor function
    def __init__(self , first_name , last_name , age , gender):
        self.first_name=first_name
        self.last_name=last_name
        self.age=age
        self.gender=gender

    #defining a setter for person class for age

    def setAge (self , age):
        self.age = age

    #defining a function that prints the age of the person

    def printAge (self):
        print(f"The age of {self.first_name} is {self.age}")


def main():
     dhia = person("dhia","benterki","24","male")
     dhia.printAge()

if __name__ == "__main__":
    main()

