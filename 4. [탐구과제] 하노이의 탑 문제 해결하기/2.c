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

// 원판 이동 함수
int move (int from, int to) { // 인수 from에서 to로 이동
  if (pole[from].length < 1) return 0; // from의 원판에 개수가 1보다 작음 = 원판이 없음 = 이동 불가능
  if (pole[to].length > 0 && pole[to].plate[pole[to].length - 1] < pole[from].plate[pole[from].length - 1]) return 0; // to의 원판에 원판이 있을경우, 기존의 원판이 새로 위에 쌓을 원판의 크기보다 작음 = 이동 불가능

  // 이동이 가능하다면...
  pole[to].plate[pole[to].length] = pole[from].plate[pole[from].length - 1]; // to기둥의 기존의 원판 위에 쌓기
  pole[from].plate[pole[from].length - 1] = 0; // 이미 이동한 from기둥의 원판은 사라짐
  pole[to].length++; // to기둥의 원판 개수가 1 늘어남
  pole[from].length--; // from기둥의 원판 개수가 1 줄어듬
  return 1;
}

int try = 0; // 이동 시도 횟수

// 하노이의 탑 풀기
int solve(int n, int from, int sub, int to) { // n개의 원판을 from번째 기둥에서 sub번째 기둥를 통해 to번째 기둥으로
  try++;
  if (n == 1) { // 처리할 원판이 1개일 경우 to번째 기둥으로 옮기고 끝내기
    move(from, to);
    return 0;
  }
  solve(n - 1, from, to, sub); // 임시로 n - 1개를 sub번째 기둥으로 옮겨놓기
  move(from, to); // 남은 1개(가장 큰 원판을)를 to번째 기둥으로 옮기기
  solve(n - 1, sub, from, to); // sub번째 기둥에 임시로 옮겨둔 원판을 to번째 기둥으로 옮기기
}

// 최초 실행 함수
int main() {
  int count; // 사용할 원판의 개수
  int to; // "0에서 to로 모든 원판을 이동"이란 목표를 저장하기 위한 변수
  scanf("%d %d", &count, &to);
  for (int c = count; c > 0; c--) { // 원판에 배열에 각각 대입
    pole[0].plate[count - c] = c;
  }

  // 원판의 개수 대입
  pole[0].length = count;
  pole[1].length = 0;
  pole[2].length = 0;

  printTower();
  
  solve(count, 0, to > 1 ? 1 : 2, to); // "count개의 원판을 0에서 1 혹은 2을 거쳐 to로 이동"
  printTower();
  printf("%d", try);
  return 0;
}

