# plain ol binary search

def search(list, value):
	return search_rec(list, value, 0, len(list) - 1)

def search_rec(list, value, start, end):
	if start == end:
		if list[start] == value:
			return start
		else:
			return -1
	elif start < 0 or end >= len(list):
		return -1
	else:
		width = end - start + 1
		mid = start + width / 2
		if value < list[mid]:
			return search_rec(list, value, start, mid - 1)
		elif value == list[mid]:
			return mid
		else:
			return search_rec(list, value, mid + 1, end)


list = sorted([1, 3, 4, 8])

print search(list, 1)
print search(list, 3)
print search(list, 4)
print search(list, 8)
print search(list, 42)


list = sorted([1, 3, 4, 8, 42])
print search(list, 1)
print search(list, 3)
print search(list, 4)
print search(list, 8)
print search(list, 42)


