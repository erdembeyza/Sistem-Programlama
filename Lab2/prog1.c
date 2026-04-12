#include <stdio.h>
int main (int argc, char *argv[]){
	if (argc!=5){
	//4dış girdi+1 program adı
	printf("tam 4 girdi yazılmalı\n");
	printf("%d 4 girdi giriniz", argc-1);
	return 1;			
			}
//argc -1: programın adını saymadan kaç girdi verdiğini buluyoruz.

	for( int i=1; i<argc; i++){
		printf("%d. girdi: %s \n", i,argv[i]);}
	return 0;
}
