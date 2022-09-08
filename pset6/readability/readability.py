from sys import argv, exit

def main():
    """Implementation with text provided as an argument
    # Check if text is provided.
    if len(argv) != 2:
        print("Please provide a text as an argument.")
        exit()
    """

    # Get counters.
    letters, words, sentences = count(get_text())
    l = letters * (100 / words)
    s = sentences * (100 / words)
    # Get index.
    grade = col(l, s)
    print_result(grade)

# Function for countnig letters, words and sentences.
def count(text):
    letters = 0
    words = 0
    sentences = 0
    for i in text:
        if i.isalpha():
            letters += 1
        elif i == " ":
            words += 1
        elif i in ['.', '!', '?']:
            sentences += 1
        else:
            continue
    words += 1  # Add the last word from text.

    return letters, words, sentences

# Function to calculate Coleman-Liau index.
def col(l, s):
    return round(0.0588 * l - 0.296 * s - 15.8)

# Get text function.
def get_text():
    text = input("Enter text for evaluation: ")
    return text

# Print result function.
def print_result(grade):
    if grade < 1:
        print("Before grade 1")
    elif grade >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")


if __name__ == "__main__":
    main()