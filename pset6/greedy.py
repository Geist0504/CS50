import cs50

while True:
   change = cs50.get_float()
   if change > 0.0:
       break
   else:
       print("Retry: ")

count = 0
while change > 0.0:
    if change >= .25:
        change -=.25
        count +=1
    elif change >=.10:
        change -=.10
        count +=1
    elif change >=.05:
        change -=.05
        count +=1
    else:
        change -=.01
        count +=1
        
print ("{}".format(count))
    