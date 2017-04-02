import cs50
import sys

key = int(sys.argv[1])
if key >= 26:
    key = key % 26
    
string = cs50.get_string()

for c in string:
    val = ord(c)
    if c.isalpha() or val >19 and val < 48:
        if c.isupper():
            if val + key >=91:
                var = chr(65+ (val+key) % 91)
                print(var, end = "")
            else:
                 print(chr(val + key), end ="")
        elif c.islower():
            if val + key >=123:
                print(chr(97 + (val + key)%123), end = "")
            else:
                print(chr(val+key), end ="")
        else:
            print(chr(val), end = "")
    else:
        break
print()
