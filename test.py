from sys import getsizeof, argv, exit
from PIL import Image, ImageFilter
import csv, os

def main():

    name = input("What's your name? ")

    if len(argv) == 2:
        name = argv[1]
    else:
        print("Missing argument")
        exit(1)

    for i in range(10):
        print(f"Hello, {name}!")

    lista = [i for i in range(50, 0, -2)]
    print(lista)

    types = [1, 'r', "proba", 2.0, True]

    for i in types:
        print(type(i), id(i))
        print(f"Size of the list is {getsizeof(types)} bytes.")

    marloop(3)

    marrec(6)

    with open("data.csv", "a") as db:
        writer = csv.writer(db)
        writer.writerow(["Oblo", "Oblić"])
        writer.writerow(["Kocko", "Kockić"])
        writer.writerow(["Šećo", "Šećić"])

    with open("data.csv", "r") as db:
        for line in csv.reader(db):
            print(line)

    os.system("ls -l")

    """
    before = Image.open("yard.bmp")
    after = before.filter(ImageFilter.BoxBlur(1))
    after.save("out.bmp")

    dict = set()
    with open("dictionary.txt", "r") as f:
        for line in f.readlines():
            print(line)
            dict.add(line.strip())

    print(dict)
    """

def marloop(n):
    for i in range(1, n+1):
        print((n-i) * " " + 2 * (i * "#") + (n-i) * " ")

def marrec(n):
    if n == 1:
        print("#")
    else:
        marrec(n-1)
        print("#" * n)

if __name__ == "__main__":
    main()
