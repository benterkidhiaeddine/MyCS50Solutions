from cs50 import get_string
from csv import  writer

name = get_string ("Name: ")
number = get_string ("Number: ")

with open("numbers.csv","a") as file:
    writer = writer(file )
    writer.writerow([name , number])