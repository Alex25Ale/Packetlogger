#include "AddressFunctions.h"
#include "AddressManager.h"
#include <cstring>
#include <QByteArray>

class CNosString
{
private:
    std::size_t m_nLength;
    char m_szPacket[5192];

public:
    CNosString(char* i_szPacket)
    {
        m_nLength = std::strlen(i_szPacket);
        std::memcpy(m_szPacket, i_szPacket, m_nLength);
        m_szPacket[m_nLength] = '\0';
    }

    char* data() { return this->m_szPacket; }
    std::size_t size() const { return this->m_nLength; }
};

void SendPacket(const QString& i_sString)
{
    QByteArray abData(i_sString.toLocal8Bit());
    CNosString oString(abData.data());
    char* szPacket(oString.data());

    DWORD dwPacketClass = AddressManager::Get(EAddress::APacketClassPointer);
    DWORD dwPacketCall = AddressManager::Get(EAddress::ASendPacket);

    __asm {
        mov eax, dwPacketClass
        mov eax, [eax]
        mov eax, [eax]
        mov edx, szPacket
        call dwPacketCall
    }
}

void RecvPacket(const QString& i_sString)
{
    QByteArray abData(i_sString.toLocal8Bit());
    CNosString oString(abData.data());
    char* szPacket(oString.data());

    DWORD dwPacketClass = AddressManager::Get(EAddress::APacketClassPointer);
    DWORD dwPacketCall = AddressManager::Get(EAddress::ARecvPacket);

    __asm {
        mov eax, dwPacketClass
        mov eax, [eax]
        mov eax, [eax]
        mov eax, [eax + 0x34]
        mov edx, szPacket
        call dwPacketCall
    }
}
