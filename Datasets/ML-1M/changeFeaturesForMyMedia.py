filein = open('featuresItems.txt', 'r')

fileout = open('attrItems.txt', 'w')

features = filein.readline().split("::")

for line in filein:
	line = line.rstrip()
	values = line.split(" ")

	item_id = values[0]
	cont = 0

	for i in values[1:]:
		cont += 1
		if i != '0':
			fileout.write("%s,%d\n" % (item_id, cont))

filein.close()
fileout.close()