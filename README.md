# Qt + OpenCV + Android 
1. 개발환경 설정
  1. Qt 및 안드로이드 개발환경 설정
    1. QtCreator를 실행하고 'Tools > Options > Android 에 보면 필요한 파일들을 받을 수 있게, 버튼으로 링크를 제공한다. 
    2. JDK, Android SDK, Android NDK, Ant 를 설치하고 각 경로를 지정해준다.
    3. 실제 Android 기기가 있으면 상관없지만 없다면 바로 아래 AVD Manager에서 가상 기기를 생성한다.
  2. OpenCV 라이브러리 설정
		1. http://opencv.org/ 에서 오른쪽 DOWNLOADS에 OpenCV for Android 선택하여 다운로드
		2. 적절한 위치에 압축을 해제

2. 예제 프로그램 실행
	1. Qt 프로젝트 생성
		1. Qt Widget Application 선택
		2. Kits 단계에서 Android 선택(x86, armeabi-v7a 목적에 맞게 선택)
		3. 다음, 다음, 다음, 다음, 다음, 다음... 완료!
	2. 프로젝트 빌드 설정 (Android Manifest 생성)
		1. QtCreator의 왼쪽 Projects 탭 선택
		2. Build Stesps의 Build Android APK 오른쪽의 Detail 선택
		3. Create Templates 버튼을 눌러 AndroidManifest.xml 생성
			1. 목적에 맞게 각 항목들을 편집 가능
			2. 별다른 설정이 필요 없다면 가만히 놔둬도 됨
	3. 포함 및 라이브러리 파일 복사
		1. Qt 프로젝트 폴더에 opencv_lib 폴더 생성 (이름은 적절하게 바꿔도 됨)
		2. 1-ii-b 단계에서 압축해제한 곳으로 이동하여 sdk/native/libs 안의 목적 플랫폼을 복사하여 opencv_lib/libs 폴더에 복사
			- 2-i-b 단계에서 선택한 플랫폼을 복사
		3. sdk/native/jni/include 를 복사하여 opencv_lib 폴더에 복사
		4. libs 안의 libopencv_java3.so 파일은 Android Manifest가 있는 곳으로 이동(NDK 폴더로 이동하는 것 같음. 자세한 건 아직 파악 못함)
			- android/libs/플랫폼 폴더로 이동
	4. Qt 프로젝트에 라이브러리 추가
		- .pro 파일을 열어 하단에 다음 명령어를 추가
      ```
      # 포함 파일 위치 추가
      INCLUDEPATH += $$PWD/opencv_lib/android/include
      # 플랫폼에 맞게 라이브러리가 있는 폴더를 추가
      LIBS += -L$$PWD/opencv_lib/android/libs/x86
      # 필요한 라이브러리 추가
      LIBS += -lopencv_core -lopencv_highgui -lopencv_imgcodecs pencv_imgproc -lopencv_java3
      ```
	5. 예제 코드 빌드 후 실행
