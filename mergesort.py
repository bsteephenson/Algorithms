# merge sort

# merges two sorted lists
def mergeLists(first, second):
	newList = []
	p1 = 0
	p2 = 0
	while p1 < len(first) or p2 < len(second):
		if (p1 == len(first)):
			newList.append(second[p2])
			p2 = p2 + 1
		elif p2 == len(second):
			newList.append(first[p1])
			p1 = p1 + 1			
		elif(first[p1] < second[p2]):
			newList.append(first[p1])
			p1 = p1 + 1
		else:
			newList.append(second[p2])
			p2 = p2 + 1
	return newList

def mergeSort(list):
	if len(list) <= 1:
		return list
	else:
		first = list[0:len(list)/2]
		second = list[len(list)/2:]
		first = mergeSort(first)
		second = mergeSort(second)
		return mergeLists(first, second)


print mergeSort([6, 5, 4, 3, 2, 1])
print mergeSort([1, 2, 3, 4, 5, 6])
print mergeSort([42, 42, 42, 42, 42])
print mergeSort([4, 2, 4, 2, 4, 2, 4, 2])
print mergeSort([])
print mergeSort([42])

