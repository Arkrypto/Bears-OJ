//#include <stdio.h>
//#include <string.h>
//#include "mpc.h"
////�����WIN32���������Լ�д��readLine
//#ifdef _WIN32
////ά��һ���ַ�������Ϊ���뻺�� 
//static char buffer[2084];
//                                                                                 
////fputs��fgets��strcpy 
//char* readLine(char* prompt){
//	fputs(prompt, stdout);
//	fgets(buffer, 2084, stdin);
//	
//	char* cpy = malloc(strlen(buffer)+1);
//	
//	strcpy(cpy, buffer);
//	cpy[strlen(cpy) - 1] = '\0';
//	
//	return cpy;
//}
//
//
////��¼������ʷ���ϼ���������ָ��Ĺ���WIN32����̨�Դ� 
//void add_history(char* unused){}
//
////����linux�����������readline.h��history.h 
//#else
//#include <readline/readline.h>
//#include <readline/history.h>
//#endif
//
//
//
// 
//
////run this program using the console pauser or add your own getch, system("pause") or input loop
//int main(int argc, char *argv[]) {
//	
//	puts("Lispy Version 0.1\nPress Ctrl+c to Exit\n");
//	
//	while(1){
//		char* input = readLine("lispy>");
//		add_history(input);
//		printf("Now you're a %s\n", input);
//		free(input);
//	}
//	
//	return 0;
//}
//

