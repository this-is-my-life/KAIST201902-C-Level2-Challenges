/**
 * 희문 구별하기
 * Made By 박민혁
 */


// 쉬운 설명을 위해 입력을 "hello"로 받았다고 합시다
// 음 근데 최대한 쉽게 설명하려 해도 잘 안되요;; (그래서 따로 파일을 만들어 뒀어요)

#include <stdio.h> // Standard I/O
#include <string.h> // String Header

typedef enum { false, true } bool; // 불리언(bool)이라는 참, 거짓을 갖는 열거형을 만든다

char input[33]; // 입력받을 문자열이 저장될 변수
bool palindromed = true; // 일단 회문인 단어이라 생각하고 회문이 아니라는 것을 증명한다

void proc (char str[], int back) { // 회문이 아니라는 것을 증명하는 함수 (함수가 처음 실행되었다고 가정하자)
  int front = strlen(str) - 1 - back; // back은 마지막 문자의 인덱스를 의미하므로 처음 문자의 인덱스, front를 구해준다, 그러면 front은 hello의 첫번째 값 h의 인덱스 0을 가지고 있고 back은 hello의 마지막 값 o의 인덱스 4를 가지고 있다
  if (front != back && back > 0) { // 입력받은 문자열이 홀수일경우 언젠가 back과 front가 같은 숫자일수 있고 문자열의 마지막 값의 인덱스는 음수일 수 없으므로 이 두 경우에는 무시한다
    if (str[front] != str[back]) palindromed = false; // 입력받은 문자열의 front를 인덱스로 갖는 문자와 back을 인덱스로 갖는 문자가 다를경우 회문이 아니다
    else proc(str, back - 1); // 같을경우 back을 1 감소 시킨후 재귀한다
  }
}

// 최초 실행 부분
int main () {
  scanf("%s", &input); // 문자열을 입력받는다
  
  proc(input, strlen(input) - 1); // 문자열 마지막 값의 인덱스는 문자열의 길이 - 1이다, 이것으로 proc함수를 실행한다

  if (palindromed == true) { // 회문일경우
    printf("true"); // true출력
  } else { // 아닐경우
    printf("false"); // false출력
  }

  return 0; // 정상 종료
}
