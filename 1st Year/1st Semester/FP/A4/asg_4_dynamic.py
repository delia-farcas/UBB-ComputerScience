#6. Given an array of integers `A`, maximize the value of the expression `A[m] - A[n] + A[p] - A[q]`, where `m, n, p, q` are array indices with `m > n > p > q`. For `A = [30, 5, 15, 18, 30, 40]`, the maximum value is `32`, obtained as `40 - 18 + 15 - 5`. Display both the maximum value as well as the expression used to calculate it.

def maximize_expression_naive(A):
    n = len(A)
    max_value = float('-inf')
    expression_used = None
    # Iterate over all combinations of indices with the constraint m > n > p > q
    for m in range(3, n):
        for n in range(2, m):
            for p in range(1, n):
                for q in range(0, p):
                    # Calculate the expression for the current indices
                    value = A[m] - A[n] + A[p] - A[q]
                    
                    # Update maximum value and the expression used
                    if value > max_value:
                        max_value = value
                        expression_used = [A[m], A[n], A[p]]
    
    return max_value, expression_used


def maximize_expression_dynamic(A):
    n = len(A)
    
    # Initialize arrays to store intermediate max values and indices
    max1 = [float('-inf')] * n
    max2 = [float('-inf')] * n
    max3 = [float('-inf')] * n
    max4 = [float('-inf')] * n
    
    # Arrays to track indices for maximum expressions
    max1_index = [0] * n
    max2_index = [0] * n
    max3_index = [0] * n
    max4_index = [0] * n
    
    # Step 1: Fill max1 with the maximum A[q] from right to left
    max1[-1] = A[-1]
    max1_index[-1] = n - 1
    
    for i in range(n-2, -1, -1):
        if A[i] >= max1[i + 1]:
            max1[i] = A[i]
            max1_index[i] = i
        else:
            max1[i] = max1[i + 1]
            max1_index[i] = max1_index[i + 1]
    
    # Step 2: Compute max2 (maximum of -A[j] + max1[j+1])
    for i in range(n-2, -1, -1):
        if -A[i] + max1[i + 1] >= max2[i + 1]:
            max2[i] = -A[i] + max1[i + 1]
            max2_index[i] = i
        else:
            max2[i] = max2[i + 1]
            max2_index[i] = max2_index[i + 1]

    # Step 3: Compute max3 (A[k] + max2[k+1])
    for i in range(n-3, -1, -1):
        if A[i] + max2[i + 1] >= max3[i + 1]:
            max3[i] = A[i] + max2[i + 1]
            max3_index[i] = i
        else:
            max3[i] = max3[i + 1]
            max3_index[i] = max3_index[i + 1]
    
    # Step 4: Compute max4 (maximum of -A[l] + max3[l+1])
    for i in range(n-4, -1, -1):
        if -A[i] + max3[i + 1] >= max4[i + 1]:
            max4[i] = -A[i] + max3[i + 1]
            max4_index[i] = i
        else:
            max4[i] = max4[i + 1]
            max4_index[i] = max4_index[i + 1]
    
    # Maximum value of the expression
    max_value = max4[0]
    
    # Retrieve indices for maximum expression
    l = max4_index[0]
    k = max3_index[l + 1]
    j = max2_index[k + 1]
    i = max1_index[j + 1]
    
    # Retrieve values at those indices
    values = [A[i], A[j], A[k], A[l]]
    
    return max_value, values

def test(arr1, val1 ,arr2, val2):
    assert val1 == val2, "Solutions are different"
    assert arr1 == arr2, "Values are not the same"

def run():
  A = []
  n = int(input("->"))
  print("->")
  for i in range (n):
      j = int(input())
      A.append(j)

  max_val_dynamic, values_dynamic = maximize_expression_dynamic(A)
  max_val_naive, values_naive = maximize_expression_naive(A)
  test(max_val_dynamic, values_dynamic, max_val_naive, values_naive)
  
  print("Maximum value:", max_val_dynamic)
  print("Expresssion_used:", values_dynamic)

run()