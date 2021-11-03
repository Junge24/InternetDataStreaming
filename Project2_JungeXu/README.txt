Name:Junge Xu
UFID:86000983

These three algorithm were implemented in different files.

1.BloomFilter
The corresponding source file is bloomFilter.cpp and the output file of the demo is bloomfilter.dat

In the source code file, the filtersize, number of elements in the set, number of hashes were marco defined as 10000,1000 and 3 respectively. 
If you want to test for other input parameters, the only thing you need to do is to modify the marco definition. These marco definitions are at the begining  of the file.
For the out put file, the first line records the number of in-filter elements from set A. The second line records the number of in filter elements from set B.

2.Counting Bloom Filter
The source file is CountingBloomFilter.cpp and the output file is CountingBloomFilter.dat
In the source code file, tnumber of elements to be encoded initially(SIZEOFA ), number of elements to be removed(NUMOFREMOVE ), number of elements to be added(SIZEOFB), number of counters in the filter(FILTERSIZE), number of hashes(NUMOFHASHES ) were marco defined as 1000,500,500,10000 and 7 respectively. 
You could modify the marco definitions to test for other inputs. 
The out put file records the number of in-filter elements from current set.

3.Coded Bloom Filter
The source file is codedBloomFilter.cpp and the output file is CodedBloomFilter.dat
In the source code file, number of sets(NUMOFSETS), number of elements in each set(SETSIZE), number of filters(NUMOFFILTERS), number of bits in each filter(FILTERSIZE), number of hashes(NUMOFHASHES) were marco defined as 7,1000,3,10000 and 7 respectively. 
You could modify the marco definitions to test for other inputs. 
The out put file records the number of elements whose lookup results are correct.
