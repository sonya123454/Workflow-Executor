#include "stdafx.h"
#include "CppUnitTest.h"
#include "../ConsoleApplication1/executor.h"
#include "../ConsoleApplication1/executor.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1 {		
	TEST_CLASS(MyComp) {
	public:
		TEST_METHOD(MyComp0) {
			Assert::AreEqual(false, my_comp("", ""));
		}
		TEST_METHOD(MyComp1) {
			Assert::AreEqual(false, my_comp("C", ""));
		}
		TEST_METHOD(MyComp2) {
			Assert::AreEqual(true, my_comp("", "C"));
		}
		TEST_METHOD(MyComp3) {
			Assert::AreEqual(false, my_comp("ABC", "ABC"));
		}
		TEST_METHOD(MyComp4) {
			Assert::AreEqual(false, my_comp("ABC1", "ABC"));
		}
		TEST_METHOD(MyComp5) {
			Assert::AreEqual(false, my_comp("ABC10", "ABC2"));
		}
		TEST_METHOD(MyComp6) {
			Assert::AreEqual(true, my_comp("22ABC10", "221ABC10"));
		}
		TEST_METHOD(MyComp7) {
			Assert::AreEqual(false, my_comp("aaaaaaaaa345aa", "a1"));
		}
		TEST_METHOD(MyComp8) {
			Assert::AreEqual(true, my_comp("21", "211"));
		}
		TEST_METHOD(MyComp9) {
			Assert::AreEqual(true, my_comp("1", "aa1"));
		}
	};
}