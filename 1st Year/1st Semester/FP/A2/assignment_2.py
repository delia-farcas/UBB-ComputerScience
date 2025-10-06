#we generate a list of n natural numbers between 0 and 1000
def generate_list(arr, n):
    import random
    for i in range(n):
        arr.append(random.randint(0,1000))
    return arr

#we check if the list for binary search is ordonated 
def check_order(arr, n):
   for i in range (n-1):
      if arr[i] > arr[i+1]: #both algorithms are sorting ascending, so in order to verify if the list is sorted
   # we make sure that there is no element bigger than the one that comes after 
         return False
   return True

def binary_search(arr, low, high, element):
   if high >= low:
      m = (low + high) // 2
      if arr[m] == element:
        print("Number found on position", m)
        return True
      elif arr[m] < element:
        return binary_search(arr, m+1, high, element)
      else:
        return binary_search(arr, low, m-1, element)
   else:
      print("Number not found")
      return False
   
def bubble_sort(arr, n , step):
   swap = True 
   nr_steps = 0
   while swap == True:
      swap = False
      for i in range(n-1):
         if arr[i] > arr[i+1]:
            swap = True
            arr[i], arr[i+1] = arr[i+1], arr[i]
            nr_steps += 1
            if nr_steps % step == 0:
              print(arr)

def merge(list_1, list_2):
   list_resulted = []
   i = j = 0
   while i < len(list_1) and j < len(list_2):
        if list_1[i] <= list_2[j]:
            list_resulted.append(list_1[i])
            i += 1
        else:
            list_resulted.append(list_2[j])
            j += 1

   list_resulted.extend(list_1[i: ])
   list_resulted.extend(list_2[j: ])
   return list_resulted

def strand_sort(arr, step):
   sorted_list = []
   nr_steps = 0
   while arr:
      aux = [arr.pop(0)]
      i = 0
      nr_steps += 1
      while i < len(arr):
        if arr[i] > aux[-1]:
           aux.append(arr.pop(i))
        else:
         i += 1
      sorted_list = merge(sorted_list, aux)
      if nr_steps % step == 0:
         print (sorted_list)
   arr.extend(sorted_list[0: ])

def command_1(list_of_numbers, n):
   list_of_numbers.clear()
   generate_list(list_of_numbers, n)
   print(list_of_numbers)

def command_2(list_of_numbers, n):
    if len(list_of_numbers) == 0:
      print("Please generate list first!")
    else:
      while True:
       print ("Please introduce a number of steps")
       try:
         step = int(input(">"))
         bubble_sort(list_of_numbers, n, step)
         print(list_of_numbers)
         break
       except ValueError:
          print("Value should be a natural number")
   
def command_3(list_of_numbers, n):
   if len(list_of_numbers) == 0:
      print("Please generate list first!")
   else:
    while True:
     print("Please intorduce a number of steps")
     try:
        step = int(input(">"))
        strand_sort(list_of_numbers, step)
        print(list_of_numbers)
        break
     except ValueError:
         print("Value should be a natural number")

def command_4(list_of_numbers, n):
   if len(list_of_numbers) == 0:
      print("Please generate list first!")
   else:
    if check_order(list_of_numbers, n) == True:
       while True:
         print("Please introduce a value to search")
         try:
          element = int(input(">"))
          binary_search(list_of_numbers, 0, n-1, element)
          break
         except ValueError:
          print("Value should be a natural number")
    else:
      print("Please sort the list first")

#this is the menu that will appear in the console
def display_menu():
   print("1. Generate list")
   print("2. Sort list using bubble sort")
   print("3. Sort list using strand sort")
   print("4. Search value in sorted list")
   print("5. Exit")

def create_menu():
   menu = {
      "1" : command_1,
      "2" : command_2,
      "3" : command_3,
      "4" : command_4
    }
   return menu

def start(): 
   list_of_numbers = [] 
   n = 0
   menu = create_menu()
   while True:
    print("Please insert a natural number")
    try:
         n = int(input(">"))
         if n < 0:
            raise Exception("Incorrect value")
         while True:
          display_menu()
          command = input(">")
          if(command == "5"): #"5" is the command which exits the program
            return
          elif command in menu:
              menu[command](list_of_numbers, n)
          else: 
                print("Bad command, please try again")
        
    except ValueError:
        print("Incorrect value")
           
   

start()
    
