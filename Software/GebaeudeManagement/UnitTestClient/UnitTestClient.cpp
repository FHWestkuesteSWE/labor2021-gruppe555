#include "pch.h"
#include "CppUnitTest.h"
#include "message.h"
#include "string"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestClient
{
	TEST_CLASS(UnitTestClient)
	{
	public:
		
		TEST_METHOD(testmessageopcode)
		{
			message* msg = new message();

			msg->setopcode("test");

			msg->makemsg();

			Assert::AreEqual(std::string("test"), msg->msg_as_s);

		}

		TEST_METHOD(testmessageraum)
		{
			message* msg = new message();

			msg->setraum("000");

			msg->makemsg();

			Assert::AreEqual(std::string("000"), msg->msg_as_s);

		}
	};
}
