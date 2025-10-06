
#11.  Two natural numbers `m` and `n` are given. Display in all possible modalities the numbers from `1` to `n`, such that between any two numbers on consecutive positions, the difference in absolute value is at least `m`. If there is no solution, display a message.


def is_valid(arr, m, next):
    if not arr:
        return True
    else:
        return abs(arr[-1] - next) >= m

#RECURSIVE solution  
def back(results, arr, n, m):
    if len(arr) == n:
        results.append(arr.copy())
    else:
        for i in range(1, n+1):
            if i not in arr and is_valid(arr, m, i):
                arr.append(i)
                back(results, arr, n, m)
                arr.pop()
'''
def generate_recursive(n, m): #function that prints the recursive generated solutions 
    solutions = []
    back(solutions, [], n, m)
    if not solutions:
        print("No solutions found")
    else:
        for i in solutions:
            print(i)
'''

#ITERATIVE solution
def generate_sequences(n, m): 
    results = []
    stack = [[]] 
    while stack:
        current_sequence = stack.pop()
        if len(current_sequence) == n:  
            results.append(current_sequence)
            continue
        for num in range(1, n + 1):
            if num not in current_sequence:  
                if is_valid(current_sequence, m, num):
                    stack.append(current_sequence + [num])
    return results

'''
def generate_iterative(n, m): #function that prints the oterative generated solutions
  solutions = generate_sequences(n, m)
  if not solutions:
    print("No solutions found")
  else:
      for i in solutions:
          print(i)
'''

def test(arr1, arr2): #function that tests if both solutions are the same 
    assert len(arr1) == len(arr2), "Solutions have different lenghts"
    arr1 = sorted(arr1)
    arr2 = sorted(arr2)
    
    assert arr1 == arr2, "Solutions are not the same"

def main():
     n = int(input("Insert the length of the sequence ->"))
     m = int(input("Insert the minimum absolute difference ->"))
     iterative = []
     iterative = generate_sequences(n, m)
     recursive = []
     back(recursive, [], n, m)
     test(iterative, recursive)
     if not recursive:
        print("No solutions found")
     else:
        for i in recursive:
            print(i)
main()
