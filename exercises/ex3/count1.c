#include <stdio.h> // stdio.h gives us printf
#include <string.h> // string.h gives us strlen


/* The purpose of this program is to convert a dna string into its
reverse complement as follows: the whole string is reversed from the
original, and additionally each base (character) is converted to its
complement: A <-> T, C <-> G.
Example: original == "ACTTAG"  reverse complement == "CTAAGT"
*/

int main() {
    // "dna" holds beginning of human mitochrondrial genome sequence
    const char dna[] = "GATCACAGGTCTATCACCCTATTAACCACTCACGGGAGCTCTCCATGCAT"
                       "TTGGTATTTTCGTCTGGGGGGTGTGCACGCGATAGCATTGCGAGACGCTG"
                       "GAGCCGGAGCACCCTATGTCGCAGTATCTGTCTTTGATTCCTGCCTCATT"
                       "CTATTATTTATCGCACCTACGTTCAATATTACAGGCGAACATACCTACTA"
                       "AAGTGTGTTAATTAATTAATGCTTGTAGGACATAATAATAACAATTGAAT";

    // Note: above is one long string literal, wrapped across lines

    // strlen is a function that returns the length of the string
    int dna_len = strlen(dna);
    // printf("%d",dna_len);
    // create array to hold the reverse complement, leaving an extra element
    // for the null character since it's not part of the reported length
    char rev_comp[dna_len+1];   

    int rci = 0;  //index into reverse complement array

    // TODO: set the value of rev_comp[rci] for every valid index
    for (rci; rci < dna_len+1; rci++) {
      switch(dna[rci]) {
      case 'A': rev_comp[rci] = 'T';
	break;
      case 'T': rev_comp[rci] = 'A';
	break;
      case 'C': rev_comp[rci] = 'G';
	break;
      case 'G': rev_comp[rci] = 'C';
	break;
	
      }
      if (rev_comp[rci] == '\0') {
	return 0;
      }
    }



    // TODO: add the null character to the end of rev_comp
    rev_comp[dna_len + 1] = '\0';



    // output results
    printf("original: %s\n", dna);
    printf("rev_comp: %s\n", rev_comp);

    return 0;
}
