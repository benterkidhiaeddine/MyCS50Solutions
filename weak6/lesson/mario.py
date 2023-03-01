from cs50 import get_int


def main ():
    height = get_height()
    for i in range (height):
        print(" "*(height-(i+1)) + "#"*(i+1) + " " + "#"*(i+1))


def get_height():
    while True:
        try:
            n = get_int("Height: ")
            if n > 0:
                break
        except ValueError:
            print("That is not an int!")
    return n

main()