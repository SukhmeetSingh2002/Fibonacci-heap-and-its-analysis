# Fibonacci heaps analysis and comparison with Binary Heap

It is a implementation of Fibonacci heaps and its comparison with Binary Heap.Fibonacci heap has much better performance comapared to binary and binomial heap.

## Usage

Run `main.c` file to run Fibonacci heaps and perform different opperations and at end it will display the time taken

Run `binaryHeap.c` file to run Binary heaps and perform different opperations and at end it will display the time taken

Run 
```
python testcase/testcasemaker.py
``` 
to generate test cases in `INSERT_UNION_FIB.txt` and `INSERT_UNION_BINARY.txt` then  uncomment lines in `main.c` and `binaryHeap.c` to redirect input and from files.

---
## Fibonacci Heap vs Binary Heap
Fibonacci heaps support deletion and decrease key `O(log n)` amortized time and all other standard heap operations in `O(1)` amortized time. Whereas Binary Heap take `O(log n)` for most of the operations and `O(n)` for union. Fibonacci heaps can perform union in `O(1)` amortized time.Thus, all the algorithms such as **Djikstra’s**, **Prim’s Min Cost Spanning Tree**, can be made even more efficient by using Fibonacci heaps in place of the Binary Heap.



---
## Contributors

| Name            | Entry Number |
| --------------- | ------------ |
| Sourabh Sanganwar | 2020CSB1121  |
| Sanyam Walia  | 2020CSB1122  |
| Sukhmeet Singh | 2020CSB1129  |

It was made under the guidance of our TA-**Sarthak Joshi**