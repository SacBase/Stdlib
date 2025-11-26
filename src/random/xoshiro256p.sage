# We precompute tables that we can use to jump ahead 2^k * 2^192 states in O(1).
# By precomputing this for k = 0, ..., 31, we can jump ahead int l states in
# O(log(l)).
#
# The theory is based on
#     1. Efficient Jump Ahead for F2-Linear Random Number Generators
#     2. Scrambled Linear Pseudorandom Number Generators

def rotate(b):
    R = matrix(GF(2), 64)
    for i in range(64):
        R[mod(i + b, 64), i] = 1
    return R

def shift(a):
    S = matrix(GF(2), 64)
    for i in range(64 - a):
        S[i + a, i] = 1
    return S

I = matrix.identity(n = 64, ring = GF(2))
R = rotate(45)
S = shift(17)
O = matrix(GF(2), 64)

xoshiro256p = block_matrix([[I, I, I, O],
                            [I, I, S, R],
                            [O, I, I, O],
                            [I, O, O, R]])

p = xoshiro256p.charpoly()

ring  = PolynomialRing(GF(2), 'x')
qring = ring.quotient(p, 'a')
a     = qring.gen()

# Packs coefficients of polynomial q in a hex string,
# with the degree-0 coefficient on the right.
def pack_hex(q, degree):
    # length degree + 1
    coeff = q.list()
    num = 0
    for b in range(degree + 1):
        if (q[b] == 1):
            num += 2^b
    return format(num, '064x')

print("jump = [")
for k in range(32):
    q = a^(2^(k) * 2^(192))
    # Polynomials in quotient rings apparently have no degree
    coeff      = pack_hex(q, 255)
    four_coeff = [coeff[i: i + 16] for i in range(0, 64, 16)]
    print("[0x"  , four_coeff[0], 
          "ul, 0x", four_coeff[1], 
          "ul, 0x", four_coeff[2], 
          "ul, 0x", four_coeff[3], 
          "ul]",
          "" if k == 31 else ",",
          sep = "")
print("];")
