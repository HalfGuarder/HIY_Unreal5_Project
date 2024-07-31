24.07.22
<언리얼5>
- 게임 엔진들은 영화 촬영에 비유할 수가 있다.
-- 게임 엔진들은 영화 촬영에 비유할 수 있다.
=> 세트장 : 월드
=> 배우 : Actor

[유니티]
- 컴포넌트를 활용해 바닥부터 생성 가능

[언리얼]
- 액터 : 소품

액터 -> 폰 -> 캐릭터 상속 구조
- 언리얼은 상속 구조와 컴포넌트 패턴이 핵심 철학
-- 언리얼의 모든 오브젝트들은 UObject를 상속 받아 만들어 진다
... 앞에 U가 붙으면 UObject를 상속 받았다는 컨벤션
... Actor만 제외 / Actor를 상속 받는 자식들은 앞에 A가 붙는다
=> 월드에 있으려면, Transform(위치, 크기, 회전)을 포함해야 하기 때문
- 구조체, 함수도 웬만하면 UObject를 상속 받는 것이 좋음
- F가 붙으면 UObject를 상속 받는 객체가 아니다

UPROPERTY

ConstructorHelpers
 - 생성자에서 언리얼 에디터에 존재(프로젝트 파일에 저장 되어 있는)하는 
정보들을 읽어올 수 있게 돕는다

- Delegate
델리게이트 <-> 클래스 객체로 직접 함수 호출
- 직접 호출 단점 : 클래스 간의 결합도

- 동적 할당
-- Actor => SpawnActor
-- Component => CreateDefaultSubobject

- 충돌
-- Block
-- Overlap

액터 = SpawnActor
액터 x = CreateDefaultSubobject

과제
데이터 매니저 - 싱글톤
게임 인스터스
how get data from datatable use raw

과제
-인벤토리 컴포넌트 만들기
--Log Inven
--Get ~
--Drop ~

++몬스터 잡으면 아이템 드롭
++아이템 데이터 테이블
