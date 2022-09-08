def main():
    n = get_int()
    build(n)

def get_int():
    height = int(input("Enter the height of the pyramid (between 1 and 8: "))
    if 1 <= height <= 8:
        return height
    else:
        return get_int()

def build(n):
    for i in range(1, n+1):
        print(" " * (n - i) + i * "#" + "  " + i * "#")


if __name__ == "__main__":
    main()