
mtab = []

def gen_region(sx, sy, px, py):
	l = [[0 for i in xrange(8)] for j in xrange(8)]
	for y in xrange(sy):
		for x in xrange(sx):
			l[py+y][px+x] = 1
	mtab.append(l)

# 0/1 need to be solid
# 1 is used to reset a macroblock to solid
gen_region(8, 8, 0, 0)
gen_region(8, 8, 0, 0)

# left/right/up/down
gen_region(4, 8, 0, 0)
gen_region(4, 8, 4, 0)
gen_region(8, 4, 0, 0)
gen_region(8, 4, 0, 4)

# 4x4 corners
for y in xrange(0,8,4):
	for x in xrange(0,8,4):
		gen_region(4, 4, x, y)

# 4x2s and 2x4s
for y in xrange(0,8,4):
	for x in xrange(0,8,2):
		gen_region(2, 4, x, y)
		gen_region(4, 2, y, x)

# 2x2s
for y in xrange(0,8,2):
	for x in xrange(0,8,2):
		gen_region(2, 2, x, y)

# 1x2s and 2x1s
for y in xrange(0,8,1):
	for x in xrange(0,8,2):
		gen_region(2, 1, x, y)
		gen_region(1, 2, y, x)

# 1x1s
for y in xrange(0,8,1):
	for x in xrange(0,8,1):
		gen_region(1, 1, x, y)

# print block tab
print "static const uint32_t cuck_dectab[%i*2] = {" % len(mtab)
for l in mtab:
	v0 = 0
	v1 = 0
	i = 0
	for y in xrange(8):
		for x in xrange(8):
			if i < 32:
				v0 |= (l[y][x])<<i
			else:
				v1 |= (l[y][x])<<(i-32)

			i += 1

	print "\t0x%08XU, 0x%08XU," % (v0, v1)

print "};"
print

