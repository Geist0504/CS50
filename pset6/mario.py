import cs50

while True:
   height = cs50.get_int()
   if height > 0 and height < 24:
       break
   #print ("Invalid, please enter number greater than, but less than 23")

blocks = 2
spaces = height - 1

for n in range(height):
    print (" " * spaces, end = "")
    print ("#" * blocks, end = "")
    print()
    spaces-=1
    blocks +=1

    