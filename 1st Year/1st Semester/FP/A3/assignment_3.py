import timeit
import random

# Define sorting algorithms
def bubble_sort(arr):
    swap = True 
    while swap == True:
      swap = False
      for i in range(len(arr)-1):
         if arr[i] > arr[i+1]:
            swap = True
            arr[i], arr[i+1] = arr[i+1], arr[i]
            
def strand_sort(arr):
    sorted_list = []
    while arr:
        sublist = []
        pivot = arr.pop(0)
        sublist.append(pivot)
        for item in arr[:]:
            if item >= pivot:
                sublist.append(item)
                arr.remove(item)
        sorted_list.extend(sublist)
    return sorted_list

def binary_search(arr, target):
    low = 0
    high = len(arr) - 1
    while low <= high:
        mid = (low + high) // 2
        if arr[mid] < target:
            low = mid + 1
        elif arr[mid] > target:
            high = mid - 1
        else:
            return mid
    return -1

# Generate lists based on the case
def generate_data(case, size):
    if case == "best":
        return list(range(size))  # Already sorted
    elif case == "average":
        return [random.randint(0, size) for _ in range(size)]  # Randomized
    elif case == "worst":
        return list(range(size, 0, -1))  # Reverse sorted
    
# Choose a target for binary search based on the case
def choose_target(case, arr):
    if case == "best":
        target = arr[0]
    elif case == "average":
        target = random.choice(arr)
    else:
        target = arr[0] -1 
    return target

# Generate the sizes of the lists
def generate_sizes():
    while True: 
     print("Please choose the lenght of the list")
     try:
        l = int(input("->"))
        break
     except:
        print("Insert a natural number")    
    arr = [l]
    for i in range(1, 5):
        arr.append(arr[-1] * 2)
    return arr

# Timing function for sorting
def time_sorting_algorithm(algorithm, data):
    timer = timeit.Timer(lambda: algorithm(data.copy()))
    duration = timer.timeit(number=10)  # Run the algorithm 10 times
    return duration / 10  # Average duration

# Timing function for searching
def time_search_algorithm(search_function, data, target):
    timer = timeit.Timer(lambda: search_function(data, target))
    duration = timer.timeit(number=10)  # Run the search 10 times
    return duration / 10  # Average duration

def main():
    algorithms = {
        'Bubble Sort': bubble_sort,
        'Strand Sort': strand_sort,
        'Binary search' : binary_search
    }
    cases = ['best', 'average', 'worst']
    list_sizes = generate_sizes()
    while True:
        print("Select case to test (best, average, worst) or 'exit': ")
        case = input().strip().lower()
        if case == 'exit':
            break
        if case not in cases:
            print("Invalid case. Please select 'best', 'average', or 'worst'.")
            continue
    
        print(f"Running tests for {case} case...")
        for name, algorithm in algorithms.items():
            print(name)
            for size in list_sizes:
                if name == 'Binary search':
                   sorted_data = generate_data("best", size)  # Sort the data for binary search
                   target = choose_target(case, sorted_data)
                   duration = time_search_algorithm(binary_search, sorted_data, target)
                else:
                   data = generate_data(case, size)
                   duration = time_sorting_algorithm(algorithm, data)
                print(f"List Size: {size}, Average Duration: {duration:.6f} seconds")
    

main()
