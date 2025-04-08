This program searches for <a href="https://en.wikipedia.org/wiki/Sator_Square"> Sator Squares </a> in given dictionaries and outputs the resoults.

Options:

| Option | Description                                              | Type   | Default | 
| ------ | -------------------------------------------------------- | ------ | ------- |
|`t,threadnum`| Number of threads for searching| `int` | `2`
|`o,outputfile`| Output file path| `string` | `out.txt`
|`i,inputfile`| Input file path. (One word per line)| `string` |`in.txt`
|`l,wordlenght`| Word Lenght for the palindrom | `int` | `5`
|`s,sorted`| Is the input dictcionary sorted|`bool` |`false`

Example:
<ul>
<li>The input is the latin dictionary at ./latin.txt.</li>

<li>The output path filename is results.txt.</li>

<li>We are loking for 7x7 palindroms.</li>

<li>We are ousing 10 threads.</li>

<li>And the dictionary is sorted.</li>
</ul>

``sh
./satorrotas -i ./latin.txt -o ./results.txt -l 7 -t 10 -s true
``
