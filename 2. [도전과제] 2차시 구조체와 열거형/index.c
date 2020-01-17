/**
 * 구조체 사용하기
 * Made by 박민혁
 */

#include <stdio.h> // Standard I/O
#include <math.h> // math

// 한 점을 나타내는 구조체 Point
typedef struct Point {
  int x, y; // 특정한 한 점을 가르키기 위해 x좌표와 y좌표를 가진다
} Point;

// 두 점을 받았을때 두 점 사이의 거리(즉, 삼각형의 한변의 길이)를 반환하는 함수
double cacuDistance (Point a, Point b) {
  return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2)); // 도전과제 설명지에 적힌 식을 참고하였다 (sqrt와 pow함수는 각각 제곱근과 제곱을 계산&반환한다)
}

// 받은 배열을 가장 값이 큰 순서대로(즉, 변의 길이가 긴 순서대로) 정렬하는 함수 (반환값은 없다)
void bubbleSort (double arr[]) { // 물론 소트를 쓰지 않거나 다른 소트를 쓸수도 있으나, 코드를 예쁘게 하기 위해 :)
  double temp; // 서로 자리를 바꾸기(스왑하기) 위해 임시로 만든 변수
  for (int i = 0; i < 2; i++) { // 2 만큼 반복(outer)
    for (int j = 0; j < 2-i; j++) { // 2-i 만큼 반복(inner)
      if (arr[j] < arr[j + 1]) { // 만약 이번 값이 다음 값보다 작을 경우
        temp = arr[j]; // 임시로 만든 변수에 이번 값을 대입
        arr[j] = arr[j + 1]; // 이번 값에 다음 값을 대입
        arr[j + 1] = temp; // 다음 값에 임시로 만든 변수를 대입 (즉, 서로 이번 값과 다음 값의 자리를 서로 바꾼다)
      }
    }
  }
}

// 코드 실행 초기 실행되는 함수
int main () {
  Point points[3]; // 한 점을 의미하는 Point 구조체 3개의 배열을 선언
  for (int c = 0; c < 3; c++) { // 각 구조체에..
    printf("%d번째 좌표> ", c + 1); // Prompt
    scanf("%d %d", &points[c].x, &points[c].y); // x와 y좌표를 정해준다
  }

  double distances[3]; // 세 변의 길이를 담는 배열
  for (int c = 0; c < 3; c++) { // 각 점(points)에..
    distances[c] = cacuDistance(points[c], points[c + 1 > 2 ? 0 : c + 1]); // 이번 점과 다음 점 사이의 거리(마지막 점일경우 첫번째 점과의 거리)를 측정후 대입
  }

  bubbleSort(distances); // 변의 길이가 긴 순서대로 정렬(버블소트)

  if (distances[0] < distances[1] + distances[2]) { // 만약 가장 긴 변의 길이가 나머지 변들의 길이의 합보다 작을경우
    printf("true"); // true출력
  } else { // 아닐경우
    printf("false"); // false출력
  }
  return 0; // 정상 종료
}
