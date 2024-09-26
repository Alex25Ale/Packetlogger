#include "HookFunctions.h"
#include "PacketUI.h"
#include <iostream>
#include <QTextCodec>

extern CPacketUI* g_pUi;

bool HookFunctions::HandleRecvPacket(char* i_szPacket) {
    QString sPacket = QString::fromLocal8Bit(i_szPacket).replace('\n', "");

    QTextCodec* codec = QTextCodec::codecForName("windows-1250");
    QTextDecoder decoder{ codec };
    QString str = decoder.toUnicode(i_szPacket).trimmed();  // Trim the decoded string

    emit g_pUi->addPacket(str, EPacketType::PTReceive);  // Emit the trimmed string
    std::cout << "Received Packet: " << sPacket.toStdString() << std::endl;

    return g_pUi->recvBlocker().isFiltered(sPacket);
}

bool HookFunctions::HandleSendPacket(char* i_szPacket) {
    QString sPacket = QString::fromLocal8Bit(i_szPacket).replace('\n', "");

    emit g_pUi->addPacket(sPacket, EPacketType::PTSend);
    std::cout << "Sent Packet: " << sPacket.toStdString() << std::endl;

    return g_pUi->sendBlocker().isFiltered(sPacket);
}
