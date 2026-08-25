<p align="center">
  <img src="https://capsule-render.vercel.app/api?type=waving&color=0:000000,100:1e293b&height=220&section=header&text=UEFI%20VMM%20BOOTLOADER&fontSize=42&fontColor=38bdf8&animation=twinkling&desc=Bare-Metal%20x86-64%20Hypervisor%20Entry%20Environment&descSize=16&descAlignY=62" width="100%" />
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Architecture-x86__64-38bdf8?style=for-the-badge&logo=cpu&logoColor=white"/>
  <img src="https://img.shields.io/badge/Environment-UEFI%20%2F%20EDK2-f97316?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/Target-VMM%20%2F%20Hypervisor-10b981?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/Language-C%20%2F%20ASM-6366f1?style=for-the-badge"/>
</p>

- **Physical Memory Allocation**: UEFI 앱 레벨에서 VMM 바이너리를 읽고 사용할 전용 물리 메모리 공간 할당
- **Custom Page Table Setup**:
  - **2MB, 4KB Page Table** 기준 구성 (0~4 엔트리부터 4KB, 총 6MB 영역 및 `0xFFE00000` 상위 가상 주소 연장 매핑)
  - VMM 가상 시작 주소 : `0x00400000`
- **Custom GDT & CR3 Switching**: UEFI 기본 셋업을 대체하는 자체 GDT 및 CR3 4-Level Page Table 연결
- **Parameter Passing**: CR3, GDT Base, VMM Entry Address, 추가 할당 메모리 포인터 등의 컨텍스트 파라미터를 VMM으로 전달
- **Safe Context Restoration**: VMM 작업 완료 후 안전하게 UEFI 앱 환경으로 복귀, 할당된 메모리 자원 완벽 해제(Clean Cleanup) 및 Safe Exit
- **PROCESSOR**:
  **Start All Aps**: 실제 UEFI에서 매우 간단하게 할 수 있는 작업이지만 직접 하기 위해 VMM 내부에서 진행,
  0xFFE00000의 주소와 프로세서 갯수를 파라미터로 전달
