import csv

def read_list_of_lists(filename = '../data/testout.csv'):
  L = []
  with open(filename,'rb') as f:
    csvreader = csv.reader(f,delimiter = '\t')
    for row in csvreader:
      L.append(map(int,row))
  return L
