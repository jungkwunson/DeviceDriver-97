#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Day10_devicedriver/DeviceDriver.cpp"

using namespace testing;
using namespace std;

//class DDMock : public DDAPI
//{
//public:
//	MOCK_METHOD(unsigned char, ddread, (long address), (override));
//	MOCK_METHOD(void, ddwrite, (long address, unsigned char data), (override));
//};
//
//TEST(TestMockRead, MockRead1) {
//	DDMock dd_mock;
//	EXPECT_CALL(dd_mock, ddread)
//		.Times(5);
//	char ch;
//	ch = dd_mock.ddread(0x00);
//	cout << ch << "\n";
//	ch = dd_mock.ddread(0x01);
//	cout << ch << "\n";
//	ch = dd_mock.ddread(0x02);
//	cout << ch << "\n";
//	ch = dd_mock.ddread(0x03);
//	cout << ch << "\n";
//	ch = dd_mock.ddread(0x04);
//	cout << ch << "\n";
//
//	//EXPECT_THAT(0, ddread(0x00));
//
//	//EXPECT_THAT(0, Eq(0));
//	//EXPECT_EQ(1, 1);
//	//EXPECT_TRUE(true);
//}


class MockDevice : public FlashMemoryDevice
{
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(DEVDRIVER_READ, Callread) {
	MockDevice mock_device;

	EXPECT_CALL(mock_device, read)
		.Times(5);

	DeviceDriver driver(&mock_device);
	driver.read(0xa);

}

TEST(DEVDRIVER_READ, Exception) {
	MockDevice mock_device;

	EXPECT_CALL(mock_device, read(0x2))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x3));


	DeviceDriver driver(&mock_device);
	EXPECT_THROW(driver.read(0x2), std::exception);
}

TEST(DEVDRIVER_READ, Time) {
	MockDevice mock_device;

	EXPECT_CALL(mock_device, read)
		.Times(5);


	DeviceDriver driver(&mock_device);

	time_t start = clock();
	driver.read(0x2);
	time_t end = clock();

	EXPECT_THAT((end - start), Ge(1000));

}
