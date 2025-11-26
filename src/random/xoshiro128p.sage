# We precompute tables that we can use to jump ahead 2^k * 2^96 states in O(1).
# By precomputing this for k = 0, ..., 31, we can jump ahead int l states in
# O(log(l)).
#
# The theory is based on
#     1. Efficient Jump Ahead for F2-Linear Random Number Generators
#     2. Scrambled Linear Pseudorandom Number Generators

def rotate(b):
    R = matrix(GF(2), 32)
    for i in range(32):
        R[mod(i + b, 32), i] = 1
    return R

def shift(a):
    S = matrix(GF(2), 32)
    for i in range(32 - a):
        S[i + a, i] = 1
    return S

I = matrix.identity(n = 32, ring = GF(2))
R = rotate(11)
S = shift(9)
O = matrix(GF(2), 32)

xoshiro128p = block_matrix([[I, I, I, O],
                            [I, I, S, R],
                            [O, I, I, O],
                            [I, O, O, R]])

p = xoshiro128p.charpoly()

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
    return format(num, '032x')

print("jump = [")
for k in range(32):
    q = a^(2^(k) * 2^(96))
    # Polynomials in quotient rings apparently have no degree
    coeff      = pack_hex(q, 127)
    four_coeff = [coeff[i: i + 8] for i in range(0, 32, 8)]
    print("[0x"  , four_coeff[0], 
          "u, 0x", four_coeff[1], 
          "u, 0x", four_coeff[2], 
          "u, 0x", four_coeff[3], 
          "u]",
          "" if k == 31 else ",",
          sep = "")
print("];")
