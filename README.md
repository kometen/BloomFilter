# BloomFilter
A basic Bloom filter example based on http://blog.michaelschmatz.com/2016/04/11/how-to-write-a-bloom-filter-cpp/.

The timer may not be very accurate. The SO-thread https://stackoverflow.com/a/2808527/319826 points to a more
"correct" https://stackoverflow.com/questions/2962785/c-using-clock-to-measure-time-in-multi-threaded-programs/2962914#2962914
but when I implemented that I sometimes had negative elapsed time. So I went back to the first answer.

The vector v is populated with the values '1', '2', '3' ... MAX and then added to the Bloom filter. Then some elements are
compared to the filter.
