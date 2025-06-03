all: build

build:
	cd source && make

run:
	./tema1

pack:
	zip -r Tema1_Badulescu_Andrei-Marcel_314CC.zip source Makefile README.md

clean:
	rm -rf tema1