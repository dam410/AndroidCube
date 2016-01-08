all: build.xml
	ndk-build
	ant debug

build.xml:
	android update project --path . --target 1

deploy:
	adb -d install -r bin/NativeActivity-debug.apk

.PHONY: clean

clean:
	rm -rf bin libs obj

.PHONY superclean:

superclean: clean
	rm -f build.xml local.properties proguard-project.txt project.properties
