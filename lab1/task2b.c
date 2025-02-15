#include <stdio.h>
#include <ctype.h>

int main() {
    FILE *inf, *ouf;  //file pointer

    inf = fopen("input.txt", "r");

    ouf = fopen("output.txt", "w");

    char ch, pc = ' ';  // pc = previous char = space

    while ((ch = fgetc(inf)) != EOF) {  //using fgetc
        if (!(isspace(ch) && isspace(pc))) {  // space checked
            fputc(ch, ouf);  // check kortesi_()
        }
        pc = ch;  // Ager char up
    }

    fclose(inf);  
    fclose(ouf);  

    printf("Extra spaces removed, Yeey!! \n");

    return 0;
}

