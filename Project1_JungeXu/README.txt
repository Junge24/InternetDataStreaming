Name:Junge Xu
UFID:86000983

These three algorithm were implemented in different files.

1.Multi-hash table
The corresponding source file is multihash.cpp and the output file of the demo is MultiHash.dat
In the source code file, the number of flows, number of entries, number of hashes was marco defined as 1000,1000 and 3 respectively. 
If you want to test for other input parameters, the only thing you need to do is to modify the marco definition. These marco definitions are at the begining  of the file.
For the out put file, the first line records the count of flows in the table. The following is the list of table entries. The value of these entries are flow IDs.

2.Cuckoo-hash table
The source file is cuckoohash.cpp and the output file is CuckooHash.dat
In the source code file, the number of flows, number of entries, number of hashes and number of steps was marco defined as 1000,1000,3 and 2 respectively. 
You could modify the marco definitions to test for other inputs. 
For the out put file, the first line records the count of flows in the table. The following is the list of table entries. The value of these entries are flow IDs.

3.DLeft-hash table
The source file is dlefthash.cpp and the output file is DLeftHash.dat
In the source code file, the number of flows, number of entries, number of segments was marco defined as 1000,1000 and 4 respectively. 
You could modify the marco definitions to test for other inputs. 
For the out put file, the first line records the count of flows in the table. The following is the list of table entries. The value of these entries are flow IDs.
