import matplotlib.pyplot as plt


#-----RZ Unipolar encoding---------------------------------------------------------------
def rz_unipolar(bits, voltage):

    time = [0]
    signal = [0]

    t = 0

    for bit in bits:


      if bit == '1':
        time.append(t)
        signal.append(voltage)
        time.extend([t, t + 0.5])
        signal.extend([voltage, voltage])

        time.extend([t + 0.5, t + 1])
        signal.extend([0, 0])

      else:
        time.append(t)
        signal.append(0)
        time.extend([t, t + 1])
        signal.extend([0, 0])

      t += 1

  
    plt.plot(time, signal,color='black')
    plt.title("RZ Unipolar Encoding")
    plt.xlabel("Time")
    plt.ylabel("Voltage")
    plt.grid(True)
    plt.axhline(0, color='green') 
    plt.axvline(0, color='green')
    plt.show()
    
#-----------------------------------------------------------------------------------------

#-----NRZ-L encoding----------------------------------------------------------------------
def nrz_l(bits, voltage):

    time = [0]
    signal = []


    first_level = voltage if bits[0] == '1' else -voltage
    signal.append(first_level)

    t = 0

    for bit in bits:

        level = voltage if bit == '1' else -voltage

        time.append(t)
        signal.append(level)

        time.append(t + 1)
        signal.append(level)

        t += 1

    plt.plot(time, signal,color='black')
    plt.title("NRZ-L Encoding")
    plt.xlabel("Time")
    plt.ylabel("Voltage")
    plt.grid(True)
    plt.axhline(0, color='green') 
    plt.axvline(0, color='green')
    plt.show()
#-----------------------------------------------------------------------------------------


#-----NRZ-I encoding----------------------------------------------------------------------
def nrz_i(bits, voltage):

    time = [0]
    signal = []

    t = 0
    level = -voltage

    signal.append(level)

    for bit in bits:

        if bit == '1':
            level = voltage if level == -voltage else -voltage

        time.append(t)
        signal.append(level)

        time.append(t + 1)
        signal.append(level)

        t += 1

    plt.plot(time, signal,color='black')
    plt.title("NRZ-I Encoding")
    plt.xlabel("Time")
    plt.ylabel("Voltage")
    plt.grid(True)
    plt.axhline(0, color='green') 
    plt.axvline(0, color='green')
    plt.show()
#-----------------------------------------------------------------------------------------


#-----Manchester encoding-----------------------------------------------------------------
def manchester(bits, voltage):

    time = [0]
    signal = []

    t = 0

    first_level = -voltage if bits[0] == '1' else voltage
    signal.append(first_level)

    for bit in bits:

        if bit == '1':
            first = -voltage
            second = voltage
        else:
            first = voltage
            second = -voltage

        time.append(t)
        signal.append(first)

        time.append(t + 0.5)
        signal.append(first)

        time.append(t + 0.5)
        signal.append(second)

        time.append(t + 1)
        signal.append(second)

        t += 1

    plt.plot(time, signal,color='black')
    plt.title("Manchester Encoding")
    plt.xlabel("Time")
    plt.ylabel("Voltage")
    plt.grid(True)
    plt.axhline(0, color='green') 
    plt.axvline(0, color='green')
    plt.show()
#-----------------------------------------------------------------------------------------


#-----Differential Manchester encoding----------------------------------------------------
def differential_manchester(bits, voltage):

    time = [0]
    signal = []

    t = 0
    level = -voltage

    signal.append(level)

    for bit in bits:

        if bit == '0':
            level = voltage if level == -voltage else -voltage

        time.append(t)
        signal.append(level)

        time.append(t + 0.5)
        signal.append(level)

        level = voltage if level == -voltage else -voltage

        time.append(t + 0.5)
        signal.append(level)

        time.append(t + 1)
        signal.append(level)

        t += 1

    plt.plot(time, signal,color='black')
    plt.title("Differential Manchester Encoding")
    plt.xlabel("Time")
    plt.ylabel("Voltage")
    plt.grid(True)
    plt.axhline(0, color='green') 
    plt.axvline(0, color='green')
    plt.show()
#-----------------------------------------------------------------------------------------


#-----AMI encoding------------------------------------------------------------------------
def ami(bits, voltage):

    time = [0]
    signal = [0]

    t = 0
    last = -voltage

    for bit in bits:

        if bit == '1':
            last = voltage if last == -voltage else -voltage
            level = last
        else:
            level = 0

        time.append(t)
        signal.append(level)

        time.append(t + 1)
        signal.append(level)

        t += 1

    plt.plot(time, signal,color='black')
    plt.title("AMI Encoding")
    plt.xlabel("Time")
    plt.ylabel("Voltage")
    plt.grid(True)
    plt.axhline(0, color='green') 
    plt.axvline(0, color='green')
    plt.show()
#-----------------------------------------------------------------------------------------


#-----Pseudoternary encoding---------------------------------------------------------------
def pseudoternary(bits, voltage):

    time = [0]
    signal = [0]

    t = 0
    last = -voltage

    for bit in bits:

        if bit == '0':
            last = voltage if last == -voltage else -voltage
            level = last
        else:
            level = 0

        time.append(t)
        signal.append(level)

        time.append(t + 1)
        signal.append(level)

        t += 1

    plt.plot(time, signal,color='black')
    plt.title("Pseudoternary Encoding")
    plt.xlabel("Time")
    plt.ylabel("Voltage")
    plt.grid(True)
    plt.axhline(0, color='green') 
    plt.axvline(0, color='green')
    plt.show()
#-----------------------------------------------------------------------------------------


#-------INPUT-------------------------------------------------------------------------------
bits = input("Enter Data Bit: ")
voltage = float(input("Enter Voltage: "))

while True:
    print("\n=== Data Encoding Menu ===")
    print("1. RZ Unipolar")
    print("2. NRZ-L")
    print("3. NRZ-I")
    print("4. Manchester")
    print("5. Differential Manchester")
    print("6. AMI")
    print("7. Pseudoternary")
    print("8. Exit")
    
    choice = input("Enter your choice (1-8): ")
    
    if choice == '1':
        rz_unipolar(bits, voltage)
    elif choice == '2':
        nrz_l(bits, voltage)
    elif choice == '3':
        nrz_i(bits, voltage)
    elif choice == '4':
        manchester(bits, voltage)
    elif choice == '5':
        differential_manchester(bits, voltage)
    elif choice == '6':
        ami(bits, voltage)
    elif choice == '7':
        pseudoternary(bits, voltage)
    elif choice == '8':
        break
    else:
        print("Invalid choice. Please try again.")


#--------------------------END--------------------------------------------