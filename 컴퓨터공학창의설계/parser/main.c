#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define MAX_LINE 1024
#define TMP_FILE_NAME "tmp_file"
typedef enum Option{
	LIST,
	LINE_COUNT,
	REPLACE,
	ANALYSIS,
	ANALYSIS_DETAIL
} Option;

typedef enum FlagType {
	F_INT,
	F_DOUBLE,
	F_VOID
} FlagType;

void printOption();
void exec();
int isOption();
void addOption();
void execList(char *);
void execLineCount(char *);
void execReplace(char *, char *, char *);
void execAnalysis(char *);
void execAnalysisDetail(char *);

void printOption(){
	printf("-list [file] : 입력파일을 화면에 출력합니다.\n");
	printf("-linecount [file] : 해당 파일의 라인 수를 출력합니다.\n");
	printf("-replace [file] a b : file내에서 a를 b로 치환합니다.\n");
	printf("-analysis [file] : file 에서 사용된 변수와 함수의 갯수를 출력합니다.\n");
	printf("-analysis_detail [file] : file에서 사용된 전역변수의 갯수랑 함수별 분석 결과를 출력합니다.\n");
}

char * addMargin(char * str){
	char * result = (char *)malloc(sizeof(char) * strlen(str) + 2);
	//result[0] = ' ';
	for(int i=0;i<strlen(str);i++){
		result[i] = str[i];
	}
	result[strlen(str)] = ' ';

	return result;
}

void exec(char * fileName, Option *options, int length, char * r_old, char * r_new){

	for(int i=0;i<length;i++){
		//printf("%d ", options[i]);
		switch(options[i]){
			case 0:
				execList(fileName);
				break;
			case 1:
				execLineCount(fileName);
				break;
			case 2:
				execReplace(fileName, r_old, r_new);
				execList(fileName);
				break;
			case 3:

				break;
			case 4:

				break;
		}
	
	}
	printf("\n");
}

int isOption(char * op){
	return op[0] == '-';
}

void addOption(Option * optionArray, Option option, int * length){
	optionArray[*length] = option;
	(*length)++;
	return;
}

void execList(char * fileName){
	FILE *fp = fopen(fileName, "r");
	if(fp==NULL){
		fprintf(stderr, "파일을 열 수 없습니다");
		exit(1);
	}

	while(1){
		char buffer[MAX_LINE];
		char * line = fgets(buffer, sizeof(buffer), fp);
		if(line==NULL) break;
		printf("%s", line);
	}

	fclose(fp);
}

void execLineCount(char * fileName){
	FILE *fp = fopen(fileName, "r");
	if(fp==NULL){
		fprintf(stderr, "파일을 열 수 없습니다");
		exit(1);
	}
	int lineCount = 0;
	while(1){
		char buffer[MAX_LINE];
		char * line = fgets(buffer, sizeof(buffer), fp);
		if(line==NULL) break;
		lineCount++;
	}
	fclose(fp);

	printf("%s 파일의 라인 갯수 : %d\n", fileName, lineCount);
}

void execReplace(char * fileName, char * oldWord, char * newWord){
	char * old = addMargin(oldWord);
	char * new = addMargin(newWord);
	printf("old : %s new : %s\n",old, new);
 	printf("fileName : %s\n", fileName);
	FILE * old_fp = fopen(fileName, "r");
	FILE * new_fp = fopen(TMP_FILE_NAME, "w");
	
	if(old_fp == NULL || new_fp == NULL){
		fprintf(stderr, "파일을 열 수 없습니다");
		exit(1);
	}
	int flag = 0;
	char buffer[MAX_LINE] = {0};
	int count = 0;	
	while(1){
		char c = fgetc(old_fp);
		if(c == EOF) break;		
		if(c == old[flag]){
			buffer[flag++] = c;
			buffer[flag] = '\0';
			if(flag == strlen(old)){
			 	fputs(new, new_fp);
				flag = 0;
				count++;
			}
		}else if(flag > 0){
			fputs(buffer, new_fp);
			fputc(c, new_fp);
			flag = 0;	
		}else{
			fputc(c, new_fp);
		}
	}
	
	printf("총 %d개의 %s 가 %s 으로 교체되었습니다.\n", count, oldWord, newWord);

	fclose(old_fp);
	fclose(new_fp);
	free(old);
	free(new);	
	remove(fileName);
	rename(TMP_FILE_NAME, fileName);
}

void execAnalysis(char * fileName){
	
	int funcCount = 0;
	int varCount = 0;
	char * INT = "int";
	char * DOUBLE = "double";
	char * VOID = "void";
	FILE * fp = fopen(fileName, "r");

	if(fp == NULL){
		fprintf(stderr, "파일을 열 수 없습니다");
		exit(1);
	}
	
	int flag = 0;
	int flagType;
	while(1){
		char c = fgetc(fp);
		if(c == EOF) break;
		/*if(c == INT[flag]) flagType = F_INT;
		else if(c == DOUBLE[flag]) flagType = F_DOUBLE;
		else if(c == VOID[flag]) flagType = F_VOID;

		else if(flag > 0){
			if(flagType == F_INT)
		}*/
	}

	fclose(fp);

}

void execAnalysisDetail(char * fileName){

}



int main(int argc, char * argv[]){
	
	Option options[5];
	int optionsLength = 0;
	int replace = 0;
	
	if(argc == 1) { printf("옵션은 필수 입니다. --help 로 옵션종류를 알아 볼 수 있습니다."); return 0; }
	for(int i=1;i<argc;i++){
		char * token = argv[i];
		
		if(isOption(token)){
			if(strcmp(argv[i], "-help")==0) printOption();
			else if (strcmp(argv[i], "-list")==0) addOption(options, LIST, &optionsLength);
			else if (strcmp(argv[i], "-linecount")==0)  addOption(options, LINE_COUNT, &optionsLength);
			else if (strcmp(argv[i], "-replace")==0) { 
				addOption(options, REPLACE, &optionsLength);
				replace = 1;
			}
			else if (strcmp(argv[i], "-analysis")==0)  addOption(options, ANALYSIS, &optionsLength);
			else if (strcmp(argv[i], "-analysis_detail")==0)  addOption(options, ANALYSIS_DETAIL, &optionsLength);
			else printf("%s 옵션은 존재하지 않습니다\n", argv[i]);	
		}else {
			if(replace) {
				char * old = argv[i+1];
				char * new = argv[i+2];
				printf("%s %s\n", old, new);
				if(old == NULL || new == NULL){
					printf("-replace 할 단어를 적어주세요\n");
					return 0;
				}
				exec(argv[i], options, optionsLength, old, new);
				i = i + 2;
			}
			else exec(argv[i], options, optionsLength, "", "");
			//파일 처리
		}

	}
	
	return 0;
}
