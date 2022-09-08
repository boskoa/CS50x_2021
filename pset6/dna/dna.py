from sys import argv, exit
import csv

def main():

    # Check if the command is valid.
    if len(argv) != 3:
        print("Invalid number of arguments. Enter: dna.py database.csv sequence.txt")
        exit()
    else:
        with open(argv[1], "r") as db:
            seq = csv.DictReader(db)
            datab = []
            for i in seq:
                datab.append(i)
            chosen_seq = seq.fieldnames[1:]

        # Read the sequence.
        with open(argv[2]) as s:
            sequence = s.read()

        # Count the STR repetitions for which there is data in the database.
        foundSTRs = []
        for i in chosen_seq:
            foundSTRs.append(count_str(i, sequence))

        # Print the persons name if there's a match.
        print(check(foundSTRs, datab))

# Get STR repetitions from the sample.
def count_str(s, seq):
    counter = 0
    tmp_counter = 0
    str_len = len(s)
    i = 0
    while i < len(seq)-str_len:
        if seq[i:i+str_len] == s:
            tmp_counter += 1
            i += str_len
        else:
            if tmp_counter >= counter:
                counter = tmp_counter
                tmp_counter = 0
                i += 1
            else:
                tmp_counter = 0
                i += 1

    return {s: counter}

# Check whose DNA matches the pattern from the sample.
def check(found, persons):
    for j in range(len(persons)):
        cond = False
        for i in found:
            k = ''.join(list(i))
            cond_part = False
            if i[k] == int(persons[j][k]):
                cond_part = True
            else:
                cond_part = False
                break
        cond = cond_part
        if cond:
            return persons[j]['name']
        else:
            continue
    return "No match"


if __name__ == "__main__":
    main()