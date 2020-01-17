#include <stdio.h> // Standard I/O
#define PLATE_MAX 50 // 원판의 최대 개수

// 기둥 구조체
struct {
  int plate[PLATE_MAX]; // 원판의 배열
  int length; // 원판의 개수
} pole[3];

// 기둥 출력 함수
void printTower() {
  int i, j;
  for (i = 0; i < 3; i++) { // 기둥 마다...
    printf("%d: ", i);
    if (pole[i].length < 1) printf("x"); // 만약 원판이 없을때..
    else {
      for (j = 0; j < pole[i].length; j++) { // 원판 마다...
        printf("%d ", pole[i].plate[j]);
      }
    }
    printf("\n"); // LF (Line Feed)
  }
}

// 최초 실행 함수
int main() {
  int count; // 사용할 원판의 개수
  scanf("%d", &count);
  for (int c = count; c > 0; c--) { // 원판의 배열에 각각 대입
    pole[0].plate[count - c] = c;
  }
  pole[0].length = count; // 원판의 개수 대입
  printTower();
  return 0;
}

