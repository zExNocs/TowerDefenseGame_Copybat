#pragma once

#include <cstdio>

#include "Singleton.h"

class SingletonSubClass1 : public Singleton<SingletonSubClass1> {
private:
	int m_iVar;

public:
	static int VAR;

	void nonstaticPrint() {
		printf("\tnonstatic print:\n");
		m_iVar = 10;
		printf("\t\tstatic number: %d.\n\t\tnonstatic number: %d.\n", VAR, m_iVar);
	}

	static void staticPrint() {
		printf("\tstatic print:\n");
		printf("\t\tstatic number: %d.\n", VAR);
	}
};

class SingletonSubClass2 : public Singleton<SingletonSubClass2> {
private:
	int m_iVar;

public:
	static int VAR;

	void nonstaticPrint() {
		printf("\tnonstatic print:\n");
		m_iVar = 20;
		printf("\t\tstatic number: %d.\n\t\tnonstatic number: %d.\n", VAR, m_iVar);
	}

	static void staticPrint() {
		printf("\tstatic print:\n");
		printf("\t\tstatic number: %d.\n", VAR);
	}
};

int SingletonSubClass1::VAR = 1;
int SingletonSubClass2::VAR = 2;

class SingletonTest
{
public:
	void run() {
		printf("-----Singleton Test-----\n");

		printf("---SubClass 1---\n");
		printf("static print 1:\n");
		SingletonSubClass1::staticPrint();
		printf("static print 2:\n");
		SingletonSubClass1::getInstance()->staticPrint();
		printf("nonstatic print:\n");
		SingletonSubClass1::getInstance()->nonstaticPrint();

		printf("---SubClass 2---\n");
		printf("static print 1:\n");
		SingletonSubClass2::staticPrint();
		printf("static print 2:\n");
		SingletonSubClass2::getInstance()->staticPrint();
		printf("nonstatic print:\n");
		SingletonSubClass2::getInstance()->nonstaticPrint();

		printf("---SubClass 1---\n");
		printf("static print 1:\n");
		SingletonSubClass1::staticPrint();
		printf("static print 2:\n");
		SingletonSubClass1::getInstance()->staticPrint();
		printf("nonstatic print:\n");
		SingletonSubClass1::getInstance()->nonstaticPrint();

		printf("-----Singleton Test End-----\n");
	}
};

