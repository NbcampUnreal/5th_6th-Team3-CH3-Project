# Project Soul
<img width="1899" height="1065" alt="image" src="https://github.com/user-attachments/assets/2c86e54c-5e3d-409b-bac0-e780505286c9" />
<br></br>

## **프로젝트 개요**
- **프로젝트 이름:** Project Soul
- **프로젝트 기간:** 2025.10.17 ~ 2025.11.10
- **팀 구성:**
    - **팀장:** 이민구 (Character 담당)
    - **팀원:** 박동엽 (Enemy, AI 담당)
    - **팀원:** 강민용 (Game Loop 담당)
    - **팀원:** 변철우 (UI 담당)
    - **팀원:** 이효정 (Weapon 담당)
    - **팀원:** 유수정 (Level Design 담당)
- **링크: [[시연 영상]](https://www.youtube.com/watch?v=k__b-ZPu13c) [[실행파일 다운로드]](https://drive.google.com/file/d/1cINo-GBNU52_PRzVQAOQ8--zELHALrgY/view?usp=sharing)**
<br></br>

## 프로젝트 목표
언리얼 엔진 5로 다크소울 스타일의 `3D 액션 RPG` 게임을 개발하는 것을 목표로 하고 있습니다.

단순히 피해를 주고 받는 구조가 아니라, 다크소울의 `정확한 회피` , `공격 패턴 분석`, `체력·스태미너 관리`에서 오는 긴장감과 몰입감을 구현합니다.

또한, 플레이어가 전투 자체에 집중하고 성취감을 느낄 수 있는 `정교한 전투 루프`를 구축하는 것을 목표로 합니다.
<br></br>

## 개발 환경
- **게임 엔진**: Unreal Engine 5.5
- **IDE:** Visual Studio 2022
- **Compiler:** C++17 이상
- **프로그래밍 언어**: Blueprint / C++
- **플랫폼**: PC
<br></br>

## 게임 진행 흐름
<img width="703" height="560" alt="image" src="https://github.com/user-attachments/assets/58bf2b8d-1576-4032-a0e9-6399d9ce7ed8" />

## 핵심 기능
- **플레이어 시스템**
    - **상태 기반(State Machine) 캐릭터 구조**
    - **Lock-on(Targeting) 시스템**
    - **스태미너 및 체력 관리**
    - **회피(Dodge) 시스템**
    - **공격(Attack) 시스템**
    - **투척(Throw) 시스템**
    - **피격(Hit) 및 사망(Die) 처리**
    - **힐링 포션(Heal) 시스템**
- **AI / Enemy**
    - **AI Perception(시야) 기반 발견/추적**
    - **Behavior Tree + Blackboard**
    - **StateMachine**
    - **적 스탯 및 상태 관리**
    - **애니메이션 연동**
- **무기/투척물 (Weapon)**
    - **무기 부착 및 소켓 관리**
    - **공격 판정(콜리전) 제어**
    - **데미지 처리**
- **GameMode (Game Loop)**
    - **게임 흐름 관리**
    - **목표/클리어 조건**
    - **점수 획득**
    - **입력/카메라 제어**
- **UI**
    - **전투 HUD(HP/MP/Stamina 바)**
    - **타겟/락온 표시**
    - **게임 오버/재시작 UI**
    - **Quest 알림**
- **Level Design**
    - **몰입감과 긴장감을 주는 어두운 분위기의 맵**
    - **플레이에 적합한 효율적인 동선**
    - **적절한 난이도의 몹 배치**
<br></br>
 
## 기술 스택
- **Programming Language:** C++, Blueprint
- **IDE:** Visual Studio 2022
- **Engine / Client:** Unreal Engine 5, Window(PC)
- **Animation:** Animation Blueprint, Anim Montage, Root Motion, Anim Notify
- **AI:** Behavior Tree, Blackboard, AI Perception(Sight), AIController
- **UI:** UMG, Widget Blueprint
- **VFX / Audio:** Niagara, Sound Cue, Sound Attenuation
- **Version Control System:** Git, Git LFS, GitHub
<br></br>

## 트러블 슈팅
- **Character의 God Object Issue (이민구)**
  <details> <summary><strong>펼치기</strong></summary>
  첫 번째는 Character 클래스 내부에서 이동, 공격, 회피 등 모든 로직을 직접 처리하면서 상태별로 다른 동작을 제어하기 위해 다수의 조건문이 중첩된 상황이었는데, 이로 인해 코드 가독성이 저하되고, 유지보수가 어려운 구조였습니다.
  
  또한, 모든 상태 로직이 단일 클래스에 집중되어 있어 상태 전이를 유연하게 제어하기 어렵고, 새로운 동작을 추가할 때 기존 분기 로직을 수정해야해서 버그가 생길 가능성이 증가했습니다.
    
  이 문제를 해결하기 위해 FSM 구조를 도입하여 각 상태를 별도의 클래스로 분리했습니다.
  
  StateMachine이 상태 전환을 관리하도록 설계하고, 각 상태의 로직을 해당 클래스에서 구현하는 방식으로 변경했습니다.
  
  이로 인해 코드 가독성 및 유지보수가 향상되었고, 상태 간 전이 로직이 명확해져 디버깅 효율이 상승했습니다.
  
  또한, 상태 추가 시 새로운 클래스만 추가하면 되기에 기존 코드에 미치는 영향을 최소화 할 수 있었습니다.
    
  <img width="793" height="429" alt="image" src="https://github.com/user-attachments/assets/71356096-5b3b-4a74-aff3-f4c574264fc1" />
  </details>

- **Character Stat 관리 문제 (이민구)**
  <details> <summary><strong>펼치기</strong></summary>
  Character가 Health, Mana, Stamina 총 3개의 Stat을 가지고 있는데, 각 Stat 별로 필요한 변수와 함수를 선언하면 관리가 복잡하고 유지보수가 좋지 않았습니다.
    
  이를 해결하기 위해 Stat Struct를 만들고, Struct 내부에서 값 처리, 무결성 검사를 처리하도록 설계했습니다.
  
  <img width="780" height="483" alt="image" src="https://github.com/user-attachments/assets/ff85ca2b-4f02-4b8e-a5aa-dd207ba3db8d" />

  그리고 3개의 Stat을 가지는 Player Stats Struct를 생성하여 Player는 하나의 Player Stat 구조체만 관리하면 되도록 했습니다.

  <img width="760" height="486" alt="image" src="https://github.com/user-attachments/assets/c8c3cb9a-f520-4363-b92b-e9a6b6b377ac" />

  <img width="1160" height="441" alt="image" src="https://github.com/user-attachments/assets/22738cd2-dc14-4324-96fe-1b1e3087cca1" />
  </details>

- **Enemy의 Player 인식 문제 (박동엽)**
  <details> <summary><strong>펼치기</strong></summary>
  첫 번째는 AttackState중 캐릭터가 구르기를 통해 순간적으로 시야에 사라졌을때 공격 사거리내에는 있지만 플레이어를 못찾아 적이 멈추는 문제가 발생했습니다.

  <img width="552" height="317" alt="image" src="https://github.com/user-attachments/assets/55282fd4-0722-464b-b509-cf8eda3db743" />

  이는 Hit, Chase, Attack과 같은 전투 상황에서는 시야의 범위를 360도로 올려 플레이어를 잃어버리지 않도록 하여 해결했습니다.
  </details>
    
- **Enemy 연속 Hit State 전환 문제 (박동엽)**
  <details> <summary><strong>펼치기</strong></summary>
  적에게 데미지를 연속적으로 줄 때, Hit State에서 Hit State로 전환이 되지 않아 피격 중임에도 Hit 애니메이션 재생 후 바로 Attack State가 되는 문제가 발생했습니다.
    
  일반 몬스터의 경우는 HitState에서 조건을 충족한다면 바로 Hit State로 상태 전환을 할 수 있게 하여 연속적인 피격이 가능하도록 했습니다.
  
  보스의 경우 오히려 해당 문제를 적용시켜 피격 애니메이션 재생을 막아 난이도를 더하는 장치로 사용했습니다.
    
  <img width="809" height="429" alt="image" src="https://github.com/user-attachments/assets/b33e4980-4e89-4140-a624-c5c0a390331f" />
    
  <img width="888" height="443" alt="image" src="https://github.com/user-attachments/assets/4133e145-0fc9-4158-aa77-bb2495e9e716" />

  <img width="956" height="179" alt="image" src="https://github.com/user-attachments/assets/10ba2df5-6e9c-4a23-9c38-b4f4824e9abe" />
  </details>
    
- **Enemy Count 문제 (강민용)**
  <details> <summary><strong>펼치기</strong></summary>
  StartGame 함수가 너무 빨리 호출이 되어 적의 수를 인식하지 못하는 현상이 발생했습니다.
    
  이를 해결하기 위해 로직 간 호출 순서를 변경하여 적 스폰, 적 카운트, UI 반영이 가능하도록 했습니다.
  </details>
    
- **게임의 승/패 구분 문제 (강민용)**
  <details> <summary><strong>펼치기</strong></summary>
  UI와 연동할 때, 클리어와 패배를 구분하기 어렵다는 피드백을 받아 EndGame 함수에 Bool 인자를 추가하여 게임의 승리/패배를 명확히 알 수 있도록 했습니다.
  </details>
    
- **월드 위치 → 스크린 좌표 전환 문제 (변철우)**
  <details> <summary><strong>펼치기</strong></summary>
  월드 위치를 스크린 좌표로 투영한 좌표가 맞지않는 문제가 발생 했었습니다.
  
  투영 시 사용한 ProjectWorldLocationToScreen()은 화면 해상도 기준 픽셀 좌표를 반환하는데, 좌표를 적용해야하는 Widget은 디자인 해상도 기준이라 두 해상도가 동일하지 않은 경우 의도와 다른 결과가 나오게 되었습니다.

  <img width="417" height="259" alt="image" src="https://github.com/user-attachments/assets/a3e6c2c8-c38e-4718-a383-dec261376dd7" />

  해결방법은 UWidgetLayoutLibrary::GetViewportScale()로 현재 해상도와 디자인해상도의 스케일 비율을 구해 투영 좌표를 보정해 해결했습니다.

  <img width="1025" height="252" alt="image" src="https://github.com/user-attachments/assets/042a3771-5ff8-464b-84f1-98b48bc76c2a" />
  </details>
    
- **GameInstanceSubsystem와 Actor의 초기화 시점 문제 (변철우)**
  <details> <summary><strong>펼치기</strong></summary>
  UI전용 GameInstanceSubsystem 생성자에서 플레이어, 몬스터에 접근해 함수 바인딩 시, 바인딩이 안되는 문제입니다.
  
  이유는 GameInstanceSubsystem 생성 시점이 월드 생성보다 빠르기 때문에 아직 생성되지 않은 플레이어, 몬스터에 접근했기 때문이였습니다.
    
  따라서, 월드에 액터 생성이 완료된 시점에 바인딩을 진행하여 해결했습니다.
  </details>
<br></br>

## 빌드/실행 방법
1. **사전 준비**
    - **엔진**: Unreal Engine 5.5
    
2. **에디터에서 패키징**
    - `Project.uproject` 더블 클릭 → 에디터 실행
    - **Edit → Project Settings → Packaging**
        - Configuration: Shipping
        - Full Rebuild 체크, Use Pak File 체크
    - 에디터 상단의 Platforms - Windows - Packaging Project
    
    <img width="597" height="497" alt="image" src="https://github.com/user-attachments/assets/13f5eb0d-720d-4bf6-a5d4-ac78a5ea5845" />

    - 출력 폴더 선택

3. **패키징 완료 후**
    - 출력 폴더에서 Windows → `ProjectSoul.exe` 실행
