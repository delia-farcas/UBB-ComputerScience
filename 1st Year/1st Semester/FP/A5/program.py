#
# Write the implementation for A5 in this file
#
import random
import math
# 
# Write below this comment 
# Functions to deal with complex numbers -- list representation
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#

def get_real_list(number):
    return number[0]

def get_img_list(number):
    return number[1]

def generate_list():
    """
    function that generates a list of complex numbers in the form of lists
    """
    data = []
    for i in range (9):
        nr = [random.randint(-100, 100), random.randint(-100, 100)]
        data.append(nr)
    return data

def to_str_list(list):
    """
    function that creates a complex number
    list: a complex number in the form of a list([a, b])
    return: a complex number in the form a + bi
    """
    return str(get_real_list(list))+ " + " + str(get_img_list(list)) + "i"

def display_numbers_list(list, a, b):
    complex = []
    for i in range(a, b+1):
        complex.append(to_str_list(list[i]))
    return complex

def create_number_list(list, a, b):
    """
    function that creates a number in the form of a list
    """
    return [a, b]
#
# Write below this comment 
# Functions to deal with complex numbers -- dict representation
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#

def get_real_dict(number):
    return number["real"]
    
def get_img_dict(number):
    return number["img"]

def generate_dict():
    '''
    function that generates a list of complex numbers in the form of dictionaries
    '''
    data = []
    for i in range (9):
        nr = {
            "real": random.randint(-100, 100),
            "img" : random.randint(-100, 100)
        }
        data.append(nr)
    return data

def to_str_dict(dict):
    """
     function that creates s complex number
     a: int
     b: int
     return: the complex number in the form a + bi
   """
    return str(get_real_dict(dict)) + " + " + str(get_img_dict(dict)) + "i"

def display_numbers_dict(list):
    complex = []
    for i in list:
         complex.append(to_str_dict(i))
    return complex

def create_number_dict(a, b):
    """
    function that creates a number in the form of a dict
    """
    return {
        "real": a,
        "img": b
    }

#
# Write below this comment 
# Functions that deal with subarray/subsequence properties
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#

#NAIVE IMPLEMENTATION

def list_of_real(list):
    arr = []
    for i in list:
        #arr.append(get_real_list(i))
        arr.append(get_real_dict(i))
    return arr
        
def is_mountain(arr, start, end):
    """
    function that checks if there is a strictly increasing part followed by a strictly decreasing part
    return: False if no peak was found
            True if it is mountain
    """
    
    peak_found = False
   
    for i in range(start, end):
        if arr[i] < arr[i + 1]:
            continue
        elif arr[i] > arr[i + 1]:  # Peak found
            peak_found = True
            break
        else:  
            return False
    
    if not peak_found:
        return False
    
    for j in range(i, end):
        if arr[j] > arr[j + 1]:
            continue
        else:  
            return False

    return True

def longest_mountain_naive(list):
    """
    function that determine the longest subarray of numbers where their real part is in the form of a mountain
    int: list of complex numbers
    return: the length of the list and the indices where it starts and it ends

    """
    arr = list_of_real(list)

    n = len(arr)
    longest = 0
    longest_start = 0
    longest_end = 0
   
    for start in range(n - 2):  
        for end in range(start + 2, n):
            if is_mountain(arr, start, end):
               if longest < end - start + 1:
                   longest = end - start + 1
                   longest_start = start
                   longest_end = end


    return longest, longest_start, longest_end

def test_mountain(longest_start, longest_end, list):
    arr = list_of_real(list)
    maxi = arr[longest_end]
    for i in range(longest_start, longest_end):
        maxi = max(maxi, arr[i])
    pmax = arr.index(maxi)
    for i in range(longest_start, pmax):
        assert arr[i] < arr[i+1], 'Subarray is not a mountain'
    for i in range(pmax, longest_end):
        assert arr[i] > arr[i+1], 'Subarray is not a mountain'
    


#DYNAMIC IMPLEMENTATION

def list_of_modulus(list):
    arr = []
    for i in list:
        #a = get_real_list(i)
        a = get_real_dict(i)
        #b = get_img_lis(i)
        b = get_img_dict(i)
        arr.append(math.sqrt(a*a + b*b))
    return arr


def lis_modulus(list):
    """
    function that determine a longest increasing subsequence, when considering each number's modulus.
    return: the length of the list and the indices of the numbers in the subsequence
    """
    arr = list_of_modulus(list)

    dp = [1] * len(arr)
    previous = [-1] * len(arr)  
 
    for i in range(1, len(arr)):
        for j in range(i):
            if arr[i] > arr[j] and dp[i] < dp[j] + 1:
                dp[i] = dp[j] + 1
                previous[i] = j 
    
    max_length = max(dp)
    max_index = dp.index(max_length)

    lis_indices = []
    while max_index != -1:
        lis_indices.append(max_index)
        max_index = previous[max_index]

    lis_indices.reverse() 

    return max_length, lis_indices

#
# Write below this comment 
# UI section
# Write all functions that have input or print statements here
# Ideally, this section should not contain any calculations relevant to program functionalities
#

def append_to_list(list):
 while True:
    try:
     print("Introduce how many numbers to add")
     n = int(input("->"))
     for i in range (n):
         a = int(input("real part->"))
         b = int(input("imaginary part->"))
         #list.append(create_number_list(a, b))
         list.append(create_number_dict(a, b))
     break
    except ValueError:
        print("Introduce a real number")

def mountain(list):
    max, a, b = longest_mountain_naive(list)
    #mountain_secv = display_numbers_list(list, a, b)
    mountain_secv = []
    for i in range (a, b+1):
         mountain_secv.append(to_str_dict(list[i])) 
    test_mountain(a, b+1, list)
    print(max)
    print(mountain_secv)
   
def lis(list):
    max, indices = lis_modulus(list)
    complex = []
    for i in indices:
        #complex.append(to_str_list(list))
        complex.append(to_str_dict(list[i]))
    print(max)
    print(complex)

def display(list):
    #print(display_numbers_list(list))
    print(display_numbers_dict(list))

def display_menu():
    """
      function that displays the menu on the console
    """
    print("1. Add numbers to list")
    print("2. Display list of complex numbers")
    print("3. A longest subarray of numbers where their real part is in the form of a mountain ")
    print("4. The longest increasing subsequence, when considering each number's modulus")
    print("0. Exit")

def create_menu():
    menu = {
        "1" : append_to_list,
        "2": display,
        "3" : mountain,
        "4" : lis


    }
    return menu

def main():
    #lst = generate_list()
    lst = generate_dict()
    #print(display_numbers_list(lst))
    print(display_numbers_dict(lst))
    menu = create_menu()
    while True:
          display_menu()
          command = input(">")
          if(command == "0"): #"0" is the command which exits the program
            return
          elif command in menu:
              menu[command](lst)
          else: 
                print("Bad command, please try again")
        
    
main()