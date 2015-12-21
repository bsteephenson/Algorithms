# Radix sort with radix 2 (the digits are the 0's and 1's)

def getBit(word, index):
	mask = 1 << index
	return word & mask != 0

def radixSort(oldList):
	newList = list(oldList)
	for digit in range(0,32):
		buckets = {0: [], 1: []}
		for value in newList:
			buckets[getBit(value, digit)].append(value)
		newList = buckets[0] + buckets[1]
		digit = digit + 1
	return newList

print radixSort([42, 7, 0, 100])
print radixSort([42, 42, 42])
print radixSort([1000, 100, 10, 1])
print radixSort([0, 1, 2, 3, 4, 5, 6, 7, 8, 9])
print radixSort([9, 8, 7, 6, 5, 4, 3, 2, 1, 0])
print radixSort([16, 1, 4, 2, 8, 0])

