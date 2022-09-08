def main():
    check_num(get_num())

def check_num(num):
    if 16 < len(str(num)) < 13:
        print("INVALID\n")
    else:
        str_num = str(num)[::-1]
        len_num = len(str_num)
        luhn_str = ''
        luhn_sum = 0
        rest_sum = 0
        for i in range(len_num):
            if (i + 1) % 2 == 0:
                luhn_str += str(int(str_num[i]) * 2)
            else:
                rest_sum += int(str_num[i])
        for i in luhn_str:
            luhn_sum += int(i)
        if (luhn_sum + rest_sum) % 10 == 0:
            if (str(num)[0:2]) in ['34', '37']:
                print("AMEX\n")
            elif (str(num)[0:2]) in ['51', '52', '53', '54', '55']:
                print("MASTERCARD\n")
            elif (str(num)[0]) == '4':
                print("VISA\n")
        else:
            print("INVALID\n")


def get_num():
    num = input("Enter credit card number: ")
    return num

if __name__ == "__main__":
    main()