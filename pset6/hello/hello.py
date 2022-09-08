def main():
    greet(get_name())

def get_name():
    name = input("What is your name?\n")
    return name

def greet(name):
    print(f"Hello, {name}!")

if __name__ == "__main__":
    main()