# In place quick sort

# start and end are the first and last indices we're working on
def qsort_rec(list, start, end):
	if start >= end:
		return
	elif start < 0 or end >= len(list):
		return
	else:
		# naively have pivot be the first element
		pivot = list[start]

		left = start
		right = end

		while left < right:
			if (pivot <= list[right]):
				right = right - 1
			elif (list[left] <= pivot):
				left = left + 1
			else:
				temp = list[left]
				list[left] = list[right]
				list[right] = temp
		
		temp = list[left]
		list[left] = pivot
		list[start] = temp

		qsort_rec(list, start, left - 1)
		qsort_rec(list, left + 1, end)

def qsort(list):
	qsort_rec(list, 0, len(list) - 1)
	return list

list = [1, 5, 25, 7, 10, 42, 5, 100, -3]
print qsort(list)
list = [1, 5, 25, 11, 10, 42, 5, 100, -3]
print qsort(list)
list = [1, 5, 25, 7, 10, 42, 5, 100]
print qsort(list)
list = [1, 3, 4]
print qsort(list)
list = [1]
print qsort(list)
list = [3, 3, 3]
print qsort(list)
list = [4, 3, 1, 0]
print qsort(list)


