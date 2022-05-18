#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

typedef enum Option{
	LIST,
	LINE_COUNT,
	REPLACE,
	ANALYSIS,
	ANALYSIS_DETAIL
} Option;

void printOption();
void exec();
int isOption();
void addOption();
void execList(char *);
void execLineCount(char *);
void execReplace(char *);
void execAnalysis(char *);
void execAnalysisDetail(char *);

void printOption(){
	printf("-list [file] : 입력파일을 화면에 출력합니다.\n");
	printf("-linecount [file] : 해당 파일의 라인 수를 출력합니다.\n");
	printf("-replace [file] a b : file내에서 a를 b로 치환합니다.\n");
	printf("-analysis [file] : file 에서 사용된 변수와 함수의 갯수를 출력합니다.\n");
	printf("-analysis_detail [file] : file에서 사용된 전역변수의 갯수랑 함수별 분석 결과를 출력합니다.\n");
}

void exec(char * fileName, Option *options, int length){
	
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

void execReplace(char * fileName){

}

void execAnalysis(char * fileName){

}

void execAnalysisDetail(char * fileName){

}



int main(int argc, char * argv[]){
	
	Option options[5];
	int optionsLength = 0;

	if(argc == 1) { printf("옵션은 필수 입니다. --help 로 옵션종류를 알아 볼 수 있습니다."); return 0; }
	for(int i=1;i<argc;i++){
		char * token = argv[i];
		
		if(isOption(token)){
			if(strcmp(argv[i], "-help")==0) printOption();
			else if (strcmp(argv[i], "-list")==0) addOption(options, LIST, &optionsLength);
			else if (strcmp(argv[i], "-linecount")==0)  addOption(options, LINE_COUNT, &optionsLength);
			else if (strcmp(argv[i], "-replace")==0)  addOption(options, REPLACE, &optionsLength);
			else if (strcmp(argv[i], "-analysis")==0)  addOption(options, ANALYSIS, &optionsLength);
			else if (strcmp(argv[i], "-analysis_detail")==0)  addOption(options, ANALYSIS_DETAIL, &optionsLength);
			else printf("%s 옵션은 존재하지 않습니다\n", argv[i]);	
		}else {
			exec(argv[i], options, optionsLength);
			//파일 처리
		}

	}
	
	return 0;
}
