/**
 * @name 포인터로 문자열 처리하기
 * @author 박민혁
 */

#include <stdio.h> // 기본 입출력을 수행하기 위해 stdio.h를 불러온다
#define MAX_LENGTH 100 // 최대 문자열 크기를 제한한다

// 같은 문자열인지 확인하는 함수
int sameStr (char *str1, char *str2) { // 배열들의 첫번째 인덱스 값들을 받는다
  int isSame = 1; // 두 문자열이 같다고 가정한 후, 같지 않음을 증명한다

  for (int c = 0; c < MAX_LENGTH && isSame; c++) { // 같지 않음을 알았을때 더이상의 불필요한 계산을 막기위해 isSame이 1일때만 작동한다
    if (*(str1 + c) != *(str2 + c)) isSame--; // "배열들의 첫번째 인덱스 값 + c"주소를 가르키는 포인터의 값을 가져와, 동일한지 확인한다, 동일하지 않을경우 isSame을 0으로 만든다
  }

  return isSame; // isSame을 반환한다
}

// 문자열에 포함된 띄어쓰기를 언더바로 바꾸는 함수
void toSnakeCase (char *str) { // 배열의 첫번째 인덱스 값을 받는다
  for (int c = 0; c < MAX_LENGTH; c++) { // 문자열의 각 문자마다 수행한다
    if (*(str + c) == ' ') *(str + c) = '_'; // "배열들의 첫번째 인덱스 값 + c"주소를 가르키는 포인터의 값을 가져와, 스페이스 일경우 언더바로 바꾼다
  }
}

// 프로그램 실행시 처음 작동되는 함수
int main () {
  char str1[MAX_LENGTH] = "", str2[MAX_LENGTH] = ""; // 받을 문자열 2개를 선언한다

  printf("첫번째 문자열을 입력하세요> ");
  gets(str1); // 문자열을 입력받는다
  printf("두번째 문자열을 입력하세요> ");
  gets(str2); // 문자열을 입력받는다


  if (sameStr(str1, str2)) printf("true\n"); // 만약 같은 문자열이면, true를 출력한다
  else printf("false\n"); // 아니라면, false를 출력한다

  toSnakeCase(str1); // str1에 포함된 띄어쓰기를 언더바로 바꾼다
  printf("%s\n", str1); // str1을 출력한다
  return 0; // 프로그램을 정상 종료한다
}
