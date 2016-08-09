#!/usr/bin/python

from random import randint

# set tolerance
r = 0.2
# set density of the selected points (the higher the density ratio the lower the odds to select the data point)
densityRatio = 10

numLines = 0
numSelectedLines = 0

# select lines of datafile for which the read counts present a significant change
with open('data/example_guide_data.tsv') as inFile, open('data/selected_data.tsv', 'w') as outFile:
    next( inFile)
    for line in inFile:
        numLines += 1
        data = line.split( '\t')
        count_0 = float( data[3])
        count_7_N_1 = float( data[4])
        count_7_N_2 = float( data[5])
        count_14_N_1 = float( data[6])
        count_14_N_2 = float( data[7])
        count_7_D_1 = float( data[8])
        count_7_D_2 = float( data[9])
        count_14_D_1 = float( data[10])
        count_14_D_2 = float( data[11])
        count_7_N = ( count_7_N_1 + count_7_N_2 ) / 2
        count_7_D = ( count_7_D_1 + count_7_D_2 ) / 2
        count_14_N = ( count_14_N_1 + count_14_N_2 ) / 2
        count_14_D = ( count_14_D_1 + count_14_D_2 ) / 2
        average = ( count_0 + count_7_N + count_7_D + count_14_N + count_14_D ) / 5
        dev_0 = count_0 / average
        dev_7_N = count_7_N / average
        dev_14_N = count_14_N / average
        dev_7_D = count_7_D / average
        dev_14_D = count_14_D / average
        if ( ( dev_0 < r ) or ( dev_0 > 1/r )
                or ( dev_7_N < r ) or ( dev_7_N > 1/r )
                or ( dev_14_N < r ) or ( dev_14_N > 1/r )
                or ( dev_7_D < r ) or ( dev_7_D > 1/r )
                or ( dev_14_D < r ) or ( dev_14_D > 1/r ) ):
            if ( randint( 0, densityRatio) == 0 ):
                numSelectedLines += 1
                outFile.write( line)

print( "Selected " + str( numSelectedLines) + " data points out of " + str( numLines))
