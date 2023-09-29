#include <stdio.h>
#include <string.h>

char s[23];
char to_print[23];
int k;

void recursive(int pos){
	if(pos == k){
    	printf("%s\n", to_print);
        return;
    }
    for(int i = 0; i < strlen(s); i++){
    	to_print[pos] = s[i];
        recursive(pos+1);
    }
}

int main(){
	scanf("%s%d", s, &k);
    recursive(0);
	return 0;
}