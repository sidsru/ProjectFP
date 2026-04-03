# 🎮 Project:FP

## 📌 Overview

**Co-op Survival Factory**는 1~4인이 함께 협력하여 자원을 수집하고, 이를 가공 및 자동화하여 더 높은 가치를 창출하는 **멀티플레이 생존 게임**입니다.

기존 협동 생존 게임의 “수집 → 탈출” 구조에서 확장하여,
**“수집 → 가공 → 자동화 → 리스크 증가”**라는 새로운 게임 루프를 중심으로 설계되었습니다.

---

## 🚀 Key Features

### 👥 Multiplayer (Steam 기반)

* 1 ~ 4인 협동 플레이
* Steam 친구 초대 기능
* 세션 생성 / 참가 시스템

---

### 🎙️ Proximity Voice Chat

* 인게임 음성 채팅 지원
* 거리 기반 볼륨 감소
* 장애물에 따른 소리 감쇠 (Line Trace 기반)

> 단순 음성 채팅이 아닌 **공간 기반 커뮤니케이션 시스템** 구현

---

### 🧠 AI (Sound-Based Behavior)

* 몬스터는 소리를 기반으로 플레이어를 탐지
* 감지 요소:

  * 플레이어 음성
  * 팩토리 소음
* 행동:

  * 순찰 → 소리 감지 → 추적

---

### ⚙️ Factory System (Core Feature)

게임의 핵심 차별화 요소

#### 구성

* Resource 입력
* Conveyor 기반 이동
* Machine을 통한 가공
* 고급 자원 출력

#### 특징

* 자동화 가능
* 효율 증가

#### 리스크

* 소음 증가 → 몬스터 유입
* 전력 소비
* 과부하 시 시스템 정지 또는 파괴

> 효율과 생존 사이의 **트레이드오프 설계**

---

### 🔁 Core Gameplay Loop

```
탐험 → 자원 수집 → 탈출
        ↓
    (확장)
        ↓
수집 → 가공 → 자동화 → 리스크 증가 → 반복
```

---

### 💰 Economy System

* 자원 판매 → 화폐 획득
* 장비 구매 시스템

#### 장비 예시

* 통신 거리 증가 장비
* 소음 감소 장비
* 이동 속도 증가 장비

---

### 🖥️ UI System

* 로비 UI
* 인게임 HUD
* 인벤토리 시스템
* 팩토리 상태 UI

---

## 🛠️ Tech Stack

* **Engine**: Unreal Engine
* **Language**: C++
* **Network**: Steam Online Subsystem
* **Architecture**:

  * Component 기반 설계
  * Subsystem 활용
  * Data Asset 기반 데이터 관리

---

## ⚙️ Technical Highlights

### 🔗 Network Synchronization

* Actor Replication
* RPC 기반 이벤트 처리

---

### 🎧 Spatial Audio System

* 거리 기반 볼륨 계산
* Line Trace 기반 장애물 감쇠
* 소리 이벤트를 AI 시스템과 연동

---

### 🧩 Data-Oriented Design

* Data Asset을 통한 아이템 및 시스템 관리
* 확장 가능한 구조 설계

---

### ⚡ Performance Optimization

* Tick 최소화 (이벤트 기반 처리)
* Object Pooling 적용

---

## 📂 Project Structure (예시)

```
/Source
  /Character
  /Factory
  /AI
  /Network
  /UI
  /System

/Content
  /Blueprints
  /DataAssets
  /UI
```

---

## 🎯 Development Scope

### ✅ Must Have

* Steam 기반 멀티플레이
* 거리 기반 음성 채팅
* 기본 게임 루프
* 팩토리 시스템 (최소 단위)
* AI 1종

---

### 🔄 Optional

* 고급 자동화 시스템
* 다양한 몬스터
* UI 고도화

---

## 📅 Development Timeline

| 기간  | 내용                 |
| --- | ------------------ |
| 1개월 | 멀티플레이 및 기본 시스템     |
| 2개월 | 게임 루프 + AI + 음성 채팅 |
| 3개월 | 팩토리 시스템            |
| 4개월 | 폴리싱 및 최적화          |

---

## 🎯 Goal

이 프로젝트의 목표는 단순한 게임 제작이 아닌,
다음과 같은 기술 역량을 증명하는 것입니다:

* 네트워크 프로그래밍
* 공간 기반 오디오 시스템
* AI 설계
* 데이터 중심 아키텍처
* 시스템 간 상호작용 설계

---

## 🔥 Summary

> 이 프로젝트는
> **협동, 소리, 자동화 시스템이 결합된 복합 문제 해결형 게임**입니다.

단순 기능 구현을 넘어
**설계 의도와 기술 선택을 설명할 수 있는 프로젝트**를 목표로 합니다.
