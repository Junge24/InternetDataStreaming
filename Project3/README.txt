Name:Junge Xu
UFID:86000983

These three algorithm were implemented in different files.

1.Count Min
The corresponding source file is CountMin.cpp and the output file of the demo is countmin.dat

In the source code file, the number of counter arrays, counter size, name of the input file were marco defined as 3, 3000 and  "project3input.txt" respectively. 
If you want to test for other input parameters, the only thing you need to do is to modify the marco definition. These marco definitions are at the begining  of the file.
In the main function, it records the flows packets. And in the query function, it estimates the flows' size and calculated the error.

2.Counter Sketch
The corresponding source file is CounterSketch.cpp and the output file of the demo is countersketch.dat

In the source code file, the number of counter arrays, counter size, name of the input file were marco defined as 3, 3000 and  "project3input.txt" respectively. 
If you want to test for other input parameters, the only thing you need to do is to modify the marco definition. These marco definitions are at the begining  of the file.
In the main function, it records the flows packets. And in the query function, it estimates the flows' size and calculated the error.
By using the language build in string hash function in std::hash, it could generate a positive number for a certain ip address( In java ,this number could be negative). I use the last bit of myhash(flows[i].id ^ hashes[j]) to determine (+/-).  After that, it removes the last bit of the myhash value, and records the flow' size in counters[j][(myhash((flows[i].id ^ hashes[j])) >>1 ) % numOfCounters].
In the query function, it estimatizes the flows size from each of the counter arrays, forms a vector of estimated sizes, sort the vector and return the medium elements. It the number of counter arrays is even, it will return the average value of the middle two elements.

3.Active Counter
The source file is ActiveCounter.cpp and the output file is activecounter.dat
In the source code file, number of increasing times ,num of bits used for  the number part of the counter, and num of bits used for the exponent part of the counter were marco defined as 1,000,000,16,16 respectively . 
You could modify the marco definitions to test for other inputs. 

The out put file records the final value of the active counter in decimal.
