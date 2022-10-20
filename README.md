# cub3D :video_game:

__mlx를 활용한 간단한 게임 만들기__

------

## 목차
[1. Mandatory Part](#mandatory-part)

[2. Bonus Part](#bonus-part)

------

# To Do List
~~좌우반전 해결~~

~~이미지 출력이 예시랑 다른 방식으로 이루어짐.~~

~~sprite 벽 통과 현상 해결~~

~~출구 구현~~

~~Ray-casting, sprite 원리에 대한 이해~~

~~미니맵 수정 필요~~

~~맵 파싱 부터 최적화~~

~~맨 마지막 개행 없을때 에러~~

~~맵이 양옆으로 뚫려있을때 에러~~

~~load image 경로 이상할때 에러~~

~~정밀도 비교~~

------
# Mandatory Part
- __원활한 창 관리(창 변경, 최소화 등)구현__  :white_check_mark:
- __벽 텍스쳐(동서남북) 구현__  :white_check_mark:
- __천장 및 바닥(RGB) 구현__  :white_check_mark:
- __이미지 관리__
	- 오른쪽, 왼쪽 키를 통한 알맞은 시점변환 구현  :white_check_mark:
	- W, A, S, D 움직임 구현  :white_check_mark:
	- ESC로 종료 구현  :white_check_mark:
	- x눌렀을 때 종료 구현  :white_check_mark:
	- 천장과 바닥 new image로 구현 :white_check_mark:
- __맵__
	- 0, 1, E, W, S, W와 공백만 허용  :white_check_mark:
	- 맵은 벽으로 막혀있어야 함  :white_check_mark:;
	- 맵 부분을 제외하고 다른 요소들은 빈 줄로 나눠져 있어야 함  :white_check_mark:
	- 맵 부분이 마지막에 오는 것을 제외하면 다른 요소들의 순서는 상관 없음  :white_check_mark:;
	- 맵 부분을 제외하고 다른 요소들의 정보는 하나 이상의 공백으로 구분되어있어야 함  :white_check_mark:
	-
- __애러메세지 출력__ :white_check_mark:

------
# Bonus Part
(디펜스 할수 있으면 다른 함수 써도 됨)
- __미니맵__  :white_check_mark:
- __벽 충돌__  :white_check_mark:
- __문__  :white_check_mark:
- __스프라이트 애니메이션__  :white_check_mark:
- __마우스 시점변환__  :white_check_mark:

:black_square_button:
:white_check_mark:
