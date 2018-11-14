import numpy as np

recs_list = ['rec_itemKNN', 'rec_MostPopular', 'rec_userKNN', 'rec_WRMF']
n_list = ['', '_5', '_10', '_20']
for rec_list in recs_list:
    for nlist in n_list:
        filein = open(rec_list+ "/" +rec_list+ "" +nlist+ "_div.txt", 'r')

        diversity = []
        novelty = []
        fileout = open(rec_list+ "/" +rec_list+ "_eval.txt", 'a')
        for line in filein:
            line = line.strip()
            values = line.split(" ")
            u_id = values[0]
            novelty.append(float(values[3]))
            diversity.append(float(values[6]))

        fileout.write("\n")
        fileout.write("%s\n" % (rec_list + "" + nlist))
        fileout.write("Novelty average: %f" % (np.mean(novelty)))
        fileout.write("    Novelty median: %f\n" % (np.median(novelty)))
        fileout.write("Diversity average: %f" % (np.mean(diversity)))
        fileout.write("    Diversity median: %f\n" % (np.median(diversity)))
        fileout.write("--------------------------\n")
        fileout.write("\n")