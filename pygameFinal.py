
import serial
ser = serial.Serial("/dev/ttyUSB0",9600)
print(ser.name)


#while(True):
#    command = input("Serial input")
#    command = command.strip()
#    command = command + "\n"
#    command = command.encode()
#    print(command)
#    ser.write(command)

#ser.close()

from random import randint
#print(randint(0,2))
doorWithPrize = randint(0,2)
print("door with Prize: " + str(doorWithPrize))

pickedDoor = 0
wouldSwitchTo = 0

state = 0


while(True):
    if(state == 0):
        print("Please Enter Start")
        command = input("")
        if(command == "start"):
            #print("you are going left")
            state = 1
            command = command.strip() + "\n"
            command = command.encode()
            ser.write(command)
        #elif(command == "right"):
            #print("you are going right")
            #state = 2
        else:
            print("Wrong input")
            state = 0
    if(state == 1):
        print("Pick a door: 0, 1, or 2")
        command = input("")
        if(command == "0"):
            message = "0" + "\n"
            message = message.encode()
            ser.write(message)
            print("you picked 0")
            pickedDoor = 0
            if(pickedDoor == doorWithPrize):
             print("prize is not in door 1!")
             wouldSwitchTo = 2
            else:
             if(doorWithPrize == 1):
              print("prize is not in door 2!")
              wouldSwitchTo = 1
             if(doorWithPrize == 2):
              print("prize is not in door 1!")
              wouldSwitchTo = 2
            state = 2
        elif(command == "1"):
            print("you picked 1")
            pickedDoor = 1
            if(pickedDoor == doorWithPrize):
             print("prize is not in door 2!")
             wouldSwitchTo = 0
            else:
             if(doorWithPrize == 0):
              print("prize is not in door 2!")
              wouldSwitchTo = 0
             if(doorWithPrize == 2):
              print("prize is not in door 0!")
              wouldSwitchTo = 2
            state = 2
        elif(command == "2"):
            print("you picked 2")
            pickedDoor = 2
            if(pickedDoor == doorWithPrize):
             print("prize is not in door 0!")
             wouldSwitchTo = 1
            else:
             if(doorWithPrize == 0):
              print("prize is not in door 1!")
              wouldSwitchTo = 0
             if(doorWithPrize == 1):
              print("prize is not in door 0!")
              wouldSwitchTo = 1
            state = 2
        else:
            print("Wrong input")
            state = 1

    if(state == 2):
        print("Do you want to switch? Y/N")
        command = input("")
        if(command == "Y"):
         if(wouldSwitchTo == doorWithPrize):
          result = "win"
          result = result.strip() + "\n"
          result = result.encode()
          ser.write(result)
          print("You Win! Thank you for playing!")
         else:
          result = "lose"
          result = result.strip() + "\n"
          result = result.encode()
          ser.write(result)
          print("You Lose! Thank you for playing!")
        elif(command == "N"):
         if(pickedDoor == doorWithPrize):
          result = "win"
          result = result.strip() + "\n"
          result = result.encode()
          ser.write(result)
          print("You Win! Thank you for playing!")
         else:
          result = "lose"
          result = result.strip() + "\n"
          result = result.encode()
          ser.write(result)
          print("You Lose! Thank you for playing!")
        else:
            print("Wrong input")
            state = 2
        break


#print("Thank you for playing")
