# sorts.py
#
# 08-30-2018
#  originally completed 03-19-2018; updated file description today. sorts.py contains some implementations
# of basic sorts, including insertion sort, selection sort, merge sort, quick sort, and a hybrid sort
# that uses insertion sort for small sets and otherwise uses recursive quick sort. potentially a heap sort
# implementation will be added at some point; some of these functions need to be rewritten more concisely
# and efficiently.
#
# 03-19-2018
# original completion
#

# insertion sort implementation
def insertion_sort(a):
    # length of a
    n = len(a)
    # for each element in a after the first one
    for i in range(1, n):
        # keep track of index i
        j = i
        # swap until a[i] is in the correct position in the array
        while (a[j] < a[j - 1] and j > 0):
            # pythonic approach; results in non-in-place insertion sort
            a.insert(j - 1, a.pop(j))
            j = j - 1
    return

# selection sort implementation
def selection_sort(a):
    # length of a
    n = len(a)
    # for each element except the last
    for i in range(0, n):
        # keep track of smallest element's index
        sei = i
        # get the smallest element
        for j in range(i, n):
            e = a[j]
            # if e <= sei, update sei (works for duplicates)
            if (e <= a[sei]):
                sei = j
        # swap a[sei] with a[i]
        t = a[sei]
        a[sei] = a[i]
        a[i] = t
    return

# merge sort implementation; there is no method overloading in python, so we use a variable amount of arguments.
# if there is one argument, a will set to args[0], si will be set to 0, and ei will be set to len(args[0]) - 1
# must take three arguments exactly to run properly
# a[] is the list to sort, si is the starting sort index, and ei is the ending sort index
def merge_sort(*args):
    # get number of arguments
    argn = len(args)
    # if there are exactly three arguments
    if (argn == 3):
        # if there are exactly three arguments, a = args[0], si = args[1], and ei = args[2]
        a = args[0]
        si = args[1]
        ei = args[2]
    # else if there are not three arguments
    else:
        # if there is only one argument
        if (argn == 1):
            a = args[0]
            # si set to 0
            si = 0
            # ei set to len(args[0]) - 1
            ei = len(args[0]) - 1
        # else print error
        else:
            print("merge_sort(*args): incorrect number of arguments, expected 1 or 3")
            return
    # base case is to do nothing on a list of length 1, since it is already sorted
    if (si < ei):
        # get middle index (int division)
        mi = (si + ei) // 2
        # merge sort left half
        merge_sort(a, si, mi)
        # merge sort right half
        merge_sort(a, mi + 1, ei)
        # merge the two sorted arrays
        # create sub array b[] from the sorted "left half"
        b = []
        for i in range(si, mi + 1):
            b.append(a[i])
        # create sub array c[] from the sorted "right half"
        c = []
        for i in range(mi + 1, ei + 1):
            c.append(a[i])
        # index pointer for b[]
        bi = 0
        # index pointer for c[]
        ci = 0
        # index pointer for a[]
        i = si
        # merge b[] and c[] by writing their values onto a[]
        while (bi < mi - si + 1 and ci < ei - mi):
            # if b[bi] <= c[ci]; we account for duplicate values and try to preserve element order
            if (b[bi] <= c[ci]):
                a[i] = b[bi]
                bi = bi + 1
                i = i + 1
            # else
            else:
                a[i] = c[ci]
                ci = ci + 1
                i = i + 1
        # write any leftover values from b[] into a[]
        while (bi < mi - si + 1):
            a[i] = b[bi]
            bi = bi + 1
            i = i + 1
        # write any leftover values from c[] into a[]
        while (ci < ei - mi):
            a[i] = c[ci]
            ci = ci + 1
            i = i + 1
    return

# quick sort implementation; there is no method overloading in python, so we use a variable amount of arguments.
# if there is one argument, a will set to args[0], si will be set to 0, and ei will be set to len(args[0]) - 1
# must take three arguments exactly to run properly
# a[] is the list to sort, si is the starting sort index, and ei is the ending sort index
def quick_sort(*args):
    # get number of arguments
    argn = len(args)
    # if there are exactly three arguments
    if (argn == 3):
        # if there are exactly three arguments, a = args[0], si = args[1], and ei = args[2]
        a = args[0]
        si = args[1]
        ei = args[2]
    # else if there are not three arguments
    else:
        # if there is only one argument
        if (argn == 1):
            a = args[0]
            # si set to 0
            si = 0
            # ei set to len(args[0]) - 1
            ei = len(args[0]) - 1
        # else print error
        else:
            print("quick_sort(*args): incorrect number of arguments, expected 1 or 3")
            return
    # base case is to nothing for a list of length 1, since it is already sorted
    if (si < ei):
        # partition the array
        # get the index of the pivot; just the middle value
        pi = (si + ei) // 2
        # get value of pivot
        p = a[pi]
        # left side index
        li = si
        # right side index
        ri = ei
        # number of duplicates: important for preventing infinite recursion given a list full of identical elements
        nd = 0
        # while ri > li; that is, while ri does not yet equal li
        while (ri > li):
            # if a[li] < p and li < pi, increment li
            if (a[li] < p and li < pi):
                li = li + 1
            # if a[li] == p and li < pi, increment li, but also increment nd as we have spotted a duplicate
            if (a[li] == p and li < pi):
                li = li + 1
                nd = nd + 1
            # if a[ri] > p and ri > pi, decrement ri
            if (a[ri] > p and ri > pi):
                ri = ri - 1
            # if ri does not equal li and a[ri] <= a[li] (accounts for duplicates); that is, there is an inversion,
            # swap and update pi if the pivot is one the elements being swapped
            if (ri > li and a[ri] <= a[li]):
                # if the pivot index pi is equal to ri
                if (pi == ri):
                    # set pi to li
                    pi = li
                # else if pi equals li
                elif (pi == li):
                    # set pi to ri
                    pi = ri
                # swap values
                t = a[li]
                a[li] = a[ri]
                a[ri] = t
        # to avoid a fringe case in which given a sublist containing values that are duplicates of the
        # pivot (in this case it was  [3, 3] and [5, 4, 5, 5, 5]), quick sort will infinitely recurse 
        # because the pivot is always the last element in this sublist. thus, we check if there are any
        # duplicate values of the pivot and if the pivot is the last element in the sublist. if so,
        # we execute quick_sort(a, si, pi - 1) to avoid infinite recursion.
        if (nd > 0):
            quick_sort(a, si, pi - 1)
        # else quick sort as usual
        else:
            # quick sort a[si] to a[pi]
            quick_sort(a, si, pi)
        # we do not have to perform the same check for the second quick sort call because the start index
        # is constantly being advanced
        # quick sort a[pi + 1] to a[ei]
        quick_sort(a, pi + 1, ei)
    return

# improved sort implementation, where insertion sort is used once quick sort recursive calls start to operate on lists
# that are size <= 10
def improved_sort(*args):
    # get number of arguments
    argn = len(args)
    # if there are exactly three arguments
    if (argn == 3):
        # if there are exactly three arguments, a = args[0], si = args[1], and ei = args[2]
        a = args[0]
        si = args[1]
        ei = args[2]
    # else if there are not three arguments
    else:
        # if there is only one argument
        if (argn == 1):
            a = args[0]
            # si set to 0
            si = 0
            # ei set to len(args[0]) - 1
            ei = len(args[0]) - 1
        # else print error
        else:
            print("improved_sort(*args): incorrect number of arguments, expected 1 or 3")
            return
    # base case is to nothing for a list of length 1, since it is already sorted
    if (si < ei):
        # if ei - si < 10, which indicates that the recursive call is going to operate an a region of 10 or
        # fewer elements, use insertion sort instead
        if (ei - si < 10):
            # for each element a[si] to a[ei]
            for i in range(si, ei + 1):
                # keep track of index i
                j = i
                # swap until a[i] is in the correct position in the array
                while (a[j] < a[j - 1] and j > 0):
                    # no use of the pop() and insert() functions because the sort will no longer be an in-place sort
                    t = a[j - 1]
                    a[j - 1] = a[j]
                    a[j] = t
                    j = j - 1
            return
        # else proceed with a typical quick sort implementation
        # partition the array
        # get the index of the pivot; just the middle value
        pi = (si + ei) // 2
        # get value of pivot
        p = a[pi]
        # left side index
        li = si
        # right side index
        ri = ei
        # number of duplicates: important for preventing infinite recursion given a list full of identical elements
        nd = 0
        # while ri > li; that is, while ri does not yet equal li
        while (ri > li):
            # if a[li] < p and li < pi, increment li
            if (a[li] < p and li < pi):
                li = li + 1
            # if a[li] == p and li < pi, increment li, but also increment nd as we have spotted a duplicate
            if (a[li] == p and li < pi):
                li = li + 1
                nd = nd + 1
            # if a[ri] > p and ri > pi, decrement ri
            if (a[ri] > p and ri > pi):
                ri = ri - 1
            # if ri does not equal li and a[ri] <= a[li] (accounts for duplicates); that is, there is an inversion,
            # swap and update pi if the pivot is one the elements being swapped
            if (ri > li and a[ri] <= a[li]):
                # if the pivot index pi is equal to ri
                if (pi == ri):
                    # set pi to li
                    pi = li
                # else if pi equals li
                elif (pi == li):
                    # set pi to ri
                    pi = ri
                # swap values
                t = a[li]
                a[li] = a[ri]
                a[ri] = t
        # to avoid a fringe case in which given a sublist containing values that are duplicates of the
        # pivot (in this case it was  [3, 3] and [5, 4, 5, 5, 5]), quick sort will infinitely recurse 
        # because the pivot is always the last element in this sublist. thus, we check if there are any
        # duplicate values of the pivot and if the pivot is the last element in the sublist. if so,
        # we execute quick_sort(a, si, pi - 1) to avoid infinite recursion.
        if (nd > 0):
            improved_sort(a, si, pi - 1)
        # else quick sort as usual
        else:
            # quick sort a[si] to a[pi]
            improved_sort(a, si, pi)
        # we do not have to perform the same check for the second quick sort call because the start index
        # is constantly being advanced
        # quick sort a[pi + 1] to a[ei]
        improved_sort(a, pi + 1, ei)
    return

# main that tests all the sorts
def main():
    # need to import copy so that we can use deepcopy()
    import copy
    # array to sort
    a = [3, 6, 2, 8, 12, 1, 15, 17, 56, 98, 34, 35, 2, 65, 43, 26, 76, 43, 36, 54, 77, 23, 55, 43, 7, 3]
    #a = [5, 6, 5, 8, 12, 5, 4, 5]
    # -- test insertion sort
    b = copy.deepcopy(a)
    insertion_sort(b)
    print("insertion sort result:\n{0}".format(b))
    # -- test selection sort
    b = copy.deepcopy(a)
    selection_sort(b)
    print("selection sort result:\n{0}".format(b))
    # -- test merge sort
    b = copy.deepcopy(a)
    merge_sort(b)
    print("merge sort result:\n{0}".format(b))
    # -- test quick sort
    b = copy.deepcopy(a)
    quick_sort(b)
    print("quick sort result:\n{0}".format(b))
    # -- test improved hybrid sort
    b = copy.deepcopy(a)
    improved_sort(b)
    print("improved sort result:\n{0}".format(b))
    return

if (__name__ == "__main__"):
    main()
