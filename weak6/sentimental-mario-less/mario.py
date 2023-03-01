

#specify the height of the pyramid

# while True:
#     try:
#         height = int (input ("Height: "))
#         if height > 0 and height <= 8:
#             break
#     except:
def main():
    height = int(get_height())


    for i in range (0,height ):
        print (" "* (height-(i+1)) + "#"*(i+1))



def get_height():
    try:
        height = int(input("Height: "))
        if height <= 0 or height >8:
            return get_height()
        else:
            return height
    except:
        return get_height()


if __name__ == "__main__":
    main()
