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
		
		TEST_METHOD(testmessage)
		{
			message* msg = new message();

			msg->setopcode("test");

			msg->makemsg();

			Assert::AreEqual(std::string("test"), msg->msg_as_s);

		}
	};
}
