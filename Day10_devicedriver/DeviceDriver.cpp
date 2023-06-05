#include "DeviceDriver.h"
#include <exception>
#include <cstdio>
#include <windows.h>

using namespace std;

//#define interface struct
//interface DDAPI {
//    //virtual string getDBName() = 0;
//    virtual unsigned char ddread(long address) = 0;
//    virtual void ddwrite(long address, unsigned char data) = 0;
//};

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    int result = 0;

    // TODO: implement this method properly
    int firstresult = (int)(m_hardware->read(address));
	Sleep(200);

    for(int i = 2 ; i<=5; i++)
    {
        int nResult = (int)(m_hardware->read(address));
        Sleep(200);

    	if(nResult == firstresult) continue;
       
    	throw std::exception("Exception!!");
    }

    return firstresult;
}

void DeviceDriver::write(long address, int data)
{

    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}
