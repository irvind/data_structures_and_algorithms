import random


def merge_sort(li):
    _sort(li, 0, len(li)) 


def _sort(li, start, end):
    # print(f'_sort, start: {start}, end: {end}')
    if start >= end:
        return
    elif end - start == 1:
        return

    mid = start + (end - start) // 2
    _sort(li, start, mid)
    _sort(li, mid, end)
    _merge(li, start, mid, end)


def _merge(li, start, mid, end):
    left_buf = li[start:mid].copy()
    right_buf = li[mid:end].copy()
    left_idx, right_idx, li_idx = 0, 0, start
    while True:
        if left_idx >= len(left_buf) and right_idx >= len(right_buf):
            break

        if left_idx >= len(left_buf):
            li[li_idx] = right_buf[right_idx]
            right_idx, li_idx = right_idx + 1, li_idx + 1
            continue

        if right_idx >= len(right_buf):
            li[li_idx] = left_buf[left_idx]
            left_idx, li_idx = left_idx + 1, li_idx + 1
            continue

        if left_buf[left_idx] < right_buf[right_idx]:
            li[li_idx] = left_buf[left_idx]
            left_idx, li_idx = left_idx + 1, li_idx + 1
        else:
            li[li_idx] = right_buf[right_idx]
            right_idx, li_idx = right_idx + 1, li_idx + 1


def main():
    li = [random.randint(0, 1000) for _ in range(21)]
    print('list before sort:')
    print(li)

    merge_sort(li)
    print('list after sort:')
    print(li)


if __name__ == '__main__':
    main()
