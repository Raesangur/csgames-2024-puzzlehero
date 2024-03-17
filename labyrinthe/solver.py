import string

nums = [int(ord(c)) for c in string.ascii_lowercase] + [int(ord(c)) for c in string.ascii_uppercase]


def is_prime_beyond_11(n):
    if n % 2 or n % 3 or n % 5 or n % 7 or n % 11:
        return False
    return True



valids = []
for n in nums:
    if n % 4 == is_prime_beyond_11(n):
        if n // 20 == n % 20:
            valids.append(n)

print([chr(c) for c in valids])

    # CERTAIN                          CERTAIN
    # assoifé    de         de_        est
print(ord('Q') + ord('r') - ord('b') - ord('M'))
print(ord('u') - ord('t'))

